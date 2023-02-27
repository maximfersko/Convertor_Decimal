#include "decimal.h"
      
int isNegInf(decimal dec) {
  return dec.value_type == NEGATIVE_INFINITYD ? TRUE : FALSE;
}

int getScale(decimal dec) {
  dec.bits[3] = unsetbit(dec.bits[3], 31);
  int scale = dec.bits[3] >> 16;
  return scale;
}

int get_sign(decimal dec) { return !!(dec.bits[3] & 0x80000000); }


int getBit(decimal dec, int i) {
  unsigned int mask = 1U << (i % 32);
  return ((dec.bits[i / 32] & (mask)) != 0);
}

int isNAND(decimal dec) { return dec.value_type == NAND ? TRUE : FALSE; }

int isNormal(decimal dec) {
  return dec.value_type == NORMAL_VALUE ? TRUE : FALSE;
}

decimal set_scale(decimal *dec, int scale) {
  dec->bits[SCALE] = (scale << 16);
  return *dec;
}

int isInfinity(decimal dec) {
  int flag = FALSE;
  if (dec.value_type == INFINITYD ||
      dec.value_type == NEGATIVE_INFINITYD) {
    flag = TRUE;
  }
  return flag;
}

void setBitS(int position, decimal *dec) {
  unsigned int x = position / 32;
  unsigned int y = position % 32;
  dec->bits[x] |= (1u << y);
}  


void decZero(decimal *d) {
  d->bits[LOW] = d->bits[MID] = d->bits[HIGH] = d->bits[SCALE] = 0;
}

int getFloatSign(float *src) { return *(int *)src >> 31; }

void printBinaryFloat(float num) {
  unsigned int fbits = *((unsigned int *)&num);
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    printf("%d", !!(fbits & mask));
  }
}

int getExpFloat(float num) {
  unsigned int fbits = *((unsigned int *)&num);
  unsigned int mask = 0x7F800000;
  unsigned int result = ((mask & fbits) >> 23) - 127;
  return result;
}

void set_sign(int sign, decimal *dec) {
  if (sign == FALSE) {
    setBitZero(127, dec);
  } else if (sign == TRUE) {
    setBitS(127, dec);
  }
}

void setBitZero(int position, decimal *dec) {
  unsigned int x = position / 32;
  unsigned int y = position % 32;
  dec->bits[x] &= ~(1u << y);
}

int unsetbit(const int value, const int position) {
  return (value & ~(1U << position));
}


decimal div_10(decimal dec) {
  decimal res = {0, 0, 0, 0};
  int n = 0; 
  for (int i = 0; i <= 96; i++) {
    n = n * 2 + getBit(dec, 96 - i);
    if (n >= 10) {
      setBitS(96 - i, &res);
      n = n - 10;
    } else {
      setBitZero(96 - i, &res);
    }
  }
  res = set_scale(&res, getScale(dec) - 1);
  return res;
}



decimal truncate(decimal dec) {
  unsigned tmp = dec.value_type;
  if (isNormal(dec)) {
    if (tmp) {
      dec.value_type = tmp;
    } else {
      while (getScale(dec)) {
        int scale = (int)dec.bits[3];
        dec = div_10(dec);
        dec.bits[3] = scale - 0x10000;
      }
    }
  } else {
    decZero(&dec);
  }
  return dec;
}
