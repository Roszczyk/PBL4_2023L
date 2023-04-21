#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_G 2
#define LED_B 0
#define LED_R 4

static const char *TAG = "PROG1";

void led_init()
{
    gpio_pad_select_gpio(LED_G);
    gpio_set_direction(LED_G, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(LED_B);
    gpio_set_direction(LED_B, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(LED_R);
    gpio_set_direction(LED_R, GPIO_MODE_OUTPUT);
}

void turn_on_led(int led)
{
    gpio_set_level(LED_G, 0);
    gpio_set_level(LED_B, 0);
    gpio_set_level(LED_R, 0);

    switch(led)
    {
        case 1:
            gpio_set_level(LED_G, 1);
            printf("Taki zwykły printf:GREEN\n");
            ESP_LOGI(TAG, "GREEN");
            break;
        case 2:
            gpio_set_level(LED_B, 1);
            printf("Taki zwykły printf:BLUE\n");
            break;
        case 3:
            gpio_set_level(LED_R, 1);
            printf("Taki zwykły printf:RED\n");
            break;
    }
}

void app_main(void)
{
    led_init();
    ESP_LOGI("INFO:", "GPIO initialized...");
    turn_on_led(1);
    ESP_LOGW("WARNING:", "Prawie kończymy");
    ESP_LOGE("ERROR:", "KONIEC");
}
