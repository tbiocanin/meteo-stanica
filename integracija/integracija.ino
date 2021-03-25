int zelenaLedSv = 3; //digitalni ulaz zelene diode
int plavaLed = 2; //digitalni ulaz plave diode
int zutaLed = 4; //digitalni ulaz zute diode
int crvenaLed = 5; //digitalni ulaz crvene diode
int peca = 6; //digitalni ulaz za pecu
float tempUlaz;
int tempAnalogniPin = A5; //analogni ulaz na kom se nalazi senzor za temperaturu
int sensorPin = A3; //analogni ulaz na kom se nalazi fotootpornik 
int gasSenzor = A4; //analogni ulaz na kom se nalazi gas senzor
int photoCellIn = 0; //ulazna vrednost fotootpornika
int granicnaVrednost = 170;


void pecaVristi(){
 
 tone(peca, 1000);
  
}

void pecaNeVristi(){
  noTone(peca);
}


float temperaturaF(int pin) {
  float tempVrednost = analogRead(pin); //ucitaj vrednost sa analognog ulaza
  
  float napon = (tempVrednost/1024.0) * 5.0;
  float temperatura = (napon - .5) * 100;
 
  return temperatura;
}

void toggle(){

  int ledStateOff = 0; //ugasena led 
  for(int led = 2; led<6; led++){
    if(digitalRead(led) == 1) { //proveri da li led radi
    digitalWrite(led, ledStateOff); //ako radi, ugasi je
    }
  }
}

void setup()
{
  Serial.begin(9600);
  
  for(int led = 2; led < 6; led++){
   pinMode(led, OUTPUT);
    
  }
  
}

void loop()
{
  
  float temperatura = temperaturaF(tempAnalogniPin);
  float kolicinaCO = analogRead(gasSenzor);

  if(temperatura >-50 && temperatura < 15) {
    toggle();
    digitalWrite(plavaLed, HIGH);
    pecaNeVristi();
  } else if (temperatura > 16 && temperatura < 30) {
    toggle();
    digitalWrite(zutaLed, HIGH);
    pecaNeVristi();
  } else { 
    toggle();
    digitalWrite(crvenaLed, HIGH);
    pecaVristi();
  }
  
  
  photoCellIn = analogRead(sensorPin)/4; //reskaliranje na interval od 0-255 zbog LED sijalice
  analogWrite(zelenaLedSv, photoCellIn); //za vrednost koju je fotootpornik pokupio, sijalica ce da svetli
  
  if(kolicinaCO > granicnaVrednost && temperatura > 31){ //granicna vrednost
    pecaVristi();
    delay(100);
    pecaVristi();
    delay(100);
    pecaNeVristi();
  } else {
    pecaNeVristi();  
  }
}
