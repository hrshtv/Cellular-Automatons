#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

/* Abstract class that describes the nature of a cell in a cellular automaton */

class Cell : public Fl_Box {

    protected:
    int x, y, w, h;

    public:

    int state;

    Cell(int x, int y, int w, int h);
    virtual void updateState(int s) = 0;
    virtual int handle(int e) = 0;

};

Cell::Cell(int x, int y, int w, int h) : Fl_Box (x, y, w, h, "") {

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    this->box(FL_BORDER_BOX);

    this->state = 0;
    this->color(FL_BLACK);

}