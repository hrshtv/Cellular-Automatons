#include "Cell.h"

class ConwayCell : public Cell {

    public:

    ConwayCell(int x, int y, int w, int h);
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
    if (state == 0)
        this->birth();
    else
        this->death();
}

void ConwayCell::updateState(int s){
    if (s == 0)
        this->death();
    else
        this->birth(); 
}

int ConwayCell::handle(int e){

    if (e == FL_PUSH)
        flip();

    else if (e == FL_DRAG)
        birth();

    return 1;

}
