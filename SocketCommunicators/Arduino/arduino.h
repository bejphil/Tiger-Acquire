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
    Arduino( std::string ip_addr, uint port_number, QObject* parent = 0 );
    Arduino& operator=( const Arduino& ) = delete; // non copyable

    /*!
     * \brief  Get the current cavity length from the Arduino.
     *
     * This function will poll the Arduino until a non-empty string is returned,
     * guaranteeing that the return value will be valid.
     *
     * Note that this does not elminate the problem of getting 'doubled' responses, e.g.
     * "7.5\r\n7.5"
     *
     * \return Current length of the cavity, in inches
     */
    double GetCavityLength();

  private:
    //

};


#endif // ARDUINO_H
