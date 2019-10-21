#pragma once
#include "ofMain.h"
#include <stdlib.h>


class ofxPoseCsv{
public:
    string filePath;
    ofFile file;
    vector<ofVboMesh> poseMesh;
    int frame = 0;
    
    void load();
    void draw();
    void update();
    ofVboMesh getMesh();
    
    
    void setMode(int _mode);
    void setFrame(int _frame);
    int getFrameSize();
    void debugDraw();
    
    
};

