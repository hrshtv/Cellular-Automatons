#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include "../cells/ConwayCell.h"
#include "../configs/Config.h"
#include "../configs/Gosper.h"

using namespace std;

class ConwayWorld{

    protected:
    int R, C, CELL_SIZE;

    public:

    vector<vector<ConwayCell*>> world;

    ConwayWorld(int R, int C, int CELL_SIZE){

        this->R = R;
        this->C = C;
        this->CELL_SIZE = CELL_SIZE;

        world.resize(R);
        for (int i = 0; i < R; i++)
            world[i].resize(C);

    }

    ~ConwayWorld(){
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                delete world[i][j];
    }

    void init(){
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                world[i][j] = new ConwayCell(CELL_SIZE*i, CELL_SIZE*j, CELL_SIZE, CELL_SIZE);
    }

    void addConfig(Config *c){
        for (int i = 0; i < c->sizeR(); i++)
            for (int j = 0; j < c->sizeC(); j++)
                world[i][j]->updateState(c->data[i][j]);
    }

    void print(){
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
        for (int r = -1; r <= 1; r++)
            for (int c = -1; c <= 1; c++)
                if (!(r == 0 && c == 0) && (world[i + r][j + c]->state == 1))
                    n_a++;
        return n_a;
    }

    void update(){
        // Updates all states based on the rules of the world

        int next_grid[R][C]; // Temporary storage for the next generation
        
        for (int i = 1; i < R-1; i++){
            for (int j = 1; j < C-1; j++){

                int n_a = nAlive(i, j);

                /* Rules: */

                // Death: Underpopulation and Overpopulation
                if ((world[i][j]->state == 1) && (n_a < 2 || n_a > 3))
                    next_grid[i][j] = 0;

                // Birth
                else if ((world[i][j]->state == 0) && (n_a == 3))
                    next_grid[i][j] = 1;

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
        // Resets the world
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                world[i][j]->death();
    }

};
