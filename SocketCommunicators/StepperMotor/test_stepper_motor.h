#ifndef TEST_STEPPER_MOTOR_H
#define TEST_STEPPER_MOTOR_H

//C System-Headers
//
//C++ System headers
#include <memory>
//Boost Headers
//
//Qt Headers
//
//Project specific headers
#include "stepper_motor.h"
#include "../Arduino/arduino.h"
#include "../../Generics/generics.h"

void TestStepperMotor() {

    std::cout << "Testing Stepper Motor." << std::endl;

    const TCPSocketParam stepper = TCPSocketParam( "Stepper", "10.95.100.177", 7776 );
    std::shared_ptr<StepperMotor> stm23_ee = std::shared_ptr<StepperMotor>( new StepperMotor( stepper.ip_addr,\
            stepper.port_addr ) );

    std::cout << "Tuning cavity by + 1 inch." << std::endl;
    stm23_ee->TuneCavity( 1.0 );

    sleep(5);

    std::cout << "Tuning cavity by - 1 inch." << std::endl;
    stm23_ee->TuneCavity( -1.0 );

}

void TestStepperMotorWithArduino() {

    std::cout << "Testing Stepper Motor and Arduino." << std::endl;

    const TCPSocketParam arduino_info = TCPSocketParam( "Arduino", ";10.66.192.41", 23 );
    std::shared_ptr<Arduino> arduino = std::shared_ptr<Arduino>( new Arduino( arduino_info.ip_addr,\
                                       arduino_info.port_addr ) );

    const TCPSocketParam stepper = TCPSocketParam( "Stepper", "10.95.100.177", 7776 );
    std::shared_ptr<StepperMotor> stm23_ee = std::shared_ptr<StepperMotor>( new StepperMotor( stepper.ip_addr,\
            stepper.port_addr ) );

    const double starting_length = 6.0;
    double cavity_length = arduino->GetCavityLength();

    std::cout << "Setting cavity to length of " << starting_length << " Inches." << std::endl;
    stm23_ee->TuneToLength( starting_length, cavity_length );

}

#endif // TEST_STEPPER_MOTOR_H
