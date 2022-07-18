#include <LiquidCrystal.h>

LiquidCrystal lcd(10,11,12,13,A0,A1);

const int in_1 = 2, exhaust_1 = 3, out_1 = 4, in_2 = 5, exhaust_2 = 6, out_2 = 7, pressure_sensor = A5;

void truncate(String* str, int columns) {
  *str = str->substring(0, columns);
}
void print_lcd(String str, int row) {
  static const int COLUMNS = 16;
  if (str.length() > COLUMNS) truncate(&str, COLUMNS);
  int pre_spaces = (COLUMNS - str.length()) / 2;
  lcd.setCursor(0, row); lcd.print("                ");
  lcd.setCursor(pre_spaces, row); lcd.print(str);
}
void print_lcd(String str0, String str1, String str2, String str3) {
  static const int COLUMNS = 20;
  if(str0.length() > COLUMNS) truncate(&str0,COLUMNS);
  if(str1.length() > COLUMNS) truncate(&str1,COLUMNS);
  if(str2.length() > COLUMNS) truncate(&str2,COLUMNS);
  if(str3.length() > COLUMNS) truncate(&str3,COLUMNS);
  int pre_spaces0 = (COLUMNS - str0.length()) / 2;
  int pre_spaces1 = (COLUMNS - str1.length()) / 2;
  int pre_spaces2 = (COLUMNS - str2.length()) / 2;
  int pre_spaces3 = (COLUMNS - str3.length()) / 2;
  lcd.clear();
  lcd.setCursor(pre_spaces0, 0); lcd.print(str0);
  lcd.setCursor(pre_spaces1, 1); lcd.print(str1);
  lcd.setCursor(pre_spaces2, 2); lcd.print(str2);
  lcd.setCursor(pre_spaces3, 3); lcd.print(str3);
}
void default_lcd_text(int del) {
  print_lcd("oxygen concetrator","","","");
  delay(del);
}
void open_filter_1() {
  print_lcd("STATUS","","SIEVE BED 1: OPEN","SIEVE BED 2: CLOSED");
  digitalWrite(in_1, 0);
  delay(500);
  digitalWrite(exhaust_2, 0);
  delay(500);
  digitalWrite(out_2, 0);
  delay(500);
}
void close_filter_1() {
  digitalWrite(in_1, 1);
  delay(1000);
  digitalWrite(exhaust_2, 1);
  delay(1000);
  digitalWrite(out_2, 1);
  delay(1000);
}
void open_filter_2() {
  print_lcd("STATUS","","SIEVE BED 1: CLOSED","SIEVE BED 2: OPEN");
  digitalWrite(in_2, 0);
  delay(500);
  digitalWrite(exhaust_1, 0);
  delay(500);
  digitalWrite(out_1, 0);
  delay(500);
}
void close_filter_2() {
  digitalWrite(in_2, 1);
  delay(1000);
  digitalWrite(exhaust_1, 1);
  delay(1000);
  digitalWrite(out_1, 1);
  delay(1000);
}
String measure_pressure() {
  int analog_value = analogRead(pressure_sensor);
  double pressure = double(analog_value) / 100.0;
  return String(pressure);
}
void setup() {
  // Serial.begin(9600);
  lcd.begin(20,4);
  pinMode(in_1, OUTPUT);
  pinMode(in_2, OUTPUT);
  pinMode(out_1, OUTPUT);
  pinMode(out_2, OUTPUT);
  pinMode(exhaust_1, OUTPUT);
  pinMode(exhaust_2, OUTPUT);
  default_lcd_text(2000);
  close_filter_1();
  close_filter_2();
  // Serial.println("starting");
}
void loop() {
  String pressure = measure_pressure();
  close_filter_2();
  delay(500);
  lcd.begin(20,4);
  open_filter_1();
  lcd.setCursor(0,1);
  lcd.print("Pressure: " + pressure + " atm");
  delay(15000);
  close_filter_1();
  delay(500);
  lcd.begin(20,4);
  open_filter_2();
  lcd.setCursor(0,1);
  lcd.print("Pressure: " + pressure + " atm");
  delay(15000);
}
