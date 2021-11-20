#include <LKCommandGenerator.h>
#include <LKAlphaComSpecs.h>



using namespace LKCommandGenerator;

/* Command group */

command_group::command_group(){
}

command_group::command_group(frame_t id_command){
    this->id_command=id_command;
}

command_group::~command_group(){

}

auto command_group::get_id_command()->frame_t{
    return id_command;
}

auto command_group::get_ctrl_values()->std::vector<frame_t>{
    return ctrl_values;
}

auto command_group::update_crtl_values()->void{
this->ctrl_values.clear();
this->ctrl_values.push_back(this->id_command);
}

/* Led */

 const std::vector<frame_t> command_group_led::list_id_led_belt={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13};
 const std::vector<frame_t> command_group_led::list_id_led_ears={0x00,0x01};

command_group_led::command_group_led():command_group()
{

}

command_group_led::command_group_led(frame_t red_value,frame_t green_value,frame_t blue_value,int part/* =0 */,std::vector<frame_t>targets/* ={} */)
:command_group()
{
    this->red_value=red_value;
    this->green_value=green_value;
    this->blue_value=blue_value;
    set_part(part);
    if(!targets.empty()){
        set_scope(0);
        update_targets(targets);
    }
    else{
        set_scope(2);
        update_all_targets();
    }
    update_id_command();
}

command_group_led::command_group_led(frame_t red_value,frame_t green_value,frame_t blue_value,int part,frame_t first_target,frame_t last_target)
:command_group()
{
    this->red_value=red_value;
    this->green_value=green_value;
    this->blue_value=blue_value;
    set_part(part);
    set_scope(1);
    update_range_targets(first_target,last_target);
    update_id_command();
}



auto command_group_led::set_part(int param)->void
{
    switch (param)
    {
    case 0:
        this->selected_part=part::ears;
    break;

    case 1:
        this->selected_part=part::belt;
    break;
    
    default:
        break;
    }
    
}

auto command_group_led::set_scope(int param)->void
{
    switch (param)
    {
    case 0:
        this->selected_scope=scope::single;
    break;

    case 1:
        this->selected_scope=scope::range;
    break;

    case 2:
        this->selected_scope=scope::all;
    break;
    
    default:
    break;
    }

}

auto command_group_led::update_targets(std::vector<frame_t>targets)->std::vector<frame_t>
{
    std::vector<frame_t>list_id;
    if(this->selected_part==part::ears){
        list_id=std::vector<frame_t>(list_id_led_ears.begin(),list_id_led_ears.end());
    }

    else if(this->selected_part==part::belt){
        list_id=std::vector<frame_t>(list_id_led_belt.begin(),list_id_led_belt.end());
    }

    for(frame_t target : targets){
    auto pos=std::find(std::begin(list_id), std::end(list_id), target);

        if(pos != std::end(list_id)){
            this->targets.push_back(target);
        }

    }

    return this->targets;
}

auto command_group_led::update_range_targets(frame_t first_target,frame_t last_target)->std::vector<frame_t>
{
    std::vector<frame_t>list_id;
    if(this->selected_part==part::ears){
        list_id=std::vector<frame_t>(list_id_led_ears.begin(),list_id_led_ears.end());
    }
    else if(this->selected_part==part::belt){
        list_id=std::vector<frame_t>(list_id_led_belt.begin(),list_id_led_belt.end());
    }
    auto start=std::find(std::begin(list_id), std::end(list_id), first_target);
    auto end=std::find(std::begin(list_id), std::end(list_id), last_target);

    int index_first_target;
    int index_last_target;
    bool in_bounds=false;

    /* First target and last target in list*/
    if(start != std::end(list_id) && end !=std::end(list_id)){
        index_first_target=start-std::begin(list_id);
        index_last_target=end-std::begin(list_id);
        in_bounds=true;

    }
    
    if(index_first_target<=index_last_target && in_bounds)
    {
        this->targets=std::vector<frame_t>(list_id.begin()+index_first_target,list_id.begin()+index_last_target+1);
    }
    return this->targets;
}

auto command_group_led::update_all_targets()->std::vector<frame_t>
{
    if(selected_part==part::ears){
    this->targets=std::vector<frame_t>(list_id_led_ears.begin(),list_id_led_ears.end());
    }
    else{
    this->targets=std::vector<frame_t>(list_id_led_belt.begin(),list_id_led_belt.end());
    }
    return this->targets;
}

auto command_group_led::update_id_command()->void
{
    if(selected_part==part::ears){
        if(selected_scope==scope::all){
            this->id_command=get_id_command_led_ears_all();
        }
        else if(selected_scope==scope::range){
            this->id_command=get_id_command_led_ears_range();
        }
        else{
            this->id_command=get_id_command_led_ears_single();
        }
    }
    else{
        if(selected_scope==scope::all){
            this->id_command=get_id_command_led_belt_all();
        }
        else if(selected_scope==scope::range){
            this->id_command=get_id_command_led_belt_range();
        }
        else{
            this->id_command=get_id_command_led_belt_single();
        }
    }
}


auto command_group_led::update_crtl_values()->void
{
    switch (this->selected_scope)
    {
    case scope::single :
    this->ctrl_values.clear();
    for(frame_t target : this->targets){
        this->ctrl_values.push_back(this->id_command);
        this->ctrl_values.push_back(target);
        this->ctrl_values.push_back(this->red_value);
        this->ctrl_values.push_back(this->green_value);
        this->ctrl_values.push_back(this->blue_value);
    }
    break;

    case scope::range :
        command_group::update_crtl_values();
        this->ctrl_values.push_back(this->targets.front());
        this->ctrl_values.push_back(this->targets.back());
        this->ctrl_values.push_back(this->red_value);
        this->ctrl_values.push_back(this->green_value);
        this->ctrl_values.push_back(this->blue_value);
    
    break;

        case scope::all:
        command_group::update_crtl_values();
        this->ctrl_values.push_back(this->red_value);
        this->ctrl_values.push_back(this->green_value);
        this->ctrl_values.push_back(this->blue_value);
    
    break;
    
    default:
        break;
    }

}

auto command_group_led::display_list_targets()->void
{
    std::cout << std::hex;
    std::cout << std::endl;
    std::cout << " Ears : ";
    std::cout << " { ";
    for(frame_t cur_frame : list_id_led_ears){
        std::cout << static_cast<int>(cur_frame) << " ";
    }
    std::cout << "} ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << " Belt : ";
    std::cout << " { ";
    for(frame_t cur_frame : list_id_led_belt){
        std::cout << static_cast<int>(cur_frame) << " ";
    }
    std::cout << "} ";
    std::cout << std::endl;
}

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

/*Motor*/

command_group_motor::command_group_motor(frame_t left_spin,frame_t left_speed,frame_t right_spin,frame_t right_speed,int scope/* =2 */):command_group()
{
    this->left_spin=left_spin;
    this->right_spin=right_spin;
    this->left_speed=left_speed;
    this->right_speed=right_speed;
    set_scope(scope);
    update_id_command();
}

auto command_group_motor::set_scope(int param)->void
{
    switch (param)
    {
    case 0:
        this->selected_scope=scope::left;
    break;

    case 1:
        this->selected_scope=scope::right;
    break;

    case 2:
        this->selected_scope=scope::duo;
    break;

    case 3:
        this->selected_scope=scope::all;
    break;
    
    default:
        break;
    }
    
}

auto command_group_motor::update_id_command()->void
{
    if(selected_scope==scope::all){
        this->id_command=get_id_command_motor_all();
    }
    else if(selected_scope==scope::duo){
        this->id_command=get_id_command_motor_duo();
    }
    else if(selected_scope==scope::left){
        this->id_command=get_id_command_motor_left();
    }
    else{
        this->id_command=get_id_command_motor_right();
    }      
}

auto command_group_motor::update_crtl_values()->void
{

    command_group::update_crtl_values();
    
    switch (this->selected_scope)
    {
    case scope::all:
    this->ctrl_values.push_back(this->left_spin);
    this->ctrl_values.push_back(this->left_speed);
    break;

    case scope::duo:
    this->ctrl_values.push_back(this->left_spin);
    this->ctrl_values.push_back(this->left_speed);
    this->ctrl_values.push_back(this->right_spin);
    this->ctrl_values.push_back(this->right_speed);       
    break;

    case scope::left:
    this->ctrl_values.push_back(this->left_spin);
    this->ctrl_values.push_back(this->left_speed);
    break;

    case scope::right:
    this->ctrl_values.push_back(this->right_spin);
    this->ctrl_values.push_back(this->right_speed); 
    break;
    
    default:
        break;
    }

}


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


Frame::Frame(){

}

Frame::Frame(std::vector<frame_t>data)
{
    set_data(data);
}

auto Frame::get_start_sequence()->std::vector<frame_t> const
{
    std::vector<frame_t>start_sequence=std::vector<frame_t>(std::begin(LKFrame::start::sequence),std::end(LKFrame::start::sequence));
    return start_sequence;
}

auto Frame::get_data()->std::vector<frame_t>
{
    return this->data;
}

auto Frame::set_data(std::vector<frame_t>list)->void
{
    this->data=std::vector<frame_t>(list.begin(),list.end());
}

auto Frame::add_data(std::vector<frame_t>list)->void
{
    this->data.insert(this->data.end(),list.begin(),list.end());
}

auto Frame::calculate_length()->frame_t
{
    frame_t length=data.size();//data
    this->length=length;
    return length;
}

auto Frame::calculate_packet_size()->frame_t
{
    frame_t size=0;
    size+=start_sequence.size(); //start sequence
    size+=1;//length
    size+=data.size();//data
    size+=1;//checksum
    this->packet_size=size;
    return size;
}



auto Frame::calculate_checksum()->frame_t
{
    frame_t checksum = 0;
    checksum = (frame_t) ((checksum >> 1) | (checksum << 7)); // Circular shift
    checksum = (frame_t) (checksum + length); // Add segment
    checksum &= 0xFF; // Apply bitmask
    for (frame_t cur_frame : data) {
        checksum = (frame_t) ((checksum >> 1) | (checksum << 7)); // Circular shift
        checksum = (frame_t) (checksum + cur_frame); // Add segment
        checksum &= 0xFF; // Apply bitmask
    }
    return checksum;
}

auto Frame::make_packet()->std::vector<frame_t>
{
    this->packet.clear();
    this->packet.insert(this->packet.end(),this->start_sequence.begin(),this->start_sequence.end());
    this->packet.push_back(calculate_length());
    this->packet.insert(this->packet.end(),this->data.begin(),this->data.end());
    this->packet.push_back(calculate_checksum());
    return this->packet;
}

auto Frame::display_packet()->void{
    std::cout << std::hex;
    std::cout << std::endl;
    std::cout << " [ ";
    for(frame_t cur_frame : packet){
        std::cout << static_cast<int>(cur_frame) << " ";
    }
    std::cout << "] ";
    std::cout << std::endl;
    std::cout << std::dec;
    std::cout << std::endl;
    std::cout << "Packet size : ";
    std::cout << static_cast<int>(calculate_packet_size());
    std::cout << " bytes";
    std::cout << std::endl;
}

auto Frame::send_packet()->void
{
        std::cout << std::endl;
        std::cout << "Packet sent !!!";
        std::cout << std::endl;
}



