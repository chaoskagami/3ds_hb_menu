#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <3ds.h>

#define WATERBORDERCOLOR (u8[]){100, 100, 100}
#define WATERCOLOR (u8[]){60, 60, 60}

#define BEERBORDERCOLOR (u8[]){240, 240, 240}
#define BEERCOLOR (u8[]){188, 157, 75}

#define BGCOLOR (u8[]){16, 16, 16}

#define BUBBLE_COUNT 25

typedef struct
{
	s32 x, y;
	u8 fade;
}bubble_t;

void initBackground(void);
void updateBackground(void);
void drawBackground(u8 bgColor[3], u8 waterBorderColor[3], u8 waterColor[3]);

#endif
