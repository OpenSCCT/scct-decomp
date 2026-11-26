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

  function: LPC low level routines
  last mod: $Id: lpc.c,v 1.35 2002/07/11 06:40:49 xiphmont Exp $

 ********************************************************************/

/* Some of these routines (autocorrelator, LPC coefficient estimator)
   are derived from code written by Jutta Degener and Carsten Bormann;
   thus we include their copyright below.  The entirety of this file
   is freely redistributable on the condition that both of these
   copyright notices are preserved without modification.  */

/* Preserved Copyright: *********************************************/

/* Copyright 1992, 1993, 1994 by Jutta Degener and Carsten Bormann,
Technische Universita"t Berlin

Any use of this software is permitted provided that this notice is not
removed and that neither the authors nor the Technische Universita"t
Berlin are deemed to have made any representations as to the
suitability of this software for any purpose nor are held responsible
for any defects of this software. THERE IS ABSOLUTELY NO WARRANTY FOR
THIS SOFTWARE.

As a matter of courtesy, the authors request to be informed about uses
this software has found, about bugs in this software, and about any
improvements that may be of general interest.

Berlin, 28.11.1994
Jutta Degener
Carsten Bormann

*********************************************************************/

/* #include <stdlib.h> : included above */
/* #include <string.h> : included above */
/* #include <math.h> : included above */
#include "campaign_vorbis_os.h"
#include "campaign_vorbis_smallft.h"
#include "campaign_vorbis_lpc.h"
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

/* Autocorrelation LPC coeff generation algorithm invented by
   N. Levinson in 1947, modified by J. Durbin in 1959. */

/* Input : n elements of time doamin data
   Output: m lpc coefficients, excitation energy */

float vorbis_lpc_from_data(float *data,float *lpc,int n,int m){
  float *aut=alloca(sizeof(*aut)*(m+1));
  float error;
  int i,j;

  /* autocorrelation, p+1 lag coefficients */

  j=m+1;
  while(j--){
    double d=0; /* double needed for accumulator depth */
    for(i=j;i<n;i++)d+=data[i]*data[i-j];
    aut[j]=d;
  }

  /* Generate lpc coefficients from autocorr values */

  error=aut[0];

  for(i=0;i<m;i++){
    float r= -aut[i+1];

    if(error==0){
      memset(lpc,0,m*sizeof(*lpc));
      return 0;
    }

    /* Sum up this iteration's reflection coefficient; note that in
       Vorbis we don't save it.  If anyone wants to recycle this code
       and needs reflection coefficients, save the results of 'r' from
       each iteration. */

    for(j=0;j<i;j++)r-=lpc[j]*aut[i-j];
    r/=error;

    /* Update LPC coefficients and total error */

    lpc[i]=r;
    for(j=0;j<i/2;j++){
      float tmp=lpc[j];
      lpc[j]+=r*lpc[i-1-j];
      lpc[i-1-j]+=r*tmp;
    }
    if(i%2)lpc[j]+=lpc[j]*r;

    error*=1.f-r*r;
  }

  /* we need the error value to know how big an impulse to hit the
     filter with later */

  return error;
}

/* Input : n element envelope spectral curve
   Output: m lpc coefficients, excitation energy */

float vorbis_lpc_from_curve(float *curve,float *lpc,lpc_lookup *l){
  int n=l->ln;
  int m=l->m;
  float *work=alloca(sizeof(*work)*(n+n));
  float fscale=.5f/n;
  int i,j;

  /* input is a real curve. make it complex-real */
  /* This mixes phase, but the LPC generation doesn't care. */
  for(i=0;i<n;i++){
    work[i*2]=curve[i]*fscale;
    work[i*2+1]=0;
  }
  work[n*2-1]=curve[n-1]*fscale;

  n*=2;
  drft_backward(&l->fft,work);

  /* The autocorrelation will not be circular.  Shift, else we lose
     most of the power in the edges. */

  for(i=0,j=n/2;i<n/2;){
    float temp=work[i];
    work[i++]=work[j];
    work[j++]=temp;
  }

  /* we *could* shave speed here by skimping on the edges (thus
     speeding up the autocorrelation in vorbis_lpc_from_data) but we
     don't right now. */

  return(vorbis_lpc_from_data(work,lpc,n,m));
}

void lpc_init(lpc_lookup *l,long mapped, int m){
  memset(l,0,sizeof(*l));

  l->ln=mapped;
  l->m=m;

  /* we cheat decoding the LPC spectrum via FFTs */
  drft_init(&l->fft,mapped*2);

}

void lpc_clear(lpc_lookup *l){
  if(l){
    drft_clear(&l->fft);
  }
}

void vorbis_lpc_predict(float *coeff,float *prime,int m,
                     float *data,long n){

  /* in: coeff[0...m-1] LPC coefficients
         prime[0...m-1] initial values (allocated size of n+m-1)
    out: data[0...n-1] data samples */

  long i,j,o,p;
  float y;
  float *work=alloca(sizeof(*work)*(m+n));

  if(!prime)
    for(i=0;i<m;i++)
      work[i]=0.f;
  else
    for(i=0;i<m;i++)
      work[i]=prime[i];

  for(i=0;i<n;i++){
    y=0;
    o=i;
    p=m;
    for(j=0;j<m;j++)
      y-=work[o++]*coeff[--p];

    data[i]=work[o]=y;
  }
}
