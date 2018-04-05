//#define ECHO_PRINTF
#define START_MSG
//#define STOP_MSG

#define NBDATASEND 3
#define NBBYTE2SEND (2*NBDATASEND)

uint16_t phi1 = 0, phi2 = 0, phi3 = 0;
uint8_t temp;
uint8_t i, j = 0;
char StartMessage[] = "START";
char StopMessage[] = "STOP";
uint8_t byteRead;
uint8_t StartAsked = 0;
uint8_t StopAsked = 0;
unsigned long previous = 0;
int mod_11k = 12; 
int mod_17k = 13; 
uint8_t Header = 174;
uint8_t tab_1[NBBYTE2SEND]={0,0,0,0,0,0};
int16_t data_toSend[NBDATASEND]={0,0,0};

void setup() {
  pinMode(mod_11k,OUTPUT);  
  digitalWrite(mod_11k,LOW);
  pinMode(mod_17k,OUTPUT);  
  digitalWrite(mod_17k,HIGH);
  //Start serial port with Gumstix at 3Mhz
  Serial1.begin(115200);
  Serial.begin(9600);
  delay(100);
  Serial.write("START");

  //Wait for start message
#ifdef START_MSG
  //Waiting START message to begin
  StartAsked = 0;
  while (StartAsked == 0)
  {
    if ((unsigned)Serial1.available() >= strlen(StartMessage))        //?????
    {
      Serial.write("Bytes available");
      // verifiy that the received stream is well the start stream
      for (i = 0; i < strlen(StartMessage); i++)
      {
        byteRead = Serial1.read();
        if ((uint8_t)StartMessage[i] == byteRead)
        {
          StartAsked = 1;
        }
        Serial.println(byteRead);
      }
    }
    delay(1);
  }
  Serial1.write("START");
  Serial.write("START");
#endif

}


void loop()
{
  tick();
}


void tick() {
  if (micros() - previous > 10000)
  {
    previous = micros();
    Codage(data_toSend,tab_1);
    HeaderSendnUInt8_RS232(tab_1,NBBYTE2SEND,Header); 
  }
  else
  {
    data_toSend[0] = analogRead(0);   //phi1 11k
    data_toSend[1] = analogRead(1); //phi2 11k
    data_toSend[2] = analogRead(2);
  }
#ifdef STOP_MSG
  CheckStopMessage();
#endif
}

void Codage(int16_t *d_send, uint8_t *tab_Send)
{
    int i;
    for(i=0; i<NBDATASEND ;i++) 
    {
       d_send[i]=d_send[i]+8192;     
       tab_Send[2*i]= (uint8_t) ((d_send[i] & 127));              //lấy 7 bit đầu
       tab_Send[2*i+1]= (uint8_t) ((d_send[i] & 16256)>>7);       //lấy 7 bit sau
    }
}  

uint8_t HeaderSendnUInt8_RS232(uint8_t *ToSend, uint8_t NbToSend, uint8_t Header)
{
    Serial1.write(&Header,1);         //Header đâu phải pointer??
    return(Serial1.write((const uint8_t*)ToSend, NbToSend));
}

#ifdef STOP_MSG
void CheckStopMessage() {
  while (Serial1.available() <= 1 )
  {

  }
  //if first char of StopMessage
  if (byteRead == (uint8_t)StopMessage[0])
  {
    //supposing STOP asking
    StopAsked = 1;
    // verifiy that the received stream is well the stop stream
    for (i = 1; i < strlen(StopMessage); i++)
    {
      byteRead = Serial1.read();
      if ((uint8_t)StopMessage[i] != byteRead) StopAsked = 0;
    }
    if (StopAsked)
    {
      Serial1.write("STOP");
      setup();
    }
  }
}
#endif
