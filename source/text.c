#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <3ds.h>
#include "text.h"
// #include "font_bin.h"

#include "font.h"

// Unused. I think.
// const u8* font = font_bin;

// @chaoskagami - It's open source, so yes it is meant to be readable.

// Mappings from original;
//   cd => char_desc
//   cy  => char_y
//   cyo => char_y_off
//   ch  => char_h

// Blits a single character, pixel-by-pixel to the framebuffer. Or so it seems.
// Why was there even a need to obfuscate this...? It's not even an exploit,
// nor even anything patented.

int drawCharacter(u8* fb, font_s* font, char c, s16 x, s16 y, u16 w, u16 h)
{
	charDesc_s* char_desc = &font->desc[(int)c];

	// Do we have data attached?
	if(!char_desc->data)
		return 0; // No. Can't draw it, return.

	x += char_desc->xo;
	y += font->height - char_desc->yo - char_desc->h;

	if( x < 0 ||
		x + char_desc->w >= w ||
		y < -(char_desc->h) ||
		y >= h + char_desc->h
	)
		return char_desc->xa;

	u8* charData = char_desc->data;

	int i, j;

	s16 char_y     = y;
	s16 char_h     = char_desc->h;
	s16 char_y_off = 0;

	if( y < 0 ) {
		char_y = 0;
		char_y_off = -y;
		char_h = char_desc->h - char_y_off;
	} else if( y + char_h > h )
		char_h = h - y;

	fb += (x * h + char_y) * 3;

	const u8 pix_r = font->color[0],
	         pix_g = font->color[1],
	         pix_b = font->color[2];

	for(i = 0; i < char_desc->w; i++) {
		charData += char_y_off;
		for(j = 0; j < char_h; j++)
		{
			u8 v = *(charData++);
			if(v)
			{
				fb[0] = (fb[0] * (0xFF - v) + (pix_b * v)) >> 8;
				fb[1] = (fb[1] * (0xFF - v) + (pix_g * v)) >> 8;
				fb[2] = (fb[2] * (0xFF - v) + (pix_r * v)) >> 8;
			}
			fb += 3;
		}
		charData += (char_desc->h - (char_y_off + char_h));
		fb += (h - char_h) * 3;
	}

	return char_desc->xa;
}

int getStringLength(font_s* f, char* str)
{
	if(!f) f = &fontDefault;

	if(!str) return 0;
	int ret;

	for(ret=0; *str; ret += f->desc[(int)*str++].xa);

	return ret;
}

void drawString(u8* fb, font_s* f, char* str, s16 x, s16 y, u16 w, u16 h)
{
	drawStringN(fb, f, str, strlen(str), x, y, w, h);
}

void drawStringN(u8* fb, font_s* f, char* str, u16 length, s16 x, s16 y, u16 w, u16 h)
{
	if(!f || !fb || !str) return;
	int k;
	int dx=0, dy=0;

	k = strlen(str);

	if (k < length) length=k;

	for(k = 0;k < length; k++)
	{
		dx += drawCharacter(fb, f, str[k], x + dx, y + dy, w, h);
		if(str[k] == '\n') {
			dx=0;
			dy-=8;
		}
	}
}
