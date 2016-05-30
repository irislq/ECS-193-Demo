#include <chrono>
#include <iostream>
#include <string>
#include <symengine/polys/uexprpoly.h>
#include <symengine/series_generic.h>

using namespace SymEngine;
using namespace std;

string int_to_bool(int i)
{
	if(i == 1)
		return "true";
	else if(i == 0)
		return "false";
	else
		return "";
}

int main()
{
	RCP<const Symbol> x = symbol("x");

	// compare tests
	cout << "Testing UExprPoly::compare" << endl;
	RCP<const Symbol> y = symbol("y");
	RCP<const UExprPoly> P = uexpr_poly(x, {{0, 1}, {1, 2}});
    RCP<const UExprPoly> Q = uexpr_poly(x, {{0, 1}, {1, 2}, {2, 1}});
    RCP<const UExprPoly> R = uexpr_poly(y, {{0, 1}, {1, 2}, {3, 3}});
    cout << "(" << P->__str__() << ") compared to (" << Q->__str__() << ") is equal to " << P->compare(*Q) << endl;
    cout << "(" << Q->__str__() << ") compared to (" << Q->__str__() << ") is equal to " << Q->compare(*Q) << endl;
    cout << "(" << R->__str__() << ") compared to (" << Q->__str__() << ") is equal to " << R->compare(*Q) << endl;
    cout << endl;

    // max_coef tests
    cout << "Testing UExprPoly::max_coef" << endl;
    RCP<const UExprPoly> a = uexpr_poly(x, {{0, 1}, {1, 2}, {2, 4}});
    cout << "The coefficient value at the highest degree of " << a->__str__() << " is " << a->max_coef() << endl;
    cout << endl;

    // eval test
    cout << "Testing UExprPoly::eval" << endl;
	RCP<const UExprPoly> b = uexpr_poly(x, {{0, 1}, {1, 2}, {2, symbol("a")}});
	int n = 2;
    cout << "Evaluating " << b->__str__() << " at x = " << n << " is equal to " << b->eval(n) << endl;
    cout << endl;

    RCP<const UExprPoly> z = uexpr_poly(x, {{0, Expression(0)}});
    RCP<const UExprPoly> o = uexpr_poly(x, {{0, Expression(1)}});
    RCP<const UExprPoly> mo = uexpr_poly(x, {{0, Expression(-1)}});
    RCP<const UExprPoly> p = uexpr_poly(x, {{0, Expression(1)}, {1, Expression(2)}});
    RCP<const UExprPoly> i = uexpr_poly(x, {{0, Expression(6)}});
    RCP<const UExprPoly> s = uexpr_poly(x, {{1, Expression(1)}});
    RCP<const UExprPoly> m = uexpr_poly(x, {{3, Expression(5)}});
    RCP<const UExprPoly> po = uexpr_poly(x, {{5, Expression(1)}});

    // is_zero tests
    cout << "Testing UExprPoly::is_zero" << endl;
    cout << z->__str__() << " is tested to be: " << int_to_bool(z->is_zero()) << endl;
    cout << o->__str__() << " is tested to be: " << int_to_bool(o->is_zero()) << endl;
    cout << endl;

    // is_one tests
    cout << "Testing UExprPoly::is_one" << endl;
    cout << z->__str__() << " is tested to be: " << int_to_bool(z->is_one()) << endl;
    cout << o->__str__() << " is tested to be: " << int_to_bool(o->is_one()) << endl;
    cout << endl;

    // is_minus_one tests
    cout << "Testing UExprPoly::is_minus_one" << endl;
    cout << mo->__str__() << " is tested to be: " << int_to_bool(mo->is_minus_one()) << endl;
    cout << o->__str__() << " is tested to be: " << int_to_bool(o->is_minus_one()) << endl;
    cout << endl;

	// is_integer tests
	cout << "Testing UExprPoly::is_integer" << endl;
    cout << p->__str__() << " is tested to be: " << int_to_bool(p->is_integer()) << endl;
    cout << i->__str__() << " is tested to be: " << int_to_bool(i->is_integer()) << endl;
    cout << endl;

	// is_symbol tests
	cout << "Testing UExprPoly::is_symbol" << endl;
    cout << i->__str__() << " is tested to be: " << int_to_bool(i->is_symbol()) << endl;
    cout << s->__str__() << " is tested to be: " << int_to_bool(s->is_symbol()) << endl;
    cout << endl;

	// is_mul tests
	cout << "Testing UExprPoly::is_mul" << endl;
    cout << i->__str__() << " is tested to be: " << int_to_bool(i->is_mul()) << endl;
    cout << m->__str__() << " is tested to be: " << int_to_bool(m->is_mul()) << endl;
    cout << endl;

	// is_pow tests
	cout << "Testing UExprPoly::is_pow" << endl;
    cout << m->__str__() << " is tested to be: " << int_to_bool(m->is_pow()) << endl;
    cout << po->__str__() << " is tested to be: " << int_to_bool(po->is_pow()) << endl;
    cout << endl;

	// diff test
	cout << "Testing diff" << endl;
	RCP<const UExprPoly> c = uexpr_poly(x, {{0, 1}, {1, 2}, {2, symbol("a")}});
    cout << "The derivative of " << c->__str__() << " with respect to x is " << a->diff(x)->__str__() << endl;
    cout << endl;

	// expand test
	cout << "Testing expand" << endl;
	RCP<const UExprPoly> d = uexpr_poly(x, {{1, 1}, {2, 1}, {3, symbol("a")}});
    RCP<const Basic> e = make_rcp<const Pow>(d, integer(3));
    cout << "Expanding " << d->__str__() << " to the power of 3 is equal to " << expand(e)->__str__() << endl;
    cout << endl;

	// add_upoly test
	cout << "Testing add_upoly" << endl;
	UExprDict cdict_({{0, 1}, {1, 2}, {2, symbol("a")}});
    UExprDict ddict_({{0, 2}, {1, 3}, {2, symbol("b")}});
    const UExprPoly cpoly(x, std::move(cdict_));
    const UExprPoly dpoly(x, std::move(ddict_));
    cout << "( " << cpoly.__str__() << " ) + ( " << dpoly.__str__() << " ) = " << add_upoly(cpoly, dpoly)->__str__() << endl;
    cout << endl;

	// neg_upoly test
	cout << "Testing neg_upoly" << endl;
	UExprDict edict_({{0, 1}, {1, symbol("a")}, {2, symbol("c")}});
    const UExprPoly epoly(x, std::move(edict_));
    cout << "-( " << epoly.__str__() << " ) = " << neg_upoly(epoly)->__str__() << endl;
    cout << endl;

	// sub_upoly test
	cout << "Testing sub_upoly" << endl;
	UExprDict adict_({{0, 1}, {1, 2}, {2, 1}});
    UExprDict bdict_({{0, 2}, {1, symbol("b")}, {2, symbol("a")}});
    const UExprPoly apoly(x, std::move(adict_));
    const UExprPoly bpoly(x, std::move(bdict_));
    cout << "( " << apoly.__str__() << " ) - ( " << bpoly.__str__() << " ) = " << sub_upoly(bpoly, apoly)->__str__() << endl;
    cout << endl;

	// mul_upoly test
	cout << "Testing mul_upoly" << endl;
	RCP<const UExprPoly> f = uexpr_poly(x, {{0, 1}, {1, symbol("b")}, {2, symbol("a")}});
    RCP<const UExprPoly> g = uexpr_poly(x, {{0, -1}, {1, -2}, {2, mul(integer(-1), symbol("a"))}});
    cout << "( " << f->__str__() << " ) * ( " << g->__str__() << " ) = " << mul_upoly(*f, *g)->__str__() << endl;
    cout << endl;

	// uexpr_poly test with UExprDict
	cout << "Testing uexprpoly from UExprPoly" << endl;
	UExprDict dict1({{0, 1}, {1, 2}, {2, 1}});
    RCP<const UExprPoly> S = uexpr_poly(x, std::move(dict1));
    cout << "Constructed: " << S->__str__() << endl;
    cout << endl;

    // uexpr_poly test with map_int_Expr
    cout << "Testing uexprpoly from map_int_Expr" << endl;
    map_int_Expr dict2 = {{0, symbol("d")}, {1, 2}, {2, 3}, {3, symbol("a")}};
    RCP<const UExprPoly> T = uexpr_poly(x, std::move(dict2));
    cout << "Constructed: " << T->__str__() << endl;
    cout << endl;

	// get_coeff test
	cout << "Testing UnivariateSeries::get_coeff" << endl;
	auto p1 = cos(x);
    auto ser1 = UnivariateSeries::series(p1, x->get_name(), 3);
    cout << "The 2nd coefficient of the series expansion of " << *p1 << " is " << *ser1->get_coeff(2) << endl;
    cout << endl;

	// series test
	cout << "Testing UnivariateSeries::series" << endl;
	auto p2 = sin(x);
    auto ser2 = UnivariateSeries::series(p2, x->get_name(), 10);
    cout << "The series expansion of " << *p2 << " is " << *ser2 << endl;
    cout << endl;

	// univariate_series test
	cout << "Testing univariate_series" << endl;
	UExprDict dict_({{0, 1}, {1, 2}, {2, 1}});
    RCP<const UnivariateSeries> U = univariate_series(x, 2, dict_);
    cout << "Constructed: " << U->__str__() << endl;
    cout << endl;

    // Series expansion benchmarking
    int N = 200;
    auto arg = add(x, pow(x, integer(2)));
    auto ex = mul(sin(arg), cos(arg));

    auto t1 = std::chrono::high_resolution_clock::now();
    auto res = UnivariateSeries::series(ex, "x", N);
    auto t2 = std::chrono::high_resolution_clock::now();
    // std::cout << *a << std::endl;
    cout << "Time to run the series expansion of " << *ex << " with a precision of " << N << " takes ";
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                     .count()
              << "ms" << endl;

	return 0;
}