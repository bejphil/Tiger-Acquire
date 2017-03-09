//Header for this file
#include "SpectrumAnalyzer/spectrumanalyzer.h"
#include "SpectrumAnalyzer/GraphicObjects/chartscalecontrols.h"
#include "SpectrumAnalyzer/GraphicObjects/frequencycontrols.h"
//C System-Headers
#include <math.h>
//C++ System headers
//
//OpenCL Headers
//
//Boost Headers
//
//Qt Headers
#include <QThread>
//Project specific headers

SpectrumAnalyzer::SpectrumAnalyzer( QWidget *parent ) : QChartView(parent),
    fft_er(  fft_points, true ),
    avg( fft_points /2 ) {

  spectrum_series = new QLineSeries();

  x_axis = new QValueAxis;
  y_axis = new QValueAxis;
  chart = new QChart();

  chart->addSeries(spectrum_series);
  chart->legend()->hide();

  chart->createDefaultAxes();
  chart->setAxisX(x_axis, spectrum_series);
  chart->setAxisY(y_axis, spectrum_series);

  chart->setTheme(QChart::ChartThemeDark);

  QPen pen(Qt::yellow);
  pen.setWidth(1);
  spectrum_series->setPen(pen);

  this->setChart( chart );
  this->setRenderHint(QPainter::Antialiasing);

}

void SpectrumAnalyzer::SetFrequencyMin( double min_frequency ) {
    chart->axisX()->setMin( min_frequency );
}

void SpectrumAnalyzer::SetPowerMin( double min_power ) {
    chart->axisY()->setMin( min_power );
}

void SpectrumAnalyzer::SetFrequencyMax( double max_frequency ) {
    chart->axisX()->setMin( max_frequency );
}

void SpectrumAnalyzer::SetPowerMax( double max_power ) {
    chart->axisY()->setMin( max_power );
}

void SpectrumAnalyzer::Activate() {
  //
}

double volts_sqr_to_dbm( double voltage ) {
    return 10.0 * log10( voltage / std::sqrt(0.05) );
}

struct VoltsSqrTodBm {
    void operator()( float& data_point ) const {
        data_point = volts_sqr_to_dbm( data_point );
    }
};

void SpectrumAnalyzer::ProcessSignal(std::vector < float > &time_series) {

  fft_er.PowerSpectrum( time_series );
  uint spectrum_size = time_series.size();

  uint n_half = (spectrum_size % 2 == 0) ? (spectrum_size / 2) : (( spectrum_size - 1) / 2);

  time_series.erase( time_series.end() - n_half, time_series.end() );

  std::for_each(time_series.begin(), time_series.end(), VoltsSqrTodBm());

}

void SpectrumAnalyzer::UpdateSignal( std::vector< float > time_series, uint sample_rate ) {

  ProcessSignal(time_series);

  float fft_span = static_cast<float>( sample_rate / 2 );

  Plot( time_series , fft_span );
}

void SpectrumAnalyzer::UpdateAndAverage(std::vector< float > time_series,
                                     uint sample_rate) {

  ProcessSignal(time_series);

  avg( time_series );

  float fft_span = static_cast<float>( sample_rate / 2 );

  Plot( avg.ReturnValue() , fft_span );
}

SpectrumAnalyzer::~SpectrumAnalyzer() {}
