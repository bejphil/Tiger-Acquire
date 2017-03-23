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

ProgramCore::ProgramCore(){

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

    arduino = std::shared_ptr<Arduino>( new Arduino( arduino_info.ip_addr,\
                                                     arduino_info.port_addr ) );

    hp8757_c = std::shared_ptr<NetworkAnalyzer>( new NetworkAnalyzer( network_analyzer.ip_addr,\
                                                                      network_analyzer.port_addr,\
                                                                      nwa_points,\
                                                                      nwa_span_MHz,\
                                                                      nwa_power_dBm ) );

    mxg_n5183b = std::shared_ptr<SignalGenerator>( new SignalGenerator( signal_generator.ip_addr,\
                                                                        signal_generator.port_addr ) );

    stm23_ee = std::shared_ptr<StepperMotor>( new StepperMotor( stepper.ip_addr,\
                                                                stepper.port_addr ) );

    xdl_35_5tp = std::shared_ptr<Switch>( new Switch( psu_switch.ip_addr,\
                                                      psu_switch.port_addr ) );
}

void ProgramCore::InitializeDigitizer() {
        ats9462 = std::shared_ptr<ATS9462Engine>( new ATS9462Engine( digitizer_rate_MHz*1e6, 5, 500e6 ) );

        ats9462->ThreadPoolSize( 10 );
        ats9462->SetSampleRate( digitizer_rate_MHz*1e6 );

        ats9462->StartCapture();
}

void ProgramCore::RetractCavity() {
    stm23_ee->TuneCavity( length_of_tune );
}

void ProgramCore::RapidTraverse() {
    MoveToStartLength();
}

void ProgramCore::PrequelTransmission() {
    xdl_35_5tp->SwitchToNetworkAnalyzer();
    xdl_35_5tp->SwitchToTransmission();
    MoveToStartLength();
}

void ProgramCore::PrequelReflection() {
    xdl_35_5tp->SwitchToNetworkAnalyzer();
    xdl_35_5tp->SwitchToReflection();
    MoveToStartLength();
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
    stm23_ee->SetToInitialLength( start_length, current_length );

}

}
