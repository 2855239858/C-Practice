#include <stdio.h>
#include <omp.h>
using namespace std;

static omp_lock_t lock;

int main() {
    int var1 = 100, var2 = 0;
    omp_init_lock(&lock);
	omp_set_num_threads(3);

#pragma omp parallel for lastprivate(var1) shared(var2)
	for (int i = 0; i < 3; i++) {
        printf("i = %d, I am Thread %d: var2(%d)\n",
                i, omp_get_thread_num(), var2);

        omp_set_lock(&lock);
        ++var1, ++var2;
        var1 = i;
        omp_unset_lock(&lock);
    }

    printf("Parallel region end: var1(%d), var2(%d)", var1, var2);
    omp_destroy_lock(&lock);
	getchar();
}

