//Header for this file
#include "program.h"
//C System-Headers
#include <cstdlib> // std::atexit
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

//Public functions

Program::Program() {

//    if ( std::atexit(Program::PanicCleanUp&) != 0 ) {
//        std::cout << "Failed to register CleanUp" << std::endl;
//    }

}

double Program::FindModeReflection() {

    auto network_analyzer_scan = hp8757_c->TakeDataMultiple();
    auto formatted_na_scan = power_to_data_list( network_analyzer_scan );

    try {
        return FindMinimaPeak( formatted_na_scan );
    } catch (const mode_track_failure& e) {
        throw( daq_failure( "Search mode not found in power spectrum." ) );
    }

}

double Program::FindModeTransmission( double mode_frequency ) {

    try {
        return CheckPeak( mode_frequency );
    } catch (const mode_track_failure& e) {
        throw( daq_failure( "Search mode not found in power spectrum." ) );
    }
}

std::vector< data_triple<double> > Program::TakeData( double mode_frequency ) {

//    ShiftFrequencyWindow( mode_frequency );

//    ats9462->Start();

//    while( !ats9462->Finished() ) {
//        sleep(5);
//    }

//    std::vector< float > signal;

//    try {
//        signal = ats9462->FinishedSignal();
//    } catch ( const std::ios_base::failure& e ) {
//        throw( daq_failure( "Signal could not be read from digitizer." ) );
//    }

//    return power_to_data_list( signal );

}

void Program::SavePowerSpectrum( data_list scan ) {

    std::string header = BuildHeader();
    data_saver.Save( scan, header );
}

void Program::PanicCleanUp() {

    double cavity_length = arduino->GetCavityLength();
    stm23_ee->ResetCavity( cavity_length );

}

void Program::Run() {

    Prequel();
    SetBackground();
    RapidTraverse();

    for( uint i = 0; i <= number_of_iterations ; i ++ ) {

        double mode_of_desire = 0.0;

        try {
            mode_of_desire = FindModeReflection();
        } catch (const daq_failure& e) {
            NextIteration();
            continue;
        }

        try {
            mode_of_desire = FindModeTransmission( mode_of_desire );
        } catch (const daq_failure& e) {
            NextIteration();
            continue;
        }

        auto current_scan = TakeData( mode_of_desire );
        SavePowerSpectrum( current_scan );

        NextIteration();

    }
}


//Private function
double Program::DeriveLengthFromStart() {

    double cavity_length = arduino->GetCavityLength();
    return start_length - cavity_length;

}
