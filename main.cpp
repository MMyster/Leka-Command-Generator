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
    bool led_range_colon=false;
    int led_first_target;
    int led_last_target;
    int led_single_target;
    std::vector<int> rgb_ctrl_values(3);
    bool hex=false;

    auto led_setup="Led setup"%(
      command("led").set(selected,command_focus::led) %"Control led(s)",

      "Robot parts which implement leds"%
      (
      required("-e","--ears").set(led_ears_focus) %"Control ears part of robot"|
      required("-b","--belt").set(led_belt_focus) %"Control belt part of robot"
      ),

      "Targets commands"%
      (
      option("-A","--all").set(led_all_target_focus) %"Control all leds of robot" %"Aim all targets"|
      "Control a range of leds of robot"%
      (option("-R","--range").set(led_range_target_focus)
      & value("first target")([&](const char* s) { led_first_target = std::stoi(s,0,16); }) 
      & value("last target")([&](const char* s) { led_last_target = std::stoi(s,0,16); }) 
            .if_missing([]{ std::cout << "You need to provide two targets!\n"; } )) %"Aim a range of targets [hex]"|
     /* (opt_value("first target")([&](const char* s) { led_first_target = std::stoi(s,0,16); })
      & required(":").set(led_range_colon)
      & opt_value("last target")([&](const char* s) { led_last_target = std::stoi(s,0,16); }) ) %"Aim a range of targets [hex]"|*/
      integer("target")([&](const char* s) { led_single_target = std::stoi(s,0,16); })
            .if_missing([]{ std::cout << "You need to provide one target!\n"; } ) %"Aim one target [hex]"
      ),

      "RGB data controls"%
      (
      option("-V","--values") & integer("Red value",rgb_ctrl_values[0]) & integer("Green value",rgb_ctrl_values[1]) & integer("Blue value",rgb_ctrl_values[2])
            .if_missing([]{ std::cout << "You need to provide RGB values!\n"; } ) %"Provide RGB values"
            |
      option("-VH","--values-hex","--hex").set(hex) & value("Red value")([&](const char* s) { rgb_ctrl_values[0] = std::stoi(s,0,16); }) 
                                                    & value("Green value") ([&](const char* s) { rgb_ctrl_values[1] = std::stoi(s,0,16); })
                                                    & value("Blue value") ([&](const char* s) { rgb_ctrl_values[2] = std::stoi(s,0,16); })
            .if_missing([]{ std::cout << "You need to provide RGB values!\n"; } ) %"Provide RGB values"
            |
            option("-r","red").set(rgb_ctrl_values[0],255)%"set Red value"|
            option("-g","green").set(rgb_ctrl_values[1],255)%"set Green value"|
            option("-b","blue").set(rgb_ctrl_values[2],255)%"set Blue value"
      )

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
      (option("-A","--all").set(motor_all_target_focus) & integer("Direction",motor_ctrl_values) & integer("Speed",motor_ctrl_values))%"Give same instructions towards both wheels"|
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

      switch (selected)
      {
      case command_focus::help :
      {
      auto fmt = doc_formatting{}.doc_column(31).last_column(80);
      std::cout << make_man_page(cli, argv[0],fmt) << '\n';
      break;
      }

      /*--------------------------------------
        LED PARSE
      --------------------------------------*/
      case command_focus::led :
      {
            std::vector<frame_t>ctrl_values(rgb_ctrl_values.begin(),rgb_ctrl_values.end());
            std::vector<command_group_led>list_command_group_led;

            std::vector<frame_t>list_id_led;
            if(led_ears_focus){
              list_id_led=std::vector<frame_t>(std::begin(list_id_led_ears),std::end(list_id_led_ears));
            }
            else if(led_belt_focus){
              list_id_led=std::vector<frame_t>(std::begin(list_id_led_belt),std::end(list_id_led_belt));
            }

              /*all*/
              if(led_all_target_focus){
                for(frame_t id : list_id_led){
                  command_group_led cmd(get_length_led_all(),led_ears_focus ? get_id_command_led_ears_all() : get_id_command_led_belt_all() , id,ctrl_values);
                  list_command_group_led.push_back(cmd);
                }
              }

              /* range */
              else if(led_range_target_focus){
                auto start=std::find(std::begin(list_id_led), std::end(list_id_led), led_first_target);
                auto end=std::find(std::begin(list_id_led), std::end(list_id_led), led_last_target);

                frame_t index_first_target;
                frame_t index_last_target;
                bool in_bound=false;

                /* First target and last target in list*/
                if(start != std::end(list_id_led) && end !=std::end(list_id_led)){
                  index_first_target=start-std::begin(list_id_led);
                  index_last_target=end-std::begin(list_id_led);
                  in_bound=true;

                }
                else if(led_range_colon){
                  if(start == std::end(list_id_led) ){
                    index_first_target=0;
                  }
                  if(end ==std::end(list_id_led)){
                    index_last_target=*end-1;
                  }
                  in_bound=true;

                }
                else 
                {
                  std::cout << "Out of bounds" << std::endl;
                }

                  if(index_first_target<=index_last_target && in_bound){
                    for(frame_t id : std::vector<frame_t>(list_id_led.begin()+index_first_target,list_id_led.begin()+index_last_target+1)){
                    command_group_led cmd(get_length_led_all(),led_ears_focus ? get_id_command_led_ears_range() : get_id_command_led_belt_range(), id,ctrl_values);
                    list_command_group_led.push_back(cmd);
                    }

                  }
                            

              }
              else{
                if(std::find(std::begin(list_id_led), std::end(list_id_led), led_single_target) != std::end(list_id_led)){
                  command_group_led cmd(get_length_led_all(),led_ears_focus ? get_id_command_led_ears_single() : get_id_command_led_belt_single(),static_cast<frame_t>(led_single_target),ctrl_values);
                  list_command_group_led.push_back(cmd);
                  
                }
                else{
                  std::cout << "\nThis target don't exist\n" << "\n";
                }
              }
            


            for(command_group_led command : list_command_group_led){
                      std::cout << "\n";
                      std::cout << std::hex;
                      std::cout << "Id command : " << static_cast<int>(command.id_command) << std::endl;
                      std::cout << "Id target : " << static_cast<int>(command.id_target) << std::endl;
                      //std::cout << std::dec;
                      std::cout << "Red value = " << static_cast<int>(command.ctrl_values[0]) << std::endl;
                      std::cout << "Green value = " << static_cast<int>(command.ctrl_values[1]) << std::endl;
                      std::cout << "Blue value = " << static_cast<int>(command.ctrl_values[2]) << std::endl;
                      std::cout << "\n";
            }

            frame.list_command_group=std::vector<command_group>(list_command_group_led.begin(),list_command_group_led.end());


      break;
      }



      /*--------------------------------------
        MOTOR PARSE
      --------------------------------------*/
      case command_focus::motor:
      {
        std::vector<frame_t>ctrl_values(motor_ctrl_values.begin(),motor_ctrl_values.end());
        if(motor_all_target_focus){
          command_group_motor cmd(get_length_motor_all(), get_id_command_motor_all(),ctrl_values);
          frame.list_command_group.push_back(cmd);
        }
        else if(motor_duo_target_focus){
          command_group_motor cmd(get_length_motor_duo(), get_id_command_motor_duo(),ctrl_values);
          frame.list_command_group.push_back(cmd);
        }
        else if(motor_left_target_focus){
          command_group_motor cmd(get_length_motor_single(), get_id_command_motor_left(),ctrl_values);
          frame.list_command_group.push_back(cmd);
        }
        else if(motor_right_target_focus){
          command_group_motor cmd(get_length_motor_single(), get_id_command_motor_right(),ctrl_values);
          frame.list_command_group.push_back(cmd);
        }
        else{
          /*...*/
        }
      break;
      }





      default:
      break;
      }


    std::cout << "\nCommand sent !!!\n" << "\n";
    
    }
    else {
        std::cout << "\nCommand not valid\n" << "\n";
        for(const auto& arg : wrong) {
            std::cout << "'" << arg << "' is not a valid command line argument\n";
        }

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