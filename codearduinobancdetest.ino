#include "HX711-multi.h"

//CAPTEURS DE FORCE
#define CLK 2      // pin clock
#define DOUT1 0    // pin premier HX711
#define DOUT2 3    // pin deuxième HX711

#define TARE_TIMEOUT_SECONDS 4 //temps de non réponse maximum

byte DOUTS[2] = {DOUT1, DOUT2}; //définit les entrées 

#define CHANNEL_COUNT sizeof(DOUTS)/sizeof(byte) //définit le nombre d'entrées

long int results[CHANNEL_COUNT];

HX711MULTI scales(CHANNEL_COUNT, DOUTS, CLK);

//CAPTEUR ULTRASON
const byte TRIGGER_PIN = 8; // Broche TRIGGER
const byte ECHO_PIN = 9;    // Broche ECHO

//VARIABLES MOYENNE DISTANCE
const int numReadings = 10;
int   rawVal = 0;         // 
float smoothedVal = 0.0;  // sensor smoothed value
float smoothStrength = 25;


//temps de non réponse maximum
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

//VITESSE DU SON
const float SOUND_SPEED = 340.0 / 1000;

void setup() {
  
  //INITIALISE ET VIDE LE PORT SERIE
  Serial.begin(115200);
  Serial.flush();
  tare();

  //DEFINIT LES BROCHES DU CAPTEUR ULTRASON
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
}


//CALIBRE LE CAPTEUR A CHAQUE DEMARAGE
void tare() {
  bool tareSuccessful = false;

  unsigned long tareStartTime = millis();
  while (!tareSuccessful && millis()<(tareStartTime+TARE_TIMEOUT_SECONDS*1000)) {
    tareSuccessful = scales.tare(20,10000);  //reject 'tare' if still ringing
  }
}


//ENVOIE PAR LE PORT SERIE LES DONNES DES CAPTEURS DE FORCE
void sendRawData() {
  scales.read(results);
  for (int i=0; i<scales.get_count(); ++i) {;
    Serial.print( -results[i]);  
    Serial.print( (i!=scales.get_count()-1)?"t":"\n");
  }  
  delay(50);
}


void loop() {
  
  sendRawData(); //REFERENCE AU VOID POUR ENVOYER LES DONNEES DES CAPTEURS DE FORCE
  
  //DEFINITLA DUREE DES IMPULSIONS POUR LE CAPTEUR ULTRASON
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
 //MESURE LE TEMPS DE RETOUR DES ULTRASONS
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   
  //CALCUL LA DISTANCE AVEC LE TEMPS DE RETOUR
  float distance_mm = measure / 2.0 * SOUND_SPEED;

  //CALCUL DE LA MOYENNE DE LA DISTANCE SUR LES 25 DERNIERES VALEURS POUR LISSER LES RESULTATS 
  rawVal = distance_mm;
    delay(10);

    smoothedVal = smooth(rawVal, smoothedVal);
    
  //ENVOIE LA VALEUR DE LA DISTANCE LISSEE ET UN SEPARATEUR ENTRE LES DONNEES
  Serial.print(smoothedVal - 53);
  Serial.print("t");
}
//CALCUL DE LA MOYENNE
float smooth(int t_rawVal, float t_smoothedVal) {
    return  t_smoothedVal + ((t_rawVal - t_smoothedVal) + 0.5) / smoothStrength;  // +0.5 for rounding
}
