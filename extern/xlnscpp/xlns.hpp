#pragma once

#include <cstdint>
#include <iosfwd>

// Shared masks and helpers for 16-bit XLNS
#ifdef _WIN32
using xlns16 = unsigned __int16;
using xlns16_signed = __int16;
#else
// u_int16_t lives in <sys/types.h> on some libc implementations.
#include <sys/types.h>
using xlns16 = u_int16_t;
using xlns16_signed = int16_t;
#endif

#define xlns16_zero          0x0000
#define xlns16_scale         0x0080
#define xlns16_logmask       0x7fff
#define xlns16_signmask      0x8000
#define xlns16_logsignmask   0x4000
#define xlns16_canonmask     0x8000
#define xlns16_sqrtmask      0x2000
#define xlns16_esszer        0x0500
#define xlns16_canonshift    15

#define xlns16_sign(x)  ((x) & xlns16_signmask)
#define xlns16_neg(x)   ((x) ^ xlns16_signmask)
#define xlns16_abs(x)   ((x) & xlns16_logmask)
#define xlns16_recip(x) (xlns16_sign(x)|xlns16_abs((~x)+1))
#define xlns16_sqrt(x)   (xlns16_abs(((xlns16_signed)((x)<<1))/4)^xlns16_sqrtmask)
#define xlns16_canon(x) ((x)^(-((x)>>xlns16_canonshift)|xlns16_signmask))

xlns16 xlns16_mul(xlns16 x, xlns16 y);
xlns16 xlns16_div(xlns16 x, xlns16 y);
xlns16 xlns16_add(xlns16 x, xlns16 y);
#define xlns16_sub(x,y) xlns16_add(x,xlns16_neg(y))

xlns16 fp2xlns16(float x);
float xlns162fp(xlns16 x);

class xlns16_float {
    xlns16 x;
 public:
    friend xlns16_float operator+(xlns16_float , xlns16_float );
    friend xlns16_float operator+(float, xlns16_float );
    friend xlns16_float operator+(xlns16_float , float);
    friend xlns16_float operator-(xlns16_float , xlns16_float );
    friend xlns16_float operator-(float, xlns16_float );
    friend xlns16_float operator-(xlns16_float , float);
    friend xlns16_float operator*(xlns16_float , xlns16_float );
    friend xlns16_float operator*(float, xlns16_float );
    friend xlns16_float operator*(xlns16_float , float);
    friend xlns16_float operator/(xlns16_float , xlns16_float );
    friend xlns16_float operator/(float, xlns16_float );
    friend xlns16_float operator/(xlns16_float , float);
    xlns16_float operator=(float);
    friend xlns16 xlns16_internal(xlns16_float );
    friend float xlns16_2float(xlns16_float );
    friend xlns16_float float2xlns16_(float);
    friend std::ostream& operator<<(std::ostream&, xlns16_float );
    friend xlns16_float operator-(xlns16_float);
    friend xlns16_float operator+=(xlns16_float &, xlns16_float);
    friend xlns16_float operator+=(xlns16_float &, float);
    friend xlns16_float operator-=(xlns16_float &, xlns16_float);
    friend xlns16_float operator-=(xlns16_float &, float);
    friend xlns16_float operator*=(xlns16_float &, xlns16_float);
    friend xlns16_float operator*=(xlns16_float &, float);
    friend xlns16_float operator/=(xlns16_float &, xlns16_float);
    friend xlns16_float operator/=(xlns16_float &, float);
    friend xlns16_float sin(xlns16_float);
    friend xlns16_float cos(xlns16_float);
    friend xlns16_float exp(xlns16_float);
    friend xlns16_float log(xlns16_float);
    friend xlns16_float atan(xlns16_float);
    friend xlns16_float abs(xlns16_float);
    friend xlns16_float sqrt(xlns16_float);
    friend int operator==(xlns16_float arg1, xlns16_float arg2);
    friend int operator!=(xlns16_float arg1, xlns16_float arg2);
    friend int operator<=(xlns16_float arg1, xlns16_float arg2);
    friend int operator>=(xlns16_float arg1, xlns16_float arg2);
    friend int operator<(xlns16_float arg1, xlns16_float arg2);
    friend int operator>(xlns16_float arg1, xlns16_float arg2);
    friend int operator==(xlns16_float arg1, float arg2);
    friend int operator!=(xlns16_float arg1, float arg2);
    friend int operator<=(xlns16_float arg1, float arg2);
    friend int operator>=(xlns16_float arg1, float arg2);
    friend int operator<(xlns16_float arg1, float arg2);
    friend int operator>(xlns16_float arg1, float arg2);
};

xlns16 xlns16_internal(xlns16_float y);
float xlns16_2float(xlns16_float y);
xlns16_float float2xlns16_(float y);

#define xlns16_cachesize 1024
extern xlns16 xlns16_cachecontent[xlns16_cachesize];
extern float xlns16_cachetag[xlns16_cachesize];
extern long xlns16_misses;
extern long xlns16_hits;


// Shared masks and helpers for 32-bit XLNS
#ifdef xlns32_arch16
  typedef unsigned long xlns32;
  typedef signed long xlns32_signed;
  #define xlns32_zero          0x00000000L
  #define xlns32_scale         0x00800000L
  #define xlns32_logmask       0x7fffffffL
  #define xlns32_signmask      0x80000000L
  #define xlns32_logsignmask   0x40000000L
  #define xlns32_canonmask     0x80000000L
  #define xlns32_sqrtmask      0x20000000L
  #define xlns32_esszer        0x0cfa0000L
  #define xlns32_canonshift    31
#else
  typedef unsigned int xlns32;
  typedef signed int xlns32_signed;
  #define xlns32_zero          0x00000000
  #define xlns32_scale         0x00800000
  #define xlns32_logmask       0x7fffffff
  #define xlns32_signmask      0x80000000
  #define xlns32_logsignmask   0x40000000
  #define xlns32_canonmask     0x80000000
  #define xlns32_sqrtmask      0x20000000
  #define xlns32_esszer        0x0cfa0000
  #define xlns32_canonshift    31
#endif

#define xlns32_sign(x)  ((x) & xlns32_signmask)
#define xlns32_neg(x)   ((x) ^ xlns32_signmask)
#define xlns32_abs(x)   ((x) & xlns32_logmask)
#define xlns32_recip(x) (xlns32_sign(x)|xlns32_abs((~x)+1))
#define xlns32_sqrt(x)   (xlns32_abs(((xlns32_signed)((x)<<1))/4)^xlns32_sqrtmask)
#define xlns32_canon(x) ((x)^(-((x)>>xlns32_canonshift)|xlns32_signmask))

xlns32 xlns32_mul(xlns32 x, xlns32 y);
xlns32 xlns32_div(xlns32 x, xlns32 y);
xlns32 xlns32_add(xlns32 x, xlns32 y);
#define xlns32_sub(x,y) xlns32_add(x,xlns32_neg(y))

xlns32 fp2xlns32(float x);
float xlns322fp(xlns32 x);

class xlns32_float {
    xlns32 x;
 public:
    friend xlns32_float operator+(xlns32_float , xlns32_float );
    friend xlns32_float operator+(float, xlns32_float );
    friend xlns32_float operator+(xlns32_float , float);
    friend xlns32_float operator-(xlns32_float , xlns32_float );
    friend xlns32_float operator-(float, xlns32_float );
    friend xlns32_float operator-(xlns32_float , float);
    friend xlns32_float operator*(xlns32_float , xlns32_float );
    friend xlns32_float operator*(float, xlns32_float );
    friend xlns32_float operator*(xlns32_float , float);
    friend xlns32_float operator/(xlns32_float , xlns32_float );
    friend xlns32_float operator/(float, xlns32_float );
    friend xlns32_float operator/(xlns32_float , float);
    xlns32_float operator=(float);
    friend xlns32 xlns32_internal(xlns32_float );
    friend float xlns32_2float(xlns32_float );
    friend xlns32_float float2xlns32_(float);
    friend std::ostream& operator<<(std::ostream&, xlns32_float );
    friend xlns32_float operator-(xlns32_float);
    friend xlns32_float operator+=(xlns32_float &, xlns32_float);
    friend xlns32_float operator+=(xlns32_float &, float);
    friend xlns32_float operator-=(xlns32_float &, xlns32_float);
    friend xlns32_float operator-=(xlns32_float &, float);
    friend xlns32_float operator*=(xlns32_float &, xlns32_float);
    friend xlns32_float operator*=(xlns32_float &, float);
    friend xlns32_float operator/=(xlns32_float &, xlns32_float);
    friend xlns32_float operator/=(xlns32_float &, float);
    friend xlns32_float sin(xlns32_float);
    friend xlns32_float cos(xlns32_float);
    friend xlns32_float exp(xlns32_float);
    friend xlns32_float log(xlns32_float);
    friend xlns32_float atan(xlns32_float);
    friend xlns32_float abs(xlns32_float);
    friend xlns32_float sqrt(xlns32_float);
    friend int operator==(xlns32_float arg1, xlns32_float arg2);
    friend int operator!=(xlns32_float arg1, xlns32_float arg2);
    friend int operator<=(xlns32_float arg1, xlns32_float arg2);
    friend int operator>=(xlns32_float arg1, xlns32_float arg2);
    friend int operator<(xlns32_float arg1, xlns32_float arg2);
    friend int operator>(xlns32_float arg1, xlns32_float arg2);
    friend int operator==(xlns32_float arg1, float arg2);
    friend int operator!=(xlns32_float arg1, float arg2);
    friend int operator<=(xlns32_float arg1, float arg2);
    friend int operator>=(xlns32_float arg1, float arg2);
    friend int operator<(xlns32_float arg1, float arg2);
    friend int operator>(xlns32_float arg1, float arg2);
};

xlns32 xlns32_internal(xlns32_float y);
float xlns32_2float(xlns32_float y);
xlns32_float float2xlns32_(float y);

#define xlns32_cachesize 1024
extern xlns32 xlns32_cachecontent[xlns32_cachesize];
extern float xlns32_cachetag[xlns32_cachesize];
extern long xlns32_misses;
extern long xlns32_hits;
