#include <iostream>
#include <string>
#include <vector>

#include<CLI11.hpp>

int main(int argc, char *argv[])
{
    CLI::App lk_command_generator{"Leka Command Generator"};/*Adding an lk_command_generator*/

    lk_command_generator.require_subcommand(1);/*Requiring 1 subcommand to run*/


    /*--------------------------------------
        LED DEFINE
    ----------------------------------------*/

    auto led=lk_command_generator.add_subcommand("led","Control led(s)");

    std::vector<std::string>ears_leds_ctrls;
    led->add_option("-e,--ears",ears_leds_ctrls,"Control ears leds");

    std::vector<std::string>belt_leds_ctrls;
    led->add_option("-b,--belt",belt_leds_ctrls,"Control belt leds");

    led->callback([&](){
        if(ears_leds_ctrls.empty()) {
          std::cout << "\nNo parameters\n" <<  std::endl;
        } else {
            for(auto ctrl : ears_leds_ctrls)
                std::cout << " " << ctrl;
        }
        /*....*/
        
    });


      /*--------------------------------------
        MOTOR DEFINE
    ----------------------------------------*/

    auto motor=lk_command_generator.add_subcommand("motor","Control motor(s)");

    std::vector<std::string>motor_ctrls;
    motor->add_option("-M",motor_ctrls,"Control motor");


     motor->callback([&](){
        /*....*/
         std::cout << "\nMotor ON!\n" <<  std::endl;

    });


    /*--------------------------------------
        PARSE
    ----------------------------------------*/

     CLI11_PARSE(lk_command_generator, argc, argv);

    std::cout << "\nThanks for using Leka Coomand Generator!\n" <<  std::endl;



    
    return 0;

}