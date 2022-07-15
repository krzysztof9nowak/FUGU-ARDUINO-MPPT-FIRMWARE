#pragma once

enum class mppt_error : int{
    OK = 0,
    OVERTEMPERATURE = 0x1,
    INPUT_OVERCURRENT = 0x2,
    OUTPUT_OVERCURRENT = 0x4,
    OUTPUT_OVERVOLTAGE = 0x8,
    FATALLY_LOW_VOLTAGE = 0x10,
    INPUT_UNDERVOLTAGE = 0x20,
    BATTERY_NOT_CONNECTED = 0x40,
};

inline constexpr mppt_error operator|(mppt_error x, mppt_error y){
    return static_cast<mppt_error>(static_cast<int>(x) | static_cast<int>(y));
}

inline constexpr mppt_error operator&(mppt_error x, mppt_error y){
    return static_cast<mppt_error>(static_cast<int>(x) & static_cast<int>(y));
}

inline mppt_error& operator|=(mppt_error & x, mppt_error y){
    x = x | y;
    return x;
}


void backflowControl();
mppt_error safety_checks();