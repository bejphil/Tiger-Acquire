//Header for this file
#include "SpectrumAnalyzer/spectrumanalyzer.h"
#include "SpectrumAnalyzer/GraphicObjects/chartscalecontrols.h"
#include "SpectrumAnalyzer/GraphicObjects/frequencycontrols.h"
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

void SpectrumAnalyzer::Activate() {
    //
}

//double volts_sqr_to_dbm( double voltage ) {
//    return 10.0 * log10( voltage / 0.05 );
//}

//struct VoltsSqrTodBm {
//    void operator()( float& data_point ) const {
//        data_point = volts_sqr_to_dbm( data_point );
//    }
//};

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

void SpectrumAnalyzer::UpdateSignal(const std::vector<float> &time_series, uint sample_rate ) {
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

    Plot( power_spec , fft_span );
}

//void SpectrumAnalyzer::UpdateAndAverage(std::vector< float > time_series, uint sample_rate) {

//    ProcessSignal(time_series);

//    avg( time_series );

//    float fft_span = static_cast<float>( sample_rate / 2 );

//    Plot( avg.ReturnValue() , fft_span );
//}

SpectrumAnalyzer::~SpectrumAnalyzer() {}
