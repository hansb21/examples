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
#include <nanvix/ulib.h>
#include <nanvix/sys/thread.h>
#include <nanvix/sys/semaphore.h>
/*============================================================================*
 * Benchmark Driver                                                           *
 *============================================================================*/

/**
 * @brief Launches a benchmark.
 */

int contador_global = 0;
struct nanvix_semaphore semaphore;

void *Increment() {
	int k;
	for (k = 0; k < 100; k++) { 
		nanvix_semaphore_down(&semaphore);
		contador_global++;
		nanvix_semaphore_up(&semaphore);
	}	
	kthread_exit(NULL);
	return 0;
}
int __main3(int argc, const char *argv[])
{	
	((void) argc);
	((void) argv);
	
	int i, j;
	kthread_t threa[THREAD_MAX - 1];
	nanvix_semaphore_init(&semaphore, THREAD_MAX - 1);

	for (i = 0; i < THREAD_MAX-1; i++) {
		kthread_create(&threa[i], Increment, NULL);
	}
	for (j = 0; j < THREAD_MAX-1; j++) { 
		kthread_join(threa[i], NULL);
	}
	uprintf("Totals Threads: %d", THREAD_MAX - 1);
	uprintf("Global Variable: %d", contador_global);
	return (0);

}

