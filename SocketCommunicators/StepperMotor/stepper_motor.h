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
#include "../SocketComm/q_socket_comm.h"
#include "../AbstractSocketCommunicator/abstractsocketcommunictor.h"

/*!
 * \brief Object to sends commands to an Applied Motion products stepper motor.
 */
class StepperMotor : public AbstractSocketCommunicator {

  public:
    StepperMotor( std::string ip_addr, uint port_number );
    StepperMotor& operator=( const StepperMotor& ) = delete; // non copyable

    void SetToInitialLength( double initial_length, double current_length );
    void ResetCavity( double length_of_tune );
    void PanicResetCavity( uint iteration, double revs_per_iter );
    void TuningLoop( double len_of_tune, double revs, uint iters, uint num_of_iters );

  private:
    void SetUpStepperMotor( double traverse_speed );




};


#endif // STEPPERMOTOR_H
