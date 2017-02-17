#ifndef EXPERIMENT_PARAMETERS_H
#define EXPERIMENT_PARAMETERS_H

//C System-Headers
//
//C++ System headers
#include <vector>
#include <string>
#include <ostream>
#include <mutex>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include "../Generics/generics.h"

class ExperimentParameters {

  public:

    const std::string save_file_path = "/home/bephillips2/workspace/Electric_Tiger_Control_Code/data/";
    const double length_of_tune = 3.0;
    const double revs_per_iterations = 2.5;
    const double start_length = 7.0;
    const double nwa_span_MHz = 400.0;
    const uint nwa_points = 401;
    const double nwa_power_dBm = -15.0;
    const double freq_window_MHz = 100.0;
    const double digitizer_rate_MHz = 50.0;
    const uint num_averages = 10000;

    const TCPSocketParam psu_switch = TCPSocketParam( "Switch", "10.95.100.174", 9221 );
    const TCPSocketParam network_analyzer = TCPSocketParam( "NetworkAnalyzer", "10.95.100.176", 1234 );
    const TCPSocketParam stepper = TCPSocketParam( "Stepper", "10.95.100.177", 7776 );
    const TCPSocketParam signal_generator = TCPSocketParam( "SignalGenerator", "10.95.100.175", 5025 );
    const TCPSocketParam arduino = TCPSocketParam( "Arduino", ";10.66.192.41", 23 );

};

#endif // EXPERIMENT_PARAMETERS_H
