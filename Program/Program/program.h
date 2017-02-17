#ifndef PROGRAM_H
#define PROGRAM_H

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
#include "../ProgramFrame/programframe.h"
#include "../../DataTransformatoions/datatransformations.h"

class Program : public ProgramFrame {

    typedef std::vector<data_triple<double>> data_list;

  public:
    Program();

    double FindModeReflection();
    double FindModeTransmission( double mode_frequency );
    data_list TakeData( double mode_frequency );
    void SetBackground();
    void SavePowerSpectrum();
    void PanicCleanUp();

    void Run();


  private:
    double DeriveLengthFromStart();

};


#endif // PROGRAM_H
