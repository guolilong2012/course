/* frame.h */
#ifndef _FRAME_H_
#define _FRAME_H_

#define FRAME_SUPPORT_JPEG
#define FRAME_SUPPORT_FONT
#define FRAME_SUPPORT_MOUSE
#define FRAME_SUPPORT_BMP

////////////////////////////////////////////////////////////////////////////
typedef unsigned char  u8_t;
typedef unsigned short u16_t;
typedef unsigned int   u32_t;

typedef struct 
{
	int w;				     /* width */
	int h;				     /* high */
	int bpp;				   /* bits per pixel */
	u8_t *fbmem;
}fb_info;

////////////////////////////////////////////////////////////////////////////
/* initial framebuffer */
extern int init_fb(fb_info *fb_inf);

/* drawing pixel */
extern int fb_pixel(fb_info fb_inf, int x, int y, u32_t color);

/* draw a color line, the slope is single */
extern int fb_draw_row(const fb_info fb_inf, int x, int y, int len, u32_t color);

/* draw a color slash line, the slope is change */
extern int fb_draw_slash_row(const fb_info fb_inf, int x, int y, int len, int slope, u32_t color);

/* draw a color circle */
extern int fb_draw_circle(const fb_info fb_inf, int x, int y, int len, u32_t color);

/* draw a color empty circle */
extern int fb_draw_empty_circle(const fb_info fb_inf, int x, int y, int len, int c_width, u32_t color);

/* draw a color oval circle */
extern int fb_draw_oval_circle(const fb_info fb_inf, int x, int y, int a_len, int b_len, u32_t color);

/* draw a color empty oval circle */
extern int fb_draw_empty_oval_circle(const fb_info fb_inf, int x, int y, int a_len, int b_len, int c_width, u32_t color);

/* draw a color squarearea */
extern int fb_draw_squarearea(const fb_info fb_inf, int x, int y, int x_len, int y_len, u32_t color);

/* draw a empty square */
extern int fb_draw_empty_square(const fb_info fb_inf, int x, int y, int x_len, int y_len, int s_width, u32_t color);

/* draw a star */
extern int fb_draw_star(const fb_info fb_inf, int x, int y, int len, u32_t color);

#ifdef FRAME_SUPPORT_FONT
////////////////////////////////////////////////////////////////////////////
/* init font library */
extern int init_ft (const char *file, int size);

/* display string */
extern int display_string (const char * buf, int x, int y, fb_info fb_inf, u32_t color);

#endif    /* FRAME_SUPPORT_FONT */

#ifdef FRAME_SUPPORT_MOUSE
////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	int x;
	int y;
	int button;
}mouse_event_t;

////////////////////////////////////////////////////////////////////////////
/* open mouse */
extern int mouse_open(char *device_name, int *fd);
/* parse mouse */
extern int mouse_parse(const u8_t *buf, mouse_event_t* mevent);

/* restore cursor */
extern int fb_restore_cursor(fb_info fb_inf, int x, int y);
/* save cursor */
extern int fb_save_cursor (fb_info fb_inf,int x,int y);
/* draw cursor */
extern int fb_draw_cursor(fb_info fb_inf, int x, int y);

#endif  /* FRAME_SUPPORT_MOUSE */


#ifdef FRAME_SUPPORT_JPEG
////////////////////////////////////////////////////////////////////////////
/* decode jpeg */
extern unsigned char *decode_jpeg (const char *filename, fb_info *jpeg_inf);
/* rgb888 to argb8888 */
extern u32_t * rgb24to32(u8_t *buf24, fb_info jpeg_inf);
/* scale24 */
u8_t * scale24(u8_t *buf24, fb_info new_inf, fb_info jpeg_inf);

/* display jpeg */
extern int display_jpeg(char *filename, fb_info fb_inf);
/* display jpeg */
extern int display_jpeg_shutter(char *filename, fb_info fb_inf);

extern int disp(char *filename, fb_info fb_inf);

#endif  /* FRAME_SUPPORT_JPEG */

#ifdef FRAME_SUPPORT_BMP
////////////////////////////////////////////////////////////////////////////
/* display bmp */
extern void display_bmp(const fb_info fb_inf, const char *bmpname);

#endif  /* FRAME_SUPPORT_BMP */

extern void display_clock(void);

#endif /* _FRAME_H_ */
