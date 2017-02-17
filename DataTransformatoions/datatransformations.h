#ifndef DATAPROCESSORS_H
#define DATAPROCESSORS_H

//C System-Headers
//
//C++ System headers
#include <vector>
#include <iostream>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include"../Generics/generics.h"


std::vector < float > string_to_power_list( std::string raw_data );
std::vector < data_triple<double> > power_to_data_triples(std::vector<double> power_list, double cavity_length, double min_freq, double max_freq);

#endif // DATAPROCESSORS_H
