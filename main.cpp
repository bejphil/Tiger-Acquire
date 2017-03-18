#include "Windows/mainwindow.h"
#include <QApplication>

//#include "Panels/SpectrumAnalyzer/test_spectrum_analyzer.h"
//#include "Panels/InstrumentView/test_instrumentview.h"
#include "Panels/testpanels.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    etig::test::TestPanels tester;
    tester.Test();

//    etig::test::TestSpectrumAnalyzer tester;
//    tester.Test();

//    etig::test::TestInstrumentView tester;
//    tester.Test();
//    MainWindow w;
//    w.show();

//    auto spec = new SpectrumAnalyzer();
//    w.SetSpectrumAnalyzerView( spec );

//    auto digitizer = std::unique_ptr<ATS9462Engine> ( new ATS9462Engine( 2e6, 50, 50e6 ) );

//    digitizer->ThreadPoolSize( 10 );
//    digitizer->SetSampleRate( 2e6 );

//    digitizer->StartCapture();

//        sleep( 1 );

//        while( true ) {
//            std::vector< float > volts_data = digitizer->PullVoltageDataTail( 1024 );
//            spec->UpdateSignal( volts_data, 2e6 );
//            sleep( 0.25 );
//        }

    return a.exec();
}
