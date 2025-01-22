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
    struct AppInfo someApp;// Define an instance
    strcpy(someApp.AppName, "Hello World!");
    someApp.AppSize = 10240;
    someApp.AppVersion = 1.0;
    someApp.Downloads = 0;
    someApp.Price = 9.99*100*discount;
    strcpy(someApp.AppID , "0000002080");
    printf("AppName = %s\n", someApp.AppName);
    printf("AppSize = %lu bytes\n", someApp.AppSize);
    printf("AppVersion = %.1f\n", someApp.AppVersion);
    printf("Downloads = %ld\n", someApp.Downloads);
    printf("Price = %0.2f\n", (double)someApp.Price/100);
    printf("AppID  = %s", someApp.AppID);
    return 0;
}

// it will always round down.
