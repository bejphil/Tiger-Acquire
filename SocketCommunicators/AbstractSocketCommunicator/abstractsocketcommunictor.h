#ifndef ABSTRACTSOCKETCOMMUNICATOR_H
#define ABSTRACTSOCKETCOMMUNICATOR_H

//C System-Headers
//
//C++ System header
//
//Boost Headers
//
//Qt Headers
#include <QObject>
//Project specific headers
#include "../SocketComm/q_socket_comm.h"
#include "../../ConfigProcessor/experiment_parameters.h"

class AbstractSocketCommunicator : public QObject {

    Q_OBJECT

  public:
    AbstractSocketCommunicator( std::string ip_addr, uint port_number, QObject* parent = 0 );
    AbstractSocketCommunicator( const TCPSocketParam socket_param, QObject* parent = 0 );

    AbstractSocketCommunicator& operator=( const AbstractSocketCommunicator& ) = delete; // non copyable
    virtual ~AbstractSocketCommunicator() = 0;

  protected:
    QSocketComm* socket;

};

#endif // ABSTRACTSOCKETCOMMUNICATOR_H
