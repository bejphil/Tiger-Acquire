template <class T, typename F>
void InstrumentView::PlotAutoScale( const T& y_signal_elements ,
                                     F x_frequency_range) {

    uint N = y_signal_elements.size();

    double N_f = static_cast<double>(N);

    uint k = static_cast<uint>(ceil(static_cast<double>(N) / 2048.0));

    data_series->clear();

    for (uint i = 0; i < N ; i += k) {

        double step = static_cast<double>(i) / N_f * x_frequency_range;
        data_series->append(step, y_signal_elements[i]);

    }

    auto y_min = std::min_element(y_signal_elements.begin(), y_signal_elements.end());

    auto y_max = std::max_element(y_signal_elements.begin(), y_signal_elements.end());

    chart->axisX()->setRange(0, x_frequency_range);
    chart->axisY()->setRange(*y_min, *y_max);
}

template <class T>
void InstrumentView::Plot( const T& y_signal_elements , double x_frequency_range ) {

    uint N = y_signal_elements.size();

    double N_f = static_cast<double>(N);

    data_series->clear();

    for (uint i = 0; i < N ; i ++ ) {

        double step = static_cast<double>(i) / N_f * x_frequency_range;
        data_series->append( step, y_signal_elements.at(i) );

    }

    chart->axisX()->setRange(0, x_frequency_range);

}

//template < typename T >
//void InstrumentView::UpdateSignal(const std::vector< T > &data, double freq_span ) {

//    PlotAutoScale( data , freq_span );

//}

