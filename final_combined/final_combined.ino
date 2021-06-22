
#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


int off_ = 13;
int switch_ = A0;
unsigned long last_time;
unsigned long present_time;

Adafruit_SSD1306 display(128, 32, &Wire, 4);
int count_ = 0;
int battery_data = 0;
void setup() {

  initialize_();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);
  testscrolltext();    // Display Text

}

void loop() {
  testscrolltext();
  int switch_data = digitalRead(switch_);
  battery_data = analogRead(switch_);
  //  Serial.println(battery_data);
  //  delay(1000);
  if (switch_data == HIGH) {
    present_time = millis();
    Serial.println(present_time - last_time);
  }

  else if ((present_time - last_time) > 3000) {
    count_ ++;
    EEPROM.update(0, count_);
//    Serial.println("Inside 8 second");
    testscrolltext();
    delay(500);
    digitalWrite(off_, HIGH);
    delay(2000);
  }
  else {
    delay(500);
//    Serial.println("Inside the else");
    digitalWrite(off_, HIGH);
    delay(2000);
  }

}

void testscrolltext(void) {
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 1);
  display.println(count_);
  //  display.println(battery_data);
  //  display.println(F(count));

  display.display();
  delay(100);
  //  display.startscrollright(0x00, 0x0F);
}

void initialize_() {
  Serial.begin(9600);
  pinMode(off_, OUTPUT);
  pinMode(switch_, INPUT);

  digitalWrite(off_, LOW);
  count_ = EEPROM.read(0);
  last_time = millis();
  //  EEPROM.update(0, 0);
}
