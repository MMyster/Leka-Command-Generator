#include <LKCommandGenerator.h>



auto LKCommandGenerator::get_id_command_led()->frame_t
{
    return LKCommand::led::id;
}

auto LKCommandGenerator::get_id_command_led_ears_all()->frame_t
{
    return LKCommand::led::ears::all;
}

auto LKCommandGenerator::get_id_command_led_ears_range()->frame_t
{
    return LKCommand::led::ears::range;
}

auto LKCommandGenerator::get_id_command_led_ears_single()->frame_t
{
    return LKCommand::led::ears::single;
}

auto LKCommandGenerator::get_id_command_led_belt_all()->frame_t
{
    return LKCommand::led::belt::all;
}

auto LKCommandGenerator::get_id_command_led_belt_range()->frame_t
{
    return LKCommand::led::belt::range;
}

auto LKCommandGenerator::get_id_command_led_belt_single()->frame_t
{
    return LKCommand::led::belt::single;
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

auto get_id_command_motor()->frame_t
{
    return LKCommand::motor::id;
}

auto get_id_command_motor_all()->frame_t
{
    return LKCommand::motor::all;
}

auto get_id_command_motor_duo()->frame_t
{
    return LKCommand::motor::duo;
}

auto get_id_command_motor_left()->frame_t
{
    return LKCommand::motor::left;
}

auto get_id_command_motor_right()->frame_t
{
    return LKCommand::motor::right;
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


