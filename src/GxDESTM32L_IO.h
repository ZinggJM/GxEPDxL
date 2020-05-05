// Class GxDESTM32L_IO : io class for parallel interface e-paper displays from Dalian Good Display Inc.
//
// Created by Jean-Marc Zingg based on demo code from Good Display for red DESTM32-L board.
//
// The GxDESTM32L_IO is board specific and serves as IO channel for the display class.
//
// This classes can also serve as an example for other boards to use with parallel e-paper displays from Good Display,
// however this is not easy, because of the e-paper specific supply voltages and big RAM buffer needed.
//
// To be used with "BLACK 407ZE (V3.0)" of "BLACK F407VE/ZE/ZG boards" of package "STM32GENERIC for STM32 boards" for Arduino.
// https://github.com/danieleff/STM32GENERIC
//
// The e-paper display and demo board is available from:
// http://www.buy-lcd.com/index.php?route=product/product&path=2897_10571&product_id=22833
// or https://www.aliexpress.com/store/product/Epaper-demo-kit-for-6-800X600-epaper-display-GDE060BA/600281_32812255729.html

#ifndef _GxDESTM32L_IO_H
#define _GxDESTM32L_IO_H

#include <Arduino.h>

class GxDESTM32L_IO
{
  public:
    GxDESTM32L_IO();
    void init(uint8_t power_on_led = PB12);
    void delay35ns(uint32_t nCount);
    void powerOn(void);
    void powerOff(void);
    void start_scan(void);
    void send_row(uint8_t row_data[], uint16_t row_size, uint32_t delay_time);
  private:
    uint8_t _pwr_led;
};

#endif
