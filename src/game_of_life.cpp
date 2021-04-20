/*
    Description: Conway's Game of Life, implemented in FLTK
    Author: Harshit Varma

    Instructions:
    - Click to add/remove cells
    - Drag mouse to add a series of chains
    - Use the right arrow key to transition to the next state/generation
    - Press spacebar to reset to the empty state
    - ESC to quit

*/

#include <string>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include "config.cpp"

using namespace std;

// Size of the world
const int R = 75;
const int C = 75;

const int CELL_SIZE = 10;

int grid[R][C] = {0}; // Global grid used for implementing the logic (1:Alive, 0:Dead)
 
template<typename T>
void print(T s){
    cout << s << endl;
}

/* The GUI */
class Cell : public Fl_Box
{
    protected:
    int x, y, w, h;
    int state; // 0: dead, 1:alive

    public:

    Cell(int x, int y, int w, int h) : Fl_Box (x, y, w, h, "") {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;

        this->box(FL_BORDER_BOX);

        this->state = 0;
        this->color(FL_BLACK);

    }
    
    virtual void birth(){
        this->state = 1;

        this->color(FL_WHITE);
        this->redraw();

        grid[x/CELL_SIZE][y/CELL_SIZE] = 1;
    }

    virtual void death(){
        this->state = 0;

        this->color(FL_BLACK);
        this->redraw();

        grid[x/CELL_SIZE][y/CELL_SIZE] = 0;
    }

    virtual void flip(){
        if (state == 0)
            this->birth();
        else
            this->death();
    }

    virtual int handle(int e){
        return 1;
    }
};

Cell* world[R][C]; // GUI grid of cells, each cell is either alive or dead

char* int2CharStar(int x)
{
    // Converts int to char*
    char *c = new char[3]; // At max 3 chars: "16\0" 
    sprintf(c, "%d", x);
    return c;
}

void initGrid()
{
    // Initialize the grid with pre-defined live cells (optional)
    Gosper gun;
    for (int i = 0; i < gun.size; i++){
        for (int j = 0; j < gun.size; j++){
            // Two gosper guns:
            grid[i][j] = gun.data[i][j];
            grid[R-i-1][C-j-1] = gun.data[i][j];
        }
    }
}

void printGrid(){
    for (int i = 1; i < R-1; i++){
        for (int j = 1; j < C-1; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int nAlive(int i, int j)
{
    // Returns the number of alive neighbours of a cell at (i, j)
    int n_a = 0;
    for (int r = -1; r <= 1; r++)
        for (int c = -1; c <= 1; c++)
            n_a += grid[i + r][j + c];
    n_a -= grid[i][j];
    return n_a;
}

void updateGrid()
{
    // Updates the world based on the current state

    int next_grid[R][C];
    
    for (int i = 1; i < R-1; i++){
        for (int j = 1; j < C-1; j++){

            int n_a = nAlive(i, j);

            /* Rules: */

            // Death: Underpopulation and Overpopulation
            if ((grid[i][j] == 1) && (n_a < 2 || n_a > 3))
                next_grid[i][j] = 0;
            // Birth
            else if ((grid[i][j] == 0) && (n_a == 3))
                next_grid[i][j] = 1;
            // *life*
            else
                next_grid[i][j] = grid[i][j];

        }
    }

    // Update
    for (int i = 1; i < R-1; i++)
        for (int j = 1; j < C-1; j++)
            grid[i][j] = next_grid[i][j];
}

void initWorld(){
    // Initializes the GUI world
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            world[i][j] = new Cell(CELL_SIZE*i, CELL_SIZE*j, CELL_SIZE, CELL_SIZE);
        }
    }
}

void updateWorld(){
    // Updates the GUI based on the current state of the grid
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            if (grid[i][j] == 1)
                world[i][j]->birth();
            else
                world[i][j]->death();
        }
    }
}

void reset(){
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            grid[i][j] = 0;
    updateWorld();
}

class CustomWindow : public Fl_Window
{
    public:
    CustomWindow(int w, int h, const char *title) : Fl_Window(w, h, title) {};

    int handle(int e){

        if (e == FL_KEYDOWN){

            if (Fl::event_key(FL_Right)){
                updateGrid();
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

        else if (e == FL_PUSH){
            int i = Fl::event_x() / CELL_SIZE;
            int j = Fl::event_y() / CELL_SIZE;
            world[i][j]->flip();
        }

        else if (e == FL_DRAG){
            int i = Fl::event_x() / CELL_SIZE;
            int j = Fl::event_y() / CELL_SIZE;
            world[i][j]->birth();
        }

        return 1;

    }
};

int main(){

    // Create the main window
    Fl_Window* window = new CustomWindow(R*CELL_SIZE, C*CELL_SIZE, "Conway's Game of Life");
    window->color(FL_BLACK);

    // Initialize    
    initGrid();
    initWorld();
    updateWorld();

    window->show();
    window->end();

    int status = Fl::run();

    cout << "Exiting ...\n";

    return status;

}