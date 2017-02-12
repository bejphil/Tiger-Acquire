//C System-Headers
//
//C++ System headers
//
//Boost Headers
#include <boost/lexical_cast.hpp>
//Qt Headers
//
//Project specific headers
#include "network_analyzer.h"

NetworkAnalyzer::NetworkAnalyzer( std::string ip_addr, uint port_number, uint points, double span, double power ) : AbstractSocketCommunicator( ip_addr, port_number ) {
    SetGPIB();
    SetNetworkAnalyzer( points );
    SetRFParameters( span, power );
}

/*!
 * \brief NetworkAnalyzer::TakeDataMultiple
 * \param frequency_centers
 * \return
 */
std::vector< float > NetworkAnalyzer::TakeDataMultiple( std::vector< float > frequency_centers ) {

}

std::vector< float > NetworkAnalyzer::TakeDataSingle( double center_frequency ) {

}

void NetworkAnalyzer::SetFrequencyWindow( double frequency_span ) {

}

/*!
 * \brief Turn the RF source on, at whatever power it was set to most recently.
 */
void NetworkAnalyzer::TurnOnRFSource() {
    SetRFSource( true );
}

/*!
 * \brief Turn the RF source off
 */
void NetworkAnalyzer::TurnOffRFSource() {
    SetRFSource( false );
}

//Begin private functions

/*!
 * \brief Initialize the Prologix GPIB-ETHERNET Controller.
 */
void NetworkAnalyzer::SetGPIB() {

    socket->Send( "++addr 16" ); // Set to network analyzer GPIB address
    socket->Send( "++auto 0" ); // Disable Auto-Read
    socket->Send( "++eoi 1" ); // Enable EOI assertion at end of commands
    socket->Send( "eos 0" ); // Append CR+LF to instrument commands

}

/*!
 * \brief Set all - Network Analyzer - parameters that will not change for the duration of the
 *  experiment.
 *
 * \param points_per_scan
 *
 * Number of data points the NA will output when collecting a -single- set of data
 *
 * \param do_averaging
 *
 * Should averaging be performed or not? Since by default we only collect data from a
 *  single signal sweep this is set to off by default.
 */
void NetworkAnalyzer::SetNetworkAnalyzer( uint points_per_scan, bool do_averaging ) {


    socket->Send( "C1" ); // set active channel to 1
    socket->Send( "CU0" ); // turn cursor off
    socket->Send( "CD0" ); // set cursor delta off
    socket->Send( "FD0" ); // set data format to ascii

    // set number of points to pointers_per_scan
    socket->Send( "SP" + boost::lexical_cast< std::string >( points_per_scan ) );

    if( do_averaging ) {
        socket->Send( "AF16" ); // Turn on averaging -- 16 samples per average
    }

}

/*!
 * \brief Set all - Signal Sweeper - parameters that will not change for the duration of the
 *  experiment.
 *
 * \param frequency_span
 *
 * How wide the frequency window is for a -single- set of data, in MHz
 *
 * \param RF_source_power
 *
 * Power to set the RF source to, in dBm
 */
void NetworkAnalyzer::SetRFParameters( double frequency_span, double RF_source_power ) {

    socket->Send( "PT19" ); // set passthrough mode to RF source
    socket->Send( "++addr 17" ); //change GPIB address to passthrough
    socket->Send( "RF1" ); // Turn RF output on

    // Set frequency span ( in MHz )
    socket->Send( "DF" + boost::lexical_cast<std::string>(frequency_span) + "MZ" );
    // Set power output ( in Dbm )
    socket->Send( "PL" + boost::lexical_cast<std::string>(RF_source_power) + "DB" );

    // provide short delay so network analyzer can set-up
    sleep(1);
    socket->Send( "++addr 16" ); // return to network analyzer
}

/*!
 * \brief Turn on the signal sweeper on or off.
 *
 * This function is only responsible for enabling/disabling the RF
 *  source -- not establishing its' settings.
 *
 * \param source_on
 *
 * value that either turns the signal sweeper on or off,
 *  True = On, False = Off
 */
void NetworkAnalyzer::SetRFSource( bool source_on ) {

    socket->Send( "PT19" ); // set passthrough mode to RF source
    socket->Send( "++addr 17" ); //change GPIB address to passthrough
    if( source_on ) {
        socket->Send( "RF1" ); // turn on RF source
    } else {
        socket->Send( "RF0" ); // turn off RF source
    }

    socket->Send( "++addr 16" );  // change back GPIB address to network analyzer

}
