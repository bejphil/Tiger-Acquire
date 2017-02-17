#ifndef GENERICS_H
#define GENERICS_H

//C System-Headers
//
//C++ System headers
#include <string>
#include <vector>
#include <iostream>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
//

struct TCPSocketParam {

    TCPSocketParam( const std::string& name, const std::string& addr, uint port ) : inst_name( name ), \
        ip_addr( addr ),\
        port_addr( port ) {}

    TCPSocketParam & operator=(const TCPSocketParam & sock_param ) {
        inst_name = sock_param.inst_name;
        ip_addr = sock_param.ip_addr;
        port_addr = sock_param.port_addr;

        return *this;
    }

    friend std::ostream& operator << (std::ostream& stream, TCPSocketParam& param) {

        stream << param.inst_name << "," \
               << param.ip_addr << "," \
               << param.port_addr;

        return stream;
    }

    std::string inst_name;
    std::string ip_addr;
    uint port_addr;
};

template< typename T >
struct data_triple {

    data_triple( T cav_len, T freq, T power ) : cavity_length( cav_len ),\
        frequency_MHz( freq ), \
        power_dBm( power ) {
        static_assert( std::is_floating_point<T>::value, "data_triple must be initialized with floating point type.");
    }

    data_triple & operator=(const data_triple & triple ) {
        cavity_length = triple.cavity_length;
        frequency_MHz = triple.frequency_MHz;
        power_dBm = triple.power_dBm;

        return *this;
    }

    /*
    friend std::ostream& operator << (std::ostream& stream, data_triple& triple) {

        stream << triple.cavity_length << "," \
               << triple.frequency_MHz << ","\
               << triple.power_dBm;

        return stream;
    }
    */

    friend std::ofstream& operator << (std::ofstream& stream, const data_triple& triple) {

        stream << triple.cavity_length << "," \
               << triple.frequency_MHz << ","\
               << triple.power_dBm;

        return stream;
    }

    T cavity_length;
    T frequency_MHz;
    T power_dBm;

};

#endif /* GENERICS_H */
