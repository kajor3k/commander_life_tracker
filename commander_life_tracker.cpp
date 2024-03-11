#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "pico/stdlib.h"
#include "libraries/gfx_pack/gfx_pack.hpp"
#include <list>

using namespace pimoroni;

ST7567 st7567(128, 64, GfxPack::gfx_pack_pins);
PicoGraphics_Pen1Bit graphics(st7567.width, st7567.height, nullptr);
RGBLED backlight_rgb(GfxPack::BL_R, GfxPack::BL_G, GfxPack::BL_B, Polarity::ACTIVE_HIGH);
Button button_a(GfxPack::A);
Button button_b(GfxPack::B);
Button button_c(GfxPack::C);
Button button_d(GfxPack::D);
Button button_e(GfxPack::E);
Point left_pane_start_location (0,0);
Point right_pane_start_location (98, 0);
Point main_label_location(40, 5);
//Point main_label_location(48, 20);
Point main_location(40, 30);
// upper left corner x and y, lower right corner x and y (not straightforward, w stands for wrapping, h for height, but effectively it's an end point coordinates)
Point left_pane_location(0,0);
Point right_pane_location (110, 0);

std::string commander_string = "Commander Damage";
std::string life_label = "Life Points";
std::string commander_damage_1_label = commander_string +" 1";
std::string commander_damage_2_label = commander_string +" 2";
std::string commander_damage_3_label = commander_string +" 3";
std::string commander_damage_4_label = commander_string +" 4";
std::string commander_damage_5_label = commander_string +" 5";
std::string commander_damage_6_label = commander_string +" 6";
std::string commander_damage_7_label = commander_string +" Own";
std::string commander_tax_label = "Commander Tax";
std::string generic_counter_label = "Generic Counter";
std::string energy_counter_label = "Energy Counter";
std::string poison_counter_label = "Poison Counter";
std::string experience_counter_label = "Experience Counter";
std::string the_ring_counter_label = "The Ring Counter";
std::string storm_counter_label = "Storm Counter";

std::vector<std::tuple<std::string, int>> get_counter_labels_vector() {
    std::vector<std::tuple<std::string, int>> counter_labels_vector;
    std::unordered_map<std::string, int> counters_labels_map;
    counter_labels_vector.emplace_back(std::pair<std::string, int>(life_label, 40));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(commander_damage_1_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(commander_damage_2_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(commander_damage_3_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(commander_damage_4_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(commander_damage_5_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(commander_damage_6_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(commander_damage_7_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(commander_tax_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(generic_counter_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(energy_counter_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(poison_counter_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(experience_counter_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(the_ring_counter_label, 0));
    counter_labels_vector.emplace_back(std::pair<std::string, int>(storm_counter_label, 0));
    return counter_labels_vector;
}

std::vector<std::tuple<std::string, int>> counter_labels_vector = get_counter_labels_vector();







int current_counter = 40;
std::string current_label = life_label;
int current_brightness = 0;

void load_screen();

std::string int_to_string(int current) {
     std::string final_string = std::to_string(current);
     return final_string;
}

void clean_screen() {
    graphics.set_pen(0);
    graphics.clear();
}

bool check_if_commander_damage(std::string key) {
    std::string substring = "commander_damage";
    size_t match = key.find(substring);
    return match;
}

bool check_if_commander_tax(std::string key) {
    std::string substring = "commander_tax";
    size_t match = key.find(substring);
    return match;
}

void load_main_screen(Point label_location) {
    //graphics.set_dimensions(5,5);
    //graphics.update_pen()
    graphics.set_pen(15);
    graphics.text(current_label, label_location, 21, 1);
    graphics.text(int_to_string(current_counter), main_location, 320,4);


    //st7567.update(&graphics);
}




void load_left_pane(Point pane_location){

    //graphics.rectangle(pane_rect);
    auto inner_counter_it = counter_labels_vector.begin();


    //pane_rect.deflate(5);
    graphics.set_pen(25);

    graphics.text("LIFE",pane_location, 29,1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[0])), Point(15,8), 29,1);
    graphics.text("C_DMG",Point(0,16), 29,1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(15,22), 29,1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[2])), Point(15,28), 29,1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[3])), Point(15,34), 29,1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[4])), Point(15,40), 29,1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[5])), Point(15,46), 29,1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[6])), Point(15,52), 29,1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[7])), Point(15,58), 29,1);
    //graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(15,24), 29,1);
    //graphics.text(std::get<0>(counter_labels_vector[1]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
    //graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
    //graphics.text(std::get<0>(counter_labels_vector[2]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
    //graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
   // graphics.text(std::get<0>(counter_labels_vector[2]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
    //graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
   // graphics.text(std::get<0>(counter_labels_vector[3]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
   // graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
   // graphics.text(std::get<0>(counter_labels_vector[3]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
   // graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(std::get<0>(counter_labels_vector[4]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(std::get<0>(counter_labels_vector[4]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
   // graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(std::get<0>(counter_labels_vector[5]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(std::get<0>(counter_labels_vector[5]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(std::get<0>(counter_labels_vector[6]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(std::get<0>(counter_labels_vector[6]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(std::get<0>(counter_labels_vector[7]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(std::get<0>(counter_labels_vector[7]), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);
  //  graphics.text(int_to_string(std::get<1>(counter_labels_vector[1])), Point(pane_rect.x, pane_rect.y+5), pane_rect.w);

    //st7567.update(&graphics);
    //sleep_ms(1000/15);
}

void load_right_pane(Point pane_location) {

    //graphics.rectangle(pane_rect);
    auto inner_counter_it = counter_labels_vector.begin();


    //pane_rect.deflate(5);
    graphics.set_pen(25);

    graphics.text("TAX", pane_location, 29, 1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[8])), Point(110, 8), 29, 1);
    graphics.text("GEN", Point(110, 16), 29, 1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[9])), Point(110, 22), 29, 1);
    graphics.text("ENG", Point(110, 28), 29, 1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[10])), Point(110, 34), 29, 1);
    graphics.text("POI", Point(110, 40), 29, 1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[11])), Point(110, 46), 29, 1);
    graphics.text("EXP", Point(110, 52), 29, 1);
    graphics.text(int_to_string(std::get<1>(counter_labels_vector[12])), Point(110, 58), 29, 1);
    //st7567.update(&graphics);
    //sleep_ms(1000);
}

void load_and_update() {
    load_main_screen(main_label_location);
    load_left_pane(left_pane_location);
    load_right_pane(right_pane_location);
    st7567.update(&graphics);
    sleep_ms(1000/15);

}
int main() {




    auto counter_it = counter_labels_vector.begin();

    st7567.set_backlight(64);


    while(true) {

        //previous tab
        if(button_a.read()){

            if (counter_it != counter_labels_vector.begin()){
                --counter_it;
                current_counter = std::get<1>(*counter_it);
            }
            current_label = std::get<0>(*counter_it);


        }

        //next tab
        if(button_b.read()){
            if (counter_it != counter_labels_vector.end()-1){
                ++counter_it;
                current_counter = std::get<1>(*counter_it);
            }
            current_label = std::get<0>(*counter_it);



        }
        // increase brightness
        if(button_c.read()){
            current_brightness += 50;
            if(current_brightness<=255){
                st7567.set_backlight( current_brightness);
            }
            else {
                current_brightness=0;
            }
        }

        //check for only one press
        //button.raw will update the state smoothly, which is not desired here
        //button.read check for state before update

        if(button_d.read()) {
            current_counter -= 1;
            std::get<1>(*counter_it) = current_counter;

        }

        if(button_e.read()) {
            if(current_label.find("Commander Tax") != std::string::npos){
                current_counter += 1;
            }
            current_counter += 1;
            std::get<1>(*counter_it) = current_counter;

            if(current_label.find("Commander Damage") != std::string::npos){
                //if commander damage, then subtract life
                if (current_counter > 0){
                    //if commander damage is negative, allow user to reset it to 0 before starting to subtract life
                    std::get<1>(counter_labels_vector.front()) -= 1;
                }
            }

        }


        clean_screen();

        //update screen
        //TODO: wrap up in method
        // load screen 1
        //load_main_screen(main_label_location);
        //load_left_pane(left_pane_location);
        //load_right_pane(right_pane_location);
        //sleep_ms(1000/15);

        load_and_update();

        //TODO drop instruction

    }
}



