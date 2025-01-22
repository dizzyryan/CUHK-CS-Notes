#include <stdio.h>
#include <string.h>
#define MAX_APPNAME 256

struct AppInfo {
    char AppName[MAX_APPNAME+1];
    unsigned long AppSize;
    double AppVersion;
    unsigned long Downloads;
    unsigned long Price;
    char AppID[MAX_APPNAME+1];
    };


int main() {
    double discount = 0.50;
    struct AppInfo someApp, secondApp;
    strcpy(someApp.AppName, "Hello World!");
    strcpy(secondApp.AppName, "Hello World!");
    if (strcmp(someApp.AppName, secondApp.AppName) == 0)
        printf("The two apps have the same name.\n");
    else
        printf("The two apps have different names.\n");
    return 0;
}
