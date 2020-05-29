#include <LiquidCrystal.h>
#include <EEPROM.h>
const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define buzzer 10
#define cikis A3
#define giris A2
#define sayacButon A1
#define dakikaButon A0
#define role 11

//float sabit = 1.94330708;//1
//float sabit = 1.97692307;//2
//float sabit = 1.98018292;//3
//float sabit = 1.98761609;//4
//float sabit = 1.98394863;//5
//float sabit = 1.98480243;//6
//float sabit = 2.00461538;//7  
//float sabit = 1.94277108;//8
//float sabit = 1.97777777;//9
//float sabit = 1.95697329;//10
//float sabit = 1.98345864;//11
//float sabit = 1.95331325;//12
//float sabit = 1.94650817;//13
//float sabit = 1.96927803;//14
//float sabit = 1.95884146;//15
//float sabit = 1.92933947;//16
//float sabit = 1.97484276;//17
//float sabit = 1.92769230;//18
//float sabit = 1.95023328;//19
//float sabit = 1.94582043;//20
float sabit = 1.81292984;//21

int switchZamanDeger=50;
long int oncekizaman = 0;
int zaman = 0;
int switchZaman = 0;
int sayacZaman = 0;
int dakikaBtnZaman = 0;
int sayac = 0;
int dakikaayari = 1;
int saniye = 0;
int dakika = 0;
int para = 0;
int sarjyuzde = 0;
int olcum = 0;
int blokeLimit = 5;
bool sayacGir = false;
bool dakikaAyarGir = false;
bool bloke = false;

byte b0[8] = {0b01110, 0b01010, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b11111};
byte b1[8] = {0b01110, 0b01010, 0b10001, 0b10001, 0b10001, 0b11111, 0b11111, 0b11111};
byte b2[8] = {0b01110, 0b01010, 0b10001, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte b3[8] = {0b01110, 0b01110, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte o[] = {B01010,B00000,B01110,B10001,B10001,B10001,B01110,B00000};
byte u[] = {B01010,B00000,B10001,B10001,B10001,B10001,B01110,B00000};

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(cikis, INPUT);
  pinMode(role, OUTPUT);
  pinMode(sayacButon, INPUT_PULLUP);
  pinMode(dakikaButon, INPUT_PULLUP);

  digitalWrite(role, HIGH);

  lcd.begin(16, 2);
  lcd.createChar(0, b0);
  lcd.createChar(1, b1);
  lcd.createChar(2, b2);
  lcd.createChar(3, b3);
  lcd.createChar(4, o);
  lcd.createChar(5, u);
  
  delay(500);
  blokeKontrol();
  dakikaAyarKontrol();
}

void dakikaAyarKontrol() {
  dakikaayari = EEPROM.read(6);
  delay(15);
}
void paraSes() {
  digitalWrite(buzzer, HIGH);
  delay(150);
  digitalWrite(buzzer, LOW);
  delay(75);
  digitalWrite(buzzer, HIGH);
  delay(150);
  digitalWrite(buzzer, LOW);
}

void sayacArtir() {
  sayac = EEPROM.read(4);
  delay(15);
  sayac++;
  EEPROM.write(4, sayac);
  delay(15);
}

void blokeSayacArtir() {
  sayac = EEPROM.read(5);
  delay(15);
  sayac++;
  EEPROM.write(5, sayac);
  delay(15);
}

void blokeKontrol() {
  sayac = EEPROM.read(5);
  delay(15);
  if (sayac >= blokeLimit) {
    bloke = true;
    digitalWrite(role, HIGH);
    para = 0;
    dakika = 0;
    saniye = 0;
    zaman = 2;
  }
  else bloke = false;
}

void blokeEkrani() {
  if (zaman == 3 || zaman == 2) {
    lcd.setCursor(0, 0);
    lcd.print("  Cihaz BLOKE   ");
    lcd.setCursor(0, 1);
    lcd.print("    Edildi!!    ");
  }
}


void beklemeEkrani() {
  if (zaman == 1) {
    lcd.setCursor(0, 0);
    lcd.print("  HOSGELDINIZ  ");
    lcd.setCursor(0, 1);
    lcd.print(dakikaayari);
    lcd.print("dk Mobil Sarj!");
    bataryaOlcum();
  }
  else if (zaman == 1500) {
    lcd.setCursor(0, 0);
    lcd.print("  SARJMATIK     ");
    sarjyuzdeYaz();
    lcd.setCursor(0, 1);
    lcd.print("  SADECE 1TL!   ");
  }
  else if (zaman == 3000)zaman = 0;
}

/*Köpüklü Kahveci
bool sarj=true;
void beklemeEkrani() {
  if (zaman == 1) {
    lcd.setCursor(0, 0);
    lcd.print("HOSGELDINIZ     ");
    lcd.setCursor(0, 1);
    lcd.print("K");
    lcd.write((uint8_t)4);
    lcd.print("P");
    lcd.write((uint8_t)5);
    lcd.print("KL");
    lcd.write((uint8_t)5);
    lcd.print(" Kahveci");
    bataryaOlcum();
    if(sarj){
      sarjyuzdeYaz();
      sarj=false;
    }
    else sarj=true;
  }
  else if (zaman == 1500) {
    lcd.setCursor(0, 0);
    lcd.print(dakikaayari);
    lcd.print("dk Mobil Sarj!");
    lcd.setCursor(0, 1);
    lcd.print("  SADECE 1TL!   ");
  }
  else if (zaman == 3000)zaman = 0;
}*/

//KIPKIRMIZI Cafe
/*bool sarj=true;
void beklemeEkrani() {
  if (zaman == 1) {
    lcd.setCursor(0, 0);
    lcd.print("HOSGELDINIZ     ");
    lcd.setCursor(0, 1);
    lcd.print("KIPKIRMIZI Cafe ");
    bataryaOlcum();
    if(sarj){
      sarjyuzdeYaz();
      sarj=false;
    }
    else sarj=true;
  }
  else if (zaman == 1500) {
    lcd.setCursor(0, 0);
    lcd.print(dakikaayari);
    lcd.print("dk Mobil Sarj!");
    lcd.setCursor(0, 1);
    lcd.print("  SADECE 1TL!   ");
  }
  else if (zaman == 3000)zaman = 0;
}*/

void sayacBtnKontrol() {
  while (digitalRead(sayacButon) == LOW) {
    sayacZaman++;
    if (sayacZaman == 100) {
      sayacGir = true;
      break;
    }
    delay(10);
  }
  sayacZaman = 0;
  if (sayacGir)sayacSifirla();
}

void dakikaAyarBtnKontrol() {
  while (digitalRead(dakikaButon) == LOW) {
    dakikaBtnZaman++;
    if (dakikaBtnZaman == 80) {
      dakikaAyarGir = true;
      break;
    }
    delay(10);
  }
  dakikaBtnZaman = 0;
  if (dakikaAyarGir)dakikaArtir();
}

void dakikaArtir() {
  dakikaayari += 5;
  if (dakikaayari > 60)dakikaayari = 5;
  EEPROM.write(6, dakikaayari);
  delay(15);
  dakikaAyarGir = false;
  lcd.setCursor(0, 0);
  lcd.print("  SARJ SURESI   ");
  lcd.setCursor(0, 1);
  lcd.print("     ");
  lcd.print(dakikaayari);
  lcd.print(" DK      ");
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void sayacSifirla() {
  sayac = EEPROM.read(4);
  delay(15);
  lcd.setCursor(0, 0);
  lcd.print("Para Sayaci:    ");
  lcd.setCursor(12, 0);
  lcd.print(sayac);
  sayac = EEPROM.read(5);
  lcd.setCursor(0, 1);
  lcd.print("Bloke Sayaci:   ");
  lcd.setCursor(13, 1);
  lcd.print(sayac);
  delay(3000);
  sayac = 0;
  lcd.setCursor(0, 0);
  lcd.print("Para Sayaci:    ");
  lcd.setCursor(12, 0);
  lcd.print(sayac);
  lcd.setCursor(0, 1);
  lcd.print("Sayac Sifirlandi");
  EEPROM.write(4, sayac);
  sayacGir = false;
  delay(15);
  EEPROM.write(5, sayac);//Bloke Sayacı.
  bloke = false;
  zaman = 1;
  delay(1000);
}

void switchKontrol() {
  while (digitalRead(2) == LOW) {
    switchZaman++;
    delayMicroseconds(500);
  }
}

void zamanKontrol() {
  if (digitalRead(2) == HIGH && switchZaman != 0) {
    if (switchZaman > switchZamanDeger*2) {
      switchZaman = 0;
      yabanciCisim();
    }
    else {
      switchZaman = 0;
      para++;
      sayacArtir();
      dakika += dakikaayari;
      paraSes();
    }
  }
}

void yabanciCisim() {
  blokeSayacArtir();
  blokeKontrol();
  digitalWrite(buzzer, HIGH);
  lcd.setCursor(0, 0);
  lcd.print(" YABANCI CiSiM  ");
  lcd.setCursor(0, 1);
  lcd.print("   ALGILANDI!!  ");
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.print("Tekrarlandiginda");
  lcd.setCursor(0, 1);
  lcd.print("Chaz Bloke Olack");
  delay(5000);
  digitalWrite(buzzer, LOW);
}

void bataryaOlcum() {
  olcum = analogRead(cikis);
  if (para == 0)sarjyuzde = map(olcum * sabit, 1200, 1300, 0, 20) * 5;
  else sarjyuzde = map(olcum * sabit, 1180, 1280, 0, 20) * 5;
  lcd.setCursor(15, 0);
  if (sarjyuzde < 0)akuBitti();
  else if (sarjyuzde < 15 && sarjyuzde >= 0)lcd.write((uint8_t)0);
  else if (sarjyuzde < 50 && sarjyuzde >= 15)lcd.write((uint8_t)1);
  else if (sarjyuzde < 85 && sarjyuzde >= 50)lcd.write((uint8_t)2);
  else if (sarjyuzde < 100 && sarjyuzde >= 85)lcd.write((uint8_t)3);
  else if (sarjyuzde >= 100){
    lcd.write((uint8_t)3);
    sarjyuzde=100;
  }
}

void akuBitti() {
  para = 0;
  dakika = 0;
  saniye = 0;
  digitalWrite(role, HIGH);
  while (analogRead(cikis) > analogRead(giris)) {
    akuBittiEkran();
  }
}

void akuBittiEkran() {
  lcd.setCursor(0, 0);
  lcd.print(" !! PIL BOS !! ");
  lcd.write((uint8_t)0);
  lcd.setCursor(0, 1);
  lcd.print("Cihazi Sarja Tak");
  digitalWrite(buzzer, HIGH);
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  digitalWrite(buzzer, LOW);
  delay(500);
}

void akuSarjKontrol() {
  while (analogRead(giris) > analogRead(cikis)) {
    olcum = analogRead(cikis);
    sarjyuzde = map(olcum * sabit, 1300, 1420, 0, 20) * 5;
    if (sarjyuzde >= 100) {
      sarjyuzde = 100;
      lcd.setCursor(0, 0);
      lcd.print("    AKU DOLU    ");
      lcd.setCursor(0, 1);
      lcd.print("SARJDAN CIKARIN!");
    }
    else {
      if(sarjyuzde<0)sarjyuzde=0;
      lcd.setCursor(0, 0);
      lcd.print("AKU SARJ OLUYOR!");
      lcd.setCursor(0, 1);
      lcd.print("       %        ");
      lcd.setCursor(8, 1);
      lcd.print(sarjyuzde);
    }
    delay(1000);
  }
}

void sarjyuzdeYaz() {
  if (sarjyuzde > 99)lcd.setCursor(12, 0);
  else lcd.setCursor(13, 0);
  lcd.print("%");
  lcd.print(sarjyuzde);
}

void sarjZaman() {
  if (millis() - oncekizaman > 1000) {
    oncekizaman = millis();
    if (saniye > 0) {
      saniye -= 1;
    }
    else {
      if (dakika == 0) {
        para = 0;
        zaman = 1;
        digitalWrite(role, HIGH);
      }
      else {
        digitalWrite(role, LOW);
        saniye = 59;
        dakika -= 1;
        para = dakika / dakikaayari + 1;
      }
    }
    sarjEkrani();
    bataryaOlcum();
    sureBitiyorKontrol();
  }
}

void sureBitiyorUyariSes() {
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(150);
  digitalWrite(buzzer, LOW);
}

void sureBitiyorKontrol() {
  if (dakika == 0 && saniye == 3)sureBitiyorUyariSes();
  else if (dakika == 0 && saniye == 2)sureBitiyorUyariSes();
  else if (dakika == 0 && saniye == 1)sureBitiyorUyariSes();
  else if (dakika == 0 && saniye == 0 && para != 0) {
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
  }
}
void sarjEkrani() {
  lcd.setCursor(0, 0);
  lcd.print("  SARJ OLUYOR! ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(6, 1);
  if (dakika > 99)lcd.setCursor(5, 1);
  if (dakika < 10)lcd.print("0");
  lcd.print(dakika);
  lcd.setCursor(8, 1);
  lcd.print(":");
  lcd.setCursor(9, 1);
  if (saniye < 10)lcd.print("0");
  lcd.print(saniye);
}

void loop() {
  if (para == 0) {
    beklemeEkrani();
    akuSarjKontrol();
    sayacBtnKontrol();
    dakikaAyarBtnKontrol();
    while (bloke == true) {
      blokeEkrani();
      sayacBtnKontrol();
      zaman = 1;
      delay(1);
    }
  }
  else {
    sarjZaman();
  }
  switchKontrol();
  zamanKontrol();
  zaman++;
  delay(1);
}
