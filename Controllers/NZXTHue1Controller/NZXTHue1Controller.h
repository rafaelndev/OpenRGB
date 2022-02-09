/*---------------------------------------------------------*\
|  Definitions for NZXT Hue 1 (Smart Device V1)             |
|                                                           |
|  Adam Honse (calcprogrammer1@gmail.com), 2/8/2022         |
\*---------------------------------------------------------*/

#include "RGBController.h"
#include <string>
#include <vector>
#include <hidapi/hidapi.h>

#pragma once

enum
{
    HUE_1_CHANNEL_ALL       = 0x00,     /* All channels                 */
    HUE_1_CHANNEL_1         = 0x01,     /* Channel 1                    */
    HUE_1_CHANNEL_2         = 0x02,     /* Channel 2                    */
    HUE_1_CHANNEL_3         = 0x03,     /* Channel 3                    */
    HUE_1_CHANNEL_4         = 0x04,     /* Channel 4                    */
    HUE_1_NUM_CHANNELS      = 0x04      /* Number of channels           */
};

enum
{
    HUE_1_CHANNEL_1_IDX     = 0x00,     /* Channel 1 array index        */
    HUE_1_CHANNEL_2_IDX     = 0x01,     /* Channel 2 array index        */
    HUE_1_CHANNEL_3_IDX     = 0x01,     /* Channel 3 array index        */
    HUE_1_CHANNEL_4_IDX     = 0x01,     /* Channel 4 array index        */
};

enum
{
    HUE_1_SPEED_SLOWEST         = 0x00,     /* Slowest speed                */
    HUE_1_SPEED_SLOW            = 0x01,     /* Slow speed                   */
    HUE_1_SPEED_NORMAL          = 0x02,     /* Normal speed                 */
    HUE_1_SPEED_FAST            = 0x03,     /* Fast speed                   */
    HUE_1_SPEED_FASTEST         = 0x04,     /* Fastest speed                */
};

enum
{
    HUE_1_MODE_FIXED            = 0x00,     /* Fixed colors mode            */
    HUE_1_MODE_FADING           = 0x01,     /* Fading mode                  */
    HUE_1_MODE_SPECTRUM         = 0x02,     /* Spectrum cycle mode          */
    HUE_1_MODE_MARQUEE          = 0x03,     /* Marquee mode                 */
    HUE_1_MODE_COVER_MARQUEE    = 0x04,     /* Cover marquee mode           */
    HUE_1_MODE_ALTERNATING      = 0x05,     /* Alternating mode             */
    HUE_1_MODE_BREATHING        = 0x06,     /* Breathing mode               */
    HUE_1_MODE_PULSING          = 0x07,     /* Pulsing mode                 */
};

class NZXTHue1Controller
{
public:
    NZXTHue1Controller(hid_device* dev_handle, unsigned int rgb_channels, unsigned int fan_channels, const char* path);
    ~NZXTHue1Controller();

    std::string     GetFirmwareVersion();
    std::string     GetLocation();
    std::string     GetSerialString();

    unsigned char   GetFanCommand
                        (
                        unsigned char   fan_channel
                        );

    unsigned short  GetFanRPM
                        (
                        unsigned char   fan_channel
                        );

    unsigned int    GetNumFanChannels();

    unsigned int    GetNumRGBChannels();

    void            SendFan
                        (
                            unsigned char       port,
                            unsigned char       mode,
                            unsigned char       speed
                        );

    void            SetChannelEffect
                        (
                        unsigned char   channel,
                        unsigned char   mode,
                        unsigned char   speed,
                        bool            direction,
                        RGBColor *      colors,
                        unsigned int    num_colors
                        );

    void            SetChannelLEDs
                        (
                        unsigned char   channel,
                        RGBColor *      colors,
                        unsigned int    num_colors
                        );

    void            UpdateDeviceList();

    void            UpdateStatus();
    
    unsigned int    channel_leds[HUE_1_NUM_CHANNELS];

private:
    hid_device*     dev;
    
    std::vector<unsigned char>  fan_cmd;
    std::vector<unsigned short> fan_rpm;

    char            firmware_version[16];
    std::string     location;
    unsigned int    num_fan_channels;
    unsigned int    num_rgb_channels;

    void            SendPacket
                        (
                        unsigned char   channel,
                        unsigned char   mode,
                        bool            direction,
                        unsigned char   color_idx,
                        unsigned char   speed,
                        unsigned char   color_count,
                        unsigned char*  color_data
                        );

    void            SendFirmwareRequest();
};
