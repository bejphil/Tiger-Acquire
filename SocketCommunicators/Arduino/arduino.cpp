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
#include "arduino.h"

Arduino::Arduino( std::string ip_addr, uint port_number ) : AbstractSocketCommunicator( ip_addr, port_number ) {}

double Arduino::GetCavityLength() {
    socket->Send( "LengthOfCavity" );

    // Arduino can take an unusually long time to respond, need to use a timeout > 2 seconds
    // need to strip any whiteespace that that will cause a bad cast from string to float
    std::string cavity_length = socket->Receive();

    return boost::lexical_cast< double >( cavity_length );
}
