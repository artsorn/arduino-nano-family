
#define switch_button_pin 4

bool switch_button_flg_initialized = false;
int switch_button_val = 0;
int switch_button_state = LOW; 

unsigned long switch_button_previous_millis_1 = 0;
const long switch_button_period_1 = 51;

bool switch_button_init() {
  pinMode(switch_button_pin, INPUT_PULLUP);
  switch_button_flg_initialized = true;
  return true;
}

bool switch_button_start(unsigned long current_millis) {
  if (!switch_button_flg_initialized)  // to avoid any runtime error in case user missed to initialize
  {
    Serial.println("ERROR in switch_button_start() - switch_button not initialized, call 'switch_button_init()' missed");
    return false;
  }

  if (current_millis - switch_button_previous_millis_1 < switch_button_period_1) {
    return false;
  }

  switch_button_previous_millis_1 = current_millis;

  switch_button_val = digitalRead(switch_button_pin);

  // Serial.print("switch_button_val: ");
  // Serial.println(String(switch_button_val));

  if (switch_button_val == LOW) {           // check if the sensor is LOW
    if (switch_button_state == HIGH) {
      Serial.println("switch_button detected!"); 
      relay_toggle(1);
      switch_button_state = LOW;       // update variable switch_button_state to LOW
      return true;
    }
  } else {
      delay(200);             // delay 200 milliseconds 
      if (switch_button_state == LOW){
        // Serial.println("Motion stopped!");
        switch_button_state = HIGH;       // update variable state to HIGH
    }
  }
  return false;
}