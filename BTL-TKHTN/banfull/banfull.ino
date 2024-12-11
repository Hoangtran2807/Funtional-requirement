
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>


 
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 4 //chân led xanh
#define LED_R 5 //chân led đỏ
#define BUZZER 2 // chân buzzer
#define lock 7
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cau hinh mfrc522
int Btn = 6;
// Cài đặt bàn phím
const byte ROWS = 4; // Bốn hàng
const byte COLS = 4; // Bốn cột
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {A3, A2, A1, A0}; // kết nối hàng của bàn phím với A3, A2, A1, A0
byte colPins[COLS] = {A7, A6, A5, A4}; // kết nối cột của bàn phím với A7, A6, A5, A4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
 
void setup() 
{
  Serial.begin(9600);   // khởi tạo màn hình serial
  SPI.begin();      //  khởi tạo SPI
    mfrc522.PCD_Init();   // 
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  pinMode(Btn,INPUT);
  pinMode(lock,OUTPUT);
  Serial.println("Place your card on reader...");
  Serial.println();
 



 }
void loop() 
{

if(digitalRead(Btn) == HIGH){
  
    Serial.println("Access Granted");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
   
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    delay(50);
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    digitalWrite(lock,HIGH);
    delay(3000);
    digitalWrite(lock,LOW);
    delay(100);
    digitalWrite(LED_G, LOW);
   
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
  delay(50);
  }
char key = keypad.getKey();
  if (key)
  {
    Serial.print("Key pressed: ");
    Serial.println(key);
    if (key == '3') 
    {  
      Serial.println("Access Granted via Keypad");
      grantAccess();
    } 
    else 
    {
    denyAccess();
    }
  }

  // quét thẻ
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //hiển thị uid lên màn hình
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();


 if (content.substring(1) == "6D DF AE 21") //thay đổi uid của thẻ tuỳ ý
  {
    Serial.println("Access Granted");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
 
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    delay(50);
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    digitalWrite(lock,HIGH);
    delay(3000);
    digitalWrite(lock,LOW);
    delay(100);
    digitalWrite(LED_G, LOW);
   
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    delay(50);
  }

else
 {    
    Serial.println(" Access denied");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 1500);
    delay(500);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
    delay(100);
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 1500);
    delay(500);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
    delay(100);
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 1500);
    delay(500);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
    
  }
 
}

void grantAccess() {
  Serial.println("Access Granted");
  delay(500);
  digitalWrite(LED_G, HIGH); // Bật LED xanh
  tone(BUZZER, 2000);
  delay(100);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 2000);
  delay(100);
  noTone(BUZZER);
  digitalWrite(lock, HIGH); // Mở khóa
  delay(3000); 
  digitalWrite(lock, LOW);  // Đóng khóa
  delay(100);
  digitalWrite(LED_G, LOW); // Tắt LED xanh
  tone(BUZZER, 2000);
  delay(100);
  noTone(BUZZER);
  delay(50);
}

void denyAccess() {
  Serial.println("Access Denied");
  digitalWrite(LED_R, HIGH); // Bật LED đỏ
  tone(BUZZER, 1500);
  delay(500);
  digitalWrite(LED_R, LOW); // Tắt LED đỏ
  noTone(BUZZER);
  delay(100);
  digitalWrite(LED_R, HIGH); // Bật LED đỏ
  tone(BUZZER, 1500);
  delay(500);
  digitalWrite(LED_R, LOW); // Tắt LED đỏ
  noTone(BUZZER);
  delay(100);
  digitalWrite(LED_R, HIGH); // Bật LED đỏ
  tone(BUZZER, 1500);
  delay(500);
  digitalWrite(LED_R, LOW); // Tắt LED đỏ
  noTone(BUZZER);
}