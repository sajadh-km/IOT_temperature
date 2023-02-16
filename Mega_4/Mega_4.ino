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
int        rp_t = 5;
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
void read_from_esp() 
{
  int wait_esp=0;
  int read =0;
  char rcvd;
  while(!ESP.available()) 
  {
    wait_esp++;
    if(wait_esp>100)
    return;
    delay(1);
  }
  while(ESP.available() && read < 10000)
  {
    rcvd=((char)ESP.read());  
    PC.print(rcvd)  ;
    read++;
    delayMicroseconds(10);
    if(rcvd == 'y')
    delay(2500);
    //resetFunc(); //call reset         
  }  
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
int read_adc()
{
  int i=0;
  int total=0;
  for(i=0; i<100; i++)
  {
    total += analogRead(A14);
    delayMicroseconds(200);
  }
  return(total/100);
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
{ pinMode(9, OUTPUT);
  pinMode(ROW_5, OUTPUT);
  pinMode(ROW_6, OUTPUT);
  pinMode(ROW_8, OUTPUT);
  pinMode(ROW_9, OUTPUT);
  PC.begin(230400);
  ESP.begin(9600);

  PC.print("Mega_4.1\n");  
  delay(5000);
}
void loop() 
{
  int count = 1000;
  float tpr;
  static int count_94 =0;
  static char random=0;
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
          digitalWrite(PULSE_SENSOR_POWER, HIGH);//PC.println("pulse sensor on");
          count_pressure_detected=4;
      }
  }
  if (data_to_send.fsr3 <=28 && data_to_send.fsr4 <=28 && data_to_send.fsr7 <=28 && data_to_send.fsr8 <=28 && count_pressure_detected > 0)
  {
      count_pressure_detected --;
  }
  if(!count_pressure_detected)
  digitalWrite(PULSE_SENSOR_POWER, LOW);
  
  //__________________________________________
  make_data();
  send_data();
  read_from_esp();
  delay(800);    
}
