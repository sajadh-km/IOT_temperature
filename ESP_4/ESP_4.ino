
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define MY_IP "http://73ad2f2f-9cb1-488c-b91c-a54cf53f6e80.mock.pstmn.io"
#define IP_2  "http://4.227.240.135:552/SaveVetMatReading"

#ifndef STASSID
#define STASSID "pet_pat"
#define STAPSK "12345678"
#endif
char       payload[3000];



typedef struct myData 
{
  int fsr1;
  int fsr2;
  int fsr3;
  int fsr4;
  int fsr5;
  int fsr6;
  int fsr7;
  int fsr8;
  int fsr9;
  int fsr10;
  int fsr11;
  int fsr12;
  int fsr13;
  int fsr14;
  int fsr15;
  int fsr16;
  int pulse;
  float temperature_1;
  float temperature_2;
}DATAS;

DATAS raw_data;
int faulty_structure_detected=0;
void make_JSON()
{
  if(raw_data.fsr16 > 179 || raw_data.fsr16 <28)
  {
      memset(&raw_data, 0x00, sizeof(myData));
      //Serial.print("structure faulty");
      //delay(100);//ESP.restart();
      faulty_structure_detected=1;
      return;
  }
  else
  {
    faulty_structure_detected=0;
  }
  
 char  num[10];
  memset(payload, 0x00, 370);
  strcat(payload, "[{\"animalName\": \"Not available\",\"age\":0,");
  
  strcat(payload, "\"pressureSensors\":[");
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 3,\"sensorLocationY\": 5,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr1);  //C1
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 4,\"sensorLocationY\":5,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr2);  //C2
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 6,\"sensorLocationY\":5,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr3);  //C3
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 7,\"sensorLocationY\":5,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr4); //C4
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 3,\"sensorLocationY\":6,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr5);  //D1
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 4,\"sensorLocationY\":6,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr6);  //D2
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 6,\"sensorLocationY\":6,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr7);  //D3
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 7,\"sensorLocationY\":6,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr8);  //D4
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 3,\"sensorLocationY\":8,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr9);  //B1
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 4,\"sensorLocationY\":8,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr10);  //B2
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 6,\"sensorLocationY\":8,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr11);  //B3
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 7,\"sensorLocationY\":8,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr12);   //B4
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 3,\"sensorLocationY\":9,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr13);  //A1
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 4,\"sensorLocationY\":9,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr14);  //A2
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 6,\"sensorLocationY\":9,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr15);  //A3
  strcat(payload,  num);
  strcat(payload, "}");
  strcat(payload, ","  );
  
  
  
  strcat(payload, "{");
  strcat(payload, "\"sensorLocationX\": 7,\"sensorLocationY\":9,");
  strcat(payload, "\"sensorStatus\": true,");
  strcat(payload, "\"pressureValue\": ");
  sprintf(num, "%d",raw_data.fsr16);  //A4
  strcat(payload,  num);
  strcat(payload, "}");  
  
  
  strcat(payload, "]," );

  strcat(payload, "\"temperatureSensors\":[{");
  strcat(payload, "\"sensorLocationX\": 5,\"sensorLocationY\":6,");
  strcat(payload, "\"temperature\":");
  sprintf(num, "%0.1f", raw_data.temperature_1);
  strcat(payload, num );
  strcat(payload, ","  );
  strcat(payload, "\"minTemperature\":");
  sprintf(num, "%d", 80);
  strcat(payload, num);
  strcat(payload, ",");
  strcat(payload, "\"maxTemperature\":");
  sprintf(num, "%d", 100);
  strcat(payload, num);
  strcat(payload, "}]");
  
  strcat(payload,  ","  );
  
  strcat(payload, "\"pulseSensors\":[{");
  strcat(payload, "\"sensorLocationX\": 5,\"sensorLocationY\":5,");
  strcat(payload, "\"pulse\":");
  sprintf(num, "%d", raw_data.pulse);
  strcat(payload, num) ;
  strcat(payload,  ","  );
  strcat(payload, "\"minPulse\":");
  strcat(payload, "90");
  strcat(payload,  ",");
  strcat(payload, "\"maxPulse\":");
  strcat(payload, "94");
  strcat(payload, "}]");
  

  strcat(payload, "}]");
 }


int parse_data()
{  
    Serial.readBytes((uint8_t*)&raw_data, sizeof(myData));
    return 0;
}



void setup() 
{

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("ESP_3");

  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{

  if ((WiFi.status() == WL_CONNECTED)) 
  {
    WiFiClient client;
    HTTPClient http;
    while(Serial.available() == 0);
    parse_data();   
    make_JSON();
    // configure traged server and url
    http.begin(client, IP_2);  // HTTP
    http.addHeader("Content-Type", "application/json");
    // start connection and send HTTP header and body
    int httpCode = http.POST(payload);
    // httpCode will be negative on error
    if (httpCode > 0) 
    {
      Serial.print("sent");
    } else {
      //Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      Serial.print("fail");
    }

    http.end();    
       
  }

}
