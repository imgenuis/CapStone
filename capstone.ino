#include "DHT.h"
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define A_SOIL_HUMI A0

int relay = 8;
int R = 10; //red
int G = 9; //green
int B = 11; //blue
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(7, DHT22);

SoftwareSerial BT() //tx,rx 
int soilHumidity;
/*디지털핀 초기화하기*/
void initPin() {
  
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);

}
void dht_value(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("hum ");
  Serial.println(h);
  Serial.print("tmp ");
  Serial.println(t);
  delay(1000);
}
void introLcd() {
  lcd.print("Cap stone");
}

/*void printLcd() {
  //lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Moisture : ");
  lcd.print(soilHumidity);
  lcd.print("%");
  lcd.setCursor(0, 1);
  if(soilHumidity < 20) lcd.print("Need Water");
  else if(soilHumidity < 50) lcd.print("Soil is Dry");
  else if(soilHumidity < 90) lcd.print("Soil is Wet");
  else lcd.print("Enough Water");
  
}*/

/*LCD 초기화하기*/
void initLcd() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  introLcd();
}

/*토양습도 계산하기*/
void calcSoilHumidity() {
  soilHumidity = map(analogRead(A_SOIL_HUMI), 1000, 400, 0, 100);
  /*Serial.print("hum:");
  Serial.print(soilHumidity);*/
  if(soilHumidity > 100) soilHumidity = 100;
  else if(soilHumidity < 0) soilHumidity = 0;
}

void LED() {
  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(B, HIGH);
}

void setup() {
  //initPin();
  initLcd();
  dht.begin();
  delay(2000);
  pinMode(relay, OUTPUT);
  
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  dht_value();
  calcSoilHumidity();
  
  //printLcd();
  int lg=analogRead(A0);

  if(lg<300){
    initPin();
  }
  if (soilHumidity < 20) 
    {
      delay(300);
      lcd.clear();
      lcd.noBacklight();
      digitalWrite(relay, LOW);
      delay(400);  
      digitalWrite(relay, HIGH);
      delay(2000);
      } else {
      digitalWrite(relay, HIGH);
      delay(2000);
     }
} 
