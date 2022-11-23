#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;
class TMatrix
{
protected:
	int rows, cols;
	double **M;
public:
	TMatrix()
	{
		rows = 0;
		cols = 0;
		M = NULL;
	}
	~TMatrix();					//Деструктор
	virtual void Show()=0;
	friend void fill(TMatrix &p);
};

void fill(TMatrix &p)
{
	for (int i = 0; i < p.rows; i++)
	{
		for (int j = 0; j < p.cols; j++)		//Инициализация матрицы случайными значениями
		{
			p.M[i][j] = double(rand() % 100) - 50.0;
		}
	}

}
//Деструктор
TMatrix::~TMatrix()
{
	if (M)
	{
		for (int i = 0; i<rows; i++)
			delete M[i];	//Освобождение выделенной памяти
		delete M;
	}
}
class Matrix: public TMatrix
{
public:
	Matrix() :TMatrix() {};
	Matrix(int n, int m);
	void Show();
	Matrix(const Matrix &m);	//Копирующий конструктор
	Matrix operator+(Matrix op2);	//Перегрузка операции сложения
	Matrix operator-(Matrix op2);	//Перегрузка операции умножения
	Matrix operator*(Matrix op2);	//Перегрузка операции умножения
	Matrix operator=(Matrix op2);		//Перегрузка операции присваивания

};
Matrix Matrix::operator=(Matrix op2)		//Перегрузка операции присваивания
{
	if (rows != op2.rows || cols != op2.cols)
	{
		if (M)
		{
			for (int i = 0; i<rows; i++)
				delete M[i];	//Освобождение выделенной памяти
			delete M;
		}
		rows = op2.rows;
		cols = op2.cols;
		M = new double*[rows];				//Динамическое выделение памяти под матрицу
		for (int i = 0; i < rows; i++)
			M[i] = new double[cols];
	}
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			M[i][j] = op2.M[i][j];			//Поэлементная замена матрицы в текущем объекте
		}
	}
	return *this;							//Возвращается модифицированный объект

}
//Перегрузка операции сложения
Matrix Matrix::operator+(Matrix op2)
{
	Matrix r(rows, cols);	//Результат
	if (rows != op2.rows || cols != op2.cols)
		throw "Недопустимые размеры матриц.";
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			r.M[i][j] = M[i][j] + op2.M[i][j];	//Поэлементное сложение матриц
		}
	}
	return r;
}
//Перегрузка операции вычитания
Matrix Matrix::operator-(Matrix op2)
{
	Matrix r(rows, cols);	//Результат
	if (rows != op2.rows || cols != op2.cols)
		throw "Недопустимые размеры матриц.";
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			r.M[i][j] = M[i][j] - op2.M[i][j];	//Поэлементное сложение матриц
		}
	}
	return r;
}
//Перегрузка операции умножения
Matrix Matrix::operator*(Matrix op2)
{
	if (cols != op2.rows)
		throw "Недопустимые размеры матриц.";
	Matrix r(rows, op2.cols);	//Результат
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<op2.cols; j++)
		{

			r.M[i][j] = 0;	//Поэлементное сложение матриц
			for (int k = 0; k<cols; k++)
				r.M[i][j] += M[i][k] * op2.M[k][j];
		}
	}
	return r;
}
//Отобразить матрицу
void Matrix::Show()
{
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			cout.width(10);
			cout.precision(4);
			cout << M[i][j];
		}
		cout << endl;
	}
}
//Копирующий конструктор
Matrix::Matrix(const Matrix &m)
{
	rows = m.rows;
	cols = m.cols;
	M = new double*[rows];		//Динамическое выделение памяти под матрицу
	for (int i = 0; i<rows; i++)
	{
		M[i] = new double[cols];
		for (int j = 0; j<cols; j++)	//Копирование матрицы из исходного экземпляра
		{
			M[i][j] = m.M[i][j];
		}
	}
}
Matrix::Matrix(int n, int m)
{
	rows = n;
	cols = m;
	M = new double*[rows];				//Динамическое выделение памяти под матрицу
	for (int i = 0; i < rows; i++)
	{
		M[i] = new double[cols];
	}
}


class SquareMatrix : public TMatrix
{
public:
	SquareMatrix() :TMatrix() {};
	SquareMatrix(int n);
	void Show();
	SquareMatrix(const SquareMatrix &m);	//Копирующий конструктор
	SquareMatrix operator+(SquareMatrix op2);	//Перегрузка операции сложения
	SquareMatrix operator-(SquareMatrix op2);	//Перегрузка операции умножения
	SquareMatrix operator*(SquareMatrix op2);	//Перегрузка операции умножения
	SquareMatrix operator=(SquareMatrix op2);		//Перегрузка операции присваивания
	double Determinant();	//определитель


};
SquareMatrix SquareMatrix::operator=(SquareMatrix op2)		//Перегрузка операции присваивания
{
	if (rows != op2.rows)
	{
		if (M)
		{
			for (int i = 0; i<rows; i++)
				delete M[i];	//Освобождение выделенной памяти
			delete M;
		}
		rows = op2.rows;
		M = new double*[rows];				//Динамическое выделение памяти под матрицу
		for (int i = 0; i < rows; i++)
			M[i] = new double[rows];
	}
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<rows; j++)
		{
			M[i][j] = op2.M[i][j];			//Поэлементная замена матрицы в текущем объекте
		}
	}
	return *this;							//Возвращается модифицированный объект

}
//Перегрузка операции сложения
SquareMatrix SquareMatrix::operator+(SquareMatrix op2)
{
	SquareMatrix r(rows);	//Результат
	if (rows != op2.rows)
		throw "Недопустимые размеры матриц.";
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<rows; j++)
		{
			r.M[i][j] = M[i][j] + op2.M[i][j];	//Поэлементное сложение матриц
		}
	}
	return r;
}
//Перегрузка операции вычитания
SquareMatrix SquareMatrix::operator-(SquareMatrix op2)
{
	SquareMatrix r(rows);	//Результат
	if (rows != op2.rows)
		throw "Недопустимые размеры матриц.";
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<rows; j++)
		{
			r.M[i][j] = M[i][j] - op2.M[i][j];	//Поэлементное сложение матриц
		}
	}
	return r;
}
//Перегрузка операции умножения
SquareMatrix SquareMatrix::operator*(SquareMatrix op2)
{
	if (rows != op2.rows)
		throw "Недопустимые размеры матриц.";
	SquareMatrix r(rows);	//Результат
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<op2.rows; j++)
		{

			r.M[i][j] = 0;	//Поэлементное сложение матриц
			for (int k = 0; k<rows; k++)
				r.M[i][j] += M[i][k] * op2.M[k][j];
		}
	}
	return r;
}
//Отобразить матрицу
void SquareMatrix::Show()
{
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<rows; j++)
		{
			cout.width(10);
			cout.precision(4);
			cout << M[i][j];
		}
		cout << endl;
	}
}
//Копирующий конструктор
SquareMatrix::SquareMatrix(const SquareMatrix &m)
{
	rows = m.rows;
	cols = rows;
	M = new double*[rows];		//Динамическое выделение памяти под матрицу
	for (int i = 0; i<rows; i++)
	{
		M[i] = new double[rows];
		for (int j = 0; j<cols; j++)	//Копирование матрицы из исходного экземпляра
		{
			M[i][j] = m.M[i][j];
		}
	}
}
SquareMatrix::SquareMatrix(int n)
{
	rows = n;
	cols = n;
	M = new double*[rows];				//Динамическое выделение памяти под матрицу
	for (int i = 0; i < rows; i++)
	{
		M[i] = new double[rows];
	}
}
double SquareMatrix::Determinant()
{
	const double EPS = 1E-9;
	double det = 1;
	for (int i = 0; i<rows; ++i) 
	{
		int k = i;
		for (int j = i + 1; j<rows; ++j)
			if (fabs(M[j][i]) > fabs(M[k][i]))
				k = j;
		if (fabs(M[k][i]) < EPS) 
		{
			det = 0;
			break;
		}
		swap(M[i], M[k]);
		if (i != k)
			det = -det;
		det *= M[i][i];
		for (int j = i + 1; j<rows; ++j)
			M[i][j] /= M[i][i];
		for (int j = 0; j<rows; ++j)
			if (j != i && fabs(M[j][i]) > EPS)
				for (int k = i + 1; k<rows; ++k)
					M[j][k] -= M[i][k] * M[j][i];
	}
	return det;
}

int main()
{
	setlocale(LC_ALL, "Russian");//русская локаль
	srand((unsigned)time(NULL));//инициализация генератора случайных чисел
	cout << "Прямоугольные матрицы" << endl;
	Matrix A(3, 4);
	fill(A);
	Matrix B(3,4);
	fill(B);
	Matrix C;
	cout << "A:" << endl;
	A.Show();
	cout << "B:" << endl;
	B.Show();
	cout << "A+B:" << endl;
	C = A + B;
	C.Show();
	C = A - B;
	cout << "A-B:" << endl;
	C.Show();
	Matrix D(4, 5);
	fill(D);
	Matrix E;
	E = A*D;
	cout << "A*D:" << endl;
	E.Show();


	cout << "Квадратные матрицы" << endl;
	SquareMatrix A1(3);
	fill(A1);
	SquareMatrix B1(3);
	fill(B1);
	SquareMatrix C1;
	cout << "A:" << endl;
	A1.Show();
	cout << "B:" << endl;
	B1.Show();
	cout << "A+B:" << endl;
	C1 = A1 + B1;
	C1.Show();
	C1 = A1 - B1;
	cout << "A-B:" << endl;
	C1.Show();
	SquareMatrix E1;
	E1 = A1*B1;
	cout << "A*B:" << endl;
	E1.Show();
	cout.precision(10);
	cout << "Det(A) = " << A1.Determinant() << endl;


	system("pause");
	return 0;
}