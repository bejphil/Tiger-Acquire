#ifndef PROGRAM_H
#define PROGRAM_H

//C System-Headers
//
//C++ System headers
//
//Qt Headers
#include <QObject>
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include "../ProgramFrame/programframe.h"
#include "../../DataTransformatoions/datatransformations.h"

namespace etig {

class Program : public QObject, public ProgramFrame {

    Q_OBJECT

    typedef std::vector<data_triple<double>> data_list;

  public:
    Program( QObject* parent = 0 );

    double FindModeReflection();
    double FindModeTransmission( double mode_frequency );
    data_list TakeData( double mode_frequency );
    void SavePowerSpectrum( data_list scan );
    void PanicCleanUp();

  private:
    double DeriveLengthFromStart();

  signals:
    void UpdateNA( std::vector< double > na_data, double na_span );
    void UpdateSpec( std::vector< float > spec_data, uint digi_rate );

  public slots:
    void Run();

};

}

#endif // PROGRAM_H
