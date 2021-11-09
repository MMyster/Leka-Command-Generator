#include <iostream>
#include <string>
#include <vector>
#include <CLI11.hpp>
#include "include/LKCommandGenerator.h"

int main(int argc, char *argv[])
{
    CLI::App lk_command_generator{"Leka Command Generator"};/*Project name : lk_command_generator*/

    lk_command_generator.require_subcommand(1);/*Require 1 subcommand to run*/


    /*--------------------------------------
        LED DEFINE
    ----------------------------------------*/

    auto led=lk_command_generator.add_subcommand("led","Control led(s)");

    auto ears_led_ctrl=false;
    led->add_flag("-e,--ears",ears_led_ctrl,"Control ears leds");

    auto belt_led_ctrl=false;
    led->add_flag("-b,--belt",belt_led_ctrl,"Control belt leds");

   /*
    auto callback = [](int count){std::cout << "This was called " << count << " times";};
    led->add_flag_function("-c", callback, "Optional description");

    led->callback([&](){
        if(!ears_led_ctrl) {
          std::cout << "\nNo parameters\n" <<  std::endl;
        } else {
          std::cout << "\nEars ON\n" <<  std::endl;
       
        }
        
    });

*/
      /*--------------------------------------
        MOTOR DEFINE
    ----------------------------------------*/

    auto motor=lk_command_generator.add_subcommand("motor","Control motor(s)");

    
    std::vector<uint8_t>all_motor_ctrls;
    auto motor_all_opt=motor->add_option("-a,--all",all_motor_ctrls,"Control all motor features")
    ->expected(LKCommandGenerator::get_length_motor_all());

    std::vector<uint8_t>duo_motor_ctrls;
    auto motor_duo_opt=motor->add_option("-R,--range",duo_motor_ctrls,"Control both spins")
    ->expected(LKCommandGenerator::get_length_motor_duo());

    std::vector<uint8_t>left_motor_ctrls;
    auto motor_left_opt=motor->add_option("-l,--left",left_motor_ctrls,"Control the left spin")
    ->expected(LKCommandGenerator::get_length_motor_single());

    std::vector<uint8_t>right_motor_ctrls;
    auto motor_right_opt=motor->add_option("-r,--right",right_motor_ctrls,"Control the rigth spin")
    ->expected(LKCommandGenerator::get_length_motor_single());

    
    
    

    int v1;
    motor->add_option<int,int>("--vs",v1);


     motor->callback([&](){
        /*....*/
         std::cout << "\nMotor ON!\n" <<  std::endl;
         std::cout << v1 << std::endl;
         std::cout << typeid(v1).name() << std::endl;

    });


    /*--------------------------------------
        PARSE
    ----------------------------------------*/

     CLI11_PARSE(lk_command_generator, argc, argv);

    std::cout << "\nThanks for using Leka Coomand Generator!\n" <<  std::endl;



    
    return 0;

}