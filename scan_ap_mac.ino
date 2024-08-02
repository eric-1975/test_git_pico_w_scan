// Simple WiFi network scanner application
// Released to the public   domain in 2022 by Earle F. Philhower, III
#include <WiFi.h>


/*------------------------------------------------------------------------------
	Serial_USB		USB CDC = VCP (for Debug)

	Serial_RS485	連接 TTL to RS485, 再接到RS485 interface sensor
	Serial_Ext		連接「延伸擴充用」
------------------------------------------------------------------------------*/
#define   Serial_USB      Serial          // USB	接電腦Debug		（沒實體port，使用USB VCP）

void setup()   
{
    Serial_USB.begin(115200);
}

const char* macToString(uint8_t mac[6])   
{
    static char s[20];
    sprintf(s, "%02X:%02X:%02X:%02X:%02X:%02X",   mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return s;
}
 
const   char* encToString(uint8_t enc) 
{
    switch (enc) 
    {
      case ENC_TYPE_NONE:   
        return "NONE";

      case ENC_TYPE_TKIP: 
        return "WPA";

      case ENC_TYPE_CCMP:   
        return "WPA2";

      case ENC_TYPE_AUTO: 
        return "AUTO";
    }

    return   "UNKN";
} 

void loop() 
{
    delay(5000);

    Serial_USB.printf("Beginning   scan at %d\n", millis());
    auto cnt = WiFi.scanNetworks();
    if (!cnt)   
    {
        Serial_USB.printf("No networks found\n");
    }
    else 
    {
        Serial_USB.printf("Found %d networks\n\n", cnt);
        Serial_USB.printf("%32s   %5s %17s %2s %4s\n", "SSID", "ENC", "BSSID        ", "CH", "RSSI");
         for (auto i = 0; i < cnt; i++) 
         {
            uint8_t bssid[6];
            WiFi.BSSID(i,   bssid);
            Serial_USB.printf("%32s %5s %17s %2d %4d\n", WiFi.SSID(i),   encToString(WiFi.encryptionType(i)), macToString(bssid), WiFi.channel(i), WiFi.RSSI(i));
         }
    }
    Serial_USB.printf("\n--- Sleeping ---\n\n\n");

    delay(5000);
}
