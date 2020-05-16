/*
 * SPDX-License-Identifier: MIT
 *
 * The MIT License (MIT)
 *
 * Copyright (c) <2020> <Stephan Gatzka>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "cio_compiler.h"
#include "cio_error_code.h"
#include "cio_eventloop.h"
#include "cio_uart.h"

static struct cio_eventloop loop;

static void sighandler(int signum)
{
	(void)signum;
	cio_eventloop_cancel(&loop);
}

int main(void)
{
	int ret = EXIT_SUCCESS;
	if (signal(SIGTERM, sighandler) == SIG_ERR) {
		return EXIT_FAILURE;
	}

	if (signal(SIGINT, sighandler) == SIG_ERR) {
		signal(SIGTERM, SIG_DFL);
		return EXIT_FAILURE;
	}

	enum cio_error err = cio_eventloop_init(&loop);
	if (err != CIO_SUCCESS) {
		return EXIT_FAILURE;
	}

	size_t num_uarts = cio_uart_get_number_of_uarts();
	fprintf(stdout, "found %zu uart(s)\n", num_uarts);

	struct cio_uart *uarts;
	size_t alloc_size = sizeof(*uarts) * num_uarts;
	uarts = malloc(alloc_size);
	if (cio_unlikely(uarts == NULL)) {
		ret = EXIT_FAILURE;
		goto malloc_failed;
	}

	size_t detected_ports = 0;
	err = cio_uart_get_ports(uarts, num_uarts, &detected_ports);
	if (cio_unlikely(err != CIO_SUCCESS)) {
		fprintf(stderr, "Could not get UART information!\n");
		ret = EXIT_FAILURE;
		goto get_ports_failed;
	}

	for (size_t i = 0; i < detected_ports; i++) {
		fprintf(stdout, "detected port %zu: %s\n", i, uarts[i].impl.name);
	}

	err = cio_eventloop_run(&loop);
	if (err != CIO_SUCCESS) {
		ret = EXIT_FAILURE;
	}

get_ports_failed:
	free(uarts);
malloc_failed:
	cio_eventloop_destroy(&loop);
	return ret;
}