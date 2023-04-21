#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <bmp280.h>
#include <string.h>

#define LED_G 2
#define LED_B 0
#define LED_R 4

static const char *TAG1 = "TASK1";

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

void sensor_task(void *pvParameter)
{
    
    bmp280_params_t params;
    bmp280_init_default_params(&params);
    bmp280_t dev;
    memset(&dev, 0, sizeof(bmp280_t));

    ESP_ERROR_CHECK(bmp280_init_desc(&dev, BMP280_I2C_ADDRESS_0, 0, 22, 21));
    ESP_ERROR_CHECK(bmp280_init(&dev, &params));

    bool bme280p = dev.id == BME280_CHIP_ID;
    ESP_LOGI("BMP280", "Found %s\n", bme280p ? "BME280" : "BMP280");

    float pressure, temperature, humidity;
    
    
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(5000));

        if (bmp280_read_float(&dev, &temperature, &pressure, &humidity) != ESP_OK)
        {
            ESP_LOGE("BMP280","Temperature/pressure reading failed\n");
            continue;
        }
        ESP_LOGI("BMP280", "Pressure: %.2f Pa, Temperature: %.2f C", pressure, temperature);
       
    }
}

void app_main(void)
{
    led_init();
    i2cdev_init();
    xTaskCreate(&blinking_task, "blinking_task", 2048, NULL, 5, NULL);
    xTaskCreate(&sensor_task, "sensor_task", 2048, NULL, 5, NULL);
}
