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
