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

    if ( std::atexit(Program::PanicCleanUp) != 0 ) {
        std::cout << "Failed to register CleanUp" << std::endl;
    }

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

}

void Program::SetBackground() {

}

void Program::SavePowerSpectrum() {

}

void Program::PanicCleanUp() {

}

void Run() {

}


//Private function
double Program::DeriveLengthFromStart() {

    double cavity_length = arduino->GetCavityLength();
    return start_length - cavity_length;

}
