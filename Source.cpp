#include <iostream>
#include <fstream>

using namespace std;


template< class T >
void selectSort(T* arr, int size);

template< class T >
void shellSort(T* arr, int size);

struct WORKER
{
	char name[15];
	char position[15];
	char number[15];
	int salary;
};

int main()
{
	int check;
	setlocale(LC_ALL, "Rus");
	system("color F0");

	const int NUM = 12;

	WORKER* arr[NUM];

	FILE* ZName;
	fopen_s(&ZName, "D:\\213\\universe\\ОАИП\\лаба 12\\Project1\\Project1\\members.txt", "r+b");

	for (int i = 0; i < NUM; i++)
	{
		arr[i] = new WORKER;
	}

	for (int i = 0; i < NUM; i++)
	{
		fread(arr[i], sizeof(*arr[i]), 1, ZName);
	}

	cout << "Что будем сортировать?\n 1)Salary\n 2)Job" << endl;
	cin >> check;

	if (check == 1)
	{
		selectSort(arr, NUM);
	}
	else if (check == 2)
	{
		shellSort(arr, NUM);
	}
	else
	{
		cout << "Error";
	}

	for (int i = 0; i < NUM; i++)
	{
		cout << "Name: " << arr[i]->name << endl;
		cout << "Job: " << arr[i]->position << endl;
		cout << "Phone number: " << arr[i]->number << endl;
		cout << "Salary: " << arr[i]->salary << endl;
		cout << endl;
	}

	for (int i = 0; i < 10; i++)
	{
		delete[] arr[i];
	}

	fclose(ZName);


	system("Pause");
	return 0;
}

template< class T >
void selectSort(T *arr, int size)
{
	int tmp_salary;
	T tmp;
	for (int i = 0; i < size; i++) // i - номер текущего шага
	{
		int pos = i;
		tmp = arr[i];
		tmp_salary = tmp->salary;
		for (int j = i + 1; j < size; j++) // цикл выбора наименьшего элемента
		{
			if (arr[j]->salary > tmp_salary)
			{
				pos = j;
				tmp = arr[j];
				tmp_salary = tmp->salary;
			}
		}
		arr[pos] = arr[i];
		arr[i] = tmp; // меняем местами наименьший с a[i]
	}
}

int increment(int inc[], int size)
{
	int p1, p2, p3, s;
	p1 = p2 = p3 = 1;
	s = -1;
	do
	{
		if (++s % 2)
		{
			inc[s] = 8 * p1 - 6 * p2 + 1;
		}
		else
		{
			inc[s] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 2;
		}
		p1 *= 2;
	} while (3 * inc[s] < size);

	return s > 0 ? --s : 0;
}


template< class T >
void shellSort(T *arr, int size)
{
	int inc, i, j, seq[40];
	int s;

	s = increment(seq, size); // вычисление последовательности приращений
	while (s >= 0)  // сортировка вставками с инкрементами inc[] 
	{
		inc = seq[s--];
		for (i = inc; i < size; i++)
		{
			T temp = arr[i];
			for (j = i; (j >= inc) && (strcmp(temp->position, arr[j - inc]->position) < 0); j -= inc) 
			{
				arr[j] = arr[j - inc];
			}
			arr[j] = temp;
		}
	}
}

//Сортировка Выбор
//Находим номер минимального значения в текущем списке
//Производим обмен этого значения со значением первой неотсоррованной позиции
//Cортируем хвост списка, исключив из рассмотрения уже отсортированные элементы
//Время работы сортировки n^2

//Сортировка Шелла
//Является усовершенствованной сортировкой вставок, пробегает не все элементы подряд, а через указанный шаг d
//Шаг начинается от самого большого и с каждым разом уменьшается, доходя до d = 1
//Cреднее время работы зависит от промежутков, предложенная Шеллом система работает за n^2, однако после были предложены
//более рациональные варианты редложенная Седжвиком последовательность: 
//8 * p1 - 6 * p2 + 1 если і четное и inc[s] = 9 * p1 - 9 * p3 + 1 нечетное , 
//При использовании таких приращений средняя сложность алгоритма составляет n^7/6, в худшем случае n^4/3, в лучшем n*(logn)^2
