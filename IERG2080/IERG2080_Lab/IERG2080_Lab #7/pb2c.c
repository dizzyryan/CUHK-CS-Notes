/* DigitsEqual()
* CHeck if two numbers are equal.
* Parameters: indigits1/numdigits1 – pointer/size of 1st input number
*	      indigits1/numdigits1 – pointer/size of 2nd input number
* Return : 0 on not equal
* 	   1 on equal
*/

int DigitsEqual(char const *indigits1, size_t numdigits1,
                char const *indigits2, size_t numdigits2) {
    if (numdigits1 != numdigits2) {
        return 0;
    }

    for (size_t i = 0; i < numdigits1; i++) {
        if (indigits1[i] != indigits2[i]) {
            return 0;
        }
    }

    return 1;
}

