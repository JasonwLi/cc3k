#include <iostream>
#include "TextDisplay.h"

using namespace std;

void TextDisplay::notify(int length, int width, char ch){
    theDisplay[length][width] = ch;
}

void TextDisplay::print(ostream &out){
    int i;
    int j;
    for (i=0; i < length; i++){
        for(j=0; j < width; j++){
            out << theDisplay[i][j];
        out << endl;
    return;
}

TextDisplay::TextDisplay(int length, int width):length(length), width(width){
    for (int i = 0; i < length; i++){
        vector<char> line;
        for (int k = 0; k < width; k++){
            line.push_back(' ');
        }
        theDisplay.push_back(line);
    }
}

TextDisplay::~TextDisplay(){}
