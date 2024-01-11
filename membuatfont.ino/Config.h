// Durasi waktu iqomah
struct Config
{

  // int jpanel;
  int iqmhs;
  int iqmhd;
  int iqmha;
  int iqmhm;
  int iqmhi;
  int durasiadzan;
  int ihti; // Koreksi Waktu Menit Jadwal Sholat
  float latitude;
  float longitude;
  int zonawaktu;
  char nama[64];
  char info1[512];
  char info2[512];
  char info3[512];
};

const char *fileconfigjws = "/configjws.json";
Config config;

int iqmh;
int menitiqmh;
int detikiqmh = 60;

struct ConfigWifi
{
  char wifissid[64];
  char wifipassword[64];
};
const char *fileconfigwifi = "/configwifi.json";
ConfigWifi configwifi;

struct ConfigDisp
{
  int cerah;
  int jpanel;
};
const char *fileconfigdisp = "/configdisp.json";
ConfigDisp configdisp;

void LoadDataAwal()
{

  if (config.iqmhs == 0)
  {
    config.iqmhs = 12;
  }

  if (config.iqmhd == 0)
  {
    config.iqmhd = 8;
  }

  if (config.iqmha == 0)
  {
    config.iqmha = 6;
  }

  if (config.iqmhm == 0)
  {
    config.iqmhm = 5;
  }

  if (config.iqmhi == 0)
  {
    config.iqmhi = 5;
  }

  if (config.durasiadzan == 0)
  {
    config.durasiadzan = 1;
  }

  if (config.ihti == 0)
  {
    config.ihti = 2;
  }

  if (config.latitude == 0)
  {
    config.latitude = -7.22;
  }

  if (config.longitude == 0)
  {
    config.longitude = 111.80;
  }

  if (config.zonawaktu == 0)
  {
    config.zonawaktu = 7;
  }

  if (strlen(config.nama) == 0)
  {
    strlcpy(config.nama, "www.hamtronik.com", sizeof(config.nama));
  }

  if (strlen(config.info1) == 0)
  {
    strlcpy(config.info1, "jws edit script by hamtronik 2024", sizeof(config.info1));
  }

  if (strlen(config.info2) == 0)
  {
    strlcpy(config.info2, "info2", sizeof(config.info2));
  }

  if (strlen(config.info3) == 0)
  {
    strlcpy(config.info3, "info3", sizeof(config.info3));
  }

  if (strlen(configwifi.wifissid) == 0)
  {
    strlcpy(configwifi.wifissid, "RAJEKWESI WIFI", sizeof(configwifi.wifissid));
  }

  if (strlen(configwifi.wifipassword) == 0)
  {
    strlcpy(configwifi.wifipassword, "", sizeof(configwifi.wifipassword));
  }

  if (configdisp.cerah == 0)
  {
    configdisp.cerah = 100;
  }

  if (configdisp.jpanel == 0)
  {
    configdisp.jpanel = 2;
  }
}

void loadDispConfig(const char *fileconfigdisp, ConfigDisp &configdisp)
{

  File configFileDisp = SPIFFS.open(fileconfigdisp, "r");

  if (!configFileDisp)
  {
    Serial.println("Gagal membuka fileconfigdisp untuk dibaca");
    return;
  }

  size_t size = configFileDisp.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFileDisp.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error)
  {
    Serial.println("Gagal parse fileconfigdisp");
    return;
  }
  configdisp.jpanel = doc["jpanel"];
  configdisp.cerah = doc["cerah"];

  configFileDisp.close();
}

void loadJwsConfig(const char *fileconfigjws, Config &config)
{

  File configFileJws = SPIFFS.open(fileconfigjws, "r");

  if (!configFileJws)
  {
    Serial.println("Gagal membuka fileconfigjws untuk dibaca");
    return;
  }

  size_t size = configFileJws.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFileJws.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error)
  {
    Serial.println("Gagal parse fileconfigjws");
    return;
  }

  config.iqmhs = doc["iqmhs"];
  config.iqmhd = doc["iqmhd"];
  config.iqmha = doc["iqmha"];
  config.iqmhm = doc["iqmhm"];
  config.iqmhi = doc["iqmhi"];
  config.durasiadzan = doc["durasiadzan"];
  config.ihti = doc["ihti"];
  config.latitude = doc["latitude"];
  config.longitude = doc["longitude"];
  config.zonawaktu = doc["zonawaktu"];
  strlcpy(config.nama, doc["nama"] | "Untuk 1000 Masjid", sizeof(config.nama)); // Set awal Nama
  strlcpy(config.info1, doc["info1"] | "", sizeof(config.info1));               // Set awal Info1
  strlcpy(config.info2, doc["info2"] | "", sizeof(config.info2));               // Set awal Info2
  strlcpy(config.info3, doc["info3"] | "", sizeof(config.info3));
  configFileJws.close();
}

void loadWifiConfig(const char *fileconfigwifi, ConfigWifi &configwifi)
{

  File configFileWifi = SPIFFS.open(fileconfigwifi, "r");

  if (!configFileWifi)
  {
    Serial.println("Gagal membuka fileconfigwifi untuk dibaca");
    return;
  }

  size_t size = configFileWifi.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFileWifi.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error)
  {
    Serial.println("Gagal untuk parse config file");
    return;
  }

  strlcpy(configwifi.wifissid, doc["wifissid"] | "", sizeof(configwifi.wifissid));
  strlcpy(configwifi.wifipassword, doc["wifipassword"] | "123456789", sizeof(configwifi.wifipassword));

  configFileWifi.close();
}