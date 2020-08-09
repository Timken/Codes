/*
 * IRremote: VIRE
 * TSOP : 39238 (3v)
 * Board : Arduino Pro mini (ATmega328-3.3v-8Mhz)
 * Created by : Timken George
 *---------------------------------------------------
 * Connections :
 *  IR data pin -->  12 
 *  LED pins --> 2 to 11
 *  Indicator led pins [blinking]  --> 10 & 11
 */

#include <IRremote.h>

#define PRESSED 4294967295
#define PWR 33441975
#define MODE 33446055
#define MUTE 33454215
#define PLAY 33456255
#define PREW 33439935
#define FORW 33472575
#define EQ 33431775
#define VOL_DEC 33464415
#define VOL_INC 33448095
#define ZERO 33480735
#define RPT 33427695
#define U/SD 33460335
#define ONE 33444015
#define TWO 33478695
#define THREE 33486855
#define FOUR 33435855
#define FIVE 33468495
#define SIX 33452175
#define SEVEN 33423615
#define EIGHT 33484815
#define NINE 33462375

int RECV_PIN = 12;
int TEST_LED = 13;

//------------------^ DONT CHANGE ANY VALUES ABOVE THIS ^------------------
//*************************************************************************

//-----EDIT THE PIN NO:'s IF NEEDED-----VVV

#define Indicator1       10        //Blinking
#define Indicator2       11   
#define Extra_Indicator  9

#define LED1             2         //Steady ON and OFF
#define LED2             3
#define LED3             4
#define LED4             5
#define LED5             6
#define LED6             7
#define LED7             8

const long Interval = 500;           // interval at which indicator blink (milliseconds)

//-----------------------------------------

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key;
int PWR_STATE;
int Ex_Indicator_Key = 0;
int Ex_Indicator_State = LOW;
int Indicator1_Key = 0;
int Indicator1_State = LOW;
int Indicator2_Key = 0;
int Indicator2_State = LOW;
int Blink_State = LOW;
unsigned long previousMillis = 0;

void setup()
{
  pinMode(TEST_LED, OUTPUT);
  for(int i = 2; i < 12; i++)
    pinMode(i, OUTPUT);
  irrecv.enableIRIn();
  digitalWrite(TEST_LED,0);
  PWR_STATE = 0;
}

void loop() {
  key = 0;
  if (irrecv.decode(&results)){
    key = results.value;
    irrecv.resume();
  } 
    
  switch(key)
  {
    case PWR : 
        PWR_STATE = !digitalRead(TEST_LED);  digitalWrite(TEST_LED, PWR_STATE); break;
        
    case ZERO : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          Ex_Indicator_Key = !Ex_Indicator_Key;
          break;
        }
        
    case ONE : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          Indicator1_Key = !Indicator1_Key;
          break;
        }
        
    case TWO : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          Indicator2_Key = !Indicator2_Key;
          break;
        }
        
    case THREE : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          digitalWrite(LED1, !digitalRead(LED1));
          break;
        }
        
    case FOUR : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          digitalWrite(LED2, !digitalRead(LED2));
          break;
        }
        
    case FIVE : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          digitalWrite(LED3, !digitalRead(LED3));
          break;
        }
        
    case SIX : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          digitalWrite(LED4, !digitalRead(LED4));
          break;
        }
        
    case SEVEN : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          digitalWrite(LED5, !digitalRead(LED5));
          break;
        }
        
    case EIGHT : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          digitalWrite(LED6, !digitalRead(LED6));
          break;
        }
        
    case NINE : 
        if(PWR_STATE == 1){
          digitalWrite(TEST_LED, 0);
          digitalWrite(LED7, !digitalRead(LED7));
          break;
        }
        
    default :
        digitalWrite(TEST_LED, PWR_STATE);
  }    
        
    if(PWR_STATE == 0){
      for(int i = 2; i < 12; i++){
        digitalWrite(i, 0);
      }
      Ex_Indicator_Key = LOW;
      Indicator1_Key = LOW;
      Indicator2_Key = LOW;
    }
        
//------INDICATOR BLINKING---------{{{DONT EDIT}}}------------      

    unsigned long currentMillis = millis();
    
      if (currentMillis - previousMillis >= Interval) {
          previousMillis = currentMillis;

		  if (Blink_State == LOW) {
                Blink_State = HIGH;
          } else {
                Blink_State = LOW;
          }
			
          if(Ex_Indicator_Key == 1){
                 Ex_Indicator_State = Blink_State;
          }else  Ex_Indicator_State = LOW;
          
          if(Indicator1_Key == 1){
                 Indicator1_State = Blink_State;
          }else  Indicator1_State = LOW;
          
          if(Indicator2_Key == 1){
                 Indicator2_State = Blink_State;
          }else  Indicator2_State = LOW;
      }
      
    digitalWrite(Extra_Indicator, Ex_Indicator_State);
    digitalWrite(Indicator1, Indicator1_State);
    digitalWrite(Indicator2, Indicator2_State);
    
  delay(40);
}
