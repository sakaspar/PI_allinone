#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <dummy.h>




#include <SPI.h> //library responsible for communicating of SPI bus
#define SS_PIN    21
#define RST_PIN   22
#define SIZE_BUFFER     18
#define MAX_SIZE_BLOCK  16
#define greenPin     12
#define redPin       32
byte nuidPICC[4];
//used in authentication
MFRC522::MIFARE_Key key;
//authentication return status code
MFRC522::StatusCode status;
// Defined pins to module RC522
MFRC522 rfid(SS_PIN, RST_PIN); 
void setup() 
{

 
 
  // Tableau contentent l'ID

  
  Serial.begin(9600);
  // Init SPI bus
  SPI.begin(); 

  // Init MFRC522 
  rfid.PCD_Init(); 
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  // Init MFRC522

  Serial.println("Approach your reader card...");
  Serial.println();

}
 int menu()
{
  Serial.println(F("\nChoose an option:"));
  Serial.println(F("0 - Reading data"));
  Serial.println(F("1 - Writing data\n"));

  //waits while the user does not start data
  while(!Serial.available()){};
  
  //retrieves the chosen option
  int op = (int)Serial.read();
  
  //remove all characters after option (as \n per example)
  while(Serial.available()) {
    if(Serial.read() == '\n') break; 
    Serial.read();
  }
  return (op-48);//subtract 48 from read value, 48 is the zero from ascii table
}

  
  
  
  void loop() 
{
 



  


  
  Serial.println("hazebi");
  // Initialisé la boucle si aucun badge n'est présent 
  if ( !rfid.PICC_IsNewCardPresent())
  {
    digitalWrite(redPin, HIGH);
    delay(1000);
    digitalWrite(redPin, LOW);
    
    return;
  }
  // Vérifier la présence d'un nouveau badge 
  if ( !rfid.PICC_ReadCardSerial())
    return;

  // Enregistrer l'ID du badge (4 octets) 
  for (byte i = 0; i < 4; i++) 
  {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  
  // Affichage de l'ID 
  Serial.println("Un badge est détecté");
  Serial.println(" L'UID du tag est:");
  for (byte i = 0; i < 4; i++) 
  {
    Serial.print(nuidPICC[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // Stop encryption on PCD
  
 

}
