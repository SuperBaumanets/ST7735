#ifndef ST7735_H_
#define ST7735_H_

//Includes
//=============================================================================================================================
//#include "stdbool.h"
#include "stm32f4xx_hal.h"
//=============================================================================================================================


//Declarations and definitions
//=============================================================================================================================
#define ST7735_COLOR_RED                                                0xF800
#define ST7735_COLOR_GREEN                                              0x07E0
#define ST7735_COLOR_BLUE                                               0x001F
#define ST7735_COLOR_YELLOW                                             0xFFE0
#define ST7735_COLOR_WHITE                                              0xFFFF
#define ST7735_COLOR_BLACK                                              0x0000
#define ST7735_COLOR_ORANGE                                             0xFA20


#define ST7735_RESET_PORT                                               (GPIOD)
#define ST7735_RESET_PIN                                                (GPIO_PIN_2)

#define ST7735_CS_PORT                                                  (GPIOD)
#define ST7735_CS_PIN                                                   (GPIO_PIN_1)

#define ST7735_DC_PORT                                                  (GPIOD)
#define ST7735_DC_PIN                                                   (GPIO_PIN_3)


#define ST7735_WIDTH 																										128
#define ST7735_HEIGHT 																									160


//System function command
#define ST7735_NOP                                                      0x00 // No operation
#define ST7735_SWRESET                                                  0x01 // Software reset
#define ST7735_RDDID                                                    0x04 // Read display id
#define ST7735_RDDST                                                    0x09 // Read display status

#define ST7735_SLPIN                                                    0x10 // Sleep in and booster off
#define ST7735_SLPOUT                                                   0x11 // Sleep out and booster on
#define ST7735_PTLON                                                    0x12 // Partial mode on
#define ST7735_NORON                                                    0x13 // Partial mode off

#define ST7735_INVOFF                                                   0x20 // Display inversion off
#define ST7735_INVON                                                    0x21 // Display inversion on
#define ST7735_DISPOFF                                                  0x28 // Display on
#define ST7735_DISPON                                                   0x29 // Display off

#define ST7735_CASET                                                    0x2A // Column address set
#define ST7735_RASET                                                    0x2B // Row address set
#define ST7735_RAMWR                                                    0x2C // Memory write
#define ST7735_RAMRD                                                    0x2E // Memory read

#define ST7735_PTLAR                                                    0x30 // Partial stert/End address
#define ST7735_COLMOD                                                   0x3A // Interface pixel format
#define ST7735_MADCTL                                                   0x36 // Memory data access control

#define ST7735_FRMCTR1                                                  0xB1  //Frame rate control
#define ST7735_FRMCTR2                                                  0xB2
#define ST7735_FRMCTR3                                                  0xB3

#define ST7735_INVCTR                                                   0xB4
#define ST7735_DISSET5                                                  0xB6

#define ST7735_PWCTR1                                                   0xC0 //Power control setting 
#define ST7735_PWCTR2                                                   0xC1
#define ST7735_PWCTR3                                                   0xC2
#define ST7735_PWCTR4                                                   0xC3
#define ST7735_PWCTR5                                                   0xC4
#define ST7735_PWCTR6                                                   0xFC

#define ST7735_VMCTR1                                                   0xC5

#define ST7735_RDID1                                                    0xDA
#define ST7735_RDID2                                                    0xDB
#define ST7735_RDID3                                                    0xDC
#define ST7735_RDID4                                                    0xDD


#define ST7735_GMCTRP1                                                  0xE0
#define ST7735_GMCTRN1                                                  0xE1

#define ST7735_SPI_TIMEOUT                                              100
//=============================================================================================================================


//Variables
//=============================================================================================================================
//variables of cursor
typedef struct __cursor_typedef
{
	uint16_t x_cursor;
	uint16_t y_cursor;
}cursor_typedef;


//variables of text
typedef struct __text_typedef
{
	uint16_t text_size;
	uint16_t text_position_x;
	uint16_t text_position_y;
}text_typedef;


//variables of screen
typedef struct __screen_typedef
{
	//x display limits
	uint16_t dsplmt_xstart; //display's coordinate of up left corner
	uint16_t dsplmt_xend; 	//display's coordinate of up right corner

	//y display limits
	uint16_t dsplmt_ystart; //display's coordinate of down left corner
	uint16_t dsplmt_yend; 	//display's coordinate of down right corner
}screen_t;


//=============================================================================================================================


//Functions
//=============================================================================================================================

//initialization
//--------------------------------------------------------------------------------------------------------
void ST7735_Init();
//--------------------------------------------------------------------------------------------------------


//Color
//--------------------------------------------------------------------------------------------------------

//@brief							function used to set 16 bits color
//@param red_5 				5 bits are used to set RED,   maximum intensity is 2^5 = 31 
//@param green_6 			6 bits are used to set GREEN, maximum intensity is 2^6 = 61 
//@param blue_5 			5 bits are used to set BLUE,  maximum intensity is 2^5 = 31 
//@return obtained_color      
uint16_t set_Color16(uint16_t red_5, uint16_t green_6, uint16_t blue_5);


//INEXACT REPRESENTATION!! THERE ARE INACCURACY!!
//@brief						function used to representation color as (255, 255, 255) 
//@param red_8 			intensity value of   RED(0..255)   which will be represented as intensity   RED(0..31)
//@param green_8 		intensity value of GREEN(0..255)   which will be represented as intensity GREEN(0..61)	
//@param blue_8			intensity value of  BLUE(0..255)   which will be represented as intensity  BLUE(0..31)
//@return obtained_color
uint16_t conv_Color24to16(uint16_t red_8, uint16_t green_8, uint16_t blue_8);
//--------------------------------------------------------------------------------------------------------


//Geometric primitives
//--------------------------------------------------------------------------------------------------------

//@param c_pos 					coordinate x0 of pixel
//@param r_pos					coordinate y0 of pixel
//@param color 					the pixel will be (uint16_t color) color
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);


//@param x0						coordinate x0 of start point
//@param x1						coordinate x1 of finish point
//@param height				height of rectangle		
//@param color				the line will be (uint16_t color) color
void plot_FastVrtLine(int16_t x0, int16_t y0, uint16_t height, uint16_t color);


//@param y0						coordinate y0 of start point
//@param y1						coordinate y1 of finish point
//@param x						width of rectangle
//@param color				the line will be (uint16_t color) color
void plot_FastHrznLine(int16_t x0, int16_t y0, uint16_t width, uint16_t color);


//@brief							Line drawing by Bresenham's line algorithm 
//@param x0						coordinate x0 of start point
//@param y0						coordinate y0 of start point
//@param x1						coordinate x1 of finish point
//@param y1						coordinate y1 of finish point
//@param color 				the line will be (uint16_t color) color
void plot_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);


//@brief							Line drawing by Bresenham's line algorithm 
//@param x0						coordinate x0 of start point
//@param y0						coordinate y0 of start point
//@param x1						coordinate x1 of finish point
//@param y1						coordinate y1 of finish point
//the line will be with smooth transition from color_x0y0 to color_x1y1. For the gradien is used linear interpolation
//@param color_x0y0 	color of start point
//@param color_x1y1		color of finish point
void plot_Line2Color(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color_x0y0, uint16_t color_x1y1);


//@param c_start			coordinate x0 of start point
//@param r_start			coordinate y0 of start point
//@param width				width of rectangle
//@param height				height of rectangle
//@param color				the rectangle will be (uint16_t color) color
void plot_Rectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void plot_FillRectangle(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, uint16_t color);


//@brief 							Circle drawing by midpoint circle drawing algorithm
//@param x0						coordinate x0 of circle center
//@param y0						coordinate y0 of circle center
//@param r						radius of the circle
//@param color				color of the circle
void plot_Circle(uint16_t x0, uint16_t y0, int16_t r, uint16_t color);
void plot_FillCircle( uint16_t x0, uint16_t y0, int16_t r, uint16_t color);


//@param x0						coordinate x0 of first point
//@param y0						coordinate y0 of first point
//@param x1						coordinate x1 of second point
//@param y1						coordinate y1 of second point
//@param x2						coordinate x0 of third point
//@param y2						coordinate y0 of third point
void plot_Triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void plot_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
//--------------------------------------------------------------------------------------------------------


void set_cursor(int16_t x, int16_t y, uint8_t auto_center, uint8_t print_cursor);


//@brief 							Set screen rotate. Default init is 0 (screen's loop up).
//										AlWAYS X-Y address(0,0) locate in up left corner of screen.
//@param angle				set 0   -> portrait
//										set 90  -> right turn
//										set 180 -> upside down
//										set 270 -> left turn
void set_ScreenRotate(uint16_t angle);


void fillScreen(uint16_t color);
//=============================================================================================================================
#endif // #ifndef ST7735_H_
