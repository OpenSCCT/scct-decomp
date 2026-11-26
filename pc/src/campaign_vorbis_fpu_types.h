/* campaign_vorbis_fpu_types.h -- shared Vorbis FPU control type */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2002             *
 * by the Xiph.Org Foundation http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************/
#ifndef CAMPAIGN_VORBIS_FPU_TYPES_H
#define CAMPAIGN_VORBIS_FPU_TYPES_H

#include "campaign_ogg_os_types.h"

#if defined(__i386__) && defined(__GNUC__) && !defined(__BEOS__)
typedef ogg_int16_t vorbis_fpu_control;
#elif defined(_WIN32) && !defined(__GNUC__) && !defined(__BORLANDC__)
typedef ogg_int16_t vorbis_fpu_control;
#elif !defined(VORBIS_FPU_CONTROL)
typedef int vorbis_fpu_control;
#endif

#endif /* CAMPAIGN_VORBIS_FPU_TYPES_H */
