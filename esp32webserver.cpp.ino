/**
 * Simple Web Server in ESP32 with basic routing in C++ - Starter Code
 * By Michele Mincone on 14 April 2024, Abruzzo, Italy
 *
 * This is a simple starter code to kickstart a simple web server on your ESP32.
 *
 * Basically, thanks to this code you'll be able to run your very simple web server on your
 * ESP32 to control LEDs, like I did to create this kickstarter code.
 *
 * You can model this code to your needs creating the project of your dreams.
 *
 * Make sure to install Arduino IDE on your PC and to correctly connect to your ESP32 board.
 *
 * Be sure to also have ESP32 drivers installed on your PC to correctly read the bord.
 *
 * Instead of ARDUINO IDE, you can use PlatformIO for Visual Studio Code.
 *
 * I tested this code on ESP32-WROOM-32 and on the ESP32-S3
 */
#include <WiFi.h>
#include <WebServer.h>

/**
 * Password name (SSID) and password
 */
const char* ssid = "wifi_name";
const char* password = "wifi_password";

/**
 * Compressed html web page.
 */
const char* html_page = "<!DOCTYPE html><html lang='en'><head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Document</title> <style> a { display: block; color: #fff; background: #0c0c0c; padding: 10px; margin: 10px; text-decoration: none; width: max-content; } </style></head><body> <h1>ESP 32 LED Test</h1> <a href='/ledon' role='button' btn-attr='off'>Accendi LED</a> <a href='/ledoff' role='button' btn-attr='on'>Spegni LED</a> <script> const links = document.querySelectorAll('a'); const XHR = new XMLHttpRequest(); links.forEach(link => { link.addEventListener('click', async (e) => { e.preventDefault() const mode = link.getAttribute('btn-attr') const endpoint = `led${mode}` await fetch(`http://192.168.41.119/${endpoint}`); }) }) </script></body></html>";

// Set the web server to port 80
WebServer server(80);

// 18th pin for the LED.
int led1 = 18;

void setup() {
  // Setup of the pins
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);

  pinMode(led1, OUTPUT);
  Serial.begin(9600);

  // Setup the wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Start to connect
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Basic routing for the server
  server.on("/", homePage);
  server.on("/ledon", ledOn);
  server.on("/ledoff", ledOff);

  // Start the server
  server.begin();
}

/**
 * In the loop handle the client.
 */
void loop() {
  server.handleClient();
  delay(2);
}

// Handler function for the homepage
void homePage() {
  server.send(200, "text/html", html_page);
}

// Handler function for the ledOn page
void ledOn() {
  digitalWrite(led1, HIGH);
  server.send(200, "text/html", html_page);
}

// Handler function for the ledOff page
void ledOff() {
  digitalWrite(led1, LOW);
  server.send(200, "text/html", html_page);
}
