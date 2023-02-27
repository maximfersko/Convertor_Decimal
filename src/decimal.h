#ifndef SRC_decimal_H_
#define SRC_decimal_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "limits.h"
#include "time.h"

typedef enum {
  NORMAL_VALUE = 0,
  INFINITYD = 1,
  NEGATIVE_INFINITYD = 2,
  NAND = 3
} value_type_t;

typedef struct {
  int bits[4];
  value_type_t value_type;
} decimal;


typedef enum { LOW, MID, HIGH, SCALE } value;

#define M 2147483647
#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define ERROR 1
#define SIZE 25
#define MAX_BIT 2147483648u
#define SIGN 0x80000000



int from_decimal_to_int(decimal src, int *dst);
int from_decimal_to_float(decimal src, float *dst);
int from_int_to_decimal(int src, decimal *dst);
int from_float_to_decimal(float src, decimal *dst);
int int_to_dec(int src, decimal *dst);
int unsetbit(const int value, const int position);
int isInfinity(decimal dec);
int isNAND(decimal dec);
int isNegative(decimal dec);
int isNormal(decimal dec);
void setBitZero(int position, decimal *dec);
int getScale(decimal dec);
int get_sign(decimal dec);
void decZero(decimal *dec);
int isEmpty(decimal d);
decimal set_scale(decimal *dec, int scale);
void setSign(decimal *d, int set);
decimal truncate(decimal dec);
int getBit(decimal dec, int i);
int setBit(unsigned int num, int index);
int getExpFloat(float num);
void setBitS(int position, decimal *dec);
int getSloatSign(float *src);
int isNegInf(decimal dec);
int getFloatSign(float *src);
void printBinaryFloat(float num);
int getExpFloat(float num);
void set_sign(int sign, decimal *dec);


#endif  // SRC_decimal_H_
