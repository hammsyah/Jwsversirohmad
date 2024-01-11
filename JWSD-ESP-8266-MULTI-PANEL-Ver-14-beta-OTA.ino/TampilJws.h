uint8_t tampilanutama;
uint8_t tampilanjam;
int langkah = 1; // pertama tampil
int berhenti = 0;
int statusku;

// FORMAT TEKS
//
void textCenter(int y, String Msg)
{

  int center = int((Disp.width() - Disp.textWidth(Msg)) / 2);
  Disp.drawText(center, y, Msg);
}

//////////////////////////////////////////////////////display empat panel/////////
void displayku()
{
  //

  ///////////////////////
  ////////////////////JAM////
  static uint8_t d;
  // static uint32_t pM;
  static uint32_t pMJam;
  static uint32_t pMKedip;
  uint32_t cM = millis();
  static boolean kedip;

  //  // RtcDateTime now = Rtc.GetDateTime();

  d = 0;
  char jam[3];
  char menit[3];
  char detik[3];
  char harine[18];
  char tanggale[18];
  char tahune[18];

  if (berhenti == 0 && langkah == 7)
  {

    if (cM - pMJam >= 1000)
    {
      pMJam = cM;
      d++;

      Disp.drawRect(13, 0, 18, 10, 0, 0); // tutup lampu murup
      Disp.drawRect(13, 9, 18, 11, 0, 0);
      Disp.drawRect(90, 0, 92, 5, 0, 0);

      // JAM
      //  sprintf(jam, "%02d", rJam);
      sprintf(jam, "%02d", rJam);

      Disp.setFont(BigNumber);
      Disp.drawText(0, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(BigNumber);
      Disp.drawText(19, 0, menit);

      // DETIK
      sprintf(detik, "%02d", rDet);
      Disp.setFont(BigNumber);
      Disp.drawText(38, 0, detik);

      // tanggal
      sprintf(harine, "%s", weekDay[rHar]);
      Disp.setFont(Font4x6);
      // Disp.drawText(98, 0, harine);

      sprintf(tanggale, " %02d-%s ", rTgl, monthYear2[rBul]);
      Disp.setFont(Font4x6);
      Disp.drawText(52, 0, tanggale);

      sprintf(tahune, "%02d  ", rTah);
      Disp.setFont(Font4x6);
      Disp.drawText(60, 8, tahune);

      // KEDIP DETIK

      if (millis() - pMKedip >= 500)
      {
        pMKedip = millis();
        kedip = !kedip;
      }

      if (kedip)
      {

        Disp.drawRect(15, 3, 16, 5, 1, 1); // koordinat titik dua
        Disp.drawRect(15, 9, 16, 11, 1, 1);

        Disp.drawRect(34, 3, 35, 5, 1, 1); // koordinat titik dua
        Disp.drawRect(34, 9, 35, 11, 1, 1);
      }
      else
      {
        Disp.drawRect(13, 0, 18, 10, 0, 0); // koordinat titik dua
        Disp.drawRect(13, 9, 18, 11, 0, 0);

        /////////////////////
        Disp.drawRect(90, 0, 92, 5, 0, 0); // tutup lampu murup
        ///////////////////////////

        Disp.drawRect(32, 0, 37, 10, 0, 0); // koordinat titik dua
        Disp.drawRect(32, 9, 37, 11, 0, 0);
      }

      if (rDet == 30)
      {
        // langkah = 1;
        // berhenti = 0;
        // Disp.clear();
      }
    }

    /////////////////

    int tahun = rTah;
    int bulan = rBul;
    int tanggal = rTgl;
    static uint8_t i;
    static uint32_t pMz;
    uint32_t cMz = millis();

    char sholat[7];
    char jamx[5];
    char TimeNamev2[][9] = {" SUBUH  ", "TERBIT  ", "DZUHUR  ", " ASHAR  ", " TRBNM  ", "MAGHRIB ", " ISYA'  "};
    int hours, minutes;
    int x;
    set_calc_method(Karachi);
    set_asr_method(Shafii);
    set_high_lats_adjust_method(AngleBased);
    set_fajr_angle(20);
    set_isha_angle(18);

    ///////////sholat

    if (cMz - pMz >= 10)
    { // lamanya

      pMz = cMz;
      // Disp.clear();

      // if (i == 1) {
      //   i = 2; // Abaikan Terbit
      //  }
      if (i == 4)
      {
        i = 5; // Abaikan Terbenam
      }

      get_float_time_parts(times[i], hours, minutes);

      minutes = minutes + config.ihti;

      if (minutes >= 60)
      {
        minutes = minutes - 60;
        hours++;
      }
      String sholat = TimeNamev2[i];

      ////////////////dinamis////////////////////////////
      static uint8_t y;
      static uint8_t dy;
      static uint32_t pMy;
      uint32_t cMy = millis();

      static uint32_t pMKedipy;
      static boolean kedipy;

      if (cMy - pMy > 50)
      { // kecepatannya jatuh

        if (dy == 0 and y < 31)
        {
          pMy = cMy;

          y++;
        }

        if (dy == 1 and y >= 0)
        {
          pMy = cMy;
          y--;
        }
      }

      if (cMy - pMy > 5000 and y == 31)
      {
        dy = 1;
        i++;
      }
      if (dy == 1)
      {
        dy = 0;
        y = 0;
        // Disp.clear();
      }

      ////////////////////

      sprintf(jamx, "%02d:%02d", hours, minutes);
      Disp.setFont(Font4x6);
      Disp.drawText(92, y - 32, sholat);
      Disp.setFont(DejaVuSansBold9);
      Disp.drawText(95, y - 23, jamx);

      if (i >= 7)
      {
        get_float_time_parts(times[0], hours, minutes);
        minutes = minutes + config.ihti;
        if (minutes < 11)
        {
          minutes = 60 - minutes;
          hours--;
        }
        else
        {
          minutes = minutes - 10;
        }
        // Disp.clear();

        sprintf(jamx, "%02d:%02d", hours, minutes);
        Disp.setFont(Font4x6);

        Disp.drawText(92, y - 32, " IMSAK  ");
        Disp.setFont(DejaVuSansBold9);
        Disp.drawText(95, y - 23, jamx);
      }
      if (i > 7)
      {
        i = 0;
        berhenti = 0;
        if (rMen == 0 || rMen == 10 || rMen == 20 || rMen == 30 || rMen == 40 || rMen == 50)
        {
          Disp.clear();
          langkah = 1;
        }
        else if (rMen == 2 || rMen == 12 || rMen == 22 || rMen == 32 || rMen == 42 || rMen == 52)
        {
          Disp.clear();
          langkah = 2;
        }
        else if (rMen == 4 || rMen == 14 || rMen == 24 || rMen == 34 || rMen == 44 || rMen == 54)
        {
          Disp.clear();
          langkah = 3;
        }
        else if (rMen == 6 || rMen == 16 || rMen == 26 || rMen == 36 || rMen == 46 || rMen == 56)
        {
          Disp.clear();
          langkah = 5;
        }
        else if (rMen == 8 || rMen == 18 || rMen == 28 || rMen == 38 || rMen == 48 || rMen == 58)
        {
          Disp.clear();
          langkah = 5;
        }
        else
        {
          langkah = 7;
        }
      }
    }
  }
  /////nama masjid
  int tahun = rTah;
  int bulan = rBul;
  int tanggal = rTgl;

  int width = Disp.width();
  if (langkah == 1 && berhenti == 0)
  {

    static char *nama[] = {config.nama};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
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
        // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 7; // MBALIK TAMPILAN JAM GEDHE
        // return;
      }

      Disp.drawText(width - x, 9, nama[0]);
      // Disp.drawFilledRect(0, 15, 0, 0, 0) ;
      // jam nya kecil
      sprintf(jam, "%02d:", rJam);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(0, 0, jam);

      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(17, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      sprintf(harine, "%s", weekDay[rHar]);
      Disp.setFont(Font4x6);
      Disp.drawText(42, -1, harine);

      sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      Disp.setFont(Font4x6);
      Disp.drawText(81, -1, tanggale);

      sprintf(tahune, "-%02d", rTah);
      Disp.setFont(Font4x6);
      Disp.drawText(105, -1, tahune);
    }
  }
  /////info1
  // int width = Disp.width();
  if (langkah == 2 && berhenti == 0)
  {

    static char *info1[] = {config.info1};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info1[0]) + width;
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
        // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 7; // MBALIK TAMPILAN JAM GEDHE
        // return;
      }

      Disp.drawText(width - x, 9, info1[0]);
      // Disp.drawFilledRect(0, 15, 0, 0, 0) ;

      // jam nya kecil

      sprintf(jam, "%02d:", rJam);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(0, 0, jam);

      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(17, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      sprintf(harine, "%s", weekDay[rHar]);
      Disp.setFont(Font4x6);
      Disp.drawText(42, -1, harine);

      sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      Disp.setFont(Font4x6);
      Disp.drawText(81, -1, tanggale);

      sprintf(tahune, "-%02d", rTah);
      Disp.setFont(Font4x6);
      Disp.drawText(105, -1, tahune);
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 3 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pMw;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width;
    if ((millis() - pMw) > Speed)
    {
      pMw = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
        // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 7; // MBALIK TAMPILAN JAM GEDHE
        // return;
      }

      Disp.drawText(width - xs, 9, info2[0]);
      // Disp.drawFilledRect(0, 15, 0, 0, 0) ;

      // jam nya kecil

      sprintf(jam, "%02d:", rJam);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(0, 0, jam);

      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(17, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      sprintf(harine, "%s", weekDay[rHar]);
      Disp.setFont(Font4x6);
      Disp.drawText(42, -1, harine);

      sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      Disp.setFont(Font4x6);
      Disp.drawText(81, -1, tanggale);

      sprintf(tahune, "-%02d", rTah);
      Disp.setFont(Font4x6);
      Disp.drawText(105, -1, tahune);
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 4 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pMw;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width;
    if ((millis() - pMw) > Speed)
    {
      pMw = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
        // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 7; // MBALIK TAMPILAN JAM GEDHE
        // return;
      }

      Disp.drawText(width - xs, 9, info2[0]);
      // Disp.drawFilledRect(0, 15, 0, 0, 0) ;

      // jam nya kecil

      sprintf(jam, "%02d:", rJam);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(0, 0, jam);

      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(17, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      sprintf(harine, "%s", weekDay[rHar]);
      Disp.setFont(Font4x6);
      Disp.drawText(42, -1, harine);

      sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      Disp.setFont(Font4x6);
      Disp.drawText(81, -1, tanggale);

      sprintf(tahune, "-%02d", rTah);
      Disp.setFont(Font4x6);
      Disp.drawText(105, -1, tahune);
    }
  }

  /////////tanggalku///////////
  static uint8_t dtgl;
  static char hari[8];
  static char tanggalan[18];
  static char tanggaladz[18];
  static char tanggalanhij[18];
  static uint32_t pMtgl;
  static uint32_t pMtglhij;
  static uint32_t pMadz;
  uint32_t cMtgl = millis();
  ///////////////////////////////////static uint32_t datane;

  /////running tanggal masehi
  static uint32_t xtgl;
  static uint32_t Speedtgl = 50;
  // int width = Disp.width();
  if (langkah == 5 && berhenti == 0)
  {

    Disp.setFont(SystemFont5x7);
    sprintf(tanggalan, "%s %s %02d %s %02d", weekDay[rHar], namaHariPasaran[tanggalJawa.pasaran], rTgl, monthYear[rBul], rTah); /// bulannya tulisn
    int fullScrolltgl = Disp.textWidth(tanggalan) + width;
    if ((millis() - pMtgl) > Speedtgl)
    {
      pMtgl = millis();
      if (xtgl < fullScrolltgl)
      {
        ++xtgl;
      }
      else
      {
        langkah = 6; // MBALIK TAMPILAN JAM GEDHE
        xtgl = 0;
        // Disp.clear();
      }

      Disp.drawText(width - xtgl, 9, tanggalan);
      // Disp.drawFilledRect(0, 15, 0, 0, 0) ;

      // jam nya kecil

      sprintf(jam, "%02d:", rJam);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(0, 0, jam);

      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(17, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      sprintf(harine, "%s", weekDay[rHar]);
      Disp.setFont(Font4x6);
      Disp.drawText(42, -1, harine);

      sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      Disp.setFont(Font4x6);
      Disp.drawText(81, -1, tanggale);

      sprintf(tahune, "-%02d", rTah);
      Disp.setFont(Font4x6);
      Disp.drawText(105, -1, tahune);
    }
  }
  /////running tanggal hijiriyah

  uint32_t cMtglhij = millis();
  static uint32_t xtglhij;
  static uint32_t Speedtglhij = 50;
  // int width = Disp.width();
  if (langkah == 6 && berhenti == 0)
  {
    islam();
    Disp.setFont(SystemFont5x7);
    sprintf(tanggalanhij, "%02d %s %02dH", tanggalHijriah.tanggal, namaBulanHijriah[tanggalHijriah.bulan - 1], tanggalHijriah.tahun);
    int fullScrolltglhij = Disp.textWidth(tanggalanhij) + width;
    if ((millis() - pMtglhij) > Speedtgl)
    {
      pMtglhij = millis();
      if (xtglhij < fullScrolltglhij)
      {
        ++xtglhij;
      }
      else
      {
        Disp.clear();
        Disp.drawFilledRect(128, 15, 0, 0, 0);
        langkah = 7; // MBALIK TAMPILAN JAM GEDHE
        xtglhij = 0;
        Disp.clear();
      }
      Disp.drawFilledRect(0, 15, 0, 0, 0);
      Disp.drawText(width - xtglhij, 9, tanggalanhij);
      Disp.drawFilledRect(0, 15, 0, 0, 0);

      // jam nya kecil

      sprintf(jam, "%02d:", rJam);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(0, 0, jam);

      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(17, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      sprintf(harine, "%s", weekDay[rHar]);
      Disp.setFont(Font4x6);
      Disp.drawText(42, -1, harine);

      sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      Disp.setFont(Font4x6);
      Disp.drawText(81, -1, tanggale);

      sprintf(tahune, "-%02d", rTah);
      Disp.setFont(Font4x6);
      Disp.drawText(105, -1, tahune);
    }
  }
}

//////////////////////////////////////////////////////display tiga panel/////////
void displaykutiga()
{

  ///////////////////////
  ////////////////////JAM////
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
  char tahune[18];

  if (berhenti == 0)
  {

    if (cM - pMJam >= 1000)
    {
      pMJam = cM;
      d++;
      // Disp.drawRect(84, 0, 89, 10, 0, 0); //hapus jejak
      // Disp.drawRect(45, 0, 50, 10, 0, 0);
      // Disp.drawRect(45, 9, 50, 11, 0, 0);

      // JAM
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(32, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 0, menit);

      // DETIK
      sprintf(detik, "%02d", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 9, detik);

      // tanggal
      sprintf(harine, "%s", weekDay[rHar]);
      Disp.setFont(Font4x6);
      // Disp.drawText(98, 0, harine);

      sprintf(tanggale, "  %02d-%s   ", rTgl, monthYear2[rBul]);
      Disp.setFont(Font4x6);
      // Disp.drawText(51, 0, tanggale);

      sprintf(tahune, "%02d    ", rTah);
      Disp.setFont(Font4x6);
      // Disp.drawText(65, 8, tahune);

      // KEDIP DETIK

      if (millis() - pMKedip >= 500)
      {
        pMKedip = millis();
        kedip = !kedip;
      }

      if (kedip)
      {

        // Disp.drawRect(45, 0, 50, 10, 0, 0); //koordinat titik dua
        //  Disp.drawRect(45, 9, 50, 11, 0, 0);

        //  Disp.drawRect(65, 0, 69, 10, 0, 0); //koordinat titik dua
        // Disp.drawRect(65, 9, 69, 11, 0, 0);

        // Disp.drawRect(84, 0, 89, 10, 0, 0); //hapus jejak
      }
      else
      {

        Disp.drawRect(47, 3, 48, 5, 1, 1); // koordinat titik dua
        Disp.drawRect(47, 9, 48, 11, 1, 1);

        // Disp.drawRect(66, 3, 67, 5, 1, 1); //koordinat titik dua
        // Disp.drawRect(66, 9, 67, 11, 1, 1);
      }

      //   if (rDet == 30) {
      //  langkah = 1;
      berhenti = 0;
      // Disp.clear();
      //  }
    }
  }

  /////////////////

  int tahun = rTah;
  int bulan = rBul;
  int tanggal = rTgl;
  static uint8_t i;
  static uint32_t pMz;
  uint32_t cMz = millis();

  char sholat[7];
  char jamx[5];
  char TimeNamev2[][9] = {"SUBUH ", "TERBIT", "DZUHUR ", "ASHAR  ", "TRBNM ", "MAGHRIB", " ISYA'  "};
  int hours, minutes;
  int x;
  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);

  ///////////sholat

  if (cMz - pMz >= 50)
  {

    pMz = cMz;
    // Disp.clear();

    // if (i == 1) {
    //   i = 2; // Abaikan Terbit
    //  }
    if (i == 4)
    {
      i = 5; // Abaikan Terbenam
    }

    get_float_time_parts(times[i], hours, minutes);

    minutes = minutes + config.ihti;

    if (minutes >= 60)
    {
      minutes = minutes - 60;
      hours++;
    }
    String sholat = TimeNamev2[i];

    ////////////////dinamis////////////////////////////
    static uint8_t y;
    static uint8_t dy;
    static uint32_t pMy;
    uint32_t cMy = millis();

    static uint32_t pMKedipy;
    static boolean kedipy;

    if (cMy - pMy > 3)
    { // kecepatannya jatuh

      if (dy == 0 and y < 31)
      {
        pMy = cMy;

        y++;
      }

      if (dy == 1 and y >= 0)
      {
        pMy = cMy;
        y--;
      }
    }

    if (cMy - pMy > 5000 and y == 31)
    {
      dy = 1;
      i++;
    }
    if (dy == 1)
    {
      dy = 0;
      y = 0;
      // Disp.clear();
    }

    ////////////////////
    if (berhenti == 0)
    {

      sprintf(jamx, "%02d:%02d", hours, minutes);
      Disp.setFont(Font4x6);
      Disp.drawText(64, y - 31, sholat);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(99, y - 31, jamx);

      if (i >= 7)
      {
        get_float_time_parts(times[0], hours, minutes);
        minutes = minutes + config.ihti;
        if (minutes < 11)
        {
          minutes = 60 - minutes;
          hours--;
        }
        else
        {
          minutes = minutes - 10;
        }
        // Disp.clear();

        sprintf(jamx, "%02d:%02d", hours, minutes);
        Disp.setFont(Font4x6);

        Disp.drawText(64, y - 31, "IMSAK  ");
        Disp.setFont(SystemFont5x7);
        Disp.drawText(99, y - 31, jamx);
      }
      if (i >= 8)
      {
        i = 0;
        // langkah = 1;
      }
    }
  }

  /////nama masjid
  // int tahun = rTah;
  // int bulan = rBul;
  // int tanggal = rTgl;

  int width = Disp.width();
  if (langkah == 1 && berhenti == 0)
  {

    static char *nama[] = {config.nama};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(nama[0]) + width - 32;
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
        // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 2;
        // return;
      }

      Disp.drawText(width - x, 9, nama[0]);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      // JAM BESAR
      Disp.drawRect(47, 3, 48, 5, 1, 1); // koordinat titik dua
      Disp.drawRect(47, 9, 48, 11, 1, 1);

      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(32, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 0, menit);

      // DETIK
      sprintf(detik, "%02d", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 9, detik);
      ///////

      // jam nya kecil
      //  sprintf(jam, "%02d:", rJam);
      //  Disp.setFont(SystemFont5x7);
      //  Disp.drawText(32, 0, jam);

      //  sprintf(menit, "%02d", rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(50, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      //  sprintf(harine, "%s,", weekDay[rHar]);
      //  Disp.setFont(Font4x6);
      //  Disp.drawText(42, -1, harine);

      // sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      // Disp.setFont(Font4x6);
      // Disp.drawText(81, -1, tanggale);

      // sprintf(tahune, "-%02d", rTah);
      // Disp.setFont(Font4x6);
      // Disp.drawText(105, -1, tahune);
    }
  }
  /////info1
  // int width = Disp.width();
  if (langkah == 2 && berhenti == 0)
  {

    static char *info1[] = {config.info1};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info1[0]) + width - 32;
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
        // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 3;
        // return;
      }

      Disp.drawText(width - x, 9, info1[0]);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      // JAM BESAR
      Disp.drawRect(47, 3, 48, 5, 1, 1); // koordinat titik dua
      Disp.drawRect(47, 9, 48, 11, 1, 1);
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(32, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 0, menit);

      // DETIK
      sprintf(detik, "%02d", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 9, detik);
      ///////

      // jam nya kecil
      //  sprintf(jam, "%02d:", rJam);
      // Disp.setFont(SystemFont5x7);
      //  Disp.drawText(32, 0, jam);

      // sprintf(menit, "%02d", rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(50, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      //  sprintf(harine, "%s,", weekDay[rHar]);
      //  Disp.setFont(Font4x6);
      //  Disp.drawText(42, -1, harine);

      // sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      // Disp.setFont(Font4x6);
      // Disp.drawText(81, -1, tanggale);

      // sprintf(tahune, "-%02d", rTah);
      // Disp.setFont(Font4x6);
      // Disp.drawText(105, -1, tahune);
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 3 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pMw;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width - 32;
    if ((millis() - pMw) > Speed)
    {
      pMw = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
        // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 4;
        // return;
      }

      Disp.drawText(width - xs, 9, info2[0]);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      // JAM BESAR
      Disp.drawRect(47, 3, 48, 5, 1, 1); // koordinat titik dua
      Disp.drawRect(47, 9, 48, 11, 1, 1);
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(32, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 0, menit);

      // DETIK
      sprintf(detik, "%02d", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 9, detik);
      ///////
      // jam nya kecil
      //   sprintf(jam, "%02d:", rJam);
      //  Disp.setFont(SystemFont5x7);
      //  Disp.drawText(32, 0, jam);

      // sprintf(menit, "%02d", rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(50, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      //  sprintf(harine, "%s,", weekDay[rHar]);
      // Disp.setFont(Font4x6);
      //  Disp.drawText(42, -1, harine);

      // sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      // Disp.setFont(Font4x6);
      // Disp.drawText(81, -1, tanggale);

      // sprintf(tahune, "-%02d", rTah);
      // Disp.setFont(Font4x6);
      // Disp.drawText(105, -1, tahune);
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 4 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pMw;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width - 32;
    if ((millis() - pMw) > Speed)
    {
      pMw = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
        //  Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 5;
        // return;
      }

      Disp.drawText(width - xs, 9, info2[0]);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      // JAM BESAR
      Disp.drawRect(47, 3, 48, 5, 1, 1); // koordinat titik dua
      Disp.drawRect(47, 9, 48, 11, 1, 1);
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(32, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 0, menit);

      // DETIK
      sprintf(detik, "%02d", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 9, detik);
      ///////
      // jam nya kecil
      //   sprintf(jam, "%02d:", rJam);
      //  Disp.setFont(SystemFont5x7);
      // Disp.drawText(32, 0, jam);

      // sprintf(menit, "%02d", rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(50, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      //  sprintf(harine, "%s,", weekDay[rHar]);
      //  Disp.setFont(Font4x6);
      //  Disp.drawText(42, -1, harine);

      // sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      // Disp.setFont(Font4x6);
      // Disp.drawText(81, -1, tanggale);

      // sprintf(tahune, "-%02d", rTah);
      // Disp.setFont(Font4x6);
      // Disp.drawText(105, -1, tahune);
    }
  }

  /////////tanggalku///////////
  static uint8_t dtgl;
  static char hari[8];
  static char tanggalan[18];
  static char tanggaladz[18];
  static char tanggalanhij[18];
  static uint32_t pMtgl;
  static uint32_t pMtglhij;
  static uint32_t pMadz;
  uint32_t cMtgl = millis();
  ///////////////////////////////////static uint32_t datane;

  /////running tanggal masehi
  static uint32_t xtgl;
  static uint32_t Speedtgl = 50;
  // int width = Disp.width();
  if (langkah == 5 && berhenti == 0)
  {

    Disp.setFont(SystemFont5x7);
    sprintf(tanggalan, "%s %s %02d %s %02d", weekDay[rHar], namaHariPasaran[tanggalJawa.pasaran], rTgl, monthYear[rBul], rTah); /// bulannya tulisn
    int fullScrolltgl = Disp.textWidth(tanggalan) + width - 32;
    if ((millis() - pMtgl) > Speedtgl)
    {
      pMtgl = millis();
      if (xtgl < fullScrolltgl)
      {
        ++xtgl;
      }
      else
      {
        langkah = 6;
        xtgl = 0;
        //  Disp.clear();
      }

      Disp.drawText(width - xtgl, 9, tanggalan);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      // JAM BESAR
      Disp.drawRect(47, 3, 48, 5, 1, 1); // koordinat titik dua
      Disp.drawRect(47, 9, 48, 11, 1, 1);
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(32, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 0, menit);

      // DETIK
      sprintf(detik, "%02d", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 9, detik);
      ///////

      // jam nya kecil
      //  sprintf(jam, "%02d:", rJam);
      //  Disp.setFont(SystemFont5x7);
      //  Disp.drawText(32, 0, jam);

      // sprintf(menit, "%02d", rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(50, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      //  sprintf(harine, "%s,", weekDay[rHar]);
      //  Disp.setFont(Font4x6);
      //  Disp.drawText(42, -1, harine);

      //  sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      //  Disp.setFont(Font4x6);
      // Disp.drawText(81, -1, tanggale);

      // sprintf(tahune, "-%02d", rTah);
      // Disp.setFont(Font4x6);
      // Disp.drawText(105, -1, tahune);
    }
  }
  /////running tanggal hijiriyah

  uint32_t cMtglhij = millis();
  static uint32_t xtglhij;
  static uint32_t Speedtglhij = 50;
  // int width = Disp.width();
  if (langkah == 6 && berhenti == 0)
  {
    islam();
    Disp.setFont(SystemFont5x7);
    sprintf(tanggalanhij, "%02d %s %02dH", tanggalHijriah.tanggal, namaBulanHijriah[tanggalHijriah.bulan - 1], tanggalHijriah.tahun);
    int fullScrolltglhij = Disp.textWidth(tanggalanhij) + width - 32;
    if ((millis() - pMtglhij) > Speedtgl)
    {
      pMtglhij = millis();
      if (xtglhij < fullScrolltglhij)
      {
        ++xtglhij;
      }
      else
      {
        // Disp.clear();
        Disp.drawFilledRect(128, 15, 0, 0, 0);
        langkah = 1;
        xtglhij = 0;
        Disp.clear();
      }
      Disp.drawFilledRect(0, 15, 0, 0, 0);
      Disp.drawText(width - xtglhij, 9, tanggalanhij);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      // JAM BESAR
      Disp.drawRect(47, 3, 48, 5, 1, 1); // koordinat titik dua
      Disp.drawRect(47, 9, 48, 11, 1, 1);
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(32, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 0, menit);

      // DETIK
      sprintf(detik, "%02d", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(51, 9, detik);
      ///////
      // jam nya kecil
      //   sprintf(jam, "%02d:", rJam);
      //  Disp.setFont(SystemFont5x7);
      //  Disp.drawText(32, 0, jam);

      // sprintf(menit, "%02d", rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(50, 0, menit);

      // sprintf(detik, "%02d  ", rDet);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(34, 0, detik);

      // tanggal
      sprintf(harine, "%s,", weekDay[rHar]);
      Disp.setFont(Font4x6);
      // Disp.drawText(42, -1, harine);

      // sprintf(tanggale, "%02d-%02d", rTgl, rBul);
      // Disp.setFont(Font4x6);
      // Disp.drawText(81, -1, tanggale);

      // sprintf(tahune, "-%02d", rTah);
      // Disp.setFont(Font4x6);
      // Disp.drawText(105, -1, tahune);
    }
  }
}

//////////////////////////////////////////////////////display dua panel////////////////////////////////
void displaykudua()
{
  //

  ///////////////////////
  ////////////////////JAM////
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

  if (berhenti == 0 && langkah == 7)
  {

    if (cM - pMJam >= 1000)
    {
      pMJam = cM;
      d++;

      // JAM
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(64, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(BigNumber);
      Disp.drawText(83, 0, menit);

      // DETIK
      //   sprintf(detik,"%02d", rDet);
      //   Disp.setFont(BigNumber);
      //    Disp.drawText(37, 0, detik);
      // tanggal
      sprintf(harine, "%s", weekDay[rHar]);
      Disp.setFont(Font4x6);
      // Disp.drawText(98, 0, harine);
      sprintf(tanggale, "%02d-%s", rTgl, monthYear2[rBul]);
      Disp.setFont(Font4x6);
      // Disp.drawText(97, 8, tanggale);

      // KEDIP DETIK

      if (millis() - pMKedip >= 500)
      {
        pMKedip = millis();
        kedip = !kedip;
      }

      if (kedip)
      {
        Disp.drawRect(79, 3, 80, 5, 1, 1); // koordinat titik dua
        Disp.drawRect(79, 9, 80, 11, 1, 1);
      }
      else
      {

        Disp.drawRect(77, 0, 82, 10, 0, 0); // koordinat titik dua
        Disp.drawRect(77, 9, 80, 11, 0, 0);
      }

      if (rDet == 30)
      {
        // langkah = 1;
        // berhenti = 0;
        // Disp.clear();
      }
    }

    /////////////////

    int tahun = rTah;
    int bulan = rBul;
    int tanggal = rTgl;
    static uint8_t i;
    static uint32_t pMz;
    uint32_t cMz = millis();

    char sholat[7];
    char jamx[5];
    char TimeNamev2[][8] = {" SUBUH ", "TERBIT", "DZUHUR ", " ASHAR ", "TRBNM", "MAGHRB", " ISYA' "};
    int hours, minutes;
    int x;
    set_calc_method(Karachi);
    set_asr_method(Shafii);
    set_high_lats_adjust_method(AngleBased);
    set_fajr_angle(20);
    set_isha_angle(18);

    ///////////sholat

    if (cMz - pMz >= 50)
    {

      pMz = cMz;
      // Disp.clear();

      // if (i == 1) {
      //   i = 2; // Abaikan Terbit
      //  }
      if (i == 4)
      {
        i = 5; // Abaikan Terbenam
      }

      get_float_time_parts(times[i], hours, minutes);

      minutes = minutes + config.ihti;

      if (minutes >= 60)
      {
        minutes = minutes - 60;
        hours++;
      }
      String sholat = TimeNamev2[i];

      ////////////////dinamis////////////////////////////
      static uint8_t y;
      static uint8_t dy;
      static uint32_t pMy;
      uint32_t cMy = millis();

      static uint32_t pMKedipy;
      static boolean kedipy;

      if (cMy - pMy > 3)
      { // kecepatannya jatuh

        if (dy == 0 and y < 31)
        {
          pMy = cMy;

          y++;
        }

        if (dy == 1 and y >= 0)
        {
          pMy = cMy;
          y--;
        }
      }

      if (cMy - pMy > 5000 and y == 31)
      {
        dy = 1;
        i++;
      }
      if (dy == 1)
      {
        dy = 0;
        y = 0;
        // Disp.clear();
      }

      ////////////////////

      sprintf(jamx, "%02d:%02d", hours, minutes);
      Disp.setFont(Font4x6);
      Disp.drawText(97, y - 32, sholat);
      Disp.setFont(DejaVuSansBold9);
      Disp.drawText(100, y - 23, jamx);

      if (i >= 7)
      {
        get_float_time_parts(times[0], hours, minutes);
        minutes = minutes + config.ihti;
        if (minutes < 11)
        {
          minutes = 60 - minutes;
          hours--;
        }
        else
        {
          minutes = minutes - 10;
        }
        // Disp.clear();

        sprintf(jamx, "%02d:%02d", hours, minutes);
        Disp.setFont(Font4x6);

        Disp.drawText(97, y - 32, " IMSAK");
        Disp.setFont(DejaVuSansBold9);
        Disp.drawText(100, y - 23, jamx);
      }
      if (i > 7)
      {
        i = 0;
        berhenti = 0;
        if (rMen == 0 || rMen == 10 || rMen == 20 || rMen == 30 || rMen == 40 || rMen == 50)
        {
          Disp.clear();
          langkah = 1;
        }
        else if (rMen == 2 || rMen == 12 || rMen == 22 || rMen == 32 || rMen == 42 || rMen == 52)
        {
          Disp.clear();
          langkah = 2;
        }
        else if (rMen == 4 || rMen == 14 || rMen == 24 || rMen == 34 || rMen == 44 || rMen == 54)
        {
          Disp.clear();
          langkah = 3;
        }
        else if (rMen == 6 || rMen == 16 || rMen == 26 || rMen == 36 || rMen == 46 || rMen == 56)
        {
          Disp.clear();
          langkah = 5;
        }
        else if (rMen == 8 || rMen == 18 || rMen == 28 || rMen == 38 || rMen == 48 || rMen == 58)
        {
          Disp.clear();
          langkah = 5;
        }
        else
        {
          langkah = 7;
        }
      }
    }
  }
  /////nama masjid
  int tahun = rTah;
  int bulan = rBul;
  int tanggal = rTgl;

  int width = Disp.width();
  if (langkah == 1 && berhenti == 0)
  {

    static char *nama[] = {config.nama};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(nama[0]) + width - 64;
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
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 2;
        // return;
      }

      Disp.drawText(width - x, 9, nama[0]);
      Disp.drawFilledRect(63, 15, 0, 0, 0);

      sprintf(menit, "%02d:", rMen);
      sprintf(jam, "%02d:", rJam);
      sprintf(detik, "%02d  ", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(73, 0, jam);
      Disp.drawText(90, 0, menit);
      Disp.drawText(108, 0, detik);
    }
  }
  /////info1
  // int width = Disp.width();
  if (langkah == 2 && berhenti == 0)
  {

    static char *info1[] = {config.info1};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info1[0]) + width - 64;
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
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 3;
        // return;
      }

      Disp.drawText(width - x, 9, info1[0]);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      sprintf(menit, "%02d:", rMen);
      sprintf(jam, "%02d:", rJam);
      sprintf(detik, "%02d  ", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(73, 0, jam);
      Disp.drawText(90, 0, menit);
      Disp.drawText(108, 0, detik);
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 3 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pMw;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width - 64;
    if ((millis() - pMw) > Speed)
    {
      pMw = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
        Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 5;
        // return;
      }

      Disp.drawText(width - xs, 9, info2[0]);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      sprintf(menit, "%02d:", rMen);
      sprintf(jam, "%02d:", rJam);
      sprintf(detik, "%02d  ", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(73, 0, jam);
      Disp.drawText(90, 0, menit);
      Disp.drawText(108, 0, detik);
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 4 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pMw;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width - 64;
    if ((millis() - pMw) > Speed)
    {
      pMw = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
        Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 5;
        // return;
      }

      Disp.drawText(width - xs, 9, info2[0]);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      sprintf(menit, "%02d:", rMen);
      sprintf(jam, "%02d:", rJam);
      sprintf(detik, "%02d  ", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(73, 0, jam);
      Disp.drawText(90, 0, menit);
      Disp.drawText(108, 0, detik);
    }
  }

  /////////tanggalku///////////
  static uint8_t dtgl;
  static char hari[8];
  static char tanggalan[18];
  static char tanggaladz[18];
  static char tanggalanhij[18];
  static uint32_t pMtgl;
  static uint32_t pMtglhij;
  static uint32_t pMadz;
  uint32_t cMtgl = millis();
  ///////////////////////////////////static uint32_t datane;

  /////running tanggal masehi
  static uint32_t xtgl;
  static uint32_t Speedtgl = 50;
  // int width = Disp.width();
  if (langkah == 5 && berhenti == 0)
  {

    Disp.setFont(SystemFont5x7);
    sprintf(tanggalan, "%s %s %02d %s %02d", weekDay[rHar], namaHariPasaran[tanggalJawa.pasaran], rTgl, monthYear[rBul], rTah); /// bulannya tulisn
    int fullScrolltgl = Disp.textWidth(tanggalan) + width - 64;
    if ((millis() - pMtgl) > Speedtgl)
    {
      pMtgl = millis();
      if (xtgl < fullScrolltgl)
      {
        ++xtgl;
      }
      else
      {
        langkah = 6;
        xtgl = 0;
        Disp.clear();
      }

      Disp.drawText(width - xtgl, 9, tanggalan);
      Disp.drawFilledRect(63, 15, 0, 0, 0);
      sprintf(menit, "%02d:", rMen);
      sprintf(jam, "%02d:", rJam);
      sprintf(detik, "%02d  ", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(73, 0, jam);
      Disp.drawText(90, 0, menit);
      Disp.drawText(108, 0, detik);
    }
  }
  /////running tanggal hijiriyah

  uint32_t cMtglhij = millis();
  static uint32_t xtglhij;
  static uint32_t Speedtglhij = 50;
  // int width = Disp.width();
  if (langkah == 6 && berhenti == 0)
  {
    islam();
    Disp.setFont(SystemFont5x7);
    sprintf(tanggalanhij, "%02d %s %02dH", tanggalHijriah.tanggal, namaBulanHijriah[tanggalHijriah.bulan - 1], tanggalHijriah.tahun);
    int fullScrolltglhij = Disp.textWidth(tanggalanhij) + width - 64;
    if ((millis() - pMtglhij) > Speedtgl)
    {
      pMtglhij = millis();
      if (xtglhij < fullScrolltglhij)
      {
        ++xtglhij;
      }
      else
      {
        Disp.clear();
        Disp.drawFilledRect(128, 15, 0, 0, 0);
        langkah = 7;
        xtglhij = 0;
        Disp.clear();
      }
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xtglhij, 9, tanggalanhij);
      Disp.drawFilledRect(64, 15, 0, 0, 0);
      sprintf(menit, "%02d:", rMen);
      sprintf(jam, "%02d:", rJam);
      sprintf(detik, "%02d  ", rDet);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(73, 0, jam);
      Disp.drawText(90, 0, menit);
      Disp.drawText(108, 0, detik);
    }
  }
}

//////////////////////////////////////////////////////display satu panel////////////////////////////////
/*
void displaykusatu()
{
  //

  ///////////////////////
  ////////////////////JAM////
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





  //TAMPILKAN JAM BESAR
  if (berhenti == 0 && langkah == 7)
  {

    // JAM
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(97, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(BigNumber);
      Disp.drawText(114, 0, menit);
    
    if (cM - pMJam >= 1000)
    {
      pMJam = cM;
      d++;

      // KEDIP DETIK

      if (millis() - pMKedip >= 500)
      {
        pMKedip = millis();
        kedip = !kedip;
        
        if (kedip)
        {
          Disp.drawRect(111, 3, 112, 5, 1, 1); // koordinat titik dua
          Disp.drawRect(111, 9, 112, 11, 1, 1);
        }
        else
        {

          Disp.drawRect(111, 0, 112, 5, 0, 0); // koordinat titik dua
          Disp.drawRect(111, 9, 112, 11, 0, 0);
        }
      
        if ((rMen == 10 && rDet == 30) || (rMen == 20 && rDet == 30) || (rMen == 30 && rDet == 30) || (rMen == 40 && rDet == 30) || (rMen == 50 && rDet == 30) || (rMen == 59 && rDet == 30) || (rMen == 5 && rDet == 30) || (rMen == 15 && rDet == 30) || (rMen == 25 && rDet == 30) || (rMen == 35 && rDet == 30) || (rMen == 45 && rDet == 30) || (rMen == 55 && rDet == 30))
        {
          langkah = 9;
          berhenti = 0;
          Disp.clear();
        }
      
      }
      
    }
  }
  /////////////////

  int tahun = rTah;
  int bulan = rBul;
  int tanggal = rTgl;
  static uint8_t i;
  static uint32_t pMz;
  uint32_t cMz = millis();

  char sholat[7];
  char jamx[5];
  char TimeNamev2[][8] = {"SUBUH ", "TERBIT ", "DZUHUR ", "ASHAR  ", "TRBNM", "MAGHRB ", " ISYA' "};
  int hours, minutes;
  int x;

  ///////////sholat




  if (cMz - pMz >= 50)
  {

    pMz = cMz;
    // Disp.clear();

    // if (i == 1) {
    //   i = 2; // Abaikan Terbit
    //  }
    if (i == 4)
    {
      i = 5; // Abaikan Terbenam
    }

    get_float_time_parts(times[i], hours, minutes);

    minutes = minutes + config.ihti;

    if (minutes >= 60)
    {
      minutes = minutes - 60;
      hours++;
    }
    String sholat = TimeNamev2[i];

    ////////////////dinamis////////////////////////////
    static uint8_t x;
    static uint8_t dy;
    static uint32_t pMy;
    uint32_t cMy = millis();

    static uint32_t pMKedipy;
    static boolean kedipy;
    if (berhenti == 0 && langkah == 9)
    {
      if (cMy - pMy > 1)
      { // kecepatannya jatuh

        if (dy == 0 and x < 116)
        {
          pMy = cMy;

          x++;
        }

        if (dy == 1 and x >= 96)
        {
          pMy = cMy;
          x--;
        }
      }

      if (cMy - pMy > 50 and x == 116)
      {
        dy = 1;
        i++;
      }
      if (dy == 1)
      {
        dy = 0;
        x = 1;
        // i++;
        // Disp.clear();
      }
    }

    ////////////////////
    if (berhenti == 0 && langkah == 9)
    {

      ////
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
      ///

      sprintf(jamx, "%02d:%02d", hours, minutes);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(135 - x, 9, sholat);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(175 - x, 9, jamx);

      if (i >= 7)
      {
        get_float_time_parts(times[0], hours, minutes);
        minutes = minutes + config.ihti;
        if (minutes < 11)
        {
          minutes = 60 - minutes;
          hours--;
        }
        else
        {
          minutes = minutes - 10;
        }
        // Disp.clear();

        sprintf(jamx, "%02d:%02d", hours, minutes);
        Disp.setFont(SystemFont5x7);
        Disp.drawText(135 - x, 9, "IMSAK ");
        Disp.setFont(SystemFont5x7);
        Disp.drawText(175 - x, 9, jamx);
      }
      if (i > 7)
      {
        i = 0;
       // Disp.clear();
        langkah = 1;
      }
    }
  }
  /////nama masjid

  int width = Disp.width();
  if (langkah == 1 && berhenti == 0)
  {

    static char *nama[] = {config.nama};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(nama[0]) + width - 95;
    
    sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen); //tampilkan jam kecil
    Disp.setFont(SystemFont5x7);
    Disp.drawText(98, 0, jamkecilnya);
    
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
       // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 2;
        // return;
      }

      Disp.drawText(width - x, 9, nama[0]);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      // sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(98, 0, jamkecilnya);
      // Disp.drawText(64, 0, jam);
    }
  }
  /////info1
  // int width = Disp.width();
  if (langkah == 2 && berhenti == 0)
  {

    static char *info1[] = {config.info1};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info1[0]) + width - 95;

      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen); //tamppilkan jam kecil
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);

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
       // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 3;
        // return;
      }

      Disp.drawText(width - x, 9, info1[0]);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      //  sprintf(jamkecilnya, "%02d:%02d", rJam,rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(97, 0, jamkecilnya);
      // Disp.drawText(64, 0, jam);

      // Disp.drawText(width - xtgl, 9, tanggalan);
      // Disp.drawFilledRect(95, 15, 0, 0, 0);
      
      // sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(98, 0, jamkecilnya);
      
      // Disp.drawText(64, 0, jam);
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 3 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pM;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width - 95;
    
      // Disp.drawFilledRect(95, 15, 0, 0, 0);
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
      
    
    if ((millis() - pM) > Speed)
    {
      pM = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
       // Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 4;
        // return;
      }
      // RtcDateTime now = Rtc.GetDateTime();
      Disp.drawText(width - xs, 9, info2[0]);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      //  sprintf(jamkecilnya, "%02d:%02d", rJam,rMen);
      //  Disp.setFont(SystemFont5x7);
      // Disp.drawText(97, 0, jamkecilnya);
      // Disp.drawText(64, 0, jam);

      // Disp.drawText(width - xtgl, 9, tanggalan);
      
      // Disp.drawFilledRect(95, 15, 0, 0, 0);
      // sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(98, 0, jamkecilnya);
      
      // Disp.drawText(64, 0, jam);
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 4 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pM;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width - 95;
    
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
    
    
    if ((millis() - pM) > Speed)
    {
      pM = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
        Disp.clear();
        get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 5;
        // return;
      }
      // RtcDateTime now = Rtc.GetDateTime();
      Disp.drawText(width - xs, 9, info2[0]);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      //  sprintf(jamkecilnya, "%02d:%02d", rJam,rMen);
      //  Disp.setFont(SystemFont5x7);
      // Disp.drawText(97, 0, jamkecilnya);
      // Disp.drawText(64, 0, jam);

      // Disp.drawText(width - xtgl, 9, tanggalan);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      // sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(98, 0, jamkecilnya);
      // Disp.drawText(64, 0, jam);
    }
  }

  /////////tanggalku///////////
  static uint8_t dtgl;
  static char hari[8];
  static char tanggalan[18];
  static char tanggaladz[18];
  static char tanggalanhij[18];
  static uint32_t pMtgl;
  static uint32_t pMtglhij;
  static uint32_t pMadz;
  uint32_t cMtgl = millis();
  ///////////////////////////////////static uint32_t datane;

  /////running tanggal masehi
  static uint32_t xtgl;
  static uint32_t Speedtgl = 50;
  // int width = Disp.width();
  if (langkah == 5 && berhenti == 0)
  {

    Disp.setFont(SystemFont5x7);
    sprintf(tanggalan, "%s %s %02d %s %02d", weekDay[rHar], namaHariPasaran[tanggalJawa.pasaran], rTgl, monthYear[rBul], rTah); /// bulannya tulisn
    int fullScrolltgl = Disp.textWidth(tanggalan) + width - 95;
    
    
    // Disp.drawFilledRect(95, 15, 0, 0, 0);
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
      // Disp.drawText(64, 0, jam);
    
    
    if ((millis() - pMtgl) > Speedtgl)
    {
      pMtgl = millis();
      if (xtgl < fullScrolltgl)
      {
        ++xtgl;
      }
      else
      {
        langkah = 6;
        xtgl = 0;
        Disp.clear();
      }

      Disp.drawText(width - xtgl, 9, tanggalan);
      // Disp.drawFilledRect(95, 15, 0, 0, 0);
      // sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      // Disp.setFont(SystemFont5x7);
      // Disp.drawText(98, 0, jamkecilnya);
      // // Disp.drawText(64, 0, jam);
    }
  }
  /////running tanggal hijiriyah

  uint32_t cMtglhij = millis();
  static uint32_t xtglhij;
  static uint32_t Speedtglhij = 50;
  // int width = Disp.width();
  if (langkah == 6 && berhenti == 0)
  {
    islam();
    Disp.setFont(SystemFont5x7);
    sprintf(tanggalanhij, "%02d %s %02dH", tanggalHijriah.tanggal, namaBulanHijriah[tanggalHijriah.bulan - 1], tanggalHijriah.tahun);
    int fullScrolltglhij = Disp.textWidth(tanggalanhij) + width - 95;
    
      // Disp.drawFilledRect(95, 15, 0, 0, 0);
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
    
    if ((millis() - pMtglhij) > Speedtgl)
    {
      pMtglhij = millis();
      if (xtglhij < fullScrolltglhij)
      {
        ++xtglhij;
      }
      else
      {
        xtglhij = 0;
        Disp.clear();
        Disp.drawFilledRect(128, 15, 0, 0, 0);
        langkah = 7;
      }

      Disp.drawText(width - xtglhij, 9, tanggalanhij);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      Disp.drawText(width - xtgl, 9, tanggalan);
      
    }
  }
}

*/

void TeksJalan(int y, uint8_t kecepatan, char *teks[]) {

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
  }  


}


void displaykusatu()
{
  //

  ///////////////////////
  ////////////////////JAM////
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





  //TAMPILKAN JAM BESAR
  if (berhenti == 0 && langkah == 7)
  {

    // JAM
      sprintf(jam, "%02d", rJam);
      Disp.setFont(BigNumber);
      Disp.drawText(97, 0, jam);

      // MENIT
      sprintf(menit, "%02d", rMen);
      Disp.setFont(BigNumber);
      Disp.drawText(114, 0, menit);
    
    if (cM - pMJam >= 1000)
    {
      pMJam = cM;
      d++;

      // KEDIP DETIK

      if (millis() - pMKedip >= 500)
      {
        pMKedip = millis();
        kedip = !kedip;
        
        if (kedip)
        {
          Disp.drawRect(111, 3, 112, 5, 1, 1); // koordinat titik dua
          Disp.drawRect(111, 9, 112, 11, 1, 1);
        }
        else
        {

          Disp.drawRect(111, 0, 112, 5, 0, 0); // koordinat titik dua
          Disp.drawRect(111, 9, 112, 11, 0, 0);
        }
      
        if ((rMen == 10 && rDet == 30) || (rMen == 20 && rDet == 30) || (rMen == 30 && rDet == 30) || (rMen == 40 && rDet == 30) || (rMen == 50 && rDet == 30) || (rMen == 59 && rDet == 30) || (rMen == 5 && rDet == 30) || (rMen == 15 && rDet == 30) || (rMen == 25 && rDet == 30) || (rMen == 35 && rDet == 30) || (rMen == 45 && rDet == 30) || (rMen == 55 && rDet == 30))
        {
          langkah = 9;
          berhenti = 0;
          Disp.clear();
        }
      
      }
      
    }
  }
  /////////////////

  int tahun = rTah;
  int bulan = rBul;
  int tanggal = rTgl;
  static uint8_t i;
  static uint32_t pMz;
  uint32_t cMz = millis();

  char sholat[7];
  char jamx[5];
  char TimeNamev2[][8] = {"SUBUH ", "TERBIT ", "DZUHUR ", "ASHAR  ", "TRBNM", "MAGHRB ", " ISYA' "};
  int hours, minutes;
  int x;

  ///////////sholat

  if (berhenti == 0 && langkah == 9)
    {
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
    
        if (cMz - pMz >= 50)
        {

          pMz = cMz;
         
          if (i == 4)
          {
            i = 5; // Abaikan Terbenam
          }

          get_float_time_parts(times[i], hours, minutes);

          minutes = minutes + config.ihti;

          if (minutes >= 60)
          {
            minutes = minutes - 60;
            hours++;
          }
          String sholat = TimeNamev2[i];

          ////////////////dinamis////////////////////////////
          static uint8_t x;
          static uint8_t dy;
          static uint32_t pMy;
          uint32_t cMy = millis();

          static uint32_t pMKedipy;
          static boolean kedipy;
          
          
            if (cMy - pMy > 1)
            { // kecepatannya jatuh

              if (dy == 0 and x < 116)
              {
                pMy = cMy;

                x++;
              }

              if (dy == 1 and x >= 96)
              {
                pMy = cMy;
                x--;
              }
            }

            if (cMy - pMy > 50 and x == 116)
            {
              dy = 1;
              i++;
            }
            if (dy == 1)
            {
              dy = 0;
              x = 1;
              // i++;
              // Disp.clear();
            }
                  

            sprintf(jamx, "%02d:%02d", hours, minutes);
            Disp.setFont(SystemFont5x7);
            Disp.drawText(135 - x, 9, sholat);
            Disp.setFont(SystemFont5x7);
            Disp.drawText(175 - x, 9, jamx);

            if (i >= 7)
            {
              get_float_time_parts(times[0], hours, minutes);
              minutes = minutes + config.ihti;
              if (minutes < 11)
              {
                minutes = 60 - minutes;
                hours--;
              }
              else
              {
                minutes = minutes - 10;
              }
              // Disp.clear();

              sprintf(jamx, "%02d:%02d", hours, minutes);
              Disp.setFont(SystemFont5x7);
              Disp.drawText(135 - x, 9, "IMSAK ");
              Disp.setFont(SystemFont5x7);
              Disp.drawText(175 - x, 9, jamx);
            }
            if (i > 7)
            {
              i = 0;
            // Disp.clear();
              langkah = 1;
            }
          
        }
    
    }     ///


 
  /////nama masjid

  int width = Disp.width();
  
  if (langkah == 1 && berhenti == 0)
  {

    static char *nama[] = {config.nama};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(nama[0]) + width - 95;
    
    sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen); //tampilkan jam kecil
    Disp.setFont(SystemFont5x7);
    Disp.drawText(98, 0, jamkecilnya);
    
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
       // Disp.clear();
        // get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 2;
        // return;
      }

      Disp.drawText(width - x, 9, nama[0]);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      
    }
  }


  /////info1
  // int width = Disp.width();
  if (langkah == 2 && berhenti == 0)
  {

    static char *info1[] = {config.info1};
    static uint32_t pM;
    static uint32_t x;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info1[0]) + width - 95;

      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen); //tamppilkan jam kecil
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);

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
       // Disp.clear();
        // get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 3;
        // return;
      }

      Disp.drawText(width - x, 9, info1[0]);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
     
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 3 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pM;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width - 95;
    
      // Disp.drawFilledRect(95, 15, 0, 0, 0);
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
      
    
    if ((millis() - pM) > Speed)
    {
      pM = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
       // Disp.clear();
        // get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 4;
        // return;
      }
      // RtcDateTime now = Rtc.GetDateTime();
      Disp.drawText(width - xs, 9, info2[0]);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      
    }
  }

  /////info2
  // int width = Disp.width();
  if (langkah == 4 && berhenti == 0)
  {

    static char *info2[] = {config.info2};
    static uint32_t pM;
    static uint32_t xs;
    static uint32_t Speed = 50;
    width = Disp.width();
    Disp.setFont(SystemFont5x7);
    int fullScroll = Disp.textWidth(info2[0]) + width - 95;
    
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
    
    
    if ((millis() - pM) > Speed)
    {
      pM = millis();
      if (xs < fullScroll)
      {
        ++xs;
      }
      else
      {
        xs = 0;
       // Disp.clear();
        // get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
        langkah = 5;
        // return;
      }
      // RtcDateTime now = Rtc.GetDateTime();
      Disp.drawText(width - xs, 9, info2[0]);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      
    }
  }

  /////////tanggalku///////////
  static uint8_t dtgl;
  static char hari[8];
  static char tanggalan[18];
  static char tanggaladz[18];
  static char tanggalanhij[18];
  static uint32_t pMtgl;
  static uint32_t pMtglhij;
  static uint32_t pMadz;
  uint32_t cMtgl = millis();
  ///////////////////////////////////static uint32_t datane;

  /////running tanggal masehi
  static uint32_t xtgl;
  static uint32_t Speedtgl = 50;
  // int width = Disp.width();
  if (langkah == 5 && berhenti == 0)
  {

    Disp.setFont(SystemFont5x7);
    sprintf(tanggalan, "%s %s %02d %s %02d", weekDay[rHar], namaHariPasaran[tanggalJawa.pasaran], rTgl, monthYear[rBul], rTah); /// bulannya tulisn
    int fullScrolltgl = Disp.textWidth(tanggalan) + width - 95;
    
    
    // Disp.drawFilledRect(95, 15, 0, 0, 0);
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
      // Disp.drawText(64, 0, jam);
    
    
    if ((millis() - pMtgl) > Speedtgl)
    {
      pMtgl = millis();
      if (xtgl < fullScrolltgl)
      {
        ++xtgl;
      }
      else
      {
        langkah = 6;
        xtgl = 0;
    //    Disp.clear();
      }

      Disp.drawText(width - xtgl, 9, tanggalan);
     
    }
  }
  /////running tanggal hijiriyah

  uint32_t cMtglhij = millis();
  static uint32_t xtglhij;
  static uint32_t Speedtglhij = 50;
 
  if (langkah == 6 && berhenti == 0)
  {
   // islam();
    Disp.setFont(SystemFont5x7);
    sprintf(tanggalanhij, "%02d %s %02dH", tanggalHijriah.tanggal, namaBulanHijriah[tanggalHijriah.bulan - 1], tanggalHijriah.tahun);
    int fullScrolltglhij = Disp.textWidth(tanggalanhij) + width - 95;
    
      // Disp.drawFilledRect(95, 15, 0, 0, 0);
      sprintf(jamkecilnya, "%02d:%02d ", rJam, rMen);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(98, 0, jamkecilnya);
    
    if ((millis() - pMtglhij) > Speedtgl)
    {
      pMtglhij = millis();
      if (xtglhij < fullScrolltglhij)
      {
        ++xtglhij;
      }
      else
      {
        xtglhij = 0;
        Disp.clear();
        // Disp.drawFilledRect(128, 15, 0, 0, 0);
        langkah = 7;
      }

      Disp.drawText(width - xtglhij, 9, tanggalanhij);
      Disp.drawFilledRect(95, 15, 0, 0, 0);
      Disp.drawText(width - xtgl, 9, tanggalan);
      
    }
  }
}


/////running ADZAN 4 PANEL//////////////////////////////////////

void saatadzan()
{

  static uint8_t d;
  int bagong;
  // RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];
  char detik[3];
  static uint32_t xadz;
  int Hari = rHar;
  int Hor = rJam;
  int Min = rMen;
  int Sec = rDet;
  int adzan = config.durasiadzan * 6;

  static uint8_t dtgl;
  static char tanggaladz[18];
  static uint32_t pMtglhij;
  static uint32_t pMadz;
  int hours, minutes;
  /////////////////////ALARM ADZAN SUBUH ////////////////////////////////////////////
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(Arial_Black_16);
    sprintf(tanggaladz, "Adzan %s", TimeName[0]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 0, tanggaladz);
      Disp.drawFilledRect(33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      //  Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(19, 0, menit);
      Disp.drawText(0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmhs;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  /////////////////////////////end/////////////////////////////////////////
  /////////////////////ALARM ADZAN DZUHUR NON JUMAT////////////////////////////////////////////
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes && Hari != 5)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(Arial_Black_16);
    sprintf(tanggaladz, "Adzan %s", TimeName[2]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 0, tanggaladz);
      Disp.drawFilledRect(33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(19, 0, menit);
      Disp.drawText(0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmhd;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////

  /////////////////////ALARM ADZAN DZUHUR HARI JUMAT////////////////////////////////////////////
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes && Hari == 5)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(Arial_Black_16);
    sprintf(tanggaladz, "Adzan Jum'at");
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 0, tanggaladz);
      Disp.drawFilledRect(33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      //  Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      //  Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(19, 0, menit);
      Disp.drawText(0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmhd;
      menitiqmh = iqmh - 1;
      tampilanutama = 2;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////

  /////////////////////ALARM ADZAN ASHAR ////////////////////////////////////////////
  get_float_time_parts(times[3], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(Arial_Black_16);
    sprintf(tanggaladz, "Adzan %s", TimeName[3]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 0, tanggaladz);
      Disp.drawFilledRect(33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(19, 0, menit);
      Disp.drawText(0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmha;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////
  /////////////////////ALARM ADZAN MAGHRIB ////////////////////////////////////////////
  get_float_time_parts(times[5], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(Arial_Black_16);
    sprintf(tanggaladz, "Adzan %s", TimeName[5]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 0, tanggaladz);
      Disp.drawFilledRect(33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      //  Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(19, 0, menit);
      Disp.drawText(0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmhm;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////
  /////////////////////ALARM ADZAN ISYA ////////////////////////////////////////////
  get_float_time_parts(times[6], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes)
  {

    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      //
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(Arial_Black_16);
    sprintf(tanggaladz, "Adzan %s", TimeName[6]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 0, tanggaladz);
      Disp.drawFilledRect(33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(19, 0, menit);
      Disp.drawText(0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmhi;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////
}

/////running ADZAN SELAIN EMPAT PANEL//////////////////////////////////////

void saatadzan2()
{

  static uint8_t d;
  int bagong;
  // RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];
  char detik[3];
  static uint32_t xadz;
  int Hari = rHar;
  int Hor = rJam;
  int Min = rMen;
  int Sec = rDet;
  int adzan = config.durasiadzan * 6;

  static uint8_t dtgl;
  static char tanggaladz[18];
  static uint32_t pMtglhij;
  static uint32_t pMadz;
  int hours, minutes;
  /////////////////////ALARM ADZAN SUBUH ////////////////////////////////////////////
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(SystemFont5x7);
    sprintf(tanggaladz, "Adzan %s", TimeName[0]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 5, tanggaladz);
      Disp.drawFilledRect(32 + 33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      //  Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(32 + 19, 0, menit);
      Disp.drawText(32 + 0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmhs;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  /////////////////////////////end/////////////////////////////////////////
  /////////////////////ALARM ADZAN DZUHUR NON JUMAT////////////////////////////////////////////
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes && Hari != 5)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(SystemFont5x7);
    sprintf(tanggaladz, "Adzan %s", TimeName[2]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 5, tanggaladz);
      Disp.drawFilledRect(32 + 33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      //  Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(32 + 19, 0, menit);
      Disp.drawText(32 + 0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmhd;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////

  /////////////////////ALARM ADZAN DZUHUR HARI JUMAT////////////////////////////////////////////
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes && Hari == 5)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(SystemFont5x7);
    sprintf(tanggaladz, "Adzan Jum'at");
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 5, tanggaladz);
      Disp.drawFilledRect(32 + 33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      //  Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(32 + 19, 0, menit);
      Disp.drawText(32 + 0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmhd;
      menitiqmh = iqmh - 1;
      tampilanutama = 2;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////

  /////////////////////ALARM ADZAN ASHAR ////////////////////////////////////////////
  get_float_time_parts(times[3], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(SystemFont5x7);
    sprintf(tanggaladz, "Adzan %s", TimeName[3]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 5, tanggaladz);
      Disp.drawFilledRect(32 + 33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      //  Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(32 + 19, 0, menit);
      Disp.drawText(32 + 0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmha;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////
  /////////////////////ALARM ADZAN MAGHRIB ////////////////////////////////////////////
  get_float_time_parts(times[5], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes)
  {
    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(SystemFont5x7);
    sprintf(tanggaladz, "Adzan %s", TimeName[5]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 5, tanggaladz);
      Disp.drawFilledRect(32 + 33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      //  Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(32 + 19, 0, menit);
      Disp.drawText(32 + 0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {
      iqmh = config.iqmhm;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////
  /////////////////////ALARM ADZAN ISYA ////////////////////////////////////////////
  get_float_time_parts(times[6], hours, minutes);
  minutes = minutes + config.ihti;
  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }
  if (Hor == hours && Min == minutes)
  {

    if (Hor == hours && Min == minutes && rDet <= 7)
    {
      //
      buzzerku();
    }
    berhenti = 1;
    //
    uint32_t cMadz = millis();
    static uint32_t xadz;
    static uint32_t Speedadz = 50;
    int width = Disp.width();
    static uint32_t pMadz;
    Disp.setFont(SystemFont5x7);
    sprintf(tanggaladz, "Adzan %s", TimeName[6]);
    int fullScrolladz = Disp.textWidth(tanggaladz) + width;

    if ((millis() - pMadz) > Speedadz)
    {
      pMadz = millis();
      if (xadz < fullScrolladz)
      {
        ++xadz;
      }
      else
      {
        xadz = 0;
        Disp.clear();
        digitalWrite(buzzer, LOW);
      }
      // Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      Disp.drawText(width - xadz, 5, tanggaladz);
      Disp.drawFilledRect(32 + 33, 15, 0, 0, 0);
      sprintf(menit, "%02d", rMen);
      sprintf(jam, "%02d", rJam);
      //  Disp.drawRect(15, 3, 16, 5, 1, 1); //koordinat titik dua
      // Disp.drawRect(15, 9, 16, 11, 1, 1);//koordinat titik dua
      Disp.setFont(BigNumber);
      Disp.drawText(32 + 19, 0, menit);
      Disp.drawText(32 + 0, 0, jam);
    }
    if (Hor == hours && Min == minutes && rDet < 57)
    {
      tampilanutama = 0;
    }
    else
    {

      iqmh = config.iqmhi;
      menitiqmh = iqmh - 1;
      tampilanutama = 1;
      Disp.drawFilledRect(128, 15, 0, 0, 0);
      digitalWrite(buzzer, LOW);
    }
  }
  //////////////////////////////end////////////////////////////////////////
}

///////////////////////////////////IQOMAH //////////////
// iqomah
void Iqomahku()
{

  int posisiku;
  //
  if (configdisp.jpanel == 4)
  {
    int statusku;

    static uint32_t pMIqmh;
    uint32_t cM = millis();
    static char hitungmundur[6];

    Disp.setFont(Arial_Black_16);

    Disp.drawText(2, 1, "IQOMAH");

    if (detikiqmh == 60)
    {
      detikiqmh = 0;
    }
    if (cM - pMIqmh >= 1000)
    {
      pMIqmh = cM;
      detikiqmh--;
      if (detikiqmh < 0)
      {
        detikiqmh = 59;
        menitiqmh--;
      }
    }
    Disp.drawFilledRect(128, 15, 0, 0, 0);
    sprintf(hitungmundur, "%02d:%02d", menitiqmh, detikiqmh);
    Disp.setFont(Arial_Black_16);
    Disp.drawText(5, 1, "IQOMAH");
    Disp.setFont(Arial_Black_16);
    Disp.drawText(80, 1, hitungmundur);
    if ((menitiqmh == 0 && detikiqmh == 7) || (menitiqmh == 0 && detikiqmh == 6) || (menitiqmh == 0 && detikiqmh == 5) ||
        (menitiqmh == 0 && detikiqmh == 4) || (menitiqmh == 0 && detikiqmh == 3) || (menitiqmh == 0 && detikiqmh == 2) ||
        (menitiqmh == 0 && detikiqmh == 1))
    {
      buzzerku();
    }

    if (menitiqmh == 0 && detikiqmh == 0)
    {
      // Disp.clear();
      tampilanutama = 2;
      digitalWrite(buzzer, LOW);
    }
  }
  if (configdisp.jpanel == 3 || configdisp.jpanel == 2)
  {

    if (configdisp.jpanel == 3)
    {
      posisiku = 0;
    }
    if (configdisp.jpanel == 2)
    {
      posisiku = 16;
    }

    int statusku;
    static uint32_t pMIqmh;
    uint32_t cM = millis();
    static char hitungmundur[6];

    Disp.setFont(SystemFont5x7);

    Disp.drawText(posisiku + 62, 0, "IQOMAH");

    if (detikiqmh == 60)
    {
      detikiqmh = 0;
    }
    if (cM - pMIqmh >= 1000)
    {
      pMIqmh = cM;
      detikiqmh--;
      if (detikiqmh < 0)
      {
        detikiqmh = 59;
        menitiqmh--;
      }
    }
    // Disp.drawFilledRect(32, 15, 0, 0, 0) ;
    Disp.drawFilledRect(128, 15, 0, 0, 0);
    sprintf(hitungmundur, "%02d:%02d", menitiqmh, detikiqmh);
    Disp.setFont(SystemFont5x7);
    Disp.drawText(posisiku + 62, 0, "IQOMAH");
    Disp.setFont(SystemFont5x7);
    Disp.drawText(posisiku + 65, 8, hitungmundur);
    if ((menitiqmh == 0 && detikiqmh == 7) || (menitiqmh == 0 && detikiqmh == 6) || (menitiqmh == 0 && detikiqmh == 5) ||
        (menitiqmh == 0 && detikiqmh == 4) || (menitiqmh == 0 && detikiqmh == 3) || (menitiqmh == 0 && detikiqmh == 2) ||
        (menitiqmh == 0 && detikiqmh == 1))
    {
      buzzerku();
    }

    if (menitiqmh == 0 && detikiqmh == 0)
    {
      // Disp.clear();
      tampilanutama = 2;
      digitalWrite(buzzer, LOW);
    }
  }
  if (configdisp.jpanel == 1)
  {

    int statusku;
    static uint32_t pMIqmh;
    uint32_t cM = millis();
    static char hitungmundur[6];

    Disp.setFont(Font4x6);

    Disp.drawText(97, 0, "IQOMAH");

    if (detikiqmh == 60)
    {
      detikiqmh = 0;
    }
    if (cM - pMIqmh >= 1000)
    {
      pMIqmh = cM;
      detikiqmh--;
      if (detikiqmh < 0)
      {
        detikiqmh = 59;
        menitiqmh--;
      }
    }
    // Disp.drawFilledRect(32, 15, 0, 0, 0) ;
    Disp.drawFilledRect(128, 15, 0, 0, 0);
    sprintf(hitungmundur, "%02d:%02d", menitiqmh, detikiqmh);
    Disp.setFont(Font4x6);
    Disp.drawText(97, 0, "IQOMAH");
    Disp.setFont(SystemFont5x7);
    Disp.drawText(97, 8, hitungmundur);
    if ((menitiqmh == 0 && detikiqmh == 7) || (menitiqmh == 0 && detikiqmh == 6) || (menitiqmh == 0 && detikiqmh == 5) ||
        (menitiqmh == 0 && detikiqmh == 4) || (menitiqmh == 0 && detikiqmh == 3) || (menitiqmh == 0 && detikiqmh == 2) ||
        (menitiqmh == 0 && detikiqmh == 1))
    {
      buzzerku();
    }

    if (menitiqmh == 0 && detikiqmh == 0)
    {
      // Disp.clear();
      tampilanutama = 2;
      digitalWrite(buzzer, LOW);
    }
  }
}
//////end///////////////////

void peringatan()
{
  //

  static char sblm[50];
  static uint32_t pM;
  static uint32_t x;
  static uint32_t Speed = 50;
  int width = Disp.width();
  width = Disp.width();
  Disp.setFont(SystemFont5x7);
  sprintf(sblm, "Lurus dan rapatkan shof");
  int fullScroll = Disp.textWidth(sblm) + width;
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
      tampilanutama = 3;
      // return;
    }

    Disp.drawFilledRect(128, 15, 0, 0, 0);
    Disp.drawText(width - x, 4, sblm);
  }
}
///////////////////////////////////////////////////
void jamciliksholat()
{
  //
  int posisine;
  if (configdisp.jpanel == 4)
  {
    posisine = 0;
  }
  if (configdisp.jpanel == 3)
  {
    posisine = 32;
  }
  if (configdisp.jpanel == 2)
  {
    posisine = 64;
  }
  if (configdisp.jpanel == 1)
  {
    posisine = 100;
  }

  static uint8_t d;
  static uint32_t pMo;
  static uint32_t pMJamo;
  static uint32_t pMKedipo;
  uint32_t cMo = millis();
  static boolean kedip;

  // RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];
  char detik[3];

  if (cMo - pMJamo >= 2000)
  { // lamanya sholat

    pMJamo = cMo;
    d++;

    // JAM
    Disp.drawFilledRect(128, 15, 0, 0, 0); // uji coba
    sprintf(jam, "%02d", rJam);
    Disp.setFont(Font3x5);
    Disp.drawText(posisine + 1, 2, jam);

    // MENIT
    sprintf(menit, "%02d", rMen);
    Disp.setFont(Font3x5);
    Disp.drawText(posisine + 15, 2, menit);

    /*//DETIK
        sprintf(detik,"%02d", rDet);
        Disp.setFont(angka6x13);
        Disp.drawText(40, 8, detik);
    */
    if (d >= 250)
    { /////////////////////////lamanya sholat/////////////////

      Disp.clear();
      tampilanutama = 0;
      tampilanjam = 0;
      berhenti = 0;
      langkah = 1;
      d = 0;
    }
  }

  // KEDIP DETIK
  if (millis() - pMKedipo >= 500)
  {
    pMKedipo = millis();
    kedip = !kedip;
  }

  if (kedip)
  {
    Disp.drawRect(posisine + 11, 6, posisine + 11, 6, 1, 1); // koordinat titik duakecil font 3 x4 (koordinatx,y,x,y,on,on,on)
    Disp.drawRect(posisine + 11, 8, posisine + 11, 8, 1, 1);
  }
  else
  {
    Disp.drawRect(posisine + 11, 6, posisine + 11, 6, 0, 0);
    Disp.drawRect(posisine + 11, 8, posisine + 11, 8, 0, 0);
  }
}

//////////////////////

void TampilJamDinamis(uint32_t y)
{
  //
  // RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];
  char detik[3];
  sprintf(jam, "%02d", rJam);
  sprintf(menit, "%02d", rMen);
  sprintf(detik, "%02d", rDet);

  // JAM
  Disp.setFont(angka6x13);
  Disp.drawText(3, y, jam);

  // MENIT
  Disp.setFont(angka6x13);
  Disp.drawText(22, y, menit);

  // DETIK
  Disp.setFont(angka6x13);
  Disp.drawText(40, y, detik);
}

void JamJatuhPulse()
{
  //

  static uint8_t y;
  static uint8_t d;
  static uint32_t pM;
  uint32_t cM = millis();

  static uint32_t pMPulse;
  static uint8_t pulse;

  if (cM - pMPulse >= 100)
  {
    pMPulse = cM;
    pulse++;
  }

  if (pulse > 8)
  {
    pulse = 0;
  }

  if (cM - pM > 25)
  {
    if (d == 0 and y < 32)
    {
      pM = cM;
      y++;
    }
    if (d == 1 and y > 0)
    {
      pM = cM;
      y--;
    }
  }

  if (cM - pM > 15000 and y == 32)
  {
    d = 1;
  }

  if (y == 32)
  {
    Disp.drawRect(17, 3 + pulse, 20, 11 - pulse, 0, 1);
  }

  if (y < 32)
  {
    Disp.drawRect(17, 3, 20, 11, 0, 0);
  }

  if (y == 0 and d == 1)
  {
    d = 0;
    Disp.clear();
    tampilanjam = 2;
  }

  TampilJamDinamis(y - 32);
}

void TampilJamArabDinamis(uint32_t y)
{
  //

  // RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];
  sprintf(jam, "%02d", rJam);
  sprintf(menit, "%02d", rMen);

  // JAM
  Disp.setFont(arab6x13);
  Disp.drawText(0, y, jam);

  // MENIT
  Disp.setFont(arab6x13);
  Disp.drawText(19, y, menit);
}

void JamArabJatuhPulse()
{
  //

  static uint8_t y;
  static uint8_t d;
  static uint32_t pM;
  uint32_t cM = millis();

  static uint32_t pMPulse;
  static uint8_t pulse;

  if (cM - pMPulse >= 100)
  {
    pMPulse = cM;
    pulse++;
  }

  if (pulse > 8)
  {
    pulse = 0;
  }

  if (cM - pM > 25)
  {
    if (d == 0 and y < 32)
    {
      pM = cM;
      y++;
    }
    if (d == 1 and y > 0)
    {
      pM = cM;
      y--;
    }
  }

  if (cM - pM > 15000 and y == 32)
  {
    d = 1;
  }

  if (y == 32)
  {
    Disp.drawRect(14, 3 + pulse, 17, 11 - pulse, 0, 1);
  }

  if (y < 32)
  {
    Disp.drawRect(14, 3, 17, 11, 0, 0);
  }

  if (y == 0 and d == 1)
  {
    d = 0;
    Disp.clear();
    tampilanjam = 3;
  }

  TampilJamArabDinamis(y - 32);
}

void JamJatuh()
{
  //

  static uint8_t y;
  static uint8_t d;
  static uint32_t pM;
  uint32_t cM = millis();

  static uint32_t pMKedip;
  static boolean kedip;

  if (cM - pMKedip >= 500)
  {
    pMKedip = cM;
    kedip = !kedip;
  }

  if (cM - pM > 50)
  {
    if (d == 0 and y < 32)
    {
      pM = cM;
      y++;
    }

    if (d == 1 and y > 0)
    {
      pM = cM;
      y--;
    }
  }

  if (cM - pM > 15000 and y == 32)
  {
    d = 1;
  }

  if (y == 32)
  {

    if (kedip)
    {
      // TITIK DUA ON
      Disp.drawRect(18, 3, 19, 5, 1, 1);
      Disp.drawRect(18, 9, 19, 11, 1, 1);
    }
    else
    {
      // TITIK DUA OFF
      Disp.drawRect(18, 3, 19, 5, 0, 0);
      Disp.drawRect(18, 9, 19, 11, 0, 0);
    }
  }

  if (y < 32)
  {
    Disp.drawRect(18, 3, 19, 5, 0, 0);
    Disp.drawRect(18, 9, 19, 11, 0, 0);
  }

  if (y == 3 and d == 1)
  {
    d = 0;
    Disp.clear();
    tampilanjam = 2;
  }

  TampilJamDinamis(y - 32);
}

//----------------------------------------------------------------------
// TAMPILKAN JAM BESAR

void TampilJam()
{
  //
  // Disp.loop(); // Jalankan Disp loop untuk refresh LED
  static uint8_t d;
  static uint32_t pM;
  static uint32_t pMJam;
  static uint32_t pMKedip;
  uint32_t cM = millis();
  static boolean kedip;

  // RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];
  char detik[3];

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
    /*
           if (d >= 15) {
             d = 0;
             Disp.clear();
             tampilanjam = 2;

           }
    */
  }

  // KEDIP DETIK
  if (millis() - pMKedip >= 500)
  {
    pMKedip = millis();
    kedip = !kedip;
  }

  if (kedip)
  {
    Disp.drawRect(15, 3, 16, 5, 1, 1); // koordinat titik dua
    Disp.drawRect(15, 9, 16, 11, 1, 1);

    // Disp.drawRect(33, 3, 34, 5, 1, 1); //koordinat titik dua
    // Disp.drawRect(33, 9, 34, 11, 1, 1);
  }
  else
  {

    Disp.drawRect(15, 3, 16, 5, 0, 0); // koordinat titik dua
    Disp.drawRect(15, 9, 16, 11, 0, 0);
    // Disp.drawRect(33, 3, 34, 5, 0, 0);
    // Disp.drawRect(33, 9, 34, 11, 0, 0);
    /*
         Disp.drawRect(43, 3, 44, 5, 0, 0); //koordinat titik dua
        Disp.drawRect(43, 9, 44, 11, 0, 0);
    */
  }
}

void TampilJamKecil()
{
  //
  // Disp.loop(); // Jalankan Disp loop untuk refresh LED
  static uint32_t pM;
  static uint32_t pMJam;
  uint32_t cM = millis();
  static boolean kedip;

  // RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];
  char detik[3];

  if (cM - pMJam >= 1000)
  {

    pMJam = cM;

    // JAM
    sprintf(jam, "%02d:%02d:%02d   %02d-%02d-%02d", rJam, rMen, rDet, rTgl, rBul, rTah);
    Disp.setFont(SystemFont5x7);
    textCenter(0, jam);
  }
}

void TampilJamKecilDua()
{
  //
  // Disp.loop(); // Jalankan Disp loop untuk refresh LED
  static uint32_t pM;
  static uint32_t pMJam;
  uint32_t cM = millis();
  static boolean kedip;

  // RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];
  char detik[3];
  static char tanggal[18];

  if (cM - pMJam >= 1000)
  {

    pMJam = cM;

    // JAM
    sprintf(jam, "%02d-%02d-%02d", rTgl, rBul, rTah - 2000);
    Disp.setFont(SystemFont5x7);
    sprintf(tanggal, "%s", weekDay[rHar]);
    // textCenter(0, jam);
    Disp.drawText(35, 9, jam);
    Disp.drawText(37, 0, tanggal);
  }
}

// TAMPILKAN TANGGAL tanggalku

void TampilTanggal()
{
  //
  // Disp.loop(); // Jalankan Disp loop untuk refresh LED

  // RtcDateTime now = Rtc.GetDateTime();
  static uint8_t d;
  static char hari[8];
  static char tanggal[18];
  static uint32_t pM;
  uint32_t cM = millis();
  ///////////////////////////////////static uint32_t datane;

  /////running tanggal
  TampilJamKecil();
  islam();
  // Disp.loop(); // Jalankan Disp loop untuk refresh LED
  static uint32_t x;
  static uint32_t Speed = 50;
  int width = Disp.width();
  Disp.setFont(SystemFont5x7);
  char *pasar[] = {"WAGE", "KLIWON", "LEGI", "PAHING", "PON"};
  // sprintf(hari, "%s", weekDay[rHar]);
  // sprintf(tanggal, "%s",namaBulanHijriah[tanggalHijriah.bulan - 1]);
  sprintf(tanggal, "%s %s %02d %s %02d", weekDay[rHar], namaHariPasaran[tanggalJawa.pasaran], rTgl, monthYear[rBul], rTah); /// bulannya tulisn

  // sprintf(tanggal, "%s %s %02d-%02d-%02d",weekDay[rHar],namaHariPasaran[tanggalJawa.pasaran], rTgl, rBul, rTah); //bulannya angka

  int fullScroll = Disp.textWidth(tanggal) + width;
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
      tampilanjam = 7;
      return;
    }

    Disp.drawText(width - x, 9, hari);
    Disp.drawText(width - x, 9, tanggal);
  }

  // sprintf(hari, "%s", weekDay[rHar]);
  //  sprintf(tanggal, "%02d.%02d.%02d", rTgl, rBul, rTah);
}
//////end///////////////////

void kalenderislam()
{
  //
  // Disp.loop(); // Jalankan Disp loop untuk refresh LED

  // RtcDateTime now = Rtc.GetDateTime();
  static uint8_t d;
  static char hari[8];
  static char tanggal[18];
  static uint32_t pM;
  uint32_t cM = millis();
  ///////////////////////////////////static uint32_t datane;

  /////running tanggal
  TampilJamKecil();
  islam();

  static uint32_t x;
  static uint32_t Speed = 50;
  int width = Disp.width();
  Disp.setFont(SystemFont5x7);
  char *pasar[] = {"WAGE", "KLIWON", "LEGI", "PAHING", "PON"};
  // sprintf(hari, "%s", weekDay[rHar]);
  // sprintf(tanggal, "%s",namaBulanHijriah[tanggalHijriah.bulan - 1]);

  sprintf(tanggal, "%02d %s %02dH", tanggalHijriah.tanggal, namaBulanHijriah[tanggalHijriah.bulan - 1], tanggalHijriah.tahun);

  int fullScroll = Disp.textWidth(tanggal) + width;
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
      tampilanjam = 0;
      return;
    }

    Disp.drawText(width - x, 9, hari);
    Disp.drawText(width - x, 9, tanggal);
  }

  // sprintf(hari, "%s", weekDay[rHar]);
  //  sprintf(tanggal, "%02d.%02d.%02d", rTgl, rBul, rTah);

  //////end///////////////////
}

// TAMPILKAN SUHU

void TampilSuhu()
{
  //
  // Tampilkan Suhu
  // RtcTemperature temp = Rtc.GetTemperature();
  // int celsius = celsius;
  char suhu[2];
  int koreksisuhu = 2; // Perkiraan selisih suhu ruangan dan luar ruangan

  static uint8_t d;
  static uint32_t pM;
  uint32_t cM = millis();

  if (cM - pM > 2000)
  {
    pM = cM;
    d++;

    Disp.setFont(SystemFont5x7);
    textCenter(0, "SUHU");
    sprintf(suhu, "%dC", celsius - koreksisuhu);
    Disp.setFont(angkasm47);
    textCenter(8, suhu);

    if (d >= 2)
    {
      d = 0;
      Disp.clear();
      tampilanjam = 5;
    }
  }
}

// PARAMETER PENGHITUNGAN JADWAL SHOLAT

void JadwalSholat()
{
  //
  // Disp.loop(); // Jalankan Disp loop untuk refresh LED

  // RtcDateTime now = Rtc.GetDateTime();

  int tahun = rTah;
  int bulan = rBul;
  int tanggal = rTgl;

  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);

  get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonawaktu, times);
}

// TAMPILAN JADWAL SHOLAT

void TampilJadwalSholat()
{
  //
  // Disp.loop(); // Jalankan Disp loop untuk refresh LED
  TampilJam();
  JadwalSholat();
  TampilJamKecilDua();

  static uint8_t i;
  static uint32_t pM;
  uint32_t cM = millis();

  char sholat[7];
  char jam[5];
  char TimeName[][8] = {"SUBUH  ", "TERBIT ", "DZUHUR ", "ASHAR  ", "TRBNM  ", "MAGHRIB", "ISYA'  "};
  int hours, minutes;

  if (cM - pM >= 5000)
  {

    pM = cM;
    // Disp.clear();

    // if (i == 1) {
    //   i = 2; // Abaikan Terbit
    //  }
    if (i == 4)
    {
      i = 5; // Abaikan Terbenam
    }

    get_float_time_parts(times[i], hours, minutes);

    minutes = minutes + config.ihti;

    if (minutes >= 60)
    {
      minutes = minutes - 60;
      hours++;
    }

    String sholat = TimeName[i];
    sprintf(jam, "%02d:%02d", hours, minutes);
    // Disp.loop();
    Disp.setFont(SystemFont5x7);
    Disp.drawText(86, 0, sholat);
    //  textCenter(0, sholat);
    Disp.setFont(SystemFont5x7);
    Disp.drawText(86, 9, jam);
    // textCenter(9, jam);

    i++;

    if (i > 7)
    {
      get_float_time_parts(times[0], hours, minutes);
      minutes = minutes + config.ihti;
      if (minutes < 11)
      {
        minutes = 60 - minutes;
        hours--;
      }
      else
      {
        minutes = minutes - 10;
      }
      // Disp.clear();
      sprintf(jam, "%02d:%02d", hours, minutes);
      Disp.setFont(SystemFont5x7);
      Disp.drawText(86, 0, "IMSAK  ");
      // textCenter(0, "IMSAK");
      Disp.setFont(SystemFont5x7);
      //   textCenter(9, jam);
      Disp.drawText(86, 9, jam);
    }

    if (i > 8)
    {
      i = 0;
      Disp.clear();
      tampilanjam = 3; // pergi ke tampilan 3
    }
  }
}

// ALARM SHOLAT BERJALAN SAAT MASUK WAKTU SHOLAT

void AlarmSholat()
{
  // Disp.loop(); // Jalankan Disp loop untuk refresh LED
  //
  //  RtcDateTime now = Rtc.GetDateTime();

  int Hari = rHar;
  int Hor = rJam;
  int Min = rMen;
  int Sec = rDet;
  int adzan = config.durasiadzan * 60000;

  //  JadwalSholat();
  int hours, minutes, seconds;

  // Tanbih Imsak
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + config.ihti;

  if (minutes < 10)
  {
    minutes = 60 - minutes;
    hours--;
  }
  else
  {
    minutes = minutes - 10;
  }

  if (Hor == hours && Min == minutes)
  {
    // BuzzerPendek();
    Disp.clear();
    Disp.setFont(SystemFont5x7);
    textCenter(0, "WAKTU");
    Disp.setFont(SystemFont5x7);
    textCenter(7, "IMSAK");
    delay(adzan);
    Disp.clear();
  }

  // Subuh
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + config.ihti;

  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }

  if (Hor == hours && Min == minutes)
  {
    // BuzzerPendek();
    Disp.clear();
    Disp.setFont(SystemFont5x7);
    textCenter(0, "ADZAN");

    Disp.setFont(SystemFont5x7);
    textCenter(9, "SUBUH");
    delay(adzan);
    Disp.clear();
    iqmh = config.iqmhs;
    menitiqmh = iqmh - 1;
    tampilanutama = 1;
  }

  // Dzuhur
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + config.ihti;

  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }

  if (Hor == hours && Min == minutes && Hari != 5)
  {
    BuzzerPendek();
    Disp.clear();
    Disp.setFont(SystemFont5x7);
    textCenter(0, "ADZAN");

    Disp.setFont(SystemFont5x7);
    textCenter(9, "DZUHUR");
    delay(adzan);
    Disp.clear();
    iqmh = config.iqmhd;
    menitiqmh = iqmh - 1;
    tampilanutama = 1;
  }
  else if (Hor == hours && Min == minutes && Hari == 5)
  {
    BuzzerPendek();
    Disp.clear();
    Disp.setFont(SystemFont5x7);
    textCenter(0, "ADZAN");

    Disp.setFont(SystemFont5x7);
    textCenter(9, "JUM'AT");
    delay(adzan);
  }

  // Ashar
  get_float_time_parts(times[3], hours, minutes);
  minutes = minutes + config.ihti;

  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }

  if (Hor == hours && Min == minutes)
  {
    BuzzerPendek();
    Disp.clear();
    Disp.setFont(SystemFont5x7);
    textCenter(0, "ADZAN");

    Disp.setFont(SystemFont5x7);
    textCenter(9, "ASHAR");
    delay(adzan);
    Disp.clear();
    iqmh = config.iqmha;
    menitiqmh = iqmh - 1;
    tampilanutama = 1;
  }

  // Maghrib
  get_float_time_parts(times[5], hours, minutes);
  minutes = minutes + config.ihti;

  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }

  if (Hor == hours && Min == minutes)
  {
    BuzzerPendek();
    Disp.clear();
    Disp.setFont(SystemFont5x7);
    textCenter(0, "ADZAN");

    Disp.setFont(SystemFont5x7);
    textCenter(9, "MAGHRIB");
    delay(adzan);
    Disp.clear();
    iqmh = config.iqmhm;
    menitiqmh = iqmh - 1;
    tampilanutama = 1;
  }

  // Isya'
  get_float_time_parts(times[6], hours, minutes);
  minutes = minutes + config.ihti;

  if (minutes >= 60)
  {
    minutes = minutes - 60;
    hours++;
  }

  if (Hor == hours && Min == minutes)
  {
    BuzzerPendek();
    Disp.clear();
    Disp.setFont(SystemFont5x7);
    textCenter(0, "ADZAN");

    Disp.setFont(SystemFont5x7);
    textCenter(9, "ISYA'");
    delay(adzan);
    Disp.clear();
    iqmh = config.iqmhi;
    menitiqmh = iqmh - 1;
    tampilanutama = 1;
  }
}

// HITUNG MUNDUR WAKTU SETELAH ADZAN SAMPAI MULAI IQOMAH

/*void Iqomah() {

  static uint32_t pMIqmh;
  uint32_t cM = millis();
  static char hitungmundur[6];

  Disp.setFont(SystemFont5x7);
  textCenter(0, "IQOMAH");

  if (detikiqmh == 60) {
    detikiqmh = 0;
  }

  if (cM - pMIqmh >= 1000) {

    pMIqmh = cM;
    detikiqmh--;

    if (menitiqmh == 0 && detikiqmh == 0) {
      Disp.clear();
      textCenter(0, "LURUS DAN");
      textCenter(9, "RAPAT SHOF");
     // BuzzerPanjang();
      detikiqmh = 59;
      Disp.clear();
      Disp.setFont(Font3x5);
      textCenter(1, "SHOLAT");
      delay(400000);//lamanya mati
      tampilanutama = 0;
    }

    if (detikiqmh < 0) {
      detikiqmh = 59;
      menitiqmh--;
    }

  }

  sprintf(hitungmundur, "%02d:%02d", menitiqmh, detikiqmh);
  Disp.setFont(SystemFont5x7);
  textCenter(9, hitungmundur);

  }

  void BuzzerPanjang() {

  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(50);

  }
*/

static char *nama[] = {config.nama};

void TeksJalanNama()
{
  //
  TampilJamKecil();
  static uint32_t pM;
  static uint32_t x;
  static uint32_t Speed = 50;
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
      tampilanjam = 4;
      return;
    }
    Disp.drawText(width - x, 9, nama[0]);
  }
}

// TAMPILKAN SCROLLING TEKS INFO1

static char *info1[] = {config.info1};

void TeksJalanInfo1()
{
  //
  TampilJamKecil();

  static uint32_t pM;
  static uint32_t x;
  static uint32_t Speed = 50;
  int width = Disp.width();
  Disp.setFont(SystemFont5x7);
  int fullScroll = Disp.textWidth(info1[0]) + width;
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
      tampilanjam = 6;
      return;
    }
    Disp.drawText(width - x, 9, info1[0]);
  }
}

// TAMPILKAN SCROLLING TEKS INFO2

static char *info2[] = {config.info2};

void TeksJalanInfo2()
{
  //
  TampilJamKecil();

  static uint32_t pM;
  static uint32_t x;
  static uint32_t Speed = 50;
  int width = Disp.width();
  Disp.setFont(SystemFont5x7);
  int fullScroll = Disp.textWidth(info2[0]) + width;
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
      tampilanjam = 0;
      return;
    }
    Disp.drawText(width - x, 9, info2[0]);
  }
}

// TAMPILKAN SCROLLING TEKS INFO3

static char *info3[] = {config.info3};

void TeksJalanInfo3()
{
  //
  TampilJamKecil();

  static uint32_t pM;
  static uint32_t x;
  static uint32_t Speed = 50;
  int width = Disp.width();
  Disp.setFont(SystemFont5x7);
  int fullScroll = Disp.textWidth(info3[0]) + width;
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
      tampilanjam = 0;
      return;
    }

    Disp.drawText(width - x, 9, info3[0]);
  }
}

void logoax(uint32_t x)
{
  static const uint8_t logoax[] PROGMEM = {
      16, 16,
      B00000000, B00000000,
      B01100110, B01111110,
      B01100110, B01111110,
      B01100110, B01100110,
      B01100110, B01100110,
      B01111110, B01111110,
      B01111110, B01111110,
      B01100000, B01100000,
      B01100000, B01100000,
      B01111110, B01111110,
      B01111110, B01111110,
      B01100110, B00000110,
      B01100110, B00000110,
      B01111111, B11111110,
      B01111111, B11111110,
      B00000000, B00000000};
  Disp.drawBitmap(x, 0, logoax);
}

void logobx(uint32_t x)
{
  static const uint8_t logobx[] PROGMEM = {
      16, 16,
      B00000000, B00000000,
      B01111111, B11111110,
      B01111111, B11111110,
      B00000000, B00000000,
      B00000000, B00000000,
      B01111110, B01100110,
      B01111110, B01100110,
      B00000110, B01100110,
      B00000110, B01100110,
      B01111110, B01100110,
      B01111110, B01100110,
      B01100110, B01100110,
      B01100110, B01100110,
      B01111111, B11111110,
      B01111111, B11111110,
      B00000000, B00000000};
  Disp.drawBitmap(x, 0, logobx);
}

//----------------------------------------------------------------------
// ANIMASI LOGO

void animLogoX()
{

  static uint8_t x;
  static uint8_t d; // 0=in, 1=out
  static uint32_t pM;
  uint32_t cM = millis();

  if ((cM - pM) > 35)
  {
    if (d == 0 and x < 16)
    {
      pM = cM;
      d++;
    }
    if (d == 1 and x > 0)
    {
      pM = cM;
      d--;
    }
  }

  if ((cM - pM) > 35 and x == 16)
  {
    d = 1;
  }

  if (x == 0 and d == 1)
  {
    d = 0;
    tampilanjam = 1;
  }

  logoax(x - 120);
  logobx(120 - x);
}

// TOGGLE LED INTERNAL UNTUK STATUS MODE WIFI

void toggleLED()
{

  digitalWrite(pin_led, !digitalRead(pin_led));
  server.send_P(200, "text/html", setwaktu);
}

void branding()
{
  //
  Disp.clear();
  Disp.setFont(SystemFont5x7);
  Disp.drawText(0, 0, "ROKHMAD");
  Disp.drawText(0, 9, ".COM");
  delay(1000);

  Disp.clear();
  Disp.setFont(SystemFont5x7);
  Disp.drawText(0, 0, "ROKHMAD");
  Disp.drawText(0, 9, ".COM");
  delay(1000);

  Disp.clear();
  Disp.setFont(SystemFont5x7);
  textCenter(3, "2020");
  delay(1000);

  Disp.clear();
}
