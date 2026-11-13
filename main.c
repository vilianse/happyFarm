#include <stdio.h>
#include <locale.h> 
#include <windows.h>
#include <string.h>


// глобальные переменные для хранения текущего дня и часа
int current_day = 1;
int current_hour = 8;
//переменная могла быть использована
int experience = 0;
//имя пользователя
char username[33];//учитываем нулевой символ в конце строки
//захотелось добавить общее время работы(можно убрать но мне показалось это прикольным)

#define MAX_ITEMS    10
#define MAX_NAME_LEN 32

char item_names[MAX_ITEMS][MAX_NAME_LEN];

// немного измененный массив инвентаря
int inventory[MAX_ITEMS] = { 0, 2, 8, 5, 1, 8, 3, 5, 4, 2 };

// заполняет массив дефолтными значениями в случае если не загрузится файл items
void fillDefaultItems()
{
	const char* defaults[MAX_ITEMS] = {
		"Пусто", "Дерево", "Камень", "Семена", "Железо",
		"Яблоко", "Лопата", "Ветка", "Мясо", "Вода"
	};
	for (int i = 0; i < MAX_ITEMS; i++)
		strcpy_s(item_names[i], MAX_NAME_LEN, defaults[i]); // заполняет инвентарь по дефолту
}


// функция для проверки ввода, очень поможет на всем промежутке работы
int readInt()
{
	int value;
	// проверяем, что scanf_s вернул 1 (т.е. успешно прочитал число)
	if (scanf_s("%d", &value) != 1)
	{
		while (getchar() != '\n');
		return -1;
	}
	while (getchar() != '\n');
	return value;
}

// функция для считывания предметов из файда
void loadItems(const char* filename)
{
	fillDefaultItems();   // сначала заменяем массив дефолтными значениями на случай если в файле чего то будет не хватать

	FILE* f = NULL;
	if (fopen_s(&f, filename, "r") != 0 || f == NULL)
	{
		printf("[!] Файл %s не найден. Используются названия по умолчанию.\n", filename);
		return;
	}

	char line[MAX_NAME_LEN];
	int i = 0;
	while (i < MAX_ITEMS && fgets(line, sizeof(line), f) != NULL)
	{
		line[strcspn(line, "\r\n")] = '\0';   // убираем \n и \r
		if (line[0] != '\0')                  // пустые строки пропускаем
		{
			strcpy_s(item_names[i], MAX_NAME_LEN, line);
			i++;
		}
	}
	fclose(f);
	printf("[+] Загружено предметов из %s: %d\n", filename, i);
}

// запрос имени фермера
void askName()
{
	printf("Как тебя зовут, фермер?: ");
	fgets(username, sizeof(username), stdin);
	username[strcspn(username, "\r\n")] = '\0'; // обрезает конец
	if (username[0] == '\0') //дает дефолтное имя
		strcpy_s(username, sizeof(username), "Фермер");
}


//добавляем функцию для смены цвета текста в консоли, чтобы сделать интерфейс более приятным
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//полностью украдено у чата гпт потому что хочется сделать чтобы учитывало все регистры а не получается
void toLowerRussian(char* str)
{
	for (int i = 0; str[i]; i++)
	{
		unsigned char a = (unsigned char)str[i];

		if (a == 0xD0 && (unsigned char)str[i + 1] >= 0x90 &&
			(unsigned char)str[i + 1] <= 0x9F)
			str[i + 1] += 0x20;

		else if (a == 0xD0 && (unsigned char)str[i + 1] == 0x81)
			str[i + 1] = 0x91;
	}
}

//функция которая считает время работы
void work()
{

	printf("Сколько вы хотите поработать:");
	int workTime = readInt();
	if (workTime > 16)
	{
		printf("Не стоит так много работать((( \n");
		//формальные ограничения можно добавить return если захочется 
	}

	if (workTime < 0)
	{
		printf("Нельзя столько работать\n");
		return;
	}
	current_hour += workTime;

	//расчет отработанных часов
	if (current_hour >= 24)
	{
		current_day += current_hour / 24;
		current_hour = current_hour % 24;
		experience += workTime;
	}
	setColor(10);
	printf("Текущее время: день %d, время %d:00\n", current_day, current_hour);
	setColor(7);
}

void Inventory()
{
	//перебор и вывод интентаря
	// был дан немгного другой пример но я считаю что такое оформление более понятно пользователю тем более про количество предметов и тому подобное слов не было да и лопаты 3 в кармане не может быть
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		printf("Слот %d: %s\n", i, item_names[inventory[i]]);

	}


}


void swapItem()
{
	int slot, item;
	//показываем весь инвентарь
	Inventory();
	printf("Выберите слот который хотите заменить:\n");
	slot = readInt();
	//проверка на то чтобы число не выходило за диапазон
	if (slot < 0 || slot > 9) { printf("Неверный номер слота!\n"); return; }
	//показываем все доступные предметы
	for (int i = 0; i < 10; i++)
	{
		if (item_names[i] == 0)
			printf("Слот %d: пусто\n", i);
		else
			printf("Предмет %d: %s\n", i, item_names[i]);
	}
	printf("Выберите предмет который хотете положить в слот:\n");
	item = readInt();

	if (item < 0 || item > 9) { printf("Неверный ввод\n"); return; }
	inventory[slot] = item;
	printf("В слот %d положен предмет %s\n", slot, item_names[item]);
}

void dropItem()
{
	//выводим инвентарь чтобы пользователь видел что у него есть
	Inventory();
	int slot;
	printf("Выберите прдемт который хотите выбросить: ");
	slot = readInt();
	if (slot < 0 || slot > 9) { printf("Неверный номер слота!\n"); return; }
	inventory[slot] = 0; // просто обнуляем слот
	printf("Предмет безвозвратно выброшен(((\n");
}


void checkNearbyItems()
{
	int item1, item2;
	int found = 0;
	//выводим инвентарь и сами предметы для удобства пользователя
	printf("Инвентарь:\n");
	Inventory();
	printf("Список предметов:\n");
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (item_names[i] == 0)
			printf("Слот %d: пусто\n", i);
		else
			printf("Предмет %d: %s\n", i, item_names[i]);
	}
	printf("Введите ID первого предмета: ");
	item1 = readInt();
	printf("Введите ID второго предмета: ");
	item2 = readInt();

	if (item1 < 0 || item1 > 9 || item2 < 0 || item2 > 9)
	{
		printf("Неверный ID предмета!\n");
		return;
	}
	//проверяем лежат ли предметы в соседних слотах
	for (int i = 0; i < 9; i++)
	{
		if ((inventory[i] == item1 && inventory[i + 1] == item2) ||
			(inventory[i] == item2 && inventory[i + 1] == item1))
		{
			printf("Предметы находятся рядом! Слоты: %d и %d\n", i, i + 1);
			found = 1;
		}
	}

	if (found == 0)
	{
		printf("Предметы не лежат рядом!\n");
	}
}

//поиск предмета по названию в инвентаре
void searchItemByName()
{
	char query[MAX_NAME_LEN];
	int count = 0;

	printf("Введите название предмета: ");
	fgets(query, sizeof(query), stdin);
	//проверяем, что введенная строка не превышает размер
	if (strchr(query, '\n') == NULL)
	{
		while (getchar() != '\n');
		printf("Слишком длинное название!\n");
		return;
	}
	query[strcspn(query, "\r\n")] = '\0';

	toLowerRussian(query);
	//ищем предмет в массиве item_names
	for (int i = 1; i < MAX_ITEMS; i++)
	{
		char name[MAX_NAME_LEN];
		strcpy_s(name, MAX_NAME_LEN, item_names[i]);
		toLowerRussian(name);

		if (strcmp(name, query) == 0)
		{
			printf("Найден предмет: %s\nСлоты: ", item_names[i]);

			for (int j = 0; j < MAX_ITEMS; j++)
				if (inventory[j] == i)
				{
					printf("%d ", j);
					count++;
				}

			printf("\nКоличество: %d\n", count);
			return;
		}
	}

	printf("Предмет не найден!\n");
}


// Заполнение дневника текущим состоянием фермы
void saveDiary()
{
	FILE* file = NULL;

	// открываем/создаем файл для записи
	if (fopen_s(&file, "diary.txt", "a") != 0 || file == NULL)
	{
		printf("[!] Не удалось открыть diary.txt\n");
		return;
	}
	//записываем основную информацию
	printf("Фермер: %s\n", username);
	fprintf(file, "Фермер: %s\n", username);

	printf("День: %d\n", current_day);
	fprintf(file, "День: %d\n", current_day);

	printf("Время: %02d:00\n", current_hour);
	fprintf(file, "Время: %02d:00\n", current_hour);

	printf("\nИнвентарь:\n");
	fprintf(file, "\nИнвентарь:\n");

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		char* itemName = item_names[inventory[i]];

		printf("Слот %d: %s\n", i, itemName);
		fprintf(file, "Слот %d: %s\n", i, itemName);
	}
	//делаем разделитель чтобы было удобнее читать
	printf("=====================================\n");
	fprintf(file, "=====================================\n");

	fclose(file);

	printf("\n[+] Состояние фермы сохранено в diary.txt\n");
}



//выводим меню в отдельную функцию
void main_menu()
{
	askName();
	while (1)
	{
		setColor(5);
		printf("Фермер: %s\n", username);   //  шапка с именем
		setColor(14);
		printf("====== МЕНЮ ========\n");
		setColor(7);
		printf(" [0] Выход \n");
		printf(" [1] Посмотреть на часы \n");
		printf(" [2] Промотать время (Поработать) \n");
		printf(" [3] Посмотреть инвентарь \n");
		printf(" [4] Положить предмет в слот \n");
		printf(" [5] Выбросить предмет \n");
		printf(" [6] Проверка соседних ячеек \n");
		printf(" [7] Поиск предмета в рюкзаке по названию \n");
		printf(" [8] Записать состояние в дневник фермера \n");
		printf(" [9] Расшифровать старые записи \n");
		int choice = readInt();
		switch (choice)
		{
		case(0):
		{
			//выход из игры
			return;
		}

		case(1):
		{
			system("cls");
			//пока что оставим так но возможно стоит вывести как отдельную функцию
			setColor(10);
			printf("Текущее время: день %d, время %d:00\n", current_day, current_hour);
			setColor(7);
			break;
		}

		case(2):
		{
			system("cls");
			work();
			break;
		}
		case(3):
		{
			system("cls");
			Inventory();
			break;
		}

		case(4):
		{
			system("cls");
			swapItem();
			break;
		}

		case(5):
		{
			system("cls");
			dropItem();
			break;
		}

		case(6):
		{
			system("cls");
			checkNearbyItems();
			break;
		}
		case(7):
		{
			system("cls");
			searchItemByName();
			break;
		}
		case(8):
		{
			system("cls");
			saveDiary();
			break;
		}
		case(9):
		{
			system("cls");
			printf("функция 9");
			break;
		}
		default: printf("Не вырный пункт меню!\n"); system("cls");break; //добавила очистку и получилось приклоно
		}
	}

}


int main()
{
	// выводим меню на русском языке
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	SetConsoleTitleA("happy farm");// добавляем название консоли чтобы было прикольно, хотелось еще ее по центру сделать но там слишком много странного кода
	loadItems("items.txt");
	main_menu();
}