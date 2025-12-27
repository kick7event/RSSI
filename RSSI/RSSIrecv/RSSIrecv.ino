#include <WiFi.h>
#include <esp_now.h>

// 受信コールバック
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  // RSSIの取り出し
  int rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // メイン処理
  delay(100);
}
