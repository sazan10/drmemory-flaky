#include <pthread.h>
#include <stdlib.h>
#define N 10000
char *a;
void *Thread(void *arg) {
long i, tid = (long)arg;
for (i = tid; i < N * 4; i += 4)
a[i] = 42; // Race on shadow.
return 0;
}

int main() {
long i;
pthread_t t[4];
a = (char_)malloc(4 * N);
for (i = 0; i < 4; i++)
pthread_create(&t[i], 0, Thread, (void_)i);
for (i = 0; i < 4; i++)
pthread_join(t[i], 0);
for (i = 0; i < N * 4; i++)
if (a[i] != 42) // DrMemory may think that
return 1; // a[i] is uninitialized.
free(a);
return 0;
}
