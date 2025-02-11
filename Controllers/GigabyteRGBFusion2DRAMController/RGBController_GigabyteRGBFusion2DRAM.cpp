/*-----------------------------------------*\
|  GigabyteRGBController_RGBFusion2DRAM.cpp |
|                                           |
|  Generic RGB Interface for OpenRGB        |
|  Gigabyte RGB Fusion 2 DRAM Driver        |
|                                           |
|  Adam Honse (CalcProgrammer1) 6/7/2020    |
\*-----------------------------------------*/

#include "RGBController_GigabyteRGBFusion2DRAM.h"

RGBController_RGBFusion2DRAM::RGBController_RGBFusion2DRAM(RGBFusion2DRAMController* controller_ptr)
{
    controller  = controller_ptr;

    name        = "RGB Fusion 2 DRAM";
    vendor      = "Gigabyte";
    description = "RGB Fusion 2 DRAM Device";
    location    = controller->GetDeviceLocation();

    type = DEVICE_TYPE_DRAM;

    mode Static;
    Static.name       = "Static";
    Static.value      = 1;
    Static.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Static.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Static);

    SetupZones();
}

RGBController_RGBFusion2DRAM::~RGBController_RGBFusion2DRAM()
{
    delete controller;
}

void RGBController_RGBFusion2DRAM::SetupZones()
{
    /*---------------------------------------------------------*\
    | Search through all LEDs and create zones for each channel |
    | type                                                      |
    \*---------------------------------------------------------*/
    zone* new_zone = new zone();

    // Set zone name to channel name
    new_zone->name          = "DRAM Zone";
    new_zone->leds_min      = 1;
    new_zone->leds_max      = 1;
    new_zone->leds_count    = 1;

    // Push new zone to zones vector
    zones.push_back(*new_zone);

    led* new_led = new led();
    new_led->name           = "DRAM LED";

    // Push new LED to LEDs vector
    leds.push_back(*new_led);

    SetupColors();
}

void RGBController_RGBFusion2DRAM::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_RGBFusion2DRAM::DeviceUpdateLEDs()
{
    RGBColor      color = colors[0];
    unsigned char red   = RGBGetRValue(color);
    unsigned char grn   = RGBGetGValue(color);
    unsigned char blu   = RGBGetBValue(color);

    int mode = modes[active_mode].value;
    unsigned int speed = modes[active_mode].speed;

    controller->SetLEDEffect(0, mode, speed, red, grn, blu);

    controller->Apply();
}

void RGBController_RGBFusion2DRAM::UpdateZoneLEDs(int /*zone*/)
{
    UpdateLEDs();
}

void RGBController_RGBFusion2DRAM::UpdateSingleLED(int /*led*/)
{
    UpdateLEDs();
}

void RGBController_RGBFusion2DRAM::SetCustomMode()
{

}

void RGBController_RGBFusion2DRAM::DeviceUpdateMode()
{

}

