#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "pico/stdlib.h"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "libraries/gfx_pack/gfx_pack.hpp"

using namespace pimoroni;

ST7789 st7789(PicoExplorer::WIDTH, PicoExplorer::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);
Button button_d(GfxPack::D);
Button button_e(GfxPack::E);
Point text_location(0, 0);

std::string convert_life_to_string(int life) {
     std::string lifeString = std::to_string(life);
     return lifeString;
}

int main() {
    graphics.set_pen(255, 0, 0);
    int life = 40;

    while(true) {

        if(button_d.raw()) {
            life -= 1;
        }

        if(button_e.raw()) {
           life += 1;
        }

        graphics.set_pen(15);
        graphics.text(convert_life_to_string(life), text_location, 320);
    }
}
