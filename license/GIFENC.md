GIF encoder
===========

This is a small C library that can be used to create GIF animations.

Features
--------

  * user-defined palette of any depth from 1 up to 8
  * each frame has its own (user-specified) delay time
  * flexible looping options: no loop, N repetitions, infinite loop
  * optional transparent background
  * GIF size optimization: only stores frame differences
  * memory efficient: saves frames to file as soon as possible
  * small and portable: less than 300 lines of C99
  * public domain


Limitations
-----------

  * no frame-local palettes (incompatible with size optimization)
  * no interlacing (bad for compression, useless for animations)


Documentation
-------------

There   are  only   three  functions   declared  in   "gifenc.h":  ge_new_gif(),
ge_add_frame() and ge_close_gif().

The  ge_new_gif() function  receives GIF  global  options and  returns a  ge_GIF
handler:

    ge_GIF *ge_new_gif(
        const char *fname,                  /* GIF file name */
        uint16_t width, uint16_t height,    /* frame size */
        uint8_t *palette, int depth,        /* color table */
        int bgindex,                        /* transparent color */
        int loop                            /* looping information */
    );

The `palette` parameter  must point to an  array of color data. Each  entry is a
24-bits RGB color, stored as three contiguous  bytes: the first is the red value
(0-255), then green, then blue. Entries are stored in a contiguous byte array.

The  `depth` parameter  specifies  how  many colors  are  present  in the  given
palette. The number of color entries must be 2 ^ depth, where 1 <= depth <= 8.

Example `palette` and `depth` values:

    uint8_t palette[] = {
        0x00, 0x00, 0x00,   /* entry 0: black */
        0xFF, 0xFF, 0xFF,   /* entry 1: white */
        0xFF, 0x00, 0x00,   /* entry 2: red */
        0x00, 0x00, 0xFF,   /* entry 3: blue */
    };
    int depth = 2;          /* palette has 1 << 2 (i.e. 4) entries */

If `palette` is NULL,  entries are taken from a default table  of 256 colors. If
`depth` < 8,  the default table will  be truncated to the  appropriate size. The
default table is composed  of the 16 standard VGA colors,  plus the 216 web-safe
colors (all combinations of  RGB with only 6 valid values  per channel), plus 24
grey colors equally spaced between black and white, excluding both.

If `depth` < 0 and `palette` is not NULL, then the default table with 2 ^ -depth
colors is used and it is stored in the array at the `palette` address.

The `bgindex`  parameter specifies the  color number  to be used  as transparent
background. If `bgindex` < 0, then transparency is disabled.

If the `loop` parameter is zero, the resulting GIF will loop forever. If it is a
positive number, the  animation will  be played that number  of times. If `loop`
is negative,  no looping  information is stored  in the GIF  file (for  most GIF
viewers, this is equivalent to `loop` == 1, i.e., "play once").

The  ge_add_frame() function  reads  pixel  data from  a  buffer  and saves  the
resulting frame to the file associated with the given ge_GIF handler:

    void ge_add_frame(ge_GIF *gif, uint16_t delay);

The `delay` parameter  specifies how long the frame will  be shown, in hundreths
of a second. For example, `delay` ==  100 means "show this frame for one second"
and `delay` == 25  means "show this frame for a quarter of  a second". Note that
short delays may not be supported by  some GIF viewers: it's recommended to keep
a minimum of `delay` == 6. If `delay` == 0, no delay information  will be stored
for the frame. This can be used when creating still (single-frame) GIF images.

Pixel data is read from `gif->frame`, which points to a memory block like this:

    uint8_t _frame_[gif->width * gif->height];

Note that,  iif transparency  is disabled, the  address of  `gif->frame` changes
between calls to ge_add_frame() (*). For this reason, each frame must be written
in its entirety to  the current address, even if one only wants  to change a few
pixels from the last frame. The encoder will automatically detect the difference
between two consecutive frames in order to minimize the size of the output. This
optimization is not applied when `gif->bgindex` >= 0, in which case it's safe to
reuse `gif->frame`'s  address and content.  Transparent GIFs are  still slightly
optimized by encoding only the rectangular region containing all opaque pixels.

Each byte in the frame buffer represents a  pixel. The value of each pixel is an
index to a palette entry. For instance, given the example  palette above, we can
create a frame displaying a red-on-black "F" letter like this:

    uint8_t pixels[] = {
        2, 2, 2, 2,
        2, 0, 0, 0,
        2, 0, 0, 0,
        2, 2, 2, 0,
        2, 0, 0, 0,
        2, 0, 0, 0,
        2, 0, 0, 0
    };
    ge_GIF *gif = ge_new_gif("F.gif", 4, 7, palette, depth, -1);
    memcpy(gif->frame, pixels, sizeof(pixels));
    ge_add_frame(gif, 0);
    ge_close_gif(gif);

The function  ge_close_gif() finishes writting  GIF data to the  file associated
with the  given ge_GIF handler and  does memory clean-up. This  function must be
called once after all desired frames have been added, in order to correctly save
the GIF  file. After calling  this function, the  ge_GIF handler cannot  be used
anymore.

    void ge_close_gif(ge_GIF* gif);

(*) The  encoder keeps two frame  buffers internally, in order  to implement the
size  optimization. The  address of  `gif->frame` alternates  between those  two
buffers after each call to ge_add_frame().


Example
-------

See the file "example.c". It can be tested like this:

$ cc -o example gifenc.c example.c
$ ./example

That should create an animated GIF named "example.gif".


Copying
-------

All of the source code and documentation for gifenc is released into the
public domain and provided without warranty of any kind.