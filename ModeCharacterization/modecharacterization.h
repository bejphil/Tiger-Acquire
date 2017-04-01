#ifndef MODECHARACTERIZATION_H
#define MODECHARACTERIZATION_H

//C System-Headers
//
//C++ System headers
#include <vector>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include "../Generics/generics.h"

class ModeTraits {
  public:
    ModeTraits( const std::vector<data_triple<double> >& data_values );
    double Q();
    double f0();

private:
    double Q_factor = 0.0;
    double f_0 = 0.0;
};

#endif /* MODECHARACTERIZATION_H */
