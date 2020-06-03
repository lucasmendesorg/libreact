/*
	Observables for C
		(c) 2020 Lucas Mendes <lucas AT lucasmendes.org>
*/

#include <stdio.h>
#include <stdarg.h>
#include <libreact.h>

int debugf(const char *who, const char *fmt, ...) {
	va_list args;
	char buffer[4096];
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	if(!who) who = "";
	return printf("%24s - %s\n", who, buffer);
}
