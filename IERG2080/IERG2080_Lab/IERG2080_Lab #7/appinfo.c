#include <stdio.h>

#define MAX_APPNAME 256

struct AppInfo {
    char AppName[MAX_APPNAME+1];    // Length limited to MAX_APPNAME. The extra byte is for null.
    unsigned long AppSize;          // Size is non-negative integer,
                                    // unsigned long allows app size up to
                                    // LONG_MAX bytes which should be sufficient.
    double AppVersion;              // Use double for higher precision.
    unsigned long Downloads;        // Size is non-negative integer,
                                    // unsigned long allows app size up to
                                    // LONG_MAX bytes which should be sufficient.
    double Price;                   // Use double for higher precision.
    char AppID[MAX_APPNAME+1];      // Length limited to MAX_APPNAME. The extra byte is for null.
    };


int main() {
    struct AppInfo someApp;// Define an instance
    printf("AppName = %s\n", someApp.AppName);
    printf("AppSize = %lu bytes\n", someApp.AppSize);
    printf("AppVersion = %.1f\n", someApp.AppVersion);
    printf("Downloads = %ld\n", someApp.Downloads);
    printf("Price = %0.2f\n", someApp.Price);
    printf("AppID  = %s", someApp.AppID);
    return 0;
}
