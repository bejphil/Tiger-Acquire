#ifndef Q_SOCKETCOMM_H
#define Q_SOCKETCOMM_H

//C System-Headers
//
//C++ System headers
//
//Boost Headers
//
//Qt Headers
#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QDataStream>
//Project specific headers
//

class QSocketComm : public QObject
{
    Q_OBJECT

public:
    explicit QSocketComm( std::string host_name, uint port_number, QObject *parent = 0 );
    ~QSocketComm();

    void Send( std::string command, std::string terminator="\n" );
    void SendScl( std::string command );

    std::string Receive();
    std::string ReceiveSafe();

private:
    QTcpSocket *socket;

};

#endif // Q_SOCKETCOMM_H
