//Header for this file
#include "mainwindow.h"
#include "ui_mainwindow.h"
//C System-Headers
//
//C++ System headers
//
//OpenCL Headers
//
//Boost Headers
//
//Qt Headers
#include <QThread>
//Project specific headers
#include "Panels/SpectrumAnalyzer/spectrumanalyzer.h"
#include "Panels/GraphicObjects/frequencycontrols.h"
#include "Panels/GraphicObjects/chartscalecontrols.h"

#include "../Program/Program/program.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Electric Tiger");

    QPalette dark_palette = palette();
    dark_palette.setColor(QPalette::Window, QRgb(0x121218));
    dark_palette.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(dark_palette);

    SpectrumAnalyzer* spec_analyzer = new SpectrumAnalyzer( this );
    SetSpectrumAnalyzerView( spec_analyzer );

    InstrumentView* na_view = new InstrumentView( "Network Analyzer", this );
    SetNetworkAnalyzerView( na_view );

    etig::Program* prog = new etig::Program;

//    QObject::connect( prog, &etig::Program::UpdateNA, na_view, &InstrumentView::UpdateSignal );
//    QObject::connect( prog, &etig::Program::UpdateSpec, spec_analyzer, &SpectrumAnalyzer::UpdateSignal );
    qRegisterMetaType< std::vector<double> >("std::vector<double>");
    qRegisterMetaType< std::vector<float> >("std::vector<float>");

    QThread* thread = new QThread;

    prog->etig::Program::moveToThread( thread );

    QObject::connect( prog, &etig::Program::UpdateNA, na_view, &InstrumentView::UpdateSignal );
    QObject::connect( prog, &etig::Program::UpdateSpec, spec_analyzer, &SpectrumAnalyzer::UpdateSignal );

    QObject::connect( thread, &QThread::started, prog, &etig::Program::Run );

    QObject::connect( thread, &QThread::finished, prog, &etig::Program::deleteLater );
    QObject::connect( thread, &QThread::finished, thread, &QThread::deleteLater );

    connect( this, &MainWindow::destroyed, prog, &etig::Program::Stop );

    thread->start();

    show();
    raise();
    activateWindow();
}

MainWindow::~MainWindow() {

//    thread->quit();
    delete ui;
}

void MainWindow::SetNetworkAnalyzerView( InstrumentView* network_analyzer ) {

    network_analyzer->setAttribute(Qt::WA_DeleteOnClose);
    ui->panelLayout->addWidget( network_analyzer );

}

void MainWindow::SetSpectrumAnalyzerView( SpectrumAnalyzer* spec_analyzer ) {

    spec_analyzer->setAttribute(Qt::WA_DeleteOnClose);

    auto power_ctrls = new PowerControls();
    power_ctrls->setAttribute(Qt::WA_DeleteOnClose);
    power_ctrls->setPalette(dark_palette);

    ui->panelLayout->addWidget( spec_analyzer );

    connect(power_ctrls, &PowerControls::MinSet, spec_analyzer, &SpectrumAnalyzer::SetPowerMin);
    connect(power_ctrls, &PowerControls::MaxSet, spec_analyzer, &SpectrumAnalyzer::SetPowerMax);

    connect(power_ctrls, &PowerControls::SelectedVolts, spec_analyzer, &SpectrumAnalyzer::ChangeToVolts);
    connect(power_ctrls, &PowerControls::SelecteddBm, spec_analyzer, &SpectrumAnalyzer::ChangeTodBm);

    addDockWidget(Qt::BottomDockWidgetArea, power_ctrls);

}
