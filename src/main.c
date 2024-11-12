#include <string.h>
#include <bcm2835.h>
#include <signal.h>
#include "ssd1306.h"

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 32
#define RESET_PIN RPI_V2_GPIO_P1_22  // 這是連接到 reset 腳位的 GPIO 25 引腳
#define DC_PIN RPI_V2_GPIO_P1_18  // 這是連接到 DC 腳位的 GPIO 24 引腳

// 中斷標誌
volatile sig_atomic_t keep_running = 1;

// 中斷處理函數
void intHandler(int dummy) {
    keep_running = 0;
}


int main(void) {
    // 安裝 SIGINT 處理器
    signal(SIGINT, intHandler);

    spi_init();
    SSD1306_Init(); // 初始化 SSD1306

    while (keep_running) {
        SSD1306_FillScreen(); // 顯示全螢幕亮白畫面
        bcm2835_delay(500);

        SSD1306_clean(); // 顯示全螢幕黑畫面
        bcm2835_delay(500);
    }

    // 清理
    spi_cleanup();
    printf("程序已安全退出\n");
    return 0;
}