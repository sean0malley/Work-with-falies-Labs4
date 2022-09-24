#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <limits>
using namespace std;

// Структару точки
struct Point
{
	int Id;            // Идентификатор
	double X, Y, Z, T, D;  // Координаты, температура, перемещение
};

// Структура списка точек за конкретное время
struct TimePoint
{
	double t;          // Время
	vector<Point> P;   // Список точек
};


// Функция загрузки данных из файлов в вектор структур TimePoint
void LoadData(vector<TimePoint>& Data)
{
	Data.clear();
	// Загрузка данных из файла BD.txt
	ifstream F1("BD.txt");
	string S;
	getline(F1, S);  // Пропуск строки заголовка
	while (1)        // Построчная загрузка
	{
		double t;
		Point P;
		F1 >> t >> P.Id >> P.T >> P.D;  // Чтение данных
		if (!F1) break;
		if (Data.size() == 0 || Data.back().t < t) // Если время увеличилось
		{
			TimePoint TP;  // Создать новый вектор точек
			TP.t = t;
			Data.push_back(TP);    // И добавить его в вектор данных
		}
		Data.back().P.push_back(P);  // Добавление точки в список
	}
	F1.close();
	// Загрузка данных из файла BD_Coords.txt
	ifstream F2("BD_Coords.txt");
	getline(F2, S);  // Пропуск строки заголовка
	while (1)        // Построчная загрузка
	{
		int Id;
		double X, Y, Z;
		F2 >> Id >> X >> Y >> Z;   // Чтение данных
		if (!F2) break;
		// Проход по всем временам для данной точки
		for (auto it = Data.begin(); it != Data.end(); it++)
		{
			it->P[Id - 1].X = X;  // Запись координат
			it->P[Id - 1].Y = Y;
			it->P[Id - 1].Z = Z;
		}
	}
	F2.close();
}

// Функция сохранения всех данных в общий файл BD_Total.txt
void SaveData(vector<TimePoint>& Data)
{
	ofstream F("BD_Total.txt");
	F << "Time\tPoint ID\tX\tY\tZ\tTemperature\tDisplacement X" << endl;   // Заголовок
	for (auto it = Data.begin(); it != Data.end(); it++)         // Проход по временам
		for (auto itt = it->P.begin(); itt != it->P.end(); itt++)   // Проход по точкам каждого времени
			F << it->t << "\t" << itt->Id << "\t\t" << itt->X << "\t" << itt->Y << "\t" << itt->Z << "\t" << itt->T << "\t\t" << itt->D << endl;  // Запись данных
	F.close();
}

// Функция поиска точки по заданному времени и координатам
// Возвращается указатель на БЛИЖАЙШУЮ точку
// Сначала ищется ближайшее время, а затем точка с минимальным расстоянием до заданной
Point* SearchPoint(vector<TimePoint>& Data, double& t, double X, double Y, double Z)
{
	// Поиск ближайшего времени
	double emin = numeric_limits<double>::max();
	auto it = Data.begin();
	for (; it != Data.end(); it++)   // Проход по временам
	{
		double eps = fabs(it->t - t);  // Расчёт погрешности
		if (eps < emin) emin = eps;     // Обновление мининмума погрешности
		else
		{
			it--;   // Погрешность увеличилась - вернуться к предыдущей точке
			break;  // И закончить перебор
		}
	}
	t = it->t;  // Возврат ближайшего времени
	// Поиск ближайшей точки
	emin = numeric_limits<double>::max();
	auto itt = it->P.begin();
	auto minR = itt;
	for (; itt != it->P.end(); itt++)  // Проход по точкам
	{
		double dx = itt->X - X;  // Вычисление расстояния до заданной точки
		double dy = itt->Y - Y;
		double dz = itt->Z - Z;
		double R = sqrt(dx * dx + dy * dy + dz * dz);
		if (R < emin)  // Обновление минимума
		{
			emin = R;
			minR = itt;
		}
	}
	Point* P = &(*minR);  // Формирование результата (указателя на точку)
	return P;
}

// Функция выборки всех точек со временем, ближайшем к t
// И записи её в файл Selection.txt
void Selection(vector<TimePoint>& Data, double t)
{
	// Поиск ближайшего времени (аналогично таковому в функции SearchPoint
	double emin = numeric_limits<double>::max();
	auto it = Data.begin();
	for (; it != Data.end(); it++)
	{
		double eps = fabs(it->t - t);
		if (eps < emin) emin = eps;
		else
		{
			it--;
			break;
		}
	}
	// Запись выборки в файл
	ofstream F("Selection.txt");
	F << "Time=" << t << endl;  // Запись условия выборки (времени)
	F << "X\tY\tZ\tTemperature\tDisplacement X" << endl;    // Заголовок
	for (auto itt = it->P.begin(); itt != it->P.end(); itt++)  // Форматированная запись точек
	{
		F.setf(ios::fixed);
		F.precision(4);
		F << itt->X << "\t" << itt->Y << "\t" << itt->Z << "\t";
		F.precision(2);
		F << itt->T << "\t\t";
		F.unsetf(ios::fixed);
		F.setf(ios::scientific);
		F.precision(2);
		F << itt->D << endl;
		F.unsetf(ios::scientific);
	}
	F.close();
}

int main()
{
	setlocale(LC_ALL, "");    // Локализация консоли
	vector<TimePoint> Data;  // Вектор данных
	cout << "Данные загружаются...";
	LoadData(Data);    // Загрузка данных из файлов
	SaveData(Data);    // Сохранение полных данных в файл
	cout << endl << endl;
	// Поиск точки по времени и координатам
	cout << "Вывод данных о точке, ближайшей к заданной" << endl;
	double t, X, Y, Z;
	cout << "t="; cin >> t;
	cout << "X="; cin >> X;
	cout << "Y="; cin >> Y;
	cout << "Z="; cin >> Z;
	Point* P = SearchPoint(Data, t, X, Y, Z);
	cout << "Time\tPoint ID\tX\tY\tZ\tTemperature\tDisplacement X" << endl;
	cout << t << "\t" << P->Id << "\t\t" << P->X << "\t" << P->Y << "\t" << P->Z << "\t" << P->T << "\t\t" << P->D << endl;
	// Формирование выборки по времени
	cout << endl << "Информация о температуре и перемещению в ближайший к заданному момент времени" << endl;
	cout << "t="; cin >> t;
	Selection(Data, t);
	cout << "Файл Selection.txt сгенерирован" << endl;

	system("pause");
	return 0;
}
