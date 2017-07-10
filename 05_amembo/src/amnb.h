//
//  mydraw.h
//  emptyExample
//
//  Created by LIFE_MAC25  on 2017/07/07.20:00ごろ
//
//　　lines

#ifndef mydraw_h
#define mydraw_h


#include "Base.h"

class amnb : public Base{
    
    vector <ofPoint> humans; //めっちゃ便利配列

    ofVec2f pos[100][100];
    
    
    
    //------
    
    float px,py = 0;//過去の座標、出発地
    float TargetX,TargetY = 0;//目的地
    float x,y = 0; //現在地
    
    int a = 200;
    int count = 0;//ランダム用
    int count2 = -400;//ランダム用
    float easing = 0.08;//抵抗
    float r = 30;//円（アメンボ）の半径
    float pr = 0; //波紋の半径
    float pr2 = -50; //波紋の半径
    float Rx,Ry;  //波紋の座標
    float Ra; //波紋のα値
    float Ra2; //波紋のα値
    float RnP;
    
public:
    
    void setup (void){
        ofBackground(0);
        
        count2 = -300;

    }
//-----------------------------------------------------
    void update (void){
        
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
        


        ofSetLineWidth(3);
        //ofNoFill();
        ofSetCircleResolution(60); //丸の解像度
        ofFill();
        ofSetColor(255, 255);  //アメンボの色
        ofDrawEllipse(x,y, r, r); //現在地、アメンボの描画
        ofDrawLine(x, y ,px, py ); //軌跡
                    x +=(TargetX - x)*easing; //目的地へ
                    y +=(TargetY - y)*easing; //目的地へ
                    px +=(x - px)*easing; //イージング、目的地へ
                    py +=(y - py)*easing; //イージング、目的地へ
        
        ofNoFill();
        ofSetColor(255, 255-Ra);  //波紋の色指定
        ofDrawEllipse(Rx,Ry, pr,pr); //波紋の表現
        
        int a = 255-Ra2;
        ofSetColor(255, a);  //待機波紋の色指定
        ofDrawEllipse(x,y, 15+pr2,15+pr2); //待機波紋の表現
        
        if(count2 > 500){       //待機波紋の描画
                        Ra2 = 2;
            pr2 = 0;     //待機波紋波紋の半径を0に
            count2 = 0;
            Ra2 = 2;
        }
        
        
        

                    pr += 2;  //波紋の波及
                    pr2 += 2;  //待機波紋の波及
                    Ra += 500/RnP;  //距離を分母にして、距離が遠いと波の減衰速度を遅くする
                    Ra2 += 3; //波紋のα値
        count += 1 +ofRandom(3) ; //
        count2 ++;
        
        
        if(count > 1500){  //カウント充したら座標更新
            
            pr = 0;
            pr2 = 3000;
            Ra = 2;
            Ra2 = 2;
            
            px = TargetX;  //出発地点に今のXの値を代入
            py = TargetY;  //出発地点に今のYの値を代入
            TargetX = ofRandom(50,ofGetWidth()-50);    //目的地を更新
            TargetY = ofRandom(50,ofGetHeight()-50);   //目的地を更新
            
            RnP = ofDist(px, py, TargetX, TargetY);  //目的地と出発地の距離を計測

            Rx = px;  //出発地点を波紋の発生地点とする
            Ry = py;  //出発地点を波紋の発生地点とする
            count = 0;
            count2 = 0;

        }

        
        for(int i = 0 ; i < humans.size(); ++ i ){
           
            if(   TargetX+50> humans[i].x && humans[i].x> TargetX-100     //人が範囲内に入ったらカウントを満たす
               && TargetY+50> humans[i].y && humans[i].y > TargetY-100){
                
                count += 1000;
            }


            
        }

}
};

#endif /* mydraw_h */
