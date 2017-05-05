//Header for this file
#include "spectrumanalyzer.h"
#include "../GraphicObjects/chartscalecontrols.h"
#include "../GraphicObjects/frequencycontrols.h"
//C System-Headers
#include <math.h>
//C++ System headers
#include <algorithm>
//OpenCL Headers
//
//Boost Headers
//
//Qt Headers
#include <QThread>
//Project specific headers

SpectrumAnalyzer::SpectrumAnalyzer( QWidget *parent ) : QChartView(parent),
    fft_er( true ) {

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

    fft_er.SetUp( fft_points );

    unit_conversion = &SpectrumAnalyzer::identity;

    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::yellow));
    chart->setTitle( "Spectrum Analyzer" );

    plot_function = &SpectrumAnalyzer::Plot;
}

void SpectrumAnalyzer::SetFrequencyMin( double min_frequency ) {
    chart->axisX()->setMin( min_frequency );
}

void SpectrumAnalyzer::SetPowerMin( double min_power ) {
    chart->axisY()->setMin( min_power );
}

void SpectrumAnalyzer::SetFrequencyMax( double max_frequency ) {
    chart->axisX()->setMax( max_frequency );
}

void SpectrumAnalyzer::SetPowerMax( double max_power ) {
    chart->axisY()->setMax( max_power );
}

void SpectrumAnalyzer::volt_sqr_to_dbm( float& volt_sqr ) {
    volt_sqr = 10.0f * log10f( volt_sqr / 0.05f );
}

void SpectrumAnalyzer::identity( float& val ) {
    val = std::sqrt( val );
}

void SpectrumAnalyzer::ChangeToVolts() {
    unit_conversion = &SpectrumAnalyzer::identity;
}

void SpectrumAnalyzer::ChangeTodBm() {
    unit_conversion = &SpectrumAnalyzer::volt_sqr_to_dbm;
}

void SpectrumAnalyzer::AutoScaleOn() {
    plot_function = &SpectrumAnalyzer::PlotAutoScale;
}

void SpectrumAnalyzer::AutoScaleOff() {
    plot_function = &SpectrumAnalyzer::Plot;
}


void SpectrumAnalyzer::UpdateSignal( std::vector<float> time_series, uint sample_rate ) {
    ;

    std::cout << "Time series size "
              << time_series.size()
              << " FFT'er expected points "
              << fft_points <<
              std::endl;

    std::vector< float > power_spec = fft_er.PowerSpectrum( time_series );

//    auto f = std::bind(&SpectrumAnalyzer::unit_conversion, this, std::placeholders::_1);
//    std::for_each(power_spec.begin(), power_spec.end(), std::bind1st(&SpectrumAnalyzer::unit_conversion, this));
    for( auto& val : power_spec ) {
        (this->*unit_conversion)( val );
    }

    float fft_span = static_cast<float>( sample_rate / 2 );

    (this->*plot_function)( power_spec, fft_span );

//    Plot( power_spec , fft_span );
}

//void SpectrumAnalyzer::UpdateAndAverage(std::vector< float > time_series, uint sample_rate) {

//    ProcessSignal(time_series);

//    avg( time_series );

//    float fft_span = static_cast<float>( sample_rate / 2 );

//    Plot( avg.ReturnValue() , fft_span );
//}

void SpectrumAnalyzer::PlotAutoScale(const std::vector<float>& y_signal_elements ,
                                     float x_frequency_range) {

    uint N = y_signal_elements.size();

    double N_f = static_cast<double>(N);

//    uint k = static_cast<uint>(ceil(static_cast<double>(N) / 2048.0));

    spectrum_series->clear();

    for (uint i = 0; i < N ; i ++ ) {

        double step = static_cast<double>(i) / N_f * x_frequency_range;
        spectrum_series->append(step, y_signal_elements[i]);

    }

    auto y_min = std::min_element(y_signal_elements.begin(), y_signal_elements.end());
    auto y_max = std::max_element(y_signal_elements.begin(), y_signal_elements.end());

    chart->axisX()->setRange(0, x_frequency_range);
    chart->axisY()->setRange(*y_min, *y_max);
}


void SpectrumAnalyzer::Plot( const std::vector<float>& y_signal_elements,
                             float x_frequency_range ) {

    uint N = y_signal_elements.size();

    double N_f = static_cast<double>(N);

    spectrum_series->clear();

    for (uint i = 0; i < N ; i ++ ) {

        double step = static_cast<double>(i) / N_f * x_frequency_range;
        spectrum_series->append( step, y_signal_elements.at(i) );

    }

    chart->axisX()->setRange(0, x_frequency_range);

}

SpectrumAnalyzer::~SpectrumAnalyzer() {}
