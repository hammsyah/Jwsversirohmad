/*
 * Contoh penggunaan library DMDESP
 * 
 * email : bonny@grobak.net - www.grobak.net - www.elektronmart.com
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


//SETUP DMD
#define DISPLAYS_WIDE 4 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  // Jumlah Panel P10 yang digunakan (KOLOM,BARIS)



//----------------------------------------------------------------------
// SETUP

void setup() {

  // DMDESP Setup
  Disp.start(); // Jalankan library DMDESP
  Disp.setBrightness(1); // Tingkat kecerahan
  Disp.setFont(SystemFont5x7); // Tentukan huruf
  
}



//----------------------------------------------------------------------
// LOOP

void loop() {

  Disp.loop(); // Jalankan Disp loop untuk refresh LED

  Disp.drawText(95,0,"DMDESP"); // Tampilkan teks
  TeksJalan(8, 50); // Tampilkan teks berjalan TeksJalan(posisi y, kecepatan);

}


//--------------------------
// TAMPILKAN SCROLLING TEKS

static char *teks[] = {"Teks berjalan dengan DMDESP"};

void TeksJalan(int y, uint8_t kecepatan) {

  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(SystemFont5x7);
  int fullScroll = Disp.textWidth(teks[0]) + width;
  if((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, teks[0]);
    // Disp.drawText(96,0,"DMDES");
  }  

}
