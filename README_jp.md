# ESP32 LINE Messaging API ライブラリ使用方法

## 概要
このライブラリは、ESP32を使用してLINE Messaging APIでメッセージを送信するためのものです。
SPRESENSE_ESP8266_LINE_Messaging_APIライブラリとの互換性を持ちながら、ESP32のネイティブWiFi機能を活用しています。

## インストール方法
1. このライブラリをダウンロードし、ZIP形式で保存します
2. Arduino IDEを開き、「スケッチ」→「ライブラリをインクルード」→「.ZIP形式のライブラリをインストール」を選択
3. ダウンロードしたZIPファイルを選択してインストール

## 使用方法

### 基本的な使い方
```cpp
#include "ESP32LineMessenger.h"

// WiFiとLINEの設定
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* accessToken = "your_line_access_token";

// ライブラリインスタンス作成
ESP32LineMessenger line;

void setup() {
  Serial.begin(115200);
  
  // アクセストークン設定
  line.setAccessToken(accessToken);
  
  // WiFi接続
  if (line.connectWiFi(ssid, password, true)) {
    // メッセージ送信
    line.sendMessage("Hello from ESP32!", true);
  }
}

void loop() {
  // 必要に応じて追加の処理
}
```

### 主要関数

#### コンストラクタ
```cpp
ESP32LineMessenger();  // 基本コンストラクタ
ESP32LineMessenger(const char* token);  // アクセストークン付きコンストラクタ
```

#### アクセストークン設定
```cpp
void setAccessToken(const char* token);
```

#### WiFi接続
```cpp
bool connectWiFi(const char* ssid, const char* password, bool showConnect = true);
```
- `ssid`: WiFiのSSID
- `password`: WiFiのパスワード
- `showConnect`: 接続状況をシリアルに表示するかどうか
- 戻り値: 接続成功でtrue、失敗でfalse

#### メッセージ送信
```cpp
bool sendMessage(const char* message, bool showSend = true);
```
- `message`: 送信するメッセージ
- `showSend`: 送信状況をシリアルに表示するかどうか
- 戻り値: 送信成功でtrue、失敗でfalse

#### 拡張機能
```cpp
bool isWiFiConnected();  // WiFi接続状態確認
void setDebug(bool debug);  // デバッグモード設定
```

## LINE Messaging APIの設定方法
1. [LINE Developers](https://developers.line.biz/)にアクセス
2. 新規プロバイダーを作成
3. Messaging APIチャネルを作成
4. チャネルアクセストークン（長期）を発行
5. 発行したトークンをプログラムに設定

## サンプルスケッチ
- `ESP32_LINE_Basic`: 基本的な使い方のサンプル
- `ESP32_LINE_Advanced`: 定期送信やボタン入力による送信のサンプル

## 注意事項
- このライブラリはESP32専用です
- SSL証明書の検証は無効化されています（本番環境では適切な証明書を使用することを推奨）
- LINE Messaging APIの利用には、LINEの利用規約に従ってください

## 参照ライブラリとの違い
- クラス名が`LineMessenger`から`ESP32LineMessenger`に変更
- ESP8266のATコマンド方式からESP32のネイティブWiFiライブラリを使用
- 拡張機能としてWiFi接続状態確認やデバッグモード設定を追加

## トラブルシューティング
- WiFi接続に失敗する場合は、SSIDとパスワードを確認
- メッセージ送信に失敗する場合は、アクセストークンの有効性を確認
- デバッグモードを有効にすると、詳細なエラー情報が表示されます
