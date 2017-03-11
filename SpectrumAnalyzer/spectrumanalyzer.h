#ifndef SPECTRUMANALYZER_H
#define SPECTRUMANALYZER_H

//C System-Headers
#include <cxxabi.h> //abi::__cxa_demangle
//C++ System headers
#include <typeinfo> //typeid(T).name()
//OpenCL Headers
//
//Boost Headers
//
//Qt Headers
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCore/QDateTime>
#include <QtCharts/QSplineSeries>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCharts/QValueAxis>
#include <QMainWindow>
#include <QTimer>
//Project specific headers
#include "../JASPL/jPlot/jplot.h"
#include "../JASPL/jTypeTraits/jtypetraits.h"
#include "../JASPL/jFFT/jfft.h"
#include "../JASPL/jAlgorithm/jalgorithm.h"

QT_CHARTS_USE_NAMESPACE

class SpectrumAnalyzer : public QChartView {

    Q_OBJECT

  public:
    explicit SpectrumAnalyzer(QWidget *parent = 0);
    ~SpectrumAnalyzer();

    void Activate();

    template <class T, typename F>
    void PlotAutoScale( const T& y_signal_elements , F x_frequency_range);

    template <class T>
    void Plot( const T& y_signal_elements , double x_frequency_range);

    void UpdateSignal( const std::vector<float>& time_series , uint sample_rate );

  private:

    void (SpectrumAnalyzer::*unit_conversion)( float& ) = NULL;

    void volt_sqr_to_dbm( float& volt_sqr );
    void identity( float& val );

    QLineSeries *spectrum_series;
    QValueAxis *x_axis;
    QValueAxis *y_axis;

    QTimer *auto_timer;
    QChart *chart;

    QString title = "Spectrum Analyzer";

    jaspl::JFFT< std::vector< float > > fft_er;
    const uint fft_points = 1024;

  public slots:
//    void UpdateSignal( std::vector<float> time_series , uint sample_rate );
//    void UpdateAndAverage( std::vector<float> time_series , uint sample_rate );

    void SetFrequencyMin( double min_frequency );
    void SetPowerMin( double min_power );
    void SetFrequencyMax( double max_frequency );
    void SetPowerMax( double max_power );

    void ChangeToVolts();
    void ChangeTodBm();

  signals:
    void SignalChanged();
};

#include "../SpectrumAnalyzer/spectrumanalyzer.tpp"

#endif // SPECTRUMANALYZER_H
