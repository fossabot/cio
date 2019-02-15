/*
 * The MIT License (MIT)
 *
 * Copyright (c) <2017> <Stephan Gatzka>
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

#ifndef CIO_HTTP_SERVER_H
#define CIO_HTTP_SERVER_H

#include <stddef.h>
#include <stdint.h>

#include "cio_error_code.h"
#include "cio_eventloop.h"
#include "cio_export.h"
#include "cio_http_location.h"
#include "cio_server_socket.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * @brief This file contains the declarations you need to know if you
 * want to implement an HTTP server.
 *
 * A cio_http_server gives you the ability to @ref cio_http_server_register "register" multiple
 * @ref cio_http_location "locations" which will be instantianted automatically
 * if an HTTP request matches a location.
 *
 * Inside a @ref cio_http_location_handler "request handler" you can specify lots of callback functions like
 * @ref cio_http_location_handler_on_header_field "on_header_field" or
 * @ref cio_http_location_handler_on_body "on_body" which will be called automatically
 * when an HTTP request is processed by the HTTP server.
 *
 * @note Please note that after you've sent a @ref cio_http_client_write_response, callbacks you've registered
 * in a @ref cio_http_location_handler "request handler"!
 */

struct cio_http_server;

/**
 * @brief The type of an server error function passed to the @ref cio_http_server_init "initialization" of an HTTP server.
 *
 * @param server The cio_http_server that caused the error.
 * @param reason A reason describing the error.
 */
typedef void (*cio_http_serve_on_error)(struct cio_http_server *server, const char *reason);

typedef void (*cio_http_server_close_hook)(struct cio_http_server *server);

#define KEEPALIVE_TIMEOUT_HEADER_MAX_LENGTH 33u // "Keep-Alive: timeout= + uint32 as string + CR + LF + \0"

/**
 * @brief The cio_http_server structure provides the implementation of a simple HTTP server.
 */
struct cio_http_server {

	/**
	 * @brief Start serving HTTP client requests.
	 *
	 * @param server The HTTP server instance that shall serve the requests.
	 * @return ::CIO_SUCCESS if serving runs correctly.
	 */
	enum cio_error (*serve)(struct cio_http_server *server);

	/**
	 * @anchor cio_http_server_register
	 * @brief Register a @ref cio_http_location "location" to the HTTP server.
	 *
	 * If you register overlapping locations like "/foo" and "/foo/bar", the HTTP server
	 * looks for the best match with respect to the path in the HTTP request.
	 *
	 * @param server The HTTP server instance which shall serve the new location.
	 * @param location The location that should be served by the HTTP server.
	 * @return ::CIO_SUCCESS if the @p location was registered correctly.
	 */
	enum cio_error (*register_location)(struct cio_http_server *server, struct cio_http_location *location);

	/**
	 * @anchor cio_http_server_shutdown
	 * @brief Shuts down the HTTP server, including the underlying server socket.
	 *
	 * @param server The HTTP server which should be shut down.
	 * @param close_hook A user provided function that will be called after the HTTP server completed the @ref cio_http_server_shutdown "shutdown".
	 * @return ::CIO_SUCCESS if the shutdown operation succeeded.
	 */
	enum cio_error (*shutdown)(struct cio_http_server *server, cio_http_server_close_hook close_hook);

	/**
	 * @privatesection
	 */
	uint16_t port;
	struct cio_eventloop *loop;
	cio_alloc_client alloc_client;
	cio_free_client free_client;

	uint64_t read_header_timeout_ns;
	uint64_t read_body_timeout_ns;
	uint64_t response_timeout_ns;
	cio_http_serve_on_error on_error;
	struct cio_server_socket server_socket;
	struct cio_http_location *first_handler;
	size_t num_handlers;
	cio_http_server_close_hook close_hook;
	char keepalive_header[KEEPALIVE_TIMEOUT_HEADER_MAX_LENGTH]; // "Keep-Alive: timeout= + uint32 as string + CR + LF + \0"
};

/**
 * @brief Initializes an HTTP server.
 * @param server The cio_http_server that should be initialized.
 * @param port The TCP port the HTTP server listens on.
 * @param loop The eventloop the HTTP server uses.
 * @param on_error This callback function will be called if something goes wrong while the HTTP client connection is established.
 * @param read_header_timeout_ns The timeout in nanoseconds until the complete HTTP header must be received.
 * The timeout is started after the HTTP connection is established and canceled after the complete HTTP header was received.
 * In case of a timeout the client connection is closed automatically.
 * @param read_body_timeout_ns The timeout in nanoseconds until the complete HTTP body must be received.
 * The timeout is started after the HTTP header was received and will be canceled after the complete HTTP message was received.
 * In case of a timeout the client connection is closed automatically.
 * @param response_timeout_ns The timeout in nanoseconds until the complete HTTP response must be sent.
 * @anchor cio_http_server_init_alloc_client
 * @param alloc_client A user provided function responsible to allocate a cio_http_client structure.
 * @anchor cio_http_server_init_free_client
 * @param free_client A user provided function to free the client memory @ref cio_http_server_init_alloc_client "allocated".
 * @return ::CIO_SUCCESS for success.
 */
CIO_EXPORT enum cio_error cio_http_server_init(struct cio_http_server *server,
                                               uint16_t port,
                                               struct cio_eventloop *loop,
                                               cio_http_serve_on_error on_error,
                                               uint64_t read_header_timeout_ns,
                                               uint64_t read_body_timeout_ns,
                                               uint64_t response_timeout_ns,
                                               cio_alloc_client alloc_client,
                                               cio_free_client free_client);

#ifdef __cplusplus
}
#endif

#endif
