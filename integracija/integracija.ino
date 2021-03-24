int zelenaLedSv = 2;
int plavaLed = 3;
int zutaLed = 4;
int crvenaLed = 5;
int peca = 6;
float tempUlaz;
int tempAnalogniPin = A5;
int sensorPin = A3; //analogni ulaz na kom se nalazi fotootpornik 
int gasSenzor = A4;
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

void toggle(int pin){

  int ledStateOff = 0; //ugasena led 
  if(digitalRead(pin) == 1) { //proveri da li led radi
   digitalWrite(pin, ledStateOff); //ako radi, ugasi je
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
    for(int led = 3; led < 6; led ++){
     toggle(led);
    }
    digitalWrite(plavaLed, HIGH);
    pecaNeVristi();
  } else if (temperatura > 16 && temperatura < 30) {
    for(int led = 3; led < 6; led ++){
     toggle(led);
    }
    digitalWrite(zutaLed, HIGH);
    pecaNeVristi();
  } else { 
    for(int led = 3; led < 6; led ++){
     toggle(led);
    }
    digitalWrite(crvenaLed, HIGH);
    pecaVristi();
  }
  
  
  photoCellIn = analogRead(sensorPin)/4; //reskaliranje na interval od 0-255 zbog LED sijalice
  analogWrite(zelenaLedSv, photoCellIn); //za vrednost koju je fotootpornik pokupio, sijalica ce da svetli
  
  if(kolicinaCO > granicnaVrednost && temperatura > 31){
    pecaVristi();
    delay(100);
    pecaVristi();
    delay(100);
    pecaNeVristi();
  } else {
    pecaNeVristi();  
  }
}
