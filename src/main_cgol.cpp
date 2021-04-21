/*
    Description:  Conway's Game of Life, implemented in FLTK
    Author: Harshit Varma

    Instructions:
    - Click to change state of cells
    - Drag mouse to add a series of chains
    - Use the right arrow key to transition to the next state/generation, keep it pressed for an animation effect
    - Press spacebar to reset to the empty state
    - ESC to quit

*/

#include <string>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "Helpers.h"
#include "worlds/ConwayWorld.h"

const int R = 75;
const int C = 75;
const int CELL_SIZE = 10;

class CustomWindow : public Fl_Window {

    ConwayWorld *world;

    public:
    CustomWindow(int w, int h, const char *title, ConwayWorld *world) : Fl_Window(w, h, title) {
        this->world = world;
    };

    int handle(int e){

        if (e == FL_KEYDOWN){

            if (Fl::event_key(FL_Right)){
                world->update();
            }

            else if (Fl::event_key(32)){
                world->reset();
            }

            else if (Fl::event_key(FL_Escape)){
                this->hide();
                exit(0);
            }

        }

        else if (e == FL_PUSH || e == FL_DRAG){
            int i = Fl::event_x() / CELL_SIZE;
            int j = Fl::event_y() / CELL_SIZE;
            if ((i >= 0) && (i < R) and (j >= 0) and (j < C))
                world->world[i][j]->handle(e);
        }

        return 1;

    }

};

int main(){

    ConwayWorld c(R, C, CELL_SIZE);

    // Create the main window
    Fl_Window* window = new CustomWindow(R*CELL_SIZE, C*CELL_SIZE, "Conway's Game of Life", &c);
    window->color(FL_BLACK);

    Config *conf = new Gosper();
    conf->init();

    // Initialize the game 
    c.init();
    c.addConfig(conf);

    // Start the game
    window->show();
    window->end();

    int status = Fl::run();

    print("Exiting...");

    return status;

}