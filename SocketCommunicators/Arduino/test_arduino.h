#ifndef TEST_ARDUINO_H
#define TEST_ARDUINO_H

//C System-Headers
//
//C++ System headers
#include <memory>
//Boost Headers
//
//Qt Headers
//
//Project specific headers
#include "arduino.h"
#include "../../Generics/generics.h"

void TestArduino() {

    std::cout << "Testing Arduino" << std::endl;

    const TCPSocketParam arduino_info = TCPSocketParam( "Arduino", ";10.66.192.41", 23 );
    std::shared_ptr<Arduino> arduino = std::shared_ptr<Arduino>( new Arduino( arduino_info.ip_addr,\
                                       arduino_info.port_addr ) );

    double current_cavity_length = arduino->GetCavityLength();

    std::cout << "Current cavity length: " << current_cavity_length << std::endl;
}

#endif // TEST_ARDUINO_H
