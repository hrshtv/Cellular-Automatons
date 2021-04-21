#include <iostream>
#include <vector>
using namespace std;

/* Abstract class that specifies the initial configuration of the world */

class Config{

    protected:
    int n;

    public:

    vector<vector<int>> data;

    virtual void init() = 0;

    Config(){}

    int size(){
        return n;
    }

};
