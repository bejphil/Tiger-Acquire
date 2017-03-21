//C System-Headers
//
//C++ System headers
//
// Qt
//#include "Windows/mainwindow.h"
#include <QApplication>
// Project specific headers
#include "Program/Program/program.h"
#include "Panels/testpanels.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    std::shared_ptr< etig::Program >( new etig::Program() );
//    prog.Run();
//    etig::test::TestPanels tester;
//    tester.Test();

    return a.exec();
}
