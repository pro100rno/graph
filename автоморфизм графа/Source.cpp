#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int grap(int **a, int c, int b, int n, int o)
{
	int i, m = 0, v = 0, k = 0, p = 0;
	int **s, **d;
	if (c == b)
	{
		return 1;
	}
	s = (int**)malloc(2 * sizeof(int*));
	s[0] = NULL;
	s[1] = NULL;
	d = (int**)malloc(2 * sizeof(int*));
	d[0] = NULL;
	d[1] = NULL;
	for (i = 0; i < n; ++i)
	{
		if (a[c][i] != 0)
		{
			m++;
			s[0] = (int*)realloc(s[0], m * sizeof(int));
			s[0][m - 1] = i;
			s[1] = (int*)realloc(s[1], m * sizeof(int));
			s[1][m - 1] = 0;
		}
	}
	for (i = 0; i < n; ++i)
	{
		if (a[b][i] != 0)
		{
			v++;
			d[0] = (int*)realloc(d[0], v * sizeof(int));
			d[0][v - 1] = i;
			d[1] = (int*)realloc(d[1], v * sizeof(int));
			d[1][v - 1] = 0;
		}
	}
	if (m == v)
	{
		for (i = 0; i < m; ++i)
		{
			for (v = 0; v < n; ++v)
			{
				if (a[s[0][i]][v] != 0)
				{
					++k;
				}
			}
		}
		for (i = 0; i<m; ++i)
		{
			for (v = 0; v < n; ++v)
			{
				if (a[d[0][i]][v] != 0)
				{
					++p;
				}
			}
		}
		if (k == p)
		{
			if (o - 1 == 0)
			{	
				return 1;
			}
			for (i = 0; i < m; ++i)
			{
				for (k = 0; k < m; ++k)
				{
					s[1][i] = s[1][i] + grap(a, s[0][i], d[0][k], n, o - 1);
				}
			}
			for (i = 0; i < m; ++i)
			{
				if (s[1][i] > 1)
				{
					v = 0;
					for (k = 0; k < m; ++k)
					{
						if (s[1][i] == s[1][k])
							v = v + grap(a, s[0][i], s[0][k], n, o - 1);
						
					}
					if (s[1][i] != v)
					{
						return 0;
					}

				}
				else
				{
					if (s[1][i] == 0)
						return 0;

				}

			} 
			return 1;
		}
	}

	return 0;

}
int main()
{
	FILE *fp;
	int **a;  // указатель на указатель на строку элементов
	int i, j, n, p = 0;
	system("chcp 1251");
	system("cls");
	if ((fp = fopen("tree.txt", "r")) == NULL)
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
	printf("\nвведите две вершины: ");
	scanf("%d %d", &i, &j);
	if (grap(a, i - 1, j - 1, n, n) == 1)
	{
		printf("\nесть");
	}
	else
	{
		printf("\n нет");
	}
	for (i = 0; i < n; ++i)
	{
		j = 0;
		for (int g = 0; g < n; ++g)
		{


			if (g != i)
			{
				j = j + grap(a, i, g, n, n);
			}
		}
		if (j == 0)
		{
			printf("\n %d", (i + 1));
			++p;
		}
	}
	if (p == 0)
		printf("\n нет не подвижных вершин");
	// Очистка памяти
	for (i = 0; i < n; i++)  // цикл по строкам
		free(a[i]);   // освобождение памяти под строку
	free(a);
	getchar();   getchar();
	getchar();
	return 0;
}