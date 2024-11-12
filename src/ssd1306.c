#include <bcm2835.h>
#include <stdio.h>

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 32
#define RESET_PIN RPI_V2_GPIO_P1_22  // 這是連接到 reset 腳位的 GPIO 25 引腳
#define DC_PIN RPI_V2_GPIO_P1_18  // 這是連接到 DC 腳位的 GPIO 24 引腳


void SSD1306_Command(uint8_t cmd) {
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
    bcm2835_gpio_write(DC_PIN, LOW);   //DC腳位低電位 指令模式
    bcm2835_spi_transfer(cmd);
}
void SSD1306_Data(uint8_t cmd) {
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
    bcm2835_gpio_write(DC_PIN, HIGH);  //DC腳位高電位 資料模式
    bcm2835_spi_transfer(cmd);
}

void spi_init(void) {
    if (!bcm2835_init()) {
        printf("bcm2835 初始化失敗！\n");
    }

    bcm2835_gpio_fsel(RESET_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(RESET_PIN, HIGH);
    bcm2835_delay(200);
    bcm2835_gpio_write(RESET_PIN, LOW);
    bcm2835_delay(200);
    bcm2835_gpio_write(RESET_PIN, HIGH);
    bcm2835_gpio_fsel(DC_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_spi_begin();
    printf("Starting\n");
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_2048); // 根據需要調整速度
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
}
void spi_cleanup(void) {
    bcm2835_spi_end();
    bcm2835_close();
}

void SSD1306_Init(void) {

    SSD1306_Command(0xAE); // Display OFF
    SSD1306_Command(0x20); // Set Memory Addressing Mode
    SSD1306_Command(0x00); // Horizontal Addressing Mode

    SSD1306_Command(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
    SSD1306_Command(0xC8); // Set COM Output Scan Direction
    SSD1306_Command(0x00); //---set low column address
    SSD1306_Command(0x10); //---set high column address
    SSD1306_Command(0x40); //--set start line address - CHECK
    SSD1306_Command(0x81); // Set Contrast Control
    SSD1306_Command(0xFF);

    SSD1306_Command(0xA1); //--set segment re-map 0 to 127 - CHECK
    SSD1306_Command(0xA6); // Set Normal Display

    
    SSD1306_Command(0xA8); // Set Multiplex Ratio
    SSD1306_Command(0x1F); // Set MUX Ratio
    SSD1306_Command(0xA4); // Entire Display ON (Resume to RAM content display)

    SSD1306_Command(0xD3); // Set Display Offset
    SSD1306_Command(0x00);
    SSD1306_Command(0xD5); 
    SSD1306_Command(0xF0); 
    SSD1306_Command(0xD8);
    SSD1306_Command(0x22);
    SSD1306_Command(0xDA); 
    SSD1306_Command(0x02);

    SSD1306_Command(0xDB);
    SSD1306_Command(0x20);
    SSD1306_Command(0x8D); 
    SSD1306_Command(0x14);
    
    SSD1306_Command(0xAF); // Display ON
}

void SSD1306_FillScreen(void) {
    for(int i = 0; i < SSD1306_WIDTH/4; i++) {
        SSD1306_Command(0xb0 + i);
        SSD1306_Command(0x00);
        SSD1306_Command(0x10);
        for(int col = 0; col < SSD1306_WIDTH; col++) {
            SSD1306_Data(0xFF); 
        }
    }
}

void SSD1306_clean(void) {
    for(int i = 0; i < SSD1306_WIDTH/4; i++) {
        SSD1306_Command(0xb0 + i);
        SSD1306_Command(0x00);
        SSD1306_Command(0x10);
        for(int col = 0; col < SSD1306_WIDTH; col++) {
            SSD1306_Data(0x00); 
        }
    }
}



