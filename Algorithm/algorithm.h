#ifndef ALGORITHM_H
#define ALGORITHM_H

//C System-Headers
//
//C++ System headers
#include <string>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
#include <boost/algorithm/string.hpp>//split(), is_any_of, trim
#include <boost/lexical_cast.hpp>
//Project specific headers
//

namespace etig {

void remove_newlines( std::string& str );

}


#endif /* ALGORITHM_H */
