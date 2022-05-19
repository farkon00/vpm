#include<stdlib.h>

#ifndef STRINGVIEW_H_
#define STRINGVIEW_H_

/* TODO */
typedef struct {
	size_t count;
	char* contents;
} String_View;

String_View cstr_to_sv(const char* cstr);

#endif //STRINGVIEW_H_
