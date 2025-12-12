// #include "HX711.h"

#define DOUT 2
#define CLK 3

HX711 scale;

long zeroRaw = 0;
const float scaleFactor = 20.0;  // adjust for sensitivity
const int avgSamples = 1;         // faster reads, less averaging

void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println("HX711 Ultra-Sensitive Fast Reader");

  pinMode(CLK, OUTPUT);
  digitalWrite(CLK, LOW);
  delay(50);

  scale.begin(DOUT, CLK);
  scale.set_gain(128);

  Serial.println("Waiting for HX711...");
  unsigned long start = millis();
  while (!scale.is_ready() && millis() - start < 10000) { // wait up to 10 seconds
    delay(2);
  }

  if (!scale.is_ready()) {
    Serial.println("ERROR: HX711 NOT READY — check wiring/power.");
    while(1){ delay(500); }
  }

  Serial.println("Taring... keep load cell still");
  delay(200);
  zeroRaw = scale.read_average(avgSamples);
  Serial.print("Zero raw = ");
  Serial.println(zeroRaw);

  Serial.println("Ready for live readings...");
}

void loop() {
  if (scale.is_ready()) {
    long raw = scale.read_average(avgSamples);
    long delta = raw - zeroRaw;  // invert if pulling decreases raw
    float grams = (float)delta / scaleFactor;
    if (grams < 0) grams = 0;

    Serial.print(grams, 2);
    Serial.println(" g");
  }

  // faster update (~50–60 readings/sec)
  delay(20);
}
