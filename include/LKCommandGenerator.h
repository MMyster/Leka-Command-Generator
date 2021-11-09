#ifndef _LEKA_COMMAND_GENERATOR_H_
#define _LEKA_COMMAND_GENERATOR_H_


#include <array>
#include <vector>
#include <string>

using frame_t = uint8_t;

namespace LKCommandGenerator{

auto create_command_group(std::vector<std::string>,const std::size_t length)->std::array<frame_t,10>;

auto get_length_led_all()->frame_t;

auto get_length_led_range()->frame_t;

auto get_length_led_single()->frame_t;

auto get_length_motor_all()->frame_t;

auto get_length_motor_duo()->frame_t;

auto get_length_motor_single()->frame_t;
    
    
}

#endif