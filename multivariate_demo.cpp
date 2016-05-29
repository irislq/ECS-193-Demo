#include <iostream>
#include <map>
#include <chrono>
#include <vector>
#include <symengine/symbol.h>
#include <symengine/polynomial.h>
#include <symengine/add.h>
#include <symengine/printer.h>
#include <symengine/dict.h>
#include <symengine/symbol.h>
#include <symengine/symengine_rcp.h>
#include <symengine/expression.h>
#include <symengine/series_generic.h>
using namespace std;
using namespace SymEngine;

void debugprint(const MultivariatePolynomial &p){
  cout << p.__str__() << endl;
  for(auto a : p.vars_){
    cout << a->__str__() << " ";
  }
  cout << endl;
  cout << "{ ";
  for(auto a : p.dict_){
    cout << "{{" ;
    for(auto b : a.first){
      cout << b << ",";
    }
    cout << "}, " <<  a.second << "}, ";
  }
  cout << "}" << endl;
}


int main(){
    RCP<const Basic> f[44];
    RCP<const Integer> one = make_rcp<Integer>(1);
    RCP<const Integer> two = make_rcp<Integer>(2);
    RCP<const Integer> three = make_rcp<Integer>(3);
    RCP<const Symbol> x = symbol("x");
    RCP<const Symbol> y = symbol("y");
    RCP<const Symbol> z = symbol("z");
    f[0] = x;
    f[1] = div(one,add(one,x));
    f[2] = cos(x);
    f[3] = sin(x);
    f[4] = pow(integer(2) , x);
    f[5] = sin(x);
    f[6] = cos(x);
    f[7] = add(sin(x), cos(x));
    f[8] = mul(sin(x), cos(x));
    f[9] = sin(atan(x));
    f[10] = cos(div(x, sub(one, x)));
    f[11] = sin(mul(symbol("a"), x));
    f[12] = div(one, sub(one, x));                 // 1/(1-x)
    f[13] = div(x, sub(sub(one, x), pow(x, two))); // x/(1-x-x^2)
    f[14] = div(pow(x, three), sub(one, mul(pow(x, two), two))); // x^3/(1-2x^2)
    f[15] = div(one, sub(one, sin(x)));                     // 1/(1-sin(x))
    f[16] = div(one, x); 
    f[17] = div(one, mul(x, sub(one, x)));
    f[18] = div(one, mul(symbol("a"), x));
    f[19] = sub(x, pow(x, two));
    f[20] = sub(x, pow(x, three));
    f[21] = sin(x);
    f[22] = mul(x, exp(x));
    f[23] = atan(x);
    f[24] = atan(div(x, sub(one, x)));
    f[25] = tan(x);
    f[26] = tan(div(x, sub(one, x)));
    f[27] = asin(x);
    f[28] = asin(div(x, sub(one, x)));
    f[29] = cot(x); //problem with mulseries1
    f[30] = cot(sin(x)); //problem with mulseries1
    f[31] = sinh(x);
    f[32] = sinh(div(x, sub(one, x)));
    f[33] = cosh(x);
    f[34] = cosh(div(x, sub(one, x)));
    f[35] = tanh(x);
    f[36] = tanh(div(x, sub(one, x)));
    f[37] = atanh(x);
    f[38] = atanh(div(x, sub(one, x)));
    f[39] = asinh(x);
    f[40] = asinh(div(x, sub(one, x)));
    f[41] = x; //lambertw(x); //not Implemented error on mulseries1
    f[42] = x; //lambertw(sin(x)); //not Implemented error on mulseries1
    f[43] = x; //gamma(x); // Complex infinity not yet implemented error on mulseries1


/*     map_basic_basic b[] = {
                          {{x,add(y,z)}},
                          {{x,mul(y,z)}},
                          {{x,div(y,add(z,integer(1)))}},
                          {{x,pow(y,z)}} //log(0) is at complex infinty yet to be implemented error on mulseries1
                          };
*/
    map_basic_basic b[] = {
                          {{x,add(add(y,z),integer(5))}},
                          {{x,add(mul(y,z),integer(5))}},
                          {{x,add(div(y,add(z,integer(1))),integer(5))}},
                          {{x,add(pow(y,z),integer(5))}} //log(0) is at complex infinty yet to be implemented error on mulseries1
			  };
auto t1 = std::chrono::high_resolution_clock::now();
auto t2 = std::chrono::high_resolution_clock::now();

//#define PRINTOUTS
#define ONE
#define TWO
#define THREE
   vector<std::pair<unsigned int, unsigned int>> misses;
   vector<std::pair<unsigned int, unsigned int>> miss1;
   vector<std::pair<unsigned int, unsigned int>> miss2;
   vector<std::pair<unsigned int, unsigned int>> disagree;

   for (unsigned int j = 0; j < 3; j++) {
    for(unsigned int i = 0; i < 44; i++) {
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

    return 0;
}

