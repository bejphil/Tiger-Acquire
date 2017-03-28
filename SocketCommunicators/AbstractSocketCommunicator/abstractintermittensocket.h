#ifndef ABSTRACTINTERMITTENSOCKET_H
#define ABSTRACTINTERMITTENSOCKET_H

//C System-Headers
//
//C++ System header
//
//Boost Headers
//
//Qt Headers
#include <QObject>
//Project specific headers
#include "../SocketComm/qsocketintermitten.h"
#include "../../ConfigProcessor/experiment_parameters.h"

class AbstractIntermittenSocket : public QObject {

    Q_OBJECT

  public:
    AbstractIntermittenSocket( std::string ip_addr, uint port_number, QObject *parent = 0  );
    AbstractIntermittenSocket( const TCPSocketParam socket_param, QObject *parent = 0  );

    AbstractIntermittenSocket& operator=( const AbstractIntermittenSocket& ) = delete; // non copyable
    virtual ~AbstractIntermittenSocket() = 0;

  protected:
    QSocketIntermitten* socket;

};

#endif // ABSTRACTINTERMITTENSOCKET_H
