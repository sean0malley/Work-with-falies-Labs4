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
	~TMatrix();					//����������
	virtual void Show()=0;
	friend void fill(TMatrix &p);
};

void fill(TMatrix &p)
{
	for (int i = 0; i < p.rows; i++)
	{
		for (int j = 0; j < p.cols; j++)		//������������� ������� ���������� ����������
		{
			p.M[i][j] = double(rand() % 100) - 50.0;
		}
	}

}
//����������
TMatrix::~TMatrix()
{
	if (M)
	{
		for (int i = 0; i<rows; i++)
			delete M[i];	//������������ ���������� ������
		delete M;
	}
}
class Matrix: public TMatrix
{
public:
	Matrix() :TMatrix() {};
	Matrix(int n, int m);
	void Show();
	Matrix(const Matrix &m);	//���������� �����������
	Matrix operator+(Matrix op2);	//���������� �������� ��������
	Matrix operator-(Matrix op2);	//���������� �������� ���������
	Matrix operator*(Matrix op2);	//���������� �������� ���������
	Matrix operator=(Matrix op2);		//���������� �������� ������������

};
Matrix Matrix::operator=(Matrix op2)		//���������� �������� ������������
{
	if (rows != op2.rows || cols != op2.cols)
	{
		if (M)
		{
			for (int i = 0; i<rows; i++)
				delete M[i];	//������������ ���������� ������
			delete M;
		}
		rows = op2.rows;
		cols = op2.cols;
		M = new double*[rows];				//������������ ��������� ������ ��� �������
		for (int i = 0; i < rows; i++)
			M[i] = new double[cols];
	}
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			M[i][j] = op2.M[i][j];			//������������ ������ ������� � ������� �������
		}
	}
	return *this;							//������������ ���������������� ������

}
//���������� �������� ��������
Matrix Matrix::operator+(Matrix op2)
{
	Matrix r(rows, cols);	//���������
	if (rows != op2.rows || cols != op2.cols)
		throw "������������ ������� ������.";
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			r.M[i][j] = M[i][j] + op2.M[i][j];	//������������ �������� ������
		}
	}
	return r;
}
//���������� �������� ���������
Matrix Matrix::operator-(Matrix op2)
{
	Matrix r(rows, cols);	//���������
	if (rows != op2.rows || cols != op2.cols)
		throw "������������ ������� ������.";
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			r.M[i][j] = M[i][j] - op2.M[i][j];	//������������ �������� ������
		}
	}
	return r;
}
//���������� �������� ���������
Matrix Matrix::operator*(Matrix op2)
{
	if (cols != op2.rows)
		throw "������������ ������� ������.";
	Matrix r(rows, op2.cols);	//���������
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<op2.cols; j++)
		{

			r.M[i][j] = 0;	//������������ �������� ������
			for (int k = 0; k<cols; k++)
				r.M[i][j] += M[i][k] * op2.M[k][j];
		}
	}
	return r;
}
//���������� �������
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
//���������� �����������
Matrix::Matrix(const Matrix &m)
{
	rows = m.rows;
	cols = m.cols;
	M = new double*[rows];		//������������ ��������� ������ ��� �������
	for (int i = 0; i<rows; i++)
	{
		M[i] = new double[cols];
		for (int j = 0; j<cols; j++)	//����������� ������� �� ��������� ����������
		{
			M[i][j] = m.M[i][j];
		}
	}
}
Matrix::Matrix(int n, int m)
{
	rows = n;
	cols = m;
	M = new double*[rows];				//������������ ��������� ������ ��� �������
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
	SquareMatrix(const SquareMatrix &m);	//���������� �����������
	SquareMatrix operator+(SquareMatrix op2);	//���������� �������� ��������
	SquareMatrix operator-(SquareMatrix op2);	//���������� �������� ���������
	SquareMatrix operator*(SquareMatrix op2);	//���������� �������� ���������
	SquareMatrix operator=(SquareMatrix op2);		//���������� �������� ������������
	double Determinant();	//������������


};
SquareMatrix SquareMatrix::operator=(SquareMatrix op2)		//���������� �������� ������������
{
	if (rows != op2.rows)
	{
		if (M)
		{
			for (int i = 0; i<rows; i++)
				delete M[i];	//������������ ���������� ������
			delete M;
		}
		rows = op2.rows;
		M = new double*[rows];				//������������ ��������� ������ ��� �������
		for (int i = 0; i < rows; i++)
			M[i] = new double[rows];
	}
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<rows; j++)
		{
			M[i][j] = op2.M[i][j];			//������������ ������ ������� � ������� �������
		}
	}
	return *this;							//������������ ���������������� ������

}
//���������� �������� ��������
SquareMatrix SquareMatrix::operator+(SquareMatrix op2)
{
	SquareMatrix r(rows);	//���������
	if (rows != op2.rows)
		throw "������������ ������� ������.";
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<rows; j++)
		{
			r.M[i][j] = M[i][j] + op2.M[i][j];	//������������ �������� ������
		}
	}
	return r;
}
//���������� �������� ���������
SquareMatrix SquareMatrix::operator-(SquareMatrix op2)
{
	SquareMatrix r(rows);	//���������
	if (rows != op2.rows)
		throw "������������ ������� ������.";
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<rows; j++)
		{
			r.M[i][j] = M[i][j] - op2.M[i][j];	//������������ �������� ������
		}
	}
	return r;
}
//���������� �������� ���������
SquareMatrix SquareMatrix::operator*(SquareMatrix op2)
{
	if (rows != op2.rows)
		throw "������������ ������� ������.";
	SquareMatrix r(rows);	//���������
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<op2.rows; j++)
		{

			r.M[i][j] = 0;	//������������ �������� ������
			for (int k = 0; k<rows; k++)
				r.M[i][j] += M[i][k] * op2.M[k][j];
		}
	}
	return r;
}
//���������� �������
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
//���������� �����������
SquareMatrix::SquareMatrix(const SquareMatrix &m)
{
	rows = m.rows;
	cols = rows;
	M = new double*[rows];		//������������ ��������� ������ ��� �������
	for (int i = 0; i<rows; i++)
	{
		M[i] = new double[rows];
		for (int j = 0; j<cols; j++)	//����������� ������� �� ��������� ����������
		{
			M[i][j] = m.M[i][j];
		}
	}
}
SquareMatrix::SquareMatrix(int n)
{
	rows = n;
	cols = n;
	M = new double*[rows];				//������������ ��������� ������ ��� �������
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
	setlocale(LC_ALL, "Russian");//������� ������
	srand((unsigned)time(NULL));//������������� ���������� ��������� �����
	cout << "������������� �������" << endl;
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


	cout << "���������� �������" << endl;
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