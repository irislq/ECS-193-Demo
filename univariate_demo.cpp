#include <iostream>
#include <symengine/polys/uexprpoly.h>
#include <symengine/series_generic.h>

using namespace SymEngine;

int main()
{
	RCP<const Symbol> x = symbol("x");

	// compare tests
	// RCP<const UExprPoly> P = uexpr_poly(x, {{0, 1}, {1, 2}});
 //    RCP<const UExprPoly> Q = uexpr_poly(x, {{0, 1}, {1, 2}, {2, 1}});
 //    RCP<const UExprPoly> R = uexpr_poly(y, {{0, 1}, {1, 2}, {3, 3}});
 //    std::cout << P->compare(*Q) << std::endl;
 //    std::cout << Q->compare(*Q) << std::endl;
 //    std::cout << R->compare(*Q) << std::endl;

    // max_coef tests
    // RCP<const UExprPoly> a = uexpr_poly(x, {{0, 1}, {1, 2}, {2, 4}});
    // std::cout << a->max_coef() << std::endl;

    // eval test
	// RCP<const UExprPoly> a = uexpr_poly(x, {{0, 1}, {1, 2}, {2, symbol("a")}});
 //    std::cout << a->eval(2) << std::endl;

    // is_zero tests
    // RCP<const UExprPoly> z = uexpr_poly(x, {{0, Expression(0)}});
    // RCP<const UExprPoly> o = uexpr_poly(x, {{0, Expression(1)}});
    // std::cout << z->is_zero() << std::endl;
    // std::cout << o->is_zero() << std::endl;

    // is_one tests
    // RCP<const UExprPoly> z = uexpr_poly(x, {{0, Expression(0)}});
    // RCP<const UExprPoly> o = uexpr_poly(x, {{0, Expression(1)}});
    // std::cout << z->is_one() << std::endl;
    // std::cout << o->is_one() << std::endl;

    // is_minus_one tests
    // RCP<const UExprPoly> mo = uexpr_poly(x, {{0, Expression(-1)}});
    // RCP<const UExprPoly> o = uexpr_poly(x, {{0, Expression(1)}});
    // std::cout << mo->is_minus_one() << std::endl;
    // std::cout << o->is_minus_one() << std::endl;

	// is_integer tests
	// RCP<const UExprPoly> p = uexpr_poly(x, {{0, Expression(1)}, {1, Expression(2)}});
 //    RCP<const UExprPoly> i = uexpr_poly(x, {{0, Expression(6)}});
 //    std::cout << p->is_integer() << std::endl;
 //    std::cout << i->is_integer() << std::endl;

	// is_symbol tests
 	// RCP<const UExprPoly> i = uexpr_poly(x, {{0, Expression(6)}});
  //   RCP<const UExprPoly> s = uexpr_poly(x, {{1, Expression(1)}});
  //   std::cout << i->is_symbol() << std::endl;
  //   std::cout << s->is_symbol() << std::endl;

	// is_mul tests
	// RCP<const UExprPoly> i = uexpr_poly(x, {{0, Expression(9)}});
 //    RCP<const UExprPoly> m = uexpr_poly(x, {{3, Expression(5)}});
 //    std::cout << i->is_mul() << std::endl;
 //    std::cout << m->is_mul() << std::endl;

	// is_pow tests
	// RCP<const UExprPoly> m = uexpr_poly(x, {{3, Expression(5)}});
 //    RCP<const UExprPoly> po = uexpr_poly(x, {{5, Expression(1)}});
 //    std::cout << m->is_pow() << std::endl;
 //    std::cout << po->is_pow() << std::endl;

	// diff test
	// RCP<const UExprPoly> a = uexpr_poly(x, {{0, 1}, {1, 2}, {2, symbol("a")}});
 //    std::cout << a->diff(x)->__str__() << std::endl;

	// expand test
	// RCP<const UExprPoly> a = uexpr_poly(x, {{1, 1}, {2, 1}, {3, symbol("a")}});
 //    RCP<const Basic> b = make_rcp<const Pow>(a, integer(3));
 //    std::cout << expand(b)->__str__() << std::endl;

	// add_upoly test
	// UExprDict adict_({{0, 1}, {1, 2}, {2, symbol("a")}});
 //    UExprDict bdict_({{0, 2}, {1, 3}, {2, symbol("b")}});
 //    const UExprPoly a(x, std::move(adict_));
 //    const UExprPoly b(x, std::move(bdict_));
 //    std::cout << add_upoly(a, b)->__str__() << std::endl;

	// neg_upoly test
	// UExprDict adict_({{0, 1}, {1, symbol("a")}, {2, symbol("c")}});
 //    const UExprPoly a(x, std::move(adict_));
 //    std::cout << neg_upoly(a)->__str__() << std::endl;

	// sub_upoly test
	// UExprDict adict_({{0, 1}, {1, 2}, {2, 1}});
 //    UExprDict bdict_({{0, 2}, {1, symbol("b")}, {2, symbol("a")}});
 //    const UExprPoly a(x, std::move(adict_));
 //    const UExprPoly b(x, std::move(bdict_));
 //    std::cout << sub_upoly(b, a)->__str__() << std::endl;

	// mul_upoly test
	// RCP<const UExprPoly> a = uexpr_poly(x, {{0, 1}, {1, symbol("b")}, {2, symbol("a")}});
 //    RCP<const UExprPoly> b = uexpr_poly(x, {{0, -1}, {1, -2}, {2, mul(integer(-1), symbol("a"))}});
 //    std::cout << mul_upoly(*a, *b)->__str__() << std::endl;

	// uexpr_poly test with UExprDict
	// UExprDict dict({{0, 1}, {1, 2}, {2, 1}});
 //    RCP<const UExprPoly> P = uexpr_poly(x, std::move(dict));
 //    std::cout << P->__str__() << std::endl;

    // uexpr_poly test with map_int_Expr
    // map_int_Expr dict = {{0, symbol("d")}, {1, 2}, {2, 3}, {3, symbol("a")}};
    // RCP<const UExprPoly> P = uexpr_poly(x, std::move(dict));
    // std::cout << P->__str__() << std::endl;

	// get_coeff test
	// auto p = cos(x);
 //    auto ser = UnivariateSeries::series(p, x->get_name(), 3);
 //    // print the 2nd-term coefficient
 //    std::cout << *ser->get_coeff(2) << std::endl;

	// series test
	// auto p = sin(x);
 //    auto ser = UnivariateSeries::series(p, x->get_name(), 10);
 //    std::cout << *ser << std::endl;

	// univariate_series test
	// UExprDict dict({{0, 1}, {1, 2}, {2, 1}});
 //    RCP<const UnivariateSeries> P = univariate_series(x, 2, dict);
 //    std::cout << P->__str__() << std::endl;

	return 0;
}