# Progress Tracker
1. Test1_matrix_spi_8x8
    - As I am using MAX7219 for the 8x8 matrix, I have to use SPI to control it. And I have extracted the IC from 8x8 matrix and connected it to the breadboard. So first I will test the SPI communication with the MAX7219 and see if I can control the LEDs on the matrix. I will use the Arduino IDE to write a simple code to turn on and off the LEDs on the matrix. If this works, then I can move on to the next step of connecting the MAX7219 to the 4 digit Seven Segment display.

2. Test2_SevSeg_with_max7219
    - After successfully testing the SPI communication with the MAX7219, I will connect it to the 4 digit Seven Segment display. I will write a code to display numbers on the Seven Segment display using the MAX7219. This will involve sending the correct commands to the MAX7219 to control which segments of the display are turned on or off. It will show 0000 to 9999 in a loop to test all the digits and segments. If this works, then I can move on to the next step of integrating the NTP time synchronization .
