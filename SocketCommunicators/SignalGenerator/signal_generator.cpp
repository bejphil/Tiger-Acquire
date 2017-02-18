//C System-Headers
//
//C++ System headers
#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream>
//Boost Headers
#include <boost/lexical_cast.hpp>
//Qt Headers
//
//Project specific headers
#include "signal_generator.h"

SignalGenerator::SignalGenerator( std::string ip_addr, uint port_number ) : AbstractSocketCommunicator( ip_addr, port_number ) {}

void SignalGenerator::RFOn() {
    socket->Send( "OUTP ON" );
}

void SignalGenerator::RFOff() {
    socket->Send( "OUTP OFF" );
}

void SignalGenerator::SetFrequency( double freq_MHz ) {

    std::string command = "FREQ ";
    command += boost::lexical_cast<std::string>( freq_MHz );
    command += " MHz";

    socket->Send( command );

}

void SignalGenerator::SetPower( double power_dBm ) {

//    std::string command = "POW:LEV:IMM:AMP ";
    std::string command = "POW:LEV ";
    command += boost::lexical_cast<std::string>( power_dBm );
    command += " dB";

    socket->Send( command );
}
