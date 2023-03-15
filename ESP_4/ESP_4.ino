
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define MY_IP "http://73ad2f2f-9cb1-488c-b91c-a54cf53f6e80.mock.pstmn.io"
#define IP_2  "http://4.227.240.135:552/SaveVetMatReading"

#ifndef STASSID
#define STASSID "pet_pat"
#define STAPSK "12345678"
#endif
char       payload[9000];



typedef struct myData 
{
  int fsr[101];
  int pulse;
  float temperature_1;
  float temperature_2;
}DATAS;

DATAS raw_data;
int faulty_structure_detected=0;
void make_JSON()
{
  int itr;
  if(raw_data.fsr[100] > 179 || raw_data.fsr[100] <28)
  {
      memset(&raw_data, 0x00, sizeof(raw_data));
      faulty_structure_detected=1;
      return;
  }
  else
  {
    faulty_structure_detected=0;
  }

  char  num[10];
  short int loc_x;
  short int loc_y;
  memset(payload, 0x00, sizeof(payload));
  strcat(payload, "[{\"animalName\": \"Not available\",\"age\":0,");
  strcat(payload, "\"pressureSensors\":[");
  for(itr = 1; itr < 101; itr++)
  {
      loc_y = (itr-1) /10;
      loc_x = (itr-1) %10;

      strcat(payload, "{");
      strcat(payload, "\"sensorLocationX\": ");
      sprintf(num, "%d",loc_x);  //3
      strcat(payload,  num);
      strcat(payload,",\"sensorLocationY\": ");
      sprintf(num, "%d",loc_y);  //5
      strcat(payload,  num);
      strcat(payload,",");
      strcat(payload, "\"sensorStatus\": true,");
      strcat(payload, "\"pressureValue\": ");
      sprintf(num, "%d",raw_data.fsr[itr]);  //C1
      strcat(payload,  num);
      strcat(payload, "}");
      if(itr < 100)
      strcat(payload, ","  );
  }
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
