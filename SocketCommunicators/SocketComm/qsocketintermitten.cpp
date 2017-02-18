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
#include <QString>
//Project specific headers
#include "qsocketintermitten.h"

QSocketIntermitten::QSocketIntermitten( std::string host_name, uint port_number, QObject *parent) :
    QObject(parent) {

    socket = new QTcpSocket(this);
    socket->connectToHost( QString::fromStdString( host_name ), port_number );

    ip_addr = QString::fromStdString( host_name );
    port = port_number;

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

    socket->disconnectFromHost();

}

QSocketIntermitten::~QSocketIntermitten() {

    socket->disconnectFromHost();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->waitForDisconnected(3000);
    }

    socket->close();
    qDebug() << __func__;

}

void QSocketIntermitten::Send( std::string command, std::string terminator ) {

    std::string message = command + terminator;

    socket->connectToHost( ip_addr, port );

    if( socket->waitForConnected(3000) ) {
        qDebug() << "Connected!";
    } else {

        QString q_sock_error = socket->errorString();
        std::string sock_error = q_sock_error.toStdString();

        std::string err_mesg = "Failed to connect to socket\n";
        err_mesg +="IP Address: " + ip_addr.toStdString();
        err_mesg +=" Port Number: " + boost::lexical_cast<std::string>( port );
        err_mesg += "\nSocket Error: " + sock_error;

        throw std::runtime_error(err_mesg);
    }

    socket->write( message.c_str() );
    socket->waitForBytesWritten(1000);

    socket->disconnectFromHost();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->waitForDisconnected(3000);
    }

}

void QSocketIntermitten::SendScl( std::string command ) {

    std::string message = "\0\a" + command;

    socket->connectToHost( ip_addr, port );

    if( socket->waitForConnected(3000) ) {
        qDebug() << "Connected!";
    } else {

        QString q_sock_error = socket->errorString();
        std::string sock_error = q_sock_error.toStdString();

        std::string err_mesg = "Failed to connect to socket\n";
        err_mesg +="IP Address: " + ip_addr.toStdString();
        err_mesg +=" Port Number: " + boost::lexical_cast<std::string>( port );
        err_mesg += "\nSocket Error: " + sock_error;

        throw std::runtime_error(err_mesg);
    }

    socket->write( message.c_str() );
    socket->waitForBytesWritten(1000);

    socket->disconnectFromHost();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->waitForDisconnected(3000);
    }

}

std::string QSocketIntermitten::Receive() {

    socket->connectToHost( ip_addr, port );

    if( socket->waitForConnected(3000) ) {
        qDebug() << "Connected!";
    } else {

        QString q_sock_error = socket->errorString();
        std::string sock_error = q_sock_error.toStdString();

        std::string err_mesg = "Failed to connect to socket\n";
        err_mesg +="IP Address: " + ip_addr.toStdString();
        err_mesg +=" Port Number: " + boost::lexical_cast<std::string>( port );
        err_mesg += "\nSocket Error: " + sock_error;

        throw std::runtime_error(err_mesg);
    }

    QByteArray array;

    while(!array.contains('\n')) {
        socket->waitForReadyRead();
        qDebug() << "Reading: " << socket->bytesAvailable();
        array += socket->readAll();
    }

    int bytes = array.indexOf('\n') + 1;     // Find the end of message
    QByteArray message = array.left(bytes);  // Cut the message
    array = array.mid(bytes);                // Keep the data read too early

    socket->disconnectFromHost();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->waitForDisconnected(3000);
    }

    return std::string( message.data(), message.size() );

}
