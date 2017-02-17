#ifndef DAQ_FAILURE_H
#define DAQ_FAILURE_H

//C System-Headers
//
//C++ System headers
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
//

class daq_failure : public std::exception {

  public:
    explicit daq_failure( const char* message ) : err_message( message ){}

    const char* what() const throw() {
        return err_message;
    }

  private:
    const char* err_message;
};


#endif // DAQ_FAILURE_H
