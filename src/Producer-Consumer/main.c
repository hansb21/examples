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

#define NPRODUCERS ((THREAD_MAX - 1) / 2)
#define NCONSUMERS ((THREAD_MAX - 1) / 2)
#define SIZE 10
/*============================================================================*
 * Benchmark Driver                                                           *
 *============================================================================*/

/**
 * @brief Launches a benchmark.
 */

int buffer[THREAD_MAX-1]; 
struct nanvix_semaphore cheio, vazio, lock_prod, lock_cons;

int f, i = 0;

void* producer(void * args)
{
	int tid = *((int *) args);
	uprintf("Produtor %d criado", tid);
	for (int value = (tid * 1000); value < ((tid + 1) * 1000); value++)
	{
		nanvix_semaphore_down(&vazio);
		nanvix_semaphore_down(&lock_prod);
		f = (f+1) % SIZE;
		buffer[f] = value;
		uprintf("produzi no indice %d: %d", f, value);
		nanvix_semaphore_up(&lock_prod);
		nanvix_semaphore_up(&cheio);
	}
	kthread_exit(NULL);
	return 0;
}


void* consumer(void * args) {
	
	int tid = *((int *) args);

	uprintf("Consumidor %d criado", tid);
	 
	for (int amount = 0; amount < 1000; amount++) {
		nanvix_semaphore_down(&cheio);
		nanvix_semaphore_down(&lock_cons);

		i = (i+1) % SIZE;
		buffer[i] = 0;
		uprintf("consumi no indice %d: %d", i, amount);
		
		nanvix_semaphore_down(&lock_cons);
		nanvix_semaphore_down(&vazio);
//		delay(1, CLUSTER_FREQ);
	}
	kthread_exit(NULL);
	return 0;
}

int __main3(int argc, const char *argv[]) {	
	
	((void) argc);
	((void) argv);
	
	nanvix_semaphore_init(&cheio, 0);
	nanvix_semaphore_init(&vazio, (THREAD_MAX-1)/2);
	nanvix_semaphore_init(&lock_prod, 1);
	nanvix_semaphore_init(&lock_cons, 1);
	
	kthread_t tid[THREAD_MAX - 1];
	int virtual_tid[THREAD_MAX - 1];

	int cons = NCONSUMERS;
	int prod = NPRODUCERS;
	int n, d = 0;

	for (; n < NCONSUMERS; ++n) {
		virtual_tid[n] = n;
		uassert(kthread_create(&tid[n], consumer, ((void * ) &virtual_tid[n])) == 0);
}
	for (; n < NCONSUMERS + NPRODUCERS; ++n) { 
		virtual_tid[n] = n;
		uassert(kthread_create(&tid[n], producer, ((void * ) &virtual_tid[n])) == 0);
}
	for (d = 0; i <cons+prod; ++d) {
		kthread_join(tid[d], NULL);	
}
	//kthread_exit(NULL);
	return (0);

}


