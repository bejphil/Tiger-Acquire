#ifndef PROGRAMCORE_H
#define PROGRAMCORE_H


//C System-Headers
//
//C++ System headers
#include <memory>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include "../../SocketCommunicators/socketcommunicators.h"
#include "../../Generics/generics.h"
#include "daq_failure.h"

class ProgramCore {

  public:
    ProgramCore();

    void RetractCavity();
    void RapidTraverse();
    void PrequelTransmission();
    void PrequelReflection();
    void NextIteration();

  protected:

    const std::string save_file_path = "/home/bephillips2/workspace/Electric_Tiger_Control_Code/data/";
    const double length_of_tune = 3.0;
    const double revs_per_iterations = 2.5;
    const double start_length = 7.0;
    const double nwa_span_MHz = 400.0;
    const uint nwa_points = 401;
    const double nwa_power_dBm = -15.0;
    const double signal_generator_power_dBm = 0.0;
    const double freq_window_MHz = 100.0;
    const double digitizer_rate_MHz = 50.0;
    const uint num_averages = 10000;

    const TCPSocketParam psu_switch = TCPSocketParam( "Switch", "10.95.100.174", 9221 );
    const TCPSocketParam network_analyzer = TCPSocketParam( "NetworkAnalyzer", "10.95.100.176", 1234 );
    const TCPSocketParam stepper = TCPSocketParam( "Stepper", "10.95.100.177", 7776 );
    const TCPSocketParam signal_generator = TCPSocketParam( "SignalGenerator", "10.95.100.175", 5025 );
    const TCPSocketParam arduino_info = TCPSocketParam( "Arduino", "10.95.100.173", 23 );


    //std::shared_ptr<ATS9462Engine> ats9462;
    std::shared_ptr<Arduino> arduino;
    std::shared_ptr<NetworkAnalyzer> hp8757_c;
    std::shared_ptr<SignalGenerator> mxg_n5183b;
    std::shared_ptr<StepperMotor> stm23_ee;
    std::shared_ptr<Switch> xdl_35_5tp;

    double number_of_iterations = 0.0;
    uint iteration = 0;

  private:
    void MoveToStartLength();
    void InitializeSocketObjects();
    void InitializeDigitizer();

    int DeriveNumberofIterations();

};


#endif // PROGRAMCORE_H
