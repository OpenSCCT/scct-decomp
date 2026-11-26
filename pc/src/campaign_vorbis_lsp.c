/* C runtime declarations come from the Visual C++ standard headers. */
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Disable the CRT's non-standard min/max macros. */
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

/* Initialized file-scope tables are declared __declspec(selectany) instead of
   static, so each is its own external contribution bound to the retail table. */
/* Writable tables (COS_LOOKUP, INVSQ_LOOKUP, INVSQ2EXP_LOOKUP, FROMdB_LOOKUP, FROMdB2_LOOKUP, INVSQ_LOOKUP_I, COS_LOOKUP_I, MLOOP_1, MLOOP_2, MLOOP_3) are declared extern and bound to
   their retail copies; each library definition follows under #if 0. */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2002             *
 * by the XIPHOPHORUS Company http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

  function: LSP (also called LSF) conversion routines
  last mod: $Id: lsp.c,v 1.22 2002/07/17 21:28:37 xiphmont Exp $

  The LSP generation code is taken (with minimal modification and a
  few bugfixes) from "On the Computation of the LSP Frequencies" by
  Joseph Rothweiler <rothwlr@altavista.net>, available at:

  http://www2.xtdl.com/~rothwlr/lsfpaper/lsfpage.html

 ********************************************************************/

/* Note that the lpc-lsp conversion finds the roots of polynomial with
   an iterative root polisher (CACM algorithm 283).  It *is* possible
   to confuse this algorithm into not converging; that should only
   happen with absurdly closely spaced roots (very sharp peaks in the
   LPC f response) which in turn should be impossible in our use of
   the code.  If this *does* happen anyway, it's a bug in the floor
   finder; find the cause of the confusion (probably a single bin
   spike or accidental near-float-limit resolution problems) and
   correct it. */

/* #include <math.h> : included above */
/* #include <string.h> : included above */
/* #include <stdlib.h> : included above */
/* ---- lsp.h ---- */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2002             *
 * by the XIPHOPHORUS Company http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

  function: LSP (also called LSF) conversion routines
  last mod: $Id: lsp.h,v 1.11 2002/07/11 06:40:49 xiphmont Exp $

 ********************************************************************/


#ifndef _V_LSP_H_
#define _V_LSP_H_

extern int vorbis_lpc_to_lsp(float *lpc,float *lsp,int m);

extern void vorbis_lsp_to_curve(float *curve,int *map,int n,int ln,
                                float *lsp,int m,
                                float amp,float ampoffset);

#endif

/* ---- end lsp.h ---- */
#include "campaign_vorbis_os.h"
/* ---- lookup.h ---- */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2002             *
 * by the XIPHOPHORUS Company http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

  function: lookup based functions
  last mod: $Id: lookup.h,v 1.7 2002/07/11 06:40:49 xiphmont Exp $

 ********************************************************************/

#ifndef _V_LOOKUP_H_

#ifdef FLOAT_LOOKUP
extern float vorbis_coslook(float a);
extern float vorbis_invsqlook(float a);
extern float vorbis_invsq2explook(int a);
extern float vorbis_fromdBlook(float a);
#endif
#ifdef INT_LOOKUP
extern long vorbis_invsqlook_i(long a,long e);
extern long vorbis_coslook_i(long a);
extern float vorbis_fromdBlook_i(long a);
#endif

#endif

/* ---- end lookup.h ---- */
/* ---- scales.h ---- */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2002             *
 * by the XIPHOPHORUS Company http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: linear scale -> dB, Bark and Mel scales
 last mod: $Id: scales.h,v 1.26 2002/07/11 06:40:50 xiphmont Exp $

 ********************************************************************/

#ifndef _V_SCALES_H_
#define _V_SCALES_H_

/* #include <math.h> : included above */

/* 20log10(x) */
#define VORBIS_IEEE_FLOAT32 1
#ifdef VORBIS_IEEE_FLOAT32

static float unitnorm(float x){
  ogg_uint32_t *ix=(ogg_uint32_t *)&x;
  *ix=(*ix&0x80000000UL)|(0x3f800000UL);
  return(x);
}

static float FABS(float *x){
  ogg_uint32_t *ix=(ogg_uint32_t *)x;
  *ix&=0x7fffffffUL;
  return(*x);
}

static float todB(const float *x){
  float calc;
  ogg_int32_t *i=(ogg_int32_t *)x;
  calc = ((*i) & 0x7fffffff);
  calc *= 7.1771144e-7f;
  calc += -764.27118f;
  return calc;
}

#define todB_nn(x) todB(x)

#else

static float unitnorm(float x){
  if(x<0)return(-1.f);
  return(1.f);
}

#define FABS(x) fabs(*(x))

#define todB(x)   (*(x)==0?-400.f:log(*(x)**(x))*4.34294480f)
#define todB_nn(x)   (*(x)==0.f?-400.f:log(*(x))*8.6858896f)

#endif

#define fromdB(x) (exp((x)*.11512925f))

/* The bark scale equations are approximations, since the original
   table was somewhat hand rolled.  The below are chosen to have the
   best possible fit to the rolled tables, thus their somewhat odd
   appearance (these are more accurate and over a longer range than
   the oft-quoted bark equations found in the texts I have).  The
   approximations are valid from 0 - 30kHz (nyquist) or so.

   all f in Hz, z in Bark */

#define toBARK(n)   (13.1f*atan(.00074f*(n))+2.24f*atan((n)*(n)*1.85e-8f)+1e-4f*(n))
#define fromBARK(z) (102.f*(z)-2.f*pow(z,2.f)+.4f*pow(z,3.f)+pow(1.46f,z)-1.f)
#define toMEL(n)    (log(1.f+(n)*.001f)*1442.695f)
#define fromMEL(m)  (1000.f*exp((m)/1442.695f)-1000.f)

/* Frequency to octave.  We arbitrarily declare 63.5 Hz to be octave
   0.0 */

#define toOC(n)     (log(n)*1.442695f-5.965784f)
#define fromOC(o)   (exp(((o)+5.965784f)*.693147f))

#endif


/* ---- end scales.h ---- */

/* three possible LSP to f curve functions; the exact computation
   (float), a lookup based float implementation, and an integer
   implementation.  The float lookup is likely the optimal choice on
   any machine with an FPU.  The integer implementation is *not* fixed
   point (due to the need for a large dynamic range and thus a
   seperately tracked exponent) and thus much more complex than the
   relatively simple float implementations. It's mostly for future
   work on a fully fixed point implementation for processors like the
   ARM family. */

/* undefine both for the 'old' but more precise implementation */
#define   FLOAT_LOOKUP
#undef    INT_LOOKUP

#ifdef FLOAT_LOOKUP
/* ---- lookup.c ---- */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2002             *
 * by the XIPHOPHORUS Company http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

  function: lookup based functions
  last mod: $Id: lookup.c,v 1.9 2002/01/22 08:06:07 xiphmont Exp $

 ********************************************************************/

/* #include <math.h> : included above */
/* ---- lookup_data.h ---- */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2002             *
 * by the XIPHOPHORUS Company http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

  function: lookup data; generated by lookups.pl; edit there
  last mod: $Id: lookup_data.h,v 1.9 2002/07/11 06:40:49 xiphmont Exp $

 ********************************************************************/

#ifndef _V_LOOKUP_DATA_H_

#ifdef FLOAT_LOOKUP
#define COS_LOOKUP_SZ 128
extern float COS_LOOKUP[COS_LOOKUP_SZ+1];
#if 0 /* the library definition; the retail copy is bound instead */
static float COS_LOOKUP[COS_LOOKUP_SZ+1]={
        +1.0000000000000f,+0.9996988186962f,+0.9987954562052f,+0.9972904566787f,
        +0.9951847266722f,+0.9924795345987f,+0.9891765099648f,+0.9852776423889f,
        +0.9807852804032f,+0.9757021300385f,+0.9700312531945f,+0.9637760657954f,
        +0.9569403357322f,+0.9495281805930f,+0.9415440651830f,+0.9329927988347f,
        +0.9238795325113f,+0.9142097557035f,+0.9039892931234f,+0.8932243011955f,
        +0.8819212643484f,+0.8700869911087f,+0.8577286100003f,+0.8448535652497f,
        +0.8314696123025f,+0.8175848131516f,+0.8032075314806f,+0.7883464276266f,
        +0.7730104533627f,+0.7572088465065f,+0.7409511253550f,+0.7242470829515f,
        +0.7071067811865f,+0.6895405447371f,+0.6715589548470f,+0.6531728429538f,
        +0.6343932841636f,+0.6152315905806f,+0.5956993044924f,+0.5758081914178f,
        +0.5555702330196f,+0.5349976198871f,+0.5141027441932f,+0.4928981922298f,
        +0.4713967368260f,+0.4496113296546f,+0.4275550934303f,+0.4052413140050f,
        +0.3826834323651f,+0.3598950365350f,+0.3368898533922f,+0.3136817403989f,
        +0.2902846772545f,+0.2667127574749f,+0.2429801799033f,+0.2191012401569f,
        +0.1950903220161f,+0.1709618887603f,+0.1467304744554f,+0.1224106751992f,
        +0.0980171403296f,+0.0735645635997f,+0.0490676743274f,+0.0245412285229f,
        +0.0000000000000f,-0.0245412285229f,-0.0490676743274f,-0.0735645635997f,
        -0.0980171403296f,-0.1224106751992f,-0.1467304744554f,-0.1709618887603f,
        -0.1950903220161f,-0.2191012401569f,-0.2429801799033f,-0.2667127574749f,
        -0.2902846772545f,-0.3136817403989f,-0.3368898533922f,-0.3598950365350f,
        -0.3826834323651f,-0.4052413140050f,-0.4275550934303f,-0.4496113296546f,
        -0.4713967368260f,-0.4928981922298f,-0.5141027441932f,-0.5349976198871f,
        -0.5555702330196f,-0.5758081914178f,-0.5956993044924f,-0.6152315905806f,
        -0.6343932841636f,-0.6531728429538f,-0.6715589548470f,-0.6895405447371f,
        -0.7071067811865f,-0.7242470829515f,-0.7409511253550f,-0.7572088465065f,
        -0.7730104533627f,-0.7883464276266f,-0.8032075314806f,-0.8175848131516f,
        -0.8314696123025f,-0.8448535652497f,-0.8577286100003f,-0.8700869911087f,
        -0.8819212643484f,-0.8932243011955f,-0.9039892931234f,-0.9142097557035f,
        -0.9238795325113f,-0.9329927988347f,-0.9415440651830f,-0.9495281805930f,
        -0.9569403357322f,-0.9637760657954f,-0.9700312531945f,-0.9757021300385f,
        -0.9807852804032f,-0.9852776423889f,-0.9891765099648f,-0.9924795345987f,
        -0.9951847266722f,-0.9972904566787f,-0.9987954562052f,-0.9996988186962f,
        -1.0000000000000f,
};
#endif

#define INVSQ_LOOKUP_SZ 32
extern float INVSQ_LOOKUP[INVSQ_LOOKUP_SZ+1];
#if 0 /* the library definition; the retail copy is bound instead */
static float INVSQ_LOOKUP[INVSQ_LOOKUP_SZ+1]={
        1.414213562373f,1.392621247646f,1.371988681140f,1.352246807566f,
        1.333333333333f,1.315191898443f,1.297771369046f,1.281025230441f,
        1.264911064067f,1.249390095109f,1.234426799697f,1.219988562661f,
        1.206045378311f,1.192569588000f,1.179535649239f,1.166919931983f,
        1.154700538379f,1.142857142857f,1.131370849898f,1.120224067222f,
        1.109400392450f,1.098884511590f,1.088662107904f,1.078719779941f,
        1.069044967650f,1.059625885652f,1.050451462878f,1.041511287847f,
        1.032795558989f,1.024295039463f,1.016001016002f,1.007905261358f,
        1.000000000000f,
};
#endif

#define INVSQ2EXP_LOOKUP_MIN -32
#define INVSQ2EXP_LOOKUP_MAX 32
extern float INVSQ2EXP_LOOKUP[INVSQ2EXP_LOOKUP_MAX-\
                              INVSQ2EXP_LOOKUP_MIN+1];
#if 0 /* the library definition; the retail copy is bound instead */
static float INVSQ2EXP_LOOKUP[INVSQ2EXP_LOOKUP_MAX-\
                              INVSQ2EXP_LOOKUP_MIN+1]={
                 65536.f,    46340.95001f,         32768.f,    23170.47501f,
                 16384.f,     11585.2375f,          8192.f,    5792.618751f,
                  4096.f,    2896.309376f,          2048.f,    1448.154688f,
                  1024.f,    724.0773439f,           512.f,     362.038672f,
                   256.f,     181.019336f,           128.f,    90.50966799f,
                    64.f,      45.254834f,            32.f,      22.627417f,
                    16.f,     11.3137085f,             8.f,    5.656854249f,
                     4.f,    2.828427125f,             2.f,    1.414213562f,
                     1.f,   0.7071067812f,            0.5f,   0.3535533906f,
                   0.25f,   0.1767766953f,          0.125f,  0.08838834765f,
                 0.0625f,  0.04419417382f,        0.03125f,  0.02209708691f,
               0.015625f,  0.01104854346f,      0.0078125f, 0.005524271728f,
             0.00390625f, 0.002762135864f,    0.001953125f, 0.001381067932f,
           0.0009765625f, 0.000690533966f,  0.00048828125f, 0.000345266983f,
         0.000244140625f,0.0001726334915f,0.0001220703125f,8.631674575e-05f,
        6.103515625e-05f,4.315837288e-05f,3.051757812e-05f,2.157918644e-05f,
        1.525878906e-05f,
};
#endif

#endif

#define FROMdB_LOOKUP_SZ 35
#define FROMdB2_LOOKUP_SZ 32
#define FROMdB_SHIFT 5
#define FROMdB2_SHIFT 3
#define FROMdB2_MASK 31
extern float FROMdB_LOOKUP[FROMdB_LOOKUP_SZ];
#if 0 /* the library definition; the retail copy is bound instead */
static float FROMdB_LOOKUP[FROMdB_LOOKUP_SZ]={
                     1.f,   0.6309573445f,   0.3981071706f,   0.2511886432f,
           0.1584893192f,            0.1f,  0.06309573445f,  0.03981071706f,
          0.02511886432f,  0.01584893192f,           0.01f, 0.006309573445f,
         0.003981071706f, 0.002511886432f, 0.001584893192f,          0.001f,
        0.0006309573445f,0.0003981071706f,0.0002511886432f,0.0001584893192f,
                 0.0001f,6.309573445e-05f,3.981071706e-05f,2.511886432e-05f,
        1.584893192e-05f,          1e-05f,6.309573445e-06f,3.981071706e-06f,
        2.511886432e-06f,1.584893192e-06f,          1e-06f,6.309573445e-07f,
        3.981071706e-07f,2.511886432e-07f,1.584893192e-07f,
};
#endif

extern float FROMdB2_LOOKUP[FROMdB2_LOOKUP_SZ];
#if 0 /* the library definition; the retail copy is bound instead */
static float FROMdB2_LOOKUP[FROMdB2_LOOKUP_SZ]={
           0.9928302478f,   0.9786445908f,   0.9646616199f,   0.9508784391f,
           0.9372921937f,     0.92390007f,   0.9106992942f,   0.8976871324f,
           0.8848608897f,   0.8722179097f,   0.8597555737f,   0.8474713009f,
            0.835362547f,   0.8234268041f,   0.8116616003f,   0.8000644989f,
           0.7886330981f,   0.7773650302f,   0.7662579617f,    0.755309592f,
           0.7445176537f,   0.7338799116f,   0.7233941627f,   0.7130582353f,
           0.7028699885f,   0.6928273125f,   0.6829281272f,   0.6731703824f,
           0.6635520573f,   0.6540711597f,   0.6447257262f,   0.6355138211f,
};
#endif

#ifdef INT_LOOKUP

#define INVSQ_LOOKUP_I_SHIFT 10
#define INVSQ_LOOKUP_I_MASK 1023
extern long INVSQ_LOOKUP_I[64+1];
#if 0 /* the library definition; the retail copy is bound instead */
static long INVSQ_LOOKUP_I[64+1]={
           92682l,   91966l,   91267l,   90583l,
           89915l,   89261l,   88621l,   87995l,
           87381l,   86781l,   86192l,   85616l,
           85051l,   84497l,   83953l,   83420l,
           82897l,   82384l,   81880l,   81385l,
           80899l,   80422l,   79953l,   79492l,
           79039l,   78594l,   78156l,   77726l,
           77302l,   76885l,   76475l,   76072l,
           75674l,   75283l,   74898l,   74519l,
           74146l,   73778l,   73415l,   73058l,
           72706l,   72359l,   72016l,   71679l,
           71347l,   71019l,   70695l,   70376l,
           70061l,   69750l,   69444l,   69141l,
           68842l,   68548l,   68256l,   67969l,
           67685l,   67405l,   67128l,   66855l,
           66585l,   66318l,   66054l,   65794l,
           65536l,
};
#endif

#define COS_LOOKUP_I_SHIFT 9
#define COS_LOOKUP_I_MASK 511
#define COS_LOOKUP_I_SZ 128
extern long COS_LOOKUP_I[COS_LOOKUP_I_SZ+1];
#if 0 /* the library definition; the retail copy is bound instead */
static long COS_LOOKUP_I[COS_LOOKUP_I_SZ+1]={
           16384l,   16379l,   16364l,   16340l,
           16305l,   16261l,   16207l,   16143l,
           16069l,   15986l,   15893l,   15791l,
           15679l,   15557l,   15426l,   15286l,
           15137l,   14978l,   14811l,   14635l,
           14449l,   14256l,   14053l,   13842l,
           13623l,   13395l,   13160l,   12916l,
           12665l,   12406l,   12140l,   11866l,
           11585l,   11297l,   11003l,   10702l,
           10394l,   10080l,    9760l,    9434l,
            9102l,    8765l,    8423l,    8076l,
            7723l,    7366l,    7005l,    6639l,
            6270l,    5897l,    5520l,    5139l,
            4756l,    4370l,    3981l,    3590l,
            3196l,    2801l,    2404l,    2006l,
            1606l,    1205l,     804l,     402l,
               0l,    -401l,    -803l,   -1204l,
           -1605l,   -2005l,   -2403l,   -2800l,
           -3195l,   -3589l,   -3980l,   -4369l,
           -4755l,   -5138l,   -5519l,   -5896l,
           -6269l,   -6638l,   -7004l,   -7365l,
           -7722l,   -8075l,   -8422l,   -8764l,
           -9101l,   -9433l,   -9759l,  -10079l,
          -10393l,  -10701l,  -11002l,  -11296l,
          -11584l,  -11865l,  -12139l,  -12405l,
          -12664l,  -12915l,  -13159l,  -13394l,
          -13622l,  -13841l,  -14052l,  -14255l,
          -14448l,  -14634l,  -14810l,  -14977l,
          -15136l,  -15285l,  -15425l,  -15556l,
          -15678l,  -15790l,  -15892l,  -15985l,
          -16068l,  -16142l,  -16206l,  -16260l,
          -16304l,  -16339l,  -16363l,  -16378l,
          -16383l,
};
#endif

#endif

#endif

/* ---- end lookup_data.h ---- */

#ifdef FLOAT_LOOKUP

/* interpolated lookup based cos function, domain 0 to PI only */
float vorbis_coslook(float a){
  double d=a*(.31830989*(float)COS_LOOKUP_SZ);
  int i=vorbis_ftoi(d-.5);

  return COS_LOOKUP[i]+ (d-i)*(COS_LOOKUP[i+1]-COS_LOOKUP[i]);
}

/* interpolated 1./sqrt(p) where .5 <= p < 1. */
float vorbis_invsqlook(float a){
  double d=a*(2.f*(float)INVSQ_LOOKUP_SZ)-(float)INVSQ_LOOKUP_SZ;
  int i=vorbis_ftoi(d-.5f);
  return INVSQ_LOOKUP[i]+ (d-i)*(INVSQ_LOOKUP[i+1]-INVSQ_LOOKUP[i]);
}

/* interpolated 1./sqrt(p) where .5 <= p < 1. */
float vorbis_invsq2explook(int a){
  return INVSQ2EXP_LOOKUP[a-INVSQ2EXP_LOOKUP_MIN];
}

/* #include <stdio.h> : included above */
/* interpolated lookup based fromdB function, domain -140dB to 0dB only */
float vorbis_fromdBlook(float a){
  int i=vorbis_ftoi(a*((float)(-(1<<FROMdB2_SHIFT)))-.5f);
  return (i<0)?1.f:
    ((i>=(FROMdB_LOOKUP_SZ<<FROMdB_SHIFT))?0.f:
     FROMdB_LOOKUP[i>>FROMdB_SHIFT]*FROMdB2_LOOKUP[i&FROMdB2_MASK]);
}

#endif

#ifdef INT_LOOKUP
/* interpolated 1./sqrt(p) where .5 <= a < 1. (.100000... to .111111...) in
   16.16 format

   returns in m.8 format */
long vorbis_invsqlook_i(long a,long e){
  long i=(a&0x7fff)>>(INVSQ_LOOKUP_I_SHIFT-1);
  long d=(a&INVSQ_LOOKUP_I_MASK)<<(16-INVSQ_LOOKUP_I_SHIFT); /*  0.16 */
  long val=INVSQ_LOOKUP_I[i]-                                /*  1.16 */
    (((INVSQ_LOOKUP_I[i]-INVSQ_LOOKUP_I[i+1])*               /*  0.16 */
      d)>>16);                                               /* result 1.16 */

  e+=32;
  if(e&1)val=(val*5792)>>13; /* multiply val by 1/sqrt(2) */
  e=(e>>1)-8;

  return(val>>e);
}

/* interpolated lookup based fromdB function, domain -140dB to 0dB only */
/* a is in n.12 format */
float vorbis_fromdBlook_i(long a){
  int i=(-a)>>(12-FROMdB2_SHIFT);
  return (i<0)?1.f:
    ((i>=(FROMdB_LOOKUP_SZ<<FROMdB_SHIFT))?0.f:
     FROMdB_LOOKUP[i>>FROMdB_SHIFT]*FROMdB2_LOOKUP[i&FROMdB2_MASK]);
}

/* interpolated lookup based cos function, domain 0 to PI only */
/* a is in 0.16 format, where 0==0, 2^^16-1==PI, return 0.14 */
long vorbis_coslook_i(long a){
  int i=a>>COS_LOOKUP_I_SHIFT;
  int d=a&COS_LOOKUP_I_MASK;
  return COS_LOOKUP_I[i]- ((d*(COS_LOOKUP_I[i]-COS_LOOKUP_I[i+1]))>>
                           COS_LOOKUP_I_SHIFT);
}

#endif

/* ---- end lookup.c ---- */
/* catch this in the build system; we #include for
                       compilers (like gcc) that can't inline across
                       modules */

/* side effect: changes *lsp to cosines of lsp */
void vorbis_lsp_to_curve(float *curve,int *map,int n,int ln,float *lsp,int m,
                            float amp,float ampoffset){
  int i;
  float wdel=M_PI/ln;
  vorbis_fpu_control fpu;

  vorbis_fpu_setround(&fpu);
  for(i=0;i<m;i++)lsp[i]=vorbis_coslook(lsp[i]);

  i=0;
  while(i<n){
    int k=map[i];
    int qexp;
    float p=.7071067812f;
    float q=.7071067812f;
    float w=vorbis_coslook(wdel*k);
    float *ftmp=lsp;
    int c=m>>1;

    do{
      q*=ftmp[0]-w;
      p*=ftmp[1]-w;
      ftmp+=2;
    }while(--c);

    if(m&1){
      /* odd order filter; slightly assymetric */
      /* the last coefficient */
      q*=ftmp[0]-w;
      q*=q;
      p*=p*(1.f-w*w);
    }else{
      /* even order filter; still symmetric */
      q*=q*(1.f+w);
      p*=p*(1.f-w);
    }

    q=frexp(p+q,&qexp);
    q=vorbis_fromdBlook(amp*
                        vorbis_invsqlook(q)*
                        vorbis_invsq2explook(qexp+m)-
                        ampoffset);

    do{
      curve[i++]*=q;
    }while(map[i]==k);
  }
  vorbis_fpu_restore(fpu);
}

#else

#ifdef INT_LOOKUP
/* catch this in the build system; we #include for
                       compilers (like gcc) that can't inline across
                       modules */

extern int MLOOP_1[64];
#if 0 /* the library definition; the retail copy is bound instead */
static int MLOOP_1[64]={
   0,10,11,11, 12,12,12,12, 13,13,13,13, 13,13,13,13,
  14,14,14,14, 14,14,14,14, 14,14,14,14, 14,14,14,14,
  15,15,15,15, 15,15,15,15, 15,15,15,15, 15,15,15,15,
  15,15,15,15, 15,15,15,15, 15,15,15,15, 15,15,15,15,
};
#endif

extern int MLOOP_2[64];
#if 0 /* the library definition; the retail copy is bound instead */
static int MLOOP_2[64]={
  0,4,5,5, 6,6,6,6, 7,7,7,7, 7,7,7,7,
  8,8,8,8, 8,8,8,8, 8,8,8,8, 8,8,8,8,
  9,9,9,9, 9,9,9,9, 9,9,9,9, 9,9,9,9,
  9,9,9,9, 9,9,9,9, 9,9,9,9, 9,9,9,9,
};
#endif

extern int MLOOP_3[8];
#if 0 /* the library definition; the retail copy is bound instead */
static int MLOOP_3[8]={0,1,2,2,3,3,3,3};
#endif


/* side effect: changes *lsp to cosines of lsp */
void vorbis_lsp_to_curve(float *curve,int *map,int n,int ln,float *lsp,int m,
                            float amp,float ampoffset){

  /* 0 <= m < 256 */

  /* set up for using all int later */
  int i;
  int ampoffseti=rint(ampoffset*4096.f);
  int ampi=rint(amp*16.f);
  long *ilsp=alloca(m*sizeof(*ilsp));
  for(i=0;i<m;i++)ilsp[i]=vorbis_coslook_i(lsp[i]/M_PI*65536.f+.5f);

  i=0;
  while(i<n){
    int j,k=map[i];
    unsigned long pi=46341; /* 2**-.5 in 0.16 */
    unsigned long qi=46341;
    int qexp=0,shift;
    long wi=vorbis_coslook_i(k*65536/ln);

    qi*=labs(ilsp[0]-wi);
    pi*=labs(ilsp[1]-wi);

    for(j=3;j<m;j+=2){
      if(!(shift=MLOOP_1[(pi|qi)>>25]))
        if(!(shift=MLOOP_2[(pi|qi)>>19]))
          shift=MLOOP_3[(pi|qi)>>16];
      qi=(qi>>shift)*labs(ilsp[j-1]-wi);
      pi=(pi>>shift)*labs(ilsp[j]-wi);
      qexp+=shift;
    }
    if(!(shift=MLOOP_1[(pi|qi)>>25]))
      if(!(shift=MLOOP_2[(pi|qi)>>19]))
        shift=MLOOP_3[(pi|qi)>>16];

    /* pi,qi normalized collectively, both tracked using qexp */

    if(m&1){
      /* odd order filter; slightly assymetric */
      /* the last coefficient */
      qi=(qi>>shift)*labs(ilsp[j-1]-wi);
      pi=(pi>>shift)<<14;
      qexp+=shift;

      if(!(shift=MLOOP_1[(pi|qi)>>25]))
        if(!(shift=MLOOP_2[(pi|qi)>>19]))
          shift=MLOOP_3[(pi|qi)>>16];

      pi>>=shift;
      qi>>=shift;
      qexp+=shift-14*((m+1)>>1);

      pi=((pi*pi)>>16);
      qi=((qi*qi)>>16);
      qexp=qexp*2+m;

      pi*=(1<<14)-((wi*wi)>>14);
      qi+=pi>>14;

    }else{
      /* even order filter; still symmetric */

      /* p*=p(1-w), q*=q(1+w), let normalization drift because it isn't
         worth tracking step by step */

      pi>>=shift;
      qi>>=shift;
      qexp+=shift-7*m;

      pi=((pi*pi)>>16);
      qi=((qi*qi)>>16);
      qexp=qexp*2+m;

      pi*=(1<<14)-wi;
      qi*=(1<<14)+wi;
      qi=(qi+pi)>>14;

    }


    /* we've let the normalization drift because it wasn't important;
       however, for the lookup, things must be normalized again.  We
       need at most one right shift or a number of left shifts */

    if(qi&0xffff0000){ /* checks for 1.xxxxxxxxxxxxxxxx */
      qi>>=1; qexp++;
    }else
      while(qi && !(qi&0x8000)){ /* checks for 0.0xxxxxxxxxxxxxxx or less*/
        qi<<=1; qexp--;
      }

    amp=vorbis_fromdBlook_i(ampi*                     /*  n.4         */
                            vorbis_invsqlook_i(qi,qexp)-
                                                      /*  m.8, m+n<=8 */
                            ampoffseti);              /*  8.12[0]     */

    curve[i]*=amp;
    while(map[++i]==k)curve[i]*=amp;
  }
}

#else

/* old, nonoptimized but simple version for any poor sap who needs to
   figure out what the hell this code does, or wants the other
   fraction of a dB precision */

/* side effect: changes *lsp to cosines of lsp */
void vorbis_lsp_to_curve(float *curve,int *map,int n,int ln,float *lsp,int m,
                            float amp,float ampoffset){
  int i;
  float wdel=M_PI/ln;
  for(i=0;i<m;i++)lsp[i]=2.f*cos(lsp[i]);

  i=0;
  while(i<n){
    int j,k=map[i];
    float p=.5f;
    float q=.5f;
    float w=2.f*cos(wdel*k);
    for(j=1;j<m;j+=2){
      q *= w-lsp[j-1];
      p *= w-lsp[j];
    }
    if(j==m){
      /* odd order filter; slightly assymetric */
      /* the last coefficient */
      q*=w-lsp[j-1];
      p*=p*(4.f-w*w);
      q*=q;
    }else{
      /* even order filter; still symmetric */
      p*=p*(2.f-w);
      q*=q*(2.f+w);
    }

    q=fromdB(amp/sqrt(p+q)-ampoffset);

    curve[i]*=q;
    while(map[++i]==k)curve[i]*=q;
  }
}

#endif
#endif

static void cheby(float *g, int ord) {
  int i, j;

  g[0] *= .5f;
  for(i=2; i<= ord; i++) {
    for(j=ord; j >= i; j--) {
      g[j-2] -= g[j];
      g[j] += g[j];
    }
  }
}

static int comp(const void *a,const void *b){
  if(*(float *)a<*(float *)b)
    return(1);
  else
    return(-1);
}

/* Newton-Raphson-Maehly actually functioned as a decent root finder,
   but there are root sets for which it gets into limit cycles
   (exacerbated by zero suppression) and fails.  We can't afford to
   fail, even if the failure is 1 in 100,000,000, so we now use
   Laguerre and later polish with Newton-Raphson (which can then
   afford to fail) */

#define EPSILON 10e-7
static int Laguerre_With_Deflation(float *a,int ord,float *r){
  int i,m;
  double lastdelta=0.f;
  double *defl=alloca(sizeof(*defl)*(ord+1));
  for(i=0;i<=ord;i++)defl[i]=a[i];

  for(m=ord;m>0;m--){
    double new=0.f,delta;

    /* iterate a root */
    while(1){
      double p=defl[m],pp=0.f,ppp=0.f,denom;

      /* eval the polynomial and its first two derivatives */
      for(i=m;i>0;i--){
        ppp = new*ppp + pp;
        pp  = new*pp  + p;
        p   = new*p   + defl[i-1];
      }

      /* Laguerre's method */
      denom=(m-1) * ((m-1)*pp*pp - m*p*ppp);
      if(denom<0)
        return(-1);  /* complex root!  The LPC generator handed us a bad filter */

      if(pp>0){
        denom = pp + sqrt(denom);
        if(denom<EPSILON)denom=EPSILON;
      }else{
        denom = pp - sqrt(denom);
        if(denom>-(EPSILON))denom=-(EPSILON);
      }

      delta  = m*p/denom;
      new   -= delta;

      if(delta<0.f)delta*=-1;

      if(fabs(delta/new)<10e-12)break;
      lastdelta=delta;
    }

    r[m-1]=new;

    /* forward deflation */

    for(i=m;i>0;i--)
      defl[i-1]+=new*defl[i];
    defl++;

  }
  return(0);
}


/* for spit-and-polish only */
static int Newton_Raphson(float *a,int ord,float *r){
  int i, k, count=0;
  double error=1.f;
  double *root=alloca(ord*sizeof(*root));

  for(i=0; i<ord;i++) root[i] = r[i];

  while(error>1e-20){
    error=0;

    for(i=0; i<ord; i++) { /* Update each point. */
      double pp=0.,delta;
      double rooti=root[i];
      double p=a[ord];
      for(k=ord-1; k>= 0; k--) {

        pp= pp* rooti + p;
        p = p * rooti + a[k];
      }

      delta = p/pp;
      root[i] -= delta;
      error+= delta*delta;
    }

    if(count>40)return(-1);

    count++;
  }

  /* Replaced the original bubble sort with a real sort.  With your
     help, we can eliminate the bubble sort in our lifetime. --Monty */

  for(i=0; i<ord;i++) r[i] = root[i];
  return(0);
}


/* Convert lpc coefficients to lsp coefficients */
int vorbis_lpc_to_lsp(float *lpc,float *lsp,int m){
  int order2=(m+1)>>1;
  int g1_order,g2_order;
  float *g1=alloca(sizeof(*g1)*(order2+1));
  float *g2=alloca(sizeof(*g2)*(order2+1));
  float *g1r=alloca(sizeof(*g1r)*(order2+1));
  float *g2r=alloca(sizeof(*g2r)*(order2+1));
  int i;

  /* even and odd are slightly different base cases */
  g1_order=(m+1)>>1;
  g2_order=(m)  >>1;

  /* Compute the lengths of the x polynomials. */
  /* Compute the first half of K & R F1 & F2 polynomials. */
  /* Compute half of the symmetric and antisymmetric polynomials. */
  /* Remove the roots at +1 and -1. */

  g1[g1_order] = 1.f;
  for(i=1;i<=g1_order;i++) g1[g1_order-i] = lpc[i-1]+lpc[m-i];
  g2[g2_order] = 1.f;
  for(i=1;i<=g2_order;i++) g2[g2_order-i] = lpc[i-1]-lpc[m-i];

  if(g1_order>g2_order){
    for(i=2; i<=g2_order;i++) g2[g2_order-i] += g2[g2_order-i+2];
  }else{
    for(i=1; i<=g1_order;i++) g1[g1_order-i] -= g1[g1_order-i+1];
    for(i=1; i<=g2_order;i++) g2[g2_order-i] += g2[g2_order-i+1];
  }

  /* Convert into polynomials in cos(alpha) */
  cheby(g1,g1_order);
  cheby(g2,g2_order);

  /* Find the roots of the 2 even polynomials.*/
  if(Laguerre_With_Deflation(g1,g1_order,g1r) ||
     Laguerre_With_Deflation(g2,g2_order,g2r))
    return(-1);

  Newton_Raphson(g1,g1_order,g1r); /* if it fails, it leaves g1r alone */
  Newton_Raphson(g2,g2_order,g2r); /* if it fails, it leaves g2r alone */

  qsort(g1r,g1_order,sizeof(*g1r),comp);
  qsort(g2r,g2_order,sizeof(*g2r),comp);

  for(i=0;i<g1_order;i++)
    lsp[i*2] = acos(g1r[i]);

  for(i=0;i<g2_order;i++)
    lsp[i*2+1] = acos(g2r[i]);
  return(0);
}
