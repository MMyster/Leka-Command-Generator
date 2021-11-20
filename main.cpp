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

    Frame frame;

    /*--------------------------------------
       HELP
    ---------------------------------------*/
    auto help="Manual"%(
         command("-h","--help","man").set(selected,command_focus::help)
    );


    /*--------------------------------------
        LED
    ---------------------------------------*/

    enum class led_part{ears,belt} led_selected_part;
    enum class led_scope{single,range,all} led_selected_scope;
    std::vector<int>led_targets;
    int led_first_target;
    int led_last_target;
    int led_red_value=0;
    int led_green_value=0;
    int led_blue_value=0;
    bool led_hex=false;

    auto led_setup="Led setup"%(
      command("led").set(selected,command_focus::led) %"Control led(s)",

      "Robot parts which implement leds"%
      (
      required("-e","--ears").set(led_selected_part,led_part::ears) %"Control ears part of robot"|
      required("-b","--belt").set(led_selected_part,led_part::belt) %"Control belt part of robot"
      ),

      "Targets commands"%
      (
      option("-A","--all").set(led_selected_scope,led_scope::all) %"Control all leds of robot" %"Aim all targets"|
      "Control a range of leds of robot"%
      (option("-R","--range").set(led_selected_scope,led_scope::range)
      & value("first target")([&](const char* s) { led_first_target = std::stoi(s,0,16); }) 
      & value("last target")([&](const char* s) { led_last_target = std::stoi(s,0,16); }) 
            .if_missing([]{ std::cout << "You need to provide two targets!\n"; } )) %"Aim a range of targets [hex]"|
      values("targets")([&](const char* s) { led_targets.push_back(std::stoi(s,0,16)); })
            .if_missing([]{ std::cout << "You need to provide one target!\n"; } ) %"Aim one target [hex]"
      ),

      "RGB data controls"%
      (
      option("-V","--values") & integer("Red value",led_red_value) & integer("Green value",led_green_value) & integer("Blue value",led_blue_value)
            .if_missing([]{ std::cout << "You need to provide RGB values!\n"; } ) %"Provide RGB values"
            |
      option("-VH","--values-hex","--hex").set(led_hex) & value("Red value")([&](const char* s) { led_red_value = std::stoi(s,0,16); }) 
                                                    & value("Green value") ([&](const char* s) { led_green_value = std::stoi(s,0,16); })
                                                    & value("Blue value") ([&](const char* s) { led_blue_value = std::stoi(s,0,16); })
            .if_missing([]{ std::cout << "You need to provide RGB values!\n"; } ) %"Provide RGB values"
            |
            option("-r","red").set(led_red_value,255)%"set Red value"|
            option("-g","green").set(led_green_value,255)%"set Green value"|
            option("-b","blue").set(led_blue_value,255)%"set Blue value"
      )

    );


      /*--------------------------------------
        MOTOR
      --------------------------------------*/

    enum class motor_scope{left,right,duo,all}motor_selected_scope;
    int motor_left_spin;
    int motor_right_spin;
    int motor_left_speed;
    int motor_right_speed;
    bool motor_hex;

    auto motor_setup="Motor setup"%(
      command("motor").set(selected,command_focus::motor)%"Control motor features" &
      (
     (
      (required("-A","--all").set(motor_selected_scope,motor_scope::all) & value("Direction")([&](const char* s) { motor_left_spin = std::stoi(s);motor_right_spin = std::stoi(s); }) 
                                                        & value("Speed")([&](const char* s) { motor_left_speed = std::stoi(s);motor_right_speed = std::stoi(s); }) )%"Give same instructions towards both wheels"|
      (required("-D","--duo").set(motor_selected_scope,motor_scope::duo)  & integer("Left Spin",motor_left_spin) & integer("Left Speed",motor_left_speed)  
                                                  & integer("Right Spin",motor_right_spin) & integer("Right Speed",motor_right_speed))%"Give instructions for each wheel"|
      (required("-l","--left").set(motor_selected_scope,motor_scope::left) & integer("Left Spin",motor_left_spin) & integer("Left Speed",motor_left_speed))%"Give instructions towards left wheel" |
      (required("-r","--right").set(motor_selected_scope,motor_scope::right) & integer("Right Spin",motor_right_spin) & integer("Right Speed",motor_right_speed) )%"Give instructions towards right wheel" 
     ) 
     |
     (option("-H","--hex").set(motor_hex) & (
      (required("-A","--all").set(motor_selected_scope,motor_scope::all) & value("Direction")([&](const char* s) { motor_left_spin = std::stoi(s,0,16);motor_right_spin = std::stoi(s,0,16); }) 
                                                        & value("Speed")([&](const char* s) { motor_left_speed = std::stoi(s,0,16);motor_right_speed = std::stoi(s,0,16); }) )%"Give same instructions towards both wheels"|
      (required("-D","--duo").set(motor_selected_scope,motor_scope::duo)  & value("Left Spin")([&](const char* s) { motor_left_spin = std::stoi(s,0,16); }) 
                                                                          & value("Left Speed")([&](const char* s) { motor_left_speed = std::stoi(s,0,16); })   
                                                                          & value("Right Spin")([&](const char* s) { motor_right_spin = std::stoi(s,0,16); })  
                                                                          & value("Right Speed")([&](const char* s) { motor_right_speed = std::stoi(s,0,16); }) 
      ) %"Give instructions for each wheel"|
      (required("-l","--left").set(motor_selected_scope,motor_scope::left) & value("Left Spin")([&](const char* s) { motor_left_spin = std::stoi(s,0,16); }) 
                                                                            & value("Left Speed")([&](const char* s) { motor_left_speed = std::stoi(s,0,16); }) 
      )%"Give instructions towards left wheel" |
      (required("-r","--right").set(motor_selected_scope,motor_scope::right) & value("Right Spin")([&](const char* s) { motor_right_spin = std::stoi(s,0,16); }) 
                                                                             & value("Right Speed")([&](const char* s) { motor_right_speed = std::stoi(s,0,16); })  
      )  %"Give instructions towards right wheel" 
      ) )


      )
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
      /*--------------------------------------
        HELP PARSE
      --------------------------------------*/
      auto fmt = doc_formatting{}.doc_column(31).last_column(80);
      std::cout << make_man_page(cli, argv[0],fmt) << '\n';
      break;
      }

      /*--------------------------------------
        LED PARSE
      --------------------------------------*/
      case command_focus::led :
      {

          switch (led_selected_scope)
          {
          case led_scope::single:
          {
            std::vector<frame_t>targets=std::vector<frame_t>(led_targets.begin(),led_targets.end());
              command_group_led command(
              static_cast<frame_t>(led_red_value),
              static_cast<frame_t>(led_green_value),
              static_cast<frame_t>(led_blue_value),
              static_cast<int>(led_selected_part),
              targets
                  );
            command.update_crtl_values();
            frame.add_data(command.get_ctrl_values()); 
            break;
          }
          case led_scope::range:
          {
            command_group_led command(
                    static_cast<frame_t>(led_red_value),
                    static_cast<frame_t>(led_green_value),
                    static_cast<frame_t>(led_blue_value),
                    static_cast<int>(led_selected_part),
                    static_cast<frame_t>(led_first_target),
                    static_cast<frame_t>(led_last_target)
                  );
                  command.update_crtl_values();
                  frame.add_data(command.get_ctrl_values()); 
            break;
          }
          case led_scope::all:
          {
            command_group_led command(
                    static_cast<frame_t>(led_red_value),
                    static_cast<frame_t>(led_green_value),
                    static_cast<frame_t>(led_blue_value),
                    static_cast<int>(led_selected_part)
                  );
                  command.update_crtl_values();
                  frame.add_data(command.get_ctrl_values()); 
          }
            break;
          
          default:
            break;
          }     
      break;
      }



      /*--------------------------------------
        MOTOR PARSE
      --------------------------------------*/
      case command_focus::motor:
      {
          command_group_motor command(
          static_cast<frame_t>(motor_left_spin), 
          static_cast<frame_t>(motor_left_speed), 
          static_cast<frame_t>(motor_right_spin), 
          static_cast<frame_t>(motor_right_speed),
          static_cast<int>(motor_selected_scope)                
          );

          command.update_crtl_values();
          frame.add_data(command.get_ctrl_values());

      break;
      }


      default:
      break;
      }

    frame.make_packet();
    frame.display_packet();
    frame.send_packet();
    std::cout << "\nOK !!!\n" << "\n";
    
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