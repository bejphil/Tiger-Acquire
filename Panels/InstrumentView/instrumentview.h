#ifndef INSTRUMENTVIEW_H
#define INSTRUMENTVIEW_H

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
#include <QTimer>
//Project specific headers
#include "../JASPL/jTypeTraits/jtypetraits.h"
#include "../JASPL/jAlgorithm/jalgorithm.h"

QT_CHARTS_USE_NAMESPACE

class InstrumentView : public QChartView {

    Q_OBJECT

  public:
    explicit InstrumentView( QString title, QWidget *parent = 0 );
    ~InstrumentView();

    template <class T, typename F>
    void PlotAutoScale( const T& y_signal_elements , F x_frequency_range);

    template <class T>
    void Plot( const T& y_signal_elements , double x_frequency_range);

    template < typename T >
    void UpdateSignal(const std::vector<T>& data , double freq_span );

  private:

    void (InstrumentView::*unit_conversion)( float& ) = NULL;

    void volt_sqr_to_dbm( float& volt_sqr );
    void identity( float& val );

    QLineSeries *data_series;
    QValueAxis *x_axis;
    QValueAxis *y_axis;

    QTimer *auto_timer;
    QChart *chart;

    QString chart_title;

  public slots:
    void SetFrequencyMin( double min_frequency );
    void SetPowerMin( double min_power );
    void SetFrequencyMax( double max_frequency );
    void SetPowerMax( double max_power );

  signals:
    void SignalChanged();
};

#include "instrumentview.tpp"

#endif // INSTRUMENTVIEW_H
