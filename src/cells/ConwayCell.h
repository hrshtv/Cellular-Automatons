#include "Cell.h"

/* Cell as described in Conway's Game of Life */

class ConwayCell : public Cell {

    public:

    ConwayCell(int x, int y, int w, int h);

    // 2 states
    void birth();
    void death();

    void flip();

    virtual void updateState(int s);
    virtual int handle(int e);

};

ConwayCell::ConwayCell(int x, int y, int w, int h) : Cell(x, y, w, h) {}

void ConwayCell::birth(){
    this->state = 1;
    this->color(FL_WHITE);
    this->redraw();
}

void ConwayCell::death(){
    this->state = 0;
    this->color(FL_BLACK);
    this->redraw();
}

void ConwayCell::flip(){
    // Flips the states (0 -> 1 -> 0)
    if (state == 0)
        this->birth();
    else if (state == 1)
        this->death();
    else
        return;
}

void ConwayCell::updateState(int s){
    if (s == 0)
        this->death();
    else if (s == 1)
        this->birth();
    else
        return; 
}

int ConwayCell::handle(int e){

    if (e == FL_PUSH)
        flip();

    else if (e == FL_DRAG)
        birth();

    return 1;

}
