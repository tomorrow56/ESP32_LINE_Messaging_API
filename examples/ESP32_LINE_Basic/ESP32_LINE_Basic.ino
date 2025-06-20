/***********
 * ESP32 LINE Messaging API Library
 * サンプルスケッチ
 * 
 * このサンプルは、ESP32を使用してLINE Messaging APIでメッセージを送信する方法を示します。
 * 使用前に、LINE Developers ConsoleでMessaging APIのチャネルを作成し、
 * アクセストークンを取得してください。
 * 
 * 参考: https://developers.line.biz/ja/services/messaging-api/
 ***********/

#include "ESP32LineMessenger.h"

// WiFiとLINEの設定
const char* ssid = "<your SSID>";              // WiFiのSSID
const char* password = "<your Password>";      // WiFiのパスワード

// 以下からLINEチャネルアクセストークンを取得する
// https://developers.line.biz/ja/
const char* accessToken = "<your LINE Access Token>";

// デバッグモード設定
#define debug true

// ライブラリインスタンス作成
ESP32LineMessenger line;

void setup() {
  Serial.begin(115200);  // デバッグ用シリアル
  delay(100);
  
  // アクセストークン設定
  line.setAccessToken(accessToken);
  
  // デバッグモード設定（オプション）
  line.setDebug(debug);
  
  // WiFi接続
  if (line.connectWiFi(ssid, password, debug)) {
    Serial.println("WiFi connected");
    
    // メッセージ送信
    line.sendMessage("Test message from ESP32", debug);
  } else {
    Serial.println("WiFi connection failed");
  }
}

void loop() {
  // 必要に応じて繰り返し送信
  // line.sendMessage("テストメッセージ");
  // delay(10000);
}
