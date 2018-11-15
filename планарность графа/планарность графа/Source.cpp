#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int graph(int **a, int n)
{
	
	int **b, t,v=0;
	if (n < 5)
	{
		
		return 0;
	}
	for (int i=0; i < n; ++i) //проверка на изолированную вершину 
	{
		t = 0;
		for (int j = 0; j < n; ++j)
		{
			if (a[i][j] == 0)  
				++t;
		}
		if (t == n)
		{	// Выделение памяти под указатели на строки
			b = (int**)calloc(n-1, sizeof(int*));
			// Ввод элементов массива
			for (int j = 0; j < n-1; ++j)  // цикл по строкам
			{
				// Выделение памяти под хранение строк
				b[j] = (int*)calloc(n-1, sizeof(int));
			}
			for (int j = 0; j < n; ++j)  // цикл по строкам
			{	
				if(j<i)
				{
					for (int w = 0; w < n; ++w)  // цикл по столбцам
					{
						if (w < i)
						{
							b[j][w] = a[j][w];
						}
						else if (w > i)
						{
							b[j][w-1] = a[j][w];
						}
					}
				}
				else if (j > i)
				{
					for (int w = 0; w < n; ++w)  // цикл по столбцам
					{
						if (w < i)
						{
							b[j-1][w] = a[j][w];
						}
						else if (w > i)
						{
							b[j-1][w - 1] = a[j][w];
						}
					}
				}
			}
			v = graph(b, n - 1);
			for (int j = 0; j < n-1; j++)  // цикл по строкам
				free(b[j]);   // освобождение памяти под строку
			free(b);
			return v;
		}
			
	}
	v = 0;
	if (n==5) //проверка на граф К5
	{
		for (int i = 0; i < n; ++i)
		{
			t = 0;
			
			for (int j = 0; j < n; ++j)
			{
				if (a[i][j] == 1)
				{
					++t;
				}
			}
			if (t == n-1)
			{
				++v;
			}
		}
		if (v == n)
		{
			return 1;
		}
	}
	if (n == 6)//проверка на граф К3,3
	{
		for (int i = 0; i < n; ++i)
		{
			t = 0;
			for (int j = 0; j < n; ++j)
			{
				if (a[i][j] == 1)
				{
					++t;
				}
			}
			if (t == 3)
			{
				++v;
			}
		}
		if (v == n)
		{
			return 1;
		}

	}
	v = 0;
	b = (int**)calloc(n - 1, sizeof(int*));
	for (int j = 0; j < n - 1; ++j)  // цикл по строкам
	{
		// Выделение памяти под хранение строк
		b[j] = (int*)calloc(n - 1, sizeof(int));
	}
	v = 0;
	for (int i = 0; i < n; ++i) // проверка на стягивание
	{
		for (int j = 0; j < n; ++j)
		{
			if (a[i][j] == 1)
			{
				if (i > j)
				{
					for (int w = 0; w < n; ++w)// проверка на удаление ребра
					{
						if (w != j)
						{
							if (w < i)
							{
								for (int e = 0; e < n; ++e)  // цикл по столбцам
								{
									if (e != j)
									{
										if (e < i)
										{
											b[w][e] = a[w][e];
										}
										else if (e > i)
										{
											b[w][e - 1] = a[w][e];
										}
									}
									else
									{
										if (a[w][e] == 1)
										{
											b[w][e] = a[w][e];
										}
										if (a[w][i] == 1)
										{
											b[w][e] = a[w][i];
										}
									}
								}
							}
							else if (w > i)
							{
								for (int e = 0; e < n; ++e)  // цикл по столбцам
								{
									if (e != j)
									{
										if (e < i)
										{
											b[w - 1][e] = a[w][e];
										}
										else if (e > i)
										{
											b[w - 1][e - 1] = a[w][e];
										}
									}
									else
									{
										if (a[w][e] == 1)
										{
											b[w - 1][e] = a[w][e];
										}
										if (a[w][i] == 1)
										{
											b[w - 1][e] = a[w][i];
										}
									}
								}
							}
						}
						else
						{
							for (int e = 0; e < n; ++e)  // цикл по столбцам
							{
								if (e != j)
								{
									if (e < i)
									{
										if (a[w][e] == 1)
										{
											b[w][e] = a[w][e];
										}
										else if (a[i][e] == 1)
										{
											b[w][e] = a[i][e];
										}
									}
									else if (e > i)
									{
										if (a[w][e] == 1)
										{
											b[w][e - 1] = a[w][e];
										}
										else if (a[i][e] == 1)
										{
											b[w][e - 1] = a[i][e];
										}
									}
								}
							}
						}
					}
					v = v + graph(b, n - 1);
					if (v == 1)
					{
						for (int w = 0; w < n - 1; w++)  // цикл по строкам
							free(b[w]);   // освобождение памяти под строку
						free(b);
						return 1;
					}
				}

			}


		}
	}
	for (int w = 0; w < n - 1; w++)  // цикл по строкам
		free(b[w]);   // освобождение памяти под строку
	free(b);
	// Выделение памяти под указатели на строки
	b = (int**)calloc(n, sizeof(int*));
	// Ввод элементов массива
	for (int j = 0; j < n; ++j)  // цикл по строкам
	{
		// Выделение памяти под хранение строк
		b[j] = (int*)calloc(n, sizeof(int));
	}
	for (int i = 0; i < n; ++i)// проверка на удаление ребра
	{
		for (int j = 0; j < n; ++j)
		{
			if (i > j)
			{
				if (a[i][j] == 1)
				{
					for (int w = 0; w < n; ++w)
					{
						for (int e = 0; e < n; ++e)
						{	
							b[w][e] = a[w][e];
						}
					}
					b[i][j] = 0;
					b[j][i] = 0;
					v = v + graph(b, n);
					if (v == 1)
					{
						for (int w = 0; w < n; w++)  // цикл по строкам
							free(b[w]);   // освобождение памяти под строку
						free(b);
						return 1;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++)  // цикл по строкам
		free(b[i]);   // освобождение памяти под строку
	free(b);
	return 0;


}
int main()
{
	FILE *fp;
	int **a;  // указатель на указатель на строку элементов
	int i, j, n, p = 0;
	system("chcp 1251");
	system("cls");
	if ((fp = fopen("graph.txt", "r")) == NULL)
	{
		printf("Warning \n");
		system("pause");
		exit(1);
	}
	fscanf(fp, "%d", &n);
	// Выделение памяти под указатели на строки
	a = (int**)calloc(n, sizeof(int*));
	// Ввод элементов массива
	for (i = 0; i < n; i++)  // цикл по строкам
	{
		// Выделение памяти под хранение строк
		a[i] = (int*)calloc(n, sizeof(int));
	}
	while (1)
	{
		fscanf(fp, "%d", &i);
		if (feof(fp))
		{
			break;
		}
		fscanf(fp, "%d", &j);
		a[i - 1][j - 1] = 1;
		a[j - 1][i - 1] = 1;
		if (feof(fp))
		{
			break;
		}
	}
	fclose(fp);
	for (i = 0; i < n; i++)  // цикл по строкам
	{
		for (j = 0; j < n; j++)  // цикл по столбцам
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	p = graph(a, n);

	if (p == 0)
	{
		printf("\n планарный ");
	}
	else
	{
		printf("\n не планарный");
	}
	// Очистка памяти
	for (i = 0; i < n; i++)  // цикл по строкам
		free(a[i]);   // освобождение памяти под строку
	free(a);
	getchar();   getchar();
	getchar();
	return 0;
}