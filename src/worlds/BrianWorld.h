#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include "../cells/BrianCell.h"
#include "../configs/Config.h"

using namespace std;

class BrianWorld{

    protected:
    int R, C, CELL_SIZE;

    public:

    vector<vector<BrianCell*>> world;

    BrianWorld(int R, int C, int CELL_SIZE){

        this->R = R;
        this->C = C;
        this->CELL_SIZE = CELL_SIZE;

        world.resize(R);
        for (int i = 0; i < R; i++)
            world[i].resize(C);

    }

    ~BrianWorld(){
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                delete world[i][j];
    }

    void init(){
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                world[i][j] = new BrianCell(CELL_SIZE*i, CELL_SIZE*j, CELL_SIZE, CELL_SIZE);
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
        for (int r = -1; r <= 1; r++){
            for (int c = -1; c <= 1; c++){
                if (!(r == 0 && c == 0) && world[i + r][j + c]->state == 1)
                    n_a++;
            }
        }
        return n_a;
    }

    void update(){
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

};
