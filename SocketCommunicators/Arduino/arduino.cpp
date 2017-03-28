//C System-Headers
//
//C++ System headers
#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream>
//Boost Headers
#include <boost/algorithm/string.hpp>//split(), is_any_of, trim
#include <boost/lexical_cast.hpp>
//Qt Headers
//
//Project specific headers
#include "../../Algorithm/algorithm.h"
#include "arduino.h"

Arduino::Arduino(std::string ip_addr,
                 uint port_number,
                 QObject *parent) : AbstractSocketCommunicator( ip_addr,
                             port_number,
                             parent ) {}

double Arduino::GetCavityLength() {
    socket->Send( "LengthOfCavity" );

    // Arduino can take an unusually long time to respond, need to use a timeout > 2 seconds
    // need to strip any whiteespace that that will cause a bad cast from string to float
    std::string raw_response = socket->Receive();

    // Remove white space
    boost::algorithm::trim( raw_response );
    // Remove newlines
    etig::remove_newlines( raw_response );

    return boost::lexical_cast< double >( raw_response );
}
