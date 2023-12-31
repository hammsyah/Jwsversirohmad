const int buzzer = 3;

void BuzzerPendek() {

  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(20);

}

void buzzerku() {

  static uint8_t d;
  static uint32_t pMo;
  static uint32_t pMJamo;
  static uint32_t pMKedipo;
  uint32_t cMo = millis();
  static boolean kedip;

  RtcDateTime now = Rtc.GetDateTime();
  char jam[3];
  char menit[3];
  char detik[3];

  if (cMo - pMJamo >= 1000) {

    pMJamo = cMo;
    d++;
    if (d >= 5) { /////////////////////////lamanya buzer/////////////////
      // Disp.clear();
      //tampilanutama = 0;
      //tampilanjam = 0;
      // berhenti = 0;
      // langkah = 1;
      digitalWrite(buzzer, LOW);
      d = 5;
    }

  }

  //KEDIP DETIK
  if (millis() - pMKedipo >= 1000) {
    pMKedipo = millis();
    kedip = !kedip;
  }

  if (kedip) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);

  }

}