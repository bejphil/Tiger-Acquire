#ifndef MODETRACK_H
#define MODETRACK_H

//C System-Headers
//
//C++ System headers
#include <tuple>
#include <vector>
#include <map>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include "../Generics/generics.h"
#include "mode_track_failure.h"

/*!
 * \brief Base Class for mode tracking algorithims; designed to be wrapped with Swig
 * and called from Python module
 *
 *
 */
class ModeTrack {
  public:
    ModeTrack();
    ~ModeTrack();

    /*!
     * \brief Set background data which will be subtracted from each
     * measurement
     * \param background_str string of power values seperated by commas,
     * eg \f$ \{p_1,p_2,...,p_n\}\f$
     */
    void SetBackground( const std::vector< data_triple< double > >& background_list );

    /*!
     * \brief Identify minima peaks in a list of power data
     * using Gaussian filtering
     *
     * This function is designed to be called by the main control code
     * during data taking. The main control program will collect
     * reflection measurements and call this function to identify
     * the position of the mode of desire.
     *
     * \param data_str string containing power data that should be
     * searched through. Needs to be in the a list of values seperated
     * by commas, eg \f$ \{p_1,p_2,...,p_n\}\f$
     *
     * \param mode_number Identify which mode should be tracked.
     * Choices are 0,1,2 and 3.
     *
     * \return The frequency of the requested mode in MHz. If the
     * requested mode was not found a value of 0 will be returned.
     */
    double GetPeaksGauss( const std::vector< data_triple< double > >& power_list, int mod_number );

    /*!
     * \brief Identify minima peaks in a list of power data
     * using Bilateral filtering
     *
     * This function is very similar to GetPeaksGauss() except
     * for the method that is used to filter data. This function
     * makes use of a Bilateral filter for data pre-processing.
     *
     * See https://users.cs.duke.edu/~tomasi/papers/tomasi/tomasiIccv98.pdf
     * for more details.
     *
     * \param data_str string containing power data that should be
     * searched through. Needs to be in the a list of values seperated
     * by commas, eg \f$ \{p_1,p_2,...,p_n\}\f$
     *
     * \param mode_number Identify which mode should be tracked.
     * Choices are 0,1,2 and 3.
     *
     * \return The frequency of the requested mode in MHz. If the
     * requested mode was not found a value of 0 will be returned.
     */
    double GetPeaksBiLat( const std::vector< data_triple< double > >& power_list, int mod_number );

    /*!
     * \brief Find a local maximum in a list of data.
     *
     * This method applies the same Gaussian Blur/Derivative filter
     * combination that 'GetPeaks' uses, but does not make reference
     * to the estimated peak positions.
     * If multiple peaks are identified take the one with the highest
     * overall value.
     * This function is designed to be called when identifying peaks
     * when looking at a transmission measurement.
     *
     * \return Frequency of maxima, if one is found. Otherwise
     * return value will be 0.
     */
    double GetMaxPeak( const std::vector< data_triple< double > >& power_list );
    //
    void SetLowerBound( double frequency );
    //
    void SetUpperBound( double frequency );

  private:
    //
    enum Method { Gauss, BiLat };
    //
    double lower_bound = 0.0, upper_bound = 0.0;
    //
    double max_search_radius = 436.344;

    /*!
    * \brief Background data, to be subtracted off of main data set
    */
    std::vector< double > background;

    //quadratic best-fit coeffecients for each of the four modes.
    //format is a*x^2+b*x+c and tuple is populated with (a,b,c)
    //first entry in vector corresponds to the first mode, etc.

    /*!
     * \brief quadratic best-fit coeffecients for each of the four modes.
     *
     * format is \f$ f(x) = a x^2+b x+c\f$ and tuple is populated with (a,b,c)
     * first entry in vector corresponds to the first mode (ie mode 0)
     * second entry corresponds to mode 1 etc.
     */
    std::vector<std::tuple<double,double,double>> estimated_paths;

    /*!
     * \brief Compute the the forth order approximation of the derivative
     *
     * Uses method \f$ f'(n) \approx \frac{-f(n+2)+8*f(n+1)-8*f(n-1)+f(n-2)}{12} \f$
     * to approximate the derivative.
     *
     * \param data_list
     * \return
     */
    std::vector<double> Derivative( const std::vector<double>& data_list );


    /*!
     * \brief Load cubic spline coeffecients for modes 0 through 3
     *
     * These values were attained by examining an old mode map.
     */
    void PopulateBestFitCurves();

    //Compute the standard deviation of a list
    /*!
     * \brief Compute the standard deviation of a list.
     *
     * Includes unbiasing via Bessel's correction, ie
     * \f$ \frac{n}{n-1} \f$
     *
     * \param data_list Input data list.
     * \return Standard deviation of list.
     */
    double StdDev( const std::vector<double>& data_list );

    /*!
     * \brief Normalize a list of data w.r.t. to the L2 norm.
     *
     * That is for the list of the values \f$ \{a_1,a_2...,a_i\}\f$
     * ensure that \f$ \sqrt{\sum_{i=1}^n | a_i |^2} = 1 \f$
     * \param data_list The input list.
     * \return Normalized list. Note that this allows the original list
     * to go unaltered.
     */
    std::vector<double> Normalize(const std::vector<double> &data_list);

    /*!
     * \brief Compute the 1D convolution of data_list with kernel.
     *
     * Note that edge effects are handeled by zero padding data_list
     *
     * \param data_list List of data to be convolved with kernel
     * \param kernel Convolution kernel, must be smaller than data_list
     * \return Convolution of data_list and kernel
     */
    std::vector<double> Convolve(const std::vector<double> &signal, const std::vector<double> &kernel);

    //convolve list with a gaussian vector

    /*!
     * \brief Compute the convulution of data_list with a Gaussian kernel
     *
     * The Gaussian kernel will have radius of 15 and sigma = 15/2.
     *
     * \param data_list
     * \return
     */
    std::vector<double> GaussBlur(const std::vector<double> &data_list);

    /*!
     * \brief Find minima peaks in a list
     * \param data_list
     * \return List of peaks in the order in which they were found.
     * Note that peak position will be given by indices with regard
     * to the original list.
     */
    std::vector<double> FindPeaks( const std::vector<double>& data_list, const ModeTrack::Method method );

    //Check to see if all identified peaks are close to an estimated peak
    //If an identified peak is not "close" to an estimated peak, fill value from estimation

    /*!
     * \brief Compare the position of each identified peak with estimated peak position
     *
     * Estimated peak positions are generated from old Reflection Map data.
     * The distance -in frequency space- between each identified peak and
     * each estimated peak is computed. Using these numbers the index of
     * each identified peak is determined (by looking at the smallest frequency
     * seperation). If duplicate peak indices are discovered the one with the
     * smallest frequency seperation is used.
     *
     * If it is found that any peaks have been missed, that is there is a gap
     * between identified peak indices, the position of the missing peaks will
     * be estimated using the GenerateSpline() function. For example if peaks
     * 0 and 3 were found, the position of peaks 1 and 2 would be estimated.
     *
     * \param peak_list List of peaks identified by FindPeaks() functions
     * \param comparison_list List of data triples generated by GenerateSpline() function
     * \return Dictionary of identified peaks, with the format of
     * [peak index]:frequency(MHz)
     */
    std::map<uint,double> CompareAndFill(std::vector<double>& peak_list, const std::vector<data_triple<double> > &comparison_list);

    //Generate estimated peak position from best fit parameters

    /*!
     * \brief GenerateSpline
     * \param mode_number
     * \param length
     * \return
     */
    double GenerateSpline(int mode_number, double length);

    //generate a gaussian kernel
    //used by 'GaussBlur' function
    /*!
     * \brief Generate a Gaussian kernel of radius r and sigma = r/2
     * Kernel is generated by sampling Gaussian function with sigma = r/2
     * a total of r times.
     *
     * \param r The radius of the generated kernel
     * \return Gassian Kernel
     */
    std::vector<double> GaussKernel(int r);

    /*!
     * \brief Apply a the Biltaral filter
     *
     * See the original paper for more details,
     *
     * C. Tomasi and R. Manduchi, “Bilateral filtering for gray and color images,”
     * in Proceedings  of  the  IEEE  International  Conference  on  Computer  Vision,
     * pp. 839–846, 1998.
     *
     * \param data_list, the list that will be filtered
     * \param sigma_s, "Spatial" standard deviation, the size of the gaussian kernel
     * \param sigma_r
     * \return
     */
    std::vector<double> BilateralFilter( const std::vector<double>& data_list, double sigma_s, double sigma_r );
    //
    uint FindMaxima( const std::vector<double>& data_list);
    //
    double GetPeaks( const std::vector<data_triple<double> > &data_str, int mode_number, Method filter_method);
    //
    bool CheckBounds(double frequency);

    std::vector< double > data_triples_to_power( std::vector< data_triple<double> > data_list );
};

#endif /* MODETRACK_H */

