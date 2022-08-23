#ifndef ST7735_H_
#define ST7735_H_

//Includes
//=============================================================================================================================
#include "stdbool.h"
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


#define ST7735_X_SIZE 																									128
#define ST7735_Y_SIZE 																									160
#define ST7735_X_CENTRE 																								ST7735_X_SIZE / 2
#define ST7735_Y_CENTRE																									ST7735_Y_SIZE / 2


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


//Functions
//=============================================================================================================================

//initialization
//--------------------------------------------------------------------------------------------------------
void ST7735_Init();
//--------------------------------------------------------------------------------------------------------


//Color
//--------------------------------------------------------------------------------------------------------

//function used to set 16 bits color
//@param uint16_t red_5 				5 bits are used to set RED,   maximum intensity is 2^5 = 31 
//@param uint16_t green_6 			6 bits are used to set GREEN, maximum intensity is 2^6 = 61 
//@param uint16_t blue_5 				5 bits are used to set BLUE,  maximum intensity is 2^5 = 31 
//@return obtained_color      
uint16_t setcolor16(uint16_t red_5, uint16_t green_6, uint16_t blue_5);


//function used to representation color as (255, 255, 255) 
//INEXACT REPRESENTATION!! THERE ARE INACCURACY!!
//@param uint16_t red_8 			intensity value of   RED(0..255)   which will be represented as intensity   RED(0..31)
//@param uint16_t green_8 		intensity value of GREEN(0..255)   which will be represented as intensity GREEN(0..61)	
//@param uint16_t blue_8			intensity value of  BLUE(0..255)   which will be represented as intensity  BLUE(0..31)
//@return obtained_color
uint16_t convcolor24to16(uint16_t red_8, uint16_t green_8, uint16_t blue_8);
//--------------------------------------------------------------------------------------------------------


//Geometric primitives
//--------------------------------------------------------------------------------------------------------

//@param uint16_t c_pos 					coordinate x0 of pixel
//@param uint16_t r_pos						coordinate y0 of pixel
//@param uint16_t color 					the pixel will be (uint16_t color) color
void ST7735_DrawPixel(uint16_t c_pos, uint16_t r_pos, uint16_t color);


//@param uint16_t c_start				coordinate x0 of start point
//@param uint16_t r_start				coordinate y0 of start point
//@param uint16_t c_stop				coordinate x1 of finish point
//@param uint16_t c_stop				coordinate y1 of finish point
//@param uint16_t color					the rectangle will be (uint16_t color) color
void ST7735_DrawRect(uint16_t c_start, uint16_t r_start, uint16_t c_stop, uint16_t r_stop, uint16_t color);


//@param uint16_t x0						coordinate x0 of start point
//@param uint16_t x1						coordinate x1 of finish point
//@param uint16_t y							coordinate y of start and finish points
//@param uint16_t color					the line will be (uint16_t color) color
void plot_fast_vrtline(uint16_t x0, uint16_t x1, uint16_t y, uint16_t color);


//@param uint16_t y0						coordinate y0 of start point
//@param uint16_t y1						coordinate y1 of finish point
//@param uint16_t x							coordinate x of start and finish points
//@param uint16_t color					the line will be (uint16_t color) color
void plot_fast_hrznline(uint16_t y0, uint16_t y1, uint16_t x, uint16_t color);


//Line drawing by Bresenham's line algorithm 
//@param uint16_t x0						coordinate x0 of start point
//@param uint16_t y0						coordinate y0 of start point
//@param uint16_t x1						coordinate x1 of finish point
//@param uint16_t y1						coordinate y1 of finish point
//@param uint16_t color 				the line will be (uint16_t color) color
void plot_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);


//Line drawing by Bresenham's line algorithm 
//the line will be with smooth transition from color_x0y0 to color_x1y1. For the gradien is used linear interpolation
//@param uint16_t x0						coordinate x0 of start point
//@param uint16_t y0						coordinate y0 of start point
//@param uint16_t x1						coordinate x1 of finish point
//@param uint16_t y1						coordinate y1 of finish point
//@param uint16_t color_x0y0 		color of start point
//@param uint16_t color_x1y1		color of finish point
void plot_line_2color(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color_x0y0, uint16_t color_x1y1);


//Circle drawing by midpoint circle drawing algorithm
//@param uint16_t x0						coordinate x0 of circle center
//@param uint16_t y0						coordinate y0 of circle center
//@param uint16_t r							radius of the circle
//@param uint16_t color					color of the circle
void plot_circle(uint16_t x0, uint16_t y0, int16_t r, uint16_t color);
//--------------------------------------------------------------------------------------------------------

//=============================================================================================================================
#endif // #ifndef ST7735_H_
