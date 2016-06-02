#include <iostream>
#include <chrono>
#include <symengine/symengine_config.h>
#include <symengine/series_generic.h>
#include <symengine/series_generic_multivariate.h>

using namespace SymEngine;

int main()
{
    RCP<const Symbol> x = symbol("x");
    RCP<const Symbol> y = symbol("y");
    int N = 200;

    auto ex = mul(sin(add(x, pow(x, integer(2)))), cos(add(x, pow(x, integer(2)))));

    std::cout << "Univariate series expansion of " << *ex << "by UnivariateSeries with precision " << N << " takes ";
    auto t1 = std::chrono::high_resolution_clock::now();
    auto res = UnivariateSeries::series(ex, "x", N);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                     .count()
              << "ms" << std::endl;
              std::cout << std::endl;

    std::cout << "Univariate series expansion of " << *ex << "by MultivariateSeries with precision " << N << " takes ";
    t1 = std::chrono::high_resolution_clock::now();
    auto res2 = MultivariateSeries::series(ex, "x", N);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                     .count()
              << "ms" << std::endl;
              std::cout << std::endl;              

    auto ex2 = mul(sin(x), cos(y));
    int M = 100;

    std::cout << "Multivariate series expansion (mult_series1) of " << *ex << " with precision " << M << " takes " ;
    t1 = std::chrono::high_resolution_clock::now();
    RCP<const MultivariateSeries> ser2 = mult_series1(ex2, {{x, M}, {y, M}});
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                     .count()
              << "ms" << std::endl;
              std::cout << std::endl;

    std::cout << "Multivariate series expansion (mult_series<MultivariateSeries>) of " << *ex << " with precision " << M << " takes ";
    t1 = std::chrono::high_resolution_clock::now();
    RCP<const MultivariateSeries> s1 = mult_series<MultivariateSeries>(ex2, {{x, M},{y, M}});
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                     .count()
              << "ms" << std::endl;
              std::cout << std::endl;

    std::cout << "Multivariate series expansion (mult_series<UnivariateSeries>) of " << *ex << " with precision " << M << " takes ";
    t1 = std::chrono::high_resolution_clock::now();
    RCP<const MultivariateSeries> s2 = mult_series<UnivariateSeries>(ex2, {{x, M},{y, M}});
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                     .count()
              << "ms" << std::endl;
              std::cout << std::endl;

    return 0;
}

