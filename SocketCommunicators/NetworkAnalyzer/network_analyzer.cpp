//C System-Headers
//
//C++ System headers
//
//Boost Headers
#include <boost/algorithm/string.hpp>//split(), is_any_of
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

std::vector< double > NetworkAnalyzer::TakeDataMultiple() {

    const std::vector< double > frequency_centers { 3200.0, 3600.0, 4000.0, 4400.0 };

    SetFrequencySpan( 400.0 );

    std::string raw_power_spectrum = "";

    for( const auto& center : frequency_centers ) {

        //Set passthrought mode to source
        socket->Send( "PT19" );
        //Change GPIB address to passthrough -- sends commands to signal sweeper
        socket->Send( "++addr 17" );
        std::string frequency_str = boost::lexical_cast<std::string>( center );
        //Set center frequency
        socket->Send( "CF " + frequency_str + "MZ" );
        //Set signal sweep time to 100ms ( fastest possible )
        socket->Send( "ST100MS" );
        sleep(1);

        //Return to Network Analyzer
        socket->Send( "++addr 16" );

        //Turn off swept mode
        socket->Send( "SW0" );
        //Set Analyzer to perform exactly one sweep
        socket->Send( "TS1" );
        //Give Network Analyzer time to complete sweep
        //This delay time needs to be much longer than the transfer time
        // for a single series of ASCII values ( ~0.8 ) for some reason.
        // If the Analyzer does not have time to complete a sweep
        // we will gather the most recent data set --
        // usually an old data set or garbage.
        sleep( 3 );

        //Take measurement, Input A absolute power measurement
        socket->Send( "C1IA" );
        socket->Send( "C1OD" );
        //Date output in ASCII mode takes ~0.8 seconds -- wait before trying to read data
        sleep(1);
        socket->Send( "++read10" );

        raw_power_spectrum += socket->Receive();

    }

    return raw_str_to_vector( raw_power_spectrum );
}

/*!
 * \brief Collect a single power spectrum from the Network Analyzer
 *
 * Settings will be whatever the Network Analyzer was set to when this function is called.
 * \return
 */
std::vector< double > NetworkAnalyzer::TakeDataSingle() {
    //Change GPIB address to passthrough -- send commands to signal sweeper
   socket->Send( "++addr 17" );

   //Set signal sweep time to 100ms (fastest possible)
   socket->Send( "ST100MS" );
   sleep(1);

   //Return to network analyzer
   socket->Send( "++addr 16" );

   //Turn off swept mode
   socket->Send( "SW0" );
   //Set Analyzer to perform exactly one sweep
   socket->Send( "TS1" );
   //Give Network Analyzer time to complete sweep
   sleep(3);

   //Take measurement
   // Input A absolute power measurement
   socket->Send( "C1IA" );
   socket->Send( "C1OD" );
   //Date output in ASCII mode takes ~0.8 seconds -- wait before trying to read data
   sleep(1);
   socket->Send( "++read10" );

   std::string raw_power_spectrum = socket->Receive();

   return raw_str_to_vector( raw_power_spectrum );
}

void NetworkAnalyzer::SetFrequencySpan( double frequency_span ) {
    // set passthrough mode to source
    socket->Send( "PT19" );
    // change GPIB address to passthrough, send commands to signal sweeper
    socket->Send( "++addr 17" );

    std::string span_str = boost::lexical_cast<std::string>( frequency_span );
    // set frequency window around center to specified span
    socket->Send( "DF " + span_str + "MZ" );
    sleep(1);

    // return to network analyzer
    socket->Send( "++addr 16" );
}

void NetworkAnalyzer::SetFrequencyWindow( double frequency, double frequency_span ) {

    // set passthrough mode to source
    socket->Send( "PT19" );
    // change GPIB address to passthrough, send commands to signal sweeper
    socket->Send( "++addr 17" );

    // set center frequency to frequency specified
    std::string freq_str = boost::lexical_cast<std::string>( frequency );

    socket->Send( "CF " + freq_str + "MZ" );
    sleep(1);

    std::string span_str = boost::lexical_cast<std::string>( frequency_span );
    // set frequency window around center to specified span
    socket->Send( "DF " + span_str + "MZ" );
    sleep(1);

    // return to network analyzer
    socket->Send( "++addr 16" );
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

/*!
 * \brief Convert raw string pulled from network analyzer to a vector
 *
 * \param raw_data
 *
 * Raw string with comma-seperated list of values ended with "\n"
 *
 * \return Vector of power values
 */
std::vector< double > NetworkAnalyzer::raw_str_to_vector( std::string raw_data ) {

    std::vector<std::string> strs;
    boost::split(strs, raw_data, boost::is_any_of(","));

    std::vector< double > power_values;
    power_values.reserve( strs.size() );

    for( uint i = 0; i < strs.size() ; i++ ) {
        power_values.push_back( boost::lexical_cast<double>( strs.at(i) ) );
    }

    return power_values;

}
