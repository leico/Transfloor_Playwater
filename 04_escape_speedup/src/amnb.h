//
//  mydraw.h
//  emptyExample
//
//  Created by LIFE_MAC25  on 2017/07/07.
//
//　　lines

#ifndef mydraw_h
#define mydraw_h


#include "Base.h"

class amnb : public Base{
    
    vector <ofPoint> humans; //めっちゃ便利配列
    float * fftSmoothed;
    int nBandsToGet;
    
    ofSoundPlayer synth;
    ofSoundPlayer snare;

    ofVec2f pos[100][100];
    
    
    
    //------
    
    float px,py = 0;//過去の座標、出発地
    float TargetX,TargetY = 0;//目的地
    float x,y = 0; //現在地
    
    int a = 200;
    int count = 0;//ランダム用
    float easing = 0.05;//抵抗
    float r = 10;//円（アメンボ）の半径
    float pr = 0; //波紋の半径
    float Rx,Ry;  //波紋の座標
    float Ra; //波紋のα値
    float RnP;
    
public:
    
    void setup (void){
        ofBackground(0);
        
        fftSmoothed = new float[8190];
        for(int i = 0; i < 8190; i++){ //8190
            fftSmoothed[i]=0;
        }
        nBandsToGet = 1;
        
        //Audioをロード
        /*
        synth.load("sound/4synth_bip.wav");
        synth.setVolume(0.8f);
        synth.setLoop(true);
        synth.play();
        
        snare.load("sound/5snare_bip.wav");
        snare.setVolume(0.8f);
        snare.setLoop(true);
        snare.play();
        */
        
        
        for(int x = 0 ; x < 100 ; ++ x ){
            for(int y = 0 ; y < 100 ; ++y){
                pos[x][y].x = x * 101; //円のxの間隔
                pos[x][y].y = y * 100; //円のyの間隔
            }
        }

    }
//-----------------------------------------------------
    void update (void){
        
        ofBackground(0,0,0);

        

    }
//-----------------------------------------------------
    void osc (vector <ofxOscMessage> &m){
        humans.resize( m.size());
        // /human x y z
        
        int j = 0;
        for(int i = 0; i < m.size() ; ++ i){
        
            if(m[i].getAddress() == "/human"){
                humans[j].x = m[i].getArgAsInt32(0);
                humans[j].y = m[i].getArgAsInt32(1);
                humans[j].z = m[i].getArgAsInt32(2);
                
                ++ j;
            }
        }

    }
//------------------------------------------------------
    void draw (void){
        

        
        ofNoFill();
        ofSetCircleResolution(60); //丸の解像度
        ofSetColor(255, 255);  //アメンボの色
        ofDrawEllipse(x,y, r, r); //現在地、アメンボの描画
        ofDrawLine(x, y ,px, py ); //軌跡
                    x +=(TargetX - x)*easing; //目的地へ
                    y +=(TargetY - y)*easing; //目的地へ
                    px +=(x - px)*easing; //イージング、目的地へ
                    py +=(y - py)*easing; //イージング、目的地へ
        
        ofNoFill();
        ofSetColor(255, 255-Ra);  //アメンボの色
        ofDrawEllipse(Rx,Ry, pr,pr); //波紋の表現
        
        
        if(TargetX == x| TargetY == y){
                ofSetColor(255, a);
                ofDrawEllipse(x,y, pr,pr); //現在地
        
        }

                    pr += 2;
                    Ra += 500/RnP;  //距離を分母にして、距離が遠いと波の減衰速度を遅くする
        
        
        count += 1+ofRandom(3) ; //
/*
        if(   TargetX+50> ofGetMouseX()&& ofGetMouseX()> TargetX-100     //マウスが範囲内に入ったらカウントを満たす
           && TargetY+50> ofGetMouseY()&& ofGetMouseY()> TargetY-100){
        
            count += 1000;
        }
*/        

        
        
        if(count > 1000){  //カウント充したら座標更新
            
            pr = 0;
            Ra = 2;
            
            px = TargetX;  //出発地点に今のXの値を代入
            py = TargetY;  //出発地点に今のYの値を代入
            TargetX = ofRandom(ofGetWidth());    //目的地を更新
            TargetY = ofRandom(ofGetHeight());   //目的地を更新
            
            RnP = ofDist(px, py, TargetX, TargetY);  //目的地と出発地の距離を計測

            Rx = px;  //出発地点を波紋の発生地点とする
            Ry = py;  //出発地点を波紋の発生地点とする
            count = 0;
            

        }
        
        
        //cout<<"[1]"<<Ra<<endl;
        //cout<<"[2]"<<RnP<<endl;
        //cout<<"[3]"<<ofGetMouseX()<<endl;
        //cout<<"[2]"<<RnP<<endl;
        
        

        
        for(int i = 0 ; i < humans.size(); ++ i ){
           
            if(   TargetX+50> humans[i].x && humans[i].x> TargetX-100     //人が範囲内に入ったらカウントを満たす
               && TargetY+50> humans[i].y && humans[i].y > TargetY-100){
                
                count += 1000;
            }


            
        }

}
};

#endif /* mydraw_h */
