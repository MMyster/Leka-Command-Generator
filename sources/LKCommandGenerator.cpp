#include "../include/LKCommandGenerator.h"
#include "../include/LKAlphaComSpecs.h"




auto create_command_group(std::vector<uint8_t>,const std::size_t length)->std::array<frame_t,10>
{
    std::array<frame_t,10>command_group;

    return command_group;

}

auto LKCommandGenerator::get_length_led_all()->frame_t
{
    return LKCommand::led::length::all;
}

auto LKCommandGenerator::get_length_led_range()->frame_t
{
    return LKCommand::led::length::range;
}

auto LKCommandGenerator::get_length_led_single()->frame_t
{
    return LKCommand::led::length::single;
}

auto LKCommandGenerator::get_length_motor_all()->frame_t
{
    return LKCommand::motor::length::all;
}

auto LKCommandGenerator::get_length_motor_duo()->frame_t
{
    return LKCommand::motor::length::duo;
}

auto LKCommandGenerator::get_length_motor_single()->frame_t
{
    return LKCommand::motor::length::single;
}


