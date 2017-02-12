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

/*!
 * \brief  Get the current cavity length from the Arduino.
 *
 * This function will poll the Arduino until a non-empty string is returned,
 * guaranteeing that the return value will be valid.
 *
 * Note that this does not elminate the problem of getting 'doubled' responses, e.g.
 * "7.5\r\n7.5"
 *
 * \return Current length of the cavity, in inches
 */
double Arduino::GetCavityLength() {
    socket->Send( "LengthOfCavity" );

    // Arduino can take an unusually long time to respond, need to use a timeout > 2 seconds
    // need to strip any whiteespace that that will cause a bad cast from string to float
    std::string cavity_length = socket->Receive();

    return boost::lexical_cast< double >( cavity_length );
}
