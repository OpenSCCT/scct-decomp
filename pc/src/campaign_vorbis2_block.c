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

 function: PCM data vector blocking, windowing and dis/reassembly
 last mod: $Id: block.c,v 1.67 2002/07/11 06:40:48 xiphmont Exp $

 Handle windowing, overlap-add, etc of the PCM vectors.  This is made
 more amusing by Vorbis' current two allowed block sizes.

 ********************************************************************/

/* #include <stdio.h> : included above */
/* #include <stdlib.h> : included above */
/* #include <string.h> : included above */
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
/* ---- codec_internal.h ---- */
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

 function: libvorbis codec headers
 last mod: $Id: codec_internal.h,v 1.15 2002/06/28 22:19:35 xiphmont Exp $

 ********************************************************************/

#ifndef _V_CODECI_H_
#define _V_CODECI_H_

/* ---- envelope.h ---- */
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

 function: PCM data envelope analysis and manipulation
 last mod: $Id: envelope.h,v 1.25 2002/07/11 06:40:48 xiphmont Exp $

 ********************************************************************/

#ifndef _V_ENVELOPE_
#define _V_ENVELOPE_

/* ---- mdct.h ---- */
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

 function: modified discrete cosine transform prototypes
 last mod: $Id: mdct.h,v 1.20 2002/01/22 11:59:00 xiphmont Exp $

 ********************************************************************/

#ifndef _OGG_mdct_H_
#define _OGG_mdct_H_






/*#define MDCT_INTEGERIZED  <- be warned there could be some hurt left here*/
#ifdef MDCT_INTEGERIZED

#define DATA_TYPE int
#define REG_TYPE  register int
#define TRIGBITS 14
#define cPI3_8 6270
#define cPI2_8 11585
#define cPI1_8 15137

#define FLOAT_CONV(x) ((int)((x)*(1<<TRIGBITS)+.5))
#define MULT_NORM(x) ((x)>>TRIGBITS)
#define HALVE(x) ((x)>>1)

#else

#define DATA_TYPE float
#define REG_TYPE  float
#define cPI3_8 .38268343236508977175F
#define cPI2_8 .70710678118654752441F
#define cPI1_8 .92387953251128675613F

#define FLOAT_CONV(x) (x)
#define MULT_NORM(x) (x)
#define HALVE(x) ((x)*.5f)

#endif


typedef struct {
  int n;
  int log2n;

  DATA_TYPE *trig;
  int       *bitrev;

  DATA_TYPE scale;
} mdct_lookup;

extern void mdct_init(mdct_lookup *lookup,int n);
extern void mdct_clear(mdct_lookup *l);
extern void mdct_forward(mdct_lookup *init, DATA_TYPE *in, DATA_TYPE *out);
extern void mdct_backward(mdct_lookup *init, DATA_TYPE *in, DATA_TYPE *out);

#endif













/* ---- end mdct.h ---- */

#define VE_PRE    16
#define VE_WIN    4
#define VE_POST   2
#define VE_AMP    (VE_PRE+VE_POST-1)

#define VE_BANDS  7
#define VE_NEARDC 15

#define VE_MINSTRETCH 2   /* a bit less than short block */
#define VE_MAXSTRETCH 12  /* one-third full block */

typedef struct {
  float ampbuf[VE_AMP];
  int   ampptr;

  float nearDC[VE_NEARDC];
  float nearDC_acc;
  float nearDC_partialacc;
  int   nearptr;

} envelope_filter_state;

typedef struct {
  int begin;
  int end;
  float *window;
  float total;
} envelope_band;

typedef struct {
  int ch;
  int winlength;
  int searchstep;
  float minenergy;

  mdct_lookup  mdct;
  float       *mdct_win;

  envelope_band          band[VE_BANDS];
  envelope_filter_state *filter;
  int   stretch;

  int                   *mark;

  long storage;
  long current;
  long curmark;
  long cursor;
} envelope_lookup;

extern void _ve_envelope_init(envelope_lookup *e,vorbis_info *vi);
extern void _ve_envelope_clear(envelope_lookup *e);
extern long _ve_envelope_search(vorbis_dsp_state *v);
extern void _ve_envelope_shift(envelope_lookup *e,long shift);
extern int  _ve_envelope_mark(vorbis_dsp_state *v);


#endif


/* ---- end envelope.h ---- */
/* ---- codebook.h ---- */
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

 function: basic shared codebook operations
 last mod: $Id: codebook.h,v 1.13 2002/06/28 22:19:35 xiphmont Exp $

 ********************************************************************/

#ifndef _V_CODEBOOK_H_
#define _V_CODEBOOK_H_


/* This structure encapsulates huffman and VQ style encoding books; it
   doesn't do anything specific to either.

   valuelist/quantlist are nonNULL (and q_* significant) only if
   there's entry->value mapping to be done.

   If encode-side mapping must be done (and thus the entry needs to be
   hunted), the auxiliary encode pointer will point to a decision
   tree.  This is true of both VQ and huffman, but is mostly useful
   with VQ.

*/

typedef struct static_codebook{
  long   dim;            /* codebook dimensions (elements per vector) */
  long   entries;        /* codebook entries */
  long  *lengthlist;     /* codeword lengths in bits */

  /* mapping ***************************************************************/
  int    maptype;        /* 0=none
                            1=implicitly populated values from map column
                            2=listed arbitrary values */

  /* The below does a linear, single monotonic sequence mapping. */
  long     q_min;       /* packed 32 bit float; quant value 0 maps to minval */
  long     q_delta;     /* packed 32 bit float; val 1 - val 0 == delta */
  int      q_quant;     /* bits: 0 < quant <= 16 */
  int      q_sequencep; /* bitflag */

  long     *quantlist;  /* map == 1: (int)(entries^(1/dim)) element column map
                           map == 2: list of dim*entries quantized entry vals
                        */

  /* encode helpers ********************************************************/
  struct encode_aux_nearestmatch *nearest_tree;
  struct encode_aux_threshmatch  *thresh_tree;
  struct encode_aux_pigeonhole  *pigeon_tree;

  int allocedp;
} static_codebook;

/* this structures an arbitrary trained book to quickly find the
   nearest cell match */
typedef struct encode_aux_nearestmatch{
  /* pre-calculated partitioning tree */
  long   *ptr0;
  long   *ptr1;

  long   *p;         /* decision points (each is an entry) */
  long   *q;         /* decision points (each is an entry) */
  long   aux;        /* number of tree entries */
  long   alloc;
} encode_aux_nearestmatch;

/* assumes a maptype of 1; encode side only, so that's OK */
typedef struct encode_aux_threshmatch{
  float *quantthresh;
  long   *quantmap;
  int     quantvals;
  int     threshvals;
} encode_aux_threshmatch;

typedef struct encode_aux_pigeonhole{
  float min;
  float del;

  int  mapentries;
  int  quantvals;
  long *pigeonmap;

  long fittotal;
  long *fitlist;
  long *fitmap;
  long *fitlength;
} encode_aux_pigeonhole;

typedef struct codebook{
  long dim;           /* codebook dimensions (elements per vector) */
  long entries;       /* codebook entries */
  long used_entries;  /* populated codebook entries */
  const static_codebook *c;

  /* for encode, the below are entry-ordered, fully populated */
  /* for decode, the below are ordered by bitreversed codeword and only
     used entries are populated */
  float        *valuelist;  /* list of dim*entries actual entry values */
  ogg_uint32_t *codelist;   /* list of bitstream codewords for each entry */

  int          *dec_index;  /* only used if sparseness collapsed */
  char         *dec_codelengths;
  ogg_uint32_t *dec_firsttable;
  int           dec_firsttablen;
  int           dec_maxlength;

} codebook;

extern void vorbis_staticbook_clear(static_codebook *b);
extern void vorbis_staticbook_destroy(static_codebook *b);
extern int vorbis_book_init_encode(codebook *dest,const static_codebook *source);
extern int vorbis_book_init_decode(codebook *dest,const static_codebook *source);
extern void vorbis_book_clear(codebook *b);

extern float *_book_unquantize(const static_codebook *b,int n,int *map);
extern float *_book_logdist(const static_codebook *b,float *vals);
extern float _float32_unpack(long val);
extern long   _float32_pack(float val);
extern int  _best(codebook *book, float *a, int step);
extern int _ilog(unsigned int v);
extern long _book_maptype1_quantvals(const static_codebook *b);

extern int vorbis_book_besterror(codebook *book,float *a,int step,int addmul);
extern long vorbis_book_codeword(codebook *book,int entry);
extern long vorbis_book_codelen(codebook *book,int entry);



extern int vorbis_staticbook_pack(const static_codebook *c,oggpack_buffer *b);
extern int vorbis_staticbook_unpack(oggpack_buffer *b,static_codebook *c);

extern int vorbis_book_encode(codebook *book, int a, oggpack_buffer *b);
extern int vorbis_book_errorv(codebook *book, float *a);
extern int vorbis_book_encodev(codebook *book, int best,float *a,
                               oggpack_buffer *b);

extern long vorbis_book_decode(codebook *book, oggpack_buffer *b);
extern long vorbis_book_decodevs_add(codebook *book, float *a,
                                     oggpack_buffer *b,int n);
extern long vorbis_book_decodev_set(codebook *book, float *a,
                                    oggpack_buffer *b,int n);
extern long vorbis_book_decodev_add(codebook *book, float *a,
                                    oggpack_buffer *b,int n);
extern long vorbis_book_decodevv_add(codebook *book, float **a,
                                     long off,int ch,
                                    oggpack_buffer *b,int n);



#endif

/* ---- end codebook.h ---- */

#define BLOCKTYPE_IMPULSE    0
#define BLOCKTYPE_PADDING    1
#define BLOCKTYPE_TRANSITION 0
#define BLOCKTYPE_LONG       1

#define PACKETBLOBS 15

typedef struct vorbis_block_internal{
  float  **pcmdelay;  /* this is a pointer into local storage */
  float  ampmax;
  int    blocktype;

  ogg_uint32_t   packetblob_markers[PACKETBLOBS];
} vorbis_block_internal;

typedef void vorbis_look_floor;
typedef void vorbis_look_residue;
typedef void vorbis_look_transform;

/* mode ************************************************************/
typedef struct {
  int blockflag;
  int windowtype;
  int transformtype;
  int mapping;
} vorbis_info_mode;

typedef void vorbis_info_floor;
typedef void vorbis_info_residue;
typedef void vorbis_info_mapping;

/* ---- psy.h ---- */
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

 function: random psychoacoustics (not including preecho)
 last mod: $Id: psy.h,v 1.32 2002/07/13 06:12:47 xiphmont Exp $

 ********************************************************************/

#ifndef _V_PSY_H_
#define _V_PSY_H_
/* ---- smallft.h ---- */
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

 function: fft transform
 last mod: $Id: smallft.h,v 1.12 2002/07/11 06:40:50 xiphmont Exp $

 ********************************************************************/

#ifndef _V_SMFT_H_
#define _V_SMFT_H_


typedef struct {
  int n;
  float *trigcache;
  int *splitcache;
} drft_lookup;

extern void drft_forward(drft_lookup *l,float *data);
extern void drft_backward(drft_lookup *l,float *data);
extern void drft_init(drft_lookup *l,int n);
extern void drft_clear(drft_lookup *l);

#endif

/* ---- end smallft.h ---- */

/* ---- backends.h ---- */
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

 function: libvorbis backend and mapping structures; needed for
           static mode headers
 last mod: $Id: backends.h,v 1.14 2002/07/11 06:40:48 xiphmont Exp $

 ********************************************************************/

/* this is exposed up here because we need it for static modes.
   Lookups for each backend aren't exposed because there's no reason
   to do so */

#ifndef _vorbis_backend_h_
#define _vorbis_backend_h_


/* this would all be simpler/shorter with templates, but.... */
/* Floor backend generic *****************************************/
typedef struct{
  void                   (*pack)  (vorbis_info_floor *,oggpack_buffer *);
  vorbis_info_floor     *(*unpack)(vorbis_info *,oggpack_buffer *);
  vorbis_look_floor     *(*look)  (vorbis_dsp_state *,vorbis_info_floor *);
  void (*free_info) (vorbis_info_floor *);
  void (*free_look) (vorbis_look_floor *);
  void *(*inverse1)  (struct vorbis_block *,vorbis_look_floor *);
  int   (*inverse2)  (struct vorbis_block *,vorbis_look_floor *,
                     void *buffer,float *);
} vorbis_func_floor;

typedef struct{
  int   order;
  long  rate;
  long  barkmap;

  int   ampbits;
  int   ampdB;

  int   numbooks; /* <= 16 */
  int   books[16];

  float lessthan;     /* encode-only config setting hacks for libvorbis */
  float greaterthan;  /* encode-only config setting hacks for libvorbis */

} vorbis_info_floor0;


#define VIF_POSIT 63
#define VIF_CLASS 16
#define VIF_PARTS 31
typedef struct{
  int   partitions;                /* 0 to 31 */
  int   partitionclass[VIF_PARTS]; /* 0 to 15 */

  int   class_dim[VIF_CLASS];        /* 1 to 8 */
  int   class_subs[VIF_CLASS];       /* 0,1,2,3 (bits: 1<<n poss) */
  int   class_book[VIF_CLASS];       /* subs ^ dim entries */
  int   class_subbook[VIF_CLASS][8]; /* [VIF_CLASS][subs] */


  int   mult;                      /* 1 2 3 or 4 */
  int   postlist[VIF_POSIT+2];    /* first two implicit */


  /* encode side analysis parameters */
  float maxover;
  float maxunder;
  float maxerr;

  float twofitweight;
  float twofitatten;

  int   n;

} vorbis_info_floor1;

/* Residue backend generic *****************************************/
typedef struct{
  void                 (*pack)  (vorbis_info_residue *,oggpack_buffer *);
  vorbis_info_residue *(*unpack)(vorbis_info *,oggpack_buffer *);
  vorbis_look_residue *(*look)  (vorbis_dsp_state *,
                                 vorbis_info_residue *);
  void (*free_info)    (vorbis_info_residue *);
  void (*free_look)    (vorbis_look_residue *);
  long **(*class)      (struct vorbis_block *,vorbis_look_residue *,
                        float **,int *,int);
  int  (*forward)      (struct vorbis_block *,vorbis_look_residue *,
                        float **,float **,int *,int,long **);
  int  (*inverse)      (struct vorbis_block *,vorbis_look_residue *,
                        float **,int *,int);
} vorbis_func_residue;

typedef struct vorbis_info_residue0{
/* block-partitioned VQ coded straight residue */
  long  begin;
  long  end;

  /* first stage (lossless partitioning) */
  int    grouping;         /* group n vectors per partition */
  int    partitions;       /* possible codebooks for a partition */
  int    groupbook;        /* huffbook for partitioning */
  int    secondstages[64]; /* expanded out to pointers in lookup */
  int    booklist[256];    /* list of second stage books */

  float  classmetric1[64];
  float  classmetric2[64];

} vorbis_info_residue0;

/* Mapping backend generic *****************************************/
typedef struct{
  void                 (*pack)  (vorbis_info *,vorbis_info_mapping *,
                                 oggpack_buffer *);
  vorbis_info_mapping *(*unpack)(vorbis_info *,oggpack_buffer *);
  void (*free_info)    (vorbis_info_mapping *);
  int  (*forward)      (struct vorbis_block *vb);
  int  (*inverse)      (struct vorbis_block *vb,vorbis_info_mapping *);
} vorbis_func_mapping;

typedef struct vorbis_info_mapping0{
  int   submaps;  /* <= 16 */
  int   chmuxlist[256];   /* up to 256 channels in a Vorbis stream */

  int   floorsubmap[16];   /* [mux] submap to floors */
  int   residuesubmap[16]; /* [mux] submap to residue */

  int   coupling_steps;
  int   coupling_mag[256];
  int   coupling_ang[256];

} vorbis_info_mapping0;

#endif



/* ---- end backends.h ---- */

#ifndef EHMER_MAX
#define EHMER_MAX 56
#endif

/* psychoacoustic setup ********************************************/
#define P_BANDS 17      /* 62Hz to 16kHz */
#define P_LEVELS 8      /* 30dB to 100dB */
#define P_LEVEL_0 30.    /* 30 dB */
#define P_NOISECURVES 3

#define NOISE_COMPAND_LEVELS 40
typedef struct vorbis_info_psy{
  int   blockflag;

  float ath_adjatt;
  float ath_maxatt;

  float tone_masteratt[P_NOISECURVES];
  float tone_centerboost;
  float tone_decay;
  float tone_abs_limit;
  float toneatt[P_BANDS];

  int noisemaskp;
  float noisemaxsupp;
  float noisewindowlo;
  float noisewindowhi;
  int   noisewindowlomin;
  int   noisewindowhimin;
  int   noisewindowfixed;
  float noiseoff[P_NOISECURVES][P_BANDS];
  float noisecompand[NOISE_COMPAND_LEVELS];

  float max_curve_dB;

  int normal_channel_p;
  int normal_point_p;
  int normal_start;
  int normal_partition;
  double normal_thresh;
} vorbis_info_psy;

typedef struct{
  int   eighth_octave_lines;

  /* for block long/short tuning; encode only */
  float preecho_thresh[VE_BANDS];
  float postecho_thresh[VE_BANDS];
  float stretch_penalty;
  float preecho_minenergy;

  float ampmax_att_per_sec;

  /* channel coupling config */
  int   coupling_pkHz[PACKETBLOBS];
  int   coupling_pointlimit[2][PACKETBLOBS];
  int   coupling_prepointamp[PACKETBLOBS];
  int   coupling_postpointamp[PACKETBLOBS];
  int   sliding_lowpass[2][PACKETBLOBS];

} vorbis_info_psy_global;

typedef struct {
  float ampmax;
  int   channels;

  vorbis_info_psy_global *gi;
  int   coupling_pointlimit[2][P_NOISECURVES];
} vorbis_look_psy_global;


typedef struct {
  int n;
  struct vorbis_info_psy *vi;

  float ***tonecurves;
  float **noiseoffset;

  float *ath;
  long  *octave;             /* in n.ocshift format */
  long  *bark;

  long  firstoc;
  long  shiftoc;
  int   eighth_octave_lines; /* power of two, please */
  int   total_octave_lines;
  long  rate; /* cache it */
} vorbis_look_psy;

extern void   _vp_psy_init(vorbis_look_psy *p,vorbis_info_psy *vi,
                           vorbis_info_psy_global *gi,int n,long rate);
extern void   _vp_psy_clear(vorbis_look_psy *p);
extern void  *_vi_psy_dup(void *source);

extern void   _vi_psy_free(vorbis_info_psy *i);
extern vorbis_info_psy *_vi_psy_copy(vorbis_info_psy *i);

extern void _vp_remove_floor(vorbis_look_psy *p,
                             float *mdct,
                             int *icodedflr,
                             float *residue,
                             int sliding_lowpass);

extern void _vp_noisemask(vorbis_look_psy *p,
                          float *logmdct,
                          float *logmask);

extern void _vp_tonemask(vorbis_look_psy *p,
                         float *logfft,
                         float *logmask,
                         float global_specmax,
                         float local_specmax);

extern void _vp_offset_and_mix(vorbis_look_psy *p,
                               float *noise,
                               float *tone,
                               int offset_select,
                               float *logmask);

extern float _vp_ampmax_decay(float amp,vorbis_dsp_state *vd);

extern float **_vp_quantize_couple_memo(vorbis_block *vb,
                                        vorbis_info_psy_global *g,
                                        vorbis_look_psy *p,
                                        vorbis_info_mapping0 *vi,
                                        float **mdct);

extern void _vp_couple(int blobno,
                       vorbis_info_psy_global *g,
                       vorbis_look_psy *p,
                       vorbis_info_mapping0 *vi,
                       float **res,
                       float **mag_memo,
                       int   **mag_sort,
                       int   **ifloor,
                       int   *nonzero,
                       int   sliding_lowpass);

extern void _vp_noise_normalize(vorbis_look_psy *p,
                                float *in,float *out,int *sortedindex);

extern void _vp_noise_normalize_sort(vorbis_look_psy *p,
                                     float *magnitudes,int *sortedindex);

extern int **_vp_quantize_couple_sort(vorbis_block *vb,
                                      vorbis_look_psy *p,
                                      vorbis_info_mapping0 *vi,
                                      float **mags);

#endif


/* ---- end psy.h ---- */
/* ---- bitrate.h ---- */
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

 function: bitrate tracking and management
 last mod: $Id: bitrate.h,v 1.7 2002/07/11 06:40:48 xiphmont Exp $

 ********************************************************************/

#ifndef _V_BITRATE_H_
#define _V_BITRATE_H_

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

/* encode side bitrate tracking */
typedef struct bitrate_manager_state {
  ogg_uint32_t  *queue_binned;
  ogg_uint32_t  *queue_actual;
  int            queue_size;

  int            queue_head;
  int            queue_bins;

  long          *avg_binacc;
  int            avg_center;
  int            avg_tail;
  ogg_uint32_t   avg_centeracc;
  ogg_uint32_t   avg_sampleacc;
  ogg_uint32_t   avg_sampledesired;
  ogg_uint32_t   avg_centerdesired;

  long          *minmax_binstack;
  long          *minmax_posstack;
  long          *minmax_limitstack;
  long           minmax_stackptr;

  long           minmax_acctotal;
  int            minmax_tail;
  ogg_uint32_t   minmax_sampleacc;
  ogg_uint32_t   minmax_sampledesired;

  int            next_to_flush;
  int            last_to_flush;

  double         avgfloat;

  /* unfortunately, we need to hold queued packet data somewhere */
  oggpack_buffer *packetbuffers;
  ogg_packet     *packets;

} bitrate_manager_state;

typedef struct bitrate_manager_info{
  /* detailed bitrate management setup */
  double queue_avg_time;
  double queue_avg_center;
  double queue_minmax_time;
  double queue_hardmin;
  double queue_hardmax;
  double queue_avgmin;
  double queue_avgmax;

  double avgfloat_downslew_max;
  double avgfloat_upslew_max;

} bitrate_manager_info;

extern void vorbis_bitrate_init(vorbis_info *vi,bitrate_manager_state *bs);
extern void vorbis_bitrate_clear(bitrate_manager_state *bs);
extern int vorbis_bitrate_managed(vorbis_block *vb);
extern int vorbis_bitrate_addblock(vorbis_block *vb);
extern int vorbis_bitrate_flushpacket(vorbis_dsp_state *vd, ogg_packet *op);

#endif

/* ---- end bitrate.h ---- */

typedef struct backend_lookup_state {
  /* local lookup storage */
  envelope_lookup        *ve; /* envelope lookup */
  float                  *window[2];
  vorbis_look_transform **transform[2];    /* block, type */
  drft_lookup             fft_look[2];

  int                     modebits;
  vorbis_look_floor     **flr;
  vorbis_look_residue   **residue;
  vorbis_look_psy        *psy;
  vorbis_look_psy_global *psy_g_look;

  /* local storage, only used on the encoding side.  This way the
     application does not need to worry about freeing some packets'
     memory and not others'; packet storage is always tracked.
     Cleared next call to a _dsp_ function */
  unsigned char *header;
  unsigned char *header1;
  unsigned char *header2;

  bitrate_manager_state bms;

} backend_lookup_state;

/* codec_setup_info contains all the setup information specific to the
   specific compression/decompression mode in progress (eg,
   psychoacoustic settings, channel setup, options, codebook
   etc).
*********************************************************************/

/* ---- highlevel.h ---- */
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

 function: highlevel encoder setup struct seperated out for vorbisenc clarity
 last mod: $Id: highlevel.h,v 1.4 2002/07/01 11:20:11 xiphmont Exp $

 ********************************************************************/

typedef struct highlevel_byblocktype {
  double tone_mask_setting;
  double tone_peaklimit_setting;
  double noise_bias_setting;
  double noise_compand_setting;
} highlevel_byblocktype;

typedef struct highlevel_encode_setup {
  void *setup;
  int   set_in_stone;

  double base_setting;
  double long_setting;
  double short_setting;
  double impulse_noisetune;

  int    managed;
  long   bitrate_min;
  long   bitrate_av_lo;
  long   bitrate_av_hi;
  long   bitrate_max;
  double bitrate_limit_window;
  double bitrate_av_window;
  double bitrate_av_window_center;

  int impulse_block_p;
  int noise_normalize_p;

  double stereo_point_setting;
  double lowpass_kHz;

  double ath_floating_dB;
  double ath_absolute_dB;

  double amplitude_track_dBpersec;
  double trigger_setting;

  highlevel_byblocktype block[4]; /* padding, impulse, transition, long */

} highlevel_encode_setup;


/* ---- end highlevel.h ---- */
typedef struct codec_setup_info {

  /* Vorbis supports only short and long blocks, but allows the
     encoder to choose the sizes */

  long blocksizes[2];

  /* modes are the primary means of supporting on-the-fly different
     blocksizes, different channel mappings (LR or M/A),
     different residue backends, etc.  Each mode consists of a
     blocksize flag and a mapping (along with the mapping setup */

  int        modes;
  int        maps;
  int        floors;
  int        residues;
  int        books;
  int        psys;     /* encode only */

  vorbis_info_mode       *mode_param[64];
  int                     map_type[64];
  vorbis_info_mapping    *map_param[64];
  int                     floor_type[64];
  vorbis_info_floor      *floor_param[64];
  int                     residue_type[64];
  vorbis_info_residue    *residue_param[64];
  static_codebook        *book_param[256];
  codebook               *fullbooks;

  vorbis_info_psy        *psy_param[4]; /* encode only */
  vorbis_info_psy_global psy_g_param;

  bitrate_manager_info   bi;
  highlevel_encode_setup hi; /* used only by vorbisenc.c.  It's a
                                highly redundant structure, but
                                improves clarity of program flow. */

} codec_setup_info;

extern vorbis_look_psy_global *_vp_global_look(vorbis_info *vi);
extern void _vp_global_free(vorbis_look_psy_global *look);

#endif


/* ---- end codec_internal.h ---- */

/* ---- window.h ---- */
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

 function: window functions
 last mod: $Id: window.h,v 1.10 2002/01/22 11:59:00 xiphmont Exp $

 ********************************************************************/

#ifndef _V_WINDOW_
#define _V_WINDOW_

extern float *_vorbis_window(int type,int left);
extern void _vorbis_apply_window(float *d,float *window[2],long *blocksizes,
                                 int lW,int W,int nW);


#endif

/* ---- end window.h ---- */
/* ---- lpc.h ---- */
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
  last mod: $Id: lpc.h,v 1.19 2002/07/11 06:40:49 xiphmont Exp $

 ********************************************************************/

#ifndef _V_LPC_H_
#define _V_LPC_H_


typedef struct lpclook{
  /* en/decode lookups */
  drft_lookup fft;

  int ln;
  int m;

} lpc_lookup;

extern void lpc_init(lpc_lookup *l,long mapped, int m);
extern void lpc_clear(lpc_lookup *l);

/* simple linear scale LPC code */
extern float vorbis_lpc_from_data(float *data,float *lpc,int n,int m);
extern float vorbis_lpc_from_curve(float *curve,float *lpc,lpc_lookup *l);

extern void vorbis_lpc_predict(float *coeff,float *prime,int m,
                               float *data,long n);

#endif

/* ---- end lpc.h ---- */
/* ---- registry.h ---- */
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

 function: registry for time, floor, res backends and channel mappings
 last mod: $Id: registry.h,v 1.13 2002/07/11 06:40:50 xiphmont Exp $

 ********************************************************************/

#ifndef _V_REG_H_
#define _V_REG_H_

#define VI_TRANSFORMB 1
#define VI_WINDOWB 1
#define VI_TIMEB 1
#define VI_FLOORB 2
#define VI_RESB 3
#define VI_MAPB 1

extern vorbis_func_floor     *_floor_P[];
extern vorbis_func_residue   *_residue_P[];
extern vorbis_func_mapping   *_mapping_P[];

#endif

/* ---- end registry.h ---- */

static int ilog2(unsigned int v){
  int ret=0;
  if(v)--v;
  while(v){
    ret++;
    v>>=1;
  }
  return(ret);
}

/* pcm accumulator examples (not exhaustive):

 <-------------- lW ---------------->
                   <--------------- W ---------------->
:            .....|.....       _______________         |
:        .'''     |     '''_---      |       |\        |
:.....'''         |_____--- '''......|       | \_______|
:.................|__________________|_______|__|______|
                  |<------ Sl ------>|      > Sr <     |endW
                  |beginSl           |endSl  |  |endSr
                  |beginW            |endlW  |beginSr


                      |< lW >|
                   <--------------- W ---------------->
                  |   |  ..  ______________            |
                  |   | '  `/        |     ---_        |
                  |___.'___/`.       |         ---_____|
                  |_______|__|_______|_________________|
                  |      >|Sl|<      |<------ Sr ----->|endW
                  |       |  |endSl  |beginSr          |endSr
                  |beginW |  |endlW
                  mult[0] |beginSl                     mult[n]

 <-------------- lW ----------------->
                          |<--W-->|
:            ..............  ___  |   |
:        .'''             |`/   \ |   |
:.....'''                 |/`....\|...|
:.........................|___|___|___|
                          |Sl |Sr |endW
                          |   |   |endSr
                          |   |beginSr
                          |   |endSl
                          |beginSl
                          |beginW
*/

/* block abstraction setup *********************************************/

#ifndef WORD_ALIGN
#define WORD_ALIGN 8
#endif

int vorbis_block_init(vorbis_dsp_state *v, vorbis_block *vb){
  memset(vb,0,sizeof(*vb));
  vb->vd=v;
  vb->localalloc=0;
  vb->localstore=NULL;
  if(v->analysisp){
    vorbis_block_internal *vbi=
      vb->internal=_ogg_calloc(1,sizeof(vorbis_block_internal));
    oggpack_writeinit(&vb->opb);
    vbi->ampmax=-9999;
  }

  return(0);
}

void *_vorbis_block_alloc(vorbis_block *vb,long bytes){
  bytes=(bytes+(WORD_ALIGN-1)) & ~(WORD_ALIGN-1);
  if(bytes+vb->localtop>vb->localalloc){
    /* can't just _ogg_realloc... there are outstanding pointers */
    if(vb->localstore){
      struct alloc_chain *link=_ogg_malloc(sizeof(*link));
      vb->totaluse+=vb->localtop;
      link->next=vb->reap;
      link->ptr=vb->localstore;
      vb->reap=link;
    }
    /* highly conservative */
    vb->localalloc=bytes;
    vb->localstore=_ogg_malloc(vb->localalloc);
    vb->localtop=0;
  }
  {
    void *ret=(void *)(((char *)vb->localstore)+vb->localtop);
    vb->localtop+=bytes;
    return ret;
  }
}

/* reap the chain, pull the ripcord */
void _vorbis_block_ripcord(vorbis_block *vb){
  /* reap the chain */
  struct alloc_chain *reap=vb->reap;
  while(reap){
    struct alloc_chain *next=reap->next;
    _ogg_free(reap->ptr);
    memset(reap,0,sizeof(*reap));
    _ogg_free(reap);
    reap=next;
  }
  /* consolidate storage */
  if(vb->totaluse){
    vb->localstore=_ogg_realloc(vb->localstore,vb->totaluse+vb->localalloc);
    vb->localalloc+=vb->totaluse;
    vb->totaluse=0;
  }

  /* pull the ripcord */
  vb->localtop=0;
  vb->reap=NULL;
}

int vorbis_block_clear(vorbis_block *vb){
  if(vb->vd)
    if(vb->vd->analysisp)
      oggpack_writeclear(&vb->opb);
  _vorbis_block_ripcord(vb);
  if(vb->localstore)_ogg_free(vb->localstore);

  if(vb->internal)
    _ogg_free(vb->internal);

  memset(vb,0,sizeof(*vb));
  return(0);
}

/* Analysis side code, but directly related to blocking.  Thus it's
   here and not in analysis.c (which is for analysis transforms only).
   The init is here because some of it is shared */

static int _vds_shared_init(vorbis_dsp_state *v,vorbis_info *vi,int encp){
  int i;
  codec_setup_info *ci=vi->codec_setup;
  backend_lookup_state *b=NULL;

  memset(v,0,sizeof(*v));
  b=v->backend_state=_ogg_calloc(1,sizeof(*b));

  v->vi=vi;
  b->modebits=ilog2(ci->modes);

  b->transform[0]=_ogg_calloc(VI_TRANSFORMB,sizeof(*b->transform[0]));
  b->transform[1]=_ogg_calloc(VI_TRANSFORMB,sizeof(*b->transform[1]));

  /* MDCT is tranform 0 */

  b->transform[0][0]=_ogg_calloc(1,sizeof(mdct_lookup));
  b->transform[1][0]=_ogg_calloc(1,sizeof(mdct_lookup));
  mdct_init(b->transform[0][0],ci->blocksizes[0]);
  mdct_init(b->transform[1][0],ci->blocksizes[1]);

  /* Vorbis I uses only window type 0 */
  b->window[0]=_vorbis_window(0,ci->blocksizes[0]/2);
  b->window[1]=_vorbis_window(0,ci->blocksizes[1]/2);

  if(encp){ /* encode/decode differ here */

    /* analysis always needs an fft */
    drft_init(&b->fft_look[0],ci->blocksizes[0]);
    drft_init(&b->fft_look[1],ci->blocksizes[1]);

    /* finish the codebooks */
    if(!ci->fullbooks){
      ci->fullbooks=_ogg_calloc(ci->books,sizeof(*ci->fullbooks));
      for(i=0;i<ci->books;i++)
        vorbis_book_init_encode(ci->fullbooks+i,ci->book_param[i]);
    }

    b->psy=_ogg_calloc(ci->psys,sizeof(*b->psy));
    for(i=0;i<ci->psys;i++){
      _vp_psy_init(b->psy+i,
                   ci->psy_param[i],
                   &ci->psy_g_param,
                   ci->blocksizes[ci->psy_param[i]->blockflag]/2,
                   vi->rate);
    }

    v->analysisp=1;
  }else{
    /* finish the codebooks */
    if(!ci->fullbooks){
      ci->fullbooks=_ogg_calloc(ci->books,sizeof(*ci->fullbooks));
      for(i=0;i<ci->books;i++){
        vorbis_book_init_decode(ci->fullbooks+i,ci->book_param[i]);
        /* decode codebooks are now standalone after init */
        vorbis_staticbook_destroy(ci->book_param[i]);
        ci->book_param[i]=NULL;
      }
    }
  }

  /* initialize the storage vectors. blocksize[1] is small for encode,
     but the correct size for decode */
  v->pcm_storage=ci->blocksizes[1];
  v->pcm=_ogg_malloc(vi->channels*sizeof(*v->pcm));
  v->pcmret=_ogg_malloc(vi->channels*sizeof(*v->pcmret));
  {
    int i;
    for(i=0;i<vi->channels;i++)
      v->pcm[i]=_ogg_calloc(v->pcm_storage,sizeof(*v->pcm[i]));
  }

  /* all 1 (large block) or 0 (small block) */
  /* explicitly set for the sake of clarity */
  v->lW=0; /* previous window size */
  v->W=0;  /* current window size */

  /* all vector indexes */
  v->centerW=ci->blocksizes[1]/2;

  v->pcm_current=v->centerW;

  /* initialize all the backend lookups */
  b->flr=_ogg_calloc(ci->floors,sizeof(*b->flr));
  b->residue=_ogg_calloc(ci->residues,sizeof(*b->residue));

  for(i=0;i<ci->floors;i++)
    b->flr[i]=_floor_P[ci->floor_type[i]]->
      look(v,ci->floor_param[i]);

  for(i=0;i<ci->residues;i++)
    b->residue[i]=_residue_P[ci->residue_type[i]]->
      look(v,ci->residue_param[i]);

  return(0);
}

/* arbitrary settings and spec-mandated numbers get filled in here */
int vorbis_analysis_init(vorbis_dsp_state *v,vorbis_info *vi){
  backend_lookup_state *b=NULL;

  _vds_shared_init(v,vi,1);
  b=v->backend_state;
  b->psy_g_look=_vp_global_look(vi);

  /* Initialize the envelope state storage */
  b->ve=_ogg_calloc(1,sizeof(*b->ve));
  _ve_envelope_init(b->ve,vi);

  vorbis_bitrate_init(vi,&b->bms);

  return(0);
}

void vorbis_dsp_clear(vorbis_dsp_state *v){
  int i;
  if(v){
    vorbis_info *vi=v->vi;
    codec_setup_info *ci=(vi?vi->codec_setup:NULL);
    backend_lookup_state *b=v->backend_state;

    if(b){
      if(b->window[0])
        _ogg_free(b->window[0]);
      if(b->window[1])
        _ogg_free(b->window[1]);

      if(b->ve){
        _ve_envelope_clear(b->ve);
        _ogg_free(b->ve);
      }

      if(b->transform[0]){
        mdct_clear(b->transform[0][0]);
        _ogg_free(b->transform[0][0]);
        _ogg_free(b->transform[0]);
      }
      if(b->transform[1]){
        mdct_clear(b->transform[1][0]);
        _ogg_free(b->transform[1][0]);
        _ogg_free(b->transform[1]);
      }

      if(b->flr){
        for(i=0;i<ci->floors;i++)
          _floor_P[ci->floor_type[i]]->
            free_look(b->flr[i]);
        _ogg_free(b->flr);
      }
      if(b->residue){
        for(i=0;i<ci->residues;i++)
          _residue_P[ci->residue_type[i]]->
            free_look(b->residue[i]);
        _ogg_free(b->residue);
      }
      if(b->psy){
        for(i=0;i<ci->psys;i++)
          _vp_psy_clear(b->psy+i);
        _ogg_free(b->psy);
      }

      if(b->psy_g_look)_vp_global_free(b->psy_g_look);
      vorbis_bitrate_clear(&b->bms);

      drft_clear(&b->fft_look[0]);
      drft_clear(&b->fft_look[1]);

    }

    if(v->pcm){
      for(i=0;i<vi->channels;i++)
        if(v->pcm[i])_ogg_free(v->pcm[i]);
      _ogg_free(v->pcm);
      if(v->pcmret)_ogg_free(v->pcmret);
    }

    if(b){
      /* free header, header1, header2 */
      if(b->header)_ogg_free(b->header);
      if(b->header1)_ogg_free(b->header1);
      if(b->header2)_ogg_free(b->header2);
      _ogg_free(b);
    }

    memset(v,0,sizeof(*v));
  }
}

float **vorbis_analysis_buffer(vorbis_dsp_state *v, int vals){
  int i;
  vorbis_info *vi=v->vi;
  backend_lookup_state *b=v->backend_state;

  /* free header, header1, header2 */
  if(b->header)_ogg_free(b->header);b->header=NULL;
  if(b->header1)_ogg_free(b->header1);b->header1=NULL;
  if(b->header2)_ogg_free(b->header2);b->header2=NULL;

  /* Do we have enough storage space for the requested buffer? If not,
     expand the PCM (and envelope) storage */

  if(v->pcm_current+vals>=v->pcm_storage){
    v->pcm_storage=v->pcm_current+vals*2;

    for(i=0;i<vi->channels;i++){
      v->pcm[i]=_ogg_realloc(v->pcm[i],v->pcm_storage*sizeof(*v->pcm[i]));
    }
  }

  for(i=0;i<vi->channels;i++)
    v->pcmret[i]=v->pcm[i]+v->pcm_current;

  return(v->pcmret);
}

static void _preextrapolate_helper(vorbis_dsp_state *v){
  int i;
  int order=32;
  float *lpc=alloca(order*sizeof(*lpc));
  float *work=alloca(v->pcm_current*sizeof(*work));
  long j;
  v->preextrapolate=1;

  if(v->pcm_current-v->centerW>order*2){ /* safety */
    for(i=0;i<v->vi->channels;i++){
      /* need to run the extrapolation in reverse! */
      for(j=0;j<v->pcm_current;j++)
        work[j]=v->pcm[i][v->pcm_current-j-1];

      /* prime as above */
      vorbis_lpc_from_data(work,lpc,v->pcm_current-v->centerW,order);

      /* run the predictor filter */
      vorbis_lpc_predict(lpc,work+v->pcm_current-v->centerW-order,
                         order,
                         work+v->pcm_current-v->centerW,
                         v->centerW);

      for(j=0;j<v->pcm_current;j++)
        v->pcm[i][v->pcm_current-j-1]=work[j];

    }
  }
}


/* call with val<=0 to set eof */

int vorbis_analysis_wrote(vorbis_dsp_state *v, int vals){
  vorbis_info *vi=v->vi;
  codec_setup_info *ci=vi->codec_setup;
  /*backend_lookup_state *b=v->backend_state;*/

  if(vals<=0){
    int order=32;
    int i;
    float *lpc=alloca(order*sizeof(*lpc));

    /* if it wasn't done earlier (very short sample) */
    if(!v->preextrapolate)
      _preextrapolate_helper(v);

    /* We're encoding the end of the stream.  Just make sure we have
       [at least] a few full blocks of zeroes at the end. */
    /* actually, we don't want zeroes; that could drop a large
       amplitude off a cliff, creating spread spectrum noise that will
       suck to encode.  Extrapolate for the sake of cleanliness. */

    vorbis_analysis_buffer(v,ci->blocksizes[1]*3);
    v->eofflag=v->pcm_current;
    v->pcm_current+=ci->blocksizes[1]*3;

    for(i=0;i<vi->channels;i++){
      if(v->eofflag>order*2){
        /* extrapolate with LPC to fill in */
        long n;

        /* make a predictor filter */
        n=v->eofflag;
        if(n>ci->blocksizes[1])n=ci->blocksizes[1];
        vorbis_lpc_from_data(v->pcm[i]+v->eofflag-n,lpc,n,order);

        /* run the predictor filter */
        vorbis_lpc_predict(lpc,v->pcm[i]+v->eofflag-order,order,
                           v->pcm[i]+v->eofflag,v->pcm_current-v->eofflag);
      }else{
        /* not enough data to extrapolate (unlikely to happen due to
           guarding the overlap, but bulletproof in case that
           assumtion goes away). zeroes will do. */
        memset(v->pcm[i]+v->eofflag,0,
               (v->pcm_current-v->eofflag)*sizeof(*v->pcm[i]));

      }
    }
  }else{

    if(v->pcm_current+vals>v->pcm_storage)
      return(OV_EINVAL);

    v->pcm_current+=vals;

    /* we may want to reverse extrapolate the beginning of a stream
       too... in case we're beginning on a cliff! */
    /* clumsy, but simple.  It only runs once, so simple is good. */
    if(!v->preextrapolate && v->pcm_current-v->centerW>ci->blocksizes[1])
      _preextrapolate_helper(v);

  }
  return(0);
}

/* do the deltas, envelope shaping, pre-echo and determine the size of
   the next block on which to continue analysis */
int vorbis_analysis_blockout(vorbis_dsp_state *v,vorbis_block *vb){
  int i;
  vorbis_info *vi=v->vi;
  codec_setup_info *ci=vi->codec_setup;
  backend_lookup_state *b=v->backend_state;
  vorbis_look_psy_global *g=b->psy_g_look;
  vorbis_info_psy_global *gi=&ci->psy_g_param;
  long beginW=v->centerW-ci->blocksizes[v->W]/2,centerNext;
  vorbis_block_internal *vbi=(vorbis_block_internal *)vb->internal;

  /* check to see if we're started... */
  if(!v->preextrapolate)return(0);

  /* check to see if we're done... */
  if(v->eofflag==-1)return(0);

  /* By our invariant, we have lW, W and centerW set.  Search for
     the next boundary so we can determine nW (the next window size)
     which lets us compute the shape of the current block's window */

  /* we do an envelope search even on a single blocksize; we may still
     be throwing more bits at impulses, and envelope search handles
     marking impulses too. */
  {
    long bp=_ve_envelope_search(v);
    if(bp==-1){

      if(v->eofflag==0)return(0); /* not enough data currently to search for a
                                     full long block */
      v->nW=0;
    }else{

      if(ci->blocksizes[0]==ci->blocksizes[1])
        v->nW=0;
      else
        v->nW=bp;
    }
  }

  centerNext=v->centerW+ci->blocksizes[v->W]/4+ci->blocksizes[v->nW]/4;

  {
    /* center of next block + next block maximum right side. */

    long blockbound=centerNext+ci->blocksizes[v->nW]/2;
    if(v->pcm_current<blockbound)return(0); /* not enough data yet;
                                               although this check is
                                               less strict that the
                                               _ve_envelope_search,
                                               the search is not run
                                               if we only use one
                                               block size */


  }

  /* fill in the block.  Note that for a short window, lW and nW are *short*
     regardless of actual settings in the stream */

  _vorbis_block_ripcord(vb);
  vb->lW=v->lW;
  vb->W=v->W;
  vb->nW=v->nW;

  if(v->W){
    if(!v->lW || !v->nW){
      vbi->blocktype=BLOCKTYPE_TRANSITION;
      /*fprintf(stderr,"-");*/
    }else{
      vbi->blocktype=BLOCKTYPE_LONG;
      /*fprintf(stderr,"_");*/
    }
  }else{
    if(_ve_envelope_mark(v)){
      vbi->blocktype=BLOCKTYPE_IMPULSE;
      /*fprintf(stderr,"|");*/

    }else{
      vbi->blocktype=BLOCKTYPE_PADDING;
      /*fprintf(stderr,".");*/

    }
  }

  vb->vd=v;
  vb->sequence=v->sequence++;
  vb->granulepos=v->granulepos;
  vb->pcmend=ci->blocksizes[v->W];

  /* copy the vectors; this uses the local storage in vb */

  /* this tracks 'strongest peak' for later psychoacoustics */
  /* moved to the global psy state; clean this mess up */
  if(vbi->ampmax>g->ampmax)g->ampmax=vbi->ampmax;
  g->ampmax=_vp_ampmax_decay(g->ampmax,v);
  vbi->ampmax=g->ampmax;

  vb->pcm=_vorbis_block_alloc(vb,sizeof(*vb->pcm)*vi->channels);
  vbi->pcmdelay=_vorbis_block_alloc(vb,sizeof(*vbi->pcmdelay)*vi->channels);
  for(i=0;i<vi->channels;i++){
    vbi->pcmdelay[i]=
      _vorbis_block_alloc(vb,(vb->pcmend+beginW)*sizeof(*vbi->pcmdelay[i]));
    memcpy(vbi->pcmdelay[i],v->pcm[i],(vb->pcmend+beginW)*sizeof(*vbi->pcmdelay[i]));
    vb->pcm[i]=vbi->pcmdelay[i]+beginW;

    /* before we added the delay
       vb->pcm[i]=_vorbis_block_alloc(vb,vb->pcmend*sizeof(*vb->pcm[i]));
       memcpy(vb->pcm[i],v->pcm[i]+beginW,ci->blocksizes[v->W]*sizeof(*vb->pcm[i]));
    */

  }

  /* handle eof detection: eof==0 means that we've not yet received EOF
                           eof>0  marks the last 'real' sample in pcm[]
                           eof<0  'no more to do'; doesn't get here */

  if(v->eofflag){
    if(v->centerW>=v->eofflag){
      v->eofflag=-1;
      vb->eofflag=1;
      return(1);
    }
  }

  /* advance storage vectors and clean up */
  {
    int new_centerNext=ci->blocksizes[1]/2;
    int movementW=centerNext-new_centerNext;

    if(movementW>0){

      _ve_envelope_shift(b->ve,movementW);
      v->pcm_current-=movementW;

      for(i=0;i<vi->channels;i++)
        memmove(v->pcm[i],v->pcm[i]+movementW,
                v->pcm_current*sizeof(*v->pcm[i]));


      v->lW=v->W;
      v->W=v->nW;
      v->centerW=new_centerNext;

      if(v->eofflag){
        v->eofflag-=movementW;
        if(v->eofflag<=0)v->eofflag=-1;
        /* do not add padding to end of stream! */
        if(v->centerW>=v->eofflag){
          v->granulepos+=movementW-(v->centerW-v->eofflag);
        }else{
          v->granulepos+=movementW;
        }
      }else{
        v->granulepos+=movementW;
      }
    }
  }

  /* done */
  return(1);
}

int vorbis_synthesis_init(vorbis_dsp_state *v,vorbis_info *vi){
  _vds_shared_init(v,vi,0);

  v->pcm_returned=-1;
  v->granulepos=-1;
  v->sequence=-1;

  return(0);
}

/* Unlike in analysis, the window is only partially applied for each
   block.  The time domain envelope is not yet handled at the point of
   calling (as it relies on the previous block). */

int vorbis_synthesis_blockin(vorbis_dsp_state *v,vorbis_block *vb){
  vorbis_info *vi=v->vi;
  codec_setup_info *ci=vi->codec_setup;
  int i,j;

  if(!vb)return(OV_EINVAL);
  if(v->pcm_current>v->pcm_returned  && v->pcm_returned!=-1)return(OV_EINVAL);

  v->lW=v->W;
  v->W=vb->W;
  v->nW=-1;

  if(v->sequence+1 != vb->sequence)v->granulepos=-1; /* out of sequence;
                                                        lose count */
  v->sequence=vb->sequence;

  if(vb->pcm){  /* not pcm to process if vorbis_synthesis_trackonly
                   was called on block */
    int n=ci->blocksizes[v->W]/2;
    int n0=ci->blocksizes[0]/2;
    int n1=ci->blocksizes[1]/2;

    int thisCenter;
    int prevCenter;

    v->glue_bits+=vb->glue_bits;
    v->time_bits+=vb->time_bits;
    v->floor_bits+=vb->floor_bits;
    v->res_bits+=vb->res_bits;

    if(v->centerW){
      thisCenter=n1;
      prevCenter=0;
    }else{
        thisCenter=0;
        prevCenter=n1;
    }

    /* v->pcm is now used like a two-stage double buffer.  We don't want
       to have to constantly shift *or* adjust memory usage.  Don't
       accept a new block until the old is shifted out */

    /* overlap/add PCM */

    for(j=0;j<vi->channels;j++){
      /* the overlap/add section */
      if(v->lW){
        if(v->W){
          /* large/large */
          float *pcm=v->pcm[j]+prevCenter;
          float *p=vb->pcm[j];
          for(i=0;i<n1;i++)
            pcm[i]+=p[i];
        }else{
          /* large/small */
          float *pcm=v->pcm[j]+prevCenter+n1/2-n0/2;
          float *p=vb->pcm[j];
          for(i=0;i<n0;i++)
            pcm[i]+=p[i];
        }
      }else{
        if(v->W){
          /* small/large */
          float *pcm=v->pcm[j]+prevCenter;
          float *p=vb->pcm[j]+n1/2-n0/2;
          for(i=0;i<n0;i++)
            pcm[i]+=p[i];
          for(;i<n1/2+n0/2;i++)
            pcm[i]=p[i];
        }else{
          /* small/small */
          float *pcm=v->pcm[j]+prevCenter;
          float *p=vb->pcm[j];
          for(i=0;i<n0;i++)
            pcm[i]+=p[i];
        }
      }

      /* the copy section */
      {
        float *pcm=v->pcm[j]+thisCenter;
        float *p=vb->pcm[j]+n;
        for(i=0;i<n;i++)
          pcm[i]=p[i];
      }
    }

    if(v->centerW)
      v->centerW=0;
    else
      v->centerW=n1;

    /* deal with initial packet state; we do this using the explicit
       pcm_returned==-1 flag otherwise we're sensitive to first block
       being short or long */

    if(v->pcm_returned==-1){
      v->pcm_returned=thisCenter;
      v->pcm_current=thisCenter;
    }else{
      v->pcm_returned=prevCenter;
      v->pcm_current=prevCenter+
        ci->blocksizes[v->lW]/4+
        ci->blocksizes[v->W]/4;
    }

  }

  /* track the frame number... This is for convenience, but also
     making sure our last packet doesn't end with added padding.  If
     the last packet is partial, the number of samples we'll have to
     return will be past the vb->granulepos.

     This is not foolproof!  It will be confused if we begin
     decoding at the last page after a seek or hole.  In that case,
     we don't have a starting point to judge where the last frame
     is.  For this reason, vorbisfile will always try to make sure
     it reads the last two marked pages in proper sequence */

  if(v->granulepos==-1){
    if(vb->granulepos!=-1){ /* only set if we have a position to set to */
      v->granulepos=vb->granulepos;
    }
  }else{
    v->granulepos+=ci->blocksizes[v->lW]/4+ci->blocksizes[v->W]/4;
    if(vb->granulepos!=-1 && v->granulepos!=vb->granulepos){

      if(v->granulepos>vb->granulepos){
        long extra=v->granulepos-vb->granulepos;

        if(vb->eofflag){
          /* partial last frame.  Strip the extra samples off */
          v->pcm_current-=extra;
        }else if(vb->sequence == 1){
          /* ^^^ argh, this can be 1 from seeking! */


          /* partial first frame.  Discard extra leading samples */
          v->pcm_returned+=extra;
          if(v->pcm_returned>v->pcm_current)
            v->pcm_returned=v->pcm_current;

        } /* else {Shouldn't happen *unless* the bitstream is out of
             spec.  Either way, believe the bitstream } */
      } /* else {Shouldn't happen *unless* the bitstream is out of
           spec.  Either way, believe the bitstream } */
      v->granulepos=vb->granulepos;
    }
  }

  /* Update, cleanup */

  if(vb->eofflag)v->eofflag=1;
  return(0);

}

/* pcm==NULL indicates we just want the pending samples, no more */
int vorbis_synthesis_pcmout(vorbis_dsp_state *v,float ***pcm){
  vorbis_info *vi=v->vi;
  if(v->pcm_returned>-1 && v->pcm_returned<v->pcm_current){
    if(pcm){
      int i;
      for(i=0;i<vi->channels;i++)
        v->pcmret[i]=v->pcm[i]+v->pcm_returned;
      *pcm=v->pcmret;
    }
    return(v->pcm_current-v->pcm_returned);
  }
  return(0);
}

int vorbis_synthesis_read(vorbis_dsp_state *v,int n){
  if(n && v->pcm_returned+n>v->pcm_current)return(OV_EINVAL);
  v->pcm_returned+=n;
  return(0);
}
