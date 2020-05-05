# GxEPDxL
E-Paper display library for Arduino for HD parallel interface displays from Dalian Good Display.

## for HD e-paper displays from Dalian Good Display on old DESTM32-L evaluation kit
- discontinued evaluation kit, no longer available
- this library is a relict, removed from GxEPD_HD (was originally in GxEPD)

### The E-Paper display classes are subclasses of Adafruit_GFX, to have graphics and text rendering.
- a graphics buffer is used to have fast rendering through Adafruit_GFX.

### Full Screen Buffer Support
- this library has only full screen update, the SRAM on DESTM32-L has enough space for full buffer

### Supporting Arduino Forum Topic:

- Good Dispay ePaper for Arduino : https://forum.arduino.cc/index.php?topic=436411.0
- don't expect me to remember any details for this library

### Arduino IDE Board (package) for build:
- processor on demo board is STM32F407ZE
- suitable STM32 Arduino package is:
- STM32GENERIC for STM32 Boards
- Board: ""BLACK F407VE/ZE/ZG boards"
- Specific Board: "BLACK 407ZE (V3.0)"
- Upload method: "STLink"

#### Version 0.0.1
- extracted from GxEPD_HD
- simplified naming and source directory structure
