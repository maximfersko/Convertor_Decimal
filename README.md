# lib_decimal
Implementation of a convertors for working with the Decimal data type

### Convertors 

| Convertor | Function | 
| ------ | ------ |
| From int  | int from_int_to_decimal(int src, decimal *dst) |
| From float  | int from_float_to_decimal(float src, decimal *dst) |
| To int  | int from_decimal_to_int(decimal src, int *dst) |
| To float  | int from_decimal_to_float(decimal src, float *dst) |

Return value - code error:
- 0 - SUCCESS
- 1 - CONVERTING ERROR