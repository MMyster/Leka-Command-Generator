#include <iostream>
#include <string>
#include <clipp.h>
#include <LKCommandGenerator.h>

int main(int argc, char *argv[])
{

    using namespace clipp;
    using namespace LKCommandGenerator;


    enum class command_focus { none, help, led, motor};
    command_focus selected = command_focus::none;

    command_frame frame;

    /*--------------------------------------
       HELP
    ---------------------------------------*/
    auto help="Manual"%(
         command("-h","--help","man").set(selected,command_focus::help)
    );


    /*--------------------------------------
        LED
    ---------------------------------------*/

    bool led_ears_focus=false;
    bool led_belt_focus=false;
    bool led_all_target_focus=false;
    bool led_range_target_focus=false;
    int led_first_target=0;
    int led_last_target=0;
    int led_single_target=1;
    std::vector<int> rgb_ctrl_values;

      std::cout << "\nTarget :" << led_single_target << std::endl;
      for(int i : rgb_ctrl_values){
         std::cout << "\nRGB :" << i << std::endl;
      }
    

    auto led_setup="Led setup"%(
      command("led").set(selected,command_focus::led) %"Control led(s)",
      required("-e","--ears").set(led_ears_focus) %"Control ears leds of robot"|
      required("-b","--belt").set(led_belt_focus) %"Control belt leds of robot",
      option("-A","--all").set(led_all_target_focus) %"Control all leds of robot"|
      option("-R","--range").set(led_range_target_focus)%"Control a range of leds of robot" & integer("first target",led_first_target) & integer("last target",led_last_target)
            .if_missing([]{ std::cout << "You need to provide two targets!\n"; } ) |
      integer("target",led_single_target)
            .if_missing([]{ std::cout << "You need to provide one target!\n"; } ),
     option("-V","--values","") & integer("Red value",rgb_ctrl_values) & integer("Green value",rgb_ctrl_values) & integer("Blue value",rgb_ctrl_values)
            .if_missing([]{ std::cout << "You need to provide RGB values!\n"; } ) %"Provide RGB values"
            /*|
            required("-r","red").set(rgb_ctrl_values[0],255)%"set Red value"|
            required("-g","green").set(rgb_ctrl_values[1],255)%"set Green value"|
            required("-b","blue").set(rgb_ctrl_values[2],255)%"set Blue value"*/
    );


      /*--------------------------------------
        MOTOR
      --------------------------------------*/

    bool motor_all_target_focus=false;
    bool motor_duo_target_focus=false;
    bool motor_left_target_focus=false;
    bool motor_right_target_focus=false;
    std::vector<int> motor_ctrl_values;

    auto motor_setup="Motor setup"%(
      command("motor").set(selected,command_focus::motor)%"Control motor features",
      (option("-A","--all").set(motor_all_target_focus) & integer("Direction",motor_ctrl_values[0]) & integer("Speed",motor_ctrl_values[1]))%"Give same instructions towards both wheels"|
      (option("-D","--duo").set(motor_duo_target_focus)  & integer("Left Spin",motor_ctrl_values) & integer("Left Speed",motor_ctrl_values)  
                                                  & integer("Right Spin",motor_ctrl_values) & integer("Right Speed",motor_ctrl_values))%"Give instructions for each wheel"|
      (option("-l","--left").set(motor_left_target_focus) & integer("Left Spin",motor_ctrl_values) & integer("Left Speed",motor_ctrl_values))%"Give instructions towards left wheel" |
      (option("-r","--right").set(motor_right_target_focus) & integer("Left Spin",motor_ctrl_values) & integer("Left Speed",motor_ctrl_values) )%"Give instructions towards right wheel" 
    );


      /*--------------------------------------
        CLI
      --------------------------------------*/
    std::vector<std::string> wrong;
    auto cli=(
      help | led_setup | motor_setup,
      any_other(wrong) 
    );


      /*--------------------------------------
        PARSER
      --------------------------------------*/
    auto res=parse(argc,argv,cli);
    if(res) {

          std::cout << "\nTarget :" << led_single_target << std::endl;
      for(int i : rgb_ctrl_values){
         std::cout << "\nRGB :" << i << std::endl;
      }

      switch (selected)
      {
      case command_focus::help :
      {
      auto fmt = doc_formatting{}.doc_column(31).last_column(80);
      std::cout << make_man_page(cli, argv[0],fmt) << '\n';
      break;
      }

      case command_focus::led :
      {
            
            if(led_ears_focus){
              if(led_all_target_focus){
                for(int id : list_id_led_ears){
                  // frame.list_command_group.push_back({get_id_command_led_ears_all(),get_length_led_all(), id,ctrl_values});
                }

                for(command_group command : frame.list_command_group){
                  std::cout << "\nR :" << command.ctrl_values[0] << std::endl;
                  std::cout << "\nG :" << command.ctrl_values[1] << std::endl;
                  std::cout << "\nB :" << command.ctrl_values[2] << std::endl;
                  std::cout << "\n";
                }
              }
              else if(led_range_target_focus){
                /*...*/
              }
              else{
                if(std::find(std::begin(list_id_led_ears), std::end(list_id_led_ears), led_single_target) != std::end(list_id_led_ears)){
                  //frame.list_command_group.push_back({get_length_led_all(),get_id_command_led_ears_all(),static_cast<frame_t>(led_single_target),ctrl_values});
                  for(command_group command : frame.list_command_group){
                    std::cout << "\nR : " << command.ctrl_values[0]  << std::endl;
                    std::cout << "\nG : " << command.ctrl_values[1] << std::endl;
                    std::cout << "\nB : " << command.ctrl_values[2] << std::endl;
                    std::cout << "\n";
                  }
                }
                else{
                  std::cout << "\nThis target don't exist\n" << "\n";
                }
              }
            }


      break;
      }
      case command_focus::motor:
      {
        if(motor_all_target_focus){

        }
      break;
      }
      default:
      break;
      }


    std::cout << "\nCommand valid\n" << "\n";
    
    }
    else {
        std::cout << "\nCommand not valid\n" << "\n";
        for(const auto& arg : wrong) {
            std::cout << "'" << arg << "' is not a valid command line argument\n";
        }
        if(res.unmapped_args_count()) { /* ... */ }
        if(res.any_bad_repeat()) { /* ... */ }
        if(res.any_blocked())    { /* ... */ }
        if(res.any_conflict())   { /* ... */ }

        for(const auto& m : res.missing()) { 
            std::cout << "missing " << m.param() << " after index " << m.after_index() << '\n';
        }

        //per-argument mapping
        for(const auto& m : res) {
            std::cout << m.index() << ": " << m.arg() << " -> " << m.param();
            std::cout << " repeat #" << m.repeat();
            if(m.blocked()) std::cout << " blocked";
            if(m.conflict()) std::cout << " conflict";
    std::cout << '\n';
}
        std::cout << "Usage:\n" << usage_lines(cli,argv[0]) << "\n";

       

    }
    
    return EXIT_SUCCESS;

}