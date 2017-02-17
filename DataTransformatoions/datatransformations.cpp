//C System-Headers
//
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
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
#include <boost/algorithm/string.hpp>//split() and is_any_of for parsing .csv files
#include <boost/lexical_cast.hpp>//lexical cast (unsurprisingly)
//Project specific headers
#include "datatransformations.h"

std::vector < data_triple<double> > power_to_data_triples( std::vector< double > power_list, double cavity_length, double min_freq, double max_freq ) {

    uint number_of_points = power_list.size();

    std::vector< data_triple<double> > processed;
    processed.reserve( number_of_points );

    for( uint i = 0; i < number_of_points ; i++ ) {

        double i_f = static_cast<double>(i);
        double num_points_f = static_cast<double>(number_of_points);

        double frequency = (i_f + 1.0)*(max_freq - min_freq)/(num_points_f) + min_freq;
        double power = power_list.at(i);

        processed.push_back( data_triple<double>( round(frequency), cavity_length, power ) );
    }

    return processed;

}

std::vector < float > string_to_power_list( std::string raw_data ) {

    std::istringstream iss (raw_data);

    while (iss) {
        std::string input;
        std::getline(iss, input);

        std::vector<std::string> strs;
        //split on comma delimiter
        boost::split(strs, input, boost::is_any_of(","));

        std::vector< float > processed;
        processed.reserve( strs.size() );

        for( uint i = 0; i < strs.size() ; i ++ ) {
            processed.push_back( boost::lexical_cast<float>( strs[i]) );
        }

        return processed;
    }

}
