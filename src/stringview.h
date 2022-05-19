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

String_View sv_trim_whitespace(String_View sv);
String_View sv_trim_whitespace_left(String_View sv);
String_View sv_trim_whitespace_right(String_View sv);
String_View sv_chop_by_delimiter(String_View *sv, char delimiter);

#endif //STRINGVIEW_H_
