#include "decimal.h"

int from_int_to_decimal(int src, decimal *dst) {
  int result = ERROR;
  if (dst != NULL) {
    decZero(dst);
    if (src < 0) {
      dst->bits[SCALE] |= 0x80000000;
      src *= -1;
    }
    dst->bits[LOW] = src;
    dst->value_type = NORMAL_VALUE;
    result = SUCCESS;
  }
  return result;
}

int from_float_to_decimal(float src, decimal *dst) {
  decZero(dst);
  int sign = getFloatSign(&src), result = ERROR;
  if (isinf(src)) {
    dst->value_type = INFINITYD;
  } else if (isinf(src) && sign) {
    dst->value_type = NEGATIVE_INFINITYD;
  } else if (isnan(src)) {
    dst->value_type = NAND;
  } else {
    dst->value_type = NORMAL_VALUE;
  }

  if (dst && dst->value_type == NORMAL_VALUE) {
    int exp = getExpFloat(src), scale = 0;
    double tmp = (double)src;
    if (exp > 95) dst->value_type = INFINITYD;
    if (fabs(src) > 7.922816251e28F) result = ERROR;
    if (exp > -95 && exp < 95) {
      for (; !(int)tmp; tmp *= 10, scale++) {
      }
    }
    for (int i = 0; !(((int)tmp) / 10000000) && scale < 28;
         tmp *= 10, i++, scale++) {
    }
    src = (float)tmp;
    exp = getExpFloat(src);
    setBitS(exp, dst);
    unsigned int fbits = *((unsigned int *)&src);
    unsigned int mask = 0x400000;
    int fl = exp - 1;
    for (; fl >= 0; fl--, mask >>= 1) {
      if (mask & fbits) setBitS(fl, dst);
    }
    set_scale(dst, scale);
    if (sign) set_sign(TRUE, dst);
  }
  return result;
}

int from_decimal_to_int(decimal src, int *dst) {
  int result = ERROR;
  if (isNormal(src) == TRUE) {
    int sign = get_sign(src);
    src = truncate(src);
    if (!src.bits[MID] && !src.bits[HIGH] && dst && *dst <= INT_MAX) {
      *dst = 0;
      *dst = src.bits[LOW];
      if (sign == TRUE) *dst *= -1;
      result = SUCCESS;
    }
  }
  return result;
}

int from_decimal_to_float(decimal src, float *dst) {
  int result = ERROR;
  if (isNormal(src) == TRUE && dst != NULL) {
    *dst = 0.0;
    int sign = get_sign(src), scale = getScale(src);
    double tmp = 0;
    for (int i = 0; i < 96; i++) {
      if (getBit(src, i)) tmp += pow(2, i);
    }
    if (scale != 0) {
      for (int i = 0; i < scale; i++) {
        tmp /= 10;
      }
    }
    *dst = tmp;
    if (sign) *dst = -*dst;
    result = SUCCESS;
  } else if (isInfinity(src) == TRUE) {
    *dst = INFINITYD;
  } else if (isNegInf(src) == TRUE) {
    *dst = -INFINITYD;
  } else if (isNAND(src) == TRUE) {
    *dst = NAND;
  }
  return result;
}
