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
/* Writable tables (ATH, tonemasks, stereo_threshholds, FLOOR1_fromdB_INV_LOOKUP, hypot_lookup) are declared extern and bound to
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

 function: psychoacoustics not including preecho
 last mod: $Id: psy.c,v 1.74 2002/07/13 10:18:33 giles Exp $

 ********************************************************************/

/* #include <stdlib.h> : included above */
/* #include <math.h> : included above */
/* #include <string.h> : included above */
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
#include "campaign_ogg_integer_types.h"

#endif  /* _OS_TYPES_H */
#include "campaign_vorbis_fpu_types.h"

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

/* ---- masking.h ---- */
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

 function: masking curve data for psychoacoustics
 last mod: $Id: masking.h,v 1.24 2002/07/01 11:20:11 xiphmont Exp $

 ********************************************************************/

#ifndef _V_MASKING_H_
#define _V_MASKING_H_

/* more detailed ATH; the bass if flat to save stressing the floor
   overly for only a bin or two of savings. */

#define MAX_ATH 88
extern float ATH[];
#if 0 /* the library definition; the retail copy is bound instead */
static float ATH[]={
  /*15*/  -51, -52, -53, -54, -55, -56, -57, -58,
  /*31*/  -59, -60, -61, -62, -63, -64, -65, -66,
  /*63*/  -67, -68, -69, -70, -71, -72, -73, -74,
  /*125*/ -75, -76, -77, -78, -80, -81, -82, -83,
  /*250*/ -84, -85, -86, -87, -88, -88, -89, -89,
  /*500*/ -90, -91, -91, -92, -93, -94, -95, -96,
  /*1k*/  -96, -97, -98, -98, -99, -99,-100,-100,
  /*2k*/ -101,-102,-103,-104,-106,-107,-107,-107,
  /*4k*/ -107,-105,-103,-102,-101, -99, -98, -96,
  /*8k*/  -95, -95, -96, -97, -96, -95, -93, -90,
  /*16k*/ -80, -70, -50, -40, -30, -30, -30, -30
};
#endif

/* The tone masking curves from Ehmer's and Fielder's papers have been
   replaced by an empirically collected data set.  The previously
   published values were, far too often, simply on crack. */

#define EHMER_OFFSET 16
#define EHMER_MAX 56

/* masking tones from -50 to 0dB, 62.5 through 16kHz at half octaves
   test tones from -2 octaves to +5 octaves sampled at eighth octaves */
/* (Vorbis 0dB, the loudest possible tone, is assumed to be ~100dB SPL
   for collection of these curves) */

extern float tonemasks[P_BANDS][6][EHMER_MAX];
#if 0 /* the library definition; the retail copy is bound instead */
static float tonemasks[P_BANDS][6][EHMER_MAX]={
  /* 62.5 Hz */
  {{ -60,  -60,  -60,  -60,  -60,  -60,  -60,  -60,
     -60,  -60,  -60,  -60,  -62,  -62,  -65,  -73,
     -69,  -68,  -68,  -67,  -70,  -70,  -72,  -74,
     -75,  -79,  -79,  -80,  -83,  -88,  -93, -100,
     -110, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -48,  -48,  -48,  -48,  -48,  -48,  -48,  -48,
     -48,  -48,  -48,  -48,  -48,  -53,  -61,  -66,
     -66,  -68,  -67,  -70,  -76,  -76,  -72,  -73,
     -75,  -76,  -78,  -79,  -83,  -88,  -93, -100,
     -110, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -37,  -37,  -37,  -37,  -37,  -37,  -37,  -37,
     -38,  -40,  -42,  -46,  -48,  -53,  -55,  -62,
     -65,  -58,  -56,  -56,  -61,  -60,  -65,  -67,
     -69,  -71,  -77,  -77,  -78,  -80,  -82,  -84,
     -88,  -93,  -98, -106, -112, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -25,  -25,  -25,  -25,  -25,  -25,  -25,  -25,
     -25,  -26,  -27,  -29,  -32,  -38,  -48,  -52,
     -52,  -50,  -48,  -48,  -51,  -52,  -54,  -60,
     -67,  -67,  -66,  -68,  -69,  -73,  -73,  -76,
     -80,  -81,  -81,  -85,  -85,  -86,  -88,  -93,
     -100, -110, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -16,  -16,  -16,  -16,  -16,  -16,  -16,  -16,
     -17,  -19,  -20,  -22,  -26,  -28,  -31,  -40,
     -47,  -39,  -39,  -40,  -42,  -43,  -47,  -51,
     -57,  -52,  -55,  -55,  -60,  -58,  -62,  -63,
     -70,  -67,  -69,  -72,  -73,  -77,  -80,  -82,
     -83,  -87,  -90,  -94,  -98, -104, -115, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   {  -8,   -8,   -8,   -8,   -8,   -8,   -8,   -8,
      -8,   -8,  -10,  -11,  -15,  -19,  -25,  -30,
      -34,  -31,  -30,  -31,  -29,  -32,  -35,  -42,
      -48,  -42,  -44,  -46,  -50,  -50,  -51,  -52,
      -59,  -54,  -55,  -55,  -58,  -62,  -63,  -66,
      -72,  -73,  -76,  -75,  -78,  -80,  -80,  -81,
      -84,  -88,  -90,  -94,  -98, -101, -106, -110}},
  /* 88Hz */
  {{ -66,  -66,  -66,  -66,  -66,  -66,  -66,  -66,
     -66,  -66,  -66,  -66,  -66,  -67,  -67,  -67,
     -76,  -72,  -71,  -74,  -76,  -76,  -75,  -78,
     -79,  -79,  -81,  -83,  -86,  -89,  -93,  -97,
     -100, -105, -110, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -47,  -47,  -47,  -47,  -47,  -47,  -47,  -47,
     -47,  -47,  -47,  -48,  -51,  -55,  -59,  -66,
     -66,  -66,  -67,  -66,  -68,  -69,  -70,  -74,
     -79,  -77,  -77,  -78,  -80,  -81,  -82,  -84,
     -86,  -88,  -91,  -95, -100, -108, -116, -999,
     -999, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -36,  -36,  -36,  -36,  -36,  -36,  -36,  -36,
     -36,  -37,  -37,  -41,  -44,  -48,  -51,  -58,
     -62,  -60,  -57,  -59,  -59,  -60,  -63,  -65,
     -72,  -71,  -70,  -72,  -74,  -77,  -76,  -78,
     -81,  -81,  -80,  -83,  -86,  -91,  -96, -100,
     -105, -110, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -28,  -28,  -28,  -28,  -28,  -28,  -28,  -28,
     -28,  -30,  -32,  -32,  -33,  -35,  -41,  -49,
     -50,  -49,  -47,  -48,  -48,  -52,  -51,  -57,
     -65,  -61,  -59,  -61,  -64,  -69,  -70,  -74,
     -77,  -77,  -78,  -81,  -84,  -85,  -87,  -90,
     -92,  -96, -100, -107, -112, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -19,  -19,  -19,  -19,  -19,  -19,  -19,  -19,
     -20,  -21,  -23,  -27,  -30,  -35,  -36,  -41,
     -46,  -44,  -42,  -40,  -41,  -41,  -43,  -48,
     -55,  -53,  -52,  -53,  -56,  -59,  -58,  -60,
     -67,  -66,  -69,  -71,  -72,  -75,  -79,  -81,
     -84,  -87,  -90,  -93,  -97, -101, -107, -114,
     -999, -999, -999, -999, -999, -999, -999, -999},
   {  -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
      -11,  -12,  -12,  -15,  -16,  -20,  -23,  -30,
      -37,  -34,  -33,  -34,  -31,  -32,  -32,  -38,
      -47,  -44,  -41,  -40,  -47,  -49,  -46,  -46,
      -58,  -50,  -50,  -54,  -58,  -62,  -64,  -67,
      -67,  -70,  -72,  -76,  -79,  -83,  -87,  -91,
      -96, -100, -104, -110, -999, -999, -999, -999}},
  /* 125 Hz */
  {{ -62,  -62,  -62,  -62,  -62,  -62,  -62,  -62,
     -62,  -62,  -63,  -64,  -66,  -67,  -66,  -68,
     -75,  -72,  -76,  -75,  -76,  -78,  -79,  -82,
     -84,  -85,  -90,  -94, -101, -110, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -59,  -59,  -59,  -59,  -59,  -59,  -59,  -59,
     -59,  -59,  -59,  -60,  -60,  -61,  -63,  -66,
     -71,  -68,  -70,  -70,  -71,  -72,  -72,  -75,
     -81,  -78,  -79,  -82,  -83,  -86,  -90,  -97,
     -103, -113, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -53,  -53,  -53,  -53,  -53,  -53,  -53,  -53,
     -53,  -54,  -55,  -57,  -56,  -57,  -55,  -61,
     -65,  -60,  -60,  -62,  -63,  -63,  -66,  -68,
     -74,  -73,  -75,  -75,  -78,  -80,  -80,  -82,
     -85,  -90,  -96, -101, -108, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -46,  -46,  -46,  -46,  -46,  -46,  -46,  -46,
     -46,  -46,  -47,  -47,  -47,  -47,  -48,  -51,
     -57,  -51,  -49,  -50,  -51,  -53,  -54,  -59,
     -66,  -60,  -62,  -67,  -67,  -70,  -72,  -75,
     -76,  -78,  -81,  -85,  -88,  -94,  -97, -104,
     -112, -999, -999, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -36,  -36,  -36,  -36,  -36,  -36,  -36,  -36,
     -39,  -41,  -42,  -42,  -39,  -38,  -41,  -43,
     -52,  -44,  -40,  -39,  -37,  -37,  -40,  -47,
     -54,  -50,  -48,  -50,  -55,  -61,  -59,  -62,
     -66,  -66,  -66,  -69,  -69,  -73,  -74,  -74,
     -75,  -77,  -79,  -82,  -87,  -91,  -95, -100,
     -108, -115, -999, -999, -999, -999, -999, -999},
   { -28,  -26,  -24,  -22,  -20,  -20,  -23,  -29,
     -30,  -31,  -28,  -27,  -28,  -28,  -28,  -35,
     -40,  -33,  -32,  -29,  -30,  -30,  -30,  -37,
     -45,  -41,  -37,  -38,  -45,  -47,  -47,  -48,
     -53,  -49,  -48,  -50,  -49,  -49,  -51,  -52,
     -58,  -56,  -57,  -56,  -60,  -61,  -62,  -70,
     -72,  -74,  -78,  -83,  -88,  -93, -100, -106}},
  /* 177 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -110, -105, -100,  -95,  -91,  -87,  -83,
    -80,  -78,  -76,  -78,  -78,  -81,  -83,  -85,
    -86,  -85,  -86,  -87,  -90,  -97, -107, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -110, -105, -100,  -95,  -90,
    -85,  -81,  -77,  -73,  -70,  -67,  -67,  -68,
    -75,  -73,  -70,  -69,  -70,  -72,  -75,  -79,
    -84,  -83,  -84,  -86,  -88,  -89,  -89,  -93,
    -98, -105, -112, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-105, -100,  -95,  -90,  -85,  -80,  -76,  -71,
    -68,  -68,  -65,  -63,  -63,  -62,  -62,  -64,
    -65,  -64,  -61,  -62,  -63,  -64,  -66,  -68,
    -73,  -73,  -74,  -75,  -76,  -81,  -83,  -85,
    -88,  -89,  -92,  -95, -100, -108, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   { -80,  -75,  -71,  -68,  -65,  -63,  -62,  -61,
     -61,  -61,  -61,  -59,  -56,  -57,  -53,  -50,
     -58,  -52,  -50,  -50,  -52,  -53,  -54,  -58,
     -67,  -63,  -67,  -68,  -72,  -75,  -78,  -80,
     -81,  -81,  -82,  -85,  -89,  -90,  -93,  -97,
     -101, -107, -114, -999, -999, -999, -999, -999,
     -999, -999, -999, -999, -999, -999, -999, -999},
   { -65,  -61,  -59,  -57,  -56,  -55,  -55,  -56,
     -56,  -57,  -55,  -53,  -52,  -47,  -44,  -44,
     -50,  -44,  -41,  -39,  -39,  -42,  -40,  -46,
     -51,  -49,  -50,  -53,  -54,  -63,  -60,  -61,
     -62,  -66,  -66,  -66,  -70,  -73,  -74,  -75,
     -76,  -75,  -79,  -85,  -89,  -91,  -96, -102,
     -110, -999, -999, -999, -999, -999, -999, -999},
   { -52,  -50,  -49,  -49,  -48,  -48,  -48,  -49,
     -50,  -50,  -49,  -46,  -43,  -39,  -35,  -33,
     -38,  -36,  -32,  -29,  -32,  -32,  -32,  -35,
     -44,  -39,  -38,  -38,  -46,  -50,  -45,  -46,
     -53,  -50,  -50,  -50,  -54,  -54,  -53,  -53,
     -56,  -57,  -59,  -66,  -70,  -72,  -74,  -79,
     -83,  -85,  -90, -97, -114, -999, -999, -999}},
  /* 250 Hz */
  {{-999, -999, -999, -999, -999, -999, -110, -105,
    -100,  -95,  -90,  -86,  -80,  -75,  -75,  -79,
    -80,  -79,  -80,  -81,  -82,  -88,  -95, -103,
    -110, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -108, -103,  -98,  -93,
    -88,  -83,  -79,  -78,  -75,  -71,  -67,  -68,
    -73,  -73,  -72,  -73,  -75,  -77,  -80,  -82,
    -88,  -93, -100, -107, -114, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -110, -105, -101,  -96,  -90,
    -86,  -81,  -77,  -73,  -69,  -66,  -61,  -62,
    -66,  -64,  -62,  -65,  -66,  -70,  -72,  -76,
    -81,  -80,  -84,  -90,  -95, -102, -110, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -107, -103,  -97,  -92,  -88,
    -83,  -79,  -74,  -70,  -66,  -59,  -53,  -58,
    -62,  -55,  -54,  -54,  -54,  -58,  -61,  -62,
    -72,  -70,  -72,  -75,  -78,  -80,  -81,  -80,
    -83,  -83,  -88,  -93, -100, -107, -115, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -105, -100,  -95,  -90,  -85,
    -80,  -75,  -70,  -66,  -62,  -56,  -48,  -44,
    -48,  -46,  -46,  -43,  -46,  -48,  -48,  -51,
    -58,  -58,  -59,  -60,  -62,  -62,  -61,  -61,
    -65,  -64,  -65,  -68,  -70,  -74,  -75,  -78,
    -81,  -86,  -95, -110, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999,  -999, -105, -100,  -95,  -90,  -85,  -80,
    -75,  -70,  -65,  -61,  -55,  -49,  -39,  -33,
    -40,  -35,  -32,  -38,  -40,  -33,  -35,  -37,
    -46,  -41,  -45,  -44,  -46,  -42,  -45,  -46,
    -52,  -50,  -50,  -50,  -54,  -54,  -55,  -57,
    -62,  -64,  -66,  -68,  -70,  -76,  -81,  -90,
    -100, -110, -999, -999, -999, -999, -999, -999}},
  /* 354 hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -105,  -98,  -90,  -85,  -82,  -83,  -80,  -78,
    -84,  -79,  -80,  -83,  -87,  -89,  -91,  -93,
    -99, -106, -117, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -105,  -98,  -90,  -85,  -80,  -75,  -70,  -68,
    -74,  -72,  -74,  -77,  -80,  -82,  -85,  -87,
    -92,  -89,  -91,  -95, -100, -106, -112, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -105,  -98,  -90,  -83,  -75,  -71,  -63,  -64,
    -67,  -62,  -64,  -67,  -70,  -73,  -77,  -81,
    -84,  -83,  -85,  -89,  -90,  -93,  -98, -104,
    -109, -114, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -103,  -96,  -88,  -81,  -75,  -68,  -58,  -54,
    -56,  -54,  -56,  -56,  -58,  -60,  -63,  -66,
    -74,  -69,  -72,  -72,  -75,  -74,  -77,  -81,
    -81,  -82,  -84,  -87,  -93,  -96,  -99, -104,
    -110, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -108, -102,  -96,
    -91,  -85,  -80,  -74,  -68,  -60,  -51,  -46,
    -48,  -46,  -43,  -45,  -47,  -47,  -49,  -48,
    -56,  -53,  -55,  -58,  -57,  -63,  -58,  -60,
    -66,  -64,  -67,  -70,  -70,  -74,  -77,  -84,
    -86,  -89,  -91,  -93,  -94, -101, -109, -118,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -108, -103,  -98,  -93,  -88,
    -83,  -78,  -73,  -68,  -60,  -53,  -44,  -35,
    -38,  -38,  -34,  -34,  -36,  -40,  -41,  -44,
    -51,  -45,  -46,  -47,  -46,  -54,  -50,  -49,
    -50,  -50,  -50,  -51,  -54,  -57,  -58,  -60,
    -66,  -66,  -66,  -64,  -65,  -68,  -77,  -82,
    -87,  -95, -110, -999, -999, -999, -999, -999}},
  /* 500 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -107, -102,  -97,  -92,  -87,  -83,  -78,  -75,
    -82,  -79,  -83,  -85,  -89,  -92,  -95,  -98,
    -101, -105, -109, -113, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -106,
    -100,  -95,  -90,  -86,  -81,  -78,  -74,  -69,
    -74,  -74,  -76,  -79,  -83,  -84,  -86,  -89,
    -92,  -97,  -93, -100, -103, -107, -110, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -106, -100,
    -95, -90, -87, -83, -80, -75, -69, -60,
    -66, -66, -68, -70, -74, -78, -79, -81,
    -81, -83, -84, -87, -93, -96, -99, -103,
    -107, -110, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -108, -103, -98,
    -93, -89, -85, -82, -78, -71, -62, -55,
    -58, -58, -54, -54, -55, -59, -61, -62,
    -70, -66, -66, -67, -70, -72, -75, -78,
    -84, -84, -84, -88, -91, -90, -95, -98,
    -102, -103, -106, -110, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -108, -103,  -98,  -94,
    -90,  -87,  -82,  -79,  -73,  -67,  -58,  -47,
    -50,  -45,  -41,  -45,  -48,  -44,  -44,  -49,
    -54,  -51,  -48,  -47,  -49,  -50,  -51,  -57,
    -58,  -60,  -63,  -69,  -70,  -69,  -71,  -74,
    -78,  -82,  -90,  -95, -101, -105, -110, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -105, -101, -97, -93, -90,
    -85, -80, -77, -72, -65, -56, -48, -37,
    -40, -36, -34, -40, -50, -47, -38, -41,
    -47, -38, -35, -39, -38, -43, -40, -45,
    -50, -45, -44, -47, -50, -55, -48, -48,
    -52, -66, -70, -76, -82, -90, -97, -105,
    -110, -999, -999, -999, -999, -999, -999, -999}},
  /* 707 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -108, -103,  -98,  -93,  -86,  -79,  -76,
    -83,  -81,  -85,  -87,  -89,  -93,  -98, -102,
    -107, -112, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -108, -103,  -98,  -93,  -86,  -79,  -71,
    -77,  -74,  -77,  -79,  -81,  -84,  -85,  -90,
    -92,  -93,  -92,  -98, -101, -108, -112, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -108, -103,  -98,  -93,  -87,  -78,  -68,  -65,
    -66,  -62,  -65,  -67,  -70,  -73,  -75,  -78,
    -82,  -82,  -83,  -84,  -91,  -93,  -98, -102,
    -106, -110, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -105, -100, -95, -90, -82, -74, -62, -57,
    -58, -56, -51, -52, -52, -54, -54, -58,
    -66, -59, -60, -63, -66, -69, -73, -79,
    -83, -84, -80, -81, -81, -82, -88, -92,
    -98, -105, -113, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -107,
    -102,  -97,  -92,  -84,  -79,  -69,  -57,  -47,
    -52,  -47,  -44,  -45,  -50,  -52,  -42,  -42,
    -53,  -43,  -43,  -48,  -51,  -56,  -55,  -52,
    -57,  -59,  -61,  -62,  -67,  -71,  -78,  -83,
    -86,  -94,  -98, -103, -110, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -105, -100,
    -95,  -90,  -84,  -78,  -70,  -61,  -51,  -41,
    -40,  -38,  -40,  -46,  -52,  -51,  -41,  -40,
    -46,  -40,  -38,  -38,  -41,  -46,  -41,  -46,
    -47,  -43,  -43,  -45,  -41,  -45,  -56,  -67,
    -68,  -83,  -87,  -90,  -95, -102, -107, -113,
    -999, -999, -999, -999, -999, -999, -999, -999}},
  /* 1000 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -109, -105, -101,  -96,  -91,  -84,  -77,
    -82,  -82,  -85,  -89,  -94, -100, -106, -110,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -106, -103,  -98,  -92,  -85,  -80,  -71,
    -75,  -72,  -76,  -80,  -84,  -86,  -89,  -93,
    -100, -107, -113, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -107,
    -104, -101,  -97,  -92,  -88,  -84,  -80,  -64,
    -66,  -63,  -64,  -66,  -69,  -73,  -77,  -83,
    -83,  -86,  -91,  -98, -104, -111, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -107,
    -104, -101,  -97,  -92,  -90,  -84,  -74,  -57,
    -58,  -52,  -55,  -54,  -50,  -52,  -50,  -52,
    -63,  -62,  -69,  -76,  -77,  -78,  -78,  -79,
    -82,  -88,  -94, -100, -106, -111, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -106, -102,
    -98,  -95,  -90,  -85,  -83,  -78,  -70,  -50,
    -50,  -41,  -44,  -49,  -47,  -50,  -50,  -44,
    -55,  -46,  -47,  -48,  -48,  -54,  -49,  -49,
    -58,  -62,  -71,  -81,  -87,  -92,  -97, -102,
    -108, -114, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -106, -102,
    -98,  -95,  -90,  -85,  -83,  -78,  -70,  -45,
    -43,  -41,  -47,  -50,  -51,  -50,  -49,  -45,
    -47,  -41,  -44,  -41,  -39,  -43,  -38,  -37,
    -40,  -41,  -44,  -50,  -58,  -65,  -73,  -79,
    -85,  -92,  -97, -101, -105, -109, -113, -999,
    -999, -999, -999, -999, -999, -999, -999, -999}},
  /* 1414 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -107, -100,  -95,  -87,  -81,
    -85,  -83,  -88,  -93, -100, -107, -114, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -107, -101,  -95,  -88,  -83,  -76,
    -73,  -72,  -79,  -84,  -90,  -95, -100, -105,
    -110, -115, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -104,  -98,  -92,  -87,  -81,  -70,
    -65,  -62,  -67,  -71,  -74,  -80,  -85,  -91,
    -95,  -99, -103, -108, -111, -114, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -103,  -97,  -90,  -85,  -76,  -60,
    -56,  -54,  -60,  -62,  -61,  -56,  -63,  -65,
    -73,  -74,  -77,  -75,  -78,  -81,  -86,  -87,
    -88,  -91,  -94,  -98, -103, -110, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -105,
    -100,  -97,  -92,  -86,  -81,  -79,  -70,  -57,
    -51,  -47,  -51,  -58,  -60,  -56,  -53,  -50,
    -58,  -52,  -50,  -50,  -53,  -55,  -64,  -69,
    -71,  -85,  -82,  -78,  -81,  -85,  -95, -102,
    -112, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -105,
    -100,  -97,  -92,  -85,  -83,  -79,  -72,  -49,
    -40,  -43,  -43,  -54,  -56,  -51,  -50,  -40,
    -43,  -38,  -36,  -35,  -37,  -38,  -37,  -44,
    -54,  -60,  -57,  -60,  -70,  -75,  -84,  -92,
    -103, -112, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999}},
  /* 2000 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -110, -102,  -95,  -89,  -82,
    -83,  -84,  -90,  -92,  -99, -107, -113, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -107, -101,  -95,  -89,  -83,  -72,
    -74,  -78,  -85,  -88,  -88,  -90,  -92,  -98,
    -105, -111, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -109, -103, -97, -93, -87, -81, -70,
    -70, -67, -75, -73, -76, -79, -81, -83,
    -88, -89, -97, -103, -110, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -107, -100,  -94,  -88,  -83,  -75,  -63,
    -59,  -59,  -63,  -66,  -60,  -62,  -67,  -67,
    -77,  -76,  -81,  -88,  -86,  -92,  -96, -102,
    -109, -116, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -105,  -98,  -92,  -86,  -81,  -73,  -56,
    -52,  -47,  -55,  -60,  -58,  -52,  -51,  -45,
    -49,  -50,  -53,  -54,  -61,  -71,  -70,  -69,
    -78,  -79,  -87,  -90,  -96, -104, -112, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -103,  -96,  -90,  -86,  -78,  -70,  -51,
    -42,  -47,  -48,  -55,  -54,  -54,  -53,  -42,
    -35,  -28,  -33,  -38,  -37,  -44,  -47,  -49,
    -54,  -63,  -68,  -78,  -82,  -89,  -94,  -99,
    -104, -109, -114, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999}},
  /* 2828 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -110, -100,  -90,  -79,
    -85,  -81,  -82,  -82,  -89,  -94,  -99, -103,
    -109, -115, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -105,  -97,  -85,  -72,
    -74,  -70,  -70,  -70,  -76,  -85,  -91,  -93,
    -97, -103, -109, -115, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -112,  -93,  -81,  -68,
    -62,  -60,  -60,  -57,  -63,  -70,  -77,  -82,
    -90,  -93,  -98, -104, -109, -113, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -113, -100,  -93,  -84,  -63,
    -58,  -48,  -53,  -54,  -52,  -52,  -57,  -64,
    -66,  -76,  -83,  -81,  -85,  -85,  -90,  -95,
    -98, -101, -103, -106, -108, -111, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -105,  -95,  -86,  -74,  -53,
    -50,  -38,  -43,  -49,  -43,  -42,  -39,  -39,
    -46,  -52,  -57,  -56,  -72,  -69,  -74,  -81,
    -87,  -92,  -94,  -97,  -99, -102, -105, -108,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -108,  -99,  -90,  -76,  -66,  -45,
    -43,  -41,  -44,  -47,  -43,  -47,  -40,  -30,
    -31,  -31,  -39,  -33,  -40,  -41,  -43,  -53,
    -59,  -70,  -73,  -77,  -79,  -82,  -84,  -87,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999}},
  /* 4000 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -110,  -91,  -76,
    -75,  -85,  -93,  -98, -104, -110, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -110,  -91,  -70,
    -70,  -75,  -86,  -89,  -94,  -98, -101, -106,
    -110, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -110,  -95,  -80,  -60,
    -65,  -64,  -74,  -83,  -88,  -91,  -95,  -99,
    -103, -107, -110, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -110,  -95,  -80,  -58,
    -55,  -49,  -66,  -68,  -71,  -78,  -78,  -80,
    -88,  -85,  -89,  -97, -100, -105, -110, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -110,  -95,  -80,  -53,
    -52,  -41,  -59,  -59,  -49,  -58,  -56,  -63,
    -86,  -79,  -90,  -93,  -98, -103, -107, -112,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -110,  -97,  -91,  -73,  -45,
    -40,  -33,  -53,  -61,  -49,  -54,  -50,  -50,
    -60,  -52,  -67,  -74,  -81,  -92,  -96, -100,
    -105, -110, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999}},
  /* 5657 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -113, -106,  -99,  -92,  -77,
    -80,  -88,  -97, -106, -115, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -116, -109, -102,  -95,  -89,  -74,
    -72,  -88,  -87,  -95, -102, -109, -116, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -116, -109, -102,  -95,  -89,  -75,
    -66,  -74,  -77,  -78,  -86,  -87,  -90,  -96,
    -105, -115, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -115, -108, -101,  -94,  -88,  -66,
    -56,  -61,  -70,  -65,  -78,  -72,  -83,  -84,
    -93,  -98, -105, -110, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -110, -105,  -95,  -89,  -82,  -57,
    -52,  -52,  -59,  -56,  -59,  -58,  -69,  -67,
    -88,  -82,  -82,  -89,  -94, -100, -108, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -110, -101,  -96,  -90,  -83,  -77,  -54,
    -43,  -38,  -50,  -48,  -52,  -48,  -42,  -42,
    -51,  -52,  -53,  -59,  -65,  -71,  -78,  -85,
    -95, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999}},
  /* 8000 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -120, -105,  -86,  -68,
    -78,  -79,  -90, -100, -110, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -120, -105,  -86,  -66,
    -73,  -77,  -88,  -96, -105, -115, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -120, -105,  -92,  -80,  -61,
    -64,  -68,  -80,  -87,  -92, -100, -110, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -120, -104,  -91,  -79,  -52,
    -60,  -54,  -64,  -69,  -77,  -80,  -82,  -84,
    -85,  -87,  -88,  -90, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -118, -100,  -87,  -77,  -49,
    -50,  -44,  -58,  -61,  -61,  -67,  -65,  -62,
    -62,  -62,  -65,  -68, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -115,  -98,  -84,  -62,  -49,
    -44,  -38,  -46,  -49,  -49,  -46,  -39,  -37,
    -39,  -40,  -42,  -43, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999}},
  /* 11314 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -110,  -88,  -74,
    -77,  -82,  -82,  -85,  -90,  -94,  -99, -104,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -110,  -88,  -66,
    -70,  -81,  -80,  -81,  -84,  -88,  -91,  -93,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -110,  -88,  -61,
    -63,  -70,  -71,  -74,  -77,  -80,  -83,  -85,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -110, -86, -62,
    -63,  -62,  -62,  -58,  -52,  -50,  -50,  -52,
    -54, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -118, -108,  -84,  -53,
    -50,  -50,  -50,  -55,  -47,  -45,  -40,  -40,
    -40, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -118, -100,  -73,  -43,
    -37,  -42,  -43,  -53,  -38,  -37,  -35,  -35,
    -38, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999}},
  /* 16000 Hz */
  {{-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -110, -100,  -91,  -84,  -74,
    -80,  -80,  -80,  -80,  -80, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -110, -100,  -91,  -84,  -74,
    -68,  -68,  -68,  -68,  -68, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -110, -100,  -86,  -78,  -70,
    -60,  -45,  -30,  -21, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -110, -100,  -87,  -78,  -67,
    -48,  -38,  -29,  -21, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -110, -100,  -86,  -69,  -56,
    -45,  -35,  -33,  -29, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999},
   {-999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -110, -100,  -83,  -71,  -48,
    -27,  -38,  -37,  -34, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999,
    -999, -999, -999, -999, -999, -999, -999, -999}}
};
#endif

#endif

/* ---- end masking.h ---- */
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

#define NEGINF -9999.f
extern double stereo_threshholds[];
#if 0 /* the library definition; the retail copy is bound instead */
static double stereo_threshholds[]={0.0, .5, 1.0, 1.5, 2.5, 4.5, 8.5, 16.5, 9e10};
#endif

vorbis_look_psy_global *_vp_global_look(vorbis_info *vi){
  codec_setup_info *ci=vi->codec_setup;
  vorbis_info_psy_global *gi=&ci->psy_g_param;
  vorbis_look_psy_global *look=_ogg_calloc(1,sizeof(*look));

  look->channels=vi->channels;

  look->ampmax=-9999.;
  look->gi=gi;
  return(look);
}

void _vp_global_free(vorbis_look_psy_global *look){
  if(look){
    memset(look,0,sizeof(*look));
    _ogg_free(look);
  }
}

void _vi_gpsy_free(vorbis_info_psy_global *i){
  if(i){
    memset(i,0,sizeof(*i));
    _ogg_free(i);
  }
}

void _vi_psy_free(vorbis_info_psy *i){
  if(i){
    memset(i,0,sizeof(*i));
    _ogg_free(i);
  }
}

static void min_curve(float *c,
                       float *c2){
  int i;
  for(i=0;i<EHMER_MAX;i++)if(c2[i]<c[i])c[i]=c2[i];
}
static void max_curve(float *c,
                       float *c2){
  int i;
  for(i=0;i<EHMER_MAX;i++)if(c2[i]>c[i])c[i]=c2[i];
}

static void attenuate_curve(float *c,float att){
  int i;
  for(i=0;i<EHMER_MAX;i++)
    c[i]+=att;
}

static float ***setup_tone_curves(float curveatt_dB[P_BANDS],float binHz,int n,
                                  float center_boost, float center_decay_rate){
  int i,j,k,m;
  float ath[EHMER_MAX];
  float workc[P_BANDS][P_LEVELS][EHMER_MAX];
  float athc[P_LEVELS][EHMER_MAX];
  float *brute_buffer=alloca(n*sizeof(*brute_buffer));

  float ***ret=_ogg_malloc(sizeof(*ret)*P_BANDS);

  memset(workc,0,sizeof(workc));

  for(i=0;i<P_BANDS;i++){
    /* we add back in the ATH to avoid low level curves falling off to
       -infinity and unnecessarily cutting off high level curves in the
       curve limiting (last step). */

    /* A half-band's settings must be valid over the whole band, and
       it's better to mask too little than too much */
    int ath_offset=i*4;
    for(j=0;j<EHMER_MAX;j++){
      float min=999.;
      for(k=0;k<4;k++)
        if(j+k+ath_offset<MAX_ATH){
          if(min>ATH[j+k+ath_offset])min=ATH[j+k+ath_offset];
        }else{
          if(min>ATH[MAX_ATH-1])min=ATH[MAX_ATH-1];
        }
      ath[j]=min;
    }

    /* copy curves into working space, replicate the 50dB curve to 30
       and 40, replicate the 100dB curve to 110 */
    for(j=0;j<6;j++)
      memcpy(workc[i][j+2],tonemasks[i][j],EHMER_MAX*sizeof(*tonemasks[i][j]));
    memcpy(workc[i][0],tonemasks[i][0],EHMER_MAX*sizeof(*tonemasks[i][0]));
    memcpy(workc[i][1],tonemasks[i][0],EHMER_MAX*sizeof(*tonemasks[i][0]));

    /* apply centered curve boost/decay */
    for(j=0;j<P_LEVELS;j++){
      for(k=0;k<EHMER_MAX;k++){
        float adj=center_boost+abs(EHMER_OFFSET-k)*center_decay_rate;
        if(adj<0. && center_boost>0)adj=0.;
        if(adj>0. && center_boost<0)adj=0.;
        workc[i][j][k]+=adj;
      }
    }

    /* normalize curves so the driving amplitude is 0dB */
    /* make temp curves with the ATH overlayed */
    for(j=0;j<P_LEVELS;j++){
      attenuate_curve(workc[i][j],curveatt_dB[i]+100.-(j<2?2:j)*10.-P_LEVEL_0);
      memcpy(athc[j],ath,EHMER_MAX*sizeof(**athc));
      attenuate_curve(athc[j],+100.-j*10.f-P_LEVEL_0);
      max_curve(athc[j],workc[i][j]);
    }

    /* Now limit the louder curves.

       the idea is this: We don't know what the playback attenuation
       will be; 0dB SL moves every time the user twiddles the volume
       knob. So that means we have to use a single 'most pessimal' curve
       for all masking amplitudes, right?  Wrong.  The *loudest* sound
       can be in (we assume) a range of ...+100dB] SL.  However, sounds
       20dB down will be in a range ...+80], 40dB down is from ...+60],
       etc... */

    for(j=1;j<P_LEVELS;j++){
      min_curve(athc[j],athc[j-1]);
      min_curve(workc[i][j],athc[j]);
    }
  }

  for(i=0;i<P_BANDS;i++){
    int hi_curve,lo_curve,bin;
    ret[i]=_ogg_malloc(sizeof(**ret)*P_LEVELS);

    /* low frequency curves are measured with greater resolution than
       the MDCT/FFT will actually give us; we want the curve applied
       to the tone data to be pessimistic and thus apply the minimum
       masking possible for a given bin.  That means that a single bin
       could span more than one octave and that the curve will be a
       composite of multiple octaves.  It also may mean that a single
       bin may span > an eighth of an octave and that the eighth
       octave values may also be composited. */

    /* which octave curves will we be compositing? */
    bin=floor(fromOC(i*.5)/binHz);
    lo_curve=  ceil(toOC(bin*binHz+1)*2);
    hi_curve=  floor(toOC((bin+1)*binHz)*2);
    if(lo_curve>i)lo_curve=i;
    if(lo_curve<0)lo_curve=0;
    if(hi_curve>=P_BANDS)hi_curve=P_BANDS-1;

    for(m=0;m<P_LEVELS;m++){
      ret[i][m]=_ogg_malloc(sizeof(***ret)*(EHMER_MAX+2));

      for(j=0;j<n;j++)brute_buffer[j]=999.;

      /* render the curve into bins, then pull values back into curve.
         The point is that any inherent subsampling aliasing results in
         a safe minimum */
      for(k=lo_curve;k<=hi_curve;k++){
        int l=0;

        for(j=0;j<EHMER_MAX;j++){
          int lo_bin= fromOC(j*.125+k*.5-2.0625)/binHz;
          int hi_bin= fromOC(j*.125+k*.5-1.9375)/binHz+1;

          if(lo_bin<0)lo_bin=0;
          if(lo_bin>n)lo_bin=n;
          if(lo_bin<l)l=lo_bin;
          if(hi_bin<0)hi_bin=0;
          if(hi_bin>n)hi_bin=n;

          for(;l<hi_bin && l<n;l++)
            if(brute_buffer[l]>workc[k][m][j])
              brute_buffer[l]=workc[k][m][j];
        }

        for(;l<n;l++)
          if(brute_buffer[l]>workc[k][m][EHMER_MAX-1])
            brute_buffer[l]=workc[k][m][EHMER_MAX-1];

      }

      /* be equally paranoid about being valid up to next half ocatve */
      if(i+1<P_BANDS){
        int l=0;
        k=i+1;
        for(j=0;j<EHMER_MAX;j++){
          int lo_bin= fromOC(j*.125+i*.5-2.0625)/binHz;
          int hi_bin= fromOC(j*.125+i*.5-1.9375)/binHz+1;

          if(lo_bin<0)lo_bin=0;
          if(lo_bin>n)lo_bin=n;
          if(lo_bin<l)l=lo_bin;
          if(hi_bin<0)hi_bin=0;
          if(hi_bin>n)hi_bin=n;

          for(;l<hi_bin && l<n;l++)
            if(brute_buffer[l]>workc[k][m][j])
              brute_buffer[l]=workc[k][m][j];
        }

        for(;l<n;l++)
          if(brute_buffer[l]>workc[k][m][EHMER_MAX-1])
            brute_buffer[l]=workc[k][m][EHMER_MAX-1];

      }


      for(j=0;j<EHMER_MAX;j++){
        int bin=fromOC(j*.125+i*.5-2.)/binHz;
        if(bin<0){
          ret[i][m][j+2]=-999.;
        }else{
          if(bin>=n){
            ret[i][m][j+2]=-999.;
          }else{
            ret[i][m][j+2]=brute_buffer[bin];
          }
        }
      }

      /* add fenceposts */
      for(j=0;j<EHMER_OFFSET;j++)
        if(ret[i][m][j+2]>-200.f)break;
      ret[i][m][0]=j;

      for(j=EHMER_MAX-1;j>EHMER_OFFSET+1;j--)
        if(ret[i][m][j+2]>-200.f)
          break;
      ret[i][m][1]=j;

    }
  }

  return(ret);
}

void _vp_psy_init(vorbis_look_psy *p,vorbis_info_psy *vi,
                  vorbis_info_psy_global *gi,int n,long rate){
  long i,j,lo=-99,hi=0;
  long maxoc;
  memset(p,0,sizeof(*p));

  p->eighth_octave_lines=gi->eighth_octave_lines;
  p->shiftoc=rint(log(gi->eighth_octave_lines*8.f)/log(2.f))-1;

  p->firstoc=toOC(.25f*rate*.5/n)*(1<<(p->shiftoc+1))-gi->eighth_octave_lines;
  maxoc=toOC((n+.25f)*rate*.5/n)*(1<<(p->shiftoc+1))+.5f;
  p->total_octave_lines=maxoc-p->firstoc+1;
  p->ath=_ogg_malloc(n*sizeof(*p->ath));

  p->octave=_ogg_malloc(n*sizeof(*p->octave));
  p->bark=_ogg_malloc(n*sizeof(*p->bark));
  p->vi=vi;
  p->n=n;
  p->rate=rate;

  /* set up the lookups for a given blocksize and sample rate */

  for(i=0,j=0;i<MAX_ATH-1;i++){
    int endpos=rint(fromOC((i+1)*.125-2.)*2*n/rate);
    float base=ATH[i];
    if(j<endpos){
      float delta=(ATH[i+1]-base)/(endpos-j);
      for(;j<endpos && j<n;j++){
        p->ath[j]=base+100.;
        base+=delta;
      }
    }
  }

  for(i=0;i<n;i++){
    float bark=toBARK(rate/(2*n)*i);

    for(;lo+vi->noisewindowlomin<i &&
          toBARK(rate/(2*n)*lo)<(bark-vi->noisewindowlo);lo++);

    for(;hi<n && (hi<i+vi->noisewindowhimin ||
          toBARK(rate/(2*n)*hi)<(bark+vi->noisewindowhi));hi++);

    p->bark[i]=(lo<<16)+hi;

  }

  for(i=0;i<n;i++)
    p->octave[i]=toOC((i+.25f)*.5*rate/n)*(1<<(p->shiftoc+1))+.5f;

  p->tonecurves=setup_tone_curves(vi->toneatt,rate*.5/n,n,
                                  vi->tone_centerboost,vi->tone_decay);

  /* set up rolling noise median */
  p->noiseoffset=_ogg_malloc(P_NOISECURVES*sizeof(*p->noiseoffset));
  for(i=0;i<P_NOISECURVES;i++)
    p->noiseoffset[i]=_ogg_malloc(n*sizeof(**p->noiseoffset));

  for(i=0;i<n;i++){
    float halfoc=toOC((i+.5)*rate/(2.*n))*2.;
    int inthalfoc;
    float del;

    if(halfoc<0)halfoc=0;
    if(halfoc>=P_BANDS-1)halfoc=P_BANDS-1;
    inthalfoc=(int)halfoc;
    del=halfoc-inthalfoc;

    for(j=0;j<P_NOISECURVES;j++)
      p->noiseoffset[j][i]=
        p->vi->noiseoff[j][inthalfoc]*(1.-del) +
        p->vi->noiseoff[j][inthalfoc+1]*del;

  }
#if 0
  {
    static int ls=0;
    _analysis_output_always("noiseoff0",ls,p->noiseoffset[0],n,1,0,0);
    _analysis_output_always("noiseoff1",ls,p->noiseoffset[1],n,1,0,0);
    _analysis_output_always("noiseoff2",ls++,p->noiseoffset[2],n,1,0,0);
  }
#endif
}

void _vp_psy_clear(vorbis_look_psy *p){
  int i,j;
  if(p){
    if(p->ath)_ogg_free(p->ath);
    if(p->octave)_ogg_free(p->octave);
    if(p->bark)_ogg_free(p->bark);
    if(p->tonecurves){
      for(i=0;i<P_BANDS;i++){
        for(j=0;j<P_LEVELS;j++){
          _ogg_free(p->tonecurves[i][j]);
        }
        _ogg_free(p->tonecurves[i]);
      }
      _ogg_free(p->tonecurves);
    }
    if(p->noiseoffset){
      for(i=0;i<P_NOISECURVES;i++){
        _ogg_free(p->noiseoffset[i]);
      }
      _ogg_free(p->noiseoffset);
    }
    memset(p,0,sizeof(*p));
  }
}

/* octave/(8*eighth_octave_lines) x scale and dB y scale */
static void seed_curve(float *seed,
                       const float **curves,
                       float amp,
                       int oc, int n,
                       int linesper,float dBoffset){
  int i,post1;
  int seedptr;
  const float *posts,*curve;

  int choice=(int)((amp+dBoffset-P_LEVEL_0)*.1f);
  choice=max(choice,0);
  choice=min(choice,P_LEVELS-1);
  posts=curves[choice];
  curve=posts+2;
  post1=(int)posts[1];
  seedptr=oc+(posts[0]-EHMER_OFFSET)*linesper-(linesper>>1);

  for(i=posts[0];i<post1;i++){
    if(seedptr>0){
      float lin=amp+curve[i];
      if(seed[seedptr]<lin)seed[seedptr]=lin;
    }
    seedptr+=linesper;
    if(seedptr>=n)break;
  }
}

static void seed_loop(vorbis_look_psy *p,
                      const float ***curves,
                      const float *f,
                      const float *flr,
                      float *seed,
                      float specmax){
  vorbis_info_psy *vi=p->vi;
  long n=p->n,i;
  float dBoffset=vi->max_curve_dB-specmax;

  /* prime the working vector with peak values */

  for(i=0;i<n;i++){
    float max=f[i];
    long oc=p->octave[i];
    while(i+1<n && p->octave[i+1]==oc){
      i++;
      if(f[i]>max)max=f[i];
    }

    if(max+6.f>flr[i]){
      oc=oc>>p->shiftoc;

      if(oc>=P_BANDS)oc=P_BANDS-1;
      if(oc<0)oc=0;

      seed_curve(seed,
                 curves[oc],
                 max,
                 p->octave[i]-p->firstoc,
                 p->total_octave_lines,
                 p->eighth_octave_lines,
                 dBoffset);
    }
  }
}

static void seed_chase(float *seeds, int linesper, long n){
  long  *posstack=alloca(n*sizeof(*posstack));
  float *ampstack=alloca(n*sizeof(*ampstack));
  long   stack=0;
  long   pos=0;
  long   i;

  for(i=0;i<n;i++){
    if(stack<2){
      posstack[stack]=i;
      ampstack[stack++]=seeds[i];
    }else{
      while(1){
        if(seeds[i]<ampstack[stack-1]){
          posstack[stack]=i;
          ampstack[stack++]=seeds[i];
          break;
        }else{
          if(i<posstack[stack-1]+linesper){
            if(stack>1 && ampstack[stack-1]<=ampstack[stack-2] &&
               i<posstack[stack-2]+linesper){
              /* we completely overlap, making stack-1 irrelevant.  pop it */
              stack--;
              continue;
            }
          }
          posstack[stack]=i;
          ampstack[stack++]=seeds[i];
          break;

        }
      }
    }
  }

  /* the stack now contains only the positions that are relevant. Scan
     'em straight through */

  for(i=0;i<stack;i++){
    long endpos;
    if(i<stack-1 && ampstack[i+1]>ampstack[i]){
      endpos=posstack[i+1];
    }else{
      endpos=posstack[i]+linesper+1; /* +1 is important, else bin 0 is
                                        discarded in short frames */
    }
    if(endpos>n)endpos=n;
    for(;pos<endpos;pos++)
      seeds[pos]=ampstack[i];
  }

  /* there.  Linear time.  I now remember this was on a problem set I
     had in Grad Skool... I didn't solve it at the time ;-) */

}

/* bleaugh, this is more complicated than it needs to be */
/* #include <stdio.h> : included above */
static void max_seeds(vorbis_look_psy *p,
                      float *seed,
                      float *flr){
  long   n=p->total_octave_lines;
  int    linesper=p->eighth_octave_lines;
  long   linpos=0;
  long   pos;

  seed_chase(seed,linesper,n); /* for masking */

  pos=p->octave[0]-p->firstoc-(linesper>>1);

  while(linpos+1<p->n){
    float minV=seed[pos];
    long end=((p->octave[linpos]+p->octave[linpos+1])>>1)-p->firstoc;
    if(minV>p->vi->tone_abs_limit)minV=p->vi->tone_abs_limit;
    while(pos+1<=end){
      pos++;
      if((seed[pos]>NEGINF && seed[pos]<minV) || minV==NEGINF)
        minV=seed[pos];
    }

    end=pos+p->firstoc;
    for(;linpos<p->n && p->octave[linpos]<=end;linpos++)
      if(flr[linpos]<minV)flr[linpos]=minV;
  }

  {
    float minV=seed[p->total_octave_lines-1];
    for(;linpos<p->n;linpos++)
      if(flr[linpos]<minV)flr[linpos]=minV;
  }

}

static void bark_noise_hybridmp(int n,const long *b,
                                const float *f,
                                float *noise,
                                const float offset,
                                const int fixed){

  float *N=alloca((n+1)*sizeof(*N));
  float *X=alloca((n+1)*sizeof(*N));
  float *XX=alloca((n+1)*sizeof(*N));
  float *Y=alloca((n+1)*sizeof(*N));
  float *XY=alloca((n+1)*sizeof(*N));

  float tN, tX, tXX, tY, tXY;
  float fi;
  int i;

  int lo, hi;
  float R, A, B, D;

  tN = tX = tXX = tY = tXY = 0.f;
  for (i = 0, fi = 0.f; i < n; i++, fi += 1.f) {
    float w, x, y;

    x = fi;
    y = f[i] + offset;
    if (y < 1.f) y = 1.f;
    w = y * y;
    N[i] = tN;
    X[i] = tX;
    XX[i] = tXX;
    Y[i] = tY;
    XY[i] = tXY;
    tN += w;
    tX += w * x;
    tXX += w * x * x;
    tY += w * y;
    tXY += w * x * y;
  }
  N[i] = tN;
  X[i] = tX;
  XX[i] = tXX;
  Y[i] = tY;
  XY[i] = tXY;

  for (i = 0, fi = 0.f;; i++, fi += 1.f) {

    lo = b[i] >> 16;
    if( lo>=0 ) break;
    hi = b[i] & 0xffff;

    tN = N[hi] + N[-lo];
    tX = X[hi] - X[-lo];
    tXX = XX[hi] + XX[-lo];
    tY = Y[hi] + Y[-lo];
    tXY = XY[hi] - XY[-lo];

    A = tY * tXX - tX * tXY;
    B = tN * tXY - tX * tY;
    D = tN * tXX - tX * tX;
    R = (A + fi * B) / D;
    if (R < 0.f)
      R = 0.f;

    noise[i] = R - offset;
  }

  for ( ; hi < n; i++, fi += 1.f) {

    lo = b[i] >> 16;
    hi = b[i] & 0xffff;

    tN = N[hi] - N[lo];
    tX = X[hi] - X[lo];
    tXX = XX[hi] - XX[lo];
    tY = Y[hi] - Y[lo];
    tXY = XY[hi] - XY[lo];

    A = tY * tXX - tX * tXY;
    B = tN * tXY - tX * tY;
    D = tN * tXX - tX * tX;
    R = (A + fi * B) / D;
    if (R < 0.f) R = 0.f;

    noise[i] = R - offset;
  }
  for ( ; i < n; i++, fi += 1.f) {

    R = (A + fi * B) / D;
    if (R < 0.f) R = 0.f;

    noise[i] = R - offset;
  }

  if (fixed <= 0) return;

  for (i = 0, fi = 0.f; i < (fixed + 1) / 2; i++, fi += 1.f) {
    hi = i + fixed / 2;
    lo = hi - fixed;

    tN = N[hi] + N[-lo];
    tX = X[hi] - X[-lo];
    tXX = XX[hi] + XX[-lo];
    tY = Y[hi] + Y[-lo];
    tXY = XY[hi] - XY[-lo];


    A = tY * tXX - tX * tXY;
    B = tN * tXY - tX * tY;
    D = tN * tXX - tX * tX;
    R = (A + fi * B) / D;

    if (R > 0.f && R - offset < noise[i]) noise[i] = R - offset;
  }
  for ( ; hi < n; i++, fi += 1.f) {

    hi = i + fixed / 2;
    lo = hi - fixed;

    tN = N[hi] - N[lo];
    tX = X[hi] - X[lo];
    tXX = XX[hi] - XX[lo];
    tY = Y[hi] - Y[lo];
    tXY = XY[hi] - XY[lo];

    A = tY * tXX - tX * tXY;
    B = tN * tXY - tX * tY;
    D = tN * tXX - tX * tX;
    R = (A + fi * B) / D;

    if (R > 0.f && R - offset < noise[i]) noise[i] = R - offset;
  }
  for ( ; i < n; i++, fi += 1.f) {
    R = (A + fi * B) / D;
    if (R > 0.f && R - offset < noise[i]) noise[i] = R - offset;
  }
}

extern float FLOOR1_fromdB_INV_LOOKUP[256];
#if 0 /* the library definition; the retail copy is bound instead */
static float FLOOR1_fromdB_INV_LOOKUP[256]={
  0.F, 8.81683e+06F, 8.27882e+06F, 7.77365e+06F,
  7.29930e+06F, 6.85389e+06F, 6.43567e+06F, 6.04296e+06F,
  5.67422e+06F, 5.32798e+06F, 5.00286e+06F, 4.69759e+06F,
  4.41094e+06F, 4.14178e+06F, 3.88905e+06F, 3.65174e+06F,
  3.42891e+06F, 3.21968e+06F, 3.02321e+06F, 2.83873e+06F,
  2.66551e+06F, 2.50286e+06F, 2.35014e+06F, 2.20673e+06F,
  2.07208e+06F, 1.94564e+06F, 1.82692e+06F, 1.71544e+06F,
  1.61076e+06F, 1.51247e+06F, 1.42018e+06F, 1.33352e+06F,
  1.25215e+06F, 1.17574e+06F, 1.10400e+06F, 1.03663e+06F,
  973377.F, 913981.F, 858210.F, 805842.F,
  756669.F, 710497.F, 667142.F, 626433.F,
  588208.F, 552316.F, 518613.F, 486967.F,
  457252.F, 429351.F, 403152.F, 378551.F,
  355452.F, 333762.F, 313396.F, 294273.F,
  276316.F, 259455.F, 243623.F, 228757.F,
  214798.F, 201691.F, 189384.F, 177828.F,
  166977.F, 156788.F, 147221.F, 138237.F,
  129802.F, 121881.F, 114444.F, 107461.F,
  100903.F, 94746.3F, 88964.9F, 83536.2F,
  78438.8F, 73652.5F, 69158.2F, 64938.1F,
  60975.6F, 57254.9F, 53761.2F, 50480.6F,
  47400.3F, 44507.9F, 41792.0F, 39241.9F,
  36847.3F, 34598.9F, 32487.7F, 30505.3F,
  28643.8F, 26896.0F, 25254.8F, 23713.7F,
  22266.7F, 20908.0F, 19632.2F, 18434.2F,
  17309.4F, 16253.1F, 15261.4F, 14330.1F,
  13455.7F, 12634.6F, 11863.7F, 11139.7F,
  10460.0F, 9821.72F, 9222.39F, 8659.64F,
  8131.23F, 7635.06F, 7169.17F, 6731.70F,
  6320.93F, 5935.23F, 5573.06F, 5232.99F,
  4913.67F, 4613.84F, 4332.30F, 4067.94F,
  3819.72F, 3586.64F, 3367.78F, 3162.28F,
  2969.31F, 2788.13F, 2617.99F, 2458.24F,
  2308.24F, 2167.39F, 2035.14F, 1910.95F,
  1794.35F, 1684.85F, 1582.04F, 1485.51F,
  1394.86F, 1309.75F, 1229.83F, 1154.78F,
  1084.32F, 1018.15F, 956.024F, 897.687F,
  842.910F, 791.475F, 743.179F, 697.830F,
  655.249F, 615.265F, 577.722F, 542.469F,
  509.367F, 478.286F, 449.101F, 421.696F,
  395.964F, 371.803F, 349.115F, 327.812F,
  307.809F, 289.026F, 271.390F, 254.830F,
  239.280F, 224.679F, 210.969F, 198.096F,
  186.008F, 174.658F, 164.000F, 153.993F,
  144.596F, 135.773F, 127.488F, 119.708F,
  112.404F, 105.545F, 99.1046F, 93.0572F,
  87.3788F, 82.0469F, 77.0404F, 72.3394F,
  67.9252F, 63.7804F, 59.8885F, 56.2341F,
  52.8027F, 49.5807F, 46.5553F, 43.7144F,
  41.0470F, 38.5423F, 36.1904F, 33.9821F,
  31.9085F, 29.9614F, 28.1332F, 26.4165F,
  24.8045F, 23.2910F, 21.8697F, 20.5352F,
  19.2822F, 18.1056F, 17.0008F, 15.9634F,
  14.9893F, 14.0746F, 13.2158F, 12.4094F,
  11.6522F, 10.9411F, 10.2735F, 9.64662F,
  9.05798F, 8.50526F, 7.98626F, 7.49894F,
  7.04135F, 6.61169F, 6.20824F, 5.82941F,
  5.47370F, 5.13970F, 4.82607F, 4.53158F,
  4.25507F, 3.99542F, 3.75162F, 3.52269F,
  3.30774F, 3.10590F, 2.91638F, 2.73842F,
  2.57132F, 2.41442F, 2.26709F, 2.12875F,
  1.99885F, 1.87688F, 1.76236F, 1.65482F,
  1.55384F, 1.45902F, 1.36999F, 1.28640F,
  1.20790F, 1.13419F, 1.06499F, 1.F
};
#endif

void _vp_remove_floor(vorbis_look_psy *p,
                      float *mdct,
                      int *codedflr,
                      float *residue,
                      int sliding_lowpass){

  int i,n=p->n;

  if(sliding_lowpass>n)sliding_lowpass=n;

  for(i=0;i<sliding_lowpass;i++){
    residue[i]=
      mdct[i]*FLOOR1_fromdB_INV_LOOKUP[codedflr[i]];
  }

  for(;i<n;i++)
    residue[i]=0.;
}

void _vp_noisemask(vorbis_look_psy *p,
                   float *logmdct,
                   float *logmask){

  int i,n=p->n;
  float *work=alloca(n*sizeof(*work));

  bark_noise_hybridmp(n,p->bark,logmdct,logmask,
                      140.,-1);

  for(i=0;i<n;i++)work[i]=logmdct[i]-logmask[i];

  bark_noise_hybridmp(n,p->bark,work,logmask,0.,
                      p->vi->noisewindowfixed);

  for(i=0;i<n;i++)work[i]=logmdct[i]-work[i];

#if 0
  {
    static int seq=0;

    float work2[n];
    for(i=0;i<n;i++){
      work2[i]=logmask[i]+work[i];
    }

    if(seq&1)
      _analysis_output("medianR",seq/2,work,n,1,0,0);
    else
      _analysis_output("medianL",seq/2,work,n,1,0,0);

    if(seq&1)
      _analysis_output("envelopeR",seq/2,work2,n,1,0,0);
    else
      _analysis_output("enveloperL",seq/2,work2,n,1,0,0);
    seq++;
  }
#endif

  for(i=0;i<n;i++){
    int dB=logmask[i]+.5;
    if(dB>=NOISE_COMPAND_LEVELS)dB=NOISE_COMPAND_LEVELS-1;
    logmask[i]= work[i]+p->vi->noisecompand[dB];
  }

}

void _vp_tonemask(vorbis_look_psy *p,
                  float *logfft,
                  float *logmask,
                  float global_specmax,
                  float local_specmax){

  int i,n=p->n;

  float *seed=alloca(sizeof(*seed)*p->total_octave_lines);
  float att=local_specmax+p->vi->ath_adjatt;
  for(i=0;i<p->total_octave_lines;i++)seed[i]=NEGINF;

  /* set the ATH (floating below localmax, not global max by a
     specified att) */
  if(att<p->vi->ath_maxatt)att=p->vi->ath_maxatt;

  for(i=0;i<n;i++)
    logmask[i]=p->ath[i]+att;

  /* tone masking */
  seed_loop(p,(const float ***)p->tonecurves,logfft,logmask,seed,global_specmax);
  max_seeds(p,seed,logmask);

}

void _vp_offset_and_mix(vorbis_look_psy *p,
                        float *noise,
                        float *tone,
                        int offset_select,
                        float *logmask){
  int i,n=p->n;
  float toneatt=p->vi->tone_masteratt[offset_select];

  for(i=0;i<n;i++){
    float val= noise[i]+p->noiseoffset[offset_select][i];
    if(val>p->vi->noisemaxsupp)val=p->vi->noisemaxsupp;
    logmask[i]=max(val,tone[i]+toneatt);
  }
}

float _vp_ampmax_decay(float amp,vorbis_dsp_state *vd){
  vorbis_info *vi=vd->vi;
  codec_setup_info *ci=vi->codec_setup;
  vorbis_info_psy_global *gi=&ci->psy_g_param;

  int n=ci->blocksizes[vd->W]/2;
  float secs=(float)n/vi->rate;

  amp+=secs*gi->ampmax_att_per_sec;
  if(amp<-9999)amp=-9999;
  return(amp);
}

static void couple_lossless(float A, float B,
                            float *qA, float *qB){
  int test1=fabs(*qA)>fabs(*qB);
  test1-= fabs(*qA)<fabs(*qB);

  if(!test1)test1=((fabs(A)>fabs(B))<<1)-1;
  if(test1==1){
    *qB=(*qA>0.f?*qA-*qB:*qB-*qA);
  }else{
    float temp=*qB;
    *qB=(*qB>0.f?*qA-*qB:*qB-*qA);
    *qA=temp;
  }

  if(*qB>fabs(*qA)*1.9999f){
    *qB= -fabs(*qA)*2.f;
    *qA= -*qA;
  }
}

extern float hypot_lookup[32];
#if 0 /* the library definition; the retail copy is bound instead */
static float hypot_lookup[32]={
  -0.009935, -0.011245, -0.012726, -0.014397,
  -0.016282, -0.018407, -0.020800, -0.023494,
  -0.026522, -0.029923, -0.033737, -0.038010,
  -0.042787, -0.048121, -0.054064, -0.060671,
  -0.068000, -0.076109, -0.085054, -0.094892,
  -0.105675, -0.117451, -0.130260, -0.144134,
  -0.159093, -0.175146, -0.192286, -0.210490,
  -0.229718, -0.249913, -0.271001, -0.292893};
#endif

static void precomputed_couple_point(float premag,
                                     int floorA,int floorB,
                                     float *mag, float *ang){

  int test=(floorA>floorB)-1;
  int offset=31-abs(floorA-floorB);
  float floormag=hypot_lookup[((offset<0)-1)&offset]+1.f;

  floormag*=FLOOR1_fromdB_INV_LOOKUP[(floorB&test)|(floorA&(~test))];

  *mag=premag*floormag;
  *ang=0.f;
}

/* just like below, this is currently set up to only do
   single-step-depth coupling.  Otherwise, we'd have to do more
   copying (which will be inevitable later) */

/* doing the real circular magnitude calculation is audibly superior
   to (A+B)/sqrt(2) */
static float dipole_hypot(float a, float b){
  if(a>0.){
    if(b>0.)return sqrt(a*a+b*b);
    if(a>-b)return sqrt(a*a-b*b);
    return -sqrt(b*b-a*a);
  }
  if(b<0.)return -sqrt(a*a+b*b);
  if(-a>b)return -sqrt(a*a-b*b);
  return sqrt(b*b-a*a);
}
static float round_hypot(float a, float b){
  if(a>0.){
    if(b>0.)return sqrt(a*a+b*b);
    if(a>-b)return sqrt(a*a+b*b);
    return -sqrt(b*b+a*a);
  }
  if(b<0.)return -sqrt(a*a+b*b);
  if(-a>b)return -sqrt(a*a+b*b);
  return sqrt(b*b+a*a);
}

/* revert to round hypot for now */
float **_vp_quantize_couple_memo(vorbis_block *vb,
                                 vorbis_info_psy_global *g,
                                 vorbis_look_psy *p,
                                 vorbis_info_mapping0 *vi,
                                 float **mdct){

  int i,j,n=p->n;
  float **ret=_vorbis_block_alloc(vb,vi->coupling_steps*sizeof(*ret));
  int limit=g->coupling_pointlimit[p->vi->blockflag][PACKETBLOBS/2];

  for(i=0;i<vi->coupling_steps;i++){
    float *mdctM=mdct[vi->coupling_mag[i]];
    float *mdctA=mdct[vi->coupling_ang[i]];
    ret[i]=_vorbis_block_alloc(vb,n*sizeof(**ret));
    for(j=0;j<limit;j++)
      ret[i][j]=dipole_hypot(mdctM[j],mdctA[j]);
    for(;j<n;j++)
      ret[i][j]=round_hypot(mdctM[j],mdctA[j]);
  }

  return(ret);
}

/* this is for per-channel noise normalization */
static int apsort(const void *a, const void *b){
  if(fabs(**(float **)a)>fabs(**(float **)b))return -1;
  return 1;
}

int **_vp_quantize_couple_sort(vorbis_block *vb,
                               vorbis_look_psy *p,
                               vorbis_info_mapping0 *vi,
                               float **mags){


  if(p->vi->normal_point_p){
    int i,j,k,n=p->n;
    int **ret=_vorbis_block_alloc(vb,vi->coupling_steps*sizeof(*ret));
    int partition=p->vi->normal_partition;
    float **work=alloca(sizeof(*work)*partition);

    for(i=0;i<vi->coupling_steps;i++){
      ret[i]=_vorbis_block_alloc(vb,n*sizeof(**ret));

      for(j=0;j<n;j+=partition){
        for(k=0;k<partition;k++)work[k]=mags[i]+k+j;
        qsort(work,partition,sizeof(*work),apsort);
        for(k=0;k<partition;k++)ret[i][k+j]=work[k]-mags[i];
      }
    }
    return(ret);
  }
  return(NULL);
}

void _vp_noise_normalize_sort(vorbis_look_psy *p,
                              float *magnitudes,int *sortedindex){
  int i,j,n=p->n;
  vorbis_info_psy *vi=p->vi;
  int partition=vi->normal_partition;
  float **work=alloca(sizeof(*work)*partition);
  int start=vi->normal_start;

  for(j=start;j<n;j+=partition){
    if(j+partition>n)partition=n-j;
    for(i=0;i<partition;i++)work[i]=magnitudes+i+j;
    qsort(work,partition,sizeof(*work),apsort);
    for(i=0;i<partition;i++){
      sortedindex[i+j-start]=work[i]-magnitudes;
    }
  }
}

void _vp_noise_normalize(vorbis_look_psy *p,
                         float *in,float *out,int *sortedindex){
  int flag=0,i,j=0,n=p->n;
  vorbis_info_psy *vi=p->vi;
  int partition=vi->normal_partition;
  int start=vi->normal_start;

  if(start>n)start=n;

  if(vi->normal_channel_p){
    for(;j<start;j++)
      out[j]=rint(in[j]);

    for(;j+partition<=n;j+=partition){
      float acc=0.;
      int k;

      for(i=j;i<j+partition;i++)
        acc+=in[i]*in[i];

      for(i=0;i<partition;i++){
        k=sortedindex[i+j-start];

        if(in[k]*in[k]>=.25f){
          out[k]=rint(in[k]);
          acc-=in[k]*in[k];
          flag=1;
        }else{
          if(acc<vi->normal_thresh)break;
          out[k]=unitnorm(in[k]);
          acc-=1.;
        }
      }

      for(;i<partition;i++){
        k=sortedindex[i+j-start];
        out[k]=0.;
      }
    }
  }

  for(;j<n;j++)
    out[j]=rint(in[j]);

}

void _vp_couple(int blobno,
                vorbis_info_psy_global *g,
                vorbis_look_psy *p,
                vorbis_info_mapping0 *vi,
                float **res,
                float **mag_memo,
                int   **mag_sort,
                int   **ifloor,
                int   *nonzero,
                int  sliding_lowpass){

  int i,j,k,n=p->n;

  /* perform any requested channel coupling */
  /* point stereo can only be used in a first stage (in this encoder)
     because of the dependency on floor lookups */
  for(i=0;i<vi->coupling_steps;i++){

    /* once we're doing multistage coupling in which a channel goes
       through more than one coupling step, the floor vector
       magnitudes will also have to be recalculated an propogated
       along with PCM.  Right now, we're not (that will wait until 5.1
       most likely), so the code isn't here yet. The memory management
       here is all assuming single depth couplings anyway. */

    /* make sure coupling a zero and a nonzero channel results in two
       nonzero channels. */
    if(nonzero[vi->coupling_mag[i]] ||
       nonzero[vi->coupling_ang[i]]){


      float *rM=res[vi->coupling_mag[i]];
      float *rA=res[vi->coupling_ang[i]];
      float *qM=rM+n;
      float *qA=rA+n;
      int *floorM=ifloor[vi->coupling_mag[i]];
      int *floorA=ifloor[vi->coupling_ang[i]];
      float prepoint=stereo_threshholds[g->coupling_prepointamp[blobno]];
      float postpoint=stereo_threshholds[g->coupling_postpointamp[blobno]];
      int partition=(p->vi->normal_point_p?p->vi->normal_partition:p->n);
      int limit=g->coupling_pointlimit[p->vi->blockflag][blobno];
      int pointlimit=limit;

      nonzero[vi->coupling_mag[i]]=1;
      nonzero[vi->coupling_ang[i]]=1;

      for(j=0;j<p->n;j+=partition){
        float acc=0.f;

        for(k=0;k<partition;k++){
          int l=k+j;

          if(l<sliding_lowpass){
            if((l>=limit && fabs(rM[l])<postpoint && fabs(rA[l])<postpoint) ||
               (fabs(rM[l])<prepoint && fabs(rA[l])<prepoint)){


              precomputed_couple_point(mag_memo[i][l],
                                       floorM[l],floorA[l],
                                       qM+l,qA+l);

              if(rint(qM[l])==0.f)acc+=qM[l]*qM[l];
            }else{
              couple_lossless(rM[l],rA[l],qM+l,qA+l);
            }
          }else{
            qM[l]=0.;
            qA[l]=0.;
          }
        }

        if(p->vi->normal_point_p){
          for(k=0;k<partition && acc>=p->vi->normal_thresh;k++){
            int l=mag_sort[i][j+k];
            if(l<sliding_lowpass && l>=pointlimit && rint(qM[l])==0.f){
              qM[l]=unitnorm(qM[l]);
              acc-=1.f;
            }
          }
        }
      }
    }
  }
}
