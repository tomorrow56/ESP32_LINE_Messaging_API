/***********
 * ESP32 LINE Messaging API Library
 * 応用サンプルスケッチ
 * 
 * このサンプルは、ESP32を使用してLINE Messaging APIでメッセージを定期的に送信する方法を示します。
 * また、ボタン入力によるメッセージ送信のトリガー例も含まれています。
 * 
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

// ボタン入力ピン（必要に応じて変更）
const int buttonPin = 0;  // ESP32の場合、多くのボードではBOOTボタンがGPIO0に接続されています

// 定期送信の間隔（ミリ秒）
const unsigned long sendInterval = 60000;  // 1分間隔

// 前回送信時刻
unsigned long lastSendTime = 0;

// ライブラリインスタンス作成
ESP32LineMessenger line;

void setup() {
  Serial.begin(115200);  // デバッグ用シリアル
  delay(100);
  
  // ボタンピン設定
  pinMode(buttonPin, INPUT_PULLUP);
  
  // アクセストークン設定
  line.setAccessToken(accessToken);
  
  // デバッグモード設定（オプション）
  line.setDebug(debug);
  
  // WiFi接続
  if (line.connectWiFi(ssid, password, debug)) {
    Serial.println("WiFi connected");
    
    // 起動メッセージ送信
    line.sendMessage("ESP32 device started", debug);
  } else {
    Serial.println("WiFi connection failed");
  }
}

void loop() {
  // WiFi接続確認
  if (!line.isWiFiConnected()) {
    Serial.println("WiFi connection lost. Reconnecting...");
    line.connectWiFi(ssid, password, false);
    delay(1000);
    return;
  }
  
  // ボタン入力によるメッセージ送信
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button pressed, sending message...");
    line.sendMessage("Button pressed on ESP32 device", debug);
    
    // チャタリング防止
    delay(500);
    while (digitalRead(buttonPin) == LOW) {
      delay(10);
    }
  }
  
  // 定期的なメッセージ送信
  unsigned long currentTime = millis();
  if (currentTime - lastSendTime >= sendInterval) {
    Serial.println("Sending periodic message...");
    
    // センサー値などを含めることも可能
    String message = "Periodic update from ESP32\n";
    message += "Uptime: " + String(currentTime / 1000) + " seconds";
    
    line.sendMessage(message.c_str(), debug);
    lastSendTime = currentTime;
  }
  
  // その他の処理
  delay(100);
}
