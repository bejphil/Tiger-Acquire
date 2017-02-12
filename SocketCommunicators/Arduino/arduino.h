#ifndef ARDUINO_H
#define ARDUINO_H

//C System-Headers
//
//C++ System headers
#include <vector>
//Boost Headers
//
//Qt Headers
//
//Project specific headers
#include "../SocketComm/q_socket_comm.h"
#include "../AbstractSocketCommunicator/abstractsocketcommunictor.h"

/*!
 * \brief Object to send and receive commands from an Arduino Uno (R3)
 *
 *  Arduino is expected to be equipped with an Ethernet Shield and string potentiometer.
 */
class Arduino : public AbstractSocketCommunicator {

  public:
    Arduino( std::string ip_addr, uint port_number );
    Arduino& operator=( const Arduino& ) = delete; // non copyable

    double GetCavityLength();

  private:
    //

};


#endif // ARDUINO_H
