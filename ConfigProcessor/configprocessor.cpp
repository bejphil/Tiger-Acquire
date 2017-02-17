//Header for this file
#include "configprocessor.h"
//C System-Headers
#include <pwd.h>//pwd
#include <fcntl.h>//fopen(),fclose()
#include <unistd.h>//read(), write()
//C++ System headers
#include <fstream> //ifstream
#include <iostream>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
#include <boost/lexical_cast.hpp>// lexical_cast<T>
#include <boost/algorithm/string.hpp>//split() and is_any_of for parsing .csv files
//Project specific headers
//

ConfigProcessor::ConfigProcessor( std::string file_path ) {
    CheckIfExists( file_path );
    Load( file_path );
}

//ConfigProcessor & operator=( const ConfigProcessor & processor );

void ConfigProcessor::CheckIfExists( std::string file_path ) {

    std::ifstream config_in;

    std::lock_guard<std::mutex> lock( monitor );

    config_in.open( file_path.c_str() );

    if( !config_in.good() ) {
        config_in.close();

        std::ofstream config_out;

        config_out.open( file_path.c_str() , std::ios::out );
        config_out.close();
    } else {
        config_in.close();
    }
}




void ConfigProcessor::Load( std::string file_path ) {

    CheckIfExists( file_path );

    std::ifstream config;

    std::lock_guard<std::mutex> lock( monitor );

    config.open( file_path.c_str() );

    while (config) {
        std::string input;
        std::getline(config, input);

        //Ignore comment lines started with #
        std::string::size_type look = input.find("#");
        if(look!=std::string::npos) {
            input=input.substr(0, look);
        }

        std::vector<std::string> strs;
        boost::split(strs, input, boost::is_any_of(","));

        std::string type_identifier = strs.at(0);

        if( type_identifier == "double" ) {
            std::string name = strs.at(1);
            double val = boost::lexical_cast<double>( strs.at(2) );

            data_list.push_back( PlainDataParam<double>(name,val) );
        } else if ( type_identifier == "string" ) {
            std::string name = strs.at(1);
            std::string val = strs.at(2);

            string_list.push_back( PlainDataParam<std::string>( name, val ) );
        } else if ( type_identifier == "socket" ) {
            std::string name = strs.at(1);
            std::string ip_addr = strs.at(2);
            uint port = boost::lexical_cast<uint>( strs.at(3) );

            socket_info_list.push_back( TCPSocketParam( name, ip_addr, port ) );
        }
    }

    config.close();
}
