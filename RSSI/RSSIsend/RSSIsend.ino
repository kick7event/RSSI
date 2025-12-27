#include <WiFi.h>
#include <esp_now.h>

uint8_t broadcastAddress[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("送信ステータス: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "成功" : "失敗");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();
  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);
}

void loop() {
  const char *msg = "Hello ESPNOW";
  esp_now_send(broadcastAddress, (uint8_t *)msg, strlen(msg));
  delay(1000);
}
