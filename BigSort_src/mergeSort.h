#pragma once
#include <stdio.h> 
#include <stdlib.h> 
#include "settings.h"

/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;

/* Boolean是布尔类型,其值是TRUE或FALSE */
typedef int Boolean;

/* k+1个文件指针(fp[k]为大文件指针)，全局变量 */
FILE *fp[k + 1];

/* 败者树是完全二叉树且不含叶子，可采用顺序存储结构 */
int input(int i, data_type *a);
void output(int i);
void Adjust(data_type *ls, data_type s);
void CreateLoserTree(data_type *ls);
void K_Merge(data_type *ls, data_type *b);
int mergeSort();




