//Header for this file
#include "modetrack.h"
//C System-Headers
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <fcntl.h>//fopen(),fclose()
#include <unistd.h>//read(), write()
//C++ System headers
#include <vector>//vector
#include <string>//string
#include <fstream>//iss*
#include <chrono>// timing functions
#include <cmath>//sqrt, abs
#include <iostream>//cout
#include <typeinfo>//typeid
#include <algorithm> // transform, find
#include <functional> // plus/minus
#include <utility>//std::make_pair
#include <map>//std::map
//Boost Headers
#include <boost/algorithm/string.hpp>//split() and is_any_of for parsing .csv files
#include <boost/lexical_cast.hpp>//lexical cast (unsurprisingly)
//Miscellaneous Headers
#include <omp.h>//OpenMP pragmas
//Project specific Headers
//


ModeTrack::ModeTrack() {

    //initialize best fit curves
    PopulateBestFitCurves();
}


ModeTrack::~ModeTrack() {}

inline void SubtractBackground(std::vector<std::vector<double>>& data,std::vector<double>& background) {

    for(auto& val:data) {
        val.resize(background.size());
        std::transform(background.begin(), background.end(), val.begin(), val.begin(),std::minus<double>());
    }
}

inline void SubtractBackground(std::vector<double>& data,std::vector<double>& background) {

    data.resize(background.size());
    std::transform(data.begin(), data.end(), background.begin(), data.begin(),std::minus<double>());
}

double ModeTrack::GetPeaks( const std::vector<data_triple<double> >& data_str, int mode_number, Method filter_method ) {

    std::vector<double> power_list = data_triples_to_power( data_str );

    SubtractBackground( power_list, background) ;

    auto peak_list = FindPeaks(power_list,filter_method);
    std::cout << "Number of peaks identified: " << peak_list.size() << std::endl;

    //check to see if any mode were identified
    //if not return the default value of 'zero'

    if( peak_list.size() >= 1 ) {

        auto identified_peaks = CompareAndFill(peak_list, data_str);

        //check to see if requested mode number has been identified
        //if it has return the frequency at which it was found
        //if not return zero, which will be interpreted as 'not found'
        if ( identified_peaks.count(mode_number) == 1 ) {
            return identified_peaks[mode_number];
        } else {
            throw mode_track_failure( "Requested mode was not identified." );
//            return 0.0;
        }
    } else {
        throw mode_track_failure( "No modes were identified." );
//        return 0.0;
    }
}

double ModeTrack::GetPeaksGauss( const std::vector<data_triple<double> >& data_str, int mode_number ) {

    try {
        return GetPeaks( data_str, mode_number, Gauss );
    } catch (const mode_track_failure& e) {
        throw mode_track_failure( "Could not identify requested mode in data set" );
    }
//    return GetPeaks( data_str, mode_number, Gauss );
}

double ModeTrack::GetPeaksBiLat( const std::vector<data_triple<double> >& data_str, int mode_number) {

    try {
        return GetPeaks( data_str, mode_number, Gauss );
    } catch (const mode_track_failure& e) {
        throw mode_track_failure( "Could not identify requested mode in data set" );
    }

//    return GetPeaks( data_str, mode_number, BiLat );
}

void ModeTrack::SetLowerBound( double frequency ) {
    upper_bound = frequency;
}

void ModeTrack::SetUpperBound( double frequency ) {
    lower_bound = frequency;
}


double ModeTrack::GetMaxPeak( const std::vector< data_triple<double> >& data_list ) {

    std::vector<double> power_list = data_triples_to_power( data_list );

    uint peak_index = 0; FindMaxima( power_list );

    try {
        peak_index = FindMaxima( power_list );
    } catch (const mode_track_failure& e) {
        throw mode_track_failure( "No maxima peak found in data set." );
    }

    data_triple<double> data_entry = data_list.at( peak_index );
    return data_entry.frequency_MHz;
}

void ModeTrack::SetBackground( const std::vector<data_triple< double > >& background_list ) {

    background = data_triples_to_power( background_list );

}

std::vector<double> ModeTrack::Derivative( const std::vector<double>& data_list ) {

    std::vector<double> der_list;

    std::deque<double> data_deque (data_list.begin(),data_list.end());
    //Pad data_list with zeros at front and back
    for ( unsigned int i=0; i < 2; i++ ) {
        data_deque.push_front(0.0);
        data_deque.push_back(0.0);
    }

    #pragma omp parallel for ordered schedule(dynamic)
    for( unsigned int n = 2; n < data_list.size() + 2; n++ ) {

        double der = ( -data_deque.at( n + 2 ) + 8.0*data_deque.at( n + 1 ) - 8*data_deque.at( n - 1 )+data_deque.at( n - 2 ) ) / 12.0;

        #pragma omp ordered
        der_list.push_back(der);
    }
    return(der_list);
}

//sum all enteries in a vector, with optional parameter of raising each entry to a power
//used by Standard Deviation function
inline double sum ( const std::vector< double >& data_list, double exponent ) {

    double tot = 0.0;

    for ( const auto& val : data_list ) {
        tot += std::pow( val, exponent );
    }

    return tot;
}

//define a gaussian function with standard deviation sigma and a mean value of zero
//used in the construction of gaussian kernels
inline double gaussian ( double x, double sigma ) {
    return 1.0 / ( std::sqrt(M_PI_2)*sigma )*std::exp( -0.5 *pow( x/sigma, 2.0) );
}

//generate a gaussian kernel of radius 'r', suitable for convolutions
//kernel will have a standard deviation of r/2.
std::vector<double> ModeTrack::GaussKernel( int r ) {

    double sigma = static_cast<double>( r )/2.0;

    std::vector<double> vals;

    for( int i = -r; i<= r ; i ++ ) {
        vals.push_back( gaussian( i, sigma ) );
    }

    //normalize kernel before returning
    return Normalize( vals );
}

double ModeTrack::StdDev( const std::vector<double>& data_list ) {

    //compute mean value of data set
    double sum_x = sum( data_list, 1.0 );
    double n = static_cast<double>( data_list.size() );
    double mean = sum_x/n;

    //compute variance taking into account Bessel's correction eg n/(n-1)
    double sum_x2 = sum( data_list, 2.0 );
    double sigma_sqr = sum_x2/( n - 1.0 ) - n/( n - 1.0 )*std::pow( mean, 2.0 );

    //return square root of variance
    return std::sqrt( sigma_sqr );
}

std::vector<double> ModeTrack::Normalize( const std::vector<double>& data_list ) {

    double norm_factor = std::sqrt( sum( data_list, 2.0 ) );
    auto normalized_data = data_list;

    std::transform( normalized_data.begin(), \
                    normalized_data.end(), \
                    normalized_data.begin(), \
                    std::bind1st(std::divides<float>(), norm_factor) );

    return normalized_data;
}

std::vector< double > ModeTrack::Convolve( const std::vector<double>& signal, const std::vector<double>& kernel ) {

    int kernel_size = kernel.size();
    int half_k_size = (kernel_size - 1 )/2;

    int signal_size = signal.size();
    int signal_max_index = signal_size - 1;

    std::vector< double > output( signal.size(), 0.0 );

    #pragma omp parallel for
    for ( int i = 0 ; i < signal_size ; i++ ) {

        double conv_elem = 0.0;

        int k_max = ( ( i + half_k_size ) > signal_max_index )?( signal_max_index + half_k_size - i ):(kernel_size);
        int k_min = ( ( i - half_k_size ) < 0 )?( half_k_size - i ):(0);

        for ( int j = k_min ; j < k_max ; j++ ) {

            conv_elem += signal[ i + j - half_k_size]*kernel[ j ];
        }

        for ( int j = 0 ; j < k_min ; j++ ) {

            conv_elem += signal[ -i - j + half_k_size ]*kernel[ j ];
        }

        for ( int j = k_max ; j < kernel_size ; j++ ) {

            conv_elem += signal[ 2*signal_max_index - i - j + half_k_size ]*kernel[ j ];

        }

        output[i] = conv_elem;

    }

    return output;
}

//Convolve the input list 'data_list' with a gaussian kernel of radius 15
//serves as a low-pass filter that surpressed noise.
std::vector<double> ModeTrack::GaussBlur( const std::vector<double>& data_list ) {

    auto gauss_matrix = GaussKernel( 15 );
    return Convolve( data_list, gauss_matrix );
}

struct RetrieveVal {
    template <typename T>
    typename T::first_type operator()(T keyValuePair) const {
        return keyValuePair.second;
    }
};

//copy values stored in std::map to std::vec
//std::transform(map.begin(), map.end(), std::back_inserter(vec), RetrieveVal());

std::vector<double> ModeTrack::FindPeaks( const std::vector<double>& data_list, const ModeTrack::Method method ) {

    auto filtered_list = ( method == Gauss )? GaussBlur( data_list ):BilateralFilter( data_list, 10, 2 );
    auto f_prime = Derivative( filtered_list );

    int f_prime_size = f_prime.size() - 1;
    int max_size = filtered_list.size();

    double sigma = StdDev( f_prime );

    std::vector< double > peak_list;

    #pragma omp parallel for ordered schedule(dynamic)
    for( int i = 0; i < f_prime_size; i++ ) {

        bool stat_signifigant = ( f_prime.at(i) < 3*sigma && f_prime.at(i+1) > 3*sigma );
        bool away_from_edges = ( i+1 < max_size - 4 && i+1 > 4 );

        if( stat_signifigant && away_from_edges ) {

            #pragma omp ordered
            peak_list.push_back( static_cast<double>( i + 1 ) );

        }
    }

    return peak_list;
}

uint ModeTrack::FindMaxima( const std::vector<double>& data_list ) {

    auto g_blur = GaussBlur( data_list );
    auto f_prime = Derivative( g_blur );

    uint length = data_list.size();

    double sigma = StdDev( f_prime );

    auto result = std::min_element( data_list.begin(), data_list.end() );
    double min_power = static_cast<double>(*result);

    uint peak_index = 0;
    double peak_power = min_power;

    bool peak_identified = false;

    for( unsigned int i = 0; i < f_prime.size() - 1; i++ ) {

        //Establish criteria for a maxima peak;

        bool maxima = ( f_prime.at(i) > 0*sigma && f_prime.at(i+1) < 0*sigma );
        bool away_from_edges = ( i+1 < (length - 5) && i+1 > 5 );

        if( maxima && away_from_edges ) {

            peak_identified |= true;

            std::cout << "Found peak at: " << i <<std::endl;

            uint found_index = i;
            double found_power = data_list.at(i);

            std::cout << "Power was: " << found_power <<std::endl;

            //check to see if peak index is already an element in the map
            //if duplicate is found check which frequency seperation is the smallest
            //between the current and stored value.
            if( peak_index != 0 ) {
                std::cout << "Duplicate Index Detected" << std::endl;

                //if stored value is greater than current value, replaced stored value with current
                if( found_power > peak_power ) {
                    std::cout << "Found Peak was Greater." << std::endl;
//                        std::cout<<"Power was: "<<found_power<<std::endl;
                    peak_index = found_index;
                    peak_power = found_power;
                    //if stored value is less than current leave stored value unchanged
                } else {
                    std::cout << "Found Peak was Less." << std::endl;
//                        std::cout<<"Power was: "<<found_power<<std::endl;
                }
            } else { //if no duplicate is found create a new entry
                peak_index = found_index;
                peak_power = found_power;
            }

        }
    }

    if( !peak_identified ) {
        throw mode_track_failure( "No local maxima found." );
    }

    return peak_index;
}

inline double QuadraticSpline( double a, double b, double c, double x ) {
    return a*std::pow( x, 2.0 ) + b*x + c;
}

double ModeTrack::GenerateSpline( int mode_number, double length ) {

    double a = std::get<0>(estimated_paths.at(mode_number));
    double b = std::get<1>(estimated_paths.at(mode_number));
    double c = std::get<2>(estimated_paths.at(mode_number));

    return QuadraticSpline(a,b,c,length);
}

void ModeTrack::PopulateBestFitCurves() {

    auto mode_one_coeffs = std::make_tuple(47.9998,-1041.54,8950.56);
    auto mode_two_coeffs = std::make_tuple(44.2758,-1055.35,9610.61);
    auto mode_three_coeffs = std::make_tuple(45.8298,-1139.8,10626.7);
    auto mode_four_coeffs = std::make_tuple(37.697,-1038.49,10780.2);

    estimated_paths.push_back(mode_one_coeffs);
    estimated_paths.push_back(mode_two_coeffs);
    estimated_paths.push_back(mode_three_coeffs);
    estimated_paths.push_back(mode_four_coeffs);
}

template<typename T>
inline void removeDuplicates(std::vector<T>& vec) {
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}

bool ModeTrack::CheckBounds(double frequency) {
    if( upper_bound == 0.0f || lower_bound == 0.0f ) {
        //if upper or lower bound is not set always return true
        return true;
    } else if (frequency >= upper_bound) {
        return false;
    } else if (frequency <= lower_bound) {
        return false;
    } else {
        return true;
    }
}

template<typename T>
inline void c_print(T text,int color) {

    switch( color ) {
    case 0:
        //red, error text
        std::cout<<"\033[1;31m"<< text << "\033[0m\n";
        break;
    case 2:
        //green, positive confirmation
        std::cout<<"\033[32m"<< text << "\033[0m\n";
        break;
    case 4:
        //magenta, header
        std::cout<<"\033[35m"<< text << "\033[0m\n";
        break;
    case 8:
        //yellow, warning text
        std::cout<<"\033[33m"<< text << "\033[0m\n";
    default:
        break;
    }
}

//peak_list: list of indices (in frequency space) where peaks were found for a particular cavity length
//comparison_list: of data triples at the same cavity length
std::map<uint,double> ModeTrack::CompareAndFill( std::vector<double>& peak_list,\
        const std::vector< data_triple< double > >& comparison_list ) {

    //format is <peak index,<delta_mu,frequency>>
    //where delta_mu is defined below
    std::map< uint,std::pair< uint,double> > found_peaks;

    //since the cavity length is identical for each element in the set of data triples
    //use the length reported by the first element.
    double g_length = comparison_list.at(0).cavity_length;

    for( const auto& peak_index : peak_list ) {

        std::vector<double> results;

        data_triple<double> data_entry = comparison_list.at(peak_index);

        double frequency = data_entry.frequency_MHz;
        double length = data_entry.cavity_length;

        for (int i = 0; i < 4 ; i++) {
            double estimated_frequency = GenerateSpline(i,length);
            double delta_mu = std::abs(frequency - estimated_frequency);
            results.push_back(delta_mu);
        }

        auto minima = std::min_element(std::begin(results), std::end(results));
        auto min_val = *minima;
        auto min_position = std::distance(std::begin(results), minima);

        std::cout<<"Smallest frequency seperation: "<<min_val;
        std::cout<<" at Peak: "<<min_position<<std::endl;

        if(min_val >= max_search_radius) {
            c_print("Identified peak was too far from any estimated value.",0);
            continue;
        }

        std::make_pair(min_val,frequency);

        //check to see if peak index is already an element in the map
        //if duplicate is found check which frequency seperation is the smallest
        //between the current and stored value.
        if( found_peaks.count(min_position) != 0 ) {
//            std::cout<<"Duplicate Index Detected"<<std::endl;

            //if stored value is greater than current value, replaced stored value with current
            if( found_peaks[min_position].first > min_val ) {
//                std::cout<<"Found Peak was Greater."<<std::endl;
                found_peaks[min_position] = std::make_pair(min_val,frequency);
                //if stored value is less than current leave stored value unchanged
            } else {
//                std::cout<<"Found Peak was Less."<<std::endl;
            }
        } else { //if no duplicate is found create a new entry
            found_peaks[min_position] = std::make_pair(min_val,frequency);
        }

    }

    //initalize map to default "error" value of all zeros
    //if this initial value is returned it will caused GetPeaks
    //to return a value of 0.0f which is interpreted as the
    //standard error value.
    if(found_peaks.empty()) {
        found_peaks[0]=std::make_pair(0,0.0);
    }

    //create container to hold identified peaks
    //format is [peak index],frequency
    std::map<uint,double> identified_peaks;

    //iterate from the first peak index to the last peak index, and all values in between
    for(uint i = found_peaks.begin()->first ; i <= found_peaks.rbegin()->first ; i ++) {

        //check if the peak index corresponds to a key in the map of found peaks
        //if peak index is present set frequency for peak using actual data
        //if peak index is not present assume that the peak was 'missed' and
        //fill in data using estimated peak position.
        if( found_peaks.count(i) != 0 ) {

            std::cout<<"Match for peak: "<<i<<", ";
            double peak_frequency = found_peaks[i].second;
//            std::cout<<"Using real value of: "<<peak_frequency<<std::endl;
            std::string message_str = "Using real value of: "+boost::lexical_cast<std::string>(peak_frequency)+"MHz";
            c_print(message_str,2);
            identified_peaks[i] = peak_frequency;

        } else {
            std::cout<<"No match for peak: "<<i<<", ";
            double peak_frequency = GenerateSpline(i,g_length);
//            std::cout<<"Filling with estimate of: "<<peak_frequency<<std::endl;
            std::string message_str = "Filling with estimate of: "+boost::lexical_cast<std::string>(peak_frequency)+"MHz";
            c_print(message_str,8);
            identified_peaks[i] = peak_frequency;
        }
    }

    return identified_peaks;

}

std::vector<double> ModeTrack::BilateralFilter( const std::vector<double>& data_list, double sigma_s, double sigma_r ) {

    int list_size = data_list.size();

    int radius = static_cast<int>( ceil( 5.0/2.0*sigma_s ) );

    //Copy data_list into deque to speed up front/back insertions that will be needed
    //for zero padding
    std::deque<double> data_deque ( data_list.begin(),data_list.end() );
    //Pad data_list with zeros at front and back
    for (int i=1; i<=radius; i++) {
        data_deque.push_front(0.0);
        data_deque.push_back(0.0);
    }

    std::vector<double> convolved_list;

    #pragma omp parallel for ordered schedule(dynamic)
    for( int p = radius; p < list_size + radius; p++ ) {

        double conv_element = 0.0;
        double norm_weight = 0.0;

        for(int q = p -radius; q <= p + radius ; q++) {

            double pos_weight = std::abs( p - q );
            double intens_weight = data_deque.at(p) - data_deque.at(q);
            double val_sigma_s = gaussian( pos_weight, sigma_s );
            double val_sigma_r = gaussian( intens_weight, sigma_r );
            norm_weight += val_sigma_s*val_sigma_r;
            conv_element += val_sigma_s*val_sigma_r*data_deque.at(q);

        }

        #pragma omp ordered
        convolved_list.push_back(conv_element/norm_weight);
    }

    return convolved_list;
}

std::vector< double > ModeTrack::data_triples_to_power(std::vector<data_triple<double> > data_list ) {

    std::vector< double > power_list;
    power_list.reserve( data_list.size() );

    for( uint i = 0; i < data_list.size() ; i++ ) {
        power_list.push_back( data_list[i].power_dBm );
    }

    return power_list;

}
