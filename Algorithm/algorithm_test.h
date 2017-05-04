#ifndef ALGORITHM_TEST_H
#define ALGORITHM_TEST_H

#include "algorithm.h"

namespace etig {

void test_Rebin() {
    auto test_rebin = Rebin<float>();

    std::vector<float> time_series = { 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5 };

    float f_res = 1.0f;
    float t_int = 3.0f*2.0f/( f_res * 1e6 );

    test_rebin( time_series, f_res, t_int );
    std::vector< float > rebinned_sig = test_rebin.RebinnedSignal();
    uint rebin_size = test_rebin.RebinSize();

    std::cout << "Rebinned signal elements " << std::endl;

    for( const auto& elem : rebinned_sig ) {
        std::cout << elem << std::endl;
    }

    std::cout << "Rebinned signal size " << rebin_size << std::endl;
}

}

#endif // ALGORITHM_TEST_H
