#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BIG 1000000000UL
int counter = 0;
pthread_mutex_t lock ;

void *count_to_big(void *arg)
{
	for(int i = 0; i < BIG;i++)
	{
		pthread_mutex_lock(&lock);
		counter ++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(void)
{
	pthread_t thr;
	pthread_create(&thr, NULL,count_to_big,NULL);
	// count_to_big(NULL);
	count_to_big(NULL);
	pthread_join(thr,NULL);
	printf("DONE Count = %u\n",counter);

	return 0;
}



/*-------------------------------------------------------------------------------------
 * Template file for 4-pin I2C OLED display, e.g. from Geekcreit
 * using Adafruit SSD1306 driver and GFX libraries.
 * Tutorial:
 * https://startingelectronics.org/tutorials/arduino/modules/OLED-128x64-I2C-display/
 *-------------------------------------------------------------------------------------*/
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// OLED display TWI address
#define OLED_ADDR   0x3C

// reset pin not used on 4-pin OLED module
Adafruit_SSD1306 display(-1);  // -1 = no reset pin

// 128 x 64 pixel display
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  
}

void loop() {
  // put your main code here, to run repeatedly:

}

