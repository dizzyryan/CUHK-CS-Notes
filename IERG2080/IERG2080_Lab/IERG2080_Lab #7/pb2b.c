/* DigitsMulti()
* Multiply two numbers.
* Parameters: outdigits/numoutdigits – pointer/size of output number
* 	      indigits1/numdigits1 – pointer/size of 1st input number
* 	      indigits1/numdigits1 – pointer/size of 2nd input number
* Return : 0 on success
* 	   -1 on overflow (result longer than output numbers size)
* 	   -2 on digits==NULL
*/

int DigitsMulti(char *outdigits, size_t numoutdigits,
                char const *indigits1, size_t numdigits1,
                char const *indigits2, size_t numdigits2){
    if (outdigits == NULL) {
        return -2;
    }

    size_t resultLength = numdigits1 + numdigits2;

    if (resultLength > numoutdigits) {
        return -1;
    }

    for (size_t i = 0; i < numoutdigits - 1; i++) {
        outdigits[i] = '0';
    }
    outdigits[numoutdigits - 1] = '\0';

    for (size_t i = 0; i < numdigits1; i++) {
        int carry = 0;
        int digit1 = indigits1[numdigits1 - i - 1] - '0';

        for (size_t j = 0; j < numdigits2; j++) {
            int digit2 = indigits2[numdigits2 - j - 1] - '0';
            int product = digit1 * digit2 + carry;

            carry = product / 10;
            product %= 10;

            size_t index = numoutdigits - i - j - 2;
            int sum = outdigits[index] - '0' + product;

            carry += sum / 10;
            sum %= 10;

            outdigits[index] = sum + '0';
        }

        if (carry > 0) {
            outdigits[numoutdigits - i - numdigits2 - 2] = carry + '0';
        }
    }

    return 0;
}
