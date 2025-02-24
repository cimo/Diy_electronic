# Diy electronic

Supports Arduino, ESP32, and STM32 boards.
Fully integrated with PlatformIO, making it easy to set up a project using just a single file: board.ini.

## Info:

-   mainboard
-   mcu
-   src_arduino
-   src_esp32
-   src_stm32cube

## Configuration:

1. In the "mainboard" folder, create a subfolder (for example "blue_pill/PlatformIO") and add the "board.ini" file inside.

2. In the "mcu" folder, create a subfolder (for example "stm32f103c8t6") and add "arduino", "esp32", and "stm32cube" subfolders based on the frameworks you want to use. Multiple frameworks can be used simultaneously.

   The main project files should be placed inside these subfolders.
STM32 supports CubeMX projects, that need be generated in this folder.

3. In the "src_arduino", "src_esp32", and "src_stm32cube" folders, you can store your libraries and custom code. Organize them based on the processor folders created in step 2.

## Example:

1. mainboard/nano

    **MCU:** nanoatmega328new
    
    **Platform:** atmelavr
    
    **Framework:** arduino

2. mainboard/blue_pill

    **MCU:** stm32f103c8t6

    **Platform:** ststm32

    **Framework:** arduino, stm32cube

3. mainboard/mks_robin_nano_v1_2

    **MCU:** stm32f103vet6

    **Platform:** ststm32

    **Framework:** arduino, stm32cube

All examples are ready for deployment and can be uploaded directly to your board.
If you start a new project, simply copy an existing one, paste it, and customize it as needed.

## Library:

1. **Display_i2c**: Supports SSD1306 and compatible displays.
2. **Localization**: Dynamic multi-language support.
3. **SD_spi**: Supports large-capacity SD cards with full filenames.
4. **Serial**: Buffered communication without interruptions.
5. **Helper**: A collection of utility methods.

All libraries work the same for both C and C++ projects.
