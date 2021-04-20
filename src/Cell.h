#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

class Cell : public Fl_Box
{
    protected:

    int state; // 0: dead, 1:alive
    int x, y;
    int w, h;

    public:

    Cell(int x, int y, int w, int h) : Fl_Box (x, y, w, h, ""){

        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;

        this->box(FL_BORDER_BOX);

        this->state = 0;
        this->color(FL_BLACK);

    }
    
    virtual void birth(){
        this->state = 1;

        this->color(FL_WHITE);
        this->redraw();

        grid[x/w][y/h] = 1;
    }

    virtual void death(){
        this->state = 0;

        this->color(FL_BLACK);
        this->redraw();

        grid[x/w][y/h] = 0;
    }

    virtual void flip(){
        if (state == 0)
            this->birth();
        else
            this->death();
    }

    virtual int handle(int e){
        return 1;
    }
};