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

#ifdef _WIN32

#  ifndef __GNUC__
   /* MSVC/Borland */
   typedef __int32 ogg_int32_t;
   typedef __int16 ogg_int16_t;
#  else
   /* Cygwin */
/* #include <_G_config.h> : declarations supplied by the prelude */
   typedef _G_int32_t ogg_int32_t;
   typedef _G_int16_t ogg_int16_t;
#  endif

#elif defined(__MACOS__)

/* #  include <sys/types.h> : declarations supplied by the prelude */
   typedef SInt16 ogg_int16_t;
   typedef SInt32 ogg_int32_t;
#elif defined(__MACOSX__) /* MacOS X Framework build */

/* #  include <sys/types.h> : declarations supplied by the prelude */
   typedef int16_t ogg_int16_t;
   typedef int32_t ogg_int32_t;
#elif defined(__BEOS__)

   /* Be */
/* #  include <inttypes.h> : declarations supplied by the prelude */
   typedef int16_t ogg_int16_t;
   typedef int32_t ogg_int32_t;
#elif defined (__EMX__)

   /* OS/2 GCC */
   typedef short ogg_int16_t;
   typedef int ogg_int32_t;
#else

/* #  include <sys/types.h> : declarations supplied by the prelude */
/* ---- ogg/config_types.h ---- */
#ifndef __CONFIG_TYPES_H__
#define __CONFIG_TYPES_H__

/* these are filled in by configure */
typedef int16_t ogg_int16_t;
typedef int32_t ogg_int32_t;
#endif

/* ---- end ogg/config_types.h ---- */

#endif

#endif /* CAMPAIGN_OGG_INTEGER_TYPES_H */
