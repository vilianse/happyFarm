#include <stdio.h>
#include <locale.h> 
#include <windows.h>

// глобальные переменные для хранения текущего дня и часа
int current_day = 1;
int current_hour = 8;
int experience = 0;
//захотелось добавить общее время работы(можно убрать но мне показалось это прикольным)

//массив для инвентаря в него будем ложить id предметов
int inventory[10] = { 0, 2, 3, 5, 4, 6, 7, 5, 8, 5 };

//список предметов с которыми можно взаимодействовать
char* itemNames[10] = {
	"Пусто",
	"Дерево",
	"Камень",
	"Семена",
	"Железо",
	"Яблоко",
	"Лопата",
	"Ветка",
	"Мясо",
	"Вода"
};
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

//добавляем функцию для смены цвета текста в консоли, чтобы сделать интерфейс более приятным
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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
	for (int i = 0; i < 10; i++)
	{
		printf("Слот %d: %s\n", i, itemNames[inventory[i]]);

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
		if (itemNames[i] == 0)
			printf("Слот %d: пусто\n", i);
		else
			printf("Предмет %d: %s\n", i, itemNames[i]);
	}
	printf("Выберите предмет который хотете положить в слот:\n");
	item = readInt();

	if (item < 0 || item > 9) { printf("Неверный ввод\n"); return; }
	inventory[slot] = item;
	printf("В слот %d положен предмет %s\n", slot, itemNames[item]);
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
	for (int i = 0; i < 10; i++)
	{
		if (itemNames[i] == 0)
			printf("Слот %d: пусто\n", i);
		else
			printf("Предмет %d: %s\n", i, itemNames[i]);
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

//выводим меню в отдельную функцию
void main_menu()
{
	while (1)
	{
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
		int choice = readInt();
		switch (choice)
		{
		case(0):
		{
			//выход из игры
			return 0;
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
	main_menu();
}