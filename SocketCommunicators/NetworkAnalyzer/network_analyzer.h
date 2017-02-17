#ifndef NETWORKANALYZER_H
#define NETWORKANALYZER_H

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
 * \brief Object to communicate with the HP8757 C Network Analyzer.
 */
class NetworkAnalyzer : public AbstractSocketCommunicator {

  public:
    NetworkAnalyzer( std::string ip_addr, uint port_number , uint points, double span, double power );
    NetworkAnalyzer& operator=( const NetworkAnalyzer& ) = delete; // non copyable

    std::vector< double > TakeDataMultiple();
    std::vector< double > TakeDataSingle();
    void SetFrequencyWindow( double frequency, double frequency_span );
    void TurnOnRFSource();
    void TurnOffRFSource();

  private:
    void SetGPIB();
    void SetNetworkAnalyzer( uint points_per_scan = 401, bool do_averaging = false );
    void SetRFParameters( double frequency_span, double RF_source_power );
    void SetRFSource( bool source_on );

    std::vector< double > raw_str_to_vector( std::string raw_data );

};


#endif // NETWORKANALYZER_H
