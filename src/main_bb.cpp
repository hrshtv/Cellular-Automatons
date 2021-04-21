/*
    Description: Brian's Brain Automaton, implemented in FLTK
    Author: Harshit Varma

    Instructions:
    - Click to change state of cells
    - Drag mouse to add a series of chains
    - Use the right arrow key to transition to the next state/generation, keep it pressed for an "animation effect"
    - Press spacebar to reset to the empty state
    - ESC to quit

*/

#include <string>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include "cells/BrianCell.h"
#include "configs/Config.h"
#include "Helpers.h"

using namespace std;

// Size of the world
const int R = 75;
const int C = 75;
const int CELL_SIZE = 10;

BrianCell* world[R][C];

void initWorld(){
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            world[i][j] = new BrianCell(CELL_SIZE*i, CELL_SIZE*j, CELL_SIZE, CELL_SIZE);
}

void addConfig(Config *c){
    for (int i = 0; i < c->size(); i++)
        for (int j = 0; j < c->size(); j++)
            world[i][j]->updateState(c->data[i][j]);
}

void printWorld(){
    // Prints the current state of all cells
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            cout << world[i][j]->state << " ";
        }
        cout << endl;
    }
}

int nAlive(int i, int j){
    // Returns the number of alive neighbours of a cell at (i, j)
    int n_a = 0;
    for (int r = -1; r <= 1; r++){
        for (int c = -1; c <= 1; c++){
            if (!(r == i && c == j) && world[i + r][j + c]->state == 1)
                n_a++;
        }
    }
    return n_a;
}

void updateWorld()
{
    // Updates the world based on the current state

    int next_grid[R][C]; // Temporary storage for the next generation
    
    for (int i = 1; i < R-1; i++){
        for (int j = 1; j < C-1; j++){

            int n_a = nAlive(i, j);

            /* Rules: */

            // Off -> On
            if ((world[i][j]->state == -1) && (n_a == 2))
                next_grid[i][j] = 1;
            // Dying -> Off
            else if (world[i][j]->state == 0)
                next_grid[i][j] = -1;
            // On -> dying
            else if (world[i][j]->state == 1)
                next_grid[i][j] = 0;
            else
                next_grid[i][j] = world[i][j]->state;

        }
    }

    // Update
    for (int i = 1; i < R-1; i++){
        for (int j = 1; j < C-1; j++){
            world[i][j]->updateState(next_grid[i][j]);
        }
    }
}

void reset(){
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            world[i][j]->off();
}

class CustomWindow : public Fl_Window
{
    public:
    CustomWindow(int w, int h, const char *title) : Fl_Window(w, h, title) {};

    int handle(int e){

        if (e == FL_KEYDOWN){

            if (Fl::event_key(FL_Right)){
                updateWorld();
            }

            else if (Fl::event_key(32)){
                reset();
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
                world[i][j]->handle(e);
        }

        return 1;

    }
};

int main(){

    // Create the main window
    Fl_Window* window = new CustomWindow(R*CELL_SIZE, C*CELL_SIZE, "Brian's Brain");
    window->color(FL_BLACK);

    // Initialize the game 
    initWorld();

    // Start the game
    window->show();
    window->end();

    int status = Fl::run();

    print("Exiting...");

    return status;

}