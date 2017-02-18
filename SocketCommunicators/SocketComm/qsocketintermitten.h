#ifndef QSOCKETINTERMITTEN_H
#define QSOCKETINTERMITTEN_H

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

class QSocketIntermitten : public QObject {

  public:
    explicit QSocketIntermitten( std::string host_name, uint port_number, QObject *parent = 0 );
    ~QSocketIntermitten();

    void OpenConnection();
    void CloseConnection();

    void Send( std::string command, std::string terminator="\n" );
    void SendScl( std::string command );

    std::string Receive();
    std::string ReceiveSafe();

  private:
    QString ip_addr;
    uint port;
    bool connection_open = false;

    QTcpSocket *socket;

};

#endif // QSOCKETINTERMITTEN_H
