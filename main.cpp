//C System-Headers
//
//C++ System headers
//
// Qt
//#include "Windows/mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QThread>
// Project specific headers
#include "Program/Program/program.h"
#include "Panels/testpanels.h"

#include "Windows/mainwindow.h"
#include "Panels/SpectrumAnalyzer/spectrumanalyzer.h"
#include "Windows/mainwindow.h"
#include "Panels/InstrumentView/instrumentview.h"
int main(int argc, char *argv[]) {

    QApplication q_app(argc, argv);

//    QThread* thread = new QThread;
    MainWindow window;

//    SpectrumAnalyzer* spec_analyzer = new SpectrumAnalyzer( window );
//    window -> SetSpectrumAnalyzerView( spec_analyzer );

//    InstrumentView* na_view = new InstrumentView( "Network Analyzer", window );
//    window -> SetNetworkAnalyzerView( na_view );

//    auto prog = std::shared_ptr<etig::Program>( new etig::Program( window ) );

//    QObject::connect( prog.get(), &etig::Program::UpdateNA, na_view, &InstrumentView::UpdateSignal );
//    QObject::connect( prog.get(), &etig::Program::UpdateSpec, spec_analyzer, &SpectrumAnalyzer::UpdateSignal );

//    prog->Run();

//    worker->moveToThread(thread);

//    QObject::connect(thread, SIGNAL(started()), worker, SLOT(process()));
//    QObject::connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
//    QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
//    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
//    thread->start();

//    etig::test::TestPanels tester;
//    tester.Test();

    return q_app.exec();
}
