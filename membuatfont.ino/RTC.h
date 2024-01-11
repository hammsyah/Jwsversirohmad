

double times[sizeof(TimeName) / sizeof(char*)];

// I2C_ClearBus menghindari gagal baca RTC (nilai 00 atau 165)

int I2C_ClearBus() {

#if defined(TWCR) && defined(TWEN)
  TWCR &= ~(_BV(TWEN)); //Disable the Atmel 2-Wire interface so we can control the SDA and SCL pins directly
#endif

  pinMode(SDA, INPUT_PULLUP); // Make SDA (data) and SCL (clock) pins Inputs with pullup.
  pinMode(SCL, INPUT_PULLUP);

  delay(2500);  // Wait 2.5 secs. This is strictly only necessary on the first power
  // up of the DS3231 module to allow it to initialize properly,
  // but is also assists in reliable programming of FioV3 boards as it gives the
  // IDE a chance to start uploaded the program
  // before existing sketch confuses the IDE by sending Serial data.

  boolean SCL_LOW = (digitalRead(SCL) == LOW); // Check is SCL is Low.
  if (SCL_LOW) { //If it is held low Arduno cannot become the I2C master.
    return 1; //I2C bus error. Could not clear SCL clock line held low
  }

  boolean SDA_LOW = (digitalRead(SDA) == LOW);  // vi. Check SDA input.
  int clockCount = 20; // > 2x9 clock

  while (SDA_LOW && (clockCount > 0)) { //  vii. If SDA is Low,
    clockCount--;
    // Note: I2C bus is open collector so do NOT drive SCL or SDA high.
    pinMode(SCL, INPUT); // release SCL pullup so that when made output it will be LOW
    pinMode(SCL, OUTPUT); // then clock SCL Low
    delayMicroseconds(10); //  for >5uS
    pinMode(SCL, INPUT); // release SCL LOW
    pinMode(SCL, INPUT_PULLUP); // turn on pullup resistors again
    // do not force high as slave may be holding it low for clock stretching.
    delayMicroseconds(10); //  for >5uS
    // The >5uS is so that even the slowest I2C devices are handled.
    SCL_LOW = (digitalRead(SCL) == LOW); // Check if SCL is Low.
    int counter = 20;
    while (SCL_LOW && (counter > 0)) {  //  loop waiting for SCL to become High only wait 2sec.
      counter--;
      delay(100);
      SCL_LOW = (digitalRead(SCL) == LOW);
    }
    if (SCL_LOW) { // still low after 2 sec error
      return 2; // I2C bus error. Could not clear. SCL clock line held low by slave clock stretch for >2sec
    }
    SDA_LOW = (digitalRead(SDA) == LOW); //   and check SDA input again and loop
  }
  if (SDA_LOW) { // still low
    return 3; // I2C bus error. Could not clear. SDA data line held low
  }

  // else pull SDA line low for Start or Repeated Start
  pinMode(SDA, INPUT); // remove pullup.
  pinMode(SDA, OUTPUT);  // and then make it LOW i.e. send an I2C Start or Repeated start control.
  // When there is only one I2C master a Start or Repeat Start has the same function as a Stop and clears the bus.
  /// A Repeat Start is a Start occurring after a Start with no intervening Stop.
  delayMicroseconds(10); // wait >5uS
  pinMode(SDA, INPUT); // remove output low
  pinMode(SDA, INPUT_PULLUP); // and make SDA high i.e. send I2C STOP control.
  delayMicroseconds(10); // x. wait >5uS
  pinMode(SDA, INPUT); // and reset pins as tri-state inputs which is the default state on reset
  pinMode(SCL, INPUT);
  return 0; // all ok

}

RtcDateTime now;
char weekDay[][7] = {"AHAD", "SENIN", "SELASA", "RABU", "KAMIS", "JUM'AT", "SABTU", "AHAD"}; // array hari, dihitung mulai dari senin, hari senin angka nya =0,
char monthYear[][10] = { "DESEMBER", "JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULI", "AGUSTUS", "SEPTEMBER", "OKTOBER", "NOVEMBER", "DESEMBER" };
char monthYear2[][5] = { "DES", "JAN", "FEB", "MAR", "APR", "MEI", "JUN", "JUL", "AGT", "SEP", "OKT", "NOV", "DES" };

//////////hijriyah
#define epochHijriah          1948439.5f //math.harvard.edu
#define tambahKurangHijriah   0


uint8_t rJam;
uint8_t rMen;
uint8_t rDet;
uint8_t rTgl;
uint8_t rHar;
uint8_t rBul;
uint16_t rTah;
int celsius;


struct TanggalDanWaktu
{
  uint8_t detik;
  uint8_t menit;
  uint8_t jam;
  uint8_t hari;
  uint8_t tanggal;
  uint8_t bulan;
  uint8_t tahun;
};
struct Tanggal
{
  uint8_t tanggal;
  uint8_t bulan;
  uint16_t tahun;
};
struct TanggalJawa
{
  uint8_t pasaran;
  uint8_t wuku;
  uint8_t tanggal;
  uint8_t bulan;
  uint16_t tahun;
};
struct JamDanMenit
{
  uint8_t jam;
  uint8_t menit;
};

uint8_t jumlahHariPerBulan[] = { 31, 28, 31, 30, 31, 30, 31, 31,
                                 30, 31, 30, 31
                               };
char namaBulanMasehi[][10] = {"Januari", "Februari", "Maret",
                              "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober",
                              "November", "Desember"
                             };
char namaHariMasehi[][7] = {"Minggu", "Senin", "Selasa", "Rabu",
                            "Kamis", "Jum'at", "Sabtu",
                           };
char namaBulanHijriah[][14] = {"Muharram", "Safar", "Rabiul awal",
                               "RabiulAkhir", "JumadilAwal", "JumadilAkir", "Rajab",
                               "Sya'ban", "Ramadhan", "Syawal",
                               "Dzulkaidah", "Dzulhijjah"
                              };
char namaBulanJawa[][12] = { "Sura", "Sapar", "Mulud", "Bakda Mulud", "Jumadilawal", "Jumadilakir", "Rejeb", "Ruwah", "Pasa", "Sawal", "Sela", "Besar"};
char namaWukuJawa[][13] = {"Shinta", "Landhep", "Wukit",
                           "Kurantil", "Tala", "Gumbreg", "Warigalit", "Warigagung",
                           "Julungwangi",
                           "Sungsang", "Galungan", "Kuningan",
                           "Langkir", "Mandasia", "Julungpujut", "Pahang", "Kuruwelut",
                           "Mrakeh", "Tambir",
                           "Madangkungan", "Maktal", "Wuye",
                           "Manahil", "Prangbakat", "Bala", "Wungu", "Wayang", "Kulawu",
                           "Dhukut", "Watugunung"
                          };
char namaHariPasaran[][7] = {"LEGI", "PAHING", "PON", "WAGE", "KLIWON"};

TanggalDanWaktu tanggalMasehi;
Tanggal tanggalHijriah;
TanggalJawa tanggalJawa;
JamDanMenit waktuMagrib;

/////end hijir/////////////////////////////////////////////////////




double get_julian_date(Tanggal tanggal)
{
  if (tanggal.bulan <= 2)
  {
    tanggal.tahun -= 1;
    tanggal.bulan += 12;
  }

  double a = floor(tanggal.tahun / 100.0);
  double b = 2 - a + floor(a / 4.0);

  if (tanggal.tahun < 1583)
    b = 0;
  if (tanggal.tahun == 1582) {
    if (tanggal.bulan > 10)
      b = -10;
    if (tanggal.bulan == 10) {
      b = 0;
      if (tanggal.tanggal > 4)
        b = -10;
    }
  }

  return floor(365.25 * (tanggal.tahun + 4716)) + floor(30.6001 *
         (tanggal.bulan + 1)) + tanggal.tanggal + b - 1524.5;
}

double konversiTanggalHijriahKeJulianDate(uint16_t tahun, uint8_t
    bulan, uint8_t tanggal)
{
  return (epochHijriah + tanggal + ceil(29.5 * (bulan - 1)) +
          (354L * (tahun - 1)) + floor((3 + (11 * tahun)) / 30)) - 1;
}

void masehiKeHijriah(TanggalDanWaktu masehi, JamDanMenit
                     waktuSholatMagrib, int8_t koreksiHijriah, Tanggal & hijriah,
                     TanggalJawa & jawa)
{
  uint16_t sisaHari;
  double julianDate = get_julian_date({masehi.tanggal,
                                       masehi.bulan, masehi.tahun + 2000
                                      });

  uint16_t menitMagrib = waktuSholatMagrib.jam * 60  +
                         waktuSholatMagrib.menit;
  uint16_t menitSekarang = masehi.jam * 60 + masehi.menit;

  if (menitSekarang >= menitMagrib)
  {
    julianDate++;//Pergantian hari hijrah pada magrib
  }

  julianDate = floor(julianDate) + 0.5;

  Tanggal tanggalHijriah;

  hijriah.tahun = floor(((30 * (julianDate - epochHijriah)) +
                         10646) / 10631);
  hijriah.bulan = min(12.0, ceil((julianDate - (29 +
                                  konversiTanggalHijriahKeJulianDate(hijriah.tahun, 1, 1))) / 29.5)
                      + 1);
  hijriah.tanggal = (julianDate -
                     konversiTanggalHijriahKeJulianDate(hijriah.tahun, hijriah.bulan,
                         1)) + 1;

  long julianLong = (long)julianDate;
  jawa.pasaran = ((julianLong + 1) % 5); //0 = legi
  jawa.wuku = (((julianLong + 65) % 210) / 7); //0 = Shinta
  jawa.tanggal = hijriah.tanggal;
  jawa.bulan = hijriah.bulan;
  jawa.tahun = hijriah.tahun + 512;

}
uint8_t hariDariTanggal(TanggalDanWaktu tanggalDanWaktu) {
  uint16_t jumlahHari = tanggalDanWaktu.tanggal;
  for (uint8_t i = 1; i < tanggalDanWaktu.bulan; ++i)
    jumlahHari += jumlahHariPerBulan[i - 1];
  if (tanggalDanWaktu.bulan > 2 && tanggalDanWaktu.tahun % 4 == 0)
    ++jumlahHari;
  jumlahHari += (365 * tanggalDanWaktu.tahun) +
                ((tanggalDanWaktu.tahun + 3) / 4) - 1;

  return ((jumlahHari + 6) % 7) + 1; // 1 Januari 2000 hari sabtu= 7

}
void printKonversi(TanggalDanWaktu tanggalMasehi, Tanggal
                   tanggalHijriah, TanggalJawa tanggalJawa)
{



  ///end hijir voidku///////////////////////////////////////////////////
}

//////hijiriyah voidku/////////////////////////////////////////////////
void islam() {
  //
  waktuMagrib = {18, 12};
  RtcDateTime now = Rtc.GetDateTime();

  tanggalMasehi.tanggal = now.Day();
  tanggalMasehi.bulan = now.Month();
  tanggalMasehi.tahun = now.Year() - 2000;

  uint32_t jumlahHari;
  double jumlahHariMatahari;

  tanggalMasehi.hari = hariDariTanggal(tanggalMasehi);
  masehiKeHijriah(tanggalMasehi, waktuMagrib, tambahKurangHijriah,
                  tanggalHijriah, tanggalJawa);
  printKonversi(tanggalMasehi, tanggalHijriah, tanggalJawa);

  //while (1);
}

void mulaiRTC() {

  int rtn = I2C_ClearBus(); // clear the I2C bus first before calling Wire.begin()
  if (rtn != 0) {
    Serial.println(F("I2C bus error. Could not clear"));
    if (rtn == 1) {
      Serial.println(F("SCL clock line held low"));
    } else if (rtn == 2) {
      Serial.println(F("SCL clock line held low by slave clock stretch"));
    } else if (rtn == 3) {
      Serial.println(F("SDA data line held low"));
    }
  } else { // bus clear, re-enable Wire, now can start Wire Arduino master
    Wire.begin();
  }
  
  Rtc.Begin();

  if (!Rtc.GetIsRunning()) {
    
    Rtc.SetIsRunning(true);
    
  }
  
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
  
  Serial.println("Setup RTC selesai");
  
}

// UPDATE WAKTU

void BacaRTC() {
  RtcDateTime now = Rtc.GetDateTime();
  RtcTemperature temp = Rtc.GetTemperature();
  celsius = temp.AsFloatDegC();
  rJam = now.Hour();
  rMen = now.Minute();
  rDet = now.Second();
  rTgl = now.Day();
  rHar = now.DayOfWeek();
  rBul = now.Month();
  rTah = now.Year();
}

//-----------------------------------
// UPDATE WAKTU

void UpdateWaktu() {

  static long pM;
  static uint16_t d;
  

  if (millis() - pM > 1000) {
    d++;
    if (d < 2) {
      BacaRTC();
  //    JadwalSholat();
  //    TanggalHijriah();
    } else if (d < 60) { // Update setiap 60 detik
      rDet++;
      if (rDet > 59) {
        rMen++;
        rDet=0;
        if (rMen > 59) {
          rJam++;
          rMen = 0;
        }
      }
    } else {
      d = 0; 
    }
    pM = millis();    
  }
  
}
