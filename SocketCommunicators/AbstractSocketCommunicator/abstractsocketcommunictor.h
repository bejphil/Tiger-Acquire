#ifndef ABSTRACTSOCKETCOMMUNICATOR_H
#define ABSTRACTSOCKETCOMMUNICATOR_H

//C System-Headers
//
//C++ System header
//
//Boost Headers
//
//Qt Headers
//
//Project specific headers
#include "../SocketComm/q_socket_comm.h"

class AbstractSocketCommunicator {

  public:
    AbstractSocketCommunicator( std::string ip_addr, uint port_number );
    AbstractSocketCommunicator& operator=( const AbstractSocketCommunicator& ) = delete; // non copyable
    virtual ~AbstractSocketCommunicator() = 0;

  protected:
    QSocketComm* socket;

};

#endif // ABSTRACTSOCKETCOMMUNICATOR_H
