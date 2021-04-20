#include <string>
#include <iostream>
using namespace std;

template<typename T>
void print(T s){
    cout << s << endl;
}

char* int2CharStar(int x){
    // Converts int to char*
    char *c = new char[3]; // At max 3 chars: "16\0" 
    sprintf(c, "%d", x);
    return c;
}
