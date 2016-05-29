#include <iostream>
#include <symengine/polys/uexprpoly.h>
#include <symengine/series_generic.h>

using namespace SymEngine;

int main()
{
	RCP<const Symbol> x = symbol("x");

	// User can edit dictionary_
	UExprDict dictionary_( {{0, 1}, {1, 2}} );
	RCP<const UExprPoly> P = uexpr_poly(x, std::move(dictionary_));
	std::cout << P->__str__() << std::endl;

	// User can edit p. This is the polynomial that will be used for series expansion
	auto p = sin(x);
	// User can edit precision number
	auto ser = UnivariateSeries::series(p, x->get_name(), 10);
	// User can edit coeff
	RCP<const Basic> coeff = ser->get_coeff( 9 );
	std::cout << coeff->__str__() << std::endl;

	return 0;
}