#include <stdio.h>
#include "strlib.h"

/* StringLength()
* Return the length in chars of the input string str.
* Return 0 upon str==NULL.
*/
size_t StringLength(char const *str){
    int i, length = 0;
    for (i = 0; str[i] != '\0'; i++)
        length++;
    return length;
}

int offset(int offsetno){
    return offsetno;
}

/* FindString()
* Find the first occurrence of a substring (needle) within a string
* (haystack).
* Input Arguments:
* - haystack : string to be searched.
* - haystacklen : length of haystack to be searched.
* - needle : substring to search for.
* - needlelen : length of substring.
* - firstpos : store the address of the first occurrence of the
* substring, NULL if not exist.
* Return address of the first occurrence of the substring,
* NULL if not exist or invalid argument(s).
*/
char *FindString(const char *haystack, size_t haystacklen,
                 const char *needle, size_t needlelen, char **firstpos, size_t *offsetno){
    size_t i = 0, j = 0;

    if (needlelen > haystacklen){
        *firstpos = NULL;
        return NULL;
    }

    if (haystack == NULL || haystacklen == 0 || needle == NULL || needlelen == 0){
        *firstpos = NULL;
        return NULL;
    }

    for (i = 0; i < (haystacklen - needlelen); i++){
        int check = 1;
        for (j = 0; j < needlelen; j++){
            if (*(haystack+i+j) != *(needle+j)){
                check = 0;
                break;
            }
        }
        if (check){
            *firstpos = (char *)(haystack + i);
            *offsetno = i;
            return *firstpos;
        }

    }
*firstpos = NULL;
return NULL;
}

