#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include "generateDataSrc.h"
#include "split.h"
#include "internalSort.h"
#include "mergeSort.h"


int main(void)
{
//	int coreNum = omp_get_num_procs();//获得处理器个数
//	printf("%d\n", coreNum);

	LARGE_INTEGER li;
	LONGLONG start, end, freq;
	QueryPerformanceFrequency(&li);
	freq = li.QuadPart;

	char srcName[128] = "test.bin";
	char dstName[128] = "result.bin";
	data_type file_num = 0;
	if (num % split_part == 0)
		file_num = num / split_part;
	else
		file_num = num / split_part + 1;

	generateDataSrc(file_num, srcName);

	QueryPerformanceCounter(&li);
	start = li.QuadPart;
	
		split_files(srcName);
		inSort(file_num);

	QueryPerformanceCounter(&li);
	end = li.QuadPart;

	int useTime1 = (int)((end - start) * 1000 / freq);

	printf("\n%d integers splited to %d parts.\n", num, file_num);
	printf("Spliting file and internal sorting used %d ms.\n", useTime1);

	QueryPerformanceCounter(&li);
	start = li.QuadPart;

		mergeSort();

	QueryPerformanceCounter(&li);
	end = li.QuadPart;

	int useTime2 = (int)((end - start) * 1000 / freq);

	printf(" Used %d ms.\n", useTime2);

	char fname[32] = "";
	int cnt = 0;
#pragma omp parallel private(cnt, fname) num_threads(8)
	{
#pragma omp for
		for (cnt = 0; cnt < k; cnt++) {
			/* 以读的方式打开文件f0,f1,… */
			sprintf(fname, "%s%d%s", "temp", cnt + 1, ".bin");
			remove(fname);
		}
	}
	
	system("pause");
	return 0;



}