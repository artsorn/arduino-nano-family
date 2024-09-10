

// bool touch_init();
// bool touch_start(unsigned long current_millis);

// #define switch_float_pin_1 3
// #define switch_button_pin_1 4

bool dht_init();
bool dht_start(unsigned long current_millis);

// bool tracker_init();
// bool tracker_start(unsigned long current_millis);

bool relay_init();
bool relay_toggle(int channel);

bool switch_button_init();
bool switch_button_start(unsigned long current_millis);

bool switch_float_init();
bool switch_float_start(unsigned long current_millis);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  unsigned long setup_millis = millis();

  dht_init();
  relay_init();
  // tracker_init();
  switch_button_init();
  switch_float_init();

  bool is_dht_detected = dht_start(setup_millis);

  // touch_init();
  // Serial.println(F("------------------------------------"));

  // pinMode(switch_float_pin_1, INPUT_PULLUP);
  // pinMode(switch_button_pin_1, INPUT_PULLUP);
}

void loop() {

  // int switch_float_val_1 = digitalRead(switch_float_pin_1);
  // if (switch_float_val_1 == HIGH)
  // {
  //   Serial.println("The switch_float is being pressed.");
  // }
  
  // int switch_button_val_1 = digitalRead(switch_button_pin_1);
  // if (switch_button_val_1 == LOW)
  // {
  //   Serial.println("The switch_button is being pressed.");
  //   relay_toggle(1);
  // }

  unsigned long current_millis = millis();
  // bool is_touch_detected = touch_start(current_millis);
  bool is_dht_detected = dht_start(current_millis);
  // bool is_tracker_detected = tracker_start(current_millis);
  bool is_switch_button_detected = switch_button_start(current_millis);
  bool is_switch_float_detected = switch_float_start(current_millis);

  if (Serial.available() > 0) {
      char input = Serial.read();

      if (input == '1') {
        relay_toggle(1);
      } else if (input == '2') {
        relay_toggle(2);
      } else if (input == '3') {
        relay_toggle(3);
      } else if (input == '4') {
        relay_toggle(4);
      } else if (input == '5') {
        relay_toggle(5);
      }
  }
  delay(100);
}
