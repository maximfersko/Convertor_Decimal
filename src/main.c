#include "decimal.h"

int main() {
    float a = 7.8;
    decimal dec;
    from_float_to_decimal(a, &dec);
    return 0;
}