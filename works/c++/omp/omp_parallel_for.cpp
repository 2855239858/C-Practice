#include <stdio.h>
#include <omp.h>
using namespace std;

static omp_lock_t lock;

int main() {

	omp_set_num_threads(3);
#pragma omp parallel for
	for (int i = 0; i < 3; i++) {
        printf("i = %d, I am Thread %d\n", i, omp_get_thread_num());
    }

	getchar();
}

