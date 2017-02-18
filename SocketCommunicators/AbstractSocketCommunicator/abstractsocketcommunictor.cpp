//C System-Headers
//
//C++ System headers
//
//Boost Headers
//
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
