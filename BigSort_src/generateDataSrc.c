#define _CRT_SECURE_NO_WARNINGS
#include "generateDataSrc.h"

int generateDataSrc(int file_num, const char * srcName)
{
	int r;
	unsigned __int32 u32;
	long counter = 0;
	data_type *ptr_d;
	FILE *ptr_fp;

	/* Part A */



	/* Part B */
	if ((ptr_fp = fopen(srcName, "wb")) == NULL)
	{
		printf("Unable to open file!\n");
		exit(1);
	}
	else printf("Opened file successfully for writing.\n");

	/* Part C */
	do
	{
		ptr_d = (data_type *)malloc(gen_ptr_part * sizeof(data_type));
		int count_split = 0;
		for (count_split = 0; count_split < gen_ptr_part;count_split++)
		{
			r = rdrand_32(&u32, 1);
			if (r != RDRAND_SUCCESS) printf("rdrand instruction failed with code %d\n", r);
			u32 = u32 << 16;
			ptr_d[count_split] = (u32 >> 16) & 0x7FFF;
			counter++;
		}
		ptr_d[gen_ptr_part - 1] = MAXKEY;
		if (fwrite(ptr_d, gen_ptr_part * sizeof(data_type), 1, ptr_fp) != 1)
		{
			printf("Write error!\n");
			exit(1);
		}
		free(ptr_d);
		fflush(ptr_fp);
	} while (counter < num);
	printf("Write was successful.\n");

	/* Part D */
	fclose(ptr_fp);
//	free(ptr_d);

	return 1;

}