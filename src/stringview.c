#include <stdlib.h>
#include <string.h>

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


