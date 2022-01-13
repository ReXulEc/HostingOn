/*
 * Author: ReXulEc
 * Website: rexulec.com
 */

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include "uptime_formatter.h" // "Uptime Library" by Yiannis Bourkelis
#include <TimeLib.h>
#include "data.h" // Local file
ESP8266WebServer server(80);

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

void handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String sender_id = bot.messages[i].from_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    
    if (from_name == ""){
      from_name = "Guest";
    }
    
    if(sender_id == USER_ID){
      
      if (text == "/status")
      {
        bot.sendMessage(chat_id, "Led is ON", "");
      }
  
      if (text == "/start")
      {
        String welcome = "Welcome to HostingOn, " + from_name + ".\n\n";
        welcome += "/status : Returns current status of Webserver";
        bot.sendMessage(chat_id, welcome, "Markdown");
      }
      
    } else {

      String someonetriedtosendmessage = "Someone tried send message to this bot.\n" + from_name + " | " + sender_id;
      String someonetriedtosendmessageelse = "Welcome to HostingOn,\nYou are not whitelisted.";
      bot.sendMessage(USER_ID, someonetriedtosendmessage);
      bot.sendMessage(sender_id, someonetriedtosendmessageelse);
      }
    
  }
}
 
void setup () {
  pinMode(12, OUTPUT); 
  pinMode(14, OUTPUT);
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  secured_client.setTrustAnchors(&cert);
  
  
  WiFi.begin(SSID_NAME, PASSWORD);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("IP Adress: ");
  Serial.print(WiFi.localIP());
  server.on("/", mainpage);
  server.on("/status", stats);
 
  server.begin();
  bot.sendMessage(USER_ID, "Webserver opened!");
  Serial.println(hour());
}
 
void loop() {
  server.handleClient();
  /*
  if(hour() > 21){
    digitalWrite(12, LOW);
  } else if (hour() < 7){
    digitalWrite(12, LOW);
  } else {
    digitalWrite(12, HIGH);
  }
  */
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}

//================== PAGES ==================

void mainpage() {
  Serial.print("Log | Open => Main Page");
  server.send(200, "text/html", webpageCode);
  digitalWrite(14, HIGH);
  delay(1000);
  digitalWrite(14, LOW);

}

void stats() {
  Serial.print("Opened | Status Page");
  DynamicJsonDocument doc(512);
  doc["status"] = "on";
  doc["lights"][0]["red"] = digitalRead(12);
  doc["lights"][0]["green"] = digitalRead(14);
  doc["uptime"] = uptime_formatter::getUptime();
  String buf;
  serializeJson(doc, buf);
  server.send(200, "application/json", buf);
}
