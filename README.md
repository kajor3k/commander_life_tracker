# Magic The Gathering life tracker

This project was created using [pico-boilerplate repository](https://github.com/pimoroni/pico-boilerplate).

- [General](#General)
- [Components](#Components)
- [How to use](#How-to-use)
- [Instruction](#Instruction)
- [Future plans](#Future-plans)
- [Author](#Author)

## General

It's a simple life tracker to be used during MTG games. I was having a commander format in mind, but it may be used for other formats

## Components

It was tested on Raspberry Pico H with GFX LCD by Pimoroni. 


## How to use
All the releases are in _release_ directory. Feel free to drop it to your Pico :)

## Instruction

A - show previous view
B - show next view
C - increase brightness (whenever max brightness is reached it is set up back to 0)
D - decrease value by 1
E - increase value by 1 (or by 2 if that's a commander tax)

## Future plans
- add support for other formats (definitely Modern, maybe Draft - adding some info about won match in best of 3 would be nice).
- add more visual effects while increasing or decreasing value (floating delta numbers. Quite convenient each time nasty opponent hits you for 17)
- play with rgb backlight (that one is risky, as I'm not sure how rgb backlight works with a battery pack. According to pimoroni docs, not so well, so I may be constrained by technology in that one. We'll see)
- prepare a tutorial about my rig to make it as easy as possible for you to assemble it on your own 

## Author
You can catch me via [kajor3k@gmail.com](mailto:kajor3k@gmail.com?subject=commander_life_tracker). Feel free to drop a feedback or ideas for improvements

## Buy me a coffee 
- if you like this projectm  you may consider [buying me a coffee](https://www.buymeacoffee.com/kajor3k). Much appreciated, definitely not necessary. 