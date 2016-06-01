#include <iostream>
#include <chrono>
#include <symengine/polys/uintpoly.h>
#include <symengine/polys/uexprpoly.h>
#include <symengine/series_generic.h>
#include <symengine/series_generic_multivariate.h>
using namespace std;
using namespace SymEngine;

int main(){
    RCP<const Integer> one = integer(1);
    RCP<const Integer> two = integer(2);
    RCP<const Integer> three = integer(3);
    RCP<const Symbol> a = symbol("a");
    RCP<const Symbol> w = symbol("w");
    RCP<const Symbol> x = symbol("x");
    RCP<const Symbol> y = symbol("y");
    RCP<const Symbol> z = symbol("z");

#define TESTS
#ifdef TESTS

    RCP<const UIntPoly> p11 = uint_poly(x, UIntDict({{1,1_z},{2,2_z},{3,2_z}}));
    RCP<const UExprPoly> p21 = uexpr_poly(x, UExprDict({{1,Expression(1)},{2,Expression(2)},{3,Expression(2)}}));

    MultivariateIntPolynomialExpr q11 = MultivariateIntPolynomialExpr::convert(*p11);
    MultivariatePolynomialExpr q21 = MultivariatePolynomialExpr::convert(*p21);

    cout << "Converting Univariate to Multivariate Polynomials" << endl << endl;
    cout << p11->__str__() << " == " << q11.toString() << endl;
    cout << p21->__str__() << " == " << q21.toString() << endl << endl;


    MultivariatePolynomialExpr p12 = MultivariatePolynomialExpr::create({x,y,z},{{{0,0,0},Expression(1)},
        {{0,0,1},Expression(2)}, {{0,1,0},Expression(3)},{{1,0,0},Expression(4)},{{2,0,2},Expression(5)}});
    MultivariatePolynomialExpr p22 = MultivariatePolynomialExpr::create({w,x,y},{{{0,0,0},Expression(6)}, 
        {{0,0,1},Expression(7)}, {{0,1,0},Expression(8)},{{1,0,0},Expression(9)},{{2,0,2},Expression(10)}});
    RCP<const UExprPoly> p32 = uexpr_poly(x, UExprDict({{1,Expression(1)},{2,Expression(2)},{3,Expression(2)}}));
    RCP<const UExprPoly> p42 = uexpr_poly(y, UExprDict({{1,Expression(1)},{2,Expression(2)},{3,Expression(2)}}));

    cout << "Arithmetic between Multivariable Polynomials" << endl << endl;;
    MultivariatePolynomialExpr q12 = add_mult_poly(p12,p22);
    cout << "(" << p12.toString() << ") + (" << p22.toString() << ") == " << q12.toString() << endl;
    q12 = mul_mult_poly(p12,p22);
    cout << "(" << p12.toString() << ") * (" << p22.toString() << ") == " << q12.toString() << endl;
    q12 = sub_mult_poly(p12,p22);
    cout << "(" << p12.toString() << ") - (" << p22.toString() << ") == " << q12.toString() << endl << endl;

    cout << "Arithmetic betweeen Multivariable and Univariable Polynomials" << endl << endl;
    q12 = add_mult_poly(p12,*p32);
    cout << "(" << p12.toString() << ") + (" << p32->__str__() << ") == " << q12.toString() << endl;
    q12 = mul_mult_poly(p12,*p32);
    cout << "(" << p12.toString() << ") * (" << p32->__str__() << ") == " << q12.toString() << endl;
    q12 = sub_mult_poly(p12,*p32);
    cout << "(" << p12.toString() << ") - (" << p32->__str__() << ") == " << q12.toString() << endl << endl;


    cout << "Artithmetic between Univariable Polynomials with different variables" << endl << endl;
    q12 = add_mult_poly(*p32,*p42);
    cout << "(" << p32->__str__() << ") + " << p42->__str__() << ") == " << q12.toString() << endl;
    q12 = mul_mult_poly(*p32,*p42);
    cout << "(" << p32->__str__() << ") * " << p42->__str__() << ") == " << q12.toString() << endl;
    q12 = sub_mult_poly(*p32,*p42);
    cout << "(" << p32->__str__() << ") - " << p42->__str__() << ") == " << q12.toString() << endl << endl;

    cout << "Arithmetic using member functions" << endl << endl;
    q12 = p12.add(p22);
    cout << "(" << p12.toString() << ") + (" << p22.toString() << ") == " << q12.toString() << endl;
    q12 = p12.sub(p22);
    cout << "(" << p12.toString() << ") - (" << p22.toString() << ") == " << q12.toString() << endl;
    q12 = p12.mul(p22);
    cout << "(" << p12.toString() << ") * (" << p22.toString() << ") == " << q12.toString() << endl;
    q12 = p12.neg();
    cout << "- (" << p12.toString() << ") == " << q12.toString() << endl << endl;



    std::map<RCP<const Basic>, Expression, RCPBasicKeyLess> m1 = {{x,Expression(1)},{y,Expression(2)},{z,Expression(3)}};

    cout << "Evalutation of " << p12.toString() << " at x = 1, y = 2, z = 3:" << endl << endl;
    Expression n1 = p12.eval(m1);
    cout << n1 << endl << endl;


    RCP<const Basic> g = sin(x);
    RCP<const MultivariateSeries> s = MultivariateSeries::series(g,"x",10);
    cout << "Series expansion of " << g->__str__() << endl << endl;
    cout << s->__str__() << endl << endl;

    cout << "Multivariable Series Expansion" << endl << endl;

#endif

    RCP<const Basic> f[13];

    f[0] = div(one, add(one, x));
    f[1] = cos(x);
    f[2] = sin(x);
    f[3] = mul(sin(x), cos(x));
    f[4] = sin(atan(x));
    f[5] = sin(mul(a, x));
    f[6] = atan(div(x, sub(one, x)));
    f[7] = tan(x);
    f[8] = tan(div(x, sub(one, x)));
    f[9] = asin(x);
    f[10] = asin(div(x, sub(one, x)));
    f[11] = cot(x);
    f[12] = pow(integer(2), x);


    map_basic_basic b[] = {
                          {{x,add(add(y,z),integer(5))}},
                          {{x,add(mul(y,z),integer(5))}},
                          {{x,add(div(y,add(z,integer(1))),integer(5))}},
                           };
auto t1 = std::chrono::high_resolution_clock::now();
auto t2 = std::chrono::high_resolution_clock::now();


#define PRINTOUTS
//#define MISSES
#define ONE
#define TWO
#define THREE
   vector<std::pair<unsigned int, unsigned int>> misses;
   vector<std::pair<unsigned int, unsigned int>> miss1;
   vector<std::pair<unsigned int, unsigned int>> miss2;
   vector<std::pair<unsigned int, unsigned int>> disagree;

   #ifdef TESTS
   for (unsigned int j = 0; j < 1; j++) {
     for(unsigned int i = 0; i < 1; i++) {
   #else
   for (unsigned int j = 0; j < 3; j++) {
     for(unsigned int i = 0; i < 13; i++) {
   #endif
        auto func = f[i]->subs(b[j]);
        cout << "f: " << func->__str__() << endl;
        #ifdef ONE
	t1 = std::chrono::high_resolution_clock::now();
        RCP<const MultivariateSeries> p1 = mult_series1(func, {{y,5}, {z,5}});
	t2 = std::chrono::high_resolution_clock::now();
        #ifdef PRINTOUTS
        cout << "p1: " << p1->__str__() << endl;
        #endif
	cout << "p1:" << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << endl;
	#endif

        #ifdef TWO
	t1 = std::chrono::high_resolution_clock::now();
        RCP<const MultivariateSeries> p2 = mult_series<UnivariateSeries>(func, {{y,5} , {z,5}});
	t2 = std::chrono::high_resolution_clock::now();
        #ifdef PRINTOUTS
        cout << "p2: " << p2->__str__() << endl;
        #endif
	cout << "p2:" << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << endl;
	#endif

        #ifdef THREE
	t1 = std::chrono::high_resolution_clock::now();
        RCP<const MultivariateSeries> p3 = mult_series<MultivariateSeries>(func, {{y,5} , {z,5}});
	t2 = std::chrono::high_resolution_clock::now();
        #ifdef PRINTOUTS
        cout << "p3: " << p3->__str__() << endl;
        #endif
	cout << "p3:" << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << "ms" << endl;
        #endif

        #ifdef ONE
        #ifdef TWO 
        #ifdef THREE
        bool hit = (eq(*p1,*p2) && eq(*p1,*p3));
	cout <<j << ":" << i << ": " << (eq(*p1,*p2) && eq(*p1,*p3)) << " agree:" << eq(*p2,*p3) << endl << endl;
        if(!hit)
            misses.push_back(std::pair<unsigned int, unsigned int>(j,i));
        if (!eq(*p2,*p3))
            disagree.push_back(std::pair<unsigned int, unsigned int>(j,i));
        if (!eq(*p1,*p2))
            miss1.push_back(std::pair<unsigned int, unsigned int>(j,i));
        if (!eq(*p1,*p3))
            miss2.push_back(std::pair<unsigned int, unsigned int>(j,i));
        #endif
        #endif
        #endif
    }

    cout << endl;
    }
    #ifdef MISSES
    cout << "misses" << endl;
    for(auto i : misses)
        cout << i.first << ":" << i.second << ", "; 
    cout << endl;

    cout << "disagree" << endl;
    for(auto i : disagree)
        cout << i.first << ":" << i.second << ", "; 
    cout << endl;

    cout << "miss 1" << endl;
    for(auto i : miss1)
        cout << i.first << ":" << i.second << ", "; 
    cout << endl;

    cout << "miss 2" << endl;
    for(auto i : miss2)
        cout << i.first << ":" << i.second << ", "; 
    cout << endl;

    #endif

   for (unsigned int j = 0; j < 1; j++) {
     for(unsigned int i = 11; i < 13; i++) {
        auto func = f[i]->subs(b[j]);
        #ifdef ONE
        cout << "f: " << func->__str__() << endl;
	t1 = std::chrono::high_resolution_clock::now();
        RCP<const MultivariateSeries> p1 = mult_series1(func, {{y,5}, {z,5}});
	t2 = std::chrono::high_resolution_clock::now();
        #ifdef PRINTOUTS
        cout << "p1: " << p1->__str__() << endl;
        #endif
	cout << "p1:" << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << endl;
	#endif

        #ifdef TWO
	t1 = std::chrono::high_resolution_clock::now();
        RCP<const MultivariateSeries> p2 = mult_series<UnivariateSeries>(func, {{y,5} , {z,5}});
	t2 = std::chrono::high_resolution_clock::now();
        #ifdef PRINTOUTS
        cout << "p2: " << p2->__str__() << endl;
        #endif
	cout << "p2:" << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << endl;
	#endif

        #ifdef THREE
	t1 = std::chrono::high_resolution_clock::now();
        RCP<const MultivariateSeries> p3 = mult_series<MultivariateSeries>(func, {{y,5} , {z,5}});
	t2 = std::chrono::high_resolution_clock::now();
        #ifdef PRINTOUTS
        cout << "p3: " << p3->__str__() << endl;
        #endif
	cout << "p3:" << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << "ms" << endl;
        #endif

        #ifdef ONE
        #ifdef TWO 
        #ifdef THREE
        bool hit = (eq(*p1,*p2) && eq(*p1,*p3));
	cout <<j << ":" << i << ": " << (eq(*p1,*p2) && eq(*p1,*p3)) << " agree:" << eq(*p2,*p3) << endl << endl;
        if(!hit)
            misses.push_back(std::pair<unsigned int, unsigned int>(j,i));
        if (!eq(*p2,*p3))
            disagree.push_back(std::pair<unsigned int, unsigned int>(j,i));
        if (!eq(*p1,*p2))
            miss1.push_back(std::pair<unsigned int, unsigned int>(j,i));
        if (!eq(*p1,*p3))
            miss2.push_back(std::pair<unsigned int, unsigned int>(j,i));
        #endif
        #endif
        #endif
    }

    cout << endl;
    }


    return 0;
}

