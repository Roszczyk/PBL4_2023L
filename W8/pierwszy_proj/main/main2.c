#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define LED_G 2
#define LED_B 0
#define LED_R 4

static const char *TAG1 = "TASK1";
static const char *TAG2 = "TASK2";

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
            ESP_LOGI(TAG1, "GREEN");
            break;
        case 2:
            gpio_set_level(LED_B, 1);
            ESP_LOGI(TAG1, "BLUE");
            break;
        case 3:
            gpio_set_level(LED_R, 1);
            ESP_LOGI(TAG1, "RED");
            break;
    }
}

void blinking_task(void *pvParameter)
{
    int current_led = 1;

    while(1) {
        turn_on_led(current_led);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        current_led++;
        if(current_led>3)
            current_led = 1;
    }
}

void writer_task(void *pvParameter)
{
    while(1) {
        ESP_LOGW(TAG2, "Uwaga, przeszkadzam");
        vTaskDelay(200 / portTICK_PERIOD_MS);   
    }
}


void app_main(void)
{
    led_init();
    ESP_LOGI("INFO:", "GPIO initialized...");
    ESP_LOGI("INFO:", "Za chwile będe odpoczywał 1s");
    vTaskDelay(1000 / portTICK_PERIOD_MS );
    xTaskCreate(&blinking_task, "blinking_task", 2048, NULL, 5, NULL);
    xTaskCreate(&writer_task, "writing_task", 2048, NULL, 5, NULL);
}
