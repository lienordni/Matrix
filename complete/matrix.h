template <class T>
class matrix {

private:
	T **A;

	int rows;
	int cols;

	int row0;
	int col0;

	int maxrows;
	int maxcols;

	// T** AllocateSpace(int,int);

public:
	
	matrix();
	matrix(int, int);
	matrix(T**,int,int); 
	matrix(T**,int,int,int,int);
	matrix(const matrix &);
	~matrix();

	void SetDimensions(int,int);
	void SetMaxDimensions(int,int);

	matrix<T> submatrix(int,int);
	matrix<T> submatrix(int,int,int,int);

	void input();

	int GetRowCount() const;
	int GetColumnCount() const;
	int GetMaxRowCount() const;
	int GetMaxColumnCount() const;
	T** GetMatrix() const;
	int GetRowZero() const;
	int GetColZero() const;

	T& element(int m, int n);

	void print(std::string);
	void printdetails(std::string);

	void operator=(matrix<T>);
	bool operator==(matrix<T>); // NOT DEFINED YET.

	matrix<T> operator-();

	matrix<T> operator+(matrix<T>);
	matrix<T> operator-(matrix<T>);
	matrix<T> operator*(matrix<T>);

};

template <class T>
T zero=T(0);

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

template <class T>
matrix<T>::matrix() {
	rows=0;
	cols=0;
	row0=0;
	col0=0;
	maxrows=0;
	maxcols=0;
}

template <class T>
matrix<T>::matrix(int m, int n){
	A=MATRIX::AllocateSpace<T>(m,n);
	rows=m;
	cols=n;
	row0=0;
	col0=0;
	maxrows=m;
	maxcols=n;
}

template <class T>
matrix<T>::matrix(T** V, int m, int n) {
	A=V;
	rows=m;
	cols=n;
	row0=0;
	col0=0;
	maxrows=m;
	maxcols=n;
}


template <class T>
matrix<T>::matrix(T** V, int u, int v, int m, int n) {
	A=V;
	rows=m;
	cols=n;
	row0=u;
	col0=v;
	maxrows=m;
	maxcols=n;
}

template <class T>
matrix<T>::matrix(const matrix &x){
	rows=x.GetRowCount();
	cols=x.GetColumnCount();
	A=x.GetMatrix();
	row0=x.GetRowZero();
	col0=x.GetColZero();
	maxrows=x.GetMaxRowCount();
	maxcols=x.GetMaxColumnCount();
}

template <class T>
void matrix<T>::SetDimensions(int rm, int rn){
	rows=rm;
	cols=rn;
}

template <class T>
void matrix<T>::SetMaxDimensions(int rm, int rn){
	maxrows=rm;
	maxcols=rn;
}

template <class T>
matrix<T> matrix<T>::submatrix(int m, int n){
	matrix<T> sub(A,row0,col0,m,n);
	sub.SetMaxDimensions(row0+rows,col0+cols);
	return sub;
}

template <class T>
matrix<T> matrix<T>::submatrix(int u, int v, int m, int n){
	matrix<T> sub(A,row0+u,col0+v,m,n);
	sub.SetMaxDimensions(MATRIX::min(maxrows,row0+rows),MATRIX::min(maxcols,col0+cols));
	return sub;	
}

template <class T>
matrix<T>::~matrix() {
	// std::cout<<"Peace out, lien."<<std::endl;
}

template <class T>
void matrix<T>::input() {
	std::cout<<"Enter no. of rows : ";
	std::cin>>rows;
	std::cout<<"Enter no. of columns : ";
	std::cin>>cols;

	A=MATRIX::AllocateSpace<T>(rows,cols);

	std::cout<<"Enter elements : "<<std::endl;
	// ADD CHECK HERE	
	int i,j;
	T var;
	for(i=0;i<rows;++i) {
		for(j=0;j<cols;++j) {
			std::cin>>var; // ADD CHECK HERE
			A[i][j]=var;
		}
	}

	row0=0;
	col0=0;
	maxrows=rows;
	maxcols=cols;

	return;
}

template <class T>
void matrix<T>::print(std::string s) {
	
	int i,j;

	int maxsize=0;
	int size,k;

	std::cout<<s<<" = ";


	for(i=0;i<rows;++i)
		for(j=0;j<cols;++j)
			if((MATRIX::length(element(i,j)))>maxsize)
				maxsize=(MATRIX::length(element(i,j)));

	for(i=0;i<rows;++i) {
		if(i>0)
			for(k=0;k<s.size()+3;++k)
				std::cout<<" ";
		std::cout<<"[ ";
		for(j=0;j<cols;++j) {
			size=(MATRIX::length(element(i,j)));
			for(k=size;k<maxsize;++k)
				std::cout<<" ";
			std::cout<<(this->element(i,j))<<" ";
		}
		std::cout<<"]"<<std::endl;
	}		

	std::cout<<std::endl;
	return;
}

template <class T>
void matrix<T>::printdetails(std::string s) {
	std::cout<<"Details of "<<s<<" ...."<<std::endl;
	std::cout<<"Rows = "<<rows<<std::endl;
	std::cout<<"Cols = "<<cols<<std::endl;
	std::cout<<"Row0 = "<<row0<<std::endl;
	std::cout<<"Col0 = "<<col0<<std::endl;
	std::cout<<"Max Rows = "<<maxrows<<std::endl;
	std::cout<<"Max Cols = "<<maxcols<<std::endl;
	std::cout<<std::endl;
}

template <class T>
T** matrix<T>::GetMatrix() const{
	return A;
}

template <class T>
int matrix<T>::GetRowCount() const{
	return rows;
}

template <class T>
int matrix<T>::GetColumnCount() const{
	return cols;
}

template <class T>
int matrix<T>::GetMaxRowCount() const{
	return maxrows;
}

template <class T>
int matrix<T>::GetMaxColumnCount() const{
	return maxcols;
}

template <class T>
int matrix<T>::GetRowZero() const{
	return row0;
}

template <class T>
int matrix<T>::GetColZero() const{
	return col0;
}

template <class T>
T& matrix<T>::element(int m, int n) {
	if(m<0 || n<0 || row0+m>=maxrows || col0+n>=maxcols){
		return zero<T>;
	}
	return A[m+row0][n+col0];
}

template <class T>
void matrix<T>::operator=(matrix<T> x) {

	rows=x.GetRowCount();
	cols=x.GetColumnCount();
	A=x.GetMatrix();
	row0=x.GetRowZero();
	col0=x.GetColZero();
	maxrows=x.GetMaxRowCount();
	maxcols=x.GetMaxColumnCount();
}

template <class T>
bool matrix<T>::operator==(matrix<T> x) {
	if(rows!=x.GetRowCount() || cols!=x.GetColumnCount())
		return false;

	int i,j;

	for(i=0;i<rows;++i)
		for(j=0;j<cols;++j)
			if(element(i,j)!=x.element(i,j))
				return false;
	return true;
}

template <class T>
matrix<T> matrix<T>::operator-() {
	matrix<T> blah(rows,cols);
	int i,j;
	for(i=0;i<rows;++i)
		for(j=0;j<cols;++j){
			blah.element(i,j)=-(element(i,j));
		}

	return blah;
}

template <class T>
matrix<T> matrix<T>::operator+(matrix<T> x) {
	if(cols!=x.GetColumnCount() || rows!=x.GetRowCount()){
		std::cout<<"Fuck Off Bitch!!"<<std::endl;
		throw std::invalid_argument("Matrix dimensions not appropriate for addition");
	}

	int i,j;

	matrix<T> sum(rows,cols);

	for(i=0;i<rows;++i)
		for(j=0;j<cols;++j)
			sum.element(i,j)=element(i,j)+x.element(i,j);

	return sum;
}

template <class T>
matrix<T> matrix<T>::operator-(matrix<T> x) {
	return (*this)+(-x);
}

template <class T>
matrix<T> matrix<T>::operator*(matrix<T> x) {
	if(cols!=x.GetRowCount()){
		std::cout<<"Fuck Off Bitch!!!"<<std::endl;
		throw std::invalid_argument("Matrix dimensions not appropriate for multiplication");
	}
	return MATRIX::StrassenProduct<T>(*this,x);
}
