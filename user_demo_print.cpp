#include <iostream>
#include <symengine/polys/uexprpoly.h>
#include <symengine/series_generic.h>
#include <symengine/polynomial_multivariate.h>
#include <symengine/series_generic_multivariate.h>

using namespace SymEngine;

int main()
{
	RCP<const Symbol> x = symbol("x");
	RCP<const Symbol> y = symbol("y");
	RCP<const Symbol> z = symbol("z");

	// User can edit dictionary_
	UExprDict dictionary_( {{0, 1}, {1, 2}} );
	RCP<const UExprPoly> P = uexpr_poly(x, std::move(dictionary_));
	std::cout << "Printing the univariate polynomial: ";
	std::cout << P->__str__() << std::endl;
	std::cout << std::endl;

	// User can edit p. This is the polynomial that will be used for series expansion
	auto p = sin(x);

	// User can edit precision number
	int uprec = 10;

	auto ser = UnivariateSeries::series(p, x->get_name(), uprec);
	std::cout << "Printing the univariate series expansion of " << *p << " with precision " << uprec << ": ";
	std::cout << *ser << std::endl;
	std::cout << std::endl;

	// User can edit Q
	MultivariatePolynomialExpr Q = MultivariatePolynomialExpr::create({x,y,z}, 
		{{{0,0,0}, Expression(symbol("a"))},
		{{0,0,1}, Expression(symbol("b"))}, 
		{{0,1,0}, Expression(symbol("c"))},
		{{1,0,0}, Expression(symbol("d"))},
		{{1,2,0}, Expression(symbol("f"))}});
	std::cout << "Printing the multivariate polynomial: ";
	std::cout << Q.toString() << std::endl;
	std::cout << std::endl;

	// User can edit precision number
	int mprec = 5;

	// User can edit p2
	auto p2 = mul(sin(x), cos(y));
	RCP<const MultivariateSeries> ser2 = mult_series1(p2, {{x,mprec}, {y,mprec}});
	std::cout << "Printing the multivariate series expansion of " << *p2 << " from mult_series1: ";
	std::cout << ser2->__str__() << std::endl;
	std::cout << std::endl;

	RCP<const MultivariateSeries> s1 = mult_series<MultivariateSeries>(p2, {{x,mprec},{y,mprec}});
	std::cout << "Printing the multivariate series expansion of " << *p2 << " from mult_series<MultivariateSeries>: ";
	std::cout << s1->__str__() << std::endl;
	std::cout << std::endl;

	RCP<const MultivariateSeries> s2 = mult_series<UnivariateSeries>(p2, {{x,mprec},{y,mprec}});
	std::cout << "Printing the multivariate series expansion of " << *p2 << " from mult_series<UnivariateSeries>: ";
	std::cout << s2->__str__() << std::endl;
	std::cout << std::endl;

	return 0;
}
