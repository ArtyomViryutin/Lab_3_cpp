
#include "Header.h" // Подключаем заголовочный файл


int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");


	int N = 1, M = 1; // Переменный для выбора количества объектов для сортировки и действия(оператор выбора switch)
	// Создание структурированной базы данных из данных файла InitialData.csv и при неуданом открытии файла выводит сообщение об ошибке и завершает программу
	while (M != 0) { // Пока M не 0
		cout << "Выберите действие:\n" << "1 - Сравнение времени сортировки пузырьком и быстрой сортировки\n" << "2 - Сортировка пузырьком и создание нового файла с отсортированными данными\n" << "3 - Быстрая сортировка и создание нового файла с отсортированными данными\n" << "0 - Выход\n" << "Ваш выбор: ";
		M = InputM(); // Ввод переменной для выбора действия
		switch (M) {
		case 1:
			while (true) { // Бесконечный цикл для сравнения длительности сортировок на данных различных размеров
				cout << "Введите количество объктов для сортировки (от 1 до 6000) или 0, чтобы закончить сравнение: ";
				N = InputN(); // Ввод количества объектов для сортировки
				if (N == 0) // Если N равна 0 выходим из бесконечного цикла
					break;
				cout << "Результат сортировки пузырьком: " << FunctionsCall(N, true, false) << " секунд" << endl; // Вывод разность EndTime и StartTime для определения дительности сортировки и делим на макрос CLK_TCK для получения секунд
				cout << "Результат быстрой сортировки : " << FunctionsCall(N, false, false) << " секунд" << endl; // Вывод разность EndTime и StartTime для определения дительности сортировки и делим на макрос CLK_TCK для получения секунд
			}
			break; // Окончание выполнение кейса
		case 2:
			cout << "Введите количество объктов для сортировки и записи в файл (от 1 до 6000) или 0, чтобы выйти в меню выбора: ";
			N = InputN(); 
			if (N == 0)
				break;
			cout << "Результат сортировки пузырьком : " << FunctionsCall(N, true, true) << " секунд" << endl;
			break; 
		case 3: // Следующие строки были описаны в case 1
			cout << "Введите количество объктов для сортировки и записи в файл (от 1 до 6000) или 0, чтобы выйти в меню выбора: ";
			N = InputN();
			if (N == 0)
				break;
			cout << "Результат быстрой сортировки : " << FunctionsCall(N, false, true) << " сеукунд" << endl;
			break;
		case 0:
			break; // Выход из оператора выбора
		}
	}

	system("pause");
	return 0;
}
