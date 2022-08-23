// Includes
//=============================================================================================================================
#include "st7735.h"
#include "math.h"
//=============================================================================================================================


//Declarations and definitions 
//=============================================================================================================================
extern SPI_HandleTypeDef hspi1;
//=============================================================================================================================

//Functions 
//=============================================================================================================================

//----------------------------------------------------------------------------
void ST7735_SendByte(uint8_t data)
{
  while((SPI1->SR & SPI_SR_TXE) == RESET);  
  SPI1->DR = data;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void ST7735_WaitLastData()
{
  while((SPI1->SR & SPI_SR_TXE) == RESET);
  while((SPI1->SR & SPI_SR_BSY) != RESET);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
static void ST7735_SendCommand(uint8_t data)
{
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_RESET);
  ST7735_SendByte(data);
  ST7735_WaitLastData();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void ST7735_SendData(uint8_t data)
{
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);  
  ST7735_SendByte(data);
  ST7735_WaitLastData();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void ST7735_SendDataMultiple(uint8_t *data, uint32_t num)
{
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);
  
  for (uint32_t i = 0; i < num; i++)
  {
    ST7735_SendByte(*data);
    data++;
  }
  
  ST7735_WaitLastData();
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void ST7735_Init()
{ 
  SPI1->CR1 |= SPI_CR1_SPE;
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
  
  HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_SET);
  HAL_Delay(5);
  HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_RESET);
  HAL_Delay(5);
  HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_SET);
  HAL_Delay(5);
    
  ST7735_SendCommand(ST7735_SWRESET);  
  HAL_Delay(150);

  ST7735_SendCommand(ST7735_SLPOUT);  
  HAL_Delay(500);

  ST7735_SendCommand(ST7735_FRMCTR1);
  ST7735_SendData(0x01);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x2D);

  ST7735_SendCommand(ST7735_FRMCTR2);
  ST7735_SendData(0x01);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x2D);

  ST7735_SendCommand(ST7735_FRMCTR3);
  ST7735_SendData(0x01);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x2D);
  ST7735_SendData(0x01);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x2D);

  ST7735_SendCommand(ST7735_INVCTR);
  ST7735_SendData(0x07);

  ST7735_SendCommand(ST7735_PWCTR1);
  ST7735_SendData(0xA2);
  ST7735_SendData(0x02);
  ST7735_SendData(0x84);

  ST7735_SendCommand(ST7735_PWCTR2);
  ST7735_SendData(0xC5);

  ST7735_SendCommand(ST7735_PWCTR3);
  ST7735_SendData(0x0A);
  ST7735_SendData(0x00);

  ST7735_SendCommand(ST7735_PWCTR4);
  ST7735_SendData(0x8A);
  ST7735_SendData(0x2A);

  ST7735_SendCommand(ST7735_PWCTR5);
  ST7735_SendData(0x8A);
  ST7735_SendData(0xEE);

  ST7735_SendCommand(ST7735_VMCTR1);
  ST7735_SendData(0x0E);

  ST7735_SendCommand(ST7735_INVOFF);

  ST7735_SendCommand(ST7735_MADCTL);
  ST7735_SendData(0xC0);

  ST7735_SendCommand(ST7735_COLMOD);
	
	//ST7735_SendData(0x03); 														//12 bits/pixel
	ST7735_SendData(0x05); 														  //16 bits/pixel R5b(31)/G6b(63)/B5b(31) R0R1R2R3|R4G0G1G2|G3G4G5B0|B1B2B3B4 
																																																
	//ST7735_SendData(0x06); 														//18 bits/pixel
	//ST7735_SendData(0x07); 														//No used
	

  ST7735_SendCommand(ST7735_GMCTRP1);
  ST7735_SendData(0x02);
  ST7735_SendData(0x1c);
  ST7735_SendData(0x07);
  ST7735_SendData(0x12);
  ST7735_SendData(0x37);
  ST7735_SendData(0x32);
  ST7735_SendData(0x29);
  ST7735_SendData(0x2d);
  ST7735_SendData(0x29);
  ST7735_SendData(0x25);
  ST7735_SendData(0x2B);
  ST7735_SendData(0x39);	
  ST7735_SendData(0x00);
  ST7735_SendData(0x01);
  ST7735_SendData(0x03);
  ST7735_SendData(0x10);

  ST7735_SendCommand(ST7735_GMCTRN1);
  ST7735_SendData(0x03);
  ST7735_SendData(0x1d);
  ST7735_SendData(0x07);
  ST7735_SendData(0x06);
  ST7735_SendData(0x2E);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x29);
  ST7735_SendData(0x2D);
  ST7735_SendData(0x2E);
  ST7735_SendData(0x2E);
  ST7735_SendData(0x37);
  ST7735_SendData(0x3F);	
  ST7735_SendData(0x00);
  ST7735_SendData(0x00);
  ST7735_SendData(0x02);
  ST7735_SendData(0x10);

  ST7735_SendCommand(ST7735_NORON);
  HAL_Delay(10);

  ST7735_SendCommand(ST7735_DISPON);
  HAL_Delay(100);

  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void ST7735_SetColAddr(uint16_t c_start, uint16_t c_stop)
{
  uint8_t data[4];
  
  data[0] = (c_start & 0xFF00) >> 8;
  data[1] = c_start & 0x00FF;
  data[2] = (c_stop & 0xFF00) >> 8;
  data[3] = c_stop & 0x00FF;
  
  ST7735_SendCommand(ST7735_CASET);
  ST7735_SendDataMultiple(data, 4);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void ST7735_SetRowAddr(uint16_t r_start, uint16_t r_stop)
{
  uint8_t data[4];
  
  data[0] = (r_start & 0xFF00) >> 8;
  data[1] = r_start & 0x00FF;
  data[2] = (r_stop & 0xFF00) >> 8;
  data[3] = r_stop & 0x00FF;

  ST7735_SendCommand(ST7735_RASET);
  ST7735_SendDataMultiple(data, 4);
}
//----------------------------------------------------------------------------


//COLOR
//=============================================================================================================================

//----------------------------------------------------------------------------------------------------------------
uint16_t setcolor16(uint16_t red_5, uint16_t green_6, uint16_t blue_5)
{
	uint16_t RGB[3] = {0x0000, 0x0000, 0x0000}; 
	uint16_t RGBtrnsf[3];
	uint16_t obtained_color;
		
	RGB[0] += red_5; 
	RGB[1] += green_6;
	RGB[2] += blue_5;
	
	RGBtrnsf[0] = RGB[0]<< 11;
	RGBtrnsf[1] = RGB[1]<< 5;
	RGBtrnsf[2] = RGB[2];
	
	obtained_color = RGBtrnsf[0] | RGBtrnsf[1] | RGBtrnsf[2];
	
	return obtained_color;
}
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
uint16_t convcolor24to16(uint16_t red_8, uint16_t green_8, uint16_t blue_8)
{
	uint16_t RGB[3] = {0x0000, 0x0000, 0x0000};
	uint16_t RGBtrnsf[3];
	uint16_t obtained_color;
	
	uint16_t   red_5,   prcnt_red_5 ;
	uint16_t green_6, prcnt_green_6;
	uint16_t  blue_5,  prcnt_blue_5;
	
	uint8_t prcnt_100 = 100;
	
	uint8_t RGB24mxvl = 255; 
	uint8_t redmxvl = 31;
	uint8_t greenmxvl = 61;
	uint8_t bluemxvl = 31;
	
	//proportions are used to find the relations between colors
	//step 1
	//RGB24mxvl(255)     = prcnt_100(100%)
  //red_8(input color value) = prcnt_red_5(OUTPUT persent value) 	
	prcnt_red_5 = red_8 * prcnt_100 / RGB24mxvl;
	
	//step 2
	//redmxvl(31)         = prcnt_100(100%)
  //red_5(OUTPUT color value) = prcnt_red_5(input persent value) 	
	red_5 = redmxvl * prcnt_red_5 / prcnt_100;
	
	prcnt_green_6 = green_8 * prcnt_100 / RGB24mxvl;
	green_6 = greenmxvl * prcnt_green_6 / prcnt_100;
	
	prcnt_blue_5 = green_8 * prcnt_100 / RGB24mxvl;
	blue_5 = bluemxvl * prcnt_blue_5 / prcnt_100;
	
	RGB[0] += red_5; 
	RGB[1] += green_6;
	RGB[2] += blue_5;
	
	RGBtrnsf[0] = RGB[0]<< 11;
	RGBtrnsf[1] = RGB[1]<< 5;
	RGBtrnsf[2] = RGB[2];
	
	obtained_color = RGBtrnsf[0] | RGBtrnsf[1] | RGBtrnsf[2];
	
	return obtained_color;
}
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
//function interpolationcolor gets values in line coordinate system.	
//@param uint16_t p_start 		start  line's coordinate
//@param uint16_t p_finish		finish line's coordinate
//@paramuint16_t step					coordinate from start to finish line's coordinate
uint16_t interpolationcolor(uint16_t p_start, uint16_t p_finish, uint16_t step,  uint16_t color_x0y0, uint16_t color_x1y1)
{
	uint16_t trnsf_color;
	
	uint16_t RGBx0y0[3];
	uint16_t RGBx1y1[3];
	uint16_t RGBtrnsf[3];
	
	uint16_t Redmask = 0xF800;
	uint16_t Greenmask = 0x07E0;
	uint16_t Bluemask = 0x001F;
		
	RGBx0y0[0] = (color_x0y0 & Redmask) >> 11;
	RGBx0y0[1] = (color_x0y0 & Greenmask) >> 5;
	RGBx0y0[2] = color_x0y0 & Bluemask;	
	
	RGBx1y1[0] = (color_x1y1 & Redmask) >> 11;
	RGBx1y1[1] = (color_x1y1 & Greenmask) >> 5;
	RGBx1y1[2] = color_x1y1 & Bluemask;	
	
	uint16_t lenght = p_finish - p_start; //line size
	
	//in general the algorithm has the form:
	//   lenght   |R_x0y0|			0     |R_x1y1|	 |R_trnsf|
	//  ------- * |G_x0y0| + ------ * |G_x1y1| = |G_trnsf|
	//   lenght   |B_x0y0|	 lenght   |B_x1y1|	 |B_trnsf|
	
	//  lenght-1   |R_x0y0|		 0+1     |R_x1y1|	  |R_trnsf|
	//  -------- * |G_x0y0| + ------ * |G_x1y1| = |G_trnsf|
	//   lenght    |B_x0y0|	  lenght   |B_x1y1|	  |B_trnsf|
	
	//  lenght-2   |R_x0y0|		 0+2     |R_x1y1|	  |R_trnsf|
	//  -------- * |G_x0y0| + ------ * |G_x1y1| = |G_trnsf|
	//   lenght    |B_x0y0|	  lenght   |B_x1y1|	  |B_trnsf|
	
	//...
	//...
	//...
	
	//     0      |R_x0y0|	 lenght   |R_x1y1|	 |R_trnsf|
	//  ------- * |G_x0y0| + ------ * |G_x1y1| = |G_trnsf|
	//   lenght   |B_x0y0|	 lenght   |B_x1y1|	 |B_trnsf|
	
	//***************************************************************************************************************************************
	for(uint8_t color = 0; color < 3; color++)
		RGBtrnsf[color] = ( ( (lenght - (step - p_start) ) * RGBx0y0[color] ) / lenght )  + ( ( (step - p_start) ) * RGBx1y1[color] ) / lenght;		
	//***************************************************************************************************************************************
	
	RGBtrnsf[0] = RGBtrnsf[0] << 11;
	RGBtrnsf[1] = RGBtrnsf[1] << 5;
	
	trnsf_color = RGBtrnsf[0] | RGBtrnsf[1] | RGBtrnsf[2];
	
	return trnsf_color;
}
//----------------------------------------------------------------------------------------------------------------
//=============================================================================================================================


//PLOT FIGURES
//=============================================================================================================================

//Draw pixel
//----------------------------------------------------------------------------------------------------------------
void ST7735_DrawPixel(uint16_t c_pos, uint16_t r_pos, uint16_t color)
{
	uint8_t colorBytes[2];
	colorBytes[0] = (color & 0xFF00) >> 8;
  colorBytes[1] = color & 0x00FF;
	
	HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
	
	//send position
	ST7735_SetColAddr(c_pos, c_pos);
  ST7735_SetRowAddr(r_pos, r_pos);
	
	ST7735_SendCommand(ST7735_RAMWR);
  
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);
  
  ST7735_SendByte(colorBytes[0]);
  ST7735_SendByte(colorBytes[1]);
	
  ST7735_WaitLastData();
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}
//----------------------------------------------------------------------------------------------------------------


//Draw rectangle
//----------------------------------------------------------------------------------------------------------------
void ST7735_DrawRect(uint16_t cStart, uint16_t rStart, uint16_t cStop, uint16_t rStop, uint16_t color)
{
	uint8_t colorBytes[2];
  colorBytes[0] = (color & 0xFF00) >> 8;
  colorBytes[1] = color & 0x00FF;
	
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
  ST7735_SetColAddr(cStart, cStop - 1);
  ST7735_SetRowAddr(rStart, rStop - 1);
  
  ST7735_SendCommand(ST7735_RAMWR);
  
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);
	
	uint32_t size = (cStop - cStart) * (rStop - rStart);
  for (uint32_t i = 0; i < size; i++)
  {
    ST7735_SendByte(colorBytes[0]);
    ST7735_SendByte(colorBytes[1]);
  }
  
  ST7735_WaitLastData();
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}
//----------------------------------------------------------------------------------------------------------------


//plot vertical line 1 color
//----------------------------------------------------------------------------------------------------------------
void plot_fast_vrtline(uint16_t x0, uint16_t x1, uint16_t y, uint16_t color)
{
	uint8_t colorBytes[2];
  colorBytes[0] = (color & 0xFF00) >> 8;
  colorBytes[1] = color & 0x00FF;
	
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
  ST7735_SetColAddr(x0, x1);
  ST7735_SetRowAddr(y, y);
  
  ST7735_SendCommand(ST7735_RAMWR);
  
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);
	
	uint32_t size = x1 - x0;
  for (uint32_t i = 0; i < size; i++)
  {
    ST7735_SendByte(colorBytes[0]);
    ST7735_SendByte(colorBytes[1]);
  }
  
  ST7735_WaitLastData();
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}
//----------------------------------------------------------------------------------------------------------------


//plot horizontal line 1 color
//----------------------------------------------------------------------------------------------------------------
void plot_fast_hrznline(uint16_t y0, uint16_t y1, uint16_t x, uint16_t color)
{
	uint8_t colorBytes[2];
  colorBytes[0] = (color & 0xFF00) >> 8;
  colorBytes[1] = color & 0x00FF;
	
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
  ST7735_SetColAddr(y0, y1);
  ST7735_SetRowAddr(x, x);
  
  ST7735_SendCommand(ST7735_RAMWR);
  
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);
	
	uint32_t size = y1 - y0;
  for (uint32_t i = 0; i < size; i++)
  {
    ST7735_SendByte(colorBytes[0]);
    ST7735_SendByte(colorBytes[1]);
  }
  
  ST7735_WaitLastData();
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}
//----------------------------------------------------------------------------------------------------------------


//plot line 1 color
//----------------------------------------------------------------------------------------------------------------
//Slopes between 0 and -1 by checking whether y needs to increase or decrease (dy < 0)
void plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int16_t x, y;
	
	int16_t yi = 1;
	
	int16_t D;
	
	if(dy < 0)
	{
		yi = - 1;
		dy = - dy;
	}
	
	D = 2 * dy - dx;
	y = y0;
	
	for(x = x0; x <= x1; x++)
	{
		ST7735_DrawPixel(x, y, color);
		if(D > 0)
		{
			y = y + yi;
			D = D + 2*(dy - dx);
		}
		else
			D = D + 2*dy;
	}
}

//an implementation for positive or negative steep slopes 
void plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int16_t x, y;
	
	int16_t xi = 1;
	
	int16_t D;
	
	if(dx < 0)
	{
		xi = - 1;
		dx = - dx;
	}
	
	D = 2 * dx - dy;
	x = x0;
	
	for(y = y0; y <= y1; y++)
	{
		ST7735_DrawPixel(x, y, color);
		if(D > 0)
		{
			x = x + xi;
			D = D + 2*(dx - dy);
		}
		else
			D = D + 2*dx;
	}
}

//detect whether x1 > x0 or y1 > y0 and reverse the input coordinates before drawing
void plot_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	if( abs((int)(y1 - y0)) < abs((int)(x1 - x0)) )
	{
		if(x0 > x1)
			plot_line_low(x1, y1, x0, y0, color);
		else
			plot_line_low(x0, y0, x1, y1, color);
	}
	else
	{
		if(y0 > y1)
			plot_line_high(x1, y1, x0, y0, color);
		else
			plot_line_high(x0, y0, x1, y1, color);
	}
}
//----------------------------------------------------------------------------------------------------------------


//plot line 2 color
//----------------------------------------------------------------------------------------------------------------
void plot_line_low_2(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color_x0y0, uint16_t color_x1y1)
{
	uint16_t color;
	
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int16_t x, y;
	
	int16_t yi = 1;
	
	int16_t D;
	
	if(dy < 0)
	{
		yi = - 1;
		dy = - dy;
	}
	
	D = 2 * dy - dx;
	y = y0;
	
	for(x = x0; x <= x1; x++)
	{
		color = interpolationcolor(x0, x1, x, color_x0y0, color_x1y1);
		ST7735_DrawPixel(x, y, color);
		if(D > 0)
		{
			y = y + yi;
			D = D + 2*(dy - dx);
		}
		else
			D = D + 2*dy;
	}
}

void plot_line_high_2(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color_x0y0, uint16_t color_x1y1)
{
	uint16_t color;
	
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int16_t x, y;
	
	int16_t xi = 1;
	
	int16_t D;
	
	if(dx < 0)
	{
		xi = - 1;
		dx = - dx;
	}
	
	D = 2 * dx - dy;
	x = x0;
	
	for(y = y0; y <= y1; y++)
	{
		color = interpolationcolor(y0, y1, y, color_x0y0, color_x1y1);
		ST7735_DrawPixel(x, y, color);
		if(D > 0)
		{
			x = x + xi;
			D = D + 2*(dx - dy);
		}
		else
			D = D + 2*dx;
	}
}


void plot_line_2color(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color_x0y0, uint16_t color_x1y1)
{
	if( abs((int)(y1 - y0)) < abs((int)(x1 - x0)) )
	{
		if(x0 > x1)
			plot_line_low_2(x1, y1, x0, y0, color_x0y0, color_x1y1);
		else
			plot_line_low_2(x0, y0, x1, y1, color_x0y0, color_x1y1);
	}
	else
	{
		if(y0 > y1)
			plot_line_high_2(x1, y1, x0, y0, color_x0y0, color_x1y1);
		else
			plot_line_high_2(x0, y0, x1, y1, color_x0y0, color_x1y1);
	}
}

//----------------------------------------------------------------------------------------------------------------


//plot circle
//----------------------------------------------------------------------------------------------------------------
void plot_circle( uint16_t x0, uint16_t y0, int16_t r, uint16_t color)
{
	//starting coordinates
	int16_t x = 0;
	int16_t y = r;
	
	//The value of p is calculated at the mid-point of the two contending pixels (x - 0.5, y+1)
	//p = (r – 0.5)^2 + (0+1)^2 – r^2 = =1.25 – r = 1 - r (because integer value)
	int16_t p = 1 - r;
	
	do
	{
		ST7735_DrawPixel(x0 + x, y0 + y, color);
		ST7735_DrawPixel(x0 + y, y0 + x, color);
		ST7735_DrawPixel(x0 - y, y0 + x, color);
		ST7735_DrawPixel(x0 - x, y0 + y, color);
		ST7735_DrawPixel(x0 - x, y0 - y, color);
		ST7735_DrawPixel(x0 - y, y0 - x, color);
		ST7735_DrawPixel(x0 + y, y0 - x, color);
		ST7735_DrawPixel(x0 + x, y0 - y, color);
		
		//inside the circle
		if(p < 0)
			p += (2*x) + 1;
		
		//p > 0 -> outside circle
		else
		{
			y = y - 1;
			p += (2*x) - (2*y) + 1;
		}
		
		x = x + 1;
	}
	while(y >= x);	
}
//----------------------------------------------------------------------------------------------------------------
//=============================================================================================================================






