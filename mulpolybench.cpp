#include <iostream>
#include <chrono>
#include <symengine/polys/uexprpoly.h>
#include <symengine/polynomial_multivariate.h>
#include <stdlib.h>

using namespace SymEngine::literals;
using namespace std;
using namespace SymEngine;

void mpolydict1(unsigned int num, umap_vec_expr& d)
{
   for(unsigned int i = 0; i < num; i++) {
            vec_int v;
            v.resize(3);
            v[0] = rand();
            v[1] = rand();
            v[2] = rand();
            d.insert(std::pair<vec_int, Expression>(v,Expression(rand())));
   }
}

void mpolyupolydict1(unsigned int num, umap_vec_expr& d1,map_int_Expr& d2)
{
   for(unsigned int i = 0; i < num; i++) {
            vec_int v;
            v.resize(1);
            int j = rand();
            int k = rand();
            v[0] = j;
            d1.insert(std::pair<vec_int, Expression>(v,Expression(k)));
            d2.insert(std::pair<int,Expression>(j,Expression(k)));
   }
}


int main()
{
    RCP<const Symbol> a = symbol("a");
    RCP<const Symbol> b = symbol("b");
    RCP<const Symbol> c = symbol("c");

    RCP<const Symbol> x = symbol("x");
    RCP<const Symbol> y = symbol("y");
    RCP<const Symbol> z = symbol("z");
    srand(42);


    cout << "Polynomials of several variables" << endl << endl;
    unsigned int limits[] = {25,100,1000,10000,100000};
    unsigned int N = 5;
    for (unsigned int k = 0; k < N ; k++) {
        std::vector<umap_vec_expr> d;
        d.resize(8);
        for(unsigned int i = 0 ; i < 8; i++)
            mpolydict1(limits[k], d[i]);

        auto t1 = std::chrono::high_resolution_clock::now();

        MultivariatePolynomialExpr p1 = MultivariatePolynomialExpr::create({x,y,z}, std::move(d[0]));

        auto t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Creating a polynomial of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;

        t1 = std::chrono::high_resolution_clock::now();

        MultivariatePolynomialExpr p2 = MultivariatePolynomialExpr::create({x,y,z}, std::move(d[1]));
        MultivariatePolynomialExpr p3 = p2.neg();

        t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Negating a polynomial of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;


        t1 = std::chrono::high_resolution_clock::now();
	
        MultivariatePolynomialExpr p4 = MultivariatePolynomialExpr::create({x,y,z}, std::move(d[2]));
        MultivariatePolynomialExpr p5 = MultivariatePolynomialExpr::create({x,y,z}, std::move(d[3]));
        MultivariatePolynomialExpr p6 = add_mult_poly(p4,p5);

        t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Adding polynomials of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;

        t1 = std::chrono::high_resolution_clock::now();

        MultivariatePolynomialExpr p7 = MultivariatePolynomialExpr::create({x,y,z}, std::move(d[4]));
        MultivariatePolynomialExpr p8 = MultivariatePolynomialExpr::create({x,y,z}, std::move(d[5]));
        MultivariatePolynomialExpr p9 = sub_mult_poly(p7,p8);

        t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Subtracting polynomials of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;

        if (limits[k] <= 1000) {    
        t1 = std::chrono::high_resolution_clock::now();


        MultivariatePolynomialExpr p10 = MultivariatePolynomialExpr::create({x,y,z},std::move(d[6]));
        MultivariatePolynomialExpr p11 = MultivariatePolynomialExpr::create({x,y,z},std::move(d[7]));

        MultivariatePolynomialExpr p12 = mul_mult_poly(p10,p11);

        t2 = std::chrono::high_resolution_clock::now();

        std::cout << "Multiplying polynomials of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
	}
	std::cout << std::endl;

    }





    
    std::cout << std::endl << "With different variables" << std::endl << std::endl;





    
    for (unsigned int k = 0; k < N ; k++) {

        std::vector<umap_vec_expr> d;
        d.resize(6);
        for(unsigned int i = 0 ; i < 6; i++)
            mpolydict1(limits[k], d[i]);

        auto t1 = std::chrono::high_resolution_clock::now();

        MultivariatePolynomialExpr p1 = MultivariatePolynomialExpr::create({x,y,z}, std::move(d[0]));
        MultivariatePolynomialExpr p2 = MultivariatePolynomialExpr::create({a,b,c}, std::move(d[1]));
        MultivariatePolynomialExpr p3 = add_mult_poly(p1,p2);

        auto t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Adding polynomials of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;

        t1 = std::chrono::high_resolution_clock::now();

        MultivariatePolynomialExpr p4 = MultivariatePolynomialExpr::create({x,y,z}, std::move(d[2]));
        MultivariatePolynomialExpr p5 = MultivariatePolynomialExpr::create({a,b,c}, std::move(d[3]));
        MultivariatePolynomialExpr p6 = sub_mult_poly(p4,p5);

        t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Subtracting polynomials of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
	if( limits[k] <= 1000) {
        t1 = std::chrono::high_resolution_clock::now();


        MultivariatePolynomialExpr p7 = MultivariatePolynomialExpr::create({x,y,z},std::move(d[4]));
        MultivariatePolynomialExpr p8 = MultivariatePolynomialExpr::create({a,b,c},std::move(d[5]));

        MultivariatePolynomialExpr p9 = mul_mult_poly(p7,p8);

        t2 =  std::chrono::high_resolution_clock::now(); 

        std::cout << "Multiplying polynomials of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
	}
	std::cout << std::endl;
    }

    std::cout << endl;
    std::cout << "Univariable Polynomials" << endl << endl;


    for (unsigned int k = 0; k < N ; k++) {

        std::vector<umap_vec_expr> d1;
        d1.resize(6);
        std::vector<map_int_Expr> d2;
        d2.resize(6);
        for(unsigned int i = 0 ; i < 6; i++)
            mpolyupolydict1(limits[k], d1[i],d2[i]);

        auto t1 = std::chrono::high_resolution_clock::now();

        MultivariatePolynomialExpr p1 = MultivariatePolynomialExpr::create({x}, std::move(d1[0]));
        MultivariatePolynomialExpr p2 = MultivariatePolynomialExpr::create({x}, std::move(d1[1]));
        MultivariatePolynomialExpr p3 = add_mult_poly(p1,p2);

        auto t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Adding MultivariatePolynomialExprs of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;


        t1 = std::chrono::high_resolution_clock::now();

        RCP<const UExprPoly> q1 = uexpr_poly(x, std::move(d2[0]));
        RCP<const UExprPoly> q2 = uexpr_poly(x, std::move(d2[1]));
        RCP<const UExprPoly> q3 = add_upoly(*q1,*q2);

        t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Adding UExprPolys of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;

        t1 = std::chrono::high_resolution_clock::now();

        MultivariatePolynomialExpr p4 = MultivariatePolynomialExpr::create({x}, std::move(d1[2]));
        MultivariatePolynomialExpr p5 = MultivariatePolynomialExpr::create({x}, std::move(d1[3]));
        MultivariatePolynomialExpr p6 = sub_mult_poly(p4,p5);

        t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Subtracting MultivaraitePolynomialExprs of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;


        t1 = std::chrono::high_resolution_clock::now();

        RCP<const UExprPoly> q4 = uexpr_poly(x, std::move(d2[2]));
        RCP<const UExprPoly> q5 = uexpr_poly(x, std::move(d2[3]));
        RCP<const UExprPoly> q6 = sub_upoly(*q4,*q5);

        t2 = std::chrono::high_resolution_clock::now(); 

        std::cout << "Subtracting UExprPolys of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;


	if( limits[k] <= 1000) {
        t1 = std::chrono::high_resolution_clock::now();


        MultivariatePolynomialExpr p7 = MultivariatePolynomialExpr::create({x},std::move(d1[4]));
        MultivariatePolynomialExpr p8 = MultivariatePolynomialExpr::create({x},std::move(d1[5]));

        MultivariatePolynomialExpr p9 = mul_mult_poly(p7,p8);

        t2 =  std::chrono::high_resolution_clock::now(); 

        std::cout << "Multiplying MultivariatePolynomialExprs of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;

        RCP<const UExprPoly> q7 = uexpr_poly(x,std::move(d2[4]));
        RCP<const UExprPoly> q8 = uexpr_poly(x,std::move(d2[5]));

        RCP<const UExprPoly> q9 = mul_upoly(*q7,*q8);

        t2 =  std::chrono::high_resolution_clock::now(); 

        std::cout << "Multiplying UExprPolys of " << limits[k] << " terms: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
	}
	std::cout << std::endl;
    }

}
