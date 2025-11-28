// This code is designed to run on an ESP32 using the Arduino framework (e.g., PlatformIO or Arduino IDE).

// Define the GPIO pins connected to the ANALOG O/P header of your IR array module.
// IMPORTANT: ESP32 only has ADC capabilities on specific pins (GPIO 32-39 are generally safest).
// Connect the 8 Analog O/P pins from your module to these pins on the ESP32.
const int NUM_CHANNELS = 8;
const int IR_PINS[NUM_CHANNELS] = {
  36, // ADC1_CH0 (VP) - Analog Channel 1
  39, // ADC1_CH3 (VN) - Analog Channel 2
  34, // ADC1_CH6 - Analog Channel 3
  35, // ADC1_CH7 - Analog Channel 4
  32, // ADC1_CH4 - Analog Channel 5
  33, // ADC1_CH5 - Analog Channel 6
  25, // ADC2_CH8 - Analog Channel 7
  26  // ADC2_CH9 - Analog Channel 8
};

// The ESP32 ADC resolution is 12-bit (0-4095).
const int ADC_MAX_VALUE = 4095;

void setup() {
  // Initialize the Serial Monitor for output
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 8-Channel IR Array Reader Initialized.");
  Serial.println("-------------------------------------------");

  // Since we are reading analog inputs, setting pin modes is often unnecessary
  // in the Arduino framework for ESP32, but it's good practice for clarity.
  for (int i = 0; i < NUM_CHANNELS; i++) {
    // pinMode(IR_PINS[i], INPUT); // Input mode is the default for analogRead
  }
}

void loop() {
  // Array to store the readings
  int ir_readings[NUM_CHANNELS];
  
  // Header
  Serial.println("\n--- Reading Sensor Array Data ---");
  
  // Read each sensor
  for (int i = 0; i < NUM_CHANNELS; i++) {
    // Read the raw analog value from the specified GPIO pin
    int raw_value = analogRead(IR_PINS[i]); 
    ir_readings[i] = raw_value;

    // Print the result for the current channel
    Serial.printf("Channel %d (GPIO %d): %4d / %d (Analog Value)\n", 
                  i + 1, IR_PINS[i], raw_value, ADC_MAX_VALUE);
  }

  // Footer and Summary
  Serial.println("---------------------------------");

  // Print a concise summary of the current readings
  Serial.print("Summary: [");
  for (int i = 0; i < NUM_CHANNELS; i++) {
    Serial.printf("CH%d: %d", i + 1, ir_readings[i]);
    if (i < NUM_CHANNELS - 1) {
      Serial.print(" | ");
    }
  }
  Serial.println("]");
  
  // Wait before taking the next set of readings (Read every 100 milliseconds)
  delay(100); 
}