#ifndef SWITCH_H
#define SWITCH_H

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

class Switch : public AbstractSocketCommunicator {

  public:
    Switch( std::string ip_addr, uint port_number );
    Switch& operator=( const Switch& ) = delete; // non copyable

    void SwitchToNetworkAnalyzer();
    void SwitchToDigitizer();

    void SwitchToTransmission();
    void SwitchToReflection();

  private:
    void SetVoltages();

};


#endif // SWITCH_H
