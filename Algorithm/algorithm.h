#ifndef ALGORITHM_H
#define ALGORITHM_H

//C System-Headers
//
//C++ System headers
#include <string>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
#include <boost/algorithm/string.hpp>//split(), is_any_of, trim
#include <boost/lexical_cast.hpp>
//Project specific headers
//

namespace etig {

void remove_newlines( std::string& str );

template < typename T >
T mean( const std::vector<T>& vect ) {
    uint size_T = static_cast<T>( vect.size() );
    T sum = static_cast<T>( 0 );

    std::for_each( vect.begin(), vect.end(), [&] (T x) {
        sum += x;
    });

    return sum / size_T;
}

template < typename T >
struct Rebin {

    Rebin() {}

    void operator()( const std::vector< T >& time_series, T f_res, T time_int ) {

        uint sig_size = time_series.size();
        T delta_f = static_cast<T>( 1 )/ time_int;

        T f_axion = f_res*1e6/ static_cast<T>( 2 );

        overbin_size = std::floor( f_axion / delta_f );
        uint tail = sig_size % overbin_size;

        uint rebin_size = std::floor( sig_size / overbin_size );

        rebinned_signal( rebin_size );

        for( uint i = 0 ; i < sig_size - tail ; i += overbin_size ) {
            rebinned_signal.at(i) = mean( std::vector<T>( time_series.begin() + i, time_series.begin() + ( i + 1 ) ) );
        }

        rebinned_signal.at( rebin_size - 1 ) = mean( std::vector<T>( time_series.end() - tail, time_series.end() ));

        processed = true;

    }

    std::vector< T > RebinnedSignal() {
        return rebinned_signal;
    }

    uint RebinSize() {
        return overbin_size;
    }

  private:
    std::vector<T> rebinned_signal;
    uint overbin_size;
    bool processed = false;

};

}

#endif /* ALGORITHM_H */
