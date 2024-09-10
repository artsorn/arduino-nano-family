// #define tracker_pin 40 //14
// #define tracker_pin P0 //14
#define tracker_pin 0 //14

bool tracker_flg_initialized = false;
int tracker_val = 0;
int tracker_state = HIGH; 

unsigned long tracker_previous_millis_1 = 0;
const long tracker_period_1 = 3000;

bool tracker_init() {
  // pinMode(tracker_pin, INPUT);
  pinMode(tracker_pin,OUTPUT);
  // pcf8575.pinMode(tracker_pin, INPUT);
  
  tracker_flg_initialized = true;
  return true;
}

bool tracker_start(unsigned long current_millis) {
  if (!tracker_flg_initialized)  // to avoid any runtime error in case user missed to initialize
  {
    Serial.println("ERROR in tracker_start() - tracker not initialized, call 'tracker_init()' missed");
    return false;
  }

  if (current_millis - tracker_previous_millis_1 < tracker_period_1) {
    return false;
  }

  tracker_previous_millis_1 = current_millis;

  tracker_val = analogRead(tracker_pin);

  Serial.print("tracker_val: ");
  Serial.println(String(tracker_val));

  // if (tracker_val == LOW) {           // check if the sensor is LOW
  //   if (tracker_state == HIGH) {
  //     Serial.println("Tracker detected!"); 
  //     tracker_state = LOW;       // update variable tracker_state to LOW
  //     return true;
  //   }
  // } else {
  //     delay(200);             // delay 200 milliseconds 
  //     if (tracker_state == LOW){
  //       // Serial.println("Motion stopped!");
  //       tracker_state = HIGH;       // update variable state to HIGH
  //   }
  // }
  return false;
}