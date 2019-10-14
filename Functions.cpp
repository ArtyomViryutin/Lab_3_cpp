#include "Header.h"

// Функция CreateDataBase создает структурированную базу данных из начальной базы данных их файла ItitialData.csv и устанавливает разделители
int CreateDataBase()
{
	ifstream FileIn; // Объект для обравотки файла(файловый ввод)
	ofstream FileOut; // Объект для обработки файла(файловый вывод)
	string FIO[6000]; // Вспомогательные массивы строк для чтения данных из файла InitialDataBase.csv
	string dep[16];
	string rank[5];
	string degree[4];
	FileIn.open("InitialData.csv", ios_base::in); // Открываем файла InitialData.csv для чтения
	if (!FileIn.is_open()) // Проверяем существования файла, если его нет, то возвращаем -1 и дальше выходим из программы в функции ClassInitialization
	{
		cout << "Невозможно создать базу данных.Отсутствует файл с начальными данными InitialData.csv." << endl; // Сообщение о ошибке
		return -1;
	}

	
	for (int i = 0; i < 6000; i++) { // Считывем 6000 заранее сгенерированных ФИО в массив FIO
		getline(FileIn, FIO[i], '\n');
	}
	for (int i = 0; i < 16; i++) // Считывем 16 заранее заготовленных кафедр НИУ ВШЭ в массив dep
		getline(FileIn, dep[i], '\n');
	for (int i = 0; i < 5; i++) // Считывем 5 заранее заготовленных учёных званий в массив rank
		getline(FileIn, rank[i], '\n');
	for (int i = 0; i < 4; i++) // Считывем 5 заранее заготовленных учёных степеней в массив degree
		getline(FileIn, degree[i], '\n');
	FileIn.close(); // Закрываем файл 

	FileOut.open("DataBase.csv", ios_base::out); // Открываем файл DataBase.csv для записи.В этом файле в дальнейшем и будет весь датасет
	FileOut << "ФИО;" << "Кафедра;" << "Учёное звание;" << "Учёная степень\n"; // Записываем названия столбцов
	for (int i = 0; i < 6000; i++) // Заполняем столбцы данными из массива и ставим разделители для корректного отображения в csv файле,а так же '\n' для разделение объектов на строки в файле
	{
		FileOut << FIO[i] + ';';
		FileOut << dep[rand() % 16] + ';'; // Генерируем рандомные числа функцией rand() и делим с остатком на кол-во элементов в массиве для получение чисел в диапазоне от 0 до кол-ва элементов в массиве
		FileOut << rank[rand() % 5] + ';';
		FileOut << degree[rand() % 4] + '\n';
	}
	FileOut.close(); // Закрываем файл
	return 0;
}
// Функция InputM осуществляет ввод переменной оператора выбора switch и проверяет корректность ввода. В случае некорректного ввод повторяется
int InputM()
{
	int n;
	while (!(std::cin >> n) or n != 1 and n != 2 and n != 3 and n != 0 or getchar() != '\n') {
		cout << "Такого действия не существует.Попробуйте ввести еще раз: ";// При некорректном вводе
		cin.clear(); // Очищаем поток
		cin.ignore(10000, '\n'); // Пропускаем все символы до символа новой строки
	}
	return n;
}
// Функция InputN осуществляет ввод числа , определяющего кол-во объектов сортировки(от 1 до 6000) и в случае некорректного ввод повторяется
int InputN()
{
	int n;
	while (!(std::cin >> n) or n < 0 or n > 6000 or getchar() != '\n') {
		cout << "Некорректный ввод.Вы должны вводить только целые числа от 1 до 6000.Попробуйте еще раз: "; // При некорректном вводе
		cin.clear(); // Очищаем поток
		cin.ignore(10000, '\n'); // Пропускаем все символы до символа новой строки
	}
	return n;
}
// Функция ClassInitialization инициализирует массив объектов данными из файла DataBase.csv, в качестве аргументов принимется указатель на массив объектов и количество элементов в нем
int ClassInitialization(Teachers *obj, int N)
{
	ifstream MyFile; // Объект для обравотки файла(файловый ввод)
	string temp; // Временная переменная для чтения строки названий столбцов
	MyFile.open("DataBase.csv", ios_base::in); // Открываем файл для чтения
	if (!MyFile.is_open()) // Проверка существования файла DataBase.csv
	{
		cout << "Файл с базой данных DataBase.csv не был найден, поэтому он будет создан и заполнен данными из файла InitialData.csv." << endl;
		if (CreateDataBase() == -1) { // Заполнение DataBase.csv начальными данными из файла InitialData.csv и в случае если файл InitialData.csv отсутсвует выполняется выход из программы
			delete[] obj; // Перед выходом очищаем массив объектов
			system("pause");
			exit(0);
		}
	}

	getline(MyFile, temp, '\n'); // Считываем строку названий столбцов
	for (int i = 0; i < N; i++) {
		getline(MyFile, obj[i].FIO, ';'); // Считываем последовательно ячейки csv файла(для это и ставились разделители ';')
		getline(MyFile, obj[i].department, ';');
		getline(MyFile, obj[i].rank, ';');
		getline(MyFile, obj[i].degree, '\n');
	}
	MyFile.close(); // Закрываем файл
	return 0;
}

// Перегрузка оператор больше > , в качестве аргументов принимаются ссылки на два объекта
bool operator>(Teachers &a, Teachers &b)
{	// Сравниваем ФИО двух объектов
	if (a.FIO == b.FIO) // Если ФИО равны, то сравниваем названия кафедр
	{
		if (a.department > b.department)
			return true; // В случае если название кафедры первого объекта лексические больше второго возвращаем true, иначе false
		else
			return false;
	}
	else
	{
		if (a.FIO > b.FIO) // Если ФИО объектов не равны, то сравниваем их и в случае если ФИО первого объекта лексически больше второго возвращаем true, иначе false
			return true;
		else
			return false;
	}
}
// Функция BubbleSorting осуществляет сортировку пузырьком, в качестве аргументов принимается указатель массив объектов и количество элементов в массиве
void BubbleSorting(Teachers *obj, int N) 
{
	Teachers temp; // Временная переменная для обмена элементов местами
	for (int i = 1; i < N; i++) { // Делаем N итераций для постановки каждого элемента на свое место
		for (int j = 0; j < N - i; j++) { // Проходим по N элементам, при каждой итерации наибольший из N - i элементов встает в конец
			if (obj[j] > obj[j + 1]) { // Если j-ый элемент больше (j + 1)-ого меняем их местами
				temp = obj[j];
				obj[j] = obj[j + 1];
				obj[j + 1] = temp;
			}
		}
	}
}
// Функция QuickSorting осуществляет быструю сортировку, в качестве аргументов принимается указатель массив объектов, номер первого элемента массива и номер последнего элемента
void QuickSorting(Teachers *obj, int first, int last)
{
	if (first < last) 
	{
		int left = first, right = last;
		string middle = obj[(left + right) / 2].FIO; // Записываем в переменную middle центральный элемент массива
		do // Цикл перемещения элементов, который больше центрального в одну часть массива и которые меньше в другую
		{
			while (middle > obj[left].FIO) left++; // Поиск индекса left элемента который будет больше чем центральный
			while (obj[right].FIO > middle) right--; // Поиск индекса right элемента который будет меньше чем центральный
			if (left <= right) // При нахождении таких элементов элементов меняем их местами и переходим к следующим элементам
			{
				string temp = obj[left].FIO; // Временная переменная temp для обмена элементов
				obj[left].FIO = obj[right].FIO;
				obj[right].FIO = temp;
				left++; // Увеличиваем индекс left на 1
				right--; // Уменьшаем индекс right на 1
			}
		} while (left <= right); // Для каждоый из частей вызываем рекурсивную функцию для дальнейшей сортировки
		QuickSorting(obj, first, right);
		QuickSorting(obj, left, last);
	}
}
// Создаем новый файл с отсортированными данными, в качестве аргументов принимается указатель на массив объектов и количество элементов в массиве
void CreateNewFile(Teachers *obj, int N) 
{
	ofstream NewFile; // Объект для обработки файла(файловый вывод)
	string filename; // Переменная для ввода имени файла
	cout << "Введите имя нового файла: ";
	getline(cin, filename); // Ввод имени файла
	while (filename == "\0") { // Обработка при пустом вводе
		cout << "Название файла не может быть пустым.Попробуйте еще раз" << endl;
		cout << "Введите имя нового файла: ";
		getline(cin, filename); // Ввод имени файла
	}

	filename += ".csv"; // Добавляем в имя файла .csv для создания файла типа csv
	NewFile.open(filename, ios_base::out); // Создаем(открываем файл, если он уже существует) для записи
	NewFile << "ФИО;" << "Кафедра;" << "Учёное звание;" << "Учёная степень\n"; // Вводим названия столбцов
	for (int i = 0; i < N; i++) // Заполняем столбцы данными из сортированного массива и ставим разделители для корректного отображения в csv файле,а так же '\n' для разделение объектов на строки в файле
	{
		NewFile << obj[i].FIO + ';';
		NewFile << obj[i].department + ';';
		NewFile << obj[i].rank + ';';
		NewFile << obj[i].degree + '\n';
	}
	cout << "Файл был создан" << endl; // Вывод надписи об окончании создании файла
	NewFile.close(); // Закрываем файл
}
// Функция FunctionsCall вызывает другие функции в зависимоти от сортировки и необходимости создания файлаю.В качестве первого аргумента принимает число объектов для сортировки
// В зависимости от аргумента TrueForBubble либо производит сортировку пузырьком, либо быструю сортировку
// А также, в зависимоти от аргумента TrueForNewFile либо создает новый файл с ортcортированными данными, либо нет
double FunctionsCall(int N, bool TrueForBubble, bool TrueForNewFile) 
{
	Teachers *ForBubbleSorting = NULL, *ForQuickSorting = NULL; // Указатели типа Teachers для создания массивов объектов для дальнейшей сортировки
	double StartTime, EndTime;  // Переменные, определяющие длительность сортировки
	if (TrueForBubble)
	{
		ForBubbleSorting = new Teachers[N]; // Выделяем память для массива сортировки пузырьком
		ClassInitialization(ForBubbleSorting, N); // Инициализируем массив объектов для сортировки пузырьком данными из файла DataBase.csv
		StartTime = clock(); // В переменную StartTime записываем время, пройденное с начала запуска прогрыммы
		BubbleSorting(ForBubbleSorting, N); // Сортируем массив пузырьком
		EndTime = clock(); // В переменную EndTime записываем время, вройденное с начала запуска программы
		if (TrueForNewFile)
			CreateNewFile(ForBubbleSorting, N);

	}
	else
	{
		ForQuickSorting = new Teachers[N]; // Выделяем память для массива быстрой сортировки
		ClassInitialization(ForQuickSorting, N);  // Инициализируем массив объектов для быстрой сортировки данными из файла DataBase.csv
		StartTime = clock(); // В переменную StartTime записываем время, пройденное с начала запуска прогрыммы
		QuickSorting(ForQuickSorting, 0, N - 1); // Сортируем массив быстрой сортировкой
		EndTime = clock();// В переменную EndTime записываем время, вройденное с начала запуска программы
		if (TrueForNewFile)
			CreateNewFile(ForQuickSorting, N);
	}


	delete[] ForBubbleSorting; // Очистка массивов
	delete[] ForQuickSorting;
	return (EndTime - StartTime) / CLK_TCK; // Возвращаем время сортировки в секундах, для этого ищем разность времен пройденных с начала запуска программы до и после сортировки и делим на макрос CLK_TCK
}
