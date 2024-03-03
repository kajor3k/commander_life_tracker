#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "pico/stdlib.h"
#include "libraries/gfx_pack/gfx_pack.hpp"

using namespace pimoroni;

ST7567 st7567(128, 64, GfxPack::gfx_pack_pins);
PicoGraphics_Pen1Bit graphics(st7567.width, st7567.height, nullptr);
RGBLED backlight_rgb(GfxPack::BL_R, GfxPack::BL_G, GfxPack::BL_B, Polarity::ACTIVE_HIGH);
Button button_a(GfxPack::A);
Button button_b(GfxPack::B);
Button button_c(GfxPack::C);
Button button_d(GfxPack::D);
Button button_e(GfxPack::E);
Point main_label_location(58, 25);
Point main_location(64, 32);

std::string convert_life_to_string(int life) {
     std::string lifeString = std::to_string(life);
     return lifeString;
}

void clean_screen() {
    graphics.set_pen(0);
    graphics.clear();
}

enum active_view
{
    life_view = 0,
    commander_tax_view = 1,
    generic_counter_view = 2
    //TODO add all views

};


int main() {

    int life_count = 40;
    int commander_damage_0 = 0;
    int commander_damage_1 = 0;
    int commander_damage_2 = 0;
    int commander_damage_3 = 0;
    int commander_damage_4 = 0;
    int commander_damage_6 = 0;
    int commander_damage_7 = 0;
    int commander_damage_8 = 0;
    int commander_tax = 0;
    int generic_counter = 0;
    int energy_counter = 0;
    int poison_counter = 0;
    int experience_counter = 0;
    int the_ring_counter = 0;
    int storm_counter = 0;

    int current_view = active_view(life_view);



    while(true) {

        //previous tab
        if(button_a.read()){
            for (int i = current_view; i >= active_view(life_view); i-- ){
                if (current_view == active_view(life_view)){
                    current_view = active_view(generic_counter_view);
                }
            }
        }

        //next tab
        if(button_b.read()){
            for (int i = current_view; i <= active_view(generic_counter_view); i++ ){
                if (current_view == active_view(generic_counter_view)){
                    current_view = active_view(life_view);
                }
            }
        }

        //check for only one press
        //button.raw will update the state smoothly, which is not desired here
        //button.read check for state before update

        //if(button_d.read()) {
          //  life_count -= 1;
       // }

        //if(button_e.read()) {
            //life_count += 1;
      //  }

        //clean screen
        //TODO: move those lines to distinct function as it will be called multiple times
        clean_screen();

        //update screen
        //TODO: wrap up in method
        graphics.set_pen(15);
        // load screen 1
        graphics.text("Life", main_label_location, 320);
        graphics.text(convert_life_to_string(life_count), main_location, 320);

        st7567.update(&graphics);

    }
}
