#define LDR 17
#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
#define AO 14
#define BUZZER 7
#define BUTTON1 15
#define BUTTON2 16

int VLDR;
int VLED;
int ADJUST;
int BIIN;

void setup() 
{
  Serial.begin(115200);
  pinMode(LDR, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
}

int CONV()
{ 
  ADJUST = (15*(VLDR-64)/(8126));

  return ADJUST;
}

int BIINARY(int DECIM)
{
  int BIIN = 0;    
  int REM;
  int PROD = 1;

  while(DECIM !=0)
  {
    REM = DECIM % 2;
    BIIN = BIIN +(REM*PROD);
    DECIM = DECIM/2;
    PROD *=10;
  }
  return BIIN;
}

void BLINK(int BIINARY)
{  
  const int SPLITTING1 = BIINARY/1000 % 10;  
  const int SPLITTING2 = BIINARY/100 % 10;
  const int SPLITTING3 = BIINARY/10 % 10;
  const int SPLITING4 = BIINARY % 10;
  if(SPLITTING1 == 1)
  {
    digitalWrite(LED1, HIGH);
  }
  if(SPLITTING2 == 1)
  {
    digitalWrite(LED2, HIGH);
  }
  if(SPLITTING3 == 1)
  {
    digitalWrite(LED3, HIGH);
  }
  if(SPLITING4 == 1)
  {
    digitalWrite(LED4, HIGH);
  }
}

void BUZZERFREQ(int BIINARYR)
{  
  if(BIINARYR <= 100)
  { 
    tone(BUZZER,294,300);
  }
  else
  {
    tone(BUZZER, 1175, 300);
  }
}

void LISTBIIN(int BIINARY, int POS, int *LIST){  
  LIST[POS] = BIINARY;
}

int LIST[100];  
int POS = 0; 
void REM(int *LIST1){  
  int BUTTONVAL = digitalRead(BUTTON2);
  if(BUTTONVAL == 0){  
    for(int i; i < POS; i ++){  
      
    BLINK(LIST1[i]);
    delay(500);

    BUZZERFREQ(LIST1[i]);
    delay(500);

    }
    POS = 0;
  }
}

void loop() {
  int BUTTONVAL2 = digitalRead(BUTTON1);
  if(BUTTONVAL2 == 0){  
    VLDR = analogRead(AO);

    CONV();  

    BLINK(BIINARY(ADJUST));  
    delay(500);

    LISTBIIN(BIINARY(ADJUST), POS, LIST);  
    POS +=1;

  }

  digitalWrite(LED1, LOW);  
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  REM(LIST);   
}
