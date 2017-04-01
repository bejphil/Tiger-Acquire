#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

//C System-Headers
//
//C++ System headers
#include <vector>
//Boost Headers
//
//Qt Headers
//
//Project specific headers
#include "../AbstractSocketCommunicator/abstractintermittensocket.h"
#include "../AbstractSocketCommunicator/abstractsocketcommunictor.h"

/*!
 * \brief Object to sends commands to an Applied Motion products stepper motor.
 */
class StepperMotor : public AbstractIntermittenSocket {

  public:
    StepperMotor( std::string ip_addr, uint port_number, QObject* parent = 0 );
    StepperMotor& operator=( const StepperMotor& ) = delete; // non copyable

    void TuneToLength( double desired_length, double current_length );
    void TuneCavity( double length_of_tune );
    void PanicResetCavity( uint iteration, double revs_per_iter );
    void TuningLoop(double len_of_tune, double revs, uint iters);

  private:
    void SetUpStepperMotor( double traverse_speed = 5.0 );

};


#endif // STEPPERMOTOR_H
