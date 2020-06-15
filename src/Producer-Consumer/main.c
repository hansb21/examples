/*
 * MIT License
 *
 * Copyright(c) 2018 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <nanvix/runtime/runtime.h>
#include <nanvix/sys/perf.h>
#include <nanvix/ulib.h>
#include <nanvix/sys/thread.h>
#include <nanvix/sys/semaphore.h>
#define SIZE 5
/*============================================================================*
 * Benchmark Driver                                                           *
 *============================================================================*/

/**
 * @brief Launches a benchmark.
 */

int buffer[THREAD_MAX-1]; 
struct nanvix_semaphore cheio, vazio, lock_prod, lock_cons;

int f, i = 0;

void* producer() {
	while (1) {
		nanvix_semaphore_down(&vazio);
		nanvix_semaphore_down(&lock_prod);

		f = (f+1) % SIZE;
		buffer[f] = 1;
		uprintf("produzi no indice %d", f);
		nanvix_semaphore_up(&lock_prod);
		nanvix_semaphore_up(&cheio);
		return 0;
	}
	kthread_exit(NULL);
}
void* consumer() {
	while(1) {
		nanvix_semaphore_down(&cheio);
		nanvix_semaphore_down(&lock_cons);

		i = (i+1) % SIZE;
		buffer[i] = 0;
		uprintf("consumi no indice %d", i);
		
		nanvix_semaphore_down(&lock_cons);
		nanvix_semaphore_down(&vazio);
		
	//	delay(1, CLUSTER_FREQ);
	}
	kthread_exit(NULL);
}

int __main3(int argc, const char *argv[]) {	
	
	((void) argc);
	((void) argv);
	
	nanvix_semaphore_init(&cheio, 0);
	nanvix_semaphore_init(&vazio, THREAD_MAX-1);
	nanvix_semaphore_init(&lock_prod, 1);
	nanvix_semaphore_init(&lock_cons, 1);
	
	kthread_t threa[2];
	int cons = 2;
	int prod = 2;
	int n, d = 0;

	for (; n < cons; ++n) {
		kthread_create(&threa[n], consumer, NULL );
}
	for (; n < cons + prod; ++n) { 
		kthread_create(&threa[n], producer, NULL);
}
	for (d = 0; i <cons+prod; ++d) {
		kthread_join(threa[d], NULL);	
}
	return (0);

}


