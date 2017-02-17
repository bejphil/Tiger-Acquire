#ifndef CONIGPROCESSOR_H
#define CONIGPROCESSOR_H

//C System-Headers
//
//C++ System headers
#include <vector>
#include <string>
#include <ostream>
#include <mutex>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
//

template < typename T >
struct PlainDataParam {

    PlainDataParam( std::string name, T val ) : data_name( name ),\
        data_value( val ) {}

    friend std::ostream& operator << (std::ostream& stream, PlainDataParam& param) {

            stream << param.data_name << "," \
                   << param.data_value;

        return stream;
    }

    const std::string data_name;
    const T data_value;
};

struct TCPSocketParam {

    TCPSocketParam( std::string name, std::string addr, uint port ) : inst_name( name ), \
        ip_addr( addr ),\
        port_addr( port ) {}

    friend std::ostream& operator << (std::ostream& stream, TCPSocketParam& param) {

            stream << param.inst_name << "," \
                   << param.ip_addr << "," \
                   << param.port_addr;

        return stream;
    }

    const std::string inst_name;
    const std::string ip_addr;
    const uint port_addr;
};

class ConfigProcessor {

  public:
    ConfigProcessor( std::string file_path );

    template < typename T >
    T GetValue( std::string param_name ) {

        for( const auto& par : data_list ) {
            if( par.data_name == par.data_name )
                return par;
        }

        for( const auto& par : string_list ) {
            if( par.data_name == param_name )
                return par;
        }

        for( const auto& par : socket_info_list ) {
            if( par.inst_name == param_name )
                return par;
        }
    }

    std::vector< PlainDataParam< double > > data_list;
    std::vector< PlainDataParam< std::string > > string_list;
    std::vector< TCPSocketParam > socket_info_list;

  private:

    void CheckIfExists( std::string file_path );
    void Load( std::string file_path );

    std::mutex monitor;
};


#endif // CONIGPROCESSOR_H
