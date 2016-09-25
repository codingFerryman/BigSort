#define _CRT_SECURE_NO_WARNINGS
#include "internalSort.h"

data_type inSort(int file_num)
{
	int id = 0;
	int idStart = 1;
	int count = 0;
	char srcName[128] = "";
	data_type *arr_d;

	FILE *ptr_fp = NULL;

	#pragma omp parallel private(id,srcName,arr_d,ptr_fp,count) shared(file_num,idStart) num_threads(8)
	{
		#pragma omp for
			for (id = idStart;id <= file_num;id++)
			{
				arr_d = (data_type*)malloc(split_part*sizeof(data_type));
				sprintf(srcName, "%s%d%s", "temp", id, ".bin");

				if ((ptr_fp = fopen(srcName, "rb")) == NULL)
				{
					printf("%d\tUnable to open the file!\n", id);
					system("pause");
					exit(1);
				}
//				else printf("%d\tOpened file successfully for reading.\n", id);

				fseek(ptr_fp, 0, SEEK_END);
				long int file_eof = ftell(ptr_fp);
				//printf("eof=%d\n", file_eof);
				//printf("sizeof(arr)=%d\n", sizeof(arr_d[0]));
				count = file_eof / sizeof(data_type);
				rewind(ptr_fp);

				if (fread(arr_d, sizeof(data_type), split_part, ptr_fp) < 1)
				{
					printf("Error Occurred!\n");
					system("pause");
					exit(1);
				}
				fclose(ptr_fp);

				qsort(arr_d,split_part,sizeof(data_type),cmp);
				if ((ptr_fp = fopen(srcName, "wb")) == NULL)
				{
					printf("%d\tUnable to open the file!\n", id);
					system("pause");
					exit(1);
				}
//				else printf("%d\tOpened file successfully for reading.\n", id);
				if (fwrite(arr_d, sizeof(data_type), split_part, ptr_fp) < 1)
				{
					printf("%d\tWrite error!\n", id);
					system("pause");
					exit(1);
				}
//				else printf("%d\tWrite was successful.\n", id);
//				printf("%d\tQuick Sort was successful.\n", id);
				fclose(ptr_fp);
				free(arr_d);
			}
	}
	printf("Internal quick sort was successful.\n");
	//FILE *ptr_fp2 = NULL;
	//arr_d = (data_type*)malloc(split_part*sizeof(data_type));
	//ptr_fp2 = fopen("temp30.bin", "rb");
	//fread(arr_d, sizeof(data_type), split_part, ptr_fp2);
	//for (int i = 0; i < split_part;i++)
	//	printf("%u\n", arr_d[i]);
	//printf("\n");
	return 1;
}

int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}