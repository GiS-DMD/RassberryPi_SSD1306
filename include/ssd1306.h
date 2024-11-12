#include <stdio.h>
#include <bcm2835.h>
#include <unistd.h>



void SSD1306_Command(uint8_t cmd);
void SSD1306_Data(uint8_t data);
void spi_init(void);
void spi_cleanup(void);
void SSD1306_Init(void);
void SSD1306_FillScreen(void);
void SSD1306_clean(void) ;