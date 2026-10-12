//Piano
//Kodex Academy

int piezo=1;


int pulser_C=13;
int pulser_D=12;
int pulser_E=11;
int pulser_F=10;
int pulser_G=9;
int pulser_A=8;
int pulser_B=7;

void setup() {

 pinMode(pulser_C, INPUT);
 pinMode(pulser_D, INPUT);
 pinMode(pulser_E, INPUT);
 pinMode(pulser_F, INPUT);
 pinMode(pulser_G, INPUT);
 pinMode(pulser_A, INPUT);
 pinMode(pulser_B, INPUT);
 pinMode(piezo, OUTPUT);



}

void loop() {

if (digitalRead(pulser_C) == HIGH) {
    tone(piezo, 263, 100); }
  

  
  if (digitalRead(pulser_D) == HIGH) {
    tone(piezo, 294, 100); }    
  
  
  
  if (digitalRead(pulser_E)== HIGH) {
    tone(piezo, 330, 100);} 
  

  
  if (digitalRead(pulser_F)== HIGH) {
    tone(piezo, 349, 100); }    
  
  
  
  if (digitalRead(pulser_G)== HIGH) {
    tone(piezo, 392, 100);} 
  

  
  if (digitalRead(pulser_A)== HIGH) {
    tone(piezo, 440, 100);}     
  
  
  
  
  if (digitalRead(pulser_B)== HIGH) {
    tone(piezo, 494, 100);} 
delay(10); 
      
      
      
       
}