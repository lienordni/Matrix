#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <stdexcept>
#include <time.h>

// #include "./complete/matrix.h"
#include <matrix.h>

int main(int argc, char* argv[]){

	int** v=MATRIX::AllocateSpace<int>(28,28);
	int i,j;

	for(i=0;i<28;++i)
		for(j=0;j<28;++j)
			v[i][j]=(i+1+j);

	srand(time(NULL));
	int m=100+rand()%100;
	int n=100+rand()%100;
	int o=100+rand()%100;

	for(int x=10;x<=600;x++) {

		m=n=o=x;

		matrix<int> a(MATRIX::random<int>(m,n));
		matrix<int> b(MATRIX::random<int>(n,o));

		// a.print("A");
		// b.print("B");

		int start_s=clock();

		matrix<int> d=MATRIX::SimpleProduct(a,b);

		int stop_s=clock();

		double tsimple=(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;

		// std::cout<<"Simple Product Evaluated in "<<t<<" ms\n\n";

		start_s=clock();

		matrix<int> c=a*b;

		stop_s=clock();

		double tstrassen=(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;

		// std::cout<<"Strassen Product Evaluated in "<<t<<" ms\n\n";
		
		// c.print("C");
		// d.print("D");

		std::cout<<"Matrix Dimensions : "<<m<<"x"<<n<<" and "<<n<<"x"<<o<<" | "<<tstrassen/tsimple<<std::endl;;

		if(!(c==d)){
			std::cout<<"FUCK."<<std::endl;	
			return 0;
		}

	}

}
