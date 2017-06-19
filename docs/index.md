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
* `$(OF_PATH)/addons/ofxJSON/libs/**
* `$(OF_PATH)/addons/ofxSimpleTimer/src/`

これらをヘッダファイルを検索する場所として設定している。末尾が `**` のパスは再帰的にフォルダ内を検索する。
何かを追加する場合、改行せずスペース区切りで続けて記述する。通常アドオンが入っているフォルダは`$(OF_PATH)/addons`で指定できる。

## XCode設定ファイルの適用方法

{% capture url %}{{site.github.url}}{% link images/01_config.png %}{% endcapture %}
{% include thumbnail.html url=url caption='
*xcconfig* 設定画面
' %}

