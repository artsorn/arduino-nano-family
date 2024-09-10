
// #define touch_pin 12

// bool touch_flg_initialized = false;
// int touch_val = 0;
// int touch_state = LOW; 

// unsigned long touch_previous_millis_1 = 0;
// const long touch_period_1 = 500;

// bool touch_init() {
//   pinMode(touch_pin, INPUT);
//   touch_flg_initialized = true;
//   return true;
// }

// bool touch_start(unsigned long current_millis) {
//   if (!touch_flg_initialized)  // to avoid any runtime error in case user missed to initialize
//   {
//     Serial.println("ERROR in touch_start() - touch not initialized, call 'touch_init()' missed");
//     return false;
//   }

//   if (current_millis - touch_previous_millis_1 < touch_period_1) {
//     return false;
//   }

//   touch_previous_millis_1 = current_millis;

//   touch_val = digitalRead(touch_pin);

//   // Serial.print("touch_val: ");
//   // Serial.println(String(touch_val));

//   if (touch_val == LOW) {           // check if the sensor is LOW
//     if (touch_state == HIGH) {
//       // Serial.println("touch detected!"); 
//       relay_toggle(1);
//       touch_state = LOW;       // update variable touch_state to LOW
//       return true;
//     }
//   } else {
//       delay(200);             // delay 200 milliseconds 
//       if (touch_state == LOW){
//         // Serial.println("Motion stopped!");
//         touch_state = HIGH;       // update variable state to HIGH
//     }
//   }
//   return false;
// }