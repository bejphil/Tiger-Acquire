//C System-Headers
//
//C++ System headers
//
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
//
// Header for this file
#include "algorithm.h"

namespace etig {

void remove_newlines( std::string& str ) {
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
}

}
