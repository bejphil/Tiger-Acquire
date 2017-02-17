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
#include "abstractsocketcommunictor.h"

AbstractSocketCommunicator::AbstractSocketCommunicator( std::string ip_addr, uint port_number ) {
    socket = new QSocketComm( ip_addr, port_number );
}

AbstractSocketCommunicator::AbstractSocketCommunicator( const TCPSocketParam socket_param ) {
    socket = new QSocketComm( socket_param.ip_addr, socket_param.port_addr );
}


AbstractSocketCommunicator::~AbstractSocketCommunicator() {
    socket->deleteLater();
}
