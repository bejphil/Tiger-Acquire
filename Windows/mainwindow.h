#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//C System-Headers
//
//C++ System headers
//
//OpenCL Headers
//
//Boost Headers
//
//Qt Headers
#include <QMainWindow>
#include <QPalette>
#include <QHBoxLayout>
#include <QThread>
//Project specific headers
#include "Panels/SpectrumAnalyzer/spectrumanalyzer.h"
#include "Panels/InstrumentView/instrumentview.h"
#include "Panels/StatusCombo/combostatuspanel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow( QWidget *parent = 0 );

    void SetSpectrumAnalyzerView( SpectrumAnalyzer* spec_analyzer );
    void SetNetworkAnalyzerView( InstrumentView* network_analyzer );
    void SetComboStatus( ComboStatusPanel* status_panel );
    ~MainWindow();

  private:

    Ui::MainWindow *ui;
    QHBoxLayout* front_panel_layout;
    QPalette dark_palette;

//    QThread* thread;
};

#endif // MAINWINDOW_H
