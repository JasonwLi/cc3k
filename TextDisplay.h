#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H
#include <iostream>
#include <vector>

using namespace std;

class TextDisplay {
private
    vector<vector<char>> theDisplay;
public:
    int const length;
    int const width;
    TextDisplay(int length, int width);
    ~TextDisplay();
    void print(ostream& out);
    void notify(int length, int width, char ch);

};

#endif 
