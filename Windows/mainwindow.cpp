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
//
//Project specific headers
#include "Panels/SpectrumAnalyzer/spectrumanalyzer.h"
#include "Panels/GraphicObjects/frequencycontrols.h"
#include "Panels/GraphicObjects/chartscalecontrols.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Electric Tiger");

    QPalette dark_palette = palette();
    dark_palette.setColor(QPalette::Window, QRgb(0x121218));
    dark_palette.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(dark_palette);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetNetworkAnalyzerView( InstrumentView* network_analyzer ) {

    network_analyzer->setAttribute(Qt::WA_DeleteOnClose);

    auto power_ctrls = new PowerControls();
    power_ctrls->setAttribute(Qt::WA_DeleteOnClose);
    power_ctrls->setPalette(dark_palette);

//        setCentralWidget( network_analyzer );
    ui->panelLayout->addWidget( network_analyzer );

    connect(power_ctrls, &PowerControls::MinSet, network_analyzer, &InstrumentView::SetPowerMin);
    connect(power_ctrls, &PowerControls::MaxSet, network_analyzer, &InstrumentView::SetPowerMax);

    connect(power_ctrls, &PowerControls::SelectedVolts, network_analyzer, &InstrumentView::ChangeToVolts);
    connect(power_ctrls, &PowerControls::SelecteddBm, network_analyzer, &InstrumentView::ChangeTodBm);

    addDockWidget(Qt::LeftDockWidgetArea, power_ctrls);
}

void MainWindow::SetSpectrumAnalyzerView( SpectrumAnalyzer* spec_analyzer ) {

//    spec_analyzer->resize();
    spec_analyzer->setAttribute(Qt::WA_DeleteOnClose);

    auto power_ctrls = new PowerControls();
    power_ctrls->setAttribute(Qt::WA_DeleteOnClose);
    power_ctrls->setPalette(dark_palette);

//    power_ctrls->resize( ui->digitizerView->size() );
//    setCentralWidget( spec_analyzer );
    ui->panelLayout->addWidget( spec_analyzer );

    connect(power_ctrls, &PowerControls::MinSet, spec_analyzer, &SpectrumAnalyzer::SetPowerMin);
    connect(power_ctrls, &PowerControls::MaxSet, spec_analyzer, &SpectrumAnalyzer::SetPowerMax);

    connect(power_ctrls, &PowerControls::SelectedVolts, spec_analyzer, &SpectrumAnalyzer::ChangeToVolts);
    connect(power_ctrls, &PowerControls::SelecteddBm, spec_analyzer, &SpectrumAnalyzer::ChangeTodBm);

    addDockWidget(Qt::RightDockWidgetArea, power_ctrls);

}