#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h> // Memasukkan library DS3231

// Inisialisasi DS3231 dan LCD
DS3231 rtc(SDA, SCL); // Prosedur pembacaan I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Konfigurasi buzzer
const int buzzerPin = A2; // Pin untuk buzzer

// Melodi "Selamat Ulang Tahun"
int melody[] = {
  262, 262, 294, 262, 349, 330, // G G A G C B
  262, 262, 294, 262, 392, 349, // G G A G D C
  262, 262, 523, 440, 349, 330, 294, // G G G E C B A
  466, 466, 440, 349, 392, 349 // F F E C D C
};

// Durasi tiap nada: 4 = seperempat ketukan, 8 = seperdelapan ketukan, dll.
int noteDurations[] = {
  4, 4, 4, 4, 4, 2,  // Durasi dari nada-nada baris pertama
  4, 4, 4, 4, 4, 2,  // Baris kedua
  4, 4, 4, 4, 4, 4, 2, // Baris ketiga
  4, 4, 4, 4, 4, 2 // Baris keempat
};

// Fungsi untuk memainkan nada "Selamat Ulang Tahun"
void playHappyBirthday() {
  // Tampilkan pesan "Selamat Ulang Tahun" di LCD
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("HBD YA");
  lcd.setCursor(1, 1);
  lcd.print("Dear");
  delay(1000); // Jeda singkat sebelum mulai memainkan nada

  for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);

    // Jeda antar nada (30% dari durasi nada)
    int pauseBetweenNotes = noteDuration * 1.50;
    delay(pauseBetweenNotes);

    // Matikan buzzer saat ini
    noTone(buzzerPin);
  }

  delay(1000); // Jeda setelah melodi selesai
}

void setup()
{
  // Set komunikasi serial di serial monitor pada kecepatan 115200
  Serial.begin(115200);
  Serial.println("Trial LCD + DS3231 + Buzzer");

  // Prosedur pembacaan RTC DS3231
  rtc.begin();

  // Inisialisasi LCD berukuran 16 kolom dan 2 baris
  lcd.begin();
  lcd.backlight(); // Menyalakan backlight LCD

  // Menampilkan pesan awal di LCD
  lcd.setCursor(0, 0);
  lcd.print("Hai");

  lcd.setCursor(5, 1);
  lcd.print("Dear");

  delay(5000); // Waktu jeda 5 detik
  lcd.clear();

  // Konfigurasi pin buzzer
  pinMode(buzzerPin, OUTPUT);

  // Memainkan melodi "Selamat Ulang Tahun" sekali
  playHappyBirthday();
  delay(500);
  lcd.clear();
}

void loop()
{
  
  // Menampilkan data waktu dan suhu dari RTC di Serial Monitor
  Serial.print(rtc.getDOWStr(1)); // Hari
  Serial.print(" ");

  Serial.print(rtc.getDateStr()); // Tanggal
  Serial.print(" -- ");

  Serial.println(rtc.getTimeStr()); // Waktu
  Serial.print(" -- ");

  Serial.println(rtc.getTemp()); // Suhu

  // Menampilkan data waktu dan suhu di LCD
  lcd.setCursor(0, 0);
  lcd.print(rtc.getDOWStr(1)); // Hari
  lcd.setCursor(3, 0);
  lcd.print(",");

  lcd.setCursor(4, 0);
  lcd.print(rtc.getDateStr()); // Tanggal

  lcd.setCursor(0, 1);
  lcd.print(rtc.getTimeStr()); // Waktu

  lcd.setCursor(10, 1);
  lcd.print(rtc.getTemp()); // Suhu

  lcd.setCursor(14, 1);
  lcd.print(" C ");

  delay(1000); // Jeda 1 detik sebelum update ulang
}
