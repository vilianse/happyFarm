#include <stdio.h>
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


//функция которая считает время работы
void work()
{

	printf("Сколько вы хотите поработать:");
	int workTime = readInt();
	//сначалоа хотелось добавить ограничения но я передумала
	//if (workTime > 12)
	//{
	//	printf("Не стоит так много работать");
	//	return;
	//}

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
	printf("Текущее время: день %d, время %d:00\n", current_day, current_hour);


}


int main()
{

	// выводим меню на русском языке
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	while (1)
	{
		printf("Меню \n");
		printf(" [0] Выход \n");
		printf(" [1] Посмотреть на часы \n");
		printf(" [2] Промотать время (Поработать) \n");
		printf(" [3] Посмотреть инвентарь \n");
		printf(" [4] Положить предмет в слот \n");
		printf(" [5] Выбросить предмет \n");
		printf(" [6] Выполнить задание по варианту \n");
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
			//пока что оставим так но возможно стоит вывести как отдельную функцию
			printf("Текущее время: день %d, время %d:00\n", current_day, current_hour);
			break;
		}

		case(2):
		{
			work();
			break;
		}
		case(3):
		{
			printf("функция3");
			break;
		}

		case(4):
		{
			printf("функция4");
			break;
		}

		case(5):
		{
			printf("функция5");
			break;
		}

		case(6):
		{
			printf("функция6");
			break;
		}
		default: printf("Не вырный пункт меню!\n"); break;
		}


	}


}