#ifndef SOCKETCOMM_H
#define SOCKETCOMM_H

//C System-Headers
#include <stdio.h> /* for printf() and fprintf() */
#include <sys/types.h> /* for Socket data types */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <netinet/in.h> /* for IP Socket data types */
#include <arpa/inet.h>/* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
//C++ System header
#include <string>
//Boost Headers
//
//Qt Headers
//
//Project specific headers
//

class SocketComm
{
public:
    explicit SocketComm( std::string host_name, uint port_number );
    ~SocketComm();

    void Send( std::string command, std::string terminator="\n" );
    void SendScl( std::string command );

    std::string Receive();
    std::string ReceiveSafe();

private:

};

#endif // SOCKETCOMM_H
