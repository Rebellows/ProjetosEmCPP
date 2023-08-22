#include <Adafruit_NeoPixel.h>

#define botao 9
#define PIN 10
#define NUMPIXELS 11

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned const int A = 2;
unsigned const int B = 3;
unsigned const int C = 4;
unsigned const int D = 5;
unsigned const int E = 6;
unsigned const int F = 7;
unsigned const int G = 8;
int estadoBotao = 0;
int vermelho = 0;
int verde = 0;
int azul = 0;

void setColor(){
  vermelho = random(0, 255);
  verde = random(0,255);
  azul = random(0, 255);
  Serial.print("Vermelho: ");
  Serial.println(vermelho);
  Serial.print("Verde: ");
  Serial.println(verde);
  Serial.print("Azul: ");
  Serial.println(azul);
}

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(botao, INPUT);
  pixels.begin();
}
void loop() {
  estadoBotao = digitalRead(botao);
  setColor();
   if (estadoBotao == 1){
     for(int i=0;i<NUMPIXELS;i++){
       if (i <= 9){
         pixels.setPixelColor(i, pixels.Color(vermelho, verde, azul));
       	 pixels.show();
         delay(1000);
       }
       else {
         pixels.setPixelColor(0, pixels.Color(0, 0, 0));
         pixels.setPixelColor(1, pixels.Color(0, 0, 0));
         pixels.setPixelColor(2, pixels.Color(0, 0, 0));
         pixels.setPixelColor(3, pixels.Color(0, 0, 0));
         pixels.setPixelColor(4, pixels.Color(0, 0, 0));
         pixels.setPixelColor(5, pixels.Color(0, 0, 0));
         pixels.setPixelColor(6, pixels.Color(0, 0, 0));
         pixels.setPixelColor(7, pixels.Color(0, 0, 0));
         pixels.setPixelColor(8, pixels.Color(0, 0, 0));
         pixels.setPixelColor(9, pixels.Color(0, 0, 0));
         pixels.show();
       }
     }
     // Liga 0
     digitalWrite(A, HIGH);
     digitalWrite(B, HIGH);
     digitalWrite(C, HIGH);
     digitalWrite(D, HIGH);
     digitalWrite(E, HIGH);
     digitalWrite(F, HIGH);
     digitalWrite(G, LOW);
     delay(1000);

     // Liga 1
     digitalWrite(A, LOW);
     digitalWrite(B, HIGH);
     digitalWrite(C, HIGH);
     digitalWrite(D, LOW); 
     digitalWrite(E, LOW);
     digitalWrite(F, LOW);
     digitalWrite(G, LOW);
     delay(1000);

     // Liga 2
     digitalWrite(A, HIGH);
     digitalWrite(B, HIGH);
     digitalWrite(C, LOW);
     digitalWrite(D, HIGH);
     digitalWrite(E, HIGH);
     digitalWrite(F, LOW);
     digitalWrite(G, HIGH);
     delay(1000);

      // Liga 3
     digitalWrite(A, HIGH);
     digitalWrite(B, HIGH);
     digitalWrite(C, HIGH);
     digitalWrite(D, HIGH);
     digitalWrite(E, LOW);
     digitalWrite(F, LOW);
     digitalWrite(G, HIGH);
     delay(1000);

     // Liga 4
     digitalWrite(A, LOW);
     digitalWrite(B, HIGH);
     digitalWrite(C, HIGH);
     digitalWrite(D, LOW);
     digitalWrite(E, LOW);
     digitalWrite(F, HIGH);
     digitalWrite(G, HIGH);
     delay(1000);

     // Liga 5
     digitalWrite(A, HIGH);
     digitalWrite(B, LOW);
     digitalWrite(C, HIGH);
     digitalWrite(D, HIGH);
     digitalWrite(E, LOW);
     digitalWrite(F, HIGH);
     digitalWrite(G, HIGH);
     delay(1000);

     // Liga 6
     digitalWrite(A, HIGH);
     digitalWrite(B, LOW);
     digitalWrite(C, HIGH);
     digitalWrite(D, HIGH);
     digitalWrite(E, HIGH);
     digitalWrite(F, HIGH);
     digitalWrite(G, HIGH);
     delay(1000);

     // Liga 7
     digitalWrite(A, HIGH);
     digitalWrite(B, HIGH);
     digitalWrite(C, HIGH);
     digitalWrite(D, LOW);
     digitalWrite(E, LOW);
     digitalWrite(F, LOW);
     digitalWrite(G, LOW);
     delay(1000);

     // Liga 8
     digitalWrite(A, HIGH);
     digitalWrite(B, HIGH);
     digitalWrite(C, HIGH);
     digitalWrite(D, HIGH);
     digitalWrite(E, HIGH);
     digitalWrite(F, HIGH);
     digitalWrite(G, HIGH);
     delay(1000);

     // Liga 9
     digitalWrite(A, HIGH);
     digitalWrite(B, HIGH);
     digitalWrite(C, HIGH);
     digitalWrite(D, HIGH);
     digitalWrite(E, LOW);
     digitalWrite(F, HIGH);
     digitalWrite(G, HIGH);    
     delay(1000);
    }
    else {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      delay(1000);
    }
}  
