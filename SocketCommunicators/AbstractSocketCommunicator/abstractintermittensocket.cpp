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

AbstractIntermittenSocket::AbstractIntermittenSocket( std::string ip_addr, uint port_number, QObject* parent ) : QObject( parent ) {
    socket = new QSocketIntermitten( ip_addr, port_number, this );
}

AbstractIntermittenSocket::AbstractIntermittenSocket(const TCPSocketParam socket_param , QObject *parent) : QObject( parent )  {
    socket = new QSocketIntermitten( socket_param.ip_addr, socket_param.port_addr, this );
}


AbstractIntermittenSocket::~AbstractIntermittenSocket() {
//    socket->deleteLater();
}
