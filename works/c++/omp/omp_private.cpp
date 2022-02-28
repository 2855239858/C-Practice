#include <stdio.h>
#include <omp.h>

using namespace std;

int main() {
    int var1 = 0, var2 = 0;

	omp_set_num_threads(3);
#pragma omp parallel private(var1) shared(var2)
	for (int i = 0, var1 = 0; i < 3; i++) {
        printf("i = %d, I am Thread %d: var1(%d), var2(%d)\n", i, omp_get_thread_num(), var1, var2);
        ++var1;
        ++var2;
    }
    printf("Parallel region end: var1(%d), var2(%d)", var1, var2);
	getchar();
}