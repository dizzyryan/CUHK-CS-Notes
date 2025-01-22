/* DigitsAdd()
* Add two numbers.
* Parameters: outdigits/numoutdigits – pointer/size of output number
* 	      indigits1/numdigits1 – pointer/size of 1st input number
* 	      indigits1/numdigits1 – pointer/size of 2nd input number
* Return : 0 on success
* 	   -1 on overflow (result longer than output numbers size)
* 	   -2 on digits==NULL
*/

int DigitsAdd(char *outdigits, size_t numoutdigits,
              char const *indigits1, size_t numdigits1,
              char const *indigits2, size_t numdigits2) {
    if (outdigits == NULL) {
        return -2;
    }

    size_t maxDigits = (numdigits1 > numdigits2) ? numdigits1 : numdigits2;
    size_t resultLength = maxDigits + 1;

    if (resultLength > numoutdigits) {
        return -1;
    }

    for (size_t i = 0; i < numoutdigits - 1; i++) {
        outdigits[i] = '0';
    }
    outdigits[numoutdigits - 1] = '\0';

    int carry = 0;
    for (size_t i = 0; i < maxDigits; i++) {
        int digit1 = (i < numdigits1) ? indigits1[numdigits1 - i - 1] - '0' : 0;
        int digit2 = (i < numdigits2) ? indigits2[numdigits2 - i - 1] - '0' : 0;
        int sum = digit1 + digit2 + carry;

        carry = sum / 10;
        sum %= 10;

        outdigits[numoutdigits - i - 2] = sum + '0';
    }

    if (carry == 1) {
        outdigits[0] = '1';
        
    }

    return 0;
}
