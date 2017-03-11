#include "Windows/mainwindow.h"
#include <QApplication>

#include "SpectrumAnalyzer/test_spectrum_analyzer.h"
#include "SpectrumAnalyzer/test_spectrum_analyzer.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    etig::test::TestSpectrumAnalyzer tester;
    tester.Test();
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
