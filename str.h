/*
 * str.h - interface to string utilities
 *
 * Copyright (C) 2019 Gordon McNutt
 */

#ifndef str_h
#define str_h

/* Create a string via printf-like syntax. */
char *str_printf(const char *fmt, ...);

/* Create a string by joining other strings with a separator. */
char *str_join(const char *sep, const char **fields);

void str_deref(char *v);

#endif
