#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

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

class SignalGenerator : public AbstractSocketCommunicator {

  public:
    SignalGenerator( std::string ip_addr, uint port_number );
    SignalGenerator& operator=( const SignalGenerator& ) = delete; // non copyable
    ~SignalGenerator();

    void RFOn();
    void RFOff();
    void SetFrequency( double freq_MHz );
    void SetPower( double power_dBm );

  private:
    //

};


#endif // SIGNALGENERATOR_H
