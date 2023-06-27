#define    PULSE_PIN A12
#define    PC        Serial
#define    ESP       Serial3
#define    COLUMN_1  A0
#define    COLUMN_2  A1
#define    COLUMN_3  A2
#define    COLUMN_4  A3
//changing from here
#define    COLUMN_5  A4
#define    COLUMN_6  A5
#define    COLUMN_7  A6
#define    COLUMN_8  A7
#define    COLUMN_9  A8
#define    COLUMN_10 A9
//changing from here
#define    ROW_1     7
#define    ROW_2     6
#define    ROW_3     5
#define    ROW_4     4
#define    ROW_5     3
#define    ROW_6     2
#define    ROW_7     16
#define    ROW_8     17
#define    ROW_9     18
#define    ROW_10    19
#define    THERMOCOUPLE_1   A14
#define    PULSE_SENSOR_POWER 9
int        rp_t = 20;
int        count_pressure_detected=0;
void(* resetFunc) (void) = 0;//declare reset function at address 0
typedef struct myData 
{
  short int fsr[101];
  short int pulse;
  float temperature_1;
  float temperature_2;
}DATAS;

DATAS data_to_send;
void select(int dio_pin)
{
    digitalWrite(ROW_1, LOW);
    digitalWrite(ROW_2, LOW);
    digitalWrite(ROW_3, LOW);
    digitalWrite(ROW_4, LOW);
    digitalWrite(ROW_5, LOW);
    digitalWrite(ROW_6, LOW);
    digitalWrite(ROW_7, LOW);
    digitalWrite(ROW_8, LOW);
    digitalWrite(ROW_9, LOW);
    digitalWrite(ROW_10, LOW);

    digitalWrite(dio_pin, HIGH);
    delay(1);
}
int read_adc(int pin)
{
    long int    total = 0;
    int         i     = 0;
    int         mapped_value = 0;

    for(i=0; i<50; i++)
    {
        total += analogRead(pin); 
        delayMicroseconds(200);
    }
    total= total/50;
    mapped_value = map(total,0,1023,28,179);
    if(mapped_value < 60)
    mapped_value = 28;
    return(mapped_value) ;
}
void read_FSR()
{
  select(ROW_1);                //16
  data_to_send.fsr[1]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[2]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[3]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[4]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[5]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[6]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[7]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[8]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[9]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[10]=read_adc(COLUMN_10);    //A9
  
  select(ROW_2);                //16
  data_to_send.fsr[11]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[12]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[13]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[14]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[15]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[16]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[17]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[18]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[19]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[20]= read_adc(COLUMN_10);    //A9
  
  
  select(ROW_3);                //16
  data_to_send.fsr[21]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[22]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[23]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[24]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[25]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[26]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[27]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[28]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[29]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[30]= read_adc(COLUMN_10);    //A9

  select(ROW_4);                //16
  data_to_send.fsr[31]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[32]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[33]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[34]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[35]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[36]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[37]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[38]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[39]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[40]= read_adc(COLUMN_10);    //A9

  select(ROW_5);                //16
  data_to_send.fsr[41]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[42]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[43]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[44]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[45]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[46]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[47]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[48]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[49]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[50]= read_adc(COLUMN_10);    //A9
  
  select(ROW_6);                //16
  data_to_send.fsr[51]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[52]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[53]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[54]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[55]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[56]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[57]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[58]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[59]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[60]= read_adc(COLUMN_10);    //A9
  
   select(ROW_7);                //16
  data_to_send.fsr[61]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[62]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[63]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[64]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[65]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[66]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[67]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[68]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[69]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[70]= read_adc(COLUMN_10);    //A9
  
  select(ROW_8);                //16
  data_to_send.fsr[71]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[72]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[73]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[74]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[75]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[76]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[77]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[78]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[79]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[80]= read_adc(COLUMN_10);    //A9

  select(ROW_9);                //16
  data_to_send.fsr[81]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[82]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[83]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[84]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[85]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[86]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[87]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[88]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[89]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[90]= read_adc(COLUMN_10);    //A9
  
  select(ROW_10);                //16
  data_to_send.fsr[91]= read_adc(COLUMN_1);     //A0
  data_to_send.fsr[92]= read_adc(COLUMN_2);     //A1
  data_to_send.fsr[93]= read_adc(COLUMN_3);     //A2
  data_to_send.fsr[94]= read_adc(COLUMN_4);     //A3
  data_to_send.fsr[95]= read_adc(COLUMN_5);     //A4
  data_to_send.fsr[96]= read_adc(COLUMN_6);     //A5
  data_to_send.fsr[97]= read_adc(COLUMN_7);     //A6
  data_to_send.fsr[98]= read_adc(COLUMN_8);     //A7
  data_to_send.fsr[99]= read_adc(COLUMN_9);     //A8
  data_to_send.fsr[100]=read_adc(COLUMN_10);    //A9
  
}
int read_from_esp() 
{
  int flag=0;
  int read =1000;
  char rcvd;
  while(!ESP.available()) ;
  while(read)
  {
    read--;
    if(ESP.available())
    {
      rcvd=((char)ESP.read());  
      if(rcvd =='t' || rcvd =='l')
      flag=1;    
      PC.print(rcvd)  ;     
    }
    delayMicroseconds(10);
  }  
  return flag;
}
void make_data()
{
  if(data_to_send.temperature_1 > 120 || data_to_send.temperature_1 < 60)
  data_to_send.temperature_1 = 0;  
}
float tem_cal()
{
  int i;
  long int val=0;
  static float temp = 76;
  float tem =0;
  delay(5);
  for(i =0; i < 100 ; i++)
  {
     val += analogRead(A14);
     delayMicroseconds(200);
  }   
  val= val/100;  
  //tem = 81 + ((val- 310)/5.7865);
  tem = 81 + ((val- 276)/7.6);
  for(i =0; i<50; i ++)
  {
    if(tem > temp)
    temp += 0.1;
    if(tem < temp)
    temp -= 0.1;
  }
  return temp;
}
int threshold()
{
  int i;
  unsigned long int s_value=0;
  for(i=0;i<1000;i++)
  {
      s_value = s_value+analogRead(PULSE_PIN);
      delay(1);
  } 
  return(s_value/1000);
}
int pulse_adc()
{
  int i=0;
  int sensorValue=0;
  for(i=0;i<50;i++)
  {
      sensorValue = sensorValue+analogRead(PULSE_PIN);
      delayMicroseconds(100);
  } 
  //PC.println(sensorValue/50); 
  return(sensorValue/50);//this is one sample
}
int get_pulse()
{
    int pulse_high_flag=0;
    static  unsigned long old_t=0;
    static unsigned long current_t=0;
    int pulse=0;
    int val_1=0;
    int thr;
    thr=threshold();
    int pulse_upper=thr+1;//510;
    int pulse_lower=thr-1;//509;
    unsigned long count=0;
       
  while(val_1<=pulse_upper)
  {
      val_1=pulse_adc();
      count++;
      if(count > 1000)
      return 0;
      //delayMicroseconds(10);
  }
  old_t=millis();
  count =0;
  while(val_1>=pulse_lower)
  {
      val_1=pulse_adc();
      count++;
      if(count>1000)
      return 0;
      //delayMicroseconds(10);
  }
  count =0;
  while(val_1<=pulse_upper)
  {     
        val_1=pulse_adc();
        count++;
        if(count>1000)
        return 0;
        //delayMicroseconds(10);
  }
  current_t=millis();
  pulse=(60000)/(current_t - old_t);
  if(pulse>60 &&pulse<140)
  return(pulse);
  else
  return(0);
}
void send_data()
{
  
    if(1)//!ESP.available())
    {
      ESP.write((uint8_t*)&data_to_send, sizeof(myData));
      ESP.flush();
    }
    else
    PC.print("port busy\n");
}
void setup() 
{ 
  pinMode(ROW_1, OUTPUT);
  pinMode(ROW_2, OUTPUT);
  pinMode(ROW_3, OUTPUT);
  pinMode(ROW_4, OUTPUT);
  pinMode(ROW_5, OUTPUT);
  pinMode(ROW_6, OUTPUT);
  pinMode(ROW_7, OUTPUT);
  pinMode(ROW_8, OUTPUT);
  pinMode(ROW_9, OUTPUT);
  pinMode(ROW_10, OUTPUT);
  pinMode(PULSE_SENSOR_POWER, OUTPUT);
  PC.begin(230400);
  ESP.begin(115200);

  PC.print("velostat_arduino_Mega_4.2\n"); 
  //digitalWrite(PULSE_SENSOR_POWER, HIGH);
  //PC.print(threshold()); 
  delay(5000);
}
void loop() 
{
  int count = 1000;
  float tpr;
  static int count_94 =0;
  static char random=0;
  int current_pulse=0;
  static int pulse_static= 92;
  read_FSR();
  
  data_to_send.temperature_1 = tem_cal();
  if(data_to_send.temperature_1 > 96.2)
  data_to_send.temperature_1 = 96.2; 
  else if(data_to_send.temperature_1 < 78) 
  data_to_send.temperature_1 =78; 
  if( data_to_send.fsr[3] > 28 || data_to_send.fsr[4] > 28 || data_to_send.fsr[7] > 28 || data_to_send.fsr[8] > 28 )
  {
      count_pressure_detected ++;  
      if(count_pressure_detected>4)
      {
          digitalWrite(PULSE_SENSOR_POWER, HIGH);
          //PC.println("pulse sensor on");
          if(rp_t==1)
          {
            current_pulse=get_pulse();
            if(current_pulse> data_to_send.pulse)
            pulse_static++;
            if(current_pulse < data_to_send.pulse)
            pulse_static--;
            if(current_pulse> data_to_send.pulse)
            pulse_static++;
            if(current_pulse < data_to_send.pulse)
            pulse_static--;
            
            PC.println(current_pulse);
          }  
          count_pressure_detected=4;
          data_to_send.pulse=pulse_static;
          //if(!current_pulse)
          //data_to_send.pulse=0;
      }
  }
  if (data_to_send.fsr[3] <=28 && data_to_send.fsr[4] <=28 && data_to_send.fsr[7] <=28 && data_to_send.fsr[8] <=28 && count_pressure_detected > 0)
  {
      count_pressure_detected --;
  }
  if(!count_pressure_detected)
  {
    digitalWrite(PULSE_SENSOR_POWER, LOW);
    data_to_send.pulse=0;
  }
  
  //__________________________________________
  
  make_data();
  PC.println("");
  read_from_esp();
  if(1)//(read_from_esp())
  {
    delay(150);
    send_data();
  }
  rp_t--;
  if(!rp_t)    
  {
    rp_t=15;

  }
      
  //delay(2);    //700 is good
}
