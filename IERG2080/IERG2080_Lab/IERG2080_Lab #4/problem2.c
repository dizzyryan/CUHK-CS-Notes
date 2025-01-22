#include <stdio.h>
#include <stdbool.h>
float pi = -3.1416;
#define pi2 3.1416L

int main() {
	bool b = pi;
	unsigned char uc = pi;
	unsigned short us = pi;
	unsigned int ui = pi;
	unsigned long ul = pi;
	unsigned long long ull = pi;
	char c = pi;
	short s = pi;
	int i = pi;
	long l = pi;
	long long ll = pi;
	float f = pi;
	double d = pi;
	long double ld = pi;
	long double ld2 = pi2;
		
	printf("bool b = %d\n", b);
	printf("unsigned char uc = %u\n", uc);
	printf("unsigned short us = %hu\n", us);
	printf("unsigned int ui = %u\n", ui);
	printf("unsigned long ul = %.lu\n", ul);
	printf("unsigned long long ull = %.llu\n", ull);
	printf("char c = %d\n", c);
	printf("short s = %hi\n", s);
	printf("int i = %i\n", i);
	printf("long l = %ld\n", l);
	printf("long long ll = %lli\n", ll);
	printf("float f = %.50f\n", f);
	printf("double d = %.50lf\n", d);
	printf("long double ld = %.50Lf\n", ld);
	printf("long double ld2 = %.50Lf\n", ld2);
	
	return 0;
}
