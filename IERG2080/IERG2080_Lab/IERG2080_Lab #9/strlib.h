#ifndef STRLIB_H_
#define STRLIB_H_

size_t StringLength(char const *str);

char *FindString(const char *haystack, size_t haystacklen,
                 const char *needle, size_t needlelen, char **firstpos, size_t *offsetno);

#endif 
