#ifndef PROGRAMFRAME_H
#define PROGRAMFRAME_H

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
#include "../ProgramCore/programcore.h"
#include "../../ModeTracker/modetrack.h"
#include "../../DataSaver/FlatFileSaver/flatfilesaver.h"
#include "../../DataTransformatoions/datatransformations.h"

namespace etig {

class ProgramFrame : public ProgramCore {

    Q_OBJECT

    typedef std::vector<data_triple<double>> data_list;

  public:
    ProgramFrame( QObject* parent );
    void Prequel();
    void ShiftFrequencyWindow( double center_frequency );
    void SetBackground();
    void EstablishBinSize();
    double FindMinimaPeak( data_list formatted_points);

  protected:
    ModeTrack mode_tracker;
    FlatFileSaver data_saver { save_file_path };

    data_list power_to_data_list ( std::vector< float > power_list,
                                   float min_freq,
                                   float max_freq );

    data_list power_to_data_list ( std::vector< double > power_list,
                                   double min_freq,
                                   double max_freq );

    template < typename T >
    std::vector< T > data_list_to_power( std::vector< data_triple <T> > data );

    double CheckPeak( double possible_mode_position );
    std::string BuildHeader();

  private:

    double DeriveCavityLength();
    double RecenterPeak(std::vector<data_triple<double> > to_check);

    //Mode characterization
    double center_frequency = 0.0;
    double hwhm = 0.0;
    double quality_factor = 0.0;

    const double single_scan_window = 100.0;

  signals:
    void UpdateNA( std::vector< double > na_data, double na_span );
    void UpdateSpec( std::vector< float > spec_data, uint digi_rate );

    void ToTransmission();
    void ToReflection();
    void OutputToDigitizer();
    void OutputToNA();

    void Iteration( uint iter );
    void CavityLength( double length );
    void LOFrequency( double lo_freq );

};

}

#endif // PROGRAMFRAME_H
