// Class GxGDE060BAxL : display class for GDE060BA e-paper display from Dalian Good Display Inc.
//
// Created by Jean-Marc Zingg based on demo code from Good Display for red DESTM32-L board.
//
// The GxGDE060BAxL class is not board specific, but relies on FMSC SRAM for buffer memory, as available on DESTM32-L,
// and on a specific IO channel class for parallel connection e-paper displays.
// 
// The GxDESTM32L_IO is board specific and serves as IO channel for the display class.
//
// These classes can serve as an example for other boards for this e-paper display,
// however this is not easy, because of the e-paper specific supply voltages and big RAM buffer needed.
//
// To be used with "BLACK 407ZE (V3.0)" of "BLACK F407VE/ZE/ZG boards" of package "STM32GENERIC for STM32 boards" for Arduino.
// https://github.com/danieleff/STM32GENERIC
//
// The e-paper display and demo board is available from:
// http://www.buy-lcd.com/index.php?route=product/product&path=2897_10571&product_id=22833
// or https://www.aliexpress.com/store/product/Epaper-demo-kit-for-6-800X600-epaper-display-GDE060BA/600281_32812255729.html

#ifndef _GxGDE060BAxL_H
#define _GxGDE060BAxL_H

#include <Arduino.h>
#include "GxEPDxL.h"
#include "GxDESTM32L_IO.h"

#define GxGDE060BAxL_WIDTH 800
#define GxGDE060BAxL_HEIGHT 600
#define GxGDE060BAxL_BUFFER_SIZE GxGDE060BAxL_WIDTH * GxGDE060BAxL_HEIGHT / 4 // 2bits per pixel
#define GxGDE060BAxL_CL_DELAY 13 // this value produces the same CL period as the hex demo code

#define GxGDE060BAxL_FRAME_BEGIN_SIZE  8
const unsigned char wave_begin_60[4][GxGDE060BAxL_FRAME_BEGIN_SIZE] =
{
  0, 0, 0, 0, 2, 2, 2, 0, //GC0->GC3
  0, 0, 0, 1, 2, 2, 2, 0, //GC1->GC3
  0, 0, 1, 1, 2, 2, 2, 0, //GC2->GC3
  0, 1, 1, 1, 2, 2, 2, 0, //GC3->GC3
};

#define GxGDE060BAxL_FRAME_END_SIZE  18
const unsigned char wave_end_60[4][GxGDE060BAxL_FRAME_END_SIZE] =
{
  0, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 0, 0, //GC3->GC0
  0, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 0, 0, 0, //GC3->GC1
  0, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 0, 0, 0, 0, //GC3->GC2
  0, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, //GC3->GC3
};

const uint8_t bw2grey[] = {
  0b00000000, 0b00000011, 0b00001100, 0b00001111, 
  0b00110000, 0b00110011, 0b00111100, 0b00111111,
  0b11000000, 0b11000011, 0b11001100, 0b11001111,
  0b11110000, 0b11110011, 0b11111100, 0b11111111,
};

#define GxGDE060BAxL_ROW_BUFFER_SIZE (GxGDE060BAxL_WIDTH / 4)

// fixed, multiple of 64 and >= GxGDE060BAxL_ROW_BUFFER_SIZE
#define WAVE_TABLE_SIZE 256

typedef uint8_t epd_buffer_type[GxGDE060BAxL_BUFFER_SIZE];

struct fmsc_sram_type
{
  epd_buffer_type epd_sram_buffer1;
  epd_buffer_type epd_sram_buffer2;
};

#define FMSC_SRAM ((fmsc_sram_type*)0x68000000) // NE3 PG10 on DESTM32-L

class GxGDE060BAxL : public GxEPDxL
{
  public:
    GxGDE060BAxL(GxDESTM32L_IO& io);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void init(Stream* pDiagnosticOutput = 0); // (pDiagnosticOutput = 0) : disabled
    void fillScreen(uint16_t color); // to buffer
    void update(void);
    // monochrome bitmap to buffer, may be cropped, drawPixel() used, update needed, Adafruit_GFX signature
    void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
    // to buffer, may be cropped, drawPixel() used, update needed, new signature, may support some bm_modes
    void drawBitmap(const uint8_t *bitmap, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, int16_t m = bm_normal);
    // 4 gray levels to full screen, filled with white if size is less, no update needed
    void drawPicture(const uint8_t *picture, uint32_t size);
    // monochrome to full screen, filled with white if size is less, no update needed
    void drawBitmap(const uint8_t *bitmap, uint32_t size, int16_t m = bm_normal); // parameter m ignored
    // undo last drawBitmap to prepare for next drawBitmap (turn display white);
    // any bitmap can be used, but real last bitmap gives slightly better result
    void erasePicture(const uint8_t *picture, uint32_t size);
    void eraseBitmap(const uint8_t *bitmap, uint32_t size);
    void eraseDisplay(); // alternative to eraseBitmap, without bitmap
    //void DisplayTestPicture(uint8_t nr);
    void fillScreenTest();
    void eraseDisplay(bool using_partial_update){eraseDisplay();}; // parameter ignored
    // partial update, not implemented
    void updateWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool using_rotation = true){};
    // paged drawing, for limited RAM, drawCallback() is called GxGDEH029A1_PAGES times
    // each call of drawCallback() should draw the same
    void drawPaged(void (*drawCallback)(void)){};
    void drawCornerTest(uint8_t em = 0x01){};
    void powerOff() {}; // not implemented
    void hibernate() {}; // not implemented
  private:
    void init_wave_table(void);
    void clear_display();
  private:
    uint8_t wave_begin_table[WAVE_TABLE_SIZE][GxGDE060BAxL_FRAME_BEGIN_SIZE];
    uint8_t wave_end_table[WAVE_TABLE_SIZE][GxGDE060BAxL_FRAME_END_SIZE];
    uint8_t row_buffer[GxGDE060BAxL_ROW_BUFFER_SIZE];
    epd_buffer_type* p_active_buffer;
    epd_buffer_type* p_erase_buffer;
    GxDESTM32L_IO& IO;
};

#define GxEPD_Class GxGDE060BAxL

#define GxEPD_WIDTH GxGDE060BAxL_WIDTH
#define GxEPD_HEIGHT GxGDE060BAxL_HEIGHT
#define GxEPD_BitmapExamples <bitmaps/BitmapExamples800x600.h>
#define GxEPD_BitmapExamplesQ "bitmaps/BitmapExamples800x600.h"
#define BitmapExample1 BitmapExample800x600_1
#define BitmapExample2 BitmapExample800x600_2

#endif
