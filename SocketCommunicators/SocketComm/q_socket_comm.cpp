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
#include "q_socket_comm.h"

QSocketComm::QSocketComm( std::string host_name, uint port_number, QObject *parent) :
    QObject(parent) {

    socket = new QTcpSocket(this);
    socket->connectToHost( QString::fromStdString( host_name ), port_number );

    if( socket->waitForConnected(3000) ) {
        qDebug() << "Connected!";
    } else {

        QString q_sock_error = socket->errorString();
        std::string sock_error = q_sock_error.toStdString();

        std::string err_mesg = "Failed to connect to socket\n";
        err_mesg +="IP Address: " + host_name;
        err_mesg +=" Port Number: " + boost::lexical_cast<std::string>( port_number );
        err_mesg += "\nSocket Error: " + sock_error;

        throw std::runtime_error(err_mesg);
    }

}

QSocketComm::~QSocketComm() {

    socket->disconnectFromHost();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->waitForDisconnected(3000);
    }

    socket->close();
    qDebug() << __func__;

}

void QSocketComm::Send( std::string command, std::string terminator ) {

    std::string message = command+terminator;

    socket->write( message.c_str() );
    socket->waitForBytesWritten(1000);

}

void QSocketComm::SendScl( std::string command ) {

    std::string message = "\0\a" + command + "\r";

    socket->write( message.c_str() );
    socket->waitForBytesWritten(1000);

}

std::string QSocketComm::Receive() {

    QByteArray array;

    while(!array.contains('\n')) {
        socket->waitForReadyRead();
        qDebug() << "Reading: " << socket->bytesAvailable();
        array += socket->readAll();
    }

    int bytes = array.indexOf('\n') + 1;     // Find the end of message
    QByteArray message = array.left(bytes);  // Cut the message
    array = array.mid(bytes);                // Keep the data read too early

    return std::string( message.data(), message.size() );

}
