#include<stdlib.h>

#ifndef STRINGVIEW_H_
#define STRINGVIEW_H_

/* TODO */
typedef struct {
	size_t count;
	char* contents;
} String_View;

String_View cstr_to_sv(char* cstr);
char *sv_to_cstr(String_View sv);

#endif //STRINGVIEW_H_
