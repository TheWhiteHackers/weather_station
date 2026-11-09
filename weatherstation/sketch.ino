#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define dhtpin 25
#define dhttype DHT11

#define screen_w 128
#define screen_h 64
#define oled_reset -1
#define screen_address 0.3C


int blueLed = 34;
int redLed = 32;
int greenLed = 35;
int motor = 33;
int display1 = 22;
int display2 = 23;
int photo = 21;
// int dht = D25;

int sensorValue = 0;

String message = "";

DHT dht(dhtpin, dhttype);
Adafruit_SSD1306 display(screen_w, screen_h, &Wire, oled_reset);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(blueLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.println("setup");

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("display fail"));
    while(1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);


  pinMode(motor, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)){
    Serial.println("falied");
    return;
  }

  if (t > 25) {
    digitalWrite(redLed, HIGH);
    digitalWrite(motor, HIGH);
    Serial.println("hot");

  } else if (t <= 25  && t > 10) {
    digitalWrite(greenLed, HIGH);
    Serial.println("mild");

  } else {
    digitalWrite(blueLed, HIGH);
    Serial.println("cold");

  }


  sensorValue = analogRead(photo);
  delay(500);

  if (sensorValue >= 850){
    message = "sunny";
  } else if (sensorValue >= 600 || sensorValue < 850){
    message = "outcast";
  } else if (sensorValue >= 400 || sensorValue < 600) {
    message = "you are indoors";
  } else {
    message = "dark";
  }

  display.setCursor(0, 0);
  display.print("The temperature is: ");
  display.print(t);
  display.setCursor(0, 16);
  display.print("The humidity is: ");
  display.print(h);
  display.setCursor(0, 32);
  display.print("The sky condition is: ");
  display.print(message);

  display.display();


}













