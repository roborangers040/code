// This Arduino sketch measures distance using the HC-SR04 ultrasonic sensor
// and outputs the result in millimeters (mm).

// Define the sensor pin connections based on your request
const int trigPin = 19; // Trigger pin connected to D19
const int echoPin = 18; // Echo pin connected to D18

// Define the speed of sound for calculation:
// Speed of Sound in air at 20°C is approximately 343 meters/second.
// This translates to about 0.0343 cm/µs (microseconds).
// The formula for distance in centimeters is: Duration / 58
// Since 1 cm = 10 mm, the formula for distance in millimeters is: Duration / 5.8
const float speedOfSoundFactor = 5.8;

void setup() {
  // Initialize Serial communication for output
  Serial.begin(9600);
  Serial.println("HC-SR04 Distance Sensor Initialized.");
  Serial.println("Output is in Millimeters (mm).");

  // Set the Trig pin as an OUTPUT (to send the sound pulse)
  pinMode(trigPin, OUTPUT);
  // Set the Echo pin as an INPUT (to receive the duration of the reflected pulse)
  pinMode(echoPin, INPUT);

  // Initial state: ensure the trigger pin is LOW
  digitalWrite(trigPin, LOW);
  delay(500); // Wait a short period to stabilize
}

void loop() {
  // 1. CLEAR THE TRIGGER PIN
  // The sensor needs a clean pulse, so ensure the pin is LOW initially.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 2. SEND A 10µS PULSE TO TRIGGER
  // Send a short HIGH pulse (minimum 10µs required) to start the measurement.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // End the pulse

  // 3. MEASURE THE ECHO DURATION
  // 'pulseIn' reads the duration of the HIGH pulse on the Echo pin in microseconds (µs).
  // This duration is the time it took for the sound wave to travel to the object and back.
  long duration_us = pulseIn(echoPin, HIGH);

  // 4. CALCULATE DISTANCE IN MILLIMETERS (mm)
  // The sound traveled to the object and back (twice the distance), so we divide the total distance by 2.
  // The formula used incorporates this division:
  // Distance (mm) = duration_us / 5.8
  float distance_mm = (float)duration_us / speedOfSoundFactor;


  // 5. PRINT THE RESULTS
  // We use a simple constraint: the sensor is typically reliable between 20mm and 4000mm.
  if (distance_mm >= 4000 || distance_mm <= 20) {
    Serial.print("Distance: [Out of Range/Error]");
  } else {
    // Print the accurate measurement
    Serial.print("Distance: ");
    Serial.print(distance_mm);
    Serial.print(" mm");
  }
  Serial.println();

  // Wait before the next measurement
  delay(500);
}