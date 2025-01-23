// #include <FlowSensor.h>

// #define type YFB1
// #define waterflow_pin 5 

// bool waterflow_flg_initialized = false;

// unsigned long waterflow_previous_millis_1 = 0;
// const long waterflow_period_1 = 1000;

// FlowSensor Sensor(type, waterflow_pin);

// void count()
// {
// 	Sensor.count();
// }

// bool waterflow_init() {
//   // pinMode(waterflow_pin, INPUT);
//   // pinMode(waterflow_pin,INPUT_PULLUP);
//   // pcf8575.pinMode(waterflow_pin, INPUT);

//   Sensor.begin(count);

//   // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
//   // Configured to trigger on a FALLING state change (transition from HIGH
//   // state to LOW state)
//   // attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  
//   waterflow_flg_initialized = true;
//   return true;
// }

// bool waterflow_start(unsigned long current_millis) {
//   if (!waterflow_flg_initialized)  // to avoid any runtime error in case user missed to initialize
//   {
//     Serial.println("ERROR in waterflow_start() - waterflow not initialized, call 'waterflow_init()' missed");
//     return false;
//   }

//   if (current_millis - waterflow_previous_millis_1 < waterflow_period_1) {
//     return false;
//   }

//   waterflow_previous_millis_1 = current_millis;

//   Sensor.read();
//   // Serial.print("Flow rate (L/minute) : ");
//   // Serial.println(Sensor.getFlowRate_m());
//   // Serial.print("Volume (L) : ");
//   // Serial.println(Sensor.getVolume());

//   return false;
// }

// float waterflow_volume() {
//   return Sensor.getVolume();
// }

// float waterflow_rate() {
//   return Sensor.getFlowRate_m();
// }

// bool waterflow_reset() {
//   Sensor.resetVolume();
// }
