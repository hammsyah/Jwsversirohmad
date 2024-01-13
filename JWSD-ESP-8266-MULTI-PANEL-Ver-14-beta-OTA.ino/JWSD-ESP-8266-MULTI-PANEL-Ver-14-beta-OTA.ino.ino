/*

   JADWAL WAKTU SHOLAT MENGGUNAKAN NODEMCU ESP8266, LED P10, RTC DS3241, BUZZER
   FITUR :  JADWAL SHOLAT 5 WAKTU DAN TANBIH IMSAK, JAM BESAR, TANGGAL, SUHU, ALARAM ADZAN DAN TANBIH IMSAK,
            DAN HITUNG MUNDUR IQOMAH DAN UBAH WAKTU LEWAT WIFI DENGAN BROWSER.


  Pin on  DMD P10     GPIO      NODEMCU               Pin on  DS3231      NODEMCU                   Pin on  Buzzer       NODEMCU
        2  A        GPIO16    D0                            SCL         D1 (GPIO 5)                       +            RX (GPIO 3)
        4  B        GPIO12    D6                            SDA         D2 (GPIO 4)                       -            GND
        8  CLK      GPIO14    D5                            VCC         3V
        10 SCK      GPIO0     D3                            GND         GND
        12 R        GPIO13    D7
        1  NOE      GPIO15    D8
        3  GND      GND       GND

  Catatan :
  o Perlu Power Eksternal 5V ke LED P10.
  o Saat Flashing (upload program) cabut sementara pin untuk buzzer.

  Eksternal Library
  - HJS589(DMD3 porting for ESP8266 by Ahmad Herman) < DMD3 by Wardi Utari @ MFH Robotic (info https://www.facebook.com/MFH.Robotic/)) < DMD : https://github.com/freetronics/DMD
  - PrayerTime : https://github.com/asmaklad/Arduino-Prayer-Times
  - RTC DS3231 : https://github.com/Makuna/Rtc
  - ArduinoJson V6 : https://github.com/bblanchon/ArduinoJson

  email : bonny@grobak.net - www.grobak.net - www.elektronmart.com


  /////////////////////////////////////////////////////////////////////////////////////////////////
  //UPDATE SKETCH AND EDIT ACAK2AN by : www.rokhmad.com
  //dengan mengganti dengan -DMD-ESP-
  hasil edit sana-sini, maaf sketch masih berantakan, silahkan di rapikan sendiri
  salam e-dukasi
  www.rokhmad.com    www.tokopedia.com/up-titl
  rokhmad1980@gmail.com
  08157712604
  2020
  ////////////////////////////////////////////////////////////////////////////////////////////////

================================================================================================
UPDATE BY hamtronik.com
pisah jadi beberapa file .h agar lebih mudah analisa programnya.
optimasi sket

31 Desember 2023


*/
#include <WebOTA.h>
#include <SPI.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <DMDESP.h>
// #include <FansElectronics_DM12ESP.h>
#include <fonts/Arial_Black_16.h>
#include <fonts/angka6x13.h>
#include <fonts/BigNumberFull.h>

#include <fonts/DejaVuSansBold9.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/angkasm47.h>
#include <fonts/Font3x5.h>
#include <fonts/Britannic.h>
#include <fonts/Tahoma.h>
#include <fonts/arab6x13.h>
#include <fonts/Font4x6.h>
#include <fonts/System_Min5x7.h>
#include <fonts/System4x7.h>
#include <fonts/CourierNew10.h>

#include <PrayerTimes.h>
#include "Panel.h"
#include "Config.h"
#include "WebPage.h"
#include "RTC.h"

#include "WebServer.h"
#include "Buzzer.h"
#include "TampilJws.h"

void Disp_init()
{

  // Disp.start();
  //  timer0_attachInterrupt(refresh);
  //  timer0_write(ESP.getCycleCount() + 40000);
  // Disp.clear();
}

void setup()
{

  // Other init code here (WiFi, etc)

  // To use a specific port and path uncomment this line
  // Defaults are 8080 and "/webota"
  // webota.init(8888, "/update");
http: // 192.168.2.1:8080/webota
  // http://esp-ota.local:8080/webota

  RtcDateTime now = Rtc.GetDateTime();
  int tahun = now.Year();
  int bulan = now.Month();
  int tanggal = now.Day();
  get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);

  //
  Serial.begin(115200);
  Disp.start(); // Jalankan library DMDESP
  //  Disp.begin(); 
  // RTC D3231

  mulaiRTC();

  pinMode(pin_led, OUTPUT);
  SPIFFS.begin();

  loadWifiConfig(fileconfigwifi, configwifi);
  loadJwsConfig(fileconfigjws, config);
  loadDispConfig(fileconfigdisp, configdisp);
  loadSettConfig(fileconfigsett, configsett);
  LoadDataAwal();

  WiFi.hostname("HAMTRONIK_ESP8266");
  WiFi.begin(configwifi.wifissid, configwifi.wifipassword);

  wifiConnect();

  server.on("/", []()
            {
    server.send_P(200, "text/html", setwaktu);

    if (server.hasArg("date")) {

      uint16_t jam;
      uint8_t menit;
      uint8_t detik;
      String sd = server.arg("date");
      String lastSd;

      jam = ((sd[0] - '0') * 1000) + ((sd[1] - '0') * 100) + ((sd[2] - '0') * 10) + (sd[3] - '0');
      menit = ((sd[5] - '0') * 10) + (sd[6] - '0');
      detik = ((sd[8] - '0') * 10) + (sd[9] - '0');

      if (sd != lastSd) {
        RtcDateTime now = Rtc.GetDateTime();
        uint8_t hour = now.Hour();
        uint8_t minute = now.Minute();
        Rtc.SetDateTime(RtcDateTime(jam, menit, detik, hour, minute, 0));
        lastSd = sd;
      }

      server.send ( 404 , "text", message );

    }

    if (server.hasArg("time")) {

      String st = server.arg("time");
      String lastSt;
      uint8_t jam = ((st[0] - '0') * 10) + (st[1] - '0');
      uint8_t menit = ((st[3] - '0') * 10) + (st[4] - '0');

      if (st != lastSt) {
        RtcDateTime now = Rtc.GetDateTime();
        uint16_t year = now.Year();
        uint8_t month = now.Month();
        uint8_t day = now.Day();
        Rtc.SetDateTime(RtcDateTime(year, month, day, jam, menit, 0));
        lastSt = st;
      }
      server.send ( 404 , "text", message );

    } });

  server.on("/toggle", toggleLED);

  server.on("/setwifi", []()
            { server.send_P(200, "text/html", setwifi); });
  server.on("/settingwifi", HTTP_POST, handleSettingWifiUpdate);
  
  server.on("/setjws", []()
            { server.send_P(200, "text/html", setjws); });
  server.on("/settingjws", HTTP_POST, handleSettingJwsUpdate);

  server.on("/setdisplay", []()
            { server.send_P(200, "text/html", setdisplay); });
  server.on("/settingdisp", HTTP_POST, handleSettingDispUpdate);
  
   server.on("/setdsetting", []()
            { server.send_P(200, "text/html", setdsetting); });
  server.on("/setting", HTTP_POST, handleSetting);

  server.on("/reboot", HTTP_GET, handleReboot);
  
  server.on("/xml", handleXML);
  
  server.begin();
  Serial.println("HTTP server started");

  delay(1000);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  delay(50);
  BuzzerPendek();

  UpdateWaktu();
  // Disp_init();
  // Disp.loop();//BARU
  // Disp.start(); // Jalankan library DMDESP
  Disp.setBrightness(configdisp.cerah);
  branding();
}

///////////////////////////////////////////loop/////////////
void loop()
{

  webota.handle();

  // Disp.setDoubleBuffer(true);
  Disp.loop(); // Jalankan Disp loop untuk refresh LED
  //  Disp.update();
  server.handleClient();
  UpdateWaktu();
 
 if(jalan!=1){
   tampilkanIP();
 } else {

  switch (tampilanutama)
  {
  case 0:
    if (configsett.jpanel == 4)
    {
      tampilanjam = 0;
    }
    if (configsett.jpanel == 3)
    {
      tampilanjam = 1;
    }
    if (configsett.jpanel == 2)
    {
      tampilanjam = 2;
    }
    if (configsett.jpanel == 1)
    {
      tampilanjam = 3;
    }

    tampilan();
    break;
  case 1:
    if(configsett.fungsi==1) Iqomahku();
    break;

  case 2:
    if(configsett.fungsi==1) peringatan();
    break;
  case 3:
    if(configsett.fungsi==1) jamciliksholat();
    break;
  }
 }  
}

//----------------------------------------------------------------------
// MODE TAMPILAN JAM

void tampilan()
{

  switch (tampilanjam)
  {

  case 0:
    displayku();
    if(configsett.fungsi==1) saatadzan();
    break;
  case 1:
    displaykutiga();
    if(configsett.fungsi==1) saatadzan();
    break;
  case 2:
    displaykudua();
    if(configsett.fungsi==1) saatadzan2();
    break;
  case 3:
    displaykusatu();
    if(configsett.fungsi==1) saatadzan2();
    break;
  }
}
