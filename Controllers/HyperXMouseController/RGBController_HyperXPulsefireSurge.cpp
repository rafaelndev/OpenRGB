/*-----------------------------------------*\
|  RGBController_HyperXPulsefireSurge.cpp   |
|                                           |
|  Generic RGB Interface for HyperX         |
|  Pulsefire Surge                          |
|                                           |
|  Adam Honse (CalcProgrammer1) 2/2/2020    |
\*-----------------------------------------*/

#include "RGBController_HyperXPulsefireSurge.h"

using namespace std::chrono_literals;

RGBController_HyperXPulsefireSurge::RGBController_HyperXPulsefireSurge(HyperXPulsefireSurgeController* controller_ptr)
{
    controller  = controller_ptr;

    name        = "HyperX Pulsefire Surge Device";
    vendor      = "HyperX";
    type        = DEVICE_TYPE_MOUSE;
    description = "HyperX Pulsefire Surge Device";
    location    = controller->GetDeviceLocation();
    serial      = controller->GetSerialString();

    mode Direct;
    Direct.name = "Direct";
    Direct.value = 0xFFFF;
    Direct.flags = MODE_FLAG_HAS_PER_LED_COLOR;
    Direct.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Direct);

    SetupZones();

    /*-----------------------------------------------------*\
    | The Corsair Lighting Node Pro requires a packet within|
    | 20 seconds of sending the lighting change in order    |
    | to not revert back into rainbow mode.  Start a thread |
    | to continuously send a keepalive packet every 5s      |
    \*-----------------------------------------------------*/
    keepalive_thread_run = 1;
    keepalive_thread = new std::thread(&RGBController_HyperXPulsefireSurge::KeepaliveThread, this);
};

RGBController_HyperXPulsefireSurge::~RGBController_HyperXPulsefireSurge()
{
    keepalive_thread_run = 0;
    keepalive_thread->join();
    delete keepalive_thread;

    delete controller;
}

void RGBController_HyperXPulsefireSurge::SetupZones()
{
    zone led_strip;
    led_strip.name       = "LED Strip";
    led_strip.type       = ZONE_TYPE_LINEAR;
    led_strip.leds_min   = 32;
    led_strip.leds_max   = 32;
    led_strip.leds_count = 32;
    led_strip.matrix_map = NULL;
    zones.push_back(led_strip);

    zone logo;
    logo.name       = "Logo";
    logo.type       = ZONE_TYPE_SINGLE;
    logo.leds_min   = 1;
    logo.leds_max   = 1;
    logo.leds_count = 1;
    logo.matrix_map = NULL;
    zones.push_back(logo);

    for(unsigned int zone_idx = 0; zone_idx < zones.size(); zone_idx++)
    {
        for(unsigned int led_idx = 0; led_idx < zones[zone_idx].leds_count; led_idx++)
        {
            led new_led;
            
            new_led.name = zones[zone_idx].name;

            if(zones[zone_idx].leds_count > 1)
            {
                new_led.name.append(" LED ");
                new_led.name.append(std::to_string(led_idx + 1));
            }  

            leds.push_back(new_led);
        }
    }

    SetupColors();
}

void RGBController_HyperXPulsefireSurge::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_HyperXPulsefireSurge::DeviceUpdateLEDs()
{
    last_update_time = std::chrono::steady_clock::now();

    if(active_mode == 0)
    {
        controller->SendDirect(&colors[0]);
    }
    else
    {
    }

}

void RGBController_HyperXPulsefireSurge::UpdateZoneLEDs(int /*zone*/)
{
    DeviceUpdateLEDs();
}

void RGBController_HyperXPulsefireSurge::UpdateSingleLED(int /*led*/)
{
    DeviceUpdateLEDs();
}

void RGBController_HyperXPulsefireSurge::SetCustomMode()
{
    active_mode = 0;
}

void RGBController_HyperXPulsefireSurge::DeviceUpdateMode()
{
    DeviceUpdateLEDs();
}

void RGBController_HyperXPulsefireSurge::KeepaliveThread()
{
    while(keepalive_thread_run.load())
    {
        if(active_mode == 0)
        {
            if((std::chrono::steady_clock::now() - last_update_time) > std::chrono::milliseconds(50))
            {
                UpdateLEDs();
            }
        }
        std::this_thread::sleep_for(10ms);
    }
}
