// components/apps/clock/ClockApp.cpp

#include "ClockApp.hpp"
#include "esp_log.h"
#include <ctime>

static const char *TAG = "ClockApp";

LV_IMG_DECLARE(img_app_clock);
LV_FONT_DECLARE(digital_clock_font);

ClockApp::ClockApp() : ESP_Brookesia_PhoneApp("Clock", &img_app_clock, true)
{
}

ClockApp::~ClockApp() {}

bool ClockApp::init()
{
    ESP_LOGI(TAG, "ClockApp init");
    return true;
}

bool ClockApp::run()
{
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), 0);
    // Create a label to display the time
    time_label_ = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(time_label_, &digital_clock_font, 0);
    lv_obj_set_style_text_color(time_label_, lv_color_white(), 0);
    lv_label_set_text(time_label_, "00:00");
    lv_obj_align(time_label_, LV_ALIGN_CENTER, 0, 0);

    // Create a timer to update the time every second
    timer_ = lv_timer_create([](lv_timer_t *timer)
                             {
        ClockApp* app = static_cast<ClockApp*>(timer->user_data);
        app->updateTime(); }, 1000, this);

    return true;
}

bool ClockApp::back()
{
    ESP_LOGI(TAG, "ClockApp back");
    return close();
}

bool ClockApp::close()
{
    ESP_LOGI(TAG, "ClockApp close");
    if (timer_)
    {
        lv_timer_del(timer_);
        timer_ = nullptr;
    }
    if (time_label_)
    {
        lv_obj_del(time_label_);
        time_label_ = nullptr;
    }
    return true;
}

bool ClockApp::pause()
{
    ESP_LOGI(TAG, "ClockApp pause");
    if (timer_)
    {
        lv_timer_pause(timer_);
    }
    return true;
}

bool ClockApp::resume()
{
    ESP_LOGI(TAG, "ClockApp resume");
    if (timer_)
    {
        lv_timer_resume(timer_);
    }
    return true;
}

void ClockApp::updateTime()
{
    time_t now = time(nullptr);
    struct tm timeinfo;
    localtime_r(&now, &timeinfo);

    char buffer[9];
    strftime(buffer, sizeof(buffer), "%H:%M", &timeinfo);
    ESP_LOGI(TAG, "Time: %s", buffer);
    // Update the label text
    lv_label_set_text(time_label_, buffer);
}