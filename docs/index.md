---
layout : default
title : transfloor
---

# Transfloor プログラム

## 利用アドオン

* ofxKinect
* ofxOpenCv
* ofxOsc
* [leico/ofxJSON: A wrapper for jsoncpp for openFrameworks](https://github.com/leico/ofxJSON.git)
* [leico/ofxSimpleTimer: simple timer](https://github.com/leico/ofxSimpleTimer)

### ヘッダー読み込み設定

```xcconfig
#include "Project.xcconfig"


HEADER_SEARCH_PATHS = $(OF_CORE_HEADERS) src $(OF_PATH)/addons/ofxOsc/src/** $(OF_PATH)/addons/ofxOsc/libs/** $(OF_PATH)/addons/ofxOpenCv/** $(OF_PATH)/addons/ofxKinect/src/** $(OF_PATH)/addons/ofxKinect/libs/libusb-1.0/** $(OF_PATH)/addons/ofxKinect/libs/libfreenect/src/** $(OF_PATH)/addons/ofxKinect/libs/libfreenect/include/** $(OF_PATH)/addons/ofxJSON/src/** $(OF_PATH)/addons/ofxJSON/libs/**
```

元々存在しているopenFrameworks用設定ファイル、`Project.xcconfig`を上書きして読み込んでいる。
横に長くてみづらいので

* `$(OF_CORE_HEADERS)` 
* `src` 
* `$(OF_PATH)/addons/ofxOsc/src/**` 
* `$(OF_PATH)/addons/ofxOsc/libs/**`
* `$(OF_PATH)/addons/ofxOpenCv/**`
* `$(OF_PATH)/addons/ofxKinect/src/**`
* `$(OF_PATH)/addons/ofxKinect/libs/libusb-1.0/**`
* `$(OF_PATH)/addons/ofxKinect/libs/libfreenect/src/**`
* `$(OF_PATH)/addons/ofxKinect/libs/libfreenect/include/**`
* `$(OF_PATH)/addons/ofxJSON/src/**`
* `$(OF_PATH)/addons/ofxJSON/libs/**`
* `$(OF_PATH)/addons/ofxSimpleTimer/src/`

これらをヘッダファイルを検索する場所として設定している。末尾が `**` のパスは再帰的にフォルダ内を検索する。
何かを追加する場合、改行せずスペース区切りで続けて記述する。通常アドオンが入っているフォルダは`$(OF_PATH)/addons`で指定できる。

## XCode設定ファイルの適用方法

{% capture url %}{{site.github.url}}{% link images/01_config.png %}{% endcapture %}
{% include thumbnail.html url=url caption='
*xcconfig* 設定画面
' %}

XCodeプロジェクト設定の *info* タブ、 *configurations* のプロジェクト設定、ターゲット設定が **transfloor** になっていることを確認する。

## Kinectの指定方法

`bin -> data -> serial.json`に割り当てるKinectのシリアルが2つ、json形式で記述されている。
```json
[
 "A00364800479053A",
 "A00363A02391053A"
]
```

シリアルの確認方法は `src -> MainScreen.h -> setup_KinectCV`が
```cpp
/* =================================================================== *
 * void setup_KinectCV(void)                                           *
 * =================================================================== */
inline void MainScreen :: setup_KinectCV(void){
  
  ofxKinect :: listDevices();
  {
    ofxJSON json;
    if( ( json.open(serialfile) ) && ( ! json.isNull() ) ){
      kinect1.setup( json[0].asString() );
      kinect2.setup( json[1].asString() );
    }
    else{
      ofLogWarning() << "json.open: Can't open serial.json file, use default serial" << std :: endl;
      kinect1.setup("A00364800479053A");
      kinect2.setup("A00363A02391053A");
    }
    if( json.open(jsonfile) ){
      ofLogVerbose() << json.getRawString() << endl;
      
      kinect1.SettingData( json );
      kinect2.SettingData( json );
    }
    else{
      ofLogWarning() << "json.open: Can't open serial.json file, use default settings" << std :: endl;
    }
    json.clear();
  }
  
  return;
  
}
```

となっていて、最初の

```cpp
ofxKinect :: listDevices();
```

でコンソールに接続されているKinectのシリアルが出力されるようになっている。
これに合わせて`serial.json`の値を変更する。


## 設営時の設定

カメラの検出設定等は *main.maxpat* を利用する。同じ階層にある *interface.maxpat* は *main.maxpat* から呼び出される。

{% capture url %}{{site.github.url}}{% link images/02_main.png %}{% endcapture %}
{% include thumbnail.html url=url caption='
*main.maxpat* の画面。このパッチを利用して外部のコンピュータから操作することができる。
' %}

