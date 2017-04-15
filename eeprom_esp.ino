#include <EEPROM.h>
#include <ESP8266WiFi.h>

unsigned char length;

char  ssid[]="ARM 32 BIT";
char  pass[]="msp430f5510";
unsigned char ssid_length,pass_length;

char  ssid_eeprom[32];
char  pass_eeprom[64];
unsigned char ssid_eeprom_length, pass_eeprom_length;


void setup() 
{
  EEPROM.begin(100);
  Serial.begin(115200);


  /* Write wifi information to eeprom */
  /* 1 byte ssid length + n bytes ssid + 1 byte pass length + m bytes pass */

  ssid_length = strlen(ssid);
  pass_length = strlen(pass);
  
  EEPROM.write(0,ssid_length);
  for(unsigned char i = 1; i <= ssid_length; i++)
  {
    EEPROM.write(i,*(ssid + i- 1));
  }

  EEPROM.write(ssid_length + 1,pass_length);
  for(unsigned char i = ssid_length + 2; i <= ssid_length + pass_length + 2 ; i++)
  {
    EEPROM.write(i,*(pass + i - ssid_length - 2));
  }
  EEPROM.commit();


  /* Read Wifi information from eeprom */
  ssid_eeprom_length = EEPROM.read(0); 
  for(unsigned char i = 1; i <= ssid_eeprom_length; i++)
  {
   *(ssid_eeprom + i -1)= EEPROM.read(i); 
  }
  
  pass_eeprom_length = EEPROM.read(ssid_eeprom_length + 1);
  for(unsigned char i = ssid_eeprom_length + 2; i <= ssid_eeprom_length + 2 + pass_eeprom_length; i++)
  {
   *(pass_eeprom + i - ssid_eeprom_length - 2)= EEPROM.read(i); 
  }

  Serial.println("");
  Serial.print("SSID: ");
  Serial.write(ssid_eeprom);

  Serial.println("");
  Serial.print("SSID LENGTH: ");
  Serial.print(strlen(ssid_eeprom));
  
  Serial.println("");
  Serial.print("PASS: ");
  Serial.write(pass_eeprom);
  
  Serial.println("");
  Serial.print("PASS LENGTH: ");
  Serial.println(strlen(pass_eeprom));
  
  WiFi.begin(ssid_eeprom, pass_eeprom);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.println(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
 



}
