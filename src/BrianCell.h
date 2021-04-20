#include "Cell.h"

/* Brian's Brain */

class BrianCell : public Cell {

    public:

    BrianCell(int x, int y, int w, int h);

    void  on();
    void dying();
    void off();

    void flip(); // circular flip

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
    if (state == -1)
        this->on();
    else if (state == 0)
        this->off();
    else
        this->dying();
}

void BrianCell::updateState(int s){
    if (s == -1)
        this->off();
    else if (s == 0)
        this->dying(); 
    else
        this->on();
}

int BrianCell::handle(int e){

    if (e == FL_PUSH)
        this->flip();

    else if (e == FL_DRAG)
        this->on();

    return 1;

}