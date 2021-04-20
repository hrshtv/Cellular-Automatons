#include <vector>
#include "Config.h"
#include "Cell.h"

class Grid{

    protected:
    int R, C;
    vector<vector<int>> g;

    public:
    Grid();
    void print(Config *c);
    int nAlive(int i, int j);
    void update();

};

Grid::Grid(Config *c){
    for (int i = 0; i < c->size(); i++){
        for (int j = 0; j < c->size(); j++){
            // Two gosper guns:
            g[i][j] = c->data[i][j];
            g[R-i-1][C-j-1] = c->data[i][j];
        }
    }
}

void Grid::print(){
    for (int i = 1; i < R-1; i++){
        for (int j = 1; j < C-1; j++){
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
}

int Grid::nAlive(int i, int j){
    // Returns the number of alive neighbours of a cell at (i, j)
    int n_a = 0;
    for (int r = -1; r <= 1; r++)
        for (int c = -1; c <= 1; c++)
            n_a += g[i + r][j + c];
    n_a -= g[i][j];
    return n_a;
}

void Grid::update()
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