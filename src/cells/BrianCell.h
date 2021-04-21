#include "Cell.h"

/* Brian's Brain : https://en.wikipedia.org/wiki/Brian%27s_Brain */

class BrianCell : public Cell {

    public:

    BrianCell(int x, int y, int w, int h);

    // 3 states
    void on();
    void dying();
    void off();

    void flip();

    virtual void updateState(int s);

    virtual int handle(int e);

};

BrianCell::BrianCell(int x, int y, int w, int h) : Cell(x, y, w, h) {}

void BrianCell::on(){
    this->state = 1;
    this->color(FL_WHITE);
    this->redraw();
}

void BrianCell::dying(){
    this->state = 0;
    this->color(FL_RED);
    this->redraw();
}

void BrianCell::off(){
    this->state = -1;
    this->color(FL_BLACK);
    this->redraw();
}

void BrianCell::flip(){
    // Circularly flips the state (-1 -> 1 -> 0 -> -1)
    if (state == -1)
        this->on();
    else if (state == 1)
        this->dying();
    else if (state == 0)
        this->off();
    else
        return;
}

void BrianCell::updateState(int s){
    if (s == -1)
        this->off();
    else if (s == 0)
        this->dying(); 
    else if (s == 1)
        this->on();
    else
        return;
}

int BrianCell::handle(int e){

    if (e == FL_PUSH)
        this->flip();

    else if (e == FL_DRAG)
        this->on();

    return 1;

}