/*
 * Contoh penggunaan library DMDESP
 * dengan NTP untuk Jam
 * 
 * email : bonny@grobak.net - www.grobak.net - www.elektronmart.com
*/

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <DMDESP.h>
#include <fonts/EMKotak5x7.h>
#include <fonts/EMSans8x16.h>
// #include <fonts/BigNumber.h>
#include <fonts/BigNumberFull.h>

#define FontDefault EMKotak5x7
#define FontBesar EMSans8x16

// DMDESP Setup
#define DISPLAYS_WIDE 1 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  // Jumlah Panel P10 yang digunakan (KOLOM,BARIS)

// WIFI Setup
#define ssid      "RAJEKWESI WIFI" // Ubah sesuaikan
#define password  ""        // Ubah sesuaikan

// NTP Client Setup
const long utcOffset = 3600 * 7; // Waktu WIB
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffset);

// Variabel
uint8_t rJam;
uint8_t rMen;
uint8_t rDet;



//----------------------------------------------------------------------
// SETUP

void setup() {

  // WIFI
  WiFi.begin(ssid, password);
  Serial.begin(115200);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  // NTP
  timeClient.begin();  

  // DMDESP
  Disp.start(); // Jalankan library DMDESP
  Disp.setBrightness(1); // Tingkat kecerahan
  Disp.setFont(FontDefault); // Huruf default
  
}



//----------------------------------------------------------------------
// LOOP

void loop() {

  timeClient.update();
  
  rJam = timeClient.getHours();
  rMen = timeClient.getMinutes();
  rDet = timeClient.getSeconds();

  // JUDUL
 // Disp.setFont(FontDefault);
 // Disp.drawText(2,3,"DMDESP NTP");

  // JAM
  // char jam[9];
  // sprintf(jam,"%02d:%02d:%02d", Jam, Men, Det);
  // Disp.setFont(FontBesar);
  // Disp.drawText(0,0,jam);  
  jambesar();
  Disp.loop();

}

void jambesar()
{

  static uint8_t d;
  // static uint32_t pM;
  static uint32_t pMJam;
  static uint32_t pMKedip;
  uint32_t cM = millis();
  static boolean kedip;

  // RtcDateTime now = Rtc.GetDateTime();
  d = 0;
  char jam[3];
  char menit[3];
  char detik[3];
  char harine[18];
  char tanggale[18];
  char jamkecilnya[10];

  

    if (cM - pMJam >= 1000)
    {
      pMJam = cM;
      d++;

      // JAM
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(0, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(BigNumber);
      Disp.drawText(19, 0, menit);

      // DETIK
      //   sprintf(detik,"%02d", rDet);
      //   Disp.setFont(BigNumber);
      //    Disp.drawText(37, 0, detik);
      // tanggal
      //  sprintf(harine, "%s", weekDay[rHar]);
      //  Disp.setFont(Font4x6);
      //  Disp.drawText(98, 0, harine);
      //  sprintf(tanggale, "%02d-%s", rTgl, monthYear2[rBul]);
      //  Disp.setFont(Font4x6);
      //  Disp.drawText(97, 8, tanggale);

      // KEDIP DETIK

      if (millis() - pMKedip >= 500)
      {
        pMKedip = millis();
        kedip = !kedip;
          if (kedip )
          {
            Disp.drawRect(15, 3, 16, 5, 1, 1); // koordinat titik dua
            Disp.drawRect(15, 9, 16, 11, 1, 1);
          }
          else
          {

            Disp.drawRect(15, 0, 16, 5, 0, 0); // koordinat titik dua
            Disp.drawRect(15, 9, 16, 11, 0, 0);
          }  
      
      }

      
      
    }
  
}