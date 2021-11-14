#include <LKCommandGenerator.h>
#include <LKAlphaComSpecs.h>





auto LKCommandGenerator::get_start_sequence()->frame_t* const
{
    return LKFrame::start::sequence;
}

auto LKCommandGenerator::get_id_command_led()->frame_t const
{
    return LKCommand::led::id;
}

auto LKCommandGenerator::get_id_command_led_ears_all()->frame_t const
{
    return LKCommand::led::ears::all;
}

auto LKCommandGenerator::get_id_command_led_ears_range()->frame_t const
{
    return LKCommand::led::ears::range;
}

auto LKCommandGenerator::get_id_command_led_ears_single()->frame_t const
{
    return LKCommand::led::ears::single;
}

auto LKCommandGenerator::get_id_command_led_belt_all()->frame_t const
{
    return LKCommand::led::belt::all;
}

auto LKCommandGenerator::get_id_command_led_belt_range()->frame_t const
{
    return LKCommand::led::belt::range;
}

auto LKCommandGenerator::get_id_command_led_belt_single()->frame_t const
{
    return LKCommand::led::belt::single;
}

auto LKCommandGenerator::get_length_led_all()->frame_t const
{
    return LKCommand::led::length::all;
}

auto LKCommandGenerator::get_length_led_range()->frame_t const
{
    return LKCommand::led::length::range;
}

auto LKCommandGenerator::get_length_led_single()->frame_t const
{
    return LKCommand::led::length::single;
}

auto LKCommandGenerator::get_id_command_motor()->frame_t const
{
    return LKCommand::motor::id;
}

auto LKCommandGenerator::get_id_command_motor_all()->frame_t const
{
    return LKCommand::motor::all;
}

auto LKCommandGenerator::get_id_command_motor_duo()->frame_t const
{
    return LKCommand::motor::duo;
}

auto LKCommandGenerator::get_id_command_motor_left()->frame_t const
{
    return LKCommand::motor::left;
}

auto LKCommandGenerator::get_id_command_motor_right()->frame_t const
{
    return LKCommand::motor::right;
}

auto LKCommandGenerator::get_length_motor_all()->frame_t const
{
    return LKCommand::motor::length::all;
}

auto LKCommandGenerator::get_length_motor_duo()->frame_t const
{
    return LKCommand::motor::length::duo;
}

auto LKCommandGenerator::get_length_motor_single()->frame_t const
{
    return LKCommand::motor::length::single;
}


