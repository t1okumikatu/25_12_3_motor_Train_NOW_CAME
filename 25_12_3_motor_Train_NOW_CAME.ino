#include "esp_camera.h"
#include <esp_now.h>
#include <WiFi.h>
#include "constant.h"

// WARNING!!! PSRAM IC required for UXGA resolution and high JPEG quality
//            Ensure ESP32 Wrover Module or other board with PSRAM is selected
//            Partial images will be transmitted if image exceeds buffer size
//
//            You must select partition scheme from the board menu that has at least 3MB APP space.
//            Face Recognition is DISABLED for ESP32 and ESP32-S2, because it takes up from 15
//            seconds to process single frame. Face Detection is ENABLED if PSRAM is enabled as well
#define CAMERA_MODEL_XIAO_ESP32S3 // Has PSRAM
#include "src/camera_pins.h"
//struct_message recvData;
// ===== 受信コールバック =====
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&recvData, incomingData, sizeof(recvData));
  Serial.println("recv.newvoltage");
  Serial.println(recvData.newvoltage);
  switch (recvData.flag) {
    case 0: Serial.println("停止");
    brake(); break;
    case 1: Serial.println("前進"); 
    forward(170);break;
    case 2: Serial.println("後退"); 
    reverse(150); break;
    default: break;
  }
}
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
  ledcAttachChannel(in1, freq, resolution,ch1);
  ledcAttachChannel(in2, freq, resolution,ch2);
  config();
  APSTA();
  StatiNowpeer();
  startCameraServer();

  //Serial.print("Camera Ready! Use 'http://  ");
  Serial.println(WiFi.localIP());
  //Serial.println("' to connect");
  delay(5000);
}

void loop() {
  //forward(180);
  readV();
  // Do nothing. Everything is done in another task by the web server
  delay(500);
}