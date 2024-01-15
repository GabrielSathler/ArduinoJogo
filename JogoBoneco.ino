#define joyX A1
#define joyY A0

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

unsigned long tempRua; 

int pontoIncrementa = 5;
int ponto = 0;


int Joystick = 5;
int estadoBotao = 0;

int bonecoAndarX;
int bonecoAndarY;

int select;

int zero = 0;
int um = 1;

int iconePasso = 0;

int JoystickMoveX;  
int JoystickMoveY;

int x;
int linhaCima[16];
int linhaBaixo[16];

int Linha1[16];
int Linha2[16];

byte customChar1[] = {
  B01010,
  B01110,
  B01110,
  B00100,
  B11111,
  B10101,
  B01010,
  B01010
};

byte customChar2[] = {
 B01010,
  B01110,
  B01110,
  B00100,
  B11111,
  B10101,
  B01010,
  B10010
};
byte customChar3[] = {
  B01010,
  B01110,
  B01110,
  B00100,
  B11111,
  B10101,
  B01010,
  B01001
};

byte customChar4[] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B01110,
  B01110,
  B00000
};

byte customChar5[] = {
  B10001,
  B01110,
  B11111,
  B10101,
  B01110,
  B11111,
  B00100,
  B00000
};

byte Moeda[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B01110,
  B00100,
  B00000,
  B00000
  };


void setup() {
 Serial.begin(9600);
 lcd.begin();
 lcd.createChar(0, customChar1);
 lcd.createChar(1, customChar2);
 lcd.createChar(2, customChar3);
 lcd.createChar(3, customChar4);
 lcd.createChar(4, customChar5);
 lcd.createChar(5, Moeda);
 lcd.backlight();
 lcd.setBacklight(HIGH);
}

void bonecoLindo(){
  lcd.setCursor(0,1);
  lcd.write(customChar1);
}

void DesenhaRua()
{
  int PosInicial = 1;
  int PosFinal = 15;
  int x;
 
  for(int x = 0;x<=15;x++)
 {
   Linha1[x] = 0;
   Linha2[x] = 0;
 }
 
 for(int x = PosInicial;x<=PosFinal;x++)
 {
  if(random(10)>6)
    {Linha1[x] = 1;}
  else
    {
      if(random(10)>6) {
        Linha2[x] = 1;
        }   
    }
 
  if( (Linha1[x] == 1)||(Linha2[x] == 1) ){
    x++;
    }
  
 }
     
  lcd.clear();
  
  lcd.setCursor(1,0);
  for(int x = PosInicial;x<=PosFinal;x++)
   {
    if(Linha1[x] == 1){
      lcd.write(3);
      }else{
        lcd.write(' ');
        
      }    
  }
  
  lcd.setCursor(1,1);
  for(int x = PosInicial;x<=PosFinal;x++)
   {
    if(Linha2[x] == 1)
      {lcd.write(4);}
    else
      {lcd.write(' ');}    
  }   
  
}

void ruaAnda(){
 
  for(int x = 1; x<= 14; x++){
    Linha1[x] = Linha1[x + 1];
    Linha2[x] = Linha2[x + 1];
    }



     if(Linha1[14] == 1 || Linha2[14] == 1){
       Linha1[15] = 0;
       Linha2[15] = 0;
      }else{
        Linha1[15] = random(10)>6;
        if(Linha1[15]==0)
         {Linha2[15] = random(10)>6;}
        else
         {Linha2[15] = 0;}
       }
    
    
    
    
     lcd.setCursor(1, 0);
      for(int x = 1; x<=15; x++){
        if (Linha1[x] == 1){
          
          lcd.write(3);
          }else{
             lcd.print(' ');
        }
    }
     lcd.setCursor(1, 1);
     
     for(int x = 1; x<=15; x++){
          if (Linha2[x] == 1){
              lcd.write(4);
              }else{
                  lcd.print(' ');
        
        }
     }

  /*for(int x = 0;x<=15;x++)
 {
   Linha1[x] = 0;
   Linha2[x] = 0;
 }*/
 
      
  }

int morte(){
    Linha1[x];
    Linha2[x];
    bonecoAndarY;
    bonecoAndarX;

    if ((bonecoAndarX == 0)&&(Linha1[bonecoAndarY] == 1)){
      return 1;
      } 
    if ((bonecoAndarX == 1)&&(Linha2[bonecoAndarY] == 1)){
      return 1;
      } 
    return 0;
  }

void bonecoAnda(int PosY, int PosX){



  lcd.setCursor(bonecoAndarY, bonecoAndarX);
  lcd.print(' ');


  bonecoAndarY = constrain(bonecoAndarY + PosY, 0, 15);
  bonecoAndarX = constrain(bonecoAndarX + PosX, 0, 1); 

  lcd.setCursor(bonecoAndarY, bonecoAndarX);
  
   lcd.write(iconePasso);
     if (++iconePasso >= 3){
       iconePasso = 0;
      }
  delay(200);
 
}

void loop() {
 int morte1 = 0;
 DesenhaRua();
 bonecoAndarX = 0;
 bonecoAndarY = 0;
 bonecoAnda(0, 0); 
 delay(1000);
 
 
 while((morte1 == 0)&&(bonecoAndarY<15)){
   if((millis() - tempRua) > 500){
   tempRua = millis();
   aumentaVelocidade();
   ruaAnda();
   }
   morte1 += morte();
   
   Serial.print("Boneco "+String(bonecoAndarX)+","+String(bonecoAndarY));
   Serial.println("  "+String(morte()));

   
   estadoBotao = digitalRead(Joystick);
   

  int JoystickMoveX = analogRead(joyX); 
  int JoystickMoveY = analogRead(joyY);

  
 
  
  if(JoystickMoveX < 100){
    bonecoAnda(-1, 0); 
      }else if (JoystickMoveX > 900){
         bonecoAnda(1, 0);
   }
  else if (JoystickMoveY < 100){
           bonecoAnda(0, 1); 
           }else if (JoystickMoveY > 900){
                  bonecoAnda(0,-1);
                 }
                else{bonecoAnda(0,0);}

  morte1 += morte();
 }
  lcd.clear();
  if(bonecoAndarY>=15)
   {
    ponto++;
    lcd.setCursor(2, 0);
    lcd.print("VOCE GANHOU");
    lcd.setCursor(2 , 1);
    lcd.print("pontos: ");
    lcd.print(ponto);
    }else
    {
     ponto--;
     lcd.setCursor(2, 0);
     lcd.print("VOCE PERDEU");
     lcd.setCursor(2 , 1);
     lcd.print("pontos: ");
     lcd.print(ponto);
     }
  delay(4000);
}

void aumentaVelocidade(){
  if(ponto > 1){
    tempRua = 100;
    tempRua = millis();
    }
  }
