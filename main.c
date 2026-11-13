#include <stdio.h>
// глобальные переменные для хранения текущего дня и часа
int current_day = 1;
int current_hour = 8;


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
		int choice;
		scanf_s("%d", &choice);
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
			printf("функция2");
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