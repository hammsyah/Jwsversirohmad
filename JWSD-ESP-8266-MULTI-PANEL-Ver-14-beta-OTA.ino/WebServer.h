ESP8266WebServer server(80);
const char *password = "123456789";
const char *mySsid = "wifi_jwsd";
IPAddress local_ip(192, 168, 2, 1);
IPAddress gateway(192, 168, 2, 1);
IPAddress netmask(255, 255, 255, 0);

uint8_t pin_led = 2;

void wifiConnect()
{

  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(1000);

  Serial.println("Sedang menyambungkan ke Aksespoint");
  WiFi.mode(WIFI_STA);
  WiFi.begin(configwifi.wifissid, configwifi.wifipassword);
  unsigned long startTime = millis();
   //tampilkan di panel
   

  while (WiFi.status() != WL_CONNECTED)
  {

    delay(500);
    Serial.print(".");
    
    digitalWrite(pin_led, !digitalRead(pin_led));

    if (millis() - startTime > 20000)
    {
      Serial.println(" ");
      Disp.clear();
      break;
      
    }
  }

  if (WiFi.status() == WL_CONNECTED)
  {

    digitalWrite(pin_led, HIGH);
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
       
  } 
  
  else
  {

    Serial.println("Gagal tersambung ke Hotspot, mode Hotspot aktif.");

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, netmask);
    WiFi.softAP(mySsid, password);

    digitalWrite(pin_led, LOW);

    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("IP: ");
    Serial.println(local_ip);
  }
}

int jalan = 0;


void tampilkanIP()
{
   Disp.setFont(SystemFont5x7); 
   Disp.drawText(97, 0, "IP:");
 String Ipne = WiFi.localIP().toString();
    int str_len = Ipne.length() + 1;
    char char_array[str_len];
    Ipne.toCharArray(char_array, str_len); 
    static char *nama[] = {char_array};
    
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 150;
    int width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(nama[0]) + width;
    
    
        
        
        if ((millis() - pM) > Speed)
        {
          pM = millis();
          if (x < fullScroll)
          {
            ++x;
          }
          else
          {
            x = 0;
            Disp.clear();
            jalan = 1;
            
          }

          Disp.drawText(width - x, 9, nama[0]);
          
        }
    

}

//----------------------------------------------------------------------
// XML UNTUK JEMBATAN DATA MESIN DENGAN WEB
void buildXML()
{

  RtcDateTime now = Rtc.GetDateTime();
  RtcTemperature temp = Rtc.GetTemperature();
  XML = "<?xml version='1.0'?>";
  XML += "<t>";
  XML += "<rWifissid>";
  XML += configwifi.wifissid;
  XML += "</rWifissid>";
  XML += "<rYear>";
  XML += now.Year();
  XML += "</rYear>";
  XML += "<rMonth>";
  XML += now.Month();
  XML += "</rMonth>";
  XML += "<rDay>";
  XML += now.Day();
  XML += "</rDay>";
  XML += "<rHour>";
  if (now.Hour() < 10)
  {
    XML += "0";
    XML += now.Hour();
  }
  else
  {
    XML += now.Hour();
  }
  XML += "</rHour>";
  XML += "<rMinute>";
  if (now.Minute() < 10)
  {
    XML += "0";
    XML += now.Minute();
  }
  else
  {
    XML += now.Minute();
  }
  XML += "</rMinute>";
  XML += "<rSecond>";
  if (now.Second() < 10)
  {
    XML += "0";
    XML += now.Second();
  }
  else
  {
    XML += now.Second();
  }
  XML += "</rSecond>";
  XML += "<rTemp>";
  XML += temp.AsFloatDegC();
  XML += "</rTemp>";
  ////////////////////////////
  // XML += "<rJpanel>";
  // XML += config.jpanel;
  // XML += "</rJpanel>";
  ////////////////////////////
  XML += "<rIqmhs>";
  XML += config.iqmhs;
  XML += "</rIqmhs>";
  XML += "<rIqmhd>";
  XML += config.iqmhd;
  XML += "</rIqmhd>";
  XML += "<rIqmha>";
  XML += config.iqmha;
  XML += "</rIqmha>";
  XML += "<rIqmhm>";
  XML += config.iqmhm;
  XML += "</rIqmhm>";
  XML += "<rIqmhi>";
  XML += config.iqmhi;
  XML += "</rIqmhi>";
  XML += "<rDurasiAdzan>";
  XML += config.durasiadzan;
  XML += "</rDurasiAdzan>";
  XML += "<rIhti>";
  XML += config.ihti;
  XML += "</rIhti>";
  XML += "<rLatitude>";
  XML += config.latitude;
  XML += "</rLatitude>";
  XML += "<rLongitude>";
  XML += config.longitude;
  XML += "</rLongitude>";
  XML += "<rZonaWaktu>";
  XML += config.zonawaktu;
  XML += "</rZonaWaktu>";
  XML += "<rNama>";
  XML += config.nama;
  XML += "</rNama>";
  XML += "<rInfo1>";
  XML += config.info1;
  XML += "</rInfo1>";
  XML += "<rInfo2>";
  XML += config.info2;
  XML += "</rInfo2>";
  XML += "<rInfo3>";
  XML += config.info2;
  XML += "</rInfo3>";
  XML += "<rCerah>";
  XML += configdisp.cerah;
  XML += "</rCerah>";
  XML += "<rPanel>";
  XML += configdisp.jpanel;
  XML += "</rPanel>";

  XML += "</t>";
}

void handleXML()
{
  buildXML();
  server.send(200, "text/xml", XML);
}

void handleSettingDispUpdate()
{

  // timer0_detachInterrupt();

  String datadisp = server.arg("plain");

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, datadisp);
  File configFileDisp = SPIFFS.open(fileconfigdisp, "w");
  if (!configFileDisp)
  {
    Serial.println("Gagal membuka Display configFile untuk ditulis");
    return;
  }

  serializeJson(doc, configFileDisp);
  if (error)
  {
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return;
  }
  else
  {

    configFileDisp.close();
    Serial.println("Berhasil mengubah configFileDisp");
    server.send(200, "application/json", "{\"status\":\"ok\"}");
    loadDispConfig(fileconfigdisp, configdisp);
    // Disp.loop(); // Jalankan Disp loop untuk refresh LED
    //
    // delay(500);
    //  timer0_attachInterrupt(refresh);
    //  timer0_write(ESP.getCycleCount() + 40000);
    Disp.setBrightness(configdisp.cerah);
    
  }
}

void handleSettingJwsUpdate()
{

  // timer0_detachInterrupt();
  String datajws = server.arg("plain");

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, datajws);

  File configFileJws = SPIFFS.open(fileconfigjws, "w");

  if (!configFileJws)
  {
    Serial.println("Gagal membuka JWS configFile untuk ditulis");
    return;
  }

  serializeJson(doc, configFileJws);

  if (error)
  {

    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return;
  }
  else
  {

    configFileJws.close();
    Serial.println("Berhasil mengubah configFileJws");

    server.send(200, "application/json", "{\"status\":\"ok\"}");

    loadJwsConfig(fileconfigjws, config);
    // Disp.loop(); // Jalankan Disp loop untuk refresh LED

    //   delay(500);
    // timer0_attachInterrupt(refresh);
    // timer0_write(ESP.getCycleCount() + 40000);
  }
}

void handleSettingWifiUpdate()
{

  // timer0_detachInterrupt();

  String data = server.arg("plain");

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, data);

  File configFile = SPIFFS.open("/configwifi.json", "w");
  if (!configFile)
  {
    Serial.println("Error opening Wifi configFile for writing");
    return;
  }

  serializeJson(doc, configFile);

  if (error)
  {

    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return;
  }
  else
  {

    configFile.close();
    Serial.println("Berhasil mengubah configFileWifi");

    server.send(200, "application/json", "{\"status\":\"ok\"}");
    loadWifiConfig(fileconfigwifi, configwifi);
    ESP.restart();
  }
}