/* @author: Lucas Lacerda (lucaaslb)
    Projeto Automação residêncial
    MICROCONTROLADORES - UAM - CCO 6° SEMESTRE
    Setembro / 2018
*/

#include <LiquidCrystal_I2C.h>

// Componetes e pinos Arduino
#define LED00 A0
#define LED01 A1
#define LED02 A2
#define LED03 A3
#define BTNLED00 2
#define BTNLED01 3
#define BTNLED02 4
#define BTNLED03 5

#define DISPLAY7_A 6
#define DISPLAY7_B 7
#define DISPLAY7_C 8
#define DISPLAY7_D 9
#define DISPLAY7_E 10
#define DISPLAY7_F 11
#define DISPLAY7_G 12

#define BUZZ 13

//Variaveis globais;
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
byte eventTime;
int const lcdWidth = 16;
int const lcdHeight = 2;
int stringStart, stringStop = 0;
int scrollCursor = lcdWidth;
String msg = "APS MICROCONTROLADORES";

void setup() {
  pinMode(LED00, OUTPUT);
  pinMode(LED01, OUTPUT);
  pinMode(LED02, OUTPUT);
  pinMode(LED03, OUTPUT);

  pinMode(BTNLED00, INPUT);
  pinMode(BTNLED01, INPUT);
  pinMode(BTNLED02, INPUT);
  pinMode(BTNLED03, INPUT);

  pinMode(BUZZ, OUTPUT);

  pinMode(DISPLAY7_A, OUTPUT); //Pino 6 do Arduino ligado ao segmento A
  pinMode(DISPLAY7_B, OUTPUT); //Pino 7 do Arduino ligado ao segmento B
  pinMode(DISPLAY7_C, OUTPUT); //Pino 8 do Arduino ligado ao segmento C
  pinMode(DISPLAY7_D, OUTPUT); //Pino 9 do Arduino ligado ao segmento D
  pinMode(DISPLAY7_E, OUTPUT); //Pino 10 do Arduino ligado ao segmento E
  pinMode(DISPLAY7_F, OUTPUT); //Pino 11 do Arduino ligado ao segmento F
  pinMode(DISPLAY7_G, OUTPUT); //Pino 12 do Arduino ligado ao segmento G

  Serial.begin(9600);
  lcd.begin (lcdWidth, lcdHeight);
  lcd.noAutoscroll();
  lcd.setBacklight(HIGH);

  writeDisplay("Proj.TRANQUILO!", 0, 0, false);

  delay(1700);

  msgStart();

  eventTime = 10;
}

void loop() {
  btnLedOnOff();

  if (Serial.available() > 0) {
    timingEffects();
  }
}


void beep() {
  tone(BUZZ, 1000);
  delay(200);
  noTone(BUZZ);
}


void tenSeconds(byte digit) {
  byte seven_seg_digits[16][7] = {
    { 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 0 }, // = Digito 0
    { 0, 1, 1, 0, 0, 0, 0 }, // = Digito 1
    { 1, 1, 0, 1, 1, 0, 1 }, // = Digito 2
    { 1, 1, 1, 1, 0, 0, 1 }, // = Digito 3
    { 0, 1, 1, 0, 0, 1, 1 }, // = Digito 4
    { 1, 0, 1, 1, 0, 1, 1 }, // = Digito 5
    { 1, 0, 1, 1, 1, 1, 1 }, // = Digito 6
    { 1, 1, 1, 0, 0, 0, 0 }, // = Digito 7
    { 1, 1, 1, 1, 1, 1, 1 }, // = Digito 8
    { 1, 1, 1, 0, 0, 1, 1 } // = Digito 9

  };
  byte pin = 6;

  //Percorre o array ligando os segmentos correspondentes ao digito
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    pin++;
  }
  delay(50);
}


void btnLedOnOff() {

  if (digitalRead(BTNLED00)) {
    digitalWrite(LED00, !digitalRead(LED00));
    delay(500);
  }

  if (digitalRead(BTNLED01)) {
    digitalWrite(LED01, !digitalRead(LED01));
    delay(500);
  }

  if (digitalRead(BTNLED02)) {
    digitalWrite(LED02, !digitalRead(LED02));
    delay(500);
  }

  if (digitalRead(BTNLED03)) {
    digitalWrite(LED03, !digitalRead(LED03));
    delay(500);
  }

}

void timingEffects() {
  byte contador;

  unsigned char SerialValue = (unsigned char)Serial.read();

  switch (SerialValue) {
    case 'l':
      digitalWrite(LED00, !digitalRead(LED00));
      delay(500);
      break;
    case 'e':
      digitalWrite(LED01, !digitalRead(LED01));
      delay(500);
      break;
    case 'd':
      digitalWrite(LED02, !digitalRead(LED02));
      delay(500);
      break;
    case 's':
      digitalWrite(LED03, !digitalRead(LED03));
      delay(500);
      break;
    case '1':
      turnLedOff();

      writeDisplay("Efeito 1:", 0, 0, true);
      writeDisplay("Flashes all", 3, 1, false);

      for (contador = eventTime; contador > 0; contador--) {
        tenSeconds(contador);
        effect00();
      }
      tenSeconds(contador);
      beep();
      msgDefault();
      break;

    case '2':
      turnLedOff();

      writeDisplay("Efeito 2:", 0, 0, true);
      writeDisplay("Boomerang", 2, 1, false);

      for (contador = eventTime; contador > 0; contador--) {
        tenSeconds(contador);

        digitalWrite(LED00, HIGH);
        delay(135);
        digitalWrite(LED00, LOW);
        digitalWrite(LED01, HIGH);
        delay(135);
        digitalWrite(LED01, LOW);
        digitalWrite(LED02, HIGH);
        delay(135);
        digitalWrite(LED02, LOW);
        digitalWrite(LED03, HIGH);
        delay(135);
        digitalWrite(LED03, LOW);
        digitalWrite(LED02, HIGH);
        delay(135);
        digitalWrite(LED02, LOW);
        digitalWrite(LED01, HIGH);
        delay(135);
        digitalWrite(LED01, LOW);
        delay(135);
      }

      tenSeconds(contador);
      turnLedOff();
      beep();
      msgDefault();

      break;

    case '3':
      turnLedOff();

      writeDisplay("Efeito 3:", 0, 0, true);
      writeDisplay("Pares", 2, 1, false);

      for (contador = eventTime; contador > 0; contador--) {
        tenSeconds(contador);
        digitalWrite(LED00, HIGH);
        digitalWrite(LED01, HIGH);
        delay(270);
        digitalWrite(LED00, LOW);
        digitalWrite(LED01, LOW);

        delay(200);
        digitalWrite(LED02, HIGH);
        digitalWrite(LED03, HIGH);
        delay(270);
        digitalWrite(LED02, LOW);
        digitalWrite(LED03, LOW);

        delay(200);
      }
      tenSeconds(contador);
      turnLedOff();
      beep();
      msgDefault();
      break;

    case '4':
      turnLedOff();

      writeDisplay("Efeito 4:", 0, 0, true);
      writeDisplay("Random", 2, 1, false);

      for (contador = eventTime; contador > 0; contador--) {
        tenSeconds(contador);
        effect03();
      }
      tenSeconds(contador);
      turnLedOff();
      beep();
      msgDefault();

      break;
    case '-':

      eventTime <= 0 ? eventTime = 0 : eventTime--;

      writeDisplay("TEMPO:", 0, 1, true);
      writeDisplay(String(eventTime), 13, 1, false);
      writeDisplay("s", 15, 1, false);

      delay(700);
      msgDefault();
      break;
    case '+':

      eventTime >= 10 ? eventTime = 10 : eventTime++;

      writeDisplay("TEMPO:", 0, 1, true);
      writeDisplay(String(eventTime), 13, 1, false);
      writeDisplay("s", 15, 1, false);

      delay(700);
      msgDefault();

      break;
  }

}

void turnLedON() {
  digitalWrite(LED00, HIGH);
  digitalWrite(LED01, HIGH);
  digitalWrite(LED02, HIGH);
  digitalWrite(LED03, HIGH);
}

void turnLedOff() {
  digitalWrite(LED00, LOW);
  digitalWrite(LED01, LOW);
  digitalWrite(LED02, LOW);
  digitalWrite(LED03, LOW);
}

//Efeito para piscar todos os leds de uma vez em um intervalo de 50ms
void effect00() {
  for (int i = 0; i < 10; i++) {
    turnLedON();
    delay(50);
    turnLedOff();
    delay(50);
  }
}

//acende ou apaga os leds aleatoriamente
void effect03() {
  int LEDS[] = {A0, A1, A2, A3};
  for (int i = 0; i < 4; i++) {
    int STATUS = random(0, 2); // entre 0 e 1
    digitalWrite(LEDS[i], STATUS);
    delay(200);
  }
  turnLedOff();
}

/*
   metodo recebe todos parametros necessarios para escrever no lcd

   @param String msg Mensagem para ser exibida
   @param int column coluna inicial para setar o cursor
   @param int line linha onde sera exibida a msg
   @param bool clearDisplay se verdadeiro o display é limpo antes de exibir a nova mensagem

*/
void writeDisplay(String msg, int column, int line, bool clearDisplay) {
  if (clearDisplay) {
    lcd.clear();
    Serial.println();
  }
  Serial.print(msg + " ");
  lcd.setCursor(column, line);
  lcd.print(msg);
}

// Exibe mensagens de inicialização
// utilizando scroll horizontal para efeito de exibição do texto
void msgStart() {
  int cont = 0;
  lcd.clear();

  do {
    lcd.setCursor(scrollCursor, 1);
    lcd.print(msg.substring(stringStart, stringStop));
    writeDisplay("SEJA BEM VINDO", 1, 0, false);

    //Quanto menor o valor do delay, mais rapido o scroll
    delay(300);
    scroll(); //Chama a rotina que executa o scroll

    cont++;
  } while (cont <= msg.length());
  stringStart = 0;
  stringStop = 0;

  for (int i = 0; i < 2; i++) {
    lcd.clear();
    delay(500);
    writeDisplay("SEJA BEM", 4, 0, true);
    writeDisplay("VINDO", 5, 1, false);
    delay(500);
  }

  delay(1000);
  msgDefault();
}

void scroll() {
  lcd.clear();
  if (stringStart == 0 && scrollCursor > 0) {
    scrollCursor--;
    stringStop++;
  } else if (stringStart == stringStop) {
    stringStart = stringStop = 0;
    scrollCursor = lcdWidth;
  } else if (stringStop == msg.length() && scrollCursor == 0) {
    stringStart++;
  } else {
    stringStart++;
    stringStop++;
  }
}

void msgDefault() {
  writeDisplay(msg.substring(0, 4), 7, 0, true);
  writeDisplay(msg.substring(4, msg.length() - 1), 0, 1, false);
}
