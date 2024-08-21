#include <ESP8266WiFi.h>

const int serverPort = 5000;

const char *password = "12345678";
const char *ssid = "esp_01swifi";

// 创建WiFiServer对象并指定端口号
WiFiServer server(5000); // 端口号5000

void setup()
{

  pinMode(0, OUTPUT);

  Serial.begin(115200);
  // 设置ESP8266为AP模式
  WiFi.softAP(ssid, password);
  Serial.println("Access Point启动");
  Serial.print("IP地址: ");
  Serial.println(WiFi.softAPIP()); // 打印AP的IP地址

  // 启动TCP服务器
  server.begin();
}

void loop()
{
  WiFiClient client = server.available(); // 检查是否有客户端连接
  if (client)
  {
    Serial.println("新客户端连接");
    while (client.connected())
    {
      bool statu = true;
      if (client.available())
      {
        String message = client.readStringUntil('\r');
        Serial.print("从STA收到: ");
        Serial.println(message);
        if (message == "ON")
        {
          Serial.println("light on");
          digitalWrite(0, statu == true ? HIGH : LOW);
          statu = !statu;
        }
        else
        {
          Serial.print("wrong message is");
          Serial.println(message);
        }
      }
      delay(10);
    }
    client.stop();
    Serial.println("客户端断开连接");
  }
}
