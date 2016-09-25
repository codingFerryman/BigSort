#define _CRT_SECURE_NO_WARNINGS

#include "mergeSort.h"

/* 全局变量 */
data_type *b;
data_type *ls;

/* 从第i个文件(第i个归并段)读入该段当前第1个记录的关键字到外结点 */
int input(int i, data_type *a) 
{
	int j = fread(a, sizeof(data_type), 1, fp[i]);
	if (j > 0) {
//		printf("%d\n", *a);
		return 1;
	}
	else {
		return 0;
	}
}

/* 将第i个文件(第i个归并段)中当前的记录写至输出归并段 */
void output(int i) 
{
	fwrite(&b[i], sizeof(data_type), 1, fp[k]);
}

/* 沿从叶子结点b[s]到根结点ls[0]的路径调整败者树。*/
void Adjust(data_type *ls, data_type s)
{
	int t;
	data_type i;

	/* ls[t]是b[s]的双亲结点 */
	t = (s + k) / 2;
	while (t > 0) {
		/* s指示新的胜者 */
		if (b[s] > b[ls[t]]) {
			i = s;
			s = ls[t];
			ls[t] = i;
		}
		t = t / 2;
	}
	ls[0] = s;
}

/**
* 已知b[0]到b[k-1]为完全二叉树ls的叶子结点，存有k个关键字，沿从叶子
* 到根的k条路径将ls调整成为败者树。
*/
void CreateLoserTree(data_type *ls)
{
	int i;
	b[k] = MINKEY;

	/* 设置ls中“败者”的初值 */
	for (i = 0; i < k; ++i) {
		ls[i] = k;
	}

	/* 依次从b[k-1]，b[k-2]，…，b[0]出发调整败者 */
	for (i = k - 1; i >= 0; --i) {
		Adjust(ls, i);
	}
}

/**
* 利用败者树ls将编号从0到k-1的k个输入归并段中的记录归并到输出归并段。
* b[0]至b[k-1]为败者树上的k个叶子结点，分别存放k个输入归并段中当前记录的关键字。
*/
void K_Merge(data_type *ls, data_type *b)
{
	int i;
	data_type q;

	/* 分别从k个输入归并段读人该段当前第一个记录的关键字到外结点 */
	for (i = 0; i < k; ++i) {
		input(i, &b[i]);
	}

	/* 建败者树ls，选得最小关键字为b[ls[0]].key */
	CreateLoserTree(ls);

	while (b[ls[0]] != MAXKEY) {
		/* q指示当前最小关键字所在归并段 */
		q = ls[0];

		/* 将编号为q的归并段中当前（关键字为b[q].key）的记录写至输出归并段 */
		output(q);

		/* 从编号为q的输入归并段中读人下一个记录的关键字 */
		if (input(q, &b[q]) > 0) {
			/* 调整败者树，选择新的最小关键字 */
			Adjust(ls, q);
		}
//		fflush(fp[k]);
	}

	/* 将含最大关键字MAXKEY的记录写至输出归并段 */
	output(ls[0]);
	fflush(fp[k]);
}

int mergeSort() 
{
	b = (data_type*)malloc((k + 1)*sizeof(data_type));
	int i = 0;
	char fname[32] = "";
	char fout[32] = "result.bin";
	ls = (data_type*)malloc(k*sizeof(data_type));;

	/* 依次打开子文件 */
	#pragma omp parallel private(i, fname) num_threads(8)
	{	
		#pragma omp for
		for (i = 0; i < k; i++) {
			/* 以读的方式打开子文件*/
			sprintf(fname, "%s%d%s", "temp", i + 1, ".bin");
			fp[i] = fopen(fname, "rb");
		}
	}
	/* 以写的方式打开大文件fout */
	fp[k] = fopen(fout, "wb");

	/* 利用败者树ls将k个输入归并段中的记录归并到输出归并段，即大文件fout */
	K_Merge(ls, b);

	/* 关闭文件f0,f1,…和文件fout */
	for (i = 0; i <= k; i++) {
		fclose(fp[i]);
	}
	/* 关闭大文件fout */
	fclose(fp[k]);
	free(b);
	printf("Merge Sort Success!");
	return 1;
}