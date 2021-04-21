#include <iostream>
#include <vector>
using namespace std;

/* Abstract class that stores a particular configuration of the world */

class Config{

    protected:
    int nr, nc;

    public:

    vector<vector<int>> data;

    virtual void init() = 0;

    Config(){}

    int sizeR(){
        return nr;
    }

    int sizeC(){
        return nc;
    }

};
