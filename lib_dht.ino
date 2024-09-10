// #include <Bonezegei_DHT22.h>

// //param = DHT22 signal pin
// Bonezegei_DHT22 dht(dht_pin);

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define dht_pin 2
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
DHT_Unified dht(dht_pin, DHTTYPE);

bool dht_flg_initialized = false;
int dht_val = 0;
int dht_state = HIGH; 

unsigned long dht_previous_millis_1 = 0;
const long dht_period_1 = 55000;

bool dht_init() {
  // pinMode(dht_pin, INPUT);
  // pcf8575.pinMode(dht_pin, INPUT);
  // sensors.begin();
  dht.begin();
  dht_flg_initialized = true;
  return true;
}

bool dht_start(unsigned long current_millis) {
  if (!dht_flg_initialized)  // to avoid any runtime error in case user missed to initialize
  {
    Serial.println("ERROR in dht_start() - dht not initialized, call 'dht_init()' missed");
    return false;
  }

  if (current_millis - dht_previous_millis_1 < dht_period_1) {
    return false;
  }

  dht_previous_millis_1 = current_millis;
  
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.print(F("°C, "));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F(" Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  return false;
}

// void layout() {
//   Serial.print("   Celsius => ");
//   Serial.println(String(double(dht.celsius) / 10, 1));
//   Serial.print("   Humdity => ");
//   Serial.println(String(double(dht.humidity) / 10, 1));
// }