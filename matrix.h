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

#include "namespace.cpp"
#include "matrix.cpp"
