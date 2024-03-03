#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "pico/stdlib.h"
#include "libraries/gfx_pack/gfx_pack.hpp"

using namespace pimoroni;

ST7567 st7567(128, 64, GfxPack::gfx_pack_pins);
PicoGraphics_Pen1Bit graphics(st7567.width, st7567.height, nullptr);
RGBLED backlight_rgb(GfxPack::BL_R, GfxPack::BL_G, GfxPack::BL_B, Polarity::ACTIVE_HIGH);
Button button_d(GfxPack::D);
Button button_e(GfxPack::E);
Point text_location(0, 0);

std::string convert_life_to_string(int life) {
     std::string lifeString = std::to_string(life);
     return lifeString;
}

int main() {

    int life = 40;
    while(true) {

        //check for only one press
        //button.raw will update the state smoothly, which is not desired here
        //button.read check for state before update
        if(button_d.read()) {
            life -= 1;
        }

        if(button_e.read()) {
           life += 1;
        }

        //clean screen
        //TODO: move those lines to distinct function as it will be called multiple times
        graphics.set_pen(0);
        graphics.clear();

        //update screen
        //TODO: wrap up in method
        graphics.set_pen(15);
        graphics.text(convert_life_to_string(life), text_location, 320);
        st7567.update(&graphics);

    }
}
