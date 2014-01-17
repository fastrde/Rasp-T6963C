//
// This is using the real screen size to compute various coordinates
//

#include <string.h>
#include "lcd_controller.h" 

// Compute the size of the screen
	int pixelX;
	int pixelY;
	
	int fontSize; // 0=6x8   1=8x8

	int BASE_TEXT;
	int BASE_GRAPHIC;
	int TEXT_SIZE;
	int GRAPHIC_SIZE;
	
	int cols,rows;
	
// Computes the screen characteristics and choose a memory	
void LCD_screen_compute(int pX, int pY, int font) {
	pixelX = pX;
	pixelY = pY;
	fontSize = font;
	
	// Raw computation
	int fontX = fontSize ? 8 : 6;
	int fontY = 8;
	cols = pixelX / fontX;          // 1E      28
	rows = pixelY / fontY;

	TEXT_SIZE = cols * rows;                     // 1E0       280
	GRAPHIC_SIZE = cols * rows * fontY;          // F00      1400 
	
	BASE_TEXT = 0;
	BASE_GRAPHIC = TEXT_SIZE;
}

void LCD_screen_init(int pX, int pY, int font) {
	LCD_screen_compute(pX, pY, font);
	LCD_init(BASE_TEXT,BASE_GRAPHIC,fontSize);
}

short LCD_getRows() { return (short)rows; }
short LCD_getCols() { return (short)cols; }
int LCD_getBaseText() { return BASE_TEXT; }
int LCD_getBaseGraphic() { return BASE_GRAPHIC; }
int LCD_getTextScreenSize() { return TEXT_SIZE; }
int LCD_getGraphicScreenSize() { return GRAPHIC_SIZE; }


void lprintln(char *text) {  
  LCD_auto_write_start();
  int len = strlen(text);
  while (*text != 0) {
	LCD_auto_write( *text - 0x20 );
	text++;
  }
  len %= cols;
  while (len++<cols) {
	LCD_auto_write( 0 );
  }
  LCD_auto_write_stop();
}