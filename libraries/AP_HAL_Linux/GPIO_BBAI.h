#pragma once

#include "AP_HAL_Linux.h"

#define SYSFS_GPIO_DIR "/sys/class/gpio"

//#define GPIO0_BASE 0x44E07000
//#define GPIO1_BASE 0x4804C000
//#define GPIO2_BASE 0x481AC000
//#define GPIO3_BASE 0x481AE000

#define GPIO1_BASE 0x4AE10000
#define GPIO2_BASE 0x48055000
#define GPIO3_BASE 0x48057000
#define GPIO4_BASE 0x48059000
#define GPIO5_BASE 0x4805B000
#define GPIO6_BASE 0x4805D000
#define GPIO7_BASE 0x48051000
#define GPIO8_BASE 0x48053000


#define GPIO_SIZE  0x00000FFF

// OE: 0 is output, 1 is input
#define GPIO_OE    0x14d
#define GPIO_IN    0x14e
#define GPIO_OUT   0x14f

#define LED_AMBER       178 // P9.9
#define LED_BLUE        164 // P9.10
#define LED_SAFETY      75  // P9.11
#define SAFETY_SWITCH   116
#define LOW             0
#define HIGH            1

#if CONFIG_HAL_BOARD_SUBTYPE == HAL_BOARD_SUBTYPE_LINUX_BBAI
#define LINUX_GPIO_NUM_BANKS 8
#else
// disable GPIO
#define LINUX_GPIO_NUM_BANKS 0
#endif

// BeagleBone AI GPIO mappings
#define BBB_USR0 81 //D2 Led - Heartbeat When Linux is Running
#define BBB_USR1 133 //D3 Led - microSD Activity
#define BBB_USR2 79 //D4 Led - CPU Activity
#define BBB_USR3 78 //D5 Led - eMMC Activity
#define BBB_USR4 71 //D6 Led - WiFi/Bluetooth Activity
#define BBB_P8_3 24
#define BBB_P8_4 25
#define BBB_P8_5 193
#define BBB_P8_6 194
#define BBB_P8_7 165
#define BBB_P8_8 166
#define BBB_P8_9 178
#define BBB_P8_10 164
#define BBB_P8_11 75
#define BBB_P8_12 74
#define BBB_P8_13 107
#define BBB_P8_14 109
#define BBB_P8_15 99
#define BBB_P8_16 125
#define BBB_P8_17 242
#define BBB_P8_18 105
#define BBB_P8_19 106
#define BBB_P8_20 190
#define BBB_P8_21 189
#define BBB_P8_22 23
#define BBB_P8_23 22
#define BBB_P8_24 192
#define BBB_P8_25 191
#define BBB_P8_26 124
#define BBB_P8_27 119
#define BBB_P8_28 115
#define BBB_P8_29 118
#define BBB_P8_30 116
#define BBB_P8_31 238
#define BBB_P8_32 239
#define BBB_P8_33 237
#define BBB_P8_34 235
#define BBB_P8_35 236
#define BBB_P8_36 234
#define BBB_P8_37 232
#define BBB_P8_38 233
#define BBB_P8_39 230
#define BBB_P8_40 231
#define BBB_P8_41 228
#define BBB_P8_42 229
#define BBB_P8_43 226
#define BBB_P8_44 227
#define BBB_P8_45 224
#define BBB_P8_46 225
#define BBB_P9_11 241
#define BBB_P9_12 128
#define BBB_P9_13 172
#define BBB_P9_14 121
#define BBB_P9_15 76
#define BBB_P9_16 122
#define BBB_P9_17 209
#define BBB_P9_18 208
#define BBB_P9_19 195
#define BBB_P9_20 196
#define BBB_P9_21 67
#define BBB_P9_22 179
#define BBB_P9_23 203
#define BBB_P9_24 175
#define BBB_P9_25 177
#define BBB_P9_26 174
#define BBB_P9_27 111
#define BBB_P9_28 113
#define BBB_P9_29 139
#define BBB_P9_30 140
#define BBB_P9_31 138
#define BBB_P9_41 180
#define BBB_P9_42 114

namespace Linux {

class GPIO_BBAI : public AP_HAL::GPIO {
private:
    struct GPIO {
        volatile uint32_t *base;
        volatile uint32_t *oe;
        volatile uint32_t *in;
        volatile uint32_t *out;
     } gpio_bank[LINUX_GPIO_NUM_BANKS];

public:
    GPIO_BBAI();
    void    init() override;
    void    pinMode(uint8_t pin, uint8_t output) override;
    uint8_t read(uint8_t pin) override;
    void    write(uint8_t pin, uint8_t value) override;
    void    toggle(uint8_t pin) override;

    /* Alternative interface: */
    AP_HAL::DigitalSource* channel(uint16_t n) override;

    /* return true if USB cable is connected */
    bool    usb_connected(void) override;
};

}
