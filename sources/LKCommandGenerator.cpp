#include <LKCommandGenerator.h>
#include <LKAlphaComSpecs.h>



using namespace LKCommandGenerator;

/*Led*/

auto command_group_led::get_id_command_led()->frame_t const
{
    return LKCommand::led::id;
}

auto command_group_led::get_id_command_led_ears_all()->frame_t const
{
    return LKCommand::led::ears::all;
}

auto command_group_led::get_id_command_led_ears_range()->frame_t const
{
    return LKCommand::led::ears::range;
}

auto command_group_led::get_id_command_led_ears_single()->frame_t const
{
    return LKCommand::led::ears::single;
}

auto command_group_led::get_id_command_led_belt_all()->frame_t const
{
    return LKCommand::led::belt::all;
}

auto command_group_led::get_id_command_led_belt_range()->frame_t const
{
    return LKCommand::led::belt::range;
}

auto command_group_led::get_id_command_led_belt_single()->frame_t const
{
    return LKCommand::led::belt::single;
}

auto command_group_led::get_length_led_all()->frame_t const
{
    return LKCommand::led::length::all;
}

auto command_group_led::get_length_led_range()->frame_t const
{
    return LKCommand::led::length::range;
}

auto command_group_led::get_length_led_single()->frame_t const
{
    return LKCommand::led::length::single;
}


/* Motor */

auto command_group_motor::get_id_command_motor()->frame_t const
{
    return LKCommand::motor::id;
}

auto command_group_motor::get_id_command_motor_all()->frame_t const
{
    return LKCommand::motor::all;
}

auto command_group_motor::get_id_command_motor_duo()->frame_t const
{
    return LKCommand::motor::duo;
}

auto command_group_motor::get_id_command_motor_left()->frame_t const
{
    return LKCommand::motor::left;
}

auto command_group_motor::get_id_command_motor_right()->frame_t const
{
    return LKCommand::motor::right;
}

auto command_group_motor::get_length_motor_all()->frame_t const
{
    return LKCommand::motor::length::all;
}

auto command_group_motor::get_length_motor_duo()->frame_t const
{
    return LKCommand::motor::length::duo;
}

auto command_group_motor::get_length_motor_single()->frame_t const
{
    return LKCommand::motor::length::single;
}

/* Frame */
auto Frame::get_start_sequence()->std::vector<frame_t> const
{
    std::vector<frame_t>start_sequence=std::vector<frame_t>(std::begin(LKFrame::start::sequence),std::end(LKFrame::start::sequence));
    return start_sequence;
}


