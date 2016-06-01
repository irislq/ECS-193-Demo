CC=g++
CFLAGS=-c -Wall
COMPILE_FLAGS=`cmake --find-package -DNAME=SymEngine -DCOMPILER_ID=GNU -DLANGUAGE=CXX -DMODE=COMPILE`
LINK_FLAGS=`cmake --find-package -DNAME=SymEngine -DCOMPILER_ID=GNU -DLANGUAGE=CXX -DMODE=LINK`

all: univariate_demo multivariate_demo user_demo_time user_demo_print mulpolybench

univariate_demo: 
	g++ -o univariate_demo.out $(COMPILE_FLAGS) univariate_demo.cpp $(LINK_FLAGS) -std=c++11

multivariate_demo:
	g++ -o multivariate_demo.out $(COMPILE_FLAGS) multivariate_demo.cpp $(LINK_FLAGS) -std=c++11

user_demo_print:
	g++ -o user_demo_print.out $(COMPILE_FLAGS) user_demo_print.cpp $(LINK_FLAGS) -std=c++11

user_demo_time:
	g++ -o user_demo_time.out $(COMPILE_FLAGS) user_demo_time.cpp $(LINK_FLAGS) -std=c++11
mulpolybench:
	g++ -o mulpolybench.out $(COMPILE_FLAGS) mulpolybench.cpp $(LINK_FLAGS) -std=c++11

clean:
	rm *.out
