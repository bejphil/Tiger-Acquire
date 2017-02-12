//C System-Headers
//
//C++ System headers
#include <iostream>
#include <unistd.h>
//Boost Headers
//
//Qt Headers
//
//Project specific headers
#include "q_socket_comm.h"

void test_socket_comm() {

    std::string host = "10.95.100.176";
    uint port = 1234;

    auto sock = new QSocketComm( host, port );

    sock->Send( "PT19" );
    sock->Send( "++addr17" );

    sock->Send( "ST100MS" );

    sleep( 1 );

    sock->Send( "++addr16" );
    sock->Send( "SW0" );
    sock->Send( "TS1" );

    sleep( 3 );

    sock->Send( "C1IA" );
    sock->Send( "C1OD" );

    sleep( 1 );

    sock->Send( "++read 10" );

    auto signal = sock->Receive();

    std::cout << signal << std::endl;

    sock->deleteLater();

}
