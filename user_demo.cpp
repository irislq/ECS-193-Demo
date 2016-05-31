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
	auto ser = UnivariateSeries::series(p, x->get_name(), 10);
	std::cout << "Printing the univariate series expansion of " << *p << ": ";
	std::cout << *ser << std::endl;
	std::cout << std::endl;

	MultivariatePolynomialExpr Q = MultivariatePolynomialExpr::create({x,y,z}, 
		{{{0,0,0}, Expression(symbol("a"))},
    		{{0,0,1}, Expression(symbol("b"))}, 
		{{0,1,0}, Expression(symbol("c"))},
		{{1,0,0}, Expression(symbol("d"))},
	        {{1,2,0}, Expression(symbol("f"))}});
	std::cout << "Printing the multivariate polynomial: ";
	std::cout << Q.toString() << std::endl;
	std::cout << std::endl;

	//MultivariateExprPolynomial p1(MultivariatePolynomial::from_dict({x},{{{0},Expression(0)},{{1},Expression(1)},{{2},Expression(3)}}));
	//RCP<const MultivariateSeries> s = multivariate_series(x,10,p1) ;

	auto p2 = mul(sin(x), cos(y));
	RCP<const MultivariateSeries> ser2 = mult_series1(p2, {{x,5}, {y,5}});
	std::cout << "Printing the multivariate series expansion of " << *p2 << " from mult_series1: ";
	std::cout << ser2->__str__() << std::endl;
	std::cout << std::endl;

	RCP<const MultivariateSeries> s1 = mult_series<MultivariateSeries>(p2, {{x,5},{y,5}});
	std::cout << "Printing the multivariate series expansion of " << *p2 << " from mult_series<MultivariateSeries>: ";
	std::cout << s1->__str__() << std::endl;
	std::cout << std::endl;

	RCP<const MultivariateSeries> s2 = mult_series<UnivariateSeries>(p2, {{x,5},{y,5}});
	std::cout << "Printing the multivariate series expansion of " << *p2 << " from mult_series<UnivariateSeries>: ";
	std::cout << s2->__str__() << std::endl;
	std::cout << std::endl;

	return 0;
}
