#ifndef FLATFILESAVER_H
#define FLATFILESAVER_H

//C System-Headers
//
//C++ System headers
#include <string>
#include <vector>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include "../../Generics/generics.h"

class FlatFileSaver {

  public:
    FlatFileSaver( std::string save_file_path );
    void Save(const std::vector<data_triple<double> > &data_values, std::string header );

  protected:
    std::string GenerateSaveFileName( uint index );

  private:
    void MakeEmptyDataFolder( std::string root_directory );
    std::string GetFolderName();

    std::string root_dir;
    uint counter = 0;

};


#endif // FLATFILESAVER_H
