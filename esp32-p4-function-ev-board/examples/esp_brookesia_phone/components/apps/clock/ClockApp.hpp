// ClockApp.hpp

#pragma once

#include "esp_brookesia.hpp"
#include "lvgl.h"

class ClockApp : public ESP_Brookesia_PhoneApp {
public:
    ClockApp();
    virtual ~ClockApp();

    // Overridden methods
    virtual bool init(void) override;
    virtual bool run(void);
    virtual bool back(void);
    virtual bool close(void);
    virtual bool pause(void) override;
    virtual bool resume(void) override;

private:
    void updateTime();
    lv_obj_t* time_label_;
    lv_timer_t* timer_;
};