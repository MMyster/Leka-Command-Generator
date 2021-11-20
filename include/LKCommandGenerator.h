#ifndef _LEKA_COMMAND_GENERATOR_H_
#define _LEKA_COMMAND_GENERATOR_H_

#include <array>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using frame_t = uint8_t;

namespace LKCommandGenerator{


class command_group
{
    protected :

    frame_t length;
    frame_t id_command;
    std::vector<frame_t>ctrl_values;

    public:

    command_group();
    /**
     * command_group 
     * 
     * @param  {frame_t} id_command : 
     */
    command_group(frame_t id_command);

    ~command_group();
   
    /**
     * get command group Id
     * @return {frame_t}  : 
     */
    auto get_id_command()->frame_t;

    /**
     * get control values
     * @return {std::vector<frame_t>}  : 
     */
    auto get_ctrl_values()->std::vector<frame_t>;
    
    /**
     * update data from command group
     * @return {void}  : 
     */
    auto update_crtl_values()->void;

};


class command_group_led : public command_group
{
    private:

    enum class part{ears,belt} selected_part;
    enum class scope{single,range,all} selected_scope;
    std::vector<frame_t>targets;
    frame_t red_value;
    frame_t green_value;
    frame_t blue_value;

    static const std::vector<frame_t> list_id_led_belt;
    static const std::vector<frame_t> list_id_led_ears;


    public :

    command_group_led();

    command_group_led(frame_t red_value,frame_t green_value,frame_t blue_value,int part=0,std::vector<frame_t>targets={});

    command_group_led(frame_t red_value,frame_t green_value,frame_t blue_value,int part,frame_t first_target,frame_t last_target);
    /**
     * set robot part
     * @param  {int} param : 
     * @return {void}      : 
     */
    auto set_part(int param)->void;

    /**
     * set the target scope
     * @param  {int} param : 
     * @return {auto}      : 
     */
    auto set_scope(int param)->void;

    /**
     * update list of targets
     * @param  {std::vector<frame_t>targets} undefined : 
     * @return {std::vector<frame_t>}                                  : 
     */
    auto update_targets(std::vector<frame_t>targets)->std::vector<frame_t>;

    /**
     * update list of targets from a range
     * @param  {frame_t} first_target : 
     * @param  {frame_t} last_target  : 
     * @return {update list of targets}                 : 
     */
    auto update_range_targets(frame_t first_target,frame_t last_target)->std::vector<frame_t>;

    /**
     * update list of targets by set all the targets
     * @return {update list of targets}  : 
     */
    auto update_all_targets()->std::vector<frame_t>;
    
    /**
     * update command group id
     * @return {void}  : 
     */
    auto update_id_command()->void;
    
    /**
     * update data from command group
     * @return {void}  : 
     */
    auto update_crtl_values()->void;

    /**
     * Disply list of all availables targets
     * @return {void}  : 
     */
    static auto display_list_targets()->void;
    
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


};

class command_group_motor : public command_group
{
    private:
    enum class scope{left,right,duo,all}selected_scope;
    frame_t left_spin;
    frame_t right_spin;
    frame_t left_speed;
    frame_t right_speed;

    public : 

    command_group_motor(frame_t left_spin,frame_t left_speed,frame_t right_spin,frame_t right_speed,int scope=2);
    /**
     * set the target scope
     * @param  {int} param : 
     * @return {void}      : 
     */
    auto set_scope(int param)->void;

    /**
     * update command group id
     * @return {void}  : 
     */
    auto update_id_command()->void;

    /**
     * update data from command group
     * @return {void}  : 
     */
    auto update_crtl_values()->void;

    auto get_id_command_motor()->frame_t const;

    auto get_id_command_motor_all()->frame_t const;

    auto get_id_command_motor_duo()->frame_t const;

    auto get_id_command_motor_left()->frame_t const;

    auto get_id_command_motor_right()->frame_t const;

    auto get_length_motor_all()->frame_t const;

    auto get_length_motor_duo()->frame_t const;

    auto get_length_motor_single()->frame_t const;

};


/* N.B :*/


class Frame
{
    private :

    //const std::vector<frame_t>start_sequence=std::vector<frame_t>(get_start_sequence().begin(),get_start_sequence().end());
    const std::vector<frame_t>start_sequence={0x2A, 0x2B, 0x2C, 0x2D};
    frame_t length;
    const frame_t command_frame_length_min=7;
    const frame_t command_frame_length_max=128;
    std::vector<frame_t>data;
    std::vector<frame_t>packet;
    frame_t checksum; 

    frame_t packet_size;

    public :

    Frame();
    
    Frame(std::vector<frame_t>data);
    /**
     * Start sequence
     * @return {std::vector<frame_t>}  : 
     */
    auto get_start_sequence()->std::vector<frame_t> const;

    /**
     * Get payload data of the packet
     * @return {std::vector<frame_t>}  : 
     */
    auto get_data()->std::vector<frame_t>;
    
    /**
     * Set payload data of the packet
     * @param  {std::vector<frame_t>list} undefined : 
     * @return {void}                               : 
     */
    auto set_data(std::vector<frame_t>list)->void;

    /**
     * add frame list to data
     * @param  {std::vector<frame_t>list} undefined : 
     * @return {void}                               : 
     */
    auto add_data(std::vector<frame_t>list)->void;

    /**
     * Calculate length of the group command
     * @return {frame_t}  : 
     */
    auto calculate_length()->frame_t;
    
    /**
     * Calculate size of the packet
     * @return {frame_t}  : 
     */
    auto calculate_packet_size()->frame_t;

    /**
     * Calculate checksum of the packet payload data
     * @return {frame_t}  : 
     */
    auto calculate_checksum()->frame_t;

    /**
     * Make and return packet
     * @return {std::vector<frame_t>}  : 
     */
    auto make_packet()->std::vector<frame_t>;

    /**
     * Display the packet
     * @return {auto}  : 
     */
    auto display_packet()->void;

    /**
     * Send the packet to Leka (Soon)
     * @return {auto}  : 
     */
    auto send_packet()->void;

};


    
}

#endif