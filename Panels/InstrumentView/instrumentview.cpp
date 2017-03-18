//Header for this file
#include "instrumentview.h"
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

InstrumentView::InstrumentView( QString title, QWidget *parent ) : QChartView(parent),
    chart_title( title ) {

    data_series = new QLineSeries();

    x_axis = new QValueAxis;
    y_axis = new QValueAxis;
    chart = new QChart();

    chart->addSeries(data_series);
    chart->legend()->hide();

    chart->createDefaultAxes();
    chart->setAxisX(x_axis, data_series);
    chart->setAxisY(y_axis, data_series);

    chart->setTheme(QChart::ChartThemeDark);

    QPen pen(Qt::cyan);
    pen.setWidth(1);
    data_series->setPen(pen);

    this->setChart( chart );
    this->setRenderHint(QPainter::Antialiasing);

    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::cyan));
    chart->setTitle( chart_title );
}

void InstrumentView::SetFrequencyMin( double min_frequency ) {
    chart->axisX()->setMin( min_frequency );
}

void InstrumentView::SetPowerMin( double min_power ) {
    chart->axisY()->setMin( min_power );
}

void InstrumentView::SetFrequencyMax( double max_frequency ) {
    chart->axisX()->setMax( max_frequency );
}

void InstrumentView::SetPowerMax( double max_power ) {
    chart->axisY()->setMax( max_power );
}

//void InstrumentView::UpdateSignal(const std::vector<float> &data, double freq_span ) {

//    Plot( data , freq_span );

//}

InstrumentView::~InstrumentView() {}
