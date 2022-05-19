#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stringview.h"

String_View cstr_to_sv(char* cstr)
{
  return (String_View) {
    .count = strlen(cstr),
    .contents = cstr
  };
}

char *sv_to_cstr(String_View sv)
{
  char *result = malloc(sv.count);
  memcpy(result, sv.contents, sv.count);
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

