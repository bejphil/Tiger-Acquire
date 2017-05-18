//C System-Headers
//
//C++ System headers
//
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
//
//Header for this file
#include "programcore.h"

namespace etig {

ProgramCore::ProgramCore(QObject *parent) : QObject( parent ) {

    number_of_iterations = DeriveNumberofIterations();
    InitializeSocketObjects();
    InitializeDigitizer();

//    window = new MainWindow();
//    window->show();

//    spec_analyzer = new SpectrumAnalyzer( window );
//    window -> SetSpectrumAnalyzerView( spec_analyzer );

//    na_view = new InstrumentView( "Network Analyzer", window );
//    window -> SetNetworkAnalyzerView( na_view );

}

void ProgramCore::InitializeSocketObjects() {

    arduino = new Arduino( arduino_info.ip_addr,
                           arduino_info.port_addr,
                           this );

    hp8757_c = new NetworkAnalyzer( network_analyzer.ip_addr,
                                    network_analyzer.port_addr,
                                    nwa_points,
                                    nwa_span_MHz,
                                    nwa_power_dBm,
                                    this );

    mxg_n5183b = new SignalGenerator( signal_generator.ip_addr,
                                      signal_generator.port_addr,
                                      this ) ;

    stm23_ee = new StepperMotor( stepper.ip_addr,
                                 stepper.port_addr,
                                 this );

    xdl_35_5tp = new Switch( psu_switch.ip_addr,
                             psu_switch.port_addr,
                             this);

}

void ProgramCore::InitializeDigitizer() {
    ats9462 = std::shared_ptr<ATS9462Engine>( new ATS9462Engine( digitizer_rate_MHz*1e6, num_averages, 500e6 ) );

    ats9462->ThreadPoolSize( 8 );
    ats9462->SetSampleRate( digitizer_rate_MHz*1e6 );

    ats9462->StartCapture();
}

void ProgramCore::RetractCavity() {
    MoveToStartLength();
}

void ProgramCore::RapidTraverse() {
}

void ProgramCore::PrequelTransmission() {
    xdl_35_5tp->SwitchToNetworkAnalyzer();
    xdl_35_5tp->SwitchToTransmission();
}

void ProgramCore::PrequelReflection() {
    xdl_35_5tp->SwitchToNetworkAnalyzer();
    xdl_35_5tp->SwitchToReflection();
}

void ProgramCore::NextIteration() {

    iteration += 1;
    stm23_ee->TuningLoop( length_of_tune, revs_per_iterations, iteration );

}

//Begin private functions
int ProgramCore::DeriveNumberofIterations() {
    double tune_length = length_of_tune*16.0;
    double revs = std::abs( revs_per_iterations );
    return static_cast<int>( tune_length/revs );
}

void ProgramCore::MoveToStartLength() {
    double current_length = arduino->GetCavityLength();
    stm23_ee->TuneToLength( start_length, current_length );
}

void ProgramCore::MoveToBGSubtractionLength() {

    double current_length = arduino->GetCavityLength();
    stm23_ee->TuneToLength( background_scan_length, current_length );

}

void ProgramCore::MoveToEndLength() {

    double current_length = arduino->GetCavityLength();
    double end_length = start_length + length_of_tune;
    stm23_ee->TuneToLength( end_length, current_length );

}

void ProgramCore::Jitter() {

    stm23_ee->TuneCavity( - 0.1 );
    stm23_ee->TuneCavity( 0.1 );

}

}
