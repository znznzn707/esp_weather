#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <esp_log.h>

#include "wifi_sta.h"
#include "my_sntp.h"


static const char *s_pbyTag = "weather_main";

void time_task()
{
    time_t now = 0;
    struct tm timeinfo = {0};
    
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        obtain_time(&now, &timeinfo);

        ESP_LOGI(s_pbyTag, "now=%ld", now);
        ESP_LOGI(s_pbyTag, "year=%d, mon=%d, mday=%d, hour=%d, min=%d, sec=%d",
                 timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday,
                 timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    }
}

void app_main()
{

    ESP_LOGI(s_pbyTag, "app_main...\n");

    wifi_init_sta();
    sntp_initialize();

    xTaskCreate(time_task, "time_task", 2048, NULL, 10, NULL);
    
}