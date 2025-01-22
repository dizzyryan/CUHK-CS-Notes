#include <stdio.h>
#include "strlib.h"

#define MAX_LENGTH 1000

int main() {
    char haystack[MAX_LENGTH];
    char needle[MAX_LENGTH];

    printf("Please input haystack string: ");
    fgets(haystack, sizeof(haystack), stdin);
    size_t haystacklen = StringLength(haystack);

    printf("Please input needle string: ");
    fgets(needle, sizeof(needle), stdin);
    size_t needlelen = StringLength(needle);

    printf("Length of haystack = %zu\n", haystacklen);
    printf("Length of needle = %zu\n", needlelen);

    // remove newline character
    if (haystack[haystacklen - 1] == '\n') {
        haystack[haystacklen - 1] = '\0';
        haystacklen--;
    }
    if (needle[needlelen - 1] == '\n') {
        needle[needlelen - 1] = '\0';
        needlelen--;
    }
    size_t offsetno = 0;
    char *firstpos = FindString(haystack, haystacklen, needle, needlelen, &firstpos, &offsetno);



    // Print the result
    if (firstpos != NULL) {
        printf("Found [%s] in offset [%ld].\n",needle, offsetno);
    } else if (firstpos == NULL) {
        printf("Needle string not found.\n");
    }

    return 0;
}
