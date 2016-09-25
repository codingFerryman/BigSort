#include <windows.h>
#include <stdio.h>

int main() {
	LARGE_INTEGER li;
	LONGLONG start, end, freq;
	QueryPerformanceFrequency(&li);
	freq = li.QuadPart;
	QueryPerformanceCounter(&li);
	start = li.QuadPart;
	Sleep(3000);
	QueryPerformanceCounter(&li);
	end = li.QuadPart;
	int useTime = (int)((end - start) * 1000 / freq);
	printf("time: %d ms\n", useTime);
	system("pause");
	return 0;
}