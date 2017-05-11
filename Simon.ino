//LEDs
#define ledVermelho     11
#define ledVerde   9
#define ledAzul    7
#define ledAmarelo  5
#define ledRespostaCerta 4
#define ledRespostaErrada   2

//Botões
#define btnVermelho    12
#define btnVerde  10
#define btnAzul   8
#define btnAmarelo 6

//Autofalante
#define autoFalante  3
#define autoFalVermelho 220
#define autoFalVerde 262
#define autoFalAzul 330
#define autoFalAmarelo 392
#define autoFalDuracao 250

//Simon
int velocidadeJogo = 250;
int statusJogo = 0;
int const sequenciaMaximaJogo = 50;
int sequenciaJogo[sequenciaMaximaJogo];
int faseJogo = 0;
int fase = 0;

void setup(){
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledRespostaCerta, OUTPUT);
  pinMode(ledRespostaErrada, OUTPUT);
  pinMode(btnVermelho, INPUT_PULLUP);
  pinMode(btnVerde, INPUT_PULLUP);
  pinMode(btnAzul, INPUT_PULLUP);
  pinMode(btnAmarelo, INPUT_PULLUP);
  pinMode(autoFalante, OUTPUT);
}

void loop(){
  
  switch(statusJogo){
    case 0:
      resetGame();
      break;
    case 1:
      Sequencia();
      break;
    case 2:
      obterSequencia();
      break;
    case 3:
      gameOver();
      break;
  }
  
}

void Sequencia(){
  for(int i=0; i<=faseJogo; i++){
    Serial.print("Set LED");
    Serial.println(sequenciaJogo[i]);
    delay(velocidadeJogo*2);
    setLED(sequenciaJogo[i]);
    tocarAlarme(sequenciaJogo[i]);
    delay(velocidadeJogo);
    clearLEDs();
    
  }
  statusJogo = 2;
}

void obterSequencia(){
  int button_value = obterSequencias();
  
  if(button_value > 0){
    if(button_value == sequenciaJogo[fase]){
      setLED(button_value);
      tocarAlarme(button_value);
      digitalWrite(ledRespostaCerta, HIGH);
      delay(velocidadeJogo);
      clearLEDs();
      digitalWrite(ledRespostaCerta, LOW);
      
      velocidadeJogo = velocidadeJogo-15;
      
      Serial.println("Correto!");
      
      if(fase == faseJogo){
        fase = 0;
        faseJogo++;
        statusJogo = 1;
        Serial.println("proximooo");
        
        setLEDs(true,true,true,true);
        delay(velocidadeJogo);
        setLEDs(false,false,false,false);
        
        
      }else{
        fase++;
      }
      
      delay(10);
      
    }else{
      statusJogo = 3;
      Serial.println("Fim de jogo, BIRL!");
    }
  }
  
  delay(10);
}

void resetGame(){
  fase = 0;
  faseJogo = 0;
  
  for(int i=0; i<sequenciaMaximaJogo; i++){
    sequenciaJogo[i] = random(4) + 1;
  }
  
  statusJogo = 1;
}

void gameOver(){
  digitalWrite(ledRespostaErrada, HIGH);
  tone(autoFalante, 98, autoFalDuracao);
  delay(autoFalDuracao);
  tone(autoFalante, 93, autoFalDuracao);
  delay(autoFalDuracao);
  tone(autoFalante, 87, autoFalDuracao);
  delay(autoFalDuracao);
  delay(velocidadeJogo);
}

void setLED(int id){
  switch(id){
    case 0:
      setLEDs(false,false,false,false);
      break;
    case 1:
      setLEDs(true,false,false,false);
      break;
    case 2:
      setLEDs(false,true,false,false);
      break;
    case 3:
      setLEDs(false,false,true,false);
      break;
    case 4:
      setLEDs(false,false,false,true);
      break; 
  }
}

void tocarAlarme(int id){
  switch(id){
    case 0:
      noTone(autoFalante);
      break;
    case 1:
      tone(autoFalante, autoFalVermelho, autoFalDuracao);
      break;
    case 2:
      tone(autoFalante, autoFalVerde, autoFalDuracao);
      break;
    case 3:
      tone(autoFalante, autoFalAzul, autoFalDuracao);
      break;
    case 4:
      tone(autoFalante, autoFalAmarelo, autoFalDuracao);
      break; 
  }
}

void setLEDs(boolean red, boolean green, boolean blue, int yellow ){
  if (red) digitalWrite(ledVermelho, HIGH);
  else digitalWrite(ledVermelho, LOW);
  if (green) digitalWrite(ledVerde, HIGH);
  else digitalWrite(ledVerde, LOW);
  if (blue) digitalWrite(ledAzul, HIGH);
  else digitalWrite(ledAzul, LOW);
  if (yellow) digitalWrite(ledAmarelo, HIGH);
  else digitalWrite(ledAmarelo, LOW);
}

void clearLEDs(){
  setLEDs(false,false,false,false);
}

int obterSequencias(void){
  if (digitalRead(btnVermelho) == 0) return 1;
  else if (digitalRead(btnVerde) == 0) return 2;
  else if (digitalRead(btnAzul) == 0) return 3;
  else if (digitalRead(btnAmarelo) == 0) return 4;
  
  return 0;
}
