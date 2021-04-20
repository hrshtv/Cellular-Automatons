#include <iostream>
#include "Cell.h"

using namespace std;

// Size of the world
const int R = 75;
const int C = 75;
const int CELL_SIZE = 10;

class World{

    public:

    Cell* world[R][C];

    World(){
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                world[i][j] = new Cell(CELL_SIZE*i, CELL_SIZE*j, CELL_SIZE, CELL_SIZE);
    }

    void addConfig(Config *c){
        for (int i = 0; i < c->size(); i++)
            for (int j = 0; j < c->size(); j++)
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
                n_a += world[i + r][j + c]->state;
        n_a -= world[i][j]->state;
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

                // Death: Underpopulation and Overpopulation
                if ((world[i][j]->state == 1) && (n_a < 2 || n_a > 3))
                    next_grid[i][j] = 0;
                // Birth
                else if ((world[i][j]->state == 0) && (n_a == 3))
                    next_grid[i][j] = 1;
                // *life*
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
                world[i][j]->updateState(0);
    }

};
