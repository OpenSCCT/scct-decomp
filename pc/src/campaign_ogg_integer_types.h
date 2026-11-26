/* campaign_ogg_integer_types.h -- shared Ogg integer aliases */
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
#ifndef CAMPAIGN_OGG_INTEGER_TYPES_H
#define CAMPAIGN_OGG_INTEGER_TYPES_H

#ifdef _WIN32
#  ifndef __GNUC__
typedef __int64 ogg_int64_t;
typedef unsigned __int32 ogg_uint32_t;
#  else
typedef _G_int64_t ogg_int64_t;
typedef _G_uint32_t ogg_uint32_t;
#  endif
#elif defined(__MACOS__)
typedef SInt64 ogg_int64_t;
typedef UInt32 ogg_uint32_t;
#elif defined(__MACOSX__)
typedef int64_t ogg_int64_t;
typedef u_int32_t ogg_uint32_t;
#elif defined(__BEOS__)
typedef int64_t ogg_int64_t;
typedef u_int32_t ogg_uint32_t;
#elif defined (__EMX__)
typedef long long ogg_int64_t;
typedef unsigned int ogg_uint32_t;
#else
typedef int64_t ogg_int64_t;
typedef u_int32_t ogg_uint32_t;
#endif

#endif /* CAMPAIGN_OGG_INTEGER_TYPES_H */
