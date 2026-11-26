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

 function: stdio-based convenience library for opening/seeking/decoding
 last mod: $Id: vorbisfile.c,v 1.62 2002/07/06 04:20:03 msmith Exp $

 ********************************************************************/

/* #include <stdlib.h> : included above */
/* #include <stdio.h> : included above */
/* #include <errno.h> : included above */
/* #include <string.h> : included above */
/* #include <math.h> : included above */

/* ---- vorbis/codec.h ---- */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2001             *
 * by the XIPHOPHORUS Company http://www.xiph.org/                  *

 ********************************************************************

 function: libvorbis codec headers
 last mod: $Id: codec.h,v 1.40 2002/02/28 04:12:47 xiphmont Exp $

 ********************************************************************/

#ifndef _vorbis_codec_h_
#define _vorbis_codec_h_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ---- ogg/ogg.h ---- */
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
 ********************************************************************

 function: toplevel libogg include
 last mod: $Id: ogg.h,v 1.18 2002/07/13 10:28:33 giles Exp $

 ********************************************************************/
#ifndef _OGG_H
#define _OGG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ---- ogg/os_types.h ---- */
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
 ********************************************************************

 function: #ifdef jail to whip a few platforms into the UNIX ideal.
 last mod: $Id: os_types.h,v 1.11 2002/07/19 08:25:51 msmith Exp $

 ********************************************************************/
#ifndef _OS_TYPES_H
#define _OS_TYPES_H

/* make it easy on the folks that want to compile the libs with a
   different malloc than stdlib */
#define _ogg_malloc  malloc
#define _ogg_calloc  calloc
#define _ogg_realloc realloc
#define _ogg_free    free

#ifdef _WIN32

#  ifndef __GNUC__
   /* MSVC/Borland */
   typedef __int64 ogg_int64_t;
   typedef __int32 ogg_int32_t;
   typedef unsigned __int32 ogg_uint32_t;
   typedef __int16 ogg_int16_t;
#  else
   /* Cygwin */
/* #include <_G_config.h> : declarations supplied by the prelude */
   typedef _G_int64_t ogg_int64_t;
   typedef _G_int32_t ogg_int32_t;
   typedef _G_uint32_t ogg_uint32_t;
   typedef _G_int16_t ogg_int16_t;
#  endif

#elif defined(__MACOS__)

/* #  include <sys/types.h> : declarations supplied by the prelude */
   typedef SInt16 ogg_int16_t;
   typedef SInt32 ogg_int32_t;
   typedef UInt32 ogg_uint32_t;
   typedef SInt64 ogg_int64_t;

#elif defined(__MACOSX__) /* MacOS X Framework build */

/* #  include <sys/types.h> : declarations supplied by the prelude */
   typedef int16_t ogg_int16_t;
   typedef int32_t ogg_int32_t;
   typedef u_int32_t ogg_uint32_t;
   typedef int64_t ogg_int64_t;

#elif defined(__BEOS__)

   /* Be */
/* #  include <inttypes.h> : declarations supplied by the prelude */
   typedef int16_t ogg_int16_t;
   typedef int32_t ogg_int32_t;
   typedef u_int32_t ogg_uint32_t;
   typedef int64_t ogg_int64_t;

#elif defined (__EMX__)

   /* OS/2 GCC */
   typedef short ogg_int16_t;
   typedef int ogg_int32_t;
   typedef unsigned int ogg_uint32_t;
   typedef long long ogg_int64_t;

#else

/* #  include <sys/types.h> : declarations supplied by the prelude */
/* ---- ogg/config_types.h ---- */
#ifndef __CONFIG_TYPES_H__
#define __CONFIG_TYPES_H__

/* these are filled in by configure */
typedef int16_t ogg_int16_t;
typedef int32_t ogg_int32_t;
typedef u_int32_t ogg_uint32_t;
typedef int64_t ogg_int64_t;

#endif

/* ---- end ogg/config_types.h ---- */

#endif

#endif  /* _OS_TYPES_H */

/* ---- end ogg/os_types.h ---- */

typedef struct {
  long endbyte;
  int  endbit;

  unsigned char *buffer;
  unsigned char *ptr;
  long storage;
} oggpack_buffer;

/* ogg_page is used to encapsulate the data in one Ogg bitstream page *****/

typedef struct {
  unsigned char *header;
  long header_len;
  unsigned char *body;
  long body_len;
} ogg_page;

/* ogg_stream_state contains the current encode/decode state of a logical
   Ogg bitstream **********************************************************/

typedef struct {
  unsigned char   *body_data;    /* bytes from packet bodies */
  long    body_storage;          /* storage elements allocated */
  long    body_fill;             /* elements stored; fill mark */
  long    body_returned;         /* elements of fill returned */


  int     *lacing_vals;      /* The values that will go to the segment table */
  ogg_int64_t *granule_vals; /* granulepos values for headers. Not compact
                                this way, but it is simple coupled to the
                                lacing fifo */
  long    lacing_storage;
  long    lacing_fill;
  long    lacing_packet;
  long    lacing_returned;

  unsigned char    header[282];      /* working space for header encode */
  int              header_fill;

  int     e_o_s;          /* set when we have buffered the last packet in the
                             logical bitstream */
  int     b_o_s;          /* set after we've written the initial page
                             of a logical bitstream */
  long    serialno;
  long    pageno;
  ogg_int64_t  packetno;      /* sequence number for decode; the framing
                             knows where there's a hole in the data,
                             but we need coupling so that the codec
                             (which is in a seperate abstraction
                             layer) also knows about the gap */
  ogg_int64_t   granulepos;

} ogg_stream_state;

/* ogg_packet is used to encapsulate the data and metadata belonging
   to a single raw Ogg/Vorbis packet *************************************/

typedef struct {
  unsigned char *packet;
  long  bytes;
  long  b_o_s;
  long  e_o_s;

  ogg_int64_t  granulepos;

  ogg_int64_t  packetno;     /* sequence number for decode; the framing
                                knows where there's a hole in the data,
                                but we need coupling so that the codec
                                (which is in a seperate abstraction
                                layer) also knows about the gap */
} ogg_packet;

typedef struct {
  unsigned char *data;
  int storage;
  int fill;
  int returned;

  int unsynced;
  int headerbytes;
  int bodybytes;
} ogg_sync_state;

/* Ogg BITSTREAM PRIMITIVES: bitstream ************************/

extern void  oggpack_writeinit(oggpack_buffer *b);
extern void  oggpack_writetrunc(oggpack_buffer *b,long bits);
extern void  oggpack_writealign(oggpack_buffer *b);
extern void  oggpack_writecopy(oggpack_buffer *b,void *source,long bits);
extern void  oggpack_reset(oggpack_buffer *b);
extern void  oggpack_writeclear(oggpack_buffer *b);
extern void  oggpack_readinit(oggpack_buffer *b,unsigned char *buf,int bytes);
extern void  oggpack_write(oggpack_buffer *b,unsigned long value,int bits);
extern long  oggpack_look(oggpack_buffer *b,int bits);
extern long  oggpack_look1(oggpack_buffer *b);
extern void  oggpack_adv(oggpack_buffer *b,int bits);
extern void  oggpack_adv1(oggpack_buffer *b);
extern long  oggpack_read(oggpack_buffer *b,int bits);
extern long  oggpack_read1(oggpack_buffer *b);
extern long  oggpack_bytes(oggpack_buffer *b);
extern long  oggpack_bits(oggpack_buffer *b);
extern unsigned char *oggpack_get_buffer(oggpack_buffer *b);

/* Ogg BITSTREAM PRIMITIVES: encoding **************************/

extern int      ogg_stream_packetin(ogg_stream_state *os, ogg_packet *op);
extern int      ogg_stream_pageout(ogg_stream_state *os, ogg_page *og);
extern int      ogg_stream_flush(ogg_stream_state *os, ogg_page *og);

/* Ogg BITSTREAM PRIMITIVES: decoding **************************/

extern int      ogg_sync_init(ogg_sync_state *oy);
extern int      ogg_sync_clear(ogg_sync_state *oy);
extern int      ogg_sync_reset(ogg_sync_state *oy);
extern int	ogg_sync_destroy(ogg_sync_state *oy);

extern char    *ogg_sync_buffer(ogg_sync_state *oy, long size);
extern int      ogg_sync_wrote(ogg_sync_state *oy, long bytes);
extern long     ogg_sync_pageseek(ogg_sync_state *oy,ogg_page *og);
extern int      ogg_sync_pageout(ogg_sync_state *oy, ogg_page *og);
extern int      ogg_stream_pagein(ogg_stream_state *os, ogg_page *og);
extern int      ogg_stream_packetout(ogg_stream_state *os,ogg_packet *op);
extern int      ogg_stream_packetpeek(ogg_stream_state *os,ogg_packet *op);

/* Ogg BITSTREAM PRIMITIVES: general ***************************/

extern int      ogg_stream_init(ogg_stream_state *os,int serialno);
extern int      ogg_stream_clear(ogg_stream_state *os);
extern int      ogg_stream_reset(ogg_stream_state *os);
extern int      ogg_stream_reset_serialno(ogg_stream_state *os,int serialno);
extern int      ogg_stream_destroy(ogg_stream_state *os);
extern int      ogg_stream_eos(ogg_stream_state *os);

extern void     ogg_page_checksum_set(ogg_page *og);

extern int      ogg_page_version(ogg_page *og);
extern int      ogg_page_continued(ogg_page *og);
extern int      ogg_page_bos(ogg_page *og);
extern int      ogg_page_eos(ogg_page *og);
extern ogg_int64_t  ogg_page_granulepos(ogg_page *og);
extern int      ogg_page_serialno(ogg_page *og);
extern long     ogg_page_pageno(ogg_page *og);
extern int      ogg_page_packets(ogg_page *og);

extern void     ogg_packet_clear(ogg_packet *op);


#ifdef __cplusplus
}
#endif

#endif  /* _OGG_H */







/* ---- end ogg/ogg.h ---- */

typedef struct vorbis_info{
  int version;
  int channels;
  long rate;

  /* The below bitrate declarations are *hints*.
     Combinations of the three values carry the following implications:

     all three set to the same value:
       implies a fixed rate bitstream
     only nominal set:
       implies a VBR stream that averages the nominal bitrate.  No hard
       upper/lower limit
     upper and or lower set:
       implies a VBR bitstream that obeys the bitrate limits. nominal
       may also be set to give a nominal rate.
     none set:
       the coder does not care to speculate.
  */

  long bitrate_upper;
  long bitrate_nominal;
  long bitrate_lower;
  long bitrate_window;

  void *codec_setup;
} vorbis_info;

/* vorbis_dsp_state buffers the current vorbis audio
   analysis/synthesis state.  The DSP state belongs to a specific
   logical bitstream ****************************************************/
typedef struct vorbis_dsp_state{
  int analysisp;
  vorbis_info *vi;

  float **pcm;
  float **pcmret;
  int      pcm_storage;
  int      pcm_current;
  int      pcm_returned;

  int  preextrapolate;
  int  eofflag;

  long lW;
  long W;
  long nW;
  long centerW;

  ogg_int64_t granulepos;
  ogg_int64_t sequence;

  ogg_int64_t glue_bits;
  ogg_int64_t time_bits;
  ogg_int64_t floor_bits;
  ogg_int64_t res_bits;

  void       *backend_state;
} vorbis_dsp_state;

typedef struct vorbis_block{
  /* necessary stream state for linking to the framing abstraction */
  float  **pcm;       /* this is a pointer into local storage */
  oggpack_buffer opb;

  long  lW;
  long  W;
  long  nW;
  int   pcmend;
  int   mode;

  int         eofflag;
  ogg_int64_t granulepos;
  ogg_int64_t sequence;
  vorbis_dsp_state *vd; /* For read-only access of configuration */

  /* local storage to avoid remallocing; it's up to the mapping to
     structure it */
  void               *localstore;
  long                localtop;
  long                localalloc;
  long                totaluse;
  struct alloc_chain *reap;

  /* bitmetrics for the frame */
  long glue_bits;
  long time_bits;
  long floor_bits;
  long res_bits;

  void *internal;

} vorbis_block;

/* vorbis_block is a single block of data to be processed as part of
the analysis/synthesis stream; it belongs to a specific logical
bitstream, but is independant from other vorbis_blocks belonging to
that logical bitstream. *************************************************/

struct alloc_chain{
  void *ptr;
  struct alloc_chain *next;
};

/* vorbis_info contains all the setup information specific to the
   specific compression/decompression mode in progress (eg,
   psychoacoustic settings, channel setup, options, codebook
   etc). vorbis_info and substructures are in backends.h.
*********************************************************************/

/* the comments are not part of vorbis_info so that vorbis_info can be
   static storage */
typedef struct vorbis_comment{
  /* unlimited user comment fields.  libvorbis writes 'libvorbis'
     whatever vendor is set to in encode */
  char **user_comments;
  int   *comment_lengths;
  int    comments;
  char  *vendor;

} vorbis_comment;


/* libvorbis encodes in two abstraction layers; first we perform DSP
   and produce a packet (see docs/analysis.txt).  The packet is then
   coded into a framed OggSquish bitstream by the second layer (see
   docs/framing.txt).  Decode is the reverse process; we sync/frame
   the bitstream and extract individual packets, then decode the
   packet back into PCM audio.

   The extra framing/packetizing is used in streaming formats, such as
   files.  Over the net (such as with UDP), the framing and
   packetization aren't necessary as they're provided by the transport
   and the streaming layer is not used */

/* Vorbis PRIMITIVES: general ***************************************/

extern void     vorbis_info_init(vorbis_info *vi);
extern void     vorbis_info_clear(vorbis_info *vi);
extern int      vorbis_info_blocksize(vorbis_info *vi,int zo);
extern void     vorbis_comment_init(vorbis_comment *vc);
extern void     vorbis_comment_add(vorbis_comment *vc, char *comment);
extern void     vorbis_comment_add_tag(vorbis_comment *vc,
                                       char *tag, char *contents);
extern char    *vorbis_comment_query(vorbis_comment *vc, char *tag, int count);
extern int      vorbis_comment_query_count(vorbis_comment *vc, char *tag);
extern void     vorbis_comment_clear(vorbis_comment *vc);

extern int      vorbis_block_init(vorbis_dsp_state *v, vorbis_block *vb);
extern int      vorbis_block_clear(vorbis_block *vb);
extern void     vorbis_dsp_clear(vorbis_dsp_state *v);

/* Vorbis PRIMITIVES: analysis/DSP layer ****************************/

extern int      vorbis_analysis_init(vorbis_dsp_state *v,vorbis_info *vi);
extern int      vorbis_commentheader_out(vorbis_comment *vc, ogg_packet *op);
extern int      vorbis_analysis_headerout(vorbis_dsp_state *v,
                                          vorbis_comment *vc,
                                          ogg_packet *op,
                                          ogg_packet *op_comm,
                                          ogg_packet *op_code);
extern float  **vorbis_analysis_buffer(vorbis_dsp_state *v,int vals);
extern int      vorbis_analysis_wrote(vorbis_dsp_state *v,int vals);
extern int      vorbis_analysis_blockout(vorbis_dsp_state *v,vorbis_block *vb);
extern int      vorbis_analysis(vorbis_block *vb,ogg_packet *op);

extern int      vorbis_bitrate_addblock(vorbis_block *vb);
extern int      vorbis_bitrate_flushpacket(vorbis_dsp_state *vd,
                                           ogg_packet *op);

/* Vorbis PRIMITIVES: synthesis layer *******************************/
extern int      vorbis_synthesis_headerin(vorbis_info *vi,vorbis_comment *vc,
                                          ogg_packet *op);

extern int      vorbis_synthesis_init(vorbis_dsp_state *v,vorbis_info *vi);
extern int      vorbis_synthesis(vorbis_block *vb,ogg_packet *op);
extern int      vorbis_synthesis_trackonly(vorbis_block *vb,ogg_packet *op);
extern int      vorbis_synthesis_blockin(vorbis_dsp_state *v,vorbis_block *vb);
extern int      vorbis_synthesis_pcmout(vorbis_dsp_state *v,float ***pcm);
extern int      vorbis_synthesis_read(vorbis_dsp_state *v,int samples);
extern long     vorbis_packet_blocksize(vorbis_info *vi,ogg_packet *op);

/* Vorbis ERRORS and return codes ***********************************/

#define OV_FALSE      -1
#define OV_EOF        -2
#define OV_HOLE       -3

#define OV_EREAD      -128
#define OV_EFAULT     -129
#define OV_EIMPL      -130
#define OV_EINVAL     -131
#define OV_ENOTVORBIS -132
#define OV_EBADHEADER -133
#define OV_EVERSION   -134
#define OV_ENOTAUDIO  -135
#define OV_EBADPACKET -136
#define OV_EBADLINK   -137
#define OV_ENOSEEK    -138

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/* ---- end vorbis/codec.h ---- */
/* ---- vorbis/vorbisfile.h ---- */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2001             *
 * by the XIPHOPHORUS Company http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: stdio-based convenience library for opening/seeking/decoding
 last mod: $Id: vorbisfile.h,v 1.17 2002/03/07 03:41:03 xiphmont Exp $

 ********************************************************************/

#ifndef _OV_FILE_H_
#define _OV_FILE_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* #include <stdio.h> : included above */
/* ---- codec.h ---- */
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2001             *
 * by the XIPHOPHORUS Company http://www.xiph.org/                  *

 ********************************************************************

 function: libvorbis codec headers
 last mod: $Id: codec.h,v 1.40 2002/02/28 04:12:47 xiphmont Exp $

 ********************************************************************/

#ifndef _vorbis_codec_h_
#define _vorbis_codec_h_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


typedef struct vorbis_info{
  int version;
  int channels;
  long rate;

  /* The below bitrate declarations are *hints*.
     Combinations of the three values carry the following implications:

     all three set to the same value:
       implies a fixed rate bitstream
     only nominal set:
       implies a VBR stream that averages the nominal bitrate.  No hard
       upper/lower limit
     upper and or lower set:
       implies a VBR bitstream that obeys the bitrate limits. nominal
       may also be set to give a nominal rate.
     none set:
       the coder does not care to speculate.
  */

  long bitrate_upper;
  long bitrate_nominal;
  long bitrate_lower;
  long bitrate_window;

  void *codec_setup;
} vorbis_info;

/* vorbis_dsp_state buffers the current vorbis audio
   analysis/synthesis state.  The DSP state belongs to a specific
   logical bitstream ****************************************************/
typedef struct vorbis_dsp_state{
  int analysisp;
  vorbis_info *vi;

  float **pcm;
  float **pcmret;
  int      pcm_storage;
  int      pcm_current;
  int      pcm_returned;

  int  preextrapolate;
  int  eofflag;

  long lW;
  long W;
  long nW;
  long centerW;

  ogg_int64_t granulepos;
  ogg_int64_t sequence;

  ogg_int64_t glue_bits;
  ogg_int64_t time_bits;
  ogg_int64_t floor_bits;
  ogg_int64_t res_bits;

  void       *backend_state;
} vorbis_dsp_state;

typedef struct vorbis_block{
  /* necessary stream state for linking to the framing abstraction */
  float  **pcm;       /* this is a pointer into local storage */
  oggpack_buffer opb;

  long  lW;
  long  W;
  long  nW;
  int   pcmend;
  int   mode;

  int         eofflag;
  ogg_int64_t granulepos;
  ogg_int64_t sequence;
  vorbis_dsp_state *vd; /* For read-only access of configuration */

  /* local storage to avoid remallocing; it's up to the mapping to
     structure it */
  void               *localstore;
  long                localtop;
  long                localalloc;
  long                totaluse;
  struct alloc_chain *reap;

  /* bitmetrics for the frame */
  long glue_bits;
  long time_bits;
  long floor_bits;
  long res_bits;

  void *internal;

} vorbis_block;

/* vorbis_block is a single block of data to be processed as part of
the analysis/synthesis stream; it belongs to a specific logical
bitstream, but is independant from other vorbis_blocks belonging to
that logical bitstream. *************************************************/

struct alloc_chain{
  void *ptr;
  struct alloc_chain *next;
};

/* vorbis_info contains all the setup information specific to the
   specific compression/decompression mode in progress (eg,
   psychoacoustic settings, channel setup, options, codebook
   etc). vorbis_info and substructures are in backends.h.
*********************************************************************/

/* the comments are not part of vorbis_info so that vorbis_info can be
   static storage */
typedef struct vorbis_comment{
  /* unlimited user comment fields.  libvorbis writes 'libvorbis'
     whatever vendor is set to in encode */
  char **user_comments;
  int   *comment_lengths;
  int    comments;
  char  *vendor;

} vorbis_comment;


/* libvorbis encodes in two abstraction layers; first we perform DSP
   and produce a packet (see docs/analysis.txt).  The packet is then
   coded into a framed OggSquish bitstream by the second layer (see
   docs/framing.txt).  Decode is the reverse process; we sync/frame
   the bitstream and extract individual packets, then decode the
   packet back into PCM audio.

   The extra framing/packetizing is used in streaming formats, such as
   files.  Over the net (such as with UDP), the framing and
   packetization aren't necessary as they're provided by the transport
   and the streaming layer is not used */

/* Vorbis PRIMITIVES: general ***************************************/

extern void     vorbis_info_init(vorbis_info *vi);
extern void     vorbis_info_clear(vorbis_info *vi);
extern int      vorbis_info_blocksize(vorbis_info *vi,int zo);
extern void     vorbis_comment_init(vorbis_comment *vc);
extern void     vorbis_comment_add(vorbis_comment *vc, char *comment);
extern void     vorbis_comment_add_tag(vorbis_comment *vc,
                                       char *tag, char *contents);
extern char    *vorbis_comment_query(vorbis_comment *vc, char *tag, int count);
extern int      vorbis_comment_query_count(vorbis_comment *vc, char *tag);
extern void     vorbis_comment_clear(vorbis_comment *vc);

extern int      vorbis_block_init(vorbis_dsp_state *v, vorbis_block *vb);
extern int      vorbis_block_clear(vorbis_block *vb);
extern void     vorbis_dsp_clear(vorbis_dsp_state *v);

/* Vorbis PRIMITIVES: analysis/DSP layer ****************************/

extern int      vorbis_analysis_init(vorbis_dsp_state *v,vorbis_info *vi);
extern int      vorbis_commentheader_out(vorbis_comment *vc, ogg_packet *op);
extern int      vorbis_analysis_headerout(vorbis_dsp_state *v,
                                          vorbis_comment *vc,
                                          ogg_packet *op,
                                          ogg_packet *op_comm,
                                          ogg_packet *op_code);
extern float  **vorbis_analysis_buffer(vorbis_dsp_state *v,int vals);
extern int      vorbis_analysis_wrote(vorbis_dsp_state *v,int vals);
extern int      vorbis_analysis_blockout(vorbis_dsp_state *v,vorbis_block *vb);
extern int      vorbis_analysis(vorbis_block *vb,ogg_packet *op);

extern int      vorbis_bitrate_addblock(vorbis_block *vb);
extern int      vorbis_bitrate_flushpacket(vorbis_dsp_state *vd,
                                           ogg_packet *op);

/* Vorbis PRIMITIVES: synthesis layer *******************************/
extern int      vorbis_synthesis_headerin(vorbis_info *vi,vorbis_comment *vc,
                                          ogg_packet *op);

extern int      vorbis_synthesis_init(vorbis_dsp_state *v,vorbis_info *vi);
extern int      vorbis_synthesis(vorbis_block *vb,ogg_packet *op);
extern int      vorbis_synthesis_trackonly(vorbis_block *vb,ogg_packet *op);
extern int      vorbis_synthesis_blockin(vorbis_dsp_state *v,vorbis_block *vb);
extern int      vorbis_synthesis_pcmout(vorbis_dsp_state *v,float ***pcm);
extern int      vorbis_synthesis_read(vorbis_dsp_state *v,int samples);
extern long     vorbis_packet_blocksize(vorbis_info *vi,ogg_packet *op);

/* Vorbis ERRORS and return codes ***********************************/

#define OV_FALSE      -1
#define OV_EOF        -2
#define OV_HOLE       -3

#define OV_EREAD      -128
#define OV_EFAULT     -129
#define OV_EIMPL      -130
#define OV_EINVAL     -131
#define OV_ENOTVORBIS -132
#define OV_EBADHEADER -133
#define OV_EVERSION   -134
#define OV_ENOTAUDIO  -135
#define OV_EBADPACKET -136
#define OV_EBADLINK   -137
#define OV_ENOSEEK    -138

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/* ---- end codec.h ---- */

/* The function prototypes for the callbacks are basically the same as for
 * the stdio functions fread, fseek, fclose, ftell.
 * The one difference is that the FILE * arguments have been replaced with
 * a void * - this is to be used as a pointer to whatever internal data these
 * functions might need. In the stdio case, it's just a FILE * cast to a void *
 *
 * If you use other functions, check the docs for these functions and return
 * the right values. For seek_func(), you *MUST* return -1 if the stream is
 * unseekable
 */
typedef struct {
  size_t (*read_func)  (void *ptr, size_t size, size_t nmemb, void *datasource);
  int    (*seek_func)  (void *datasource, ogg_int64_t offset, int whence);
  int    (*close_func) (void *datasource);
  long   (*tell_func)  (void *datasource);
} ov_callbacks;

#define  NOTOPEN   0
#define  PARTOPEN  1
#define  OPENED    2
#define  STREAMSET 3
#define  INITSET   4

typedef struct OggVorbis_File {
  void            *datasource; /* Pointer to a FILE *, etc. */
  int              seekable;
  ogg_int64_t      offset;
  ogg_int64_t      end;
  ogg_sync_state   oy;

  /* If the FILE handle isn't seekable (eg, a pipe), only the current
     stream appears */
  int              links;
  ogg_int64_t     *offsets;
  ogg_int64_t     *dataoffsets;
  long            *serialnos;
  ogg_int64_t     *pcmlengths; /* overloaded to maintain binary
                                  compatability; x2 size, stores both
                                  beginning and end values */
  vorbis_info     *vi;
  vorbis_comment  *vc;

  /* Decoding working state local storage */
  ogg_int64_t      pcm_offset;
  int              ready_state;
  long             current_serialno;
  int              current_link;

  double           bittrack;
  double           samptrack;

  ogg_stream_state os; /* take physical pages, weld into a logical
                          stream of packets */
  vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
  vorbis_block     vb; /* local working space for packet->PCM decode */

  ov_callbacks callbacks;

} OggVorbis_File;

extern int ov_clear(OggVorbis_File *vf);
extern int ov_open(FILE *f,OggVorbis_File *vf,char *initial,long ibytes);
extern int ov_open_callbacks(void *datasource, OggVorbis_File *vf,
                char *initial, long ibytes, ov_callbacks callbacks);

extern int ov_test(FILE *f,OggVorbis_File *vf,char *initial,long ibytes);
extern int ov_test_callbacks(void *datasource, OggVorbis_File *vf,
                char *initial, long ibytes, ov_callbacks callbacks);
extern int ov_test_open(OggVorbis_File *vf);

extern long ov_bitrate(OggVorbis_File *vf,int i);
extern long ov_bitrate_instant(OggVorbis_File *vf);
extern long ov_streams(OggVorbis_File *vf);
extern long ov_seekable(OggVorbis_File *vf);
extern long ov_serialnumber(OggVorbis_File *vf,int i);

extern ogg_int64_t ov_raw_total(OggVorbis_File *vf,int i);
extern ogg_int64_t ov_pcm_total(OggVorbis_File *vf,int i);
extern double ov_time_total(OggVorbis_File *vf,int i);

extern int ov_raw_seek(OggVorbis_File *vf,ogg_int64_t pos);
extern int ov_pcm_seek(OggVorbis_File *vf,ogg_int64_t pos);
extern int ov_pcm_seek_page(OggVorbis_File *vf,ogg_int64_t pos);
extern int ov_time_seek(OggVorbis_File *vf,double pos);
extern int ov_time_seek_page(OggVorbis_File *vf,double pos);

extern ogg_int64_t ov_raw_tell(OggVorbis_File *vf);
extern ogg_int64_t ov_pcm_tell(OggVorbis_File *vf);
extern double ov_time_tell(OggVorbis_File *vf);

extern vorbis_info *ov_info(OggVorbis_File *vf,int link);
extern vorbis_comment *ov_comment(OggVorbis_File *vf,int link);

extern long ov_read_float(OggVorbis_File *vf,float ***pcm_channels,int samples,
                          int *bitstream);
extern long ov_read(OggVorbis_File *vf,char *buffer,int length,
                    int bigendianp,int word,int sgned,int *bitstream);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif



/* ---- end vorbis/vorbisfile.h ---- */

/* ---- os.h ---- */
#ifndef _OS_H
#define _OS_H
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

 function: #ifdef jail to whip a few platforms into the UNIX ideal.
 last mod: $Id: os.h,v 1.32 2002/07/11 06:40:49 xiphmont Exp $

 ********************************************************************/

/* #include <math.h> : included above */

/* ---- misc.h ---- */
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

 function: miscellaneous prototypes
 last mod: $Id: misc.h,v 1.12 2002/06/28 22:19:37 xiphmont Exp $

 ********************************************************************/

#ifndef _V_RANDOM_H_
#define _V_RANDOM_H_

extern int analysis_noisy;

extern void *_vorbis_block_alloc(vorbis_block *vb,long bytes);
extern void _vorbis_block_ripcord(vorbis_block *vb);
extern void _analysis_output(char *base,int i,float *v,int n,int bark,int dB,
                             ogg_int64_t off);

#ifdef DEBUG_MALLOC

#define _VDBG_GRAPHFILE "malloc.m"
extern void *_VDBG_malloc(void *ptr,long bytes,char *file,long line);
extern void _VDBG_free(void *ptr,char *file,long line);

#ifndef MISC_C
#undef _ogg_malloc
#undef _ogg_calloc
#undef _ogg_realloc
#undef _ogg_free

#define _ogg_malloc(x) _VDBG_malloc(NULL,(x),__FILE__,__LINE__)
#define _ogg_calloc(x,y) _VDBG_malloc(NULL,(x)*(y),__FILE__,__LINE__)
#define _ogg_realloc(x,y) _VDBG_malloc((x),(y),__FILE__,__LINE__)
#define _ogg_free(x) _VDBG_free((x),__FILE__,__LINE__)
#endif
#endif

#endif





/* ---- end misc.h ---- */

#ifndef _V_IFDEFJAIL_H_
#  define _V_IFDEFJAIL_H_

#  ifdef __GNUC__
#    define STIN static __inline__
#  elif _WIN32
#    define STIN static __inline
#else
#  define STIN static
#endif

#ifndef M_PI
#  define M_PI (3.1415926536f)
#endif

#ifdef _WIN32
/* #include <malloc.h> : included above */
#  define rint(x)   (floor((x)+0.5f))
#  define NO_FLOAT_MATH_LIB
#  define FAST_HYPOT(a, b) sqrt((a)*(a) + (b)*(b))
#endif

#ifndef FAST_HYPOT
#  define FAST_HYPOT hypot
#endif

#endif

#ifdef HAVE_ALLOCA_H
/* #  include <alloca.h> : declarations supplied by the prelude */
#endif

#ifdef USE_MEMORY_H
/* #  include <memory.h> : declarations supplied by the prelude */
#endif

#ifndef min
#  define min(x,y)  ((x)>(y)?(y):(x))
#endif

#ifndef max
#  define max(x,y)  ((x)<(y)?(y):(x))
#endif

#if defined(__i386__) && defined(__GNUC__) && !defined(__BEOS__)
#  define VORBIS_FPU_CONTROL
/* both GCC and MSVC are kinda stupid about rounding/casting to int.
   Because of encapsulation constraints (GCC can't see inside the asm
   block and so we end up doing stupid things like a store/load that
   is collectively a noop), we do it this way */

/* we must set up the fpu before this works!! */

typedef ogg_int16_t vorbis_fpu_control;

static inline void vorbis_fpu_setround(vorbis_fpu_control *fpu){
  ogg_int16_t ret;
  ogg_int16_t temp;
  __asm__ __volatile__("fnstcw %0\n\t"
          "movw %0,%%dx\n\t"
          "orw $62463,%%dx\n\t"
          "movw %%dx,%1\n\t"
          "fldcw %1\n\t":"=m"(ret):"m"(temp): "dx");
  *fpu=ret;
}

static inline void vorbis_fpu_restore(vorbis_fpu_control fpu){
  __asm__ __volatile__("fldcw %0":: "m"(fpu));
}

/* assumes the FPU is in round mode! */
static inline int vorbis_ftoi(double f){  /* yes, double!  Otherwise,
                                             we get extra fst/fld to
                                             truncate precision */
  int i;
  __asm__("fistl %0": "=m"(i) : "t"(f));
  return(i);
}
#endif


#if defined(_WIN32) && !defined(__GNUC__) && !defined(__BORLANDC__)
#  define VORBIS_FPU_CONTROL

typedef ogg_int16_t vorbis_fpu_control;

static __inline int vorbis_ftoi(double f){
        int i;
        __asm{
                fld f
                fistp i
        }
        return i;
}

static __inline void vorbis_fpu_setround(vorbis_fpu_control *fpu){
}

static __inline void vorbis_fpu_restore(vorbis_fpu_control fpu){
}

#endif


#ifndef VORBIS_FPU_CONTROL

typedef int vorbis_fpu_control;

static int vorbis_ftoi(double f){
  return (int)(f+.5);
}

/* We don't have special code for this compiler/arch, so do it the slow way */
#  define vorbis_fpu_setround(vorbis_fpu_control) {}
#  define vorbis_fpu_restore(vorbis_fpu_control) {}

#endif

#endif /* _OS_H */

/* ---- end os.h ---- */

/* A 'chained bitstream' is a Vorbis bitstream that contains more than
   one logical bitstream arranged end to end (the only form of Ogg
   multiplexing allowed in a Vorbis bitstream; grouping [parallel
   multiplexing] is not allowed in Vorbis) */

/* A Vorbis file can be played beginning to end (streamed) without
   worrying ahead of time about chaining (see decoder_example.c).  If
   we have the whole file, however, and want random access
   (seeking/scrubbing) or desire to know the total length/time of a
   file, we need to account for the possibility of chaining. */

/* We can handle things a number of ways; we can determine the entire
   bitstream structure right off the bat, or find pieces on demand.
   This example determines and caches structure for the entire
   bitstream, but builds a virtual decoder on the fly when moving
   between links in the chain. */

/* There are also different ways to implement seeking.  Enough
   information exists in an Ogg bitstream to seek to
   sample-granularity positions in the output.  Or, one can seek by
   picking some portion of the stream roughly in the desired area if
   we only want coarse navigation through the stream. */

/*************************************************************************
 * Many, many internal helpers.  The intention is not to be confusing;
 * rampant duplication and monolithic function implementation would be
 * harder to understand anyway.  The high level functions are last.  Begin
 * grokking near the end of the file */

/* read a little more data from the file/pipe into the ogg_sync framer
*/
#define CHUNKSIZE 8500 /* a shade over 8k; anyone using pages well
                          over 8k gets what they deserve */
static long _get_data(OggVorbis_File *vf){
  errno=0;
  if(vf->datasource){
    char *buffer=ogg_sync_buffer(&vf->oy,CHUNKSIZE);
    long bytes=(vf->callbacks.read_func)(buffer,1,CHUNKSIZE,vf->datasource);
    if(bytes>0)ogg_sync_wrote(&vf->oy,bytes);
    if(bytes==0 && errno)return(-1);
    return(bytes);
  }else
    return(0);
}

/* save a tiny smidge of verbosity to make the code more readable */
static void _seek_helper(OggVorbis_File *vf,ogg_int64_t offset){
  if(vf->datasource){
    (vf->callbacks.seek_func)(vf->datasource, offset, SEEK_SET);
    vf->offset=offset;
    ogg_sync_reset(&vf->oy);
  }else{
    /* shouldn't happen unless someone writes a broken callback */
    return;
  }
}

/* The read/seek functions track absolute position within the stream */

/* from the head of the stream, get the next page.  boundary specifies
   if the function is allowed to fetch more data from the stream (and
   how much) or only use internally buffered data.

   boundary: -1) unbounded search
              0) read no additional data; use cached only
              n) search for a new page beginning for n bytes

   return:   <0) did not find a page (OV_FALSE, OV_EOF, OV_EREAD)
              n) found a page at absolute offset n */

static ogg_int64_t _get_next_page(OggVorbis_File *vf,ogg_page *og,
                                  ogg_int64_t boundary){
  if(boundary>0)boundary+=vf->offset;
  while(1){
    long more;

    if(boundary>0 && vf->offset>=boundary)return(OV_FALSE);
    more=ogg_sync_pageseek(&vf->oy,og);

    if(more<0){
      /* skipped n bytes */
      vf->offset-=more;
    }else{
      if(more==0){
        /* send more paramedics */
        if(!boundary)return(OV_FALSE);
        {
          long ret=_get_data(vf);
          if(ret==0)return(OV_EOF);
          if(ret<0)return(OV_EREAD);
        }
      }else{
        /* got a page.  Return the offset at the page beginning,
           advance the internal offset past the page end */
        ogg_int64_t ret=vf->offset;
        vf->offset+=more;
        return(ret);

      }
    }
  }
}

/* find the latest page beginning before the current stream cursor
   position. Much dirtier than the above as Ogg doesn't have any
   backward search linkage.  no 'readp' as it will certainly have to
   read. */
/* returns offset or OV_EREAD, OV_FAULT */
static ogg_int64_t _get_prev_page(OggVorbis_File *vf,ogg_page *og){
  ogg_int64_t begin=vf->offset;
  ogg_int64_t end=begin;
  ogg_int64_t ret;
  ogg_int64_t offset=-1;

  while(offset==-1){
    begin-=CHUNKSIZE;
    if(begin<0)
      begin=0;
    _seek_helper(vf,begin);
    while(vf->offset<end){
      ret=_get_next_page(vf,og,end-vf->offset);
      if(ret==OV_EREAD)return(OV_EREAD);
      if(ret<0){
        break;
      }else{
        offset=ret;
      }
    }
  }

  /* we have the offset.  Actually snork and hold the page now */
  _seek_helper(vf,offset);
  ret=_get_next_page(vf,og,CHUNKSIZE);
  if(ret<0)
    /* this shouldn't be possible */
    return(OV_EFAULT);

  return(offset);
}

/* finds each bitstream link one at a time using a bisection search
   (has to begin by knowing the offset of the lb's initial page).
   Recurses for each link so it can alloc the link storage after
   finding them all, then unroll and fill the cache at the same time */
static int _bisect_forward_serialno(OggVorbis_File *vf,
                                    ogg_int64_t begin,
                                    ogg_int64_t searched,
                                    ogg_int64_t end,
                                    long currentno,
                                    long m){
  ogg_int64_t endsearched=end;
  ogg_int64_t next=end;
  ogg_page og;
  ogg_int64_t ret;

  /* the below guards against garbage seperating the last and
     first pages of two links. */
  while(searched<endsearched){
    ogg_int64_t bisect;

    if(endsearched-searched<CHUNKSIZE){
      bisect=searched;
    }else{
      bisect=(searched+endsearched)/2;
    }

    _seek_helper(vf,bisect);
    ret=_get_next_page(vf,&og,-1);
    if(ret==OV_EREAD)return(OV_EREAD);
    if(ret<0 || ogg_page_serialno(&og)!=currentno){
      endsearched=bisect;
      if(ret>=0)next=ret;
    }else{
      searched=ret+og.header_len+og.body_len;
    }
  }

  _seek_helper(vf,next);
  ret=_get_next_page(vf,&og,-1);
  if(ret==OV_EREAD)return(OV_EREAD);

  if(searched>=end || ret<0){
    vf->links=m+1;
    vf->offsets=_ogg_malloc((vf->links+1)*sizeof(*vf->offsets));
    vf->serialnos=_ogg_malloc(vf->links*sizeof(*vf->serialnos));
    vf->offsets[m+1]=searched;
  }else{
    ret=_bisect_forward_serialno(vf,next,vf->offset,
                                 end,ogg_page_serialno(&og),m+1);
    if(ret==OV_EREAD)return(OV_EREAD);
  }

  vf->offsets[m]=begin;
  vf->serialnos[m]=currentno;
  return(0);
}

/* uses the local ogg_stream storage in vf; this is important for
   non-streaming input sources */
static int _fetch_headers(OggVorbis_File *vf,vorbis_info *vi,vorbis_comment *vc,
                          long *serialno,ogg_page *og_ptr){
  ogg_page og;
  ogg_packet op;
  int i,ret;

  if(!og_ptr){
    ogg_int64_t llret=_get_next_page(vf,&og,CHUNKSIZE);
    if(llret==OV_EREAD)return(OV_EREAD);
    if(llret<0)return OV_ENOTVORBIS;
    og_ptr=&og;
  }

  ogg_stream_reset_serialno(&vf->os,ogg_page_serialno(og_ptr));
  if(serialno)*serialno=vf->os.serialno;
  vf->ready_state=STREAMSET;

  /* extract the initial header from the first page and verify that the
     Ogg bitstream is in fact Vorbis data */

  vorbis_info_init(vi);
  vorbis_comment_init(vc);

  i=0;
  while(i<3){
    ogg_stream_pagein(&vf->os,og_ptr);
    while(i<3){
      int result=ogg_stream_packetout(&vf->os,&op);
      if(result==0)break;
      if(result==-1){
        ret=OV_EBADHEADER;
        goto bail_header;
      }
      if((ret=vorbis_synthesis_headerin(vi,vc,&op))){
        goto bail_header;
      }
      i++;
    }
    if(i<3)
      if(_get_next_page(vf,og_ptr,CHUNKSIZE)<0){
        ret=OV_EBADHEADER;
        goto bail_header;
      }
  }
  return 0;

 bail_header:
  vorbis_info_clear(vi);
  vorbis_comment_clear(vc);
  vf->ready_state=OPENED;

  return ret;
}

/* last step of the OggVorbis_File initialization; get all the
   vorbis_info structs and PCM positions.  Only called by the seekable
   initialization (local stream storage is hacked slightly; pay
   attention to how that's done) */

/* this is void and does not propogate errors up because we want to be
   able to open and use damaged bitstreams as well as we can.  Just
   watch out for missing information for links in the OggVorbis_File
   struct */
static void _prefetch_all_headers(OggVorbis_File *vf, ogg_int64_t dataoffset){
  ogg_page og;
  int i;
  ogg_int64_t ret;

  vf->vi=_ogg_realloc(vf->vi,vf->links*sizeof(*vf->vi));
  vf->vc=_ogg_realloc(vf->vc,vf->links*sizeof(*vf->vc));
  vf->dataoffsets=_ogg_malloc(vf->links*sizeof(*vf->dataoffsets));
  vf->pcmlengths=_ogg_malloc(vf->links*2*sizeof(*vf->pcmlengths));

  for(i=0;i<vf->links;i++){
    if(i==0){
      /* we already grabbed the initial header earlier.  Just set the offset */
      vf->dataoffsets[i]=dataoffset;
      _seek_helper(vf,dataoffset);

    }else{

      /* seek to the location of the initial header */

      _seek_helper(vf,vf->offsets[i]);
      if(_fetch_headers(vf,vf->vi+i,vf->vc+i,NULL,NULL)<0){
        vf->dataoffsets[i]=-1;
      }else{
        vf->dataoffsets[i]=vf->offset;
      }
    }

    /* fetch beginning PCM offset */

    if(vf->dataoffsets[i]!=-1){
      ogg_int64_t accumulated=0;
      long        lastblock=-1;
      int         result;

      ogg_stream_reset_serialno(&vf->os,vf->serialnos[i]);

      while(1){
        ogg_packet op;

        ret=_get_next_page(vf,&og,-1);
        if(ret<0)
          /* this should not be possible unless the file is
             truncated/mangled */
          break;

        if(ogg_page_serialno(&og)!=vf->serialnos[i])
          break;

        /* count blocksizes of all frames in the page */
        ogg_stream_pagein(&vf->os,&og);
        while((result=ogg_stream_packetout(&vf->os,&op))){
          if(result>0){ /* ignore holes */
            long thisblock=vorbis_packet_blocksize(vf->vi+i,&op);
            if(lastblock!=-1)
              accumulated+=(lastblock+thisblock)>>2;
            lastblock=thisblock;
          }
        }

        if(ogg_page_granulepos(&og)!=-1){
          /* pcm offset of last packet on the first audio page */
          accumulated= ogg_page_granulepos(&og)-accumulated;
          break;
        }
      }

      /* less than zero?  This is a stream with samples trimmed off
         the beginning, a normal occurrence; set the offset to zero */
      if(accumulated<0)accumulated=0;

      vf->pcmlengths[i*2]=accumulated;
    }

    /* get the PCM length of this link. To do this,
       get the last page of the stream */
    {
      ogg_int64_t end=vf->offsets[i+1];
      _seek_helper(vf,end);

      while(1){
        ret=_get_prev_page(vf,&og);
        if(ret<0){
          /* this should not be possible */
          vorbis_info_clear(vf->vi+i);
          vorbis_comment_clear(vf->vc+i);
          break;
        }
        if(ogg_page_granulepos(&og)!=-1){
          vf->pcmlengths[i*2+1]=ogg_page_granulepos(&og)-vf->pcmlengths[i*2];
          break;
        }
        vf->offset=ret;
      }
    }
  }
}

static void _make_decode_ready(OggVorbis_File *vf){
  if(vf->ready_state!=STREAMSET)return;
  if(vf->seekable){
    vorbis_synthesis_init(&vf->vd,vf->vi+vf->current_link);
  }else{
    vorbis_synthesis_init(&vf->vd,vf->vi);
  }
  vorbis_block_init(&vf->vd,&vf->vb);
  vf->ready_state=INITSET;
  return;
}

static int _open_seekable2(OggVorbis_File *vf){
  long serialno=vf->current_serialno;
  ogg_int64_t dataoffset=vf->offset, end;
  ogg_page og;

  /* we're partially open and have a first link header state in
     storage in vf */
  /* we can seek, so set out learning all about this file */
  (vf->callbacks.seek_func)(vf->datasource,0,SEEK_END);
  vf->offset=vf->end=(vf->callbacks.tell_func)(vf->datasource);

  /* We get the offset for the last page of the physical bitstream.
     Most OggVorbis files will contain a single logical bitstream */
  end=_get_prev_page(vf,&og);
  if(end<0)return(end);

  /* more than one logical bitstream? */
  if(ogg_page_serialno(&og)!=serialno){

    /* Chained bitstream. Bisect-search each logical bitstream
       section.  Do so based on serial number only */
    if(_bisect_forward_serialno(vf,0,0,end+1,serialno,0)<0)return(OV_EREAD);

  }else{

    /* Only one logical bitstream */
    if(_bisect_forward_serialno(vf,0,end,end+1,serialno,0))return(OV_EREAD);

  }

  /* the initial header memory is referenced by vf after; don't free it */
  _prefetch_all_headers(vf,dataoffset);
  return(ov_raw_seek(vf,0));
}

/* clear out the current logical bitstream decoder */
static void _decode_clear(OggVorbis_File *vf){
  vorbis_dsp_clear(&vf->vd);
  vorbis_block_clear(&vf->vb);
  vf->ready_state=OPENED;

  vf->bittrack=0.f;
  vf->samptrack=0.f;
}

/* fetch and process a packet.  Handles the case where we're at a
   bitstream boundary and dumps the decoding machine.  If the decoding
   machine is unloaded, it loads it.  It also keeps pcm_offset up to
   date (seek and read both use this.  seek uses a special hack with
   readp).

   return: <0) error, OV_HOLE (lost packet) or OV_EOF
            0) need more data (only if readp==0)
            1) got a packet
*/

static int _fetch_and_process_packet(OggVorbis_File *vf,
                                     ogg_packet *op_in,
                                     int readp){
  ogg_page og;

  /* handle one packet.  Try to fetch it from current stream state */
  /* extract packets from page */
  while(1){

    /* process a packet if we can.  If the machine isn't loaded,
       neither is a page */
    if(vf->ready_state==INITSET){
      while(1) {
        ogg_packet op;
        ogg_packet *op_ptr=(op_in?op_in:&op);
        int result=ogg_stream_packetout(&vf->os,op_ptr);
        ogg_int64_t granulepos;

        op_in=NULL;
        if(result==-1)return(OV_HOLE); /* hole in the data. */
        if(result>0){
          /* got a packet.  process it */
          granulepos=op_ptr->granulepos;
          if(!vorbis_synthesis(&vf->vb,op_ptr)){ /* lazy check for lazy
                                                    header handling.  The
                                                    header packets aren't
                                                    audio, so if/when we
                                                    submit them,
                                                    vorbis_synthesis will
                                                    reject them */

            /* suck in the synthesis data and track bitrate */
            {
              int oldsamples=vorbis_synthesis_pcmout(&vf->vd,NULL);
              /* for proper use of libvorbis within libvorbisfile,
                 oldsamples will always be zero. */
              if(oldsamples)return(OV_EFAULT);

              vorbis_synthesis_blockin(&vf->vd,&vf->vb);
              vf->samptrack+=vorbis_synthesis_pcmout(&vf->vd,NULL)-oldsamples;
              vf->bittrack+=op_ptr->bytes*8;
            }

            /* update the pcm offset. */
            if(granulepos!=-1 && !op_ptr->e_o_s){
              int link=(vf->seekable?vf->current_link:0);
              int i,samples;

              /* this packet has a pcm_offset on it (the last packet
                 completed on a page carries the offset) After processing
                 (above), we know the pcm position of the *last* sample
                 ready to be returned. Find the offset of the *first*

                 As an aside, this trick is inaccurate if we begin
                 reading anew right at the last page; the end-of-stream
                 granulepos declares the last frame in the stream, and the
                 last packet of the last page may be a partial frame.
                 So, we need a previous granulepos from an in-sequence page
                 to have a reference point.  Thus the !op_ptr->e_o_s clause
                 above */

              if(vf->seekable && link>0)
                granulepos-=vf->pcmlengths[link*2];
              if(granulepos<0)granulepos=0; /* actually, this
                                               shouldn't be possible
                                               here unless the stream
                                               is very broken */

              samples=vorbis_synthesis_pcmout(&vf->vd,NULL);

              granulepos-=samples;
              for(i=0;i<link;i++)
                granulepos+=vf->pcmlengths[i*2+1];
              vf->pcm_offset=granulepos;
            }
            return(1);
          }
        }
        else
          break;
      }
    }

    if(vf->ready_state>=OPENED){
      if(!readp)return(0);
      if(_get_next_page(vf,&og,-1)<0)return(OV_EOF); /* eof.
                                                        leave unitialized */
      /* bitrate tracking; add the header's bytes here, the body bytes
         are done by packet above */
      vf->bittrack+=og.header_len*8;

      /* has our decoding just traversed a bitstream boundary? */
      if(vf->ready_state==INITSET){
        if(vf->current_serialno!=ogg_page_serialno(&og)){
          _decode_clear(vf);

          if(!vf->seekable){
            vorbis_info_clear(vf->vi);
            vorbis_comment_clear(vf->vc);
          }
        }
      }
    }

    /* Do we need to load a new machine before submitting the page? */
    /* This is different in the seekable and non-seekable cases.

       In the seekable case, we already have all the header
       information loaded and cached; we just initialize the machine
       with it and continue on our merry way.

       In the non-seekable (streaming) case, we'll only be at a
       boundary if we just left the previous logical bitstream and
       we're now nominally at the header of the next bitstream
    */

    if(vf->ready_state!=INITSET){
      int link;

      if(vf->ready_state<STREAMSET){
        if(vf->seekable){
          vf->current_serialno=ogg_page_serialno(&og);

          /* match the serialno to bitstream section.  We use this rather than
             offset positions to avoid problems near logical bitstream
             boundaries */
          for(link=0;link<vf->links;link++)
            if(vf->serialnos[link]==vf->current_serialno)break;
          if(link==vf->links)return(OV_EBADLINK); /* sign of a bogus
                                                     stream.  error out,
                                                     leave machine
                                                     uninitialized */

          vf->current_link=link;

          ogg_stream_reset_serialno(&vf->os,vf->current_serialno);
          vf->ready_state=STREAMSET;

        }else{
          /* we're streaming */
          /* fetch the three header packets, build the info struct */

          int ret=_fetch_headers(vf,vf->vi,vf->vc,&vf->current_serialno,&og);
          if(ret)return(ret);
          vf->current_link++;
          link=0;
        }
      }

      _make_decode_ready(vf);
    }
    ogg_stream_pagein(&vf->os,&og);
  }
}

/* if, eg, 64 bit stdio is configured by default, this will build with
   fseek64 */
static int _fseek64_wrap(FILE *f,ogg_int64_t off,int whence){
  if(f==NULL)return(-1);
  return fseek(f,off,whence);
}

static int _ov_open1(void *f,OggVorbis_File *vf,char *initial,
                     long ibytes, ov_callbacks callbacks){
  int offsettest=(f?callbacks.seek_func(f,0,SEEK_CUR):-1);
  int ret;

  memset(vf,0,sizeof(*vf));
  vf->datasource=f;
  vf->callbacks = callbacks;

  /* init the framing state */
  ogg_sync_init(&vf->oy);

  /* perhaps some data was previously read into a buffer for testing
     against other stream types.  Allow initialization from this
     previously read data (as we may be reading from a non-seekable
     stream) */
  if(initial){
    char *buffer=ogg_sync_buffer(&vf->oy,ibytes);
    memcpy(buffer,initial,ibytes);
    ogg_sync_wrote(&vf->oy,ibytes);
  }

  /* can we seek? Stevens suggests the seek test was portable */
  if(offsettest!=-1)vf->seekable=1;

  /* No seeking yet; Set up a 'single' (current) logical bitstream
     entry for partial open */
  vf->links=1;
  vf->vi=_ogg_calloc(vf->links,sizeof(*vf->vi));
  vf->vc=_ogg_calloc(vf->links,sizeof(*vf->vc));
  ogg_stream_init(&vf->os,-1); /* fill in the serialno later */

  /* Try to fetch the headers, maintaining all the storage */
  if((ret=_fetch_headers(vf,vf->vi,vf->vc,&vf->current_serialno,NULL))<0){
    vf->datasource=NULL;
    ov_clear(vf);
  }else if(vf->ready_state < PARTOPEN)
    vf->ready_state=PARTOPEN;
  return(ret);
}

static int _ov_open2(OggVorbis_File *vf){
  if(vf->ready_state < OPENED)
    vf->ready_state=OPENED;
  if(vf->seekable){
    int ret=_open_seekable2(vf);
    if(ret){
      vf->datasource=NULL;
      ov_clear(vf);
    }
    return(ret);
  }
  return 0;
}


/* clear out the OggVorbis_File struct */
int ov_clear(OggVorbis_File *vf){
  if(vf){
    vorbis_block_clear(&vf->vb);
    vorbis_dsp_clear(&vf->vd);
    ogg_stream_clear(&vf->os);

    if(vf->vi && vf->links){
      int i;
      for(i=0;i<vf->links;i++){
        vorbis_info_clear(vf->vi+i);
        vorbis_comment_clear(vf->vc+i);
      }
      _ogg_free(vf->vi);
      _ogg_free(vf->vc);
    }
    if(vf->dataoffsets)_ogg_free(vf->dataoffsets);
    if(vf->pcmlengths)_ogg_free(vf->pcmlengths);
    if(vf->serialnos)_ogg_free(vf->serialnos);
    if(vf->offsets)_ogg_free(vf->offsets);
    ogg_sync_clear(&vf->oy);
    if(vf->datasource)(vf->callbacks.close_func)(vf->datasource);
    memset(vf,0,sizeof(*vf));
  }
#ifdef DEBUG_LEAKS
  _VDBG_dump();
#endif
  return(0);
}

/* inspects the OggVorbis file and finds/documents all the logical
   bitstreams contained in it.  Tries to be tolerant of logical
   bitstream sections that are truncated/woogie.

   return: -1) error
            0) OK
*/

int ov_open_callbacks(void *f,OggVorbis_File *vf,char *initial,long ibytes,
    ov_callbacks callbacks){
  int ret=_ov_open1(f,vf,initial,ibytes,callbacks);
  if(ret)return ret;
  return _ov_open2(vf);
}

int ov_open(FILE *f,OggVorbis_File *vf,char *initial,long ibytes){
  ov_callbacks callbacks = {
    (size_t (*)(void *, size_t, size_t, void *))  fread,
    (int (*)(void *, ogg_int64_t, int))              _fseek64_wrap,
    (int (*)(void *))                             fclose,
    (long (*)(void *))                            ftell
  };

  return ov_open_callbacks((void *)f, vf, initial, ibytes, callbacks);
}

/* Only partially open the vorbis file; test for Vorbisness, and load
   the headers for the first chain.  Do not seek (although test for
   seekability).  Use ov_test_open to finish opening the file, else
   ov_clear to close/free it. Same return codes as open. */

int ov_test_callbacks(void *f,OggVorbis_File *vf,char *initial,long ibytes,
    ov_callbacks callbacks)
{
  return _ov_open1(f,vf,initial,ibytes,callbacks);
}

int ov_test(FILE *f,OggVorbis_File *vf,char *initial,long ibytes){
  ov_callbacks callbacks = {
    (size_t (*)(void *, size_t, size_t, void *))  fread,
    (int (*)(void *, ogg_int64_t, int))              _fseek64_wrap,
    (int (*)(void *))                             fclose,
    (long (*)(void *))                            ftell
  };

  return ov_test_callbacks((void *)f, vf, initial, ibytes, callbacks);
}

int ov_test_open(OggVorbis_File *vf){
  if(vf->ready_state!=PARTOPEN)return(OV_EINVAL);
  return _ov_open2(vf);
}

/* How many logical bitstreams in this physical bitstream? */
long ov_streams(OggVorbis_File *vf){
  return vf->links;
}

/* Is the FILE * associated with vf seekable? */
long ov_seekable(OggVorbis_File *vf){
  return vf->seekable;
}

/* returns the bitrate for a given logical bitstream or the entire
   physical bitstream.  If the file is open for random access, it will
   find the *actual* average bitrate.  If the file is streaming, it
   returns the nominal bitrate (if set) else the average of the
   upper/lower bounds (if set) else -1 (unset).

   If you want the actual bitrate field settings, get them from the
   vorbis_info structs */

long ov_bitrate(OggVorbis_File *vf,int i){
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(i>=vf->links)return(OV_EINVAL);
  if(!vf->seekable && i!=0)return(ov_bitrate(vf,0));
  if(i<0){
    ogg_int64_t bits=0;
    int i;
    for(i=0;i<vf->links;i++)
      bits+=(vf->offsets[i+1]-vf->dataoffsets[i])*8;
    return(rint(bits/ov_time_total(vf,-1)));
  }else{
    if(vf->seekable){
      /* return the actual bitrate */
      return(rint((vf->offsets[i+1]-vf->dataoffsets[i])*8/ov_time_total(vf,i)));
    }else{
      /* return nominal if set */
      if(vf->vi[i].bitrate_nominal>0){
        return vf->vi[i].bitrate_nominal;
      }else{
        if(vf->vi[i].bitrate_upper>0){
          if(vf->vi[i].bitrate_lower>0){
            return (vf->vi[i].bitrate_upper+vf->vi[i].bitrate_lower)/2;
          }else{
            return vf->vi[i].bitrate_upper;
          }
        }
        return(OV_FALSE);
      }
    }
  }
}

/* returns the actual bitrate since last call.  returns -1 if no
   additional data to offer since last call (or at beginning of stream),
   EINVAL if stream is only partially open
*/
long ov_bitrate_instant(OggVorbis_File *vf){
  int link=(vf->seekable?vf->current_link:0);
  long ret;
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(vf->samptrack==0)return(OV_FALSE);
  ret=vf->bittrack/vf->samptrack*vf->vi[link].rate+.5;
  vf->bittrack=0.f;
  vf->samptrack=0.f;
  return(ret);
}

/* Guess */
long ov_serialnumber(OggVorbis_File *vf,int i){
  if(i>=vf->links)return(ov_serialnumber(vf,vf->links-1));
  if(!vf->seekable && i>=0)return(ov_serialnumber(vf,-1));
  if(i<0){
    return(vf->current_serialno);
  }else{
    return(vf->serialnos[i]);
  }
}

/* returns: total raw (compressed) length of content if i==-1
            raw (compressed) length of that logical bitstream for i==0 to n
            OV_EINVAL if the stream is not seekable (we can't know the length)
            or if stream is only partially open
*/
ogg_int64_t ov_raw_total(OggVorbis_File *vf,int i){
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable || i>=vf->links)return(OV_EINVAL);
  if(i<0){
    ogg_int64_t acc=0;
    int i;
    for(i=0;i<vf->links;i++)
      acc+=ov_raw_total(vf,i);
    return(acc);
  }else{
    return(vf->offsets[i+1]-vf->offsets[i]);
  }
}

/* returns: total PCM length (samples) of content if i==-1 PCM length
            (samples) of that logical bitstream for i==0 to n
            OV_EINVAL if the stream is not seekable (we can't know the
            length) or only partially open
*/
ogg_int64_t ov_pcm_total(OggVorbis_File *vf,int i){
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable || i>=vf->links)return(OV_EINVAL);
  if(i<0){
    ogg_int64_t acc=0;
    int i;
    for(i=0;i<vf->links;i++)
      acc+=ov_pcm_total(vf,i);
    return(acc);
  }else{
    return(vf->pcmlengths[i*2+1]);
  }
}

/* returns: total seconds of content if i==-1
            seconds in that logical bitstream for i==0 to n
            OV_EINVAL if the stream is not seekable (we can't know the
            length) or only partially open
*/
double ov_time_total(OggVorbis_File *vf,int i){
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable || i>=vf->links)return(OV_EINVAL);
  if(i<0){
    double acc=0;
    int i;
    for(i=0;i<vf->links;i++)
      acc+=ov_time_total(vf,i);
    return(acc);
  }else{
    return((double)(vf->pcmlengths[i*2+1])/vf->vi[i].rate);
  }
}

/* seek to an offset relative to the *compressed* data. This also
   scans packets to update the PCM cursor. It will cross a logical
   bitstream boundary, but only if it can't get any packets out of the
   tail of the bitstream we seek to (so no surprises).

   returns zero on success, nonzero on failure */

int ov_raw_seek(OggVorbis_File *vf,ogg_int64_t pos){
  ogg_stream_state work_os;

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable)
    return(OV_ENOSEEK); /* don't dump machine if we can't seek */

  if(pos<0 || pos>vf->end)return(OV_EINVAL);

  /* clear out decoding machine state */
  vf->pcm_offset=-1;
  _decode_clear(vf);

  _seek_helper(vf,pos);

  /* we need to make sure the pcm_offset is set, but we don't want to
     advance the raw cursor past good packets just to get to the first
     with a granulepos.  That's not equivalent behavior to beginning
     decoding as immediately after the seek position as possible.

     So, a hack.  We use two stream states; a local scratch state and
     a the shared vf->os stream state.  We use the local state to
     scan, and the shared state as a buffer for later decode.

     Unfortuantely, on the last page we still advance to last packet
     because the granulepos on the last page is not necessarily on a
     packet boundary, and we need to make sure the granpos is
     correct.
  */

  {
    ogg_page og;
    ogg_packet op;
    int lastblock=0;
    int accblock=0;
    int thisblock;
    int eosflag;

    ogg_stream_init(&work_os,-1); /* get the memory ready */

    while(1){
      if(vf->ready_state==STREAMSET){
        /* snarf/scan a packet if we can */
        int result=ogg_stream_packetout(&work_os,&op);

        if(result>0){

          if(vf->vi[vf->current_link].codec_setup)
            thisblock=vorbis_packet_blocksize(vf->vi+vf->current_link,&op);
          if(eosflag)
            ogg_stream_packetout(&vf->os,NULL);
          else
            if(lastblock)accblock+=(lastblock+thisblock)>>2;

          if(op.granulepos!=-1){
            int i,link=vf->current_link;
            ogg_int64_t granulepos=op.granulepos-vf->pcmlengths[link*2];
            if(granulepos<0)granulepos=0;

            for(i=0;i<link;i++)
              granulepos+=vf->pcmlengths[i*2+1];
            vf->pcm_offset=granulepos-accblock;
            break;
          }
          lastblock=thisblock;
          continue;
        }
      }

      if(!lastblock){
        if(_get_next_page(vf,&og,-1)<0){
          vf->pcm_offset=ov_pcm_total(vf,-1);
          break;
        }
      }else{
        /* huh?  Bogus stream with packets but no granulepos */
        vf->pcm_offset=-1;
        break;
      }

      /* has our decoding just traversed a bitstream boundary? */
      if(vf->ready_state==STREAMSET)
        if(vf->current_serialno!=ogg_page_serialno(&og)){
        _decode_clear(vf); /* clear out stream state */
        ogg_stream_clear(&work_os);
      }

      if(vf->ready_state<STREAMSET){
        int link;

        vf->current_serialno=ogg_page_serialno(&og);
        for(link=0;link<vf->links;link++)
          if(vf->serialnos[link]==vf->current_serialno)break;
        if(link==vf->links)goto seek_error; /* sign of a bogus stream.
                                               error out, leave
                                               machine uninitialized */
        vf->current_link=link;

        ogg_stream_reset_serialno(&vf->os,vf->current_serialno);
        ogg_stream_reset_serialno(&work_os,vf->current_serialno);
        vf->ready_state=STREAMSET;

      }

      ogg_stream_pagein(&vf->os,&og);
      ogg_stream_pagein(&work_os,&og);
      eosflag=ogg_page_eos(&og);
    }
  }

  ogg_stream_clear(&work_os);
  return(0);

 seek_error:
  /* dump the machine so we're in a known state */
  vf->pcm_offset=-1;
  ogg_stream_clear(&work_os);
  _decode_clear(vf);
  return OV_EBADLINK;
}

/* Page granularity seek (faster than sample granularity because we
   don't do the last bit of decode to find a specific sample).

   Seek to the last [granule marked] page preceeding the specified pos
   location, such that decoding past the returned point will quickly
   arrive at the requested position. */
int ov_pcm_seek_page(OggVorbis_File *vf,ogg_int64_t pos){
  int link=-1;
  ogg_int64_t result=0;
  ogg_int64_t total=ov_pcm_total(vf,-1);

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable)return(OV_ENOSEEK);

  if(pos<0 || pos>total)return(OV_EINVAL);

  /* which bitstream section does this pcm offset occur in? */
  for(link=vf->links-1;link>=0;link--){
    total-=vf->pcmlengths[link*2+1];
    if(pos>=total)break;
  }

  /* search within the logical bitstream for the page with the highest
     pcm_pos preceeding (or equal to) pos.  There is a danger here;
     missing pages or incorrect frame number information in the
     bitstream could make our task impossible.  Account for that (it
     would be an error condition) */

  /* new search algorithm by HB (Nicholas Vinen) */
  {
    ogg_int64_t end=vf->offsets[link+1];
    ogg_int64_t begin=vf->offsets[link];
    ogg_int64_t begintime = vf->pcmlengths[link*2];
    ogg_int64_t endtime = vf->pcmlengths[link*2+1]+begintime;
    ogg_int64_t target=pos-total+begintime;
    ogg_int64_t best=begin;

    ogg_page og;
    while(begin<end){
      ogg_int64_t bisect;

      if(end-begin<CHUNKSIZE){
        bisect=begin;
      }else{
        /* take a (pretty decent) guess. */
        bisect=begin +
          (target-begintime)*(end-begin)/(endtime-begintime) - CHUNKSIZE;
        if(bisect<=begin)
          bisect=begin+1;
      }

      _seek_helper(vf,bisect);

      while(begin<end){
        result=_get_next_page(vf,&og,end-vf->offset);
        if(result==OV_EREAD) goto seek_error;
        if(result<0){
          if(bisect<=begin+1)
            end=begin; /* found it */
          else{
            if(bisect==0) goto seek_error;
            bisect-=CHUNKSIZE;
            if(bisect<=begin)bisect=begin+1;
            _seek_helper(vf,bisect);
          }
        }else{
          ogg_int64_t granulepos=ogg_page_granulepos(&og);
          if(granulepos==-1)continue;
          if(granulepos<target){
            best=result;  /* raw offset of packet with granulepos */
            begin=vf->offset; /* raw offset of next page */
            begintime=granulepos;

            if(target-begintime>44100)break;
            bisect=begin; /* *not* begin + 1 */
          }else{
            if(bisect<=begin+1)
              end=begin;  /* found it */
            else{
              if(end==vf->offset){ /* we're pretty close - we'd be stuck in */
                end=result;
                bisect-=CHUNKSIZE; /* an endless loop otherwise. */
                if(bisect<=begin)bisect=begin+1;
                _seek_helper(vf,bisect);
              }else{
                end=result;
                endtime=granulepos;
                break;
              }
            }
          }
        }
      }
    }

    /* found our page. seek to it, update pcm offset. Easier case than
       raw_seek, don't keep packets preceeding granulepos. */
    {
      ogg_page og;
      ogg_packet op;
      /* clear out decoding machine state */
      _decode_clear(vf);
      /* seek */
      _seek_helper(vf,best);

      if(_get_next_page(vf,&og,-1)<0)return(OV_EOF); /* shouldn't happen */
      vf->current_serialno=ogg_page_serialno(&og);
      vf->current_link=link;

      ogg_stream_reset_serialno(&vf->os,vf->current_serialno);
      vf->ready_state=STREAMSET;
      ogg_stream_pagein(&vf->os,&og);

      /* pull out all but last packet; the one with granulepos */
      while(1){
        result=ogg_stream_packetpeek(&vf->os,&op);
        if(result==0){
          /* !!! the packet finishing this page originated on a
             preceeding page. Keep fetching previous pages until we
             get one with a granulepos or without the 'continued' flag
             set.  Then just use raw_seek for simplicity. */

          _decode_clear(vf);
          _seek_helper(vf,best);

          while(1){
            result=_get_prev_page(vf,&og);
            if(result<0) goto seek_error;
            if(ogg_page_granulepos(&og)>-1 ||
               !ogg_page_continued(&og)){
              return ov_raw_seek(vf,result);
            }
            vf->offset=result;
          }
        }
        if(result<0){
      result = OV_EBADPACKET;
      goto seek_error;
    }
        if(op.granulepos!=-1){
          vf->pcm_offset=op.granulepos-vf->pcmlengths[vf->current_link*2];
          if(vf->pcm_offset<0)vf->pcm_offset=0;
          vf->pcm_offset+=total;
          break;
        }else
          result=ogg_stream_packetout(&vf->os,NULL);
      }
    }
  }

  /* verify result */
  if(vf->pcm_offset>pos || pos>ov_pcm_total(vf,-1)){
    result=OV_EFAULT;
    goto seek_error;
  }
  return(0);

 seek_error:
  /* dump machine so we're in a known state */
  vf->pcm_offset=-1;
  _decode_clear(vf);
  return (int)result;
}

/* seek to a sample offset relative to the decompressed pcm stream
   returns zero on success, nonzero on failure */

int ov_pcm_seek(OggVorbis_File *vf,ogg_int64_t pos){
  int thisblock,lastblock=0;
  int ret=ov_pcm_seek_page(vf,pos);
  if(ret<0)return(ret);
  _make_decode_ready(vf);

  /* discard leading packets we don't need for the lapping of the
     position we want; don't decode them */

  while(1){
    ogg_packet op;
    ogg_page og;

    int ret=ogg_stream_packetpeek(&vf->os,&op);
    if(ret>0){
      thisblock=vorbis_packet_blocksize(vf->vi+vf->current_link,&op);
      if(thisblock<0)thisblock=0; /* non audio packet */
      if(lastblock)vf->pcm_offset+=(lastblock+thisblock)>>2;

      if(vf->pcm_offset+((thisblock+
                          vorbis_info_blocksize(vf->vi,1))>>2)>=pos)break;

      /* remove the packet from packet queue and track its granulepos */
      ogg_stream_packetout(&vf->os,NULL);
      vorbis_synthesis_trackonly(&vf->vb,&op);  /* set up a vb with
                                                   only tracking, no
                                                   pcm_decode */
      vorbis_synthesis_blockin(&vf->vd,&vf->vb);

      /* end of logical stream case is hard, especially with exact
         length positioning. */

      if(op.granulepos>-1){
        int i;
        /* always believe the stream markers */
        vf->pcm_offset=op.granulepos-vf->pcmlengths[vf->current_link*2];
        if(vf->pcm_offset<0)vf->pcm_offset=0;
        for(i=0;i<vf->current_link;i++)
          vf->pcm_offset+=vf->pcmlengths[i*2+1];
      }

      lastblock=thisblock;

    }else{
      if(ret<0 && ret!=OV_HOLE)break;

      /* suck in a new page */
      if(_get_next_page(vf,&og,-1)<0)break;
      if(vf->current_serialno!=ogg_page_serialno(&og))_decode_clear(vf);

      if(vf->ready_state<STREAMSET){
        int link;

        vf->current_serialno=ogg_page_serialno(&og);
        for(link=0;link<vf->links;link++)
          if(vf->serialnos[link]==vf->current_serialno)break;
        if(link==vf->links)return(OV_EBADLINK);
        vf->current_link=link;

        ogg_stream_reset_serialno(&vf->os,vf->current_serialno);
        vf->ready_state=STREAMSET;
        _make_decode_ready(vf);
        lastblock=0;
      }

      ogg_stream_pagein(&vf->os,&og);
    }
  }

  /* discard samples until we reach the desired position. Crossing a
     logical bitstream boundary with abandon is OK. */
  while(vf->pcm_offset<pos){
    float **pcm;
    ogg_int64_t target=pos-vf->pcm_offset;
    long samples=vorbis_synthesis_pcmout(&vf->vd,&pcm);

    if(samples>target)samples=target;
    vorbis_synthesis_read(&vf->vd,samples);
    vf->pcm_offset+=samples;

    if(samples<target)
      if(_fetch_and_process_packet(vf,NULL,1)<=0)
        vf->pcm_offset=ov_pcm_total(vf,-1); /* eof */
  }
  return 0;
}

/* seek to a playback time relative to the decompressed pcm stream
   returns zero on success, nonzero on failure */
int ov_time_seek(OggVorbis_File *vf,double seconds){
  /* translate time to PCM position and call ov_pcm_seek */

  int link=-1;
  ogg_int64_t pcm_total=ov_pcm_total(vf,-1);
  double time_total=ov_time_total(vf,-1);

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable)return(OV_ENOSEEK);
  if(seconds<0 || seconds>time_total)return(OV_EINVAL);

  /* which bitstream section does this time offset occur in? */
  for(link=vf->links-1;link>=0;link--){
    pcm_total-=vf->pcmlengths[link*2+1];
    time_total-=ov_time_total(vf,link);
    if(seconds>=time_total)break;
  }

  /* enough information to convert time offset to pcm offset */
  {
    ogg_int64_t target=pcm_total+(seconds-time_total)*vf->vi[link].rate;
    return(ov_pcm_seek(vf,target));
  }
}

/* page-granularity version of ov_time_seek
   returns zero on success, nonzero on failure */
int ov_time_seek_page(OggVorbis_File *vf,double seconds){
  /* translate time to PCM position and call ov_pcm_seek */

  int link=-1;
  ogg_int64_t pcm_total=ov_pcm_total(vf,-1);
  double time_total=ov_time_total(vf,-1);

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable)return(OV_ENOSEEK);
  if(seconds<0 || seconds>time_total)return(OV_EINVAL);

  /* which bitstream section does this time offset occur in? */
  for(link=vf->links-1;link>=0;link--){
    pcm_total-=vf->pcmlengths[link*2+1];
    time_total-=ov_time_total(vf,link);
    if(seconds>=time_total)break;
  }

  /* enough information to convert time offset to pcm offset */
  {
    ogg_int64_t target=pcm_total+(seconds-time_total)*vf->vi[link].rate;
    return(ov_pcm_seek_page(vf,target));
  }
}

/* tell the current stream offset cursor.  Note that seek followed by
   tell will likely not give the set offset due to caching */
ogg_int64_t ov_raw_tell(OggVorbis_File *vf){
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  return(vf->offset);
}

/* return PCM offset (sample) of next PCM sample to be read */
ogg_int64_t ov_pcm_tell(OggVorbis_File *vf){
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  return(vf->pcm_offset);
}

/* return time offset (seconds) of next PCM sample to be read */
double ov_time_tell(OggVorbis_File *vf){
  /* translate time to PCM position and call ov_pcm_seek */

  int link=-1;
  ogg_int64_t pcm_total=0;
  double time_total=0.f;

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(vf->seekable){
    pcm_total=ov_pcm_total(vf,-1);
    time_total=ov_time_total(vf,-1);

    /* which bitstream section does this time offset occur in? */
    for(link=vf->links-1;link>=0;link--){
      pcm_total-=vf->pcmlengths[link*2+1];
      time_total-=ov_time_total(vf,link);
      if(vf->pcm_offset>=pcm_total)break;
    }
  }

  return((double)time_total+(double)(vf->pcm_offset-pcm_total)/vf->vi[link].rate);
}

/*  link:   -1) return the vorbis_info struct for the bitstream section
                currently being decoded
           0-n) to request information for a specific bitstream section

    In the case of a non-seekable bitstream, any call returns the
    current bitstream.  NULL in the case that the machine is not
    initialized */

vorbis_info *ov_info(OggVorbis_File *vf,int link){
  if(vf->seekable){
    if(link<0)
      if(vf->ready_state>=STREAMSET)
        return vf->vi+vf->current_link;
      else
      return vf->vi;
    else
      if(link>=vf->links)
        return NULL;
      else
        return vf->vi+link;
  }else{
    return vf->vi;
  }
}

/* grr, strong typing, grr, no templates/inheritence, grr */
vorbis_comment *ov_comment(OggVorbis_File *vf,int link){
  if(vf->seekable){
    if(link<0)
      if(vf->ready_state>=STREAMSET)
        return vf->vc+vf->current_link;
      else
        return vf->vc;
    else
      if(link>=vf->links)
        return NULL;
      else
        return vf->vc+link;
  }else{
    return vf->vc;
  }
}

static int host_is_big_endian() {
  ogg_int32_t pattern = 0xfeedface; /* deadbeef */
  unsigned char *bytewise = (unsigned char *)&pattern;
  if (bytewise[0] == 0xfe) return 1;
  return 0;
}

/* up to this point, everything could more or less hide the multiple
   logical bitstream nature of chaining from the toplevel application
   if the toplevel application didn't particularly care.  However, at
   the point that we actually read audio back, the multiple-section
   nature must surface: Multiple bitstream sections do not necessarily
   have to have the same number of channels or sampling rate.

   ov_read returns the sequential logical bitstream number currently
   being decoded along with the PCM data in order that the toplevel
   application can take action on channel/sample rate changes.  This
   number will be incremented even for streamed (non-seekable) streams
   (for seekable streams, it represents the actual logical bitstream
   index within the physical bitstream.  Note that the accessor
   functions above are aware of this dichotomy).

   input values: buffer) a buffer to hold packed PCM data for return
                 length) the byte length requested to be placed into buffer
                 bigendianp) should the data be packed LSB first (0) or
                             MSB first (1)
                 word) word size for output.  currently 1 (byte) or
                       2 (16 bit short)

   return values: <0) error/hole in data (OV_HOLE), partial open (OV_EINVAL)
                   0) EOF
                   n) number of bytes of PCM actually returned.  The
                   below works on a packet-by-packet basis, so the
                   return length is not related to the 'length' passed
                   in, just guaranteed to fit.

            *section) set to the logical bitstream number */

long ov_read(OggVorbis_File *vf,char *buffer,int length,
                    int bigendianp,int word,int sgned,int *bitstream){
  int i,j;
  int host_endian = host_is_big_endian();

  float **pcm;
  long samples;

  if(vf->ready_state<OPENED)return(OV_EINVAL);

  while(1){
    if(vf->ready_state>=STREAMSET){
      samples=vorbis_synthesis_pcmout(&vf->vd,&pcm);
      if(samples)break;
    }

    /* suck in another packet */
    {
      int ret=_fetch_and_process_packet(vf,NULL,1);
      if(ret==OV_EOF)return(0);
      if(ret<=0)return(ret);
    }

  }

  if(samples>0){

    /* yay! proceed to pack data into the byte buffer */

    long channels=ov_info(vf,-1)->channels;
    long bytespersample=word * channels;
    vorbis_fpu_control fpu;
    if(samples>length/bytespersample)samples=length/bytespersample;

    if(samples <= 0)
      return OV_EINVAL;

    /* a tight loop to pack each size */
    {
      int val;
      if(word==1){
        int off=(sgned?0:128);
        vorbis_fpu_setround(&fpu);
        for(j=0;j<samples;j++)
          for(i=0;i<channels;i++){
            val=vorbis_ftoi(pcm[i][j]*128.f);
            if(val>127)val=127;
            else if(val<-128)val=-128;
            *buffer++=val+off;
          }
        vorbis_fpu_restore(fpu);
      }else{
        int off=(sgned?0:32768);

        if(host_endian==bigendianp){
          if(sgned){

            vorbis_fpu_setround(&fpu);
            for(i=0;i<channels;i++) { /* It's faster in this order */
              float *src=pcm[i];
              short *dest=((short *)buffer)+i;
              for(j=0;j<samples;j++) {
                val=vorbis_ftoi(src[j]*32768.f);
                if(val>32767)val=32767;
                else if(val<-32768)val=-32768;
                *dest=val;
                dest+=channels;
              }
            }
            vorbis_fpu_restore(fpu);

          }else{

            vorbis_fpu_setround(&fpu);
            for(i=0;i<channels;i++) {
              float *src=pcm[i];
              short *dest=((short *)buffer)+i;
              for(j=0;j<samples;j++) {
                val=vorbis_ftoi(src[j]*32768.f);
                if(val>32767)val=32767;
                else if(val<-32768)val=-32768;
                *dest=val+off;
                dest+=channels;
              }
            }
            vorbis_fpu_restore(fpu);

          }
        }else if(bigendianp){

          vorbis_fpu_setround(&fpu);
          for(j=0;j<samples;j++)
            for(i=0;i<channels;i++){
              val=vorbis_ftoi(pcm[i][j]*32768.f);
              if(val>32767)val=32767;
              else if(val<-32768)val=-32768;
              val+=off;
              *buffer++=(val>>8);
              *buffer++=(val&0xff);
            }
          vorbis_fpu_restore(fpu);

        }else{
          int val;
          vorbis_fpu_setround(&fpu);
          for(j=0;j<samples;j++)
            for(i=0;i<channels;i++){
              val=vorbis_ftoi(pcm[i][j]*32768.f);
              if(val>32767)val=32767;
              else if(val<-32768)val=-32768;
              val+=off;
              *buffer++=(val&0xff);
              *buffer++=(val>>8);
                }
          vorbis_fpu_restore(fpu);

        }
      }
    }

    vorbis_synthesis_read(&vf->vd,samples);
    vf->pcm_offset+=samples;
    if(bitstream)*bitstream=vf->current_link;
    return(samples*bytespersample);
  }else{
    return(samples);
  }
}

/* input values: pcm_channels) a float vector per channel of output
                 length) the sample length being read by the app

   return values: <0) error/hole in data (OV_HOLE), partial open (OV_EINVAL)
                   0) EOF
                   n) number of samples of PCM actually returned.  The
                   below works on a packet-by-packet basis, so the
                   return length is not related to the 'length' passed
                   in, just guaranteed to fit.

            *section) set to the logical bitstream number */



long ov_read_float(OggVorbis_File *vf,float ***pcm_channels,int length,
                   int *bitstream){

  if(vf->ready_state<OPENED)return(OV_EINVAL);

  while(1){
    if(vf->ready_state>=STREAMSET){
      float **pcm;
      long samples=vorbis_synthesis_pcmout(&vf->vd,&pcm);
      if(samples){
        if(pcm_channels)*pcm_channels=pcm;
        if(samples>length)samples=length;
        vorbis_synthesis_read(&vf->vd,samples);
        vf->pcm_offset+=samples;
        if(bitstream)*bitstream=vf->current_link;
        return samples;

      }
    }

    /* suck in another packet */
    {
      int ret=_fetch_and_process_packet(vf,NULL,1);
      if(ret==OV_EOF)return(0);
      if(ret<=0)return(ret);
    }

  }
}
