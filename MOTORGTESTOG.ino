#define left_DIR 32
#define left_PWM 33
#define right_DIR 25
#define right_PWM 26
#define LED_BUILTIN 2

void setup() {
  // Set motor and LED pins as output
  pinMode(left_DIR, OUTPUT);
  pinMode(left_PWM, OUTPUT);
  pinMode(right_DIR, OUTPUT);
  pinMode(right_PWM, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("Starting DC Motor Test...");
}

// === Helper Function to Set Motor Speed and Direction ===
void setMotor(int pwmPin, int dirPin, int speed, bool reverse) {
  speed = constrain(speed, -255, 255);  // limit speed range
  bool direction = speed >= 0;
  if (reverse) direction = !direction;

  digitalWrite(dirPin, direction);  // set direction
  analogWrite(pwmPin, abs(speed));  // set speed (PWM value)
}

void loop() {
  // === Forward Test ===
  Serial.println("Forward Speed Up");
  for (int speed = 0; speed <= 255; speed++) {
    setMotor(left_PWM, left_DIR, speed, false);
    setMotor(right_PWM, right_DIR, speed, true);  // reverse one side if needed
    delay(12);                                    // 256 * 12ms ≈ 3 seconds
  }

  Serial.println("Forward Slow Down");
  for (int speed = 255; speed >= 0; speed--) {
    setMotor(left_PWM, left_DIR, speed, false);
    setMotor(right_PWM, right_DIR, speed, true);
    delay(12);
  }

  delay(500);

  // === Backward Test ===
  Serial.println("Backward Speed Up");
  for (int speed = 0; speed <= 255; speed++) {
    setMotor(left_PWM, left_DIR, -speed, false);
    setMotor(right_PWM, right_DIR, -speed, true);
    delay(12);
  }

  Serial.println("Backward Slow Down");
  for (int speed = 255; speed >= 0; speed--) {
    setMotor(left_PWM, left_DIR, -speed, false);
    setMotor(right_PWM, right_DIR, -speed, true);
    delay(12);
  }

  // === Stop Motors ===
  setMotor(left_PWM, left_DIR, 0, false);
  setMotor(right_PWM, right_DIR, 0, true);
  Serial.println("Test Complete. Robot Stopped.");

  // === Light up LED to show test done ===
  digitalWrite(LED_BUILTIN, HIGH);
  while (1)
    ;  // Stop program here
}
