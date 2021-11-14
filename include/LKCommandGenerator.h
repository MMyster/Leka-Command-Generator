#ifndef _LEKA_COMMAND_GENERATOR_H_
#define _LEKA_COMMAND_GENERATOR_H_

#include <array>
#include <list>
#include <vector>
#include <string>

using frame_t = uint8_t;

namespace LKCommandGenerator{

const frame_t list_id_led_belt[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13};
const frame_t list_id_led_ears[]={0x00,0x01};



struct command_group
{
    frame_t length;
    frame_t id_command;
    std::vector<frame_t>ctrl_values;

};


struct command_group_led : command_group
{
    frame_t id_target;

    command_group_led(frame_t length,frame_t id_command,frame_t id_target,std::vector<frame_t>rgb_ctrl_values){
        this->length=length;
        this->id_command=id_command;
        this->id_target=id_target;
        this->ctrl_values=rgb_ctrl_values;
    }

};

struct command_group_motor : command_group
{

    command_group_motor(frame_t length,frame_t id_command,std::vector<frame_t>ctrl_values){
        this->length=length;
        this->id_command=id_command;
        this->ctrl_values=ctrl_values;
    }

};


/* N.B :*/


struct command_frame
{
    frame_t length;
    const frame_t command_frame_length_min=7;
    const frame_t command_frame_length_max=128;
    const std::vector<frame_t>start_sequence;
    std::vector<command_group>list_command_group;
    frame_t checksum;
};


auto calculate_checksum(command_frame frame)->frame_t;


auto get_start_sequence()->frame_t* const;

/*Led*/
auto get_id_command_led()->frame_t const;

auto get_id_command_led_ears_all()->frame_t const;

auto get_id_command_led_ears_range()->frame_t const;

auto get_id_command_led_ears_single()->frame_t const;

auto get_id_command_led_belt_all()->frame_t const;

auto get_id_command_led_belt_range()->frame_t const;

auto get_id_command_led_belt_single()->frame_t const;

auto get_length_led_all()->frame_t const;

auto get_length_led_range()->frame_t const;

auto get_length_led_single()->frame_t const;


/*Motor*/
auto get_id_command_motor()->frame_t const;

auto get_id_command_motor_all()->frame_t const;

auto get_id_command_motor_duo()->frame_t const;

auto get_id_command_motor_left()->frame_t const;

auto get_id_command_motor_right()->frame_t const;

auto get_length_motor_all()->frame_t const;

auto get_length_motor_duo()->frame_t const;

auto get_length_motor_single()->frame_t const;
    
}

#endif