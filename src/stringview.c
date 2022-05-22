#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stringview.h"

String_View cstr_to_sv(char* cstr)
{
  return (String_View) {
    .count = strlen(cstr) + 1,
    .contents = cstr
  };
}

char *sv_to_cstr(String_View sv)
{
  char *result = malloc(sv.count + 1);
  memcpy(result, sv.contents, sv.count);
  *(result + sv.count) = '\0';
  return result;
}

String_View sv_trim_whitespace(String_View sv)
{
  return sv_trim_whitespace_left(sv_trim_whitespace_right(sv));
}

String_View sv_trim_whitespace_left(String_View sv)
{
  size_t i = 0;

  while (i < sv.count && isspace(sv.contents[i])) {
    ++i;
  }

  return (String_View) {
    .count = sv.count - i,
    .contents = sv.contents + i
  };
}

String_View sv_trim_whitespace_right(String_View sv)
{
  size_t i = 0;
  while (i < sv.count && isspace(sv.contents[sv.count - 1 - i])) {
    ++i;
  }

  return (String_View) {
    .count = sv.count - i,
    .contents = sv.contents
  };
}

String_View sv_chop_by_delimiter(String_View *sv, char delimiter)
{
  size_t i = 0;
  while (i < sv->count && sv->contents[i] != delimiter) {
    i += 1;
  }

  String_View res = {
    .count = i,
    .contents = sv->contents,
  };

  if (i < sv->count) {
    sv->count -= i + 1;
    sv->contents += i + 1;
  } else {
    sv->count -= i;
    sv->contents += i;
  }

  return res;
}

size_t sv_cmp_cstr(String_View sv, char* to_compare)
{
    return strcmp(sv_to_cstr(sv), to_compare);
}
