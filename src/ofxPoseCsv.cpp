//
//  ofxPoseCsv.cpp
//  csvParseTest
//
//  Created by 奥山裕大 on 10/20/31 H.
//

#include "ofxPoseCsv.hpp"

using namespace glm;


void ofxPoseCsv::load(){
    int lineCount = 0;
    int current_frame = -1;
    ofFileDialogResult openFileResult=ofSystemLoadDialog("load");//window開いてね！
    if(openFileResult.bSuccess){
        filePath =openFileResult.getPath();//ファイル開いてbufferに読むよ！
        cout<<filePath<<endl;
        ofLogVerbose("User selected a file");
        
        file.open(filePath);
        
        ofBuffer buffer(file);
        
        for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
            string line = *it;
            //Split line into strings
            //一行ずつ読んで先頭の以外は格納するよ！
            //dummy,frame,human,point,x,y で格納されてる
            //frameの数だけmesh準備する必要あるね！
            //一人を想定してるからhumanはすっ飛ばしていいね！
            //vec3で格納するけど2Dでの推定だからzは使わない、そこにpointいれ込んじゃいましょ
            if(lineCount !=0){
                vector<string> words = ofSplitString(line, ",");
                if(atoi(words[1].c_str()) != current_frame){
                    
                    current_frame++;
                    
                    ofVboMesh tmp;
                    tmp.setMode(OF_PRIMITIVE_POINTS);
                    poseMesh.push_back(tmp);
                }
                poseMesh[current_frame].addVertex(vec3(atoi(words[4].c_str()),atoi(words[5].c_str()),atoi(words[3].c_str())));
                
            }
            lineCount++;
        }
        
        cout<<poseMesh.size()<<endl;
        
    }else{
        ofLogVerbose("User hit cancel");
    }
}


void ofxPoseCsv::draw()
{
    poseMesh[frame].draw();
}


void ofxPoseCsv::setMode(int _mode){
    for(int i = 0;i<poseMesh.size();i++){
        if(_mode == 0){
            poseMesh[i].setMode(OF_PRIMITIVE_POINTS);
        }
        if(_mode == 1){
            poseMesh[i].setMode(OF_PRIMITIVE_LINES);
        }
        if(_mode == 2){
            poseMesh[i].setMode(OF_PRIMITIVE_LINE_LOOP);
        }
        if(_mode == 3){
            poseMesh[i].setMode(OF_PRIMITIVE_TRIANGLES);
        }
        if(_mode == 4){
            poseMesh[i].setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        }
        
        
    }
}


void ofxPoseCsv::setFrame(int _frame){
    frame = _frame;
}


int ofxPoseCsv::getFrameSize(){
    return  poseMesh.size();
}


void ofxPoseCsv::debugDraw(){
    poseMesh[frame].drawVertices();
    for(int i = 0;i<poseMesh[frame].getNumVertices();i++){
        vec3 loc = poseMesh[frame].getVertex(i);
        ofDrawCircle(loc.x,loc.y,2);
        ofDrawBitmapString(ofToString(loc.z),loc.x,loc.y);
    }
}


void ofxPoseCsv::update(){
    frame++;
    frame= frame%getFrameSize();
}




