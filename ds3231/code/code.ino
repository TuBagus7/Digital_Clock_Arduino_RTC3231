#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h> //memasukan library DS3231

DS3231  rtc(SDA, SCL); //prosedur pembacaan I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup()
{
//set komunikasi baut di serial monitor pada kecepatan 115200
Serial.begin(115200);
//menuliskan data di serial monitor
Serial.println("Trial LCD + DS3231");

//prosedur pembacaan RTC DS3231
rtc.begin();

//Inisialisasi LCD berukuran 16 kolom dan 2 baris
lcd.begin();
//menyalakan backlight LCD, jika mematikan dapat diisi dengan nilai "0"
lcd.backlight();

  //setting pertama download program
  // rtc.setDate(29, 9, 2024);   //mensetting tanggal 07 april 2018
  // rtc.setTime(18, 34, 50);     //menset jam 22:00:00
  // rtc.setDOW(7);     //menset hari "Sabtu"

lcd.setCursor(0,0);
lcd.print("nyebarilmu.com"); //pada baris pertama dituliskan nyebarilmu.com

lcd.setCursor(0,1);
lcd.print("  LCD + DS3231  "); //pada baris kedua dituliskan LCD + DS3231

delay(5000); //Waktu jeda
lcd.clear();
} 

void loop()
{
Serial.print(rtc.getDOWStr(1));
Serial.print(" ");
  
Serial.print(rtc.getDateStr());
Serial.print(" -- ");
  
Serial.println(rtc.getTimeStr());
Serial.print(" -- ");
  
Serial.println(rtc.getTemp());

lcd.setCursor(0,0);
lcd.print(rtc.getDOWStr(1)); //prosedur pemanggilan hari
lcd.setCursor(3,0);
lcd.print(",");

lcd.setCursor(4,0);
lcd.print(rtc.getDateStr()); //prosedur pemanggilan tanggal

lcd.setCursor(0,1);
lcd.print(rtc.getTimeStr()); //prosedur pemanggilan waktu

lcd.setCursor(10,1);
lcd.print("t:");

lcd.setCursor(12,1);
lcd.print(rtc.getTemp()); //prosedur pemanggilan suhu

delay (1000);
}