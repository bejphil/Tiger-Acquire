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

    //Check to make sure we can connect
    if( socket->waitForConnected(5000) ) {
        qDebug() << "Connected!";
    } else {

        QString q_sock_error = socket->errorString();
        std::string sock_error = q_sock_error.toStdString();

        std::string err_mesg = "Failed to connect to socket\n";
        err_mesg +=" IP Address: " + host_name;
        err_mesg +=" Port Number: " + boost::lexical_cast<std::string>( port_number );
        err_mesg += "\nSocket Error: " + sock_error;

        throw std::runtime_error(err_mesg);
    }

    socket->disconnectFromHost();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->waitForDisconnected(5000);
    }

}

QSocketIntermitten::~QSocketIntermitten() {

    socket->disconnectFromHost();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->waitForDisconnected(5000);
    }

    socket->close();
    qDebug() << __func__;

}

void QSocketIntermitten::OpenConnection() {

    socket->connectToHost( ip_addr, port );

    if( socket->waitForConnected(5000) ) {
        connection_open = true;
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

}

void QSocketIntermitten::CloseConnection() {

    socket->disconnectFromHost();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->waitForDisconnected(5000);
    }

    connection_open = false;

}

void QSocketIntermitten::Send( std::string command, std::string terminator ) {

    if( connection_open == false ) {
        return;
    }

    std::string message = command + terminator;

    socket->write( message.c_str() );
    socket->waitForBytesWritten(5000);

}

void QSocketIntermitten::SendScl( std::string command ) {

    if( connection_open == false ) {
        return;
    }

    // Yes, we really do have to build the string in exactly this way
    // The more intuitive, std::string message = "\0\a" + command + "\r",
    // Will indeed fail.
    std::string message;
    message.push_back( '\0' );
    message.push_back( '\a' );
    message += command;
    message.push_back( '\r' );

    QByteArray message_array( message.c_str(), message.length() );
    socket->write( message_array );

    socket->waitForBytesWritten(5000);

}

std::string QSocketIntermitten::Receive() {

    if( connection_open == false ) {

        std::string err_mesg = "Connection to socket is closed! ";
        err_mesg +="Must call QSocketIntermitten::OpenConnection before reading.";

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

    return std::string( message.data(), message.size() );

}
