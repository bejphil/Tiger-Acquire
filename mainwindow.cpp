#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SpectrumAnalyzer/spectrumanalyzer.h"
#include "SpectrumAnalyzer/GraphicObjects/frequencycontrols.h"
#include "SpectrumAnalyzer/GraphicObjects/chartscalecontrols.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Electric Tiger");

    QPalette dark_palette = palette();
    dark_palette.setColor(QPalette::Window, QRgb(0x121218));
    dark_palette.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(dark_palette);

    SetupSpectrumAnalzyerView();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetupNetworkAnalzyerView() {

}


void MainWindow::SetupSpectrumAnalzyerView() {

    auto spec_analyzer = new SpectrumAnalyzer( ui->digitizerView );
    spec_analyzer->resize( ui->digitizerView->size());
    spec_analyzer->setAttribute(Qt::WA_DeleteOnClose);

    auto power_ctrls = new PowerControls();
    power_ctrls->setAttribute(Qt::WA_DeleteOnClose);
    power_ctrls->setPalette(dark_palette);

    power_ctrls->resize( ui->digitizerView->size() );

    connect(power_ctrls, &PowerControls::MinSet, spec_analyzer, &SpectrumAnalyzer::SetPowerMin);
    connect(power_ctrls, &PowerControls::MaxSet, spec_analyzer, &SpectrumAnalyzer::SetPowerMax);

    addDockWidget(Qt::RightDockWidgetArea, power_ctrls);

}
