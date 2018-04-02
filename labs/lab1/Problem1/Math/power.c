
/* Power function */
long long power(int base, int exponent)
{
    // write your code here
    long long result=1;
    for (size_t i = 0; i < exponent; i++) {
      /* code */
      result*=base;
    }
    return result;
}
