//C System-Headers
//
//C++ System headers
//
//Boost Headers
//
//Qt Headers
//
//Project specific headers
#include "abstractintermittensocket.h"

AbstractIntermittenSocket::AbstractIntermittenSocket( std::string ip_addr, uint port_number ) {
    socket = new QSocketIntermitten( ip_addr, port_number );
}

AbstractIntermittenSocket::AbstractIntermittenSocket( const TCPSocketParam socket_param ) {
    socket = new QSocketIntermitten( socket_param.ip_addr, socket_param.port_addr );
}


AbstractIntermittenSocket::~AbstractIntermittenSocket() {
    socket->deleteLater();
}
