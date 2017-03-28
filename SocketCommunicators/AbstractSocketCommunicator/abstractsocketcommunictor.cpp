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

AbstractSocketCommunicator::AbstractSocketCommunicator( std::string ip_addr,
                                                        uint port_number,
                                                        QObject* parent ) : QObject( parent ) {
    socket = new QSocketComm( ip_addr, port_number, this );
}

AbstractSocketCommunicator::AbstractSocketCommunicator( const TCPSocketParam socket_param,
                                                        QObject* parent ) : QObject( parent ) {
    socket = new QSocketComm( socket_param.ip_addr, socket_param.port_addr, this );
}


AbstractSocketCommunicator::~AbstractSocketCommunicator() {
//    socket->deleteLater();
}
