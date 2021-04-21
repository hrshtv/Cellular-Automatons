/*
    Description: Brian's Brain Automaton, implemented in FLTK
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
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include "Helpers.h"
#include "World.h"

class CustomWindow : public Fl_Window{

    World *world;

    public:
    CustomWindow(int w, int h, const char *title, World *world) : Fl_Window(w, h, title) {
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

    World b;

    // Create the main window
    Fl_Window* window = new CustomWindow(R*CELL_SIZE, C*CELL_SIZE, "Brian's Brain", &b);
    window->color(FL_BLACK);

    // Initialize the game 
    b.init();

    // Start the game
    window->show();
    window->end();

    int status = Fl::run();

    print("Exiting...");

    return status;

}