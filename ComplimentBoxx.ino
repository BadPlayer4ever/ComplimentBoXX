#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //Declaracion de pins para pantalla LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Creacion de objeto LCD



//Caracteres especiales
byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};
byte heartBig[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};
byte heartSmall[8] = {
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b00000
};
byte sun[8]{
  0b00100,
  0b10001,
  0b00100,
  0b01110,
  0b11111,
  0b01110,
  0b00100,
  0b10001
  
};

//Creacion de arrays que contienen las frases. 
//Deben almacenarse en memoria de programa para evitar consumir toda la memoria Dinamica
const char string0[] PROGMEM = "Sos una chimba  Creaselas!      ";
const char string1[] PROGMEM = "Esos crespos no se arman solos! ";
const char string2[] PROGMEM = " Praise the sun        \4        ";
const char string3[] PROGMEM = "Estoy mas buena que una ensalada";
const char string4[] PROGMEM = "Maybe not today     But tomorrow";
const char string5[] PROGMEM = "Good job Me!           Thank Me!";
const char string6[] PROGMEM = "  HOME    FOOD     IS    SACRED ";
const char string7[] PROGMEM = "You gotta get Up  Get out!      ";
const char string8[] PROGMEM = "Llevo mas colore  que un jarron!";
const char string9[] PROGMEM = "Love The Curls! They deserve it!";
const char string10[] PROGMEM = "Knot by Knot... You'll get there";
const char string11[] PROGMEM = "Gotta gimmie      \3 Some Love  ";
const char string12[] PROGMEM = "Nourish yourself Like a plant \4 ";
const char string13[] PROGMEM = "Stay Healthy    \1 Stay beautiful";
const char string14[] PROGMEM = "Your simplicity Outshines \3     ";
const char string15[] PROGMEM = "Keep moving     Those joints    ";
const char string16[] PROGMEM = "You know? You're  Really cool   ";
const char string17[] PROGMEM = "    You did a   damn fine job \3";
const char string18[] PROGMEM = "You deserve to be cared about";
const char string19[] PROGMEM = "Charming as fuck wink wink *";
const char string20[] PROGMEM = "I'm as authenticAs they come ";
const char string21[] PROGMEM = "Your hair just  add to the charm";
const char string22[] PROGMEM = "  Lo mio es       todo natural  ";
const char string23[] PROGMEM = "May i steal a   curl from you?";
const char string24[] PROGMEM = "My feelings are   not decoration";
const char string25[] PROGMEM = "Sabes lo que soy   I'm Worth it";

 

//Array con las direcciones de las cadenas de texto
const char* const compliments[] PROGMEM={string0,string1,string2,string3,string4,string5,string6,string7,string8,string9,string10,string11,string12,string13,string14,string15,string16,string17,string18,string19,string20,string21,string22,string23,string24,string25};



char buffer[33];
int keyValue=0;
int complimentNumber=0;


void nextCompliment() { //Obtener un cumplido aleatorio
  
  int rand=random(0,complimentNumber);
  Serial.print(rand);
  String half1,half2="";
  strcpy_P(buffer, (char*)pgm_read_word(&(compliments[rand])));
  String compliment=String(buffer);
  Serial.println(compliment);
  half1=compliment.substring(0,16); //Dividir cadena en 2 mitades
  half2=compliment.substring(16,32);

  lcd.clear();    //Imprimir en pantalla LCD
  lcd.setCursor(0,0);
  lcd.print(half1);
  lcd.setCursor(0, 1);
  lcd.print(half2);
}


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A2));
  for(const char* a: compliments){
    complimentNumber++;
  }
  Serial.println("Compliment number: "+String(complimentNumber));
  
  //Inicializacion de LCD y caracteres especiales
  lcd.begin(16, 2);  
  lcd.createChar(0, armsDown);
  lcd.createChar(1, armsUp);
  lcd.createChar(2, heartSmall);
  lcd.createChar(3, heartBig);
  lcd.createChar(4, sun);
  lcd.setCursor(0, 0);
  lcd.print("Compliment BoXX");  
  lcd.setCursor(0, 1);
  lcd.print("  Made with love");

  //Animacion de bienvenida
  while ((millis()/1000)<4) {
    lcd.setCursor(0,1);
    lcd.write(byte(2));
    delay(500);
    lcd.setCursor(0,1);
    lcd.write(byte(3));
    delay(500);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Push the button");
  lcd.setCursor(0, 1);
  lcd.print(" for compliments");
}

void loop() {

  //Escaneo de boton y debouncing
  bool wake=false;
  bool keyPressed=false;
  while (!wake){
    keyValue=analogRead(A0);
    if (keyValue!=0){
      delay(50);
      keyValue=analogRead(A0);
      if (keyValue!=0){
        keyPressed=true;
        nextCompliment();
        while (keyPressed) {
          delay(80);
          keyValue=analogRead(A0);
          if (keyValue==0) keyPressed=false;
        }
      }
    delay(80);
  }
}
}



