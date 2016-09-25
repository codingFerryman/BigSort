#define _CRT_SECURE_NO_WARNINGS
#include "split.h"

data_type split_files(const char * srcName)
{
	int counter = 0;
	int split_num;
	data_type *ptr_d;
	FILE *ptr_fp;
	FILE *ptr_fo = NULL ;
	char dstName[128];

	/* Part E */
	ptr_d = (data_type *)malloc(split_part * sizeof(data_type));
	if (!ptr_d)
	{
		printf("Memory allocation error!\n");
		exit(1);
	}
	else printf("Memory allocation successful.\n");

	/* Part F */
	if ((ptr_fp = fopen(srcName, "rb")) == NULL)
	{
		printf("Unable to open the file!\n");
		exit(1);
	}
	else printf("Opened file successfully for reading.\n");


	/* Part G */
	int tempcount = 1;
	split_num = num / split_part;

	for (tempcount = 1; tempcount <= split_num; tempcount++)
	{
		sprintf(dstName, "%s%d%s", "temp", tempcount, ".bin");

		if (fread(ptr_d, split_part * sizeof(data_type), 1, ptr_fp) != 1)
		{
			printf("Read error!\n");
			exit(1);
		}
//		else printf("Read was successful.\n");

		if ((ptr_fo = fopen(dstName, "wb")) == NULL)
		{
			printf("Unable to open file!\n");
			exit(1);
		}
//		else printf("Opened %d file successfully for writing.\n", tempcount);

		if (fwrite(ptr_d, split_part * sizeof(data_type), 1, ptr_fo) != 1)
		{
			printf("Write error!\n");
			exit(1);
		}
//		else printf("Write was successful.\n");

		fclose(ptr_fo);
	}
	free(ptr_d);
	long int file_ptr = ftell(ptr_fp);
	printf("ftell=%ld\n", file_ptr);
	fseek(ptr_fp, 0, SEEK_END);
	long int file_eof = ftell(ptr_fp);
	printf("SEEK_END_ftell=%ld\n", file_eof);
	if (file_ptr != file_eof)
	{
		sprintf(dstName, "%s%d%s", "temp", tempcount, ".bin");
		int last = (file_eof - file_ptr) / sizeof(data_type);
		ptr_d = (data_type *)malloc(last * sizeof(data_type));
		rewind(ptr_fp);
		if (fread(ptr_d, last * sizeof(data_type), 1, ptr_fp) != 1)
		{
			printf("Read error!\n");
			exit(1);
		}
		else printf("Read was successful.\n");

		if ((ptr_fo = fopen(dstName, "wb")) == NULL)
		{
			printf("Unable to open file!\n");
			exit(1);
		}
		else printf("Opened %d file successfully for writing.\n", tempcount);

		if (fwrite(ptr_d, last * sizeof(data_type), 1, ptr_fo) != 1)
		{
			printf("Write error!\n");
			exit(1);
		}
		else printf("Write was successful.\n");

		fclose(ptr_fo);
	}
	else
		fclose(ptr_fo);
	file_ptr = ftell(ptr_fp);
	printf("ftell=%ld\n", file_ptr);
	printf("SEEK_END_ftell=%ld\n", file_eof);
	printf("Splited to the End Of File!\n");
	printf("%d files were generated.\n", split_num);
	/* Part H */

	fclose(ptr_fp);

	return 1;

}