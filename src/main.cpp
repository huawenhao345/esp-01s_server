#include <ESP8266WiFi.h>

const int serverPort = 5000;

const char *ssid = "esp_01swifi";
const char *password = "12345678";

void setup() {
  Serial.begin(115200);
  // 设置ESP8266为AP模式
  WiFi.softAP(ssid, password);
  Serial.println("Access Point启动");
  Serial.print("IP地址: ");
  Serial.println(WiFi.softAPIP()); // 打印AP的IP地址

  // 启动TCP服务器
  Server.begin();
}

void loop() {
  WiFiClient client = Server.available(); // 检查是否有客户端连接
  if (client) {
    Serial.println("新客户端连接");
    while (client.connected()) {
      if (client.available()) {
        String message = client.readStringUntil('\r');
        Serial.print("从STA收到: ");
        Serial.println(message);
      }
    }
    client.stop();
    Serial.println("客户端断开连接");
  }
}