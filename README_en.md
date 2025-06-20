# ESP32 LINE Messaging API Library

## Overview
This library enables sending messages through the LINE Messaging API using ESP32. It's designed to be compatible with the SPRESENSE_ESP8266_LINE_Messaging_API library while utilizing ESP32's native WiFi capabilities.

## Installation
1. Download this library and save it as a ZIP file
2. Open Arduino IDE, go to "Sketch" → "Include Library" → "Add .ZIP Library..."
3. Select the downloaded ZIP file to install

## Basic Usage
```cpp
#include "ESP32LineMessenger.h"

// WiFi and LINE configuration
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* accessToken = "your_line_access_token";

// Create library instance
ESP32LineMessenger line;

void setup() {
  Serial.begin(115200);
  
  // Set access token
  line.setAccessToken(accessToken);
  
  // Connect to WiFi
  if (line.connectWiFi(ssid, password, true)) {
    // Send message
    line.sendMessage("Hello from ESP32!", true);
  }
}

void loop() {
  // Additional code if needed
}
```

## Key Functions

### Constructors
```cpp
ESP32LineMessenger();  // Basic constructor
ESP32LineMessenger(const char* token);  // Constructor with access token
```

### Set Access Token
```cpp
void setAccessToken(const char* token);
```

### Connect to WiFi
```cpp
bool connectWiFi(const char* ssid, const char* password, bool showConnect = true);
```
- `ssid`: WiFi SSID
- `password`: WiFi password
- `showConnect`: Whether to show connection status on serial (default: true)
- Returns: `true` on success, `false` on failure

### Send Message
```cpp
bool sendMessage(const char* message, bool showSend = true);
```
- `message`: Message to send
- `showSend`: Whether to show send status on serial (default: true)
- Returns: `true` on success, `false` on failure

### Additional Features
```cpp
bool isWiFiConnected();  // Check WiFi connection status
void setDebug(bool debug);  // Enable/disable debug mode
```

## LINE Messaging API Setup
1. Go to [LINE Developers](https://developers.line.biz/)
2. Create a new provider
3. Create a Messaging API channel
4. Issue a long-lived channel access token
5. Set the token in your program

## Example Sketches
- `ESP32_LINE_Basic`: Basic usage example
- `ESP32_LINE_Advanced`: Example with scheduled messages and button-triggered sending

## Notes
- This library is specifically designed for ESP32
- SSL certificate verification is disabled (recommended to use proper certificates in production)
- Usage of LINE Messaging API is subject to LINE's Terms of Use

## Differences from Reference Library
- Class name changed from `LineMessenger` to `ESP32LineMessenger`
- Uses ESP32's native WiFi library instead of ESP8266's AT commands
- Added features like WiFi connection status check and debug mode

## Troubleshooting
- If WiFi connection fails, verify SSID and password
- If message sending fails, check the validity of your access token
- Enable debug mode for detailed error information

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.
