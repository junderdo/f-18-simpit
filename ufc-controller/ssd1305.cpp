/* 
 * @description ssd1305 controller 
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 */

#include <SPI.h>
#include <Wire.h>
#include <avr/pgmspace.h>

#include <stdio.h>
#include "ssd1305.h"
#include "oled.h"


// images
#include "1.c"
#include "2.c"
#include "3.c"
#include "4.c"
#include "5.c"
#include "6.c"
#include "7.c"
#include "8.c"
#include "9.c"
#include "10.c"
#include "11.c"
#include "12.c"
#include "13.c"
#include "14.c"
#include "15.c"
#include "16.c"
#include "17.c"
#include "18.c"
#include "19.c"
#include "20.c"
#include "21.c"

#include "black.c"

#include "font1206.c"
#include "font1608.c"
#include "font1612.c"
#include "font3216.c"

uint8_t oled_buf[WIDTH * HEIGHT / 8];

void command(uint8_t cmd) {
  digitalWrite(OLED_DC, LOW);
  SPIWrite(&cmd, 1);
}

void SPIWrite(uint8_t *buffer, int bufferLength) {
  int i;
  digitalWrite(OLED_CS, LOW);
  for (i = 0; i < bufferLength; i++) {
    SPI.transfer(buffer[i]);
  }
  digitalWrite(OLED_CS, HIGH);
}

void SSD1305_begin()
{

  pinMode(OLED_RST, OUTPUT);
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_CS, OUTPUT);
  SPI.begin();

  Serial.print("starting oled\n");

  SPI.setClockDivider(SPI_CLOCK_DIV128);

  digitalWrite(OLED_CS, LOW);
  digitalWrite(OLED_RST, HIGH);
  delay(10);
  digitalWrite(OLED_RST, LOW);
  delay(10);
  digitalWrite(OLED_RST, HIGH);
  
  command(0xAE);//--turn off oled panel
  command(0x04);//--turn off oled panel
  command(0x10);//--turn off oled panel
  command(0x40);//---set low column address
  command(0x81);//---set high column address
  command(0x80);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  command(0xA1);//--set contrast control register
  command(0xA6); // Set SEG Output Current Brightness
  command(0xA8);//--Set SEG/Column Mapping     0xa0×óÓÒ·´ÖÃ 0xa1Õý³£
  command(0x1F);//Set COM/Row Scan Direction   0xc0ÉÏÏÂ·´ÖÃ 0xc8Õý³£
  command(0xC8);//--set normal display
  command(0xD3);//--set multiplex ratio(1 to 64)
  command(0x00);//--1/64 duty
  command(0xD5);//-set display offset Shift Mapping RAM Counter (0x00~0x3F)
  command(0xF0);//-not offset
  command(0xd8);//--set display clock divide ratio/oscillator frequency
  command(0x05);//--set divide ratio, Set Clock as 100 Frames/Sec
  command(0xD9);//--set pre-charge period
  command(0xC2);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  command(0xDA);//--set com pins hardware configuration
  command(0x12);
  command(0xDB);//--set vcomh
  command(0x08);//Set VCOM Deselect Level
  command(0xAF);//-Set Page Addressing Mode (0x00/0x01/0x02)
  Serial.print("oled startup complete\n");
}

void SSD1305_boot()
{
    Serial.print("booting oled\n");
    /* display boot sequence image slideshow/video */
    SSD1305_begin();
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq1, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq2, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq3, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq4, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq5, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq6, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq7, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq8, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq9, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq10, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq11, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq12, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq13, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq14, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq15, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq16, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq17, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq18, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq19, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq20, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(50);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq21, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    Serial.print("oled boot complete\n");
}

void SSD1305_clear(uint8_t* buffer)
{
  int i;
  for (i = 0; i < WIDTH * HEIGHT / 8; i++)
  {
    buffer[i] = 0;
  }
}

void SSD1305_pixel(int x, int y, char color, uint8_t* buffer)
{
  if (x > WIDTH || y > HEIGHT)return ;
  if (color)
    buffer[x + (y / 8)*WIDTH] |= 1 << (y % 8);
  else
    buffer[x + (y / 8)*WIDTH] &= ~(1 << (y % 8));
}

void SSD1305_char1616(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer)
{
  uint8_t i, j;
  uint8_t chTemp = 0, y0 = y, chMode = 0;

  for (i = 0; i < 32; i++) {
    chTemp = pgm_read_byte(&Font1612[chChar - 0x30][i]);
    for (j = 0; j < 8; j++) {
      chMode = chTemp & 0x80 ? 1 : 0;
      SSD1305_pixel(x, y, chMode, buffer);
      chTemp <<= 1;
      y++;
      if ((y - y0) == 16) {
        y = y0;
        x++;
        break;
      }
    }
  }
}

void SSD1305_char(unsigned char x, unsigned char y, char acsii, char size, char mode, uint8_t* buffer)
{
  unsigned char i, j, y0 = y;
  char temp;
  unsigned char ch = acsii - ' ';
  unsigned char width = size;
  if (width == 32) {
    width = 16;
  }
  for (i = 0; i < size; i++) {
    if (size == 12)
    {
      if (mode)temp = pgm_read_byte(&Font1206[ch][i]);
      else temp = ~pgm_read_byte(&Font1206[ch][i]);
    }
    else if (size == 16)
    {
      if (mode)temp = pgm_read_byte(&Font1608[ch][i]);
      else temp = ~pgm_read_byte(&Font1608[ch][i]);
    }
    else if (size == 32)
    {
      if (mode)temp = pgm_read_byte(&Font3216[ch][i]);
      else temp = ~pgm_read_byte(&Font3216[ch][i]);
    }
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80) SSD1305_pixel(x, y, 1, buffer);
      else SSD1305_pixel(x, y, 0, buffer);
      temp <<= 1;
      y++;
      if ((y - y0) == width)
      {
        y = y0;
        x++;
        break;
      }
    }
  }
}

void SSD1305_string(uint8_t x, uint8_t y, const char *pString, uint8_t Size, uint8_t Mode, uint8_t* buffer)
{
  while (*pString != '\0') {
    if (x > (WIDTH - Size / 2)) {
      x = 0;
      y += Size;
      if (y > (HEIGHT - Size)) {
        y = x = 0;
      }
    }

    SSD1305_char(x, y, *pString, Size, Mode, buffer);
    x += Size / 2;
    pString++;
  }
}

void SSD1305_char3216(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer)
{
  uint8_t i, j;
  uint8_t chTemp = 0, y0 = y, chMode = 0;

  for (i = 0; i < 64; i++) {
    chTemp = pgm_read_byte(&Font3216[chChar - 0x30][i]);
    for (j = 0; j < 8; j++) {
      chMode = chTemp & 0x80 ? 1 : 0;
      SSD1305_pixel(x, y, chMode, buffer);
      chTemp <<= 1;
      y++;
      if ((y - y0) == 32) {
        y = y0;
        x++;
        break;
      }
    }
  }
}

void SSD1305_bitmap(uint8_t x, uint8_t y, const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t* buffer)
{
  uint8_t i, j, byteWidth = (chWidth + 7) / 8;
  for (j = 0; j < chHeight; j++) {
    for (i = 0; i < chWidth; i++) {
      if (pgm_read_byte(pBmp + j * byteWidth + i / 8) & (128 >> (i & 7))) {
        SSD1305_pixel(x + i, y + j, 1, buffer);
      }
    }
  }
}

void SSD1305_display(uint8_t* pBuf)
{
  uint8_t page;
  for (page = 0; page < 8; page++) {
    /* set page address */
    command(0xB0 + page);
    /* set low column address */
    command(0x04);
    /* set high column address */
    command(0x10);
    /* write data */
    digitalWrite(OLED_DC, HIGH);
    SPIWrite(pBuf, WIDTH);
    pBuf += WIDTH;
  }
}
