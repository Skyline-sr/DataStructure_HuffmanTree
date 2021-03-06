#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode, * HuffmanTree;

typedef char** HuffmanCode;

static int n_create;

void CreateHuffmanTree(HuffmanTree* HT, int n);
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode* HC, int n);
void Select(HuffmanTree HT, int max_range, int* min_index_1, int* min_index_2);
void PrintHuffmanTree(HuffmanTree HT);
void PrintHuffmanCode(HuffmanCode HC, int n);

void main() {
	HuffmanTree HT;
	HuffmanCode HC;
	printf("请输入要插入的元素数目：");
	scanf("%d", &n_create);
	CreateHuffmanTree(&HT, n_create);
	PrintHuffmanTree(HT);
	CreateHuffmanCode(HT, &HC, n_create);
	PrintHuffmanCode(HC, n_create);
}

void CreateHuffmanTree(HuffmanTree* HT, int n) {
	if (n <= 1)
	{
		return;
	}
	int i, min_index_1, min_index_2;
	int m = 2 * n - 1;
	(*HT) = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	for (i = 1; i <= m; i++)
	{
		(*HT)[i].parent = (*HT)[i].lchild = (*HT)[i].rchild = 0;
	}
	for (i = 1; i <= n; i++)
	{
		printf("请输入第%d元素的权重：", i);
		scanf("%d", &((*HT)[i].weight));
	}
	for (i = n + 1; i <= m; i++)
	{
		Select(*HT, i - 1, &min_index_1, &min_index_2);
		(*HT)[i].lchild = min_index_1, (*HT)[i].rchild = min_index_2;
		(*HT)[i].weight = (*HT)[min_index_1].weight + (*HT)[min_index_2].weight;
		(*HT)[min_index_1].parent = (*HT)[min_index_2].parent = i;
		min_index_1 = min_index_2 = 0;
	}
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode* HC, int n) {
	if (HT == NULL)
	{
		return;
	}
	int i, f, c, start;
	char* cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	(*HC) = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	for (i = 1; i <= n; i++)
	{
		f = HT[i].parent;
		c = i;
		start = n - 1;
		while (f != 0)
		{
			start--;
			if (HT[f].lchild == c)
			{
				cd[start] = '0';
			}
			else
			{
				cd[start] = '1';
			}
			c = f;
			f = HT[f].parent;
		}
		(*HC)[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy((*HC)[i], &cd[start]);
	}
	free(cd);
}

void Select(HuffmanTree HT, int max_range, int* min_index_1, int* min_index_2) {
	int i, init_num, min_index_temp, min_weight_1, min_weight_2, min_weight_temp;
	init_num = 0;
	for (i = 1; i <= max_range; i++)
	{
		if (HT[i].parent == 0)
		{
			if (init_num == 0)
			{
				*min_index_1 = i;
				min_weight_1 = HT[i].weight;
				init_num++;
			}
			else if (init_num == 1)
			{
				*min_index_2 = i;
				min_weight_2 = HT[i].weight;
				init_num++;
				break;
			}
		}
	}
	for (i = 1; i <= max_range; i++)
	{
		if (HT[i].parent != 0 || i == *min_index_2)
		{
			continue;
		}
		if (HT[i].weight < min_weight_1)
		{
			*min_index_1 = i;
			min_weight_1 = HT[i].weight;
		}
	}
	for (i = 1; i <= max_range; i++)
	{
		if (HT[i].parent != 0 || i == *min_index_1)
		{
			continue;
		}
		if (HT[i].weight < min_weight_2)
		{
			*min_index_2 = i;
			min_weight_2 = HT[i].weight;
		}
	}
	if (min_weight_1 > min_weight_2)
	{
		min_weight_temp = min_weight_1, min_weight_1 = min_weight_2, min_weight_2 = min_weight_temp;
		min_index_temp = (*min_index_1), (*min_index_1) = (*min_index_2), (*min_index_2) = min_index_temp;
	}
}

void PrintHuffmanTree(HuffmanTree HT) {
	int i;
	printf("哈夫曼树中元素的权重分别为：");
	for (i = 1; i <= 2 * n_create - 1; i++)
	{
		printf(" %d", HT[i].weight);
	}
	printf("\n");
	printf("哈夫曼树中元素的双亲分别为：");
	for (i = 1; i <= 2 * n_create - 1; i++)
	{
		printf(" %d", HT[i].parent);
	}
	printf("\n");
	printf("哈夫曼树中元素的左孩子分别为：");
	for (i = 1; i <= 2 * n_create - 1; i++)
	{
		printf(" %d", HT[i].lchild);
	}
	printf("\n");
	printf("哈夫曼树中元素的右孩子分别为：");
	for (i = 1; i <= 2 * n_create - 1; i++)
	{
		printf(" %d", HT[i].rchild);
	}
	printf("\n");
}

void PrintHuffmanCode(HuffmanCode HC, int n) {
	int i;
	for (i = 1; i <= n; i++)
	{
		printf("第%d个元素的哈夫曼编码：%s\n", i, HC[i]);
	}
}