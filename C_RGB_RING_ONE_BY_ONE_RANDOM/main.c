/*
 * C_RGB_RING_ONE_BY_ONE_RANDOM.c
 *
 * Created: 7.1.2023. 02:39:39
 * Author : Aleksandar Bogdanovic
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "ws2811.h"

#define  PAUSE 1000
#define DELAY 10
#define LENGTH 24
#define PORT_PIN PORTB0
#define RAND_MAX 1024

// Define the output function, using pin 0 on PORT B.
DEFINE_WS2811_FN(WS2811RGB, PORTB, 0)

void setPixel(RGB_t pixel, uint8_t row, RGB_t *array)
{
	array[row].r = pixel.r;
	array[row].g = pixel.g;
	array[row].b = pixel.b;
}

void setPixelColor(uint8_t r, uint8_t g, uint8_t b, uint8_t row, RGB_t *array)
{
	array[row].r = r;
	array[row].g = g;
	array[row].b = b;
}

void setColor(uint8_t r, uint8_t g, uint8_t b, RGB_t *array)
{
	for (uint8_t i = 0; i < LENGTH; i++)
	{
		setPixelColor(r, g, b, i, array);
	}
}

void rotate(RGB_t *array)
{
	uint8_t i;
	RGB_t temp;
	
	temp = array[0];
	for (i = 0; i < (LENGTH - 1); i++)
	{
		setPixel(array[i+1], i, array);
	}
	setPixel(temp, LENGTH - 1, array);
}
// Configure pin(s) for output
void init(void)
{
	DDRB |= (1 << PORT_PIN);
	PORTB &= ~(1 << PORT_PIN);
}


int main(void)
{
    init();
	
	RGB_t rgb[LENGTH];														// Make a place to hold the current LED pattern
	setColor(0,0,0, &rgb);													// Make sure the ring color is cleared to begin
	
    while (1) {
	    setPixelColor(rand() % 256, rand() % 256, rand() % 256, 0, &rgb);	// set the first LED to a random color
	    WS2811RGB(rgb, LENGTH);	
													// update the ring with the new pixel data
	    _delay_ms(PAUSE);
	    rotate(&rgb);														// rotate the pixel array by one element
		
    }
}

/*
Black: 0x000000
White: 0xFFFFFF
Grey: 0x808080
Light grey: 0xD3D3D3
Dark grey: 0xA9A9A9
Brown: 0xA52A2A
Red: 0xFF0000
Orange: 0xFFA500
Yellow: 0xFFFF00
Green: 0x00FF00
Light blue: 0xADD8E6
Blue: 0x0000FF
Purple: 0x800080
Pink: 0xFFC0CB
Magenta: 0xFF00FF
*/
