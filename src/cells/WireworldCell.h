#include "Cell.h"

/* Wireworld Cell : https://en.wikipedia.org/wiki/Wireworld */

class WireworldCell : public Cell {

    public:

    WireworldCell(int x, int y, int w, int h);

    // 4 states
    void empty();
    void head();
    void tail();
    void conductor();

    void flip();

    virtual void updateState(int s);

    virtual int handle(int e);

};

WireworldCell::WireworldCell(int x, int y, int w, int h) : Cell(x, y, w, h) {}

void WireworldCell::empty(){
    this->state = 0;
    this->color(FL_BLACK);
    this->redraw();
}

void WireworldCell::head(){
    this->state = 1;
    this->color(FL_GREEN);
    this->redraw();
}

void WireworldCell::tail(){
    this->state = 2;
    this->color(FL_RED);
    this->redraw();
}

void WireworldCell::conductor(){
    this->state = 3;
    this->color(FL_YELLOW);
    this->redraw();
}

void WireworldCell::flip(){
    if (state == 0)
        this->conductor();
    else if (state == 3)
        this->tail();
    else if (state == 2)
        this->head();
    else if (state == 1)
        this->empty();
    else
        return;
}

void WireworldCell::updateState(int s){
    if (s == 0)
        this->empty();
    else if (s == 1)
        this->head(); 
    else if (s == 2)
        this->tail(); 
    else if (s == 3)
        this->conductor();
    else
        return;
}

int WireworldCell::handle(int e){

    if (e == FL_PUSH)
        this->flip();

    else if (e == FL_DRAG)
        this->conductor();

    return 1;

}