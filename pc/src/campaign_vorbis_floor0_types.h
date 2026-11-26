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

 function: floor backend 0 implementation
 last mod: $Id: floor0.c,v 1.53 2002/07/17 21:34:31 xiphmont Exp $

 ********************************************************************/

/* Private types shared by the two Campaign builds of floor0.c. */
#ifndef CAMPAIGN_VORBIS_FLOOR0_TYPES_H
#define CAMPAIGN_VORBIS_FLOOR0_TYPES_H

#include "campaign_vorbis_codec_internal.h"
#include "campaign_vorbis_lpc.h"

typedef struct {
  int ln;
  int  m;
  int **linearmap;
  int  n[2];

  vorbis_info_floor0 *vi;
  lpc_lookup lpclook;
  float *lsp_look;

  long bits;
  long frames;
} vorbis_look_floor0;

#endif
