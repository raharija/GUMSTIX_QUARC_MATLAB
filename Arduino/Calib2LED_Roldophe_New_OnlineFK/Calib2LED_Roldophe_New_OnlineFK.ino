//#define ECHO_PRINTF
#define START_MSG
//#define STOP_MSG

#define NBDATASEND 6
#define NBBYTE2SEND (2*NBDATASEND)

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
uint8_t tab_1[NBBYTE2SEND]={0,0,0,0,0,0,0,0,0,0,0,0};
int16_t data_toSend[NBDATASEND]={0,0,0,0,0,0};

float P1[4];float P2[4];float P3[4]; float P4[4];float P5[4];float P6[4];
float xprec1[2];float xprec2[2];float xprec3[2];float xprec4[2];float xprec5[2];float xprec6[2];
float *sol1;float *sol2;float *sol3; float *sol4;float *sol5;float *sol6;
float Te;
float Tbeg;

void setup() {
  pinMode(mod_11k,OUTPUT);  
  pinMode(mod_17k,OUTPUT);
  digitalWrite(mod_11k,LOW);
  digitalWrite(mod_17k,LOW);
  //Start serial port with Gumstix 
  Serial1.begin(115200);

float qkf = 0.02;
//Initialize KF
 P1[0] = qkf; P1[1] =0; P1[2] =0; P1[3] = qkf;
 P2[0] = qkf; P2[1] =0; P2[2] =0; P2[3] = qkf;
 P3[0] = qkf; P3[1] =0; P3[2] =0; P3[3] = qkf;
 P4[0] = qkf; P4[1] =0; P4[2] =0; P4[3] = qkf;
 P5[0] = qkf; P5[1] =0; P5[2] =0; P5[3] = qkf;
 P6[0] = qkf; P6[1] =0; P6[2] =0; P6[3] = qkf;
 xprec1[0] =0; xprec1[1] =0;
 xprec2[0] =0; xprec2[1] =0;
 xprec3[0] =0; xprec3[1] =0;
 xprec4[0] =0; xprec4[1] =0;
 xprec5[0] =0; xprec5[1] =0;
 xprec6[0] =0; xprec6[1] =0;

  //Wait for start message
#ifdef START_MSG
  //Waiting START message to begin
  StartAsked = 0;
  while (StartAsked == 0)
  {
    if (Serial1.available() >= strlen(StartMessage))        //?????
    {
      //Serial.write("Bytes available");
      // verifiy that the received stream is well the start stream
      for (i = 0; i < strlen(StartMessage); i++)
      {
        byteRead = Serial1.read();
        if ((uint8_t)StartMessage[i] == byteRead)
        {
          StartAsked = 1;
        }
       // Serial.println(byteRead);
      }
    }
    delay(1);
  }
  Serial1.write("START");
  //Serial.write("START");
#endif

//KF first time
    Tbeg = millis();
    digitalWrite(mod_11k,HIGH);
    delayMicroseconds(3800);
    data_toSend[0] = analogRead(0);   //phi1 11k
    data_toSend[1] = analogRead(1); //phi2 11k
    data_toSend[2] = analogRead(2);
    digitalWrite(mod_11k,LOW);
    delayMicroseconds(200);
    digitalWrite(mod_17k,HIGH);
    delayMicroseconds(3800);
    data_toSend[3] = analogRead(0);
    data_toSend[4] = analogRead(1);
    data_toSend[5] = analogRead(2);
    digitalWrite(mod_17k,LOW);
    delayMicroseconds(200);
    xprec1[0] = data_toSend[0];
    xprec2[0] = data_toSend[1]; 
    xprec3[0] = data_toSend[2];
    xprec4[0] = data_toSend[3];
    xprec5[0] = data_toSend[4]; 
    xprec6[0] = data_toSend[5];

    // theo như matlab thì ko can filter chỗ này
    Te = (millis() - Tbeg)/1000;
    sol1 = Fkalman(xprec1,data_toSend[0],P1,Te);
    sol2 = Fkalman(xprec2,data_toSend[1],P2,Te);
    sol3 = Fkalman(xprec3,data_toSend[2],P3,Te);
    sol4 = Fkalman(xprec4,data_toSend[3],P4,Te);
    sol5 = Fkalman(xprec5,data_toSend[4],P5,Te);
    sol6 = Fkalman(xprec6,data_toSend[5],P6,Te);
    Tbeg= millis();
}


void loop()
{
    tick();
}


void tick() {
    //Previous value for filtering
    P1[0] =sol1[2]; P1[1] =sol1[3]; P1[2] =sol1[4]; P1[3] =sol1[5];
    P2[0] =sol2[2]; P2[1] =sol2[3]; P2[2] =sol2[4]; P2[3] =sol2[5];
    P3[0] =sol3[2]; P3[1] =sol3[3]; P3[2] =sol3[4]; P3[3] =sol3[5];
    P4[0] =sol4[2]; P4[1] =sol4[3]; P4[2] =sol4[4]; P4[3] =sol4[5];
    P5[0] =sol5[2]; P5[1] =sol5[3]; P5[2] =sol5[4]; P5[3] =sol5[5];
    P6[0] =sol6[2]; P6[1] =sol6[3]; P6[2] =sol6[4]; P6[3] =sol6[5];
    xprec1[0] =sol1[0]; xprec1[1] =sol1[1];
    xprec2[0] =sol2[0]; xprec2[1] =sol2[1];
    xprec3[0] =sol3[0]; xprec3[1] =sol3[1];
    xprec4[0] =sol4[0]; xprec4[1] =sol4[1];
    xprec5[0] =sol5[0]; xprec5[1] =sol5[1];
    xprec6[0] =sol6[0]; xprec6[1] =sol6[1];
    free(sol1);                                        // Libération de l'espace de stockage des solutions
    free(sol2);
    free(sol3);
    free(sol4);                                        // Libération de l'espace de stockage des solutions
    free(sol5);
    free(sol6);

    //Get data
    digitalWrite(mod_11k,HIGH);
    delayMicroseconds(3800);
    data_toSend[0] = analogRead(0);   //phi1 11k
    data_toSend[1] = analogRead(1); //phi2 11k
    data_toSend[2] = analogRead(2);
    digitalWrite(mod_11k,LOW);
    delayMicroseconds(200);
    digitalWrite(mod_17k,HIGH);
    delayMicroseconds(3800);
    data_toSend[3] = analogRead(0);
    data_toSend[4] = analogRead(1);
    data_toSend[5] = analogRead(2);
    digitalWrite(mod_17k,LOW);
    delayMicroseconds(200);
    Te = (millis() - Tbeg)/1000;
    
    //Filter
    sol1 = Fkalman(xprec1,data_toSend[0],P1,Te);           // Filtrage des mesures led1
    sol2 = Fkalman(xprec2,data_toSend[1],P2,Te);
    sol3 = Fkalman(xprec3,data_toSend[2],P3,Te);
    sol4 = Fkalman(xprec4,data_toSend[3],P4,Te);           // Filtrage des mesures led2
    sol5 = Fkalman(xprec5,data_toSend[4],P5,Te);
    sol6 = Fkalman(xprec6,data_toSend[5],P6,Te);
    Tbeg= millis();
    
    data_toSend[0] = sol1[0];
    data_toSend[1] = sol2[0];
    data_toSend[2] = sol3[0];
    data_toSend[3] = sol4[0];
    data_toSend[4] = sol5[0];
    data_toSend[5] = sol6[0];

    //Use Processing
    
    
    //Send data MATLAB
    Codage(data_toSend,tab_1);
    HeaderSendnUInt8_RS232(tab_1,NBBYTE2SEND,Header); 
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

float *Fkalman(float xprec[2],float ymes,float P[4],float Te){ 
                     // Filtre proprement dit  
    float *sol = NULL ;
    sol = (float*) malloc (sizeof(float) * 6);
    float xpred[2];
    float Ppred[4] ;
    float Kf[2] ;
    float q = 0.02;
    int r = 15;

    //x prediction
    xpred[0] = xprec[0] + Te*xprec[1];
    xpred[1] = xprec[1]; 

    //P_pred = F.P.F'+Q
    Ppred[0] = q + P[0]+ Te*(P[2] +P[1]+Te*P[3]);
    Ppred[1] = P[1] + Te*P[3];
    Ppred[2] = P[2] + Te*P[3] ;
    Ppred[3] = q+ P[3];

    //Kf = (P_pred.C').inv(C.P_pred.C'+R)
    Kf[0]  = (Ppred[0]/(r+Ppred[0]));
    Kf[1]  = (Ppred[2]/(r+Ppred[0]));

    //X_est  
    sol[0] = xpred[0] + Kf[0]*(ymes-xpred[0]);
    sol[1] = xprec[1] + Kf[1]*(ymes-xprec[0]);

    //P_est = (I-Kf*C)*P_pred
    sol[2] = Ppred[0]*(1-Kf[0]);
    sol[3] = Ppred[1]*(1-Kf[0]);
    sol[4] = -Kf[1]*Ppred[0]+Ppred[2];
    sol[5] = -Kf[1]*Ppred[1]+Ppred[3];
    return sol;
  }
