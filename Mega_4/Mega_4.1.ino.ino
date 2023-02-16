#define    PULSE_PIN A12
#define    PC        Serial
#define    ESP       Serial3
#define    COLUMN_7  A0
#define    COLUMN_6  A1
#define    COLUMN_4  A2
#define    COLUMN_3  A3
#define    ROW_9     16
#define    ROW_8     18
#define    ROW_6     20
#define    ROW_5     19
#define    THERMOCOUPLE_1   A14
#define    PULSE_SENSOR_POWER 9
int        rp_t = 20;
int        count_pressure_detected=0;
void(* resetFunc) (void) = 0;//declare reset function at address 0
typedef struct myData 
{
  long int fsr1;
  long int fsr2;
  long int fsr3;
  long int fsr4;
  long int fsr5;
  long int fsr6;
  long int fsr7;
  long int fsr8;
  long int fsr9;
  long int fsr10;
  long int fsr11;
  long int fsr12;
  long int fsr13;
  long int fsr14;
  long int fsr15;
  long int fsr16;
  long int pulse;
  float temperature_1;
  float temperature_2;
}DATAS;

DATAS data_to_send;
void select(int dio_pin)
{
    digitalWrite(ROW_9, LOW);
    digitalWrite(ROW_8, LOW);
    digitalWrite(ROW_6, LOW);
    digitalWrite(ROW_5, LOW);
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
    return(mapped_value) ;
}
void read_FSR()
{
  select(ROW_6);                //16
  data_to_send.fsr1 = read_adc(COLUMN_3);     //A0
  data_to_send.fsr2 = read_adc(COLUMN_4);     //A1
  data_to_send.fsr3 = read_adc(COLUMN_6);     //A2
  data_to_send.fsr4 = read_adc(COLUMN_7);     //A3
  
  select(ROW_5);                //18
  data_to_send.fsr5 = read_adc(COLUMN_3);
  data_to_send.fsr6 = read_adc(COLUMN_4);
  data_to_send.fsr7 = read_adc(COLUMN_6);
  data_to_send.fsr8 = read_adc(COLUMN_7);  

  select(ROW_8);                //20
  data_to_send.fsr9 = read_adc(COLUMN_3);
  data_to_send.fsr10 = read_adc(COLUMN_4);
  data_to_send.fsr11 = read_adc(COLUMN_6);
  data_to_send.fsr12 = read_adc(COLUMN_7);  
  
  select(ROW_9);                 //19
  data_to_send.fsr13 = read_adc(COLUMN_3);
  data_to_send.fsr14 = read_adc(COLUMN_4);
  data_to_send.fsr15 = read_adc(COLUMN_6);
  data_to_send.fsr16 = read_adc(COLUMN_7);  

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
  pinMode(9, OUTPUT);
  pinMode(ROW_5, OUTPUT);
  pinMode(ROW_6, OUTPUT);
  pinMode(ROW_8, OUTPUT);
  pinMode(ROW_9, OUTPUT);
  pinMode(PULSE_SENSOR_POWER, OUTPUT);
  PC.begin(230400);
  ESP.begin(115200);

  PC.print("Mega_4.2\n"); 
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
  if( data_to_send.fsr3 > 28 || data_to_send.fsr4 > 28 || data_to_send.fsr7 > 28 || data_to_send.fsr8 > 28 )
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
  if (data_to_send.fsr3 <=28 && data_to_send.fsr4 <=28 && data_to_send.fsr7 <=28 && data_to_send.fsr8 <=28 && count_pressure_detected > 0)
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
