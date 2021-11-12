#include <iostream>
#include <string>
#include <clipp.h>
#include <LKCommandGenerator.h>

int main(int argc, char *argv[])
{
    using namespace clipp;
    using namespace LKCommandGenerator;

    command_frame frame;

    /*--------------------------------------
       HELP
    ---------------------------------------*/
    bool help_focus;
    auto help="Manual"%(
         command("-h","--help","man").set(help_focus)
    );


    /*--------------------------------------
        LED
    ---------------------------------------*/

    bool led_focus=false;
    bool led_ears_focus=false;
    bool led_belt_focus=false;
    bool led_all_target_focus=false;
    bool led_range_target_focus=false;
    frame_t led_first_target;
    frame_t led_last_target;
    frame_t led_single_target;
    std::vector<frame_t>rgb_ctrl_values{0,0,0};

    auto led_setup="Led setup"%(
      command("led").set(led_focus) %"Control led(s)",
      required("-e","--ears").set(led_ears_focus) %"Control ears leds of robot"|
      required("-b","--belt").set(led_belt_focus) %"Control belt leds of robot",
      option("-A","--all").set(led_all_target_focus) %"Control all leds of robot"|
      option("-R","--range").set(led_range_target_focus)%"Control a range of leds of robot" & integer("first target",led_first_target) & integer("last target",led_last_target)
            .if_missing([]{ std::cout << "You need to provide two targets!\n"; } ) |
      integer("target",led_single_target)
            .if_missing([]{ std::cout << "You need to provide one target!\n"; } ),
      integer("Red value",rgb_ctrl_values[0]) & integer("Green value",rgb_ctrl_values[1]) & integer("Blue value",rgb_ctrl_values[2])
            .if_missing([]{ std::cout << "You need to provide RGB values!\n"; } )%"Provide RGB value"|
      required("-r","red").set(rgb_ctrl_values[0],255)|required("-g","green").set(rgb_ctrl_values[1],255)|required("-b","blue").set(rgb_ctrl_values[2],255)
    );


      /*--------------------------------------
        MOTOR
      --------------------------------------*/

    bool motor_all_target=false;
    bool motor_duo_target=false;
    bool motor_left_target=false;
    bool motor_right_target=false;

    auto motor_setup="Motor setup"%(
      command("motor"),
      option("-A","--all").set(motor_all_target),
      option("-D","--duo").set(motor_duo_target),
      option("-l","--left").set(motor_left_target),
      option("-r","--right").set(motor_right_target)
    );


      /*--------------------------------------
        CLI
      --------------------------------------*/
    std::vector<std::string> wrong;
    auto cli=(
      help | led_setup | motor_setup,
      any_other(wrong) 
    );

    if(parse(argc, argv, cli)) {

      if(led_focus){
        if(led_ears_focus){
          if(led_all_target_focus){
            for(frame_t id : list_id_led_ears){
              frame.list_command_group.push_back({get_length_led_all(),get_id_command_led_ears_all(), id,rgb_ctrl_values});
            }

            for(command_group command : frame.list_command_group){
              std::cout << "\nR :" << command.ctrl_values[0];
              std::cout << "\nG :" << command.ctrl_values[1];
              std::cout << "\nB :" << command.ctrl_values[2];
              std::cout << "\n";
            }
          }
        }

      }
    std::cout << "\nCommand valid\n" << "\n";
    
    }
    else {
        std::cout << "\nCommand not valid\n" << "\n";
        for(const auto& arg : wrong) {
            std::cout << "'" << arg << "' is not a valid command line argument\n";
        }
        std::cout << "Usage:\n" << usage_lines(cli,argv[0]) << "\n";

        //std::cout << make_man_page(cli, argv[0]) << '\n';

    }
    
    return EXIT_SUCCESS;

}