#ifndef MODE_TRACK_FAILURE_H
#define MODE_TRACK_FAILURE_H

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

class mode_track_failure : public std::exception {

  public:
    explicit mode_track_failure( const char* message ) : err_message( message ){}

    const char* what() const throw() {
        return err_message;
    }

  private:
    const char* err_message;
};

#endif // MODE_TRACK_FAILURE_H
