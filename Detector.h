#pragma once

#include "DeviceDetector.h"

#define REGISTER_DETECTOR(name, func)                                            static DeviceDetector    device_detector_obj_##func(name, func)
#define REGISTER_I2C_DETECTOR(name, func)                                        static I2CDeviceDetector device_detector_obj_##func(name, func)
#define REGISTER_I2C_BUS_DETECTOR(func)                                          static I2CBusDetector    device_detector_obj_##func(func)
#define REGISTER_HID_DETECTOR(name, func, vid, pid)                              static HIDDeviceDetector device_detector_obj_##vid##pid(name, func, vid, pid, HID_INTERFACE_ANY, HID_USAGE_PAGE_ANY, HID_USAGE_ANY)
#define REGISTER_HID_DETECTOR_I(name, func, vid, pid, interface)                 static HIDDeviceDetector device_detector_obj_##vid##pid##_##interface(name, func, vid, pid, interface, HID_USAGE_PAGE_ANY, HID_USAGE_ANY)
#define REGISTER_HID_DETECTOR_IP(name, func, vid, pid, interface, page)          static HIDDeviceDetector device_detector_obj_##vid##pid##_##interface##_##page(name, func, vid, pid, interface, page, HID_USAGE_ANY)
#define REGISTER_HID_DETECTOR_IPU(name, func, vid, pid, interface, page, usage)  static HIDDeviceDetector device_detector_obj_##vid##pid##_##interface##_##page##_##usage(name, func, vid, pid, interface, page, usage)
#define REGISTER_HID_DETECTOR_P(name, func, vid, pid, page)                      static HIDDeviceDetector device_detector_obj_##vid##pid##__##page(name, func, vid, pid, HID_INTERFACE_ANY, page, HID_USAGE_ANY)
#define REGISTER_HID_DETECTOR_PU(name, func, vid, pid, page, usage)              static HIDDeviceDetector device_detector_obj_##vid##pid##__##page##_##usage(name, func, vid, pid, HID_INTERFACE_ANY, page, usage)
#define REGISTER_DYNAMIC_DETECTOR(name, func)                                    static DynamicDetector   device_detector_obj_##func(name, func)
#define REGISTER_PRE_DETECTION_HOOK(func)                                        static PreDetectionHook  device_detector_obj_##func(func)

#define REGISTER_DYNAMIC_I2C_DETECTOR(name, func)                                       I2CDeviceDetector device_detector_obj_##func(name, func)
#define REGISTER_DYNAMIC_I2C_BUS_DETECTOR(func)                                         I2CBusDetector    device_detector_obj_##func(func)
#define REGISTER_DYNAMIC_HID_DETECTOR(name, func, vid, pid)                             HIDDeviceDetector device_detector_obj_##vid##pid(name, func, vid, pid, HID_INTERFACE_ANY, HID_USAGE_PAGE_ANY, HID_USAGE_ANY)
#define REGISTER_DYNAMIC_HID_DETECTOR_I(name, func, vid, pid, interface)                HIDDeviceDetector device_detector_obj_##vid##pid##_##interface(name, func, vid, pid, interface, HID_USAGE_PAGE_ANY, HID_USAGE_ANY)
#define REGISTER_DYNAMIC_HID_DETECTOR_IP(name, func, vid, pid, interface, page)         HIDDeviceDetector device_detector_obj_##vid##pid##_##interface##_##page(name, func, vid, pid, interface, page, HID_USAGE_ANY)
#define REGISTER_DYNAMIC_HID_DETECTOR_IPU(name, func, vid, pid, interface, page, usage) HIDDeviceDetector device_detector_obj_##vid##pid##_##interface##_##page##_##usage(name, func, vid, pid, interface, page, usage)
#define REGISTER_DYNAMIC_HID_DETECTOR_P(name, func, vid, pid, page)                     HIDDeviceDetector device_detector_obj_##vid##pid##__##page(name, func, vid, pid, HID_INTERFACE_ANY, page, HID_USAGE_ANY)
#define REGISTER_DYNAMIC_HID_DETECTOR_PU(name, func, vid, pid, page, usage)             HIDDeviceDetector device_detector_obj_##vid##pid##__##page##_##usage(name, func, vid, pid, HID_INTERFACE_ANY, page, usage)
