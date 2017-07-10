//
//  takami.h
//  emptyExample
//
//  Created by asamiTakami on 2015/12/01.
//
//

#ifndef emptyExample_takami_h
#define emptyExample_takami_h


#include "Base.h"
#include "Particle.h"

class takami : public Base{
    
private:
    
    vector < ofPoint > humans; //vector 可変長配列　超便利配列！
    
    vector< Particle > particles ;
    
    vector< int > col;
    vector< float > kaiten ;
    static const int NUM = 200;
    
    
public:
    
    
    void setup(void){
        
        ofSetFrameRate(60);
        ofSetBackgroundAuto(true);
        ofFill();
        
        Particle :: resize(ofGetWidth(), ofGetHeight());
        
        humans   .clear();
        particles.clear();
        col      .clear();
        kaiten   .clear();
        
        for (int i = 0; i < NUM; i++) {
            int c;
            c = ofRandom(15,210);
            
            col.push_back(c);
            
            float k = ofRandom(360);
            kaiten.push_back(k);
            
            
            Particle p;
            p.friction = 0.002;
            p.setup(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), ofVec2f(0, 0));
            particles.push_back(p);
        }
        
        
    }
    
    
    void osc(vector<ofxOscMessage> &m){
        
        humans.resize(m.size());// m.size()でvectorの大きさ、resizeでサイズ変更
        int j = 0;
        for(int i = 0 ; i < m.size() ; ++i ){
            if(m[i].getAddress()== "/human"){
                
                humans[j].x = m[i].getArgAsInt32(0);
                humans[j].y = m[i].getArgAsInt32(1);
                humans[j].z = m[i].getArgAsInt32(2);
                
                ++j;
            }
        }
    }
    
    
    
    
    void update(void){
        
        for (int i = 0; i < particles.size(); i++){
            // パーティクルの数だけ計算
            
            // 力をリセット
            particles[i].resetForce();
            for (int j = 0; j < humans.size(); j++){
                //引力
                particles[i].addRepulsionForce(humans[j].x, humans[j].y, 300, 0.4);
            }
            // パーティクル更新
            particles[i].update();
            // 画面の端にきたら反対側へ
            particles[i].bounceOffWalls();
        }
        
        
    }
    
    
    
    void draw(void){
        
        for (int i = 0; i < particles.size(); i++) {
            
            //ofSetColor(col[i]);
            ofColor coll;
            
            float radian     = ofMap(particles[i].position.y, 0, ofGetHeight(), 0.0f, TWO_PI);
            float brightness = ofClamp( (sin(radian + ofGetElapsedTimef() * 1.2) - 0.5) * 2, -1, 1);
            brightness = ofMap(brightness, -1, 1, 200, 255);
            
            float size = ofClamp( (sin(radian + ofGetElapsedTimef() * 1.2) - 0.5) * 2, -1, 1);
            size = ofMap(size, -1, 1, 0, 8);
            
            coll.setHsb(col[i], 180, brightness);
            ofSetColor(coll);
            ofPushMatrix();
            
            ofTranslate(particles[i].position.x, particles[i].position.y);
            ofRotateZ(ofGetFrameNum()+kaiten[i]);
            
            if(i <= particles.size()/3){
                ofDrawRectangle(0, 0, 20 + size, 20 + size);
                ofPopMatrix();
                continue;
            }
            
            
            if(i <= particles.size()*2/3){
                ofSetCircleResolution(32);
                ofDrawCircle(0,0,12 + size / 2);
                ofPopMatrix();
                continue;
            }
            
            ofSetCircleResolution(3);
            ofDrawCircle(0, 0, 16 + size / 2);
            ofPopMatrix();
            
            
        }
    }
    
    void resize(const int w, const int h){
        Base :: resize(w, h);
        Particle :: resize(w, h);
        
        setup();
        
        
    }
    
    
    
    
    
};



#endif
