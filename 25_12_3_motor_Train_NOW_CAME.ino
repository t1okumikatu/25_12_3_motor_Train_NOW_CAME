#include "esp_camera.h"
#include <esp_now.h>
#include <WiFi.h>
// WARNING!!! PSRAM IC required for UXGA resolution and high JPEG quality
//            Ensure ESP32 Wrover Module or other board with PSRAM is selected
//            Partial images will be transmitted if image exceeds buffer size
//
//            You must select partition scheme from the board menu that has at least 3MB APP space.
//            Face Recognition is DISABLED for ESP32 and ESP32-S2, because it takes up from 15
//            seconds to process single frame. Face Detection is ENABLED if PSRAM is enabled as well
#define CAMERA_MODEL_XIAO_ESP32S3 // Has PSRAM
#include "src/camera_pins.h"
// Station（親）の STAモードMACアドレス
uint8_t stationAddress[] = {0xA0, 0xB7, 0x65, 0x58, 0x7A, 0xFC};
// データ構造体
typedef struct struct_message {
  //int command;
  float voltage;
} struct_message;
struct_message sendData;
//struct_message recvData;

// ===== 送信完了コールバック =====
void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  //Serial.print("Send Status: ");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void startCameraServer();
void setup() {
  //Serial.begin(250000);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  config();
  APSTA();
  nowpeer();
  startCameraServer();

  //Serial.print("Camera Ready! Use 'http://  ");
  Serial.println(WiFi.localIP());
  //Serial.println("' to connect");
  delay(5000);
}

void loop() {
  readV();
  // Do nothing. Everything is done in another task by the web server
  delay(500);
}