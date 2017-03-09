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

void VoltsTodBm(float &voltage) {
  voltage = 20.0f * log10f(voltage / 50.0f);
}

//void VoltsTodBm_FFTCorrection(float &voltage, float signal_size) {
//  voltage = 10.0f * log10f(voltage) - log10f(signal_size * 50);
//}

//Combination of operations designed to compensate for
//1/N term introduce in FFT, and then convert from volts
//to dBm
//1) compensate for FFT effects: voltage/signal_size
//2) convert to dBm: volts -> dBm
//3) compensate for discarding half of spectrum: dBm/2
struct VoltsTodBm_FFTCorrection {
  float val;
  VoltsTodBm_FFTCorrection(float signal_size) : val(signal_size) {}

  void operator()(float &voltage) const {
    voltage = 10.0f * log10f(voltage / (50.0f * val));
  }
};

void SpectrumAnalyzer::ProcessSignal(std::vector < float > &time_series) {

  fft_er.PowerSpectrum( time_series );
  uint spectrum_size = time_series.size();
  float spectrum_size_f = static_cast<float>(spectrum_size);


  uint n_half = (spectrum_size % 2 == 0) ? (spectrum_size / 2) : ((
                  spectrum_size - 1) / 2);
  time_series.erase(time_series.end() - n_half , time_series.end());

  std::for_each(time_series.begin(), time_series.end(),
                VoltsTodBm_FFTCorrection(spectrum_size_f));

}

void SpectrumAnalyzer::UpdateSignal(std::vector< float > time_series,
                                     uint sample_rate) {

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
