namespace MATRIX {

	int min(int a, int b){
		return (a<b)?(a):(b);
	}

	int length(int x) {
		if(x<=0)
			return 1;
		return 1+floor(log10(x));
	}

	template <typename T>
	T** AllocateSpace(int m, int n) {
		T** K=new T*[m];
		for(int i=0;i<m;++i)
			K[i]=new T[n];	
		return K;
	}

	template <typename T>
	matrix<T> random(int m, int n) {
		matrix<T> r(m,n);
		int i,j;
		srand(time(NULL));
		for(i=0;i<m;++i)
			for(j=0;j<n;++j)
				r.element(i,j)=1+rand()%100;
		return r;
	}

	template <typename T>
	matrix<T> combine(matrix<T> a, matrix<T> b, matrix<T> c, matrix<T> d){
		int m=a.GetRowCount();
		int n=a.GetColumnCount();

		int i,j;

		matrix<T> final(2*m,2*n);

		for(i=0;i<m;++i)
			for(j=0;j<n;++j)
				final.element(i,j)=a.element(i,j);

		for(i=0;i<m;++i)
			for(j=0;j<n;++j)
				final.element(m+i,j)=c.element(i,j);

		for(i=0;i<m;++i)
			for(j=0;j<n;++j)
				final.element(i,n+j)=b.element(i,j);

		for(i=0;i<m;++i)
			for(j=0;j<n;++j)
				final.element(m+i,n+j)=d.element(i,j);

		return final;

	}

	template <typename T>
	matrix<T> SimpleProduct(matrix<T> a, matrix<T> b) {

		int m=a.GetRowCount();
		int n=a.GetColumnCount();
		int o=b.GetColumnCount();
		int i,j,k;
		T s;

		matrix<T> mat(m,o);

		for(i=0;i<m;++i) {
			for(j=0;j<o;++j) {
				s=zero<T>;

				for(k=0;k<n;++k)
					s+=a.element(i,k)*b.element(k,j);

				mat.element(i,j)=s;
			}	
		}

		return mat;
	}

	template <typename T>
	matrix<T> StrassenProduct(matrix<T> X, matrix<T> Y) {		
		int m=X.GetRowCount();
		int n=X.GetColumnCount();
		int o=Y.GetColumnCount();
		int i,j,k;

		if(m<=10 || n<=10 || o<=10)
			return SimpleProduct(X,Y);

		matrix<T> A11=X.submatrix(m%2+m/2,n%2+n/2);
		matrix<T> A12=X.submatrix(0,n%2+n/2,m%2+m/2,n%2+n/2);
		matrix<T> A21=X.submatrix(m%2+m/2,0,m%2+m/2,n%2+n/2);
		matrix<T> A22=X.submatrix(m%2+m/2,n%2+n/2,m%2+m/2,n%2+n/2);
		
		matrix<T> B11=Y.submatrix(n%2+n/2,o%2+o/2);
		matrix<T> B12=Y.submatrix(0,o%2+o/2,n%2+n/2,o%2+o/2);
		matrix<T> B21=Y.submatrix(n%2+n/2,0,n%2+n/2,o%2+o/2);
		matrix<T> B22=Y.submatrix(n%2+n/2,o%2+o/2,n%2+n/2,o%2+o/2);

		matrix<T> S1(B12-B22);
		matrix<T> S2(A11+A12);
		matrix<T> S3(A21+A22);
		matrix<T> S4(B21-B11);
		matrix<T> S5(A11+A22);
		matrix<T> S6(B11+B22);
		matrix<T> S7(A12-A22);
		matrix<T> S8(B21+B22);
		matrix<T> S9(A11-A21);
		matrix<T> S10(B11+B12);

		matrix<T> P1(StrassenProduct(A11,S1));
		matrix<T> P2(StrassenProduct(S2,B22));
		matrix<T> P3(StrassenProduct(S3,B11));
		matrix<T> P4(StrassenProduct(A22,S4));
		matrix<T> P5(StrassenProduct(S5,S6));
		matrix<T> P6(StrassenProduct(S7,S8));
		matrix<T> P7(StrassenProduct(S9,S10));

		matrix<T> C11(P5+P4-P2+P6);
		matrix<T> C12(P1+P2);
		matrix<T> C21(P3+P4);
		matrix<T> C22(P5+P1-P3-P7);

		matrix<T> z(combine(C11,C12,C21,C22));

		z.SetDimensions(m,o);
		return z;
	}

};