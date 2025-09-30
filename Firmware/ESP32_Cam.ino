#include "esp32-hal-ledc.h"
#include "config.h"
#include <WiFiClientSecure.h>
#include "esp_camera.h"
#include "Base64.h"
#include "time.h"
#include "lwip/apps/sntp.h"

#define CAMERA_MODEL_AI_THINKER
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

// Pin definitions
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22
#define LED_GPIO_NUM 4

const char *folder = FOLDER;
const char *scriptID = SCRIPT_ID;
const char *wifiNetwork = WIFI_NETWORK;
const char *password = PASSWORD;
const char *host = HOST;
const int port = PORT;

int pic_num = 0;

bool connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiNetwork, password);
  int retry = 20;
  while (WiFi.status() != WL_CONNECTED && retry-- > 0) {
    delay(500);
  }
  return WiFi.status() == WL_CONNECTED;
}

void IRAM_ATTR isr() { pic_num++; }

void setup() {
  Serial.begin(115200);
  pinMode(14, INPUT_PULLDOWN);
  attachInterrupt(14, isr, RISING);
  connectWifi();
}

void loop() {
  if(pic_num>0) {
    camera_fb_t *fb = getPicture();
    if (WiFi.status() == WL_CONNECTED) {
      sendPhotoDrive(fb);
      pic_num--;
    }
    esp_camera_fb_return(fb);
  }
}

esp_err_t initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 2;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 2;
    config.fb_count = 1;
  }

  return esp_camera_init(&config);
}

void sendPhotoDrive(camera_fb_t *fb) {
  WiFiClientSecure client;
  client.setInsecure();
  if (client.connect(host, port)) {
    String url = "/macros/s/" + String(scriptID) + "/exec?folder=" + String(folder);
    client.println("POST " + url + " HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Transfer-Encoding: chunked");
    client.println();

    int fbLen = fb->len;
    char *input = (char *)fb->buf;
    int chunkSize = 3000;
    char output[base64_enc_len(chunkSize) + 1];
    for (int i = 0; i < fbLen; i += chunkSize) {
      int l = base64_encode(output, input, min(fbLen - i, chunkSize));
      client.print(l, HEX); client.print("\r\n");
      client.print(output); client.print("\r\n");
      input += chunkSize;
    }
    client.print("0\r\n\r\n");
  }
}

camera_fb_t *getPicture() {
  esp_err_t err = initCamera();
  if (err != ESP_OK) return NULL;
  ledcSetup(2, 5000, 8);
  ledcAttachPin(LED_GPIO_NUM, 2);
  ledcWrite(2, 255);
  delay(200);
  camera_fb_t *fb = esp_camera_fb_get();
  ledcWrite(2, 0);
  return fb;
}
