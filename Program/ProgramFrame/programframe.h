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

class ProgramFrame : public ProgramCore {

    typedef std::vector<data_triple<double>> data_list;

  public:
    ProgramFrame();
    void Prequel();
    void ShiftFrequencyWindow( double center_frequency );
    void SetBackground();
    double FindMinimaPeak( data_list formatted_points);

  protected:
    ModeTrack mode_tracker;
    FlatFileSaver data_saver { save_file_path };

    data_list power_to_data_list ( std::vector< float > power_list );
    data_list power_to_data_list ( std::vector< double > power_list );

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

};


#endif // PROGRAMFRAME_H
