#include <UTFTGLUE.h>              //use GLUE class and constructor
#include <stdint.h>
#include "TouchScreen.h"
#include <MCUFRIEND_kbv.h>
#include <Servo.h>
UTFTGLUE myGLCD(0,A2,A1,A3,A4,A0); //all dummy args
MCUFRIEND_kbv tft;
Servo myServo ;
Servo myServoAv ;
Servo myServoAp ;
#define YP A1  
#define XM A2  
#define YM 7   
#define XP 6   
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define degree 50
int angle,Passnum1[4]={0},Passnum2[4]={0},Passnum3[4]={0},Passnum4[4]={0},Passnum5[4]={0},Passnum6[4]={0},Passnum7[4]={0},Passnum8[4]={0},Passnum9[4]={0},Passnum10[4]={0},Passnum11[4]={0},Passnum12[4]={0},Passnum13[4]={0},Passnum14[4]={0},Passnum15[4]={0},Passnum16[4]={0}
;
int Passurgent[4]={9,9,9,9},PassE1[4]={0},PassE2[4]={0},PassE3[4]={0},PassE4[4]={0},PassE5[4]={0},PassE6[4]={0},PassE7[4]={0},PassE8[4]={0},PassE9[4]={0},PassE10[4]={0},PassE11[4]={0},PassE12[4]={0},PassE13[4]={0},PassE14[4]={0},PassE15[4]={0},PassE16[4]={0};
int num=0,d=140,x1,y1,i=0,pass,Press_S,nbrCases=3,x,y,statut0=0,statut1=0,statut2=0,statut3=0,statut4=0,statut5=0,Press;
char pressed,val,stCurrent[4]="",select='1',Page='0',select1='0',select2='0',select3='0',select4='0',select5='0',select6='0',select7='0',select8='0',select9='0',select10='0',select11='0',select12='0',select13='0',select14='0',select15='0',select16='0';
#define Servopin 21   // Moteur de la roue 
#define ServopinAv 33 // Moteur du 1ére barrière
#define ServopinAp 35 // Moteur du 2éme barrière
#define infr0 45 // attach pin 43 Arduino to pin of IR sensor 
#define infr1 43 // attach pin 45 Arduino to pin of IR sensor
#define infr2 47 // attach pin 47 Arduino to pin of IR sensor
#define infr3 49 // attach pin 49 Arduino to pin of IR sensor
#define infr4 51 // attach pin 51 Arduino to pin of IR sensor
#define infr5 53 // attach pin 53 Arduino to pin of IR sensor

void drawHomeScreen()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.setTextSize(2); // Sets font to big
  myGLCD.setCursor(70,10);
  myGLCD.println("Bienvenue dans Smart Parking");
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,32,480,32); // Draws the red line
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.setTextSize(2);
  myGLCD.setCursor(60,40);
  myGLCD.println("voulez-vous entrer ou sortir ?");
  // Button - Interface d'entrée
  myGLCD.setColor(VGA_RED); // Sets Red color
  myGLCD.fillRoundRect (35, 90, 445, 140); // Draws filled rounded rectangle
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.drawRoundRect (35, 90, 445, 140);
  myGLCD.setTextSize(3); // Sets the font to big
  myGLCD.setBackColor(VGA_WHITE); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.setCursor(70,100);
  myGLCD.println("INTERFACE D'ENTREE"); // Prints the string
  // Button - Interface de sortie
   myGLCD.setColor(VGA_RED);
  myGLCD.fillRoundRect (35, 150, 445, 200);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (35, 150, 445, 200);
  myGLCD.setTextSize(3);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.setCursor(70,160);
  myGLCD.println("INTERFACE DE SORTIE");
  // Button - Interface de sortie
   myGLCD.setColor(VGA_RED);
  myGLCD.fillRoundRect (10, 210, 470, 260);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (10, 210, 470, 260);
  myGLCD.setTextSize(3);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.setCursor(15,220);
  myGLCD.println("NOMBRE DES CASES REMPLIES"); 
}
void drawEnterScreen()
{
   myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setColor(VGA_AQUA);
  myGLCD.fillRoundRect (10, 10, 90, 55);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.drawRoundRect (10, 10, 90, 55);
   myGLCD.setTextSize(4);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setCursor(25,20);
  myGLCD.println("<-");
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(3);
  myGLCD.setCursor(130,20);
  myGLCD.println("Retournez au Menu");
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,60,480,60); // Draws the red line
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(2);
  myGLCD.setCursor(130,70);
  myGLCD.println("INTERFACE D'ENTREE");
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,90,480,90); // Draws the red line
   if((select1=='1')&&(select2=='1')&&(select3=='1')&&(select4=='1')&&(select5=='1')&&(select6=='1')&&(select7=='1')&&(select8=='1')&&(select9=='1')&&(select10=='1')&&(select11=='1')&&(select12=='1')&&(select13=='1')&&(select14=='1')&&(select15=='1')&&(select16=='1'))
  {
    myGLCD.setBackColor(VGA_BLACK);
    myGLCD.setTextSize(2); // Sets the font to small
    myGLCD.setCursor(50,100);
    myGLCD.println("");
    myGLCD.setTextSize(3);
    myGLCD.setColor(VGA_AQUA);
    myGLCD.setCursor(50,170);
    myGLCD.println("LE PARKING EST PLEIN");
  }
  else
  {
    myGLCD.setColor(VGA_WHITE);
    myGLCD.setTextSize(2); // Sets the font to small
    myGLCD.setCursor(50,100);
    myGLCD.println("Veuillez Selectionnez votre case");
  }
  // Button 1
  if(select1 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 30,  120 , 80 ,  170);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(40,125);
  myGLCD.println("1");
  }
  else
  {
    myGLCD.setBackColor(VGA_BLACK);
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 30,  120 , 80 ,  170);// Button 1
  }
  // Button 2
  if(select2 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 90,  120 , 140 ,  170);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(100,125);
  myGLCD.println("2");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 90,  120 , 140 ,  170);
  }
  // Button 3
  if(select3 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 150,  120 , 200 ,  170);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(160,125);
  myGLCD.println("3");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 150,  120 , 200 ,  170);// Button 1
  }
  // Button 4
  if(select4 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 210,  120 , 260 ,  170);// Button 4
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(220,125);
  myGLCD.println("4");
  }
  else
  {
   myGLCD.setColor(VGA_BLACK); // Sets green color
   myGLCD.fillRoundRect( 210,  120 , 260 ,  170);// Button 4
  }
  // Button 5
  if (select5 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 270,  120 , 320 ,  170);// Button 5
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(280,125);
  myGLCD.println("5");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 270,  120 , 320 ,  170);// Button 5
  }
  // Button 6
  if(select6 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 330,  120 , 380 ,  170);// Button 6
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(340,125);
  myGLCD.println("6");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 330,  120 , 380 ,  170);// Button 6
  }
  // Button 7
  if(select7 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 390,  120 , 440 ,  170);// Button 7
  myGLCD.setTextSize(5); // Sets the font to big
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(400,125);
  myGLCD.println("7");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 390,  120 , 440 ,  170);// Button 7
  }
  // Button 8
  if(select8 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 30,  190 , 80 ,  240);// Button 8
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(40,195);
  myGLCD.println("8");
  }
  else 
  {
     myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 30,  190 , 80 ,  240);// Button 8
  }
  // Button 9
  if(select9 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 90,  190 , 140 ,  240);// Button 9
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(100,195);
  myGLCD.println("9");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 90,  190 , 140 ,  240);// Button 9
  }
  // Button 10
  if(select10 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 150,  190 , 230 ,  240);// Button 10
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(160,195);
  myGLCD.println("10");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 150,  190 , 230 ,  240);// Button 10
  }
  // Button 11
  if(select11 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 240,  190 , 320 ,  240);// Button 11
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(250,195);
  myGLCD.println("11");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 240,  190 , 320 ,  240);// Button 11
  }
  // Button 12
  if(select12 == '0')
  {
    myGLCD.setColor(VGA_AQUA); // Sets green color
    myGLCD.fillRoundRect( 330,  190 , 410 ,  240);// Button 12
    myGLCD.setTextSize(5); // Sets the font to big 
    myGLCD.setColor(VGA_BLACK);//White
    myGLCD.setCursor(340,195);
    myGLCD.println("12");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 330,  190 , 410 ,  240);// Button 12
  }
  // Button 13
  if(select13 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 40,  260 , 120 ,  310);// Button 13
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(50,265);
  myGLCD.println("13");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 40,  260 , 120 ,  310);// Button 13
  }
  // Button 14
  if(select14 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 130,  260 , 210 ,  310);// Button 14
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(140,265);
  myGLCD.println("14");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 130,  260 , 210 ,  310);// Button 14
  }
  // Button 15
  if(select15 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 220,  260 , 300 ,  310);// Button 15
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(230,265);
  myGLCD.println("15");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 220,  260 , 300 ,  310);// Button 15
  }
  // Button 16
  if(select16 == '0')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 310,  260 , 390 ,  310);// Button 16
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(320,265);
  myGLCD.println("16");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 310,  260 , 390 ,  310);// Button 16
  }
}
void drawExitScreen()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setColor(VGA_AQUA);
  myGLCD.fillRoundRect (10, 10, 90, 55);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.drawRoundRect (10, 10, 90, 55);
   myGLCD.setTextSize(4);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setCursor(25,20);
  myGLCD.println("<-");
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(3);
  myGLCD.setCursor(130,20);
  myGLCD.println("Retournez au Menu");
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,60,480,60); // Draws the red line
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(2);
  myGLCD.setCursor(130,70);
  myGLCD.println("INTERFACE DE SORTIE");
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,90,480,90); // Draws the red line
  if((select1=='0')&&(select2=='0')&&(select3=='0')&&(select4=='0')&&(select5=='0')&&(select6=='0')&&(select7=='0')&&(select8=='0')&&(select9=='0')&&(select10=='0')&&(select11=='0')&&(select12=='0')&&(select13=='0')&&(select14=='0')&&(select15=='0')&&(select16=='0'))
  {
    myGLCD.setBackColor(VGA_BLACK);
    myGLCD.setTextSize(2); // Sets the font to small
    myGLCD.setCursor(50,100);
    myGLCD.println("");
    myGLCD.setTextSize(3);
    myGLCD.setColor(VGA_AQUA);
    myGLCD.setCursor(50,170);
    myGLCD.println("AUCUNE PLACE RESERVEE");
  }
  else
  {
    myGLCD.setColor(VGA_WHITE);
    myGLCD.setTextSize(2); // Sets the font to small
    myGLCD.setCursor(50,100);
    myGLCD.println("Veuillez Selectionnez votre case");
  }
  // Button 1
  if(select1 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 30,  120 , 80 ,  170);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(40,125);
  myGLCD.println("1");
  }
  else
  {
    myGLCD.setBackColor(VGA_BLACK);
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 30,  120 , 80 ,  170);// Button 1
  }
  // Button 2
  if(select2 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 90,  120 , 140 ,  170);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(100,125);
  myGLCD.println("2");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 90,  120 , 140 ,  170);
  }
  // Button 3
  if(select3 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 150,  120 , 200 ,  170);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(160,125);
  myGLCD.println("3");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 150,  120 , 200 ,  170);// Button 1
  }
  // Button 4
  if(select4 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 210,  120 , 260 ,  170);// Button 4
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(220,125);
  myGLCD.println("4");
  }
  else
  {
   myGLCD.setColor(VGA_BLACK); // Sets green color
   myGLCD.fillRoundRect( 210,  120 , 260 ,  170);// Button 4
  }
  // Button 5
  if (select5 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 270,  120 , 320 ,  170);// Button 5
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(280,125);
  myGLCD.println("5");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 270,  120 , 320 ,  170);// Button 5
  }
  // Button 6
  if(select6 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 330,  120 , 380 ,  170);// Button 6
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(340,125);
  myGLCD.println("6");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 330,  120 , 380 ,  170);// Button 6
  }
  // Button 7
  if(select7 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 390,  120 , 440 ,  170);// Button 7
  myGLCD.setTextSize(5); // Sets the font to big
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(400,125);
  myGLCD.println("7");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 390,  120 , 440 ,  170);// Button 7
  }
  // Button 8
  if(select8 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 30,  190 , 80 ,  240);// Button 8
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(40,195);
  myGLCD.println("8");
  }
  else 
  {
     myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 30,  190 , 80 ,  240);// Button 8
  }
  // Button 9
  if(select9 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 90,  190 , 140 ,  240);// Button 9
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(100,195);
  myGLCD.println("9");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 90,  190 , 140 ,  240);// Button 9
  }
  // Button 10
  if(select10 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 150,  190 , 230 ,  240);// Button 10
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(160,195);
  myGLCD.println("10");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 150,  190 , 230 ,  240);// Button 10
  }
  // Button 11
  if(select11 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 240,  190 , 320 ,  240);// Button 11
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(250,195);
  myGLCD.println("11");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 240,  190 , 320 ,  240);// Button 11
  }
  // Button 12
  if(select12 == '1')
  {
    myGLCD.setColor(VGA_AQUA); // Sets green color
    myGLCD.fillRoundRect( 330,  190 , 410 ,  240);// Button 12
    myGLCD.setTextSize(5); // Sets the font to big 
    myGLCD.setColor(VGA_BLACK);//White
    myGLCD.setCursor(340,195);
    myGLCD.println("12");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 330,  190 , 410 ,  240);// Button 12
  }
  // Button 13
  if(select13 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 40,  260 , 120 ,  310);// Button 13
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(50,265);
  myGLCD.println("13");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 40,  260 , 120 ,  310);// Button 13
  }
  // Button 14
  if(select14 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 130,  260 , 210 ,  310);// Button 14
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(140,265);
  myGLCD.println("14");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 130,  260 , 210 ,  310);// Button 14
  }
  // Button 15
  if(select15 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 220,  260 , 300 ,  310);// Button 15
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(230,265);
  myGLCD.println("15");
  }
  else 
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect( 220,  260 , 300 ,  310);// Button 15
  }
  // Button 16
  if(select16 == '1')
  {
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 310,  260 , 390 ,  310);// Button 16
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(320,265);
  myGLCD.println("16");
  }
  else
  {
    myGLCD.setColor(VGA_BLACK); // Sets green color
    myGLCD.fillRoundRect( 310,  260 , 390 ,  310);// Button 16
  }
}
void drawCaseLibre(){
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setColor(VGA_AQUA);
  myGLCD.fillRoundRect (10, 30, 90, 80);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.drawRoundRect (10, 30, 90, 80);
   myGLCD.setTextSize(4);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setCursor(30,40);
  myGLCD.println("<-");
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(3);
  myGLCD.setCursor(130,45);
  myGLCD.println("Retournez au Menu");
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,90,480,90); // Draws the red line
  myGLCD.setColor(255, 255 , 255); // Sets color to White 
  myGLCD.setTextSize(7);
  if((nbrCases>=10)&&(nbrCases<16))
  {
  myGLCD.printNumI(nbrCases,135,170);
  myGLCD.setCursor(220,170);
  myGLCD.println("/16");
  }
   if((nbrCases>=0)&&(nbrCases<10))
  {
    myGLCD.setCursor(135,170);
    myGLCD.println("0");
    myGLCD.printNumI(nbrCases,190,170);
    myGLCD.setCursor(220,170);
    myGLCD.println("/16");
  }
   if(nbrCases==16)
  {
    myGLCD.setTextSize(3);
    myGLCD.setColor(VGA_RED);
    myGLCD.setBackColor(VGA_RED);
    myGLCD.setCursor(50,170);
    myGLCD.println("LE PARKING EST PLEIN");
  }
}
void drawAffichagePass()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.setTextSize(3); // Sets font to big
  myGLCD.setCursor(40,70);
  myGLCD.println("Votre Mot de passe est");
  if(Press==1)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum1[k]=random(9);
      myGLCD.printNumI(Passnum1[k],d+=30,140);
    }
    d=140;
  }
  if(Press==2)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum2[k]=random(9);
      myGLCD.printNumI(Passnum2[k],d+=30,140);
    }
    d=140;
  }
  if(Press==3)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum3[k]=random(9);
      myGLCD.printNumI(Passnum3[k],d+=30,140);
    }
    d=140;
  }
  if(Press==4)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum4[k]=random(9);
      myGLCD.printNumI(Passnum4[k],d+=30,140);
    }
    d=140;
  }
  if(Press==5)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum5[k]=random(9);
      myGLCD.printNumI(Passnum5[k],d+=30,140);
    }
    d=140;
  }
  if(Press==6)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum6[k]=random(9);
      myGLCD.printNumI(Passnum6[k],d+=30,140);
    }
    d=140;
  }
  if(Press==7)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum7[k]=random(9);
      myGLCD.printNumI(Passnum7[k],d+=30,140);
    }
    d=140;
  }
  if(Press==8)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum8[k]=random(9);
      myGLCD.printNumI(Passnum8[k],d+=30,140);
    }
    d=140;
  }
  if(Press==9)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum9[k]=random(9);
      myGLCD.printNumI(Passnum9[k],d+=30,140);
    }
    d=140;
  }
  if(Press==10)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum10[k]=random(9);
      myGLCD.printNumI(Passnum10[k],d+=30,140);
    }
    d=140;
  }
  if(Press==11)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum11[k]=random(9);
      myGLCD.printNumI(Passnum11[k],d+=30,140);
    }
    d=140;
  }
  if(Press==12)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum12[k]=random(9);
      myGLCD.printNumI(Passnum12[k],d+=30,140);
    }
    d=140;
  }
  if(Press==13)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum13[k]=random(9);
      myGLCD.printNumI(Passnum13[k],d+=30,140);
    }
    d=140;
  }
  if(Press==14)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum14[k]=random(9);
      myGLCD.printNumI(Passnum14[k],d+=30,140);
    }
    d=140;
  }
  if(Press==15)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum15[k]=random(9);
      myGLCD.printNumI(Passnum15[k],d+=30,140);
    }
    d=140;
  }
  if(Press==16)
  {
    for(int k=0;k<4;k++)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(5); // Sets font to big
      Passnum16[k]=random(9);
      myGLCD.printNumI(Passnum16[k],d+=30,140);
    }
    d=140;
  }
}
void drawAffichageCorrect()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  
    if(pass==1)
    {
      myGLCD.setColor(VGA_GREEN); // Sets color to white
      myGLCD.setBackColor(VGA_GREEN);
      myGLCD.setTextSize(4); // Sets font to big
      myGLCD.setCursor(70,100);
      myGLCD.println("Mot de passe est correct");
    }
    if(pass==0)
    {
      myGLCD.setColor(VGA_RED); // Sets color to white
      myGLCD.setBackColor(VGA_RED);
      myGLCD.setTextSize(4); // Sets font to big
      myGLCD.setCursor(70,100);
      myGLCD.println("Mot de passe est incorrect");
    }
  
}
void drawPassScreen()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.setTextSize(2); // Sets font to big
  myGLCD.setCursor(70,10);
  myGLCD.println("Bienvenue dans Smart Parking");
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,32,480,32); // Draws the red line
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.setTextSize(2);
  myGLCD.setCursor(80,50);
  myGLCD.println("Entrez votre mot de passe");
  //button 1
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 30,  100 , 80 ,  150);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(40,108);
  myGLCD.println("1");
  //button 2
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 85,  100 , 135 ,  150);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(98,108);
  myGLCD.println("2");
  //button 3
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 140,  100 , 190 ,  150);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(146,108);
  myGLCD.println("3");
  //button 4
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 30,  155 , 80 ,  205);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(40,163);
  myGLCD.println("4");
  //button 5
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 85,  155 , 135 ,  205);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(98,163);
  myGLCD.println("5");
  //button 6
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 140,  155 , 190 ,  205);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(146,163);
  myGLCD.println("6");
  //button 7
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 30,  210 , 80 ,  260);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(40,218);
  myGLCD.println("7");
  //button 8
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 85,  210 , 135 ,  260);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(98,218);
  myGLCD.println("8");
  //button 9
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 140,  210 , 190 ,  260);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(146,218);
  myGLCD.println("9");
  //button 0
  myGLCD.setColor(VGA_AQUA); // Sets green color
  myGLCD.fillRoundRect( 85,  265 , 135 ,  315);// Button 1
  myGLCD.setTextSize(5); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(98,273);
  myGLCD.println("0");
  /* Button Valider
  myGLCD.setColor(VGA_GREEN); // Sets green color
  myGLCD.fillRoundRect( 140,  265 , 270 ,  315);// Button 1
  myGLCD.setTextSize(3); // Sets the font to big 
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(146,279);
  myGLCD.println("Valider");*/             
  //Delete
  myGLCD.setColor(VGA_RED); // Sets green color
  myGLCD.fillRoundRect( 30,  265 , 80 ,  315);// Button 1
  myGLCD.setTextSize(4); // Sets the font to big 
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);//White
  myGLCD.setCursor(45,275);
  myGLCD.println("X");
  
  
   
}
void setup() {
  Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.clrScr();
  drawHomeScreen();
  myServo.attach(Servopin);
  angle=myServo.read();
          if(angle==45)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
  myServoAv.attach(ServopinAv);
  myServoAv.write(0);
  myServoAp.attach(ServopinAp);
  myServoAp.write(0);
  pinMode(infr0,INPUT);
  pinMode(infr1,INPUT);
  pinMode(infr2,INPUT);
  pinMode(infr3,INPUT);
  pinMode(infr4,INPUT);
  pinMode(infr5,INPUT);
}

void loop()
{
  bool val0 = digitalRead(infr0);
  bool val1 = digitalRead(infr1);
  bool val2 = digitalRead(infr2);
  bool val3 = digitalRead(infr3);
  bool val4 = digitalRead(infr4);
  bool val5 = digitalRead(infr5);
  if((val0==HIGH)&&(statut0==0))
  {
    nbrCases+=1;
    delay(1000);
    if((x>=30) && (x<=69) && (y>=152) && (y<=190))
        {
          select1 = '1';
        }
        if((x>=79) && (x<=117) && (y>=152) && (y<=190))
        {    
          select2 = '1'; 
        }
        if((x>=128) && (x<=167) && (y>=152) && (y<=190))
        {
           select3 = '1';  
        }
        if((x>=177) && (x<=218) && (y>=152) && (y<=190))
        {
          select4 = '1'; 
        }
        if((x>=229) && (x<=270) && (y>=152) && (y<=190))
        {
           select5 = '1';  
        }
        if((x>=280) && (x<=320) && (y>=152) && (y<=190))
        {
           select6 = '1'; 
        }
        if((x>=330) && (x<=370) && (y>=152) && (y<=190))
        {
          select7 = '1'; 
        }
        if((x>=28) && (x<=67) && (y>=210) && (y<=247))
        {
          select8 = '1'; 
        }
        if((x>=79) && (x<=116) && (y>=210) && (y<=247))
        {
          select9 = '1';  
        }
        if((x>=127) && (x<=193) && (y>=210) && (y<=247))
        {
          select10 = '1'; 
        }
        if((x>=205) && (x<=269) && (y>=210) && (y<=247))
        {
          select11 = '1'; 
        }
        if((x>=271) && (x<=315) && (y>=210) && (y<=247))
        {
          select12 = '1'; 
        }
        if((x>=38) && (x<=98) && (y>=268) && (y<=300))
        {
          select13 = '1'; 
        }
        if((x>=111) && (x<=174) && (y>=268) && (y<=300))
        {
          select14 = '1'; 
        }
        if((x>=187) && (x<=250) && (y>=268) && (y<=300))
        {
          select15 = '1';
        }
        if((x>=262) && (x<=324) && (y>=268) && (y<=300))
        {
          select16 = '1'; 
        }
        myServoAv.write(90);
        myServoAp.write(0);
    statut0=1;
  }
  else if(val0==LOW)statut0=0;
  if((val5==HIGH)&&(statut5==0))
  {
    myServoAv.write(90);
    myServoAp.write(0);
    delay(1000);
    statut5=1;
  }
  else if(val5==LOW)  statut5=0;
  if((val1==HIGH)&&(statut1==0))
  {
    nbrCases--;
    delay(1000);
    statut1=1;
  }
  else if(val1==LOW)  statut1=0;
  if((val2==HIGH)&&(statut2==0))
  {
    nbrCases--;
    delay(1000);
    statut2=1;
  }
  else if(val2==LOW)statut2=0;
  if((val3==HIGH)&&(statut3==0))
  {
    nbrCases--;
    delay(1000);
    statut3=1;
  }
  else if(val3==LOW)statut3=0;
  if((val4==HIGH)&&(statut4==0))
  {
    nbrCases--;
    delay(1000);
    statut4=1;
  }
  else if(val4==LOW) statut4=0;
  
  if (Page == '0') 
  {
   TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE){
       y = map(p.x, 30, 960, 0, 320);
       x =map(p.y, 970, 20, 0, 480);
      if ((x>=31) && (x<=370) && (y>=130) && (y<=170)) 
      {
        Page = '1'; // Indicates that we are the first example
        myGLCD.clrScr(); // Clears the screen
        drawEnterScreen(); // It is called only once, because in the next iteration of the loop, this above if statement will be false so this funtion won't be called. This function will draw the graphics of the first example.
      }
      // If we press Interface de sortie
      if ((x>=35) && (x<=370) && (y>=180) && (y<=215)) {
       
        Page = '2';
        myGLCD.clrScr();
        drawExitScreen();
      }  
      // If we presse Nbr Des cases remplies
      if ((x>=24) && (x<=379) && (y>=225) && (y<=262)) {
        Page = '3';
        myGLCD.clrScr();
        drawCaseLibre();
      
     }
   
}
}
if (Page == '1')
   {
     TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE){
       y = map(p.x, 30, 960, 0, 320);
       x =map(p.y, 970, 20, 0, 480);
       if((x>=12) && (x<=72) && (y>=68) && (y<=98))
        {
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
        }
        if((x>=28) && (x<=67) && (y>=152) && (y<=190))
        {
          angle=myServo.read();
          if(angle==45)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(0);
          Press=1;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select1 = '1'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=79) && (x<=117) && (y>=152) && (y<=190))
        {
          angle=myServo.read();
          if(angle==45)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(0);
          Press=2;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);       
          Page = '0';
          select2 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=128) && (x<=167) && (y>=152) && (y<=190))
        {
          angle=myServo.read();
          if(angle==45)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(0);
          Press=3;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select3 = '0';  
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=177) && (x<=218) && (y>=152) && (y<=190))
        {
          angle=myServo.read();
          if(angle==45)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(0);
          Press=4;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select4 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=229) && (x<=270) && (y>=152) && (y<=190))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=45;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(45);
          Press=5;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          select5 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=280) && (x<=320) && (y>=152) && (y<=190))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=45;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(45);
          Press=6;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select6 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=330) && (x<=370) && (y>=152) && (y<=190))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=45;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(45);
          Press=7;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select7 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=28) && (x<=67) && (y>=210) && (y<=247))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=90;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(45);
          Press=8;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select8 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=79) && (x<=116) && (y>=210) && (y<=247))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=90;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(90);
          Press=9;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select9 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=127) && (x<=193) && (y>=210) && (y<=247))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=90;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(90);
          Press=10;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select10 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=205) && (x<=269) && (y>=210) && (y<=247))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=90;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(90);
          Press=11;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select11 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=271) && (x<=315) && (y>=210) && (y<=247))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=90;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(90);
          Press=12;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select12 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=38) && (x<=98) && (y>=268) && (y<=300))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(135);
          Press=13;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select13 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=111) && (x<=174) && (y>=268) && (y<=300))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(135);
          Press=14;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select14 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=187) && (x<=250) && (y>=268) && (y<=300))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(135);
          Press=15;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select15 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen(); 
        }
        if((x>=262) && (x<=324) && (y>=268) && (y<=300))
        {
          angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(135);
          Press=16;
          myGLCD.clrScr();
          drawAffichagePass();
          delay(4000);
          myServoAv.write(0);
          myServoAp.write(90);
          Page = '0';
          select16 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();  
        }
   }
}
if (Page == '2')
   {
     TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE){
       y = map(p.x, 30, 960, 0, 320);
       x =map(p.y, 970, 20, 0, 480);
        if((x>=30) && (x<=69) && (y>=152) && (y<=190))
        {
          Press_S=1;
          select1 = '0';
          Page='4';
          drawPassScreen();
        }
        if((x>=79) && (x<=117) && (y>=152) && (y<=190))
        {
          Press_S=2;
          select2 = '0'; 
          Page='4';
          drawPassScreen();
        }
        if((x>=128) && (x<=167) && (y>=152) && (y<=190))
        {
          select3 = '0'; 
          Press_S=3;
          Page='4';
          drawPassScreen();
        }
        if((x>=177) && (x<=218) && (y>=152) && (y<=190))
        {
          select4 = '0'; 
          Press_S=4;
          Page='4';
          drawPassScreen(); 
        }
        if((x>=229) && (x<=270) && (y>=152) && (y<=190))
        {
          select5 = '0'; 
          Press_S=5;
          Page='4';
          drawPassScreen(); 
        }
        if((x>=280) && (x<=320) && (y>=152) && (y<=190))
        {
           select6 = '0'; 
           Press_S=6;
          Page='4';
          drawPassScreen(); 
        }
        if((x>=330) && (x<=370) && (y>=152) && (y<=190))
        {
          select7 = '0'; 
          Press_S=7;
          Page='4';
          drawPassScreen(); 
        }
        if((x>=28) && (x<=67) && (y>=210) && (y<=247))
        {
          select8 = '0'; 
          Press_S=8;
          Page='4';
          drawPassScreen();
        }
        if((x>=79) && (x<=116) && (y>=210) && (y<=247))
        {
          select9 = '0'; 
          Press_S=9;
          Page='4';
          drawPassScreen();
        }
        if((x>=127) && (x<=193) && (y>=210) && (y<=247))
        {
          select10 = '0'; 
          Press_S=10;
          Page='4';
          drawPassScreen();
        }
        if((x>=205) && (x<=269) && (y>=210) && (y<=247))
        {
          select11 = '0'; 
          Press_S=11;
          Page='4';
          drawPassScreen();
        }
        if((x>=271) && (x<=315) && (y>=210) && (y<=247))
        {
          select12 = '0'; 
          Press_S=12;
          Page='4';
          drawPassScreen(); 
        }
        if((x>=38) && (x<=98) && (y>=268) && (y<=300))
        {
          select13 = '0'; 
          Press_S=13;
          Page='4';
          drawPassScreen(); 
        }
        if((x>=111) && (x<=174) && (y>=268) && (y<=300))
        {
          select14 = '0'; 
          Press_S=14;
          Page='4';
          drawPassScreen(); 
        }
        if((x>=187) && (x<=250) && (y>=268) && (y<=300))
        {
          select15 = '0'; 
          Press_S=15;
          Page='4';
          drawPassScreen();
        }
        if((x>=262) && (x<=324) && (y>=268) && (y<=300))
        {
          select16 = '0'; 
          Press_S=16;
          Page='4';
          drawPassScreen();
        }
     if((x>=12) && (x<=72) && (y>=68) && (y<=98))
        {
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
        }
   }
}
if (Page == '3')
  {
    TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE){
       y = map(p.x, 30, 960, 0, 320);
       x =map(p.y, 970, 20, 0, 480);
        if((x>=15) && (x<=79) && (y>=70) && (y<=110))
        {
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
        }
     }
}
if(Page == '4')
{
  TSPoint p = ts.getPoint();
        if(Press_S==1)
         {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
          PassE1[i]=1;
          i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE1[i]=2;
          i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE1[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE1[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE1[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE1[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE1[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE1[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE1[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE1[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select1 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE1[j]==Passnum1[j])||(PassE1[j]==Passurgent[j])){
            num++;
            select1='0';
          }
          else if((PassE1[j]!=Passnum1[j])&&(PassE1[j]!=Passurgent[j]))
          {
          pass=0;
          select1='1';
          }
        }
        if(num==4)
        pass=1;
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==45)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(0);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==2)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE2[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE2[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE2[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE2[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE2[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE2[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE2[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE2[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE2[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE2[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select2 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE2[j]==Passnum1[j])||(PassE2[j]==Passurgent[j])){
            pass=1;
            select2='0';
          }
          else if((PassE2[j]!=Passnum1[j])&&(PassE2[j]!=Passurgent[j]))
          {
          pass=0;
          select2='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==45)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(0);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==3)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE3[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE3[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE3[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE3[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE3[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE3[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE3[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE3[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE3[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE3[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select3 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE3[j]==Passnum3[j])||(PassE3[j]==Passurgent[j])){
            pass=1;
            select3='0';
          }
          else if((PassE3[j]!=Passnum3[j])&&(PassE3[j]!=Passurgent[j]))
          {
          pass=0;
          select3='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==45)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(0);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==4)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE4[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE4[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE4[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE4[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE4[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE4[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE4[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE4[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE4[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE4[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select4 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE4[j]==Passnum4[j])||(PassE4[j]==Passurgent[j])){
            pass=1;
            select4='0';
          }
          else if((PassE4[j]!=Passnum4[j])&&(PassE4[j]!=Passurgent[j]))
          {
          pass=0;
          select4='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==45)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=0;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(0);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==5)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE5[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE5[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE5[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE5[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE5[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE5[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE5[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE5[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE5[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE5[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select5 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE5[j]==Passnum5[j])||(PassE5[j]==Passurgent[j])){
            pass=1;
            select5='0';
          }
          else if((PassE5[j]!=Passnum5[j])&&(PassE5[j]!=Passurgent[j]))
          {
          pass=0;
          select5='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=45;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(45);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==6)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE6[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE6[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE6[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE6[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE6[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE6[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE6[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE6[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE6[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE6[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select6 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE6[j]==Passnum6[j])||(PassE6[j]==Passurgent[j])){
            pass=1;
            select6='0';
          }
          else if((PassE6[j]!=Passnum6[j])&&(PassE6[j]!=Passurgent[j]))
          {
          pass=0;
          select6='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=45;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(45);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==7)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE7[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE7[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE7[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE7[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE7[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE7[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE7[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE7[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE7[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE7[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select7 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE7[j]==Passnum7[j])||(PassE7[j]==Passurgent[j])){
            pass=1;
            select7='0';
          }
          else if((PassE7[j]!=Passnum7[j])&&(PassE7[j]!=Passurgent[j]))
          {
          pass=0;
          select7='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=45;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(45);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  
   else if(Press_S==8)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE8[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE8[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE8[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE8[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE8[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE8[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE8[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE8[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE8[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE8[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select8 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE8[j]==Passnum8[j])||(PassE8[j]==Passurgent[j])){
            pass=1;
            select8='0';
          }
          else if((PassE8[j]!=Passnum8[j])&&(PassE8[j]!=Passurgent[j]))
          {
          pass=0;
          select8='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=45;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=45;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(45);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==9)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE9[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE9[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE9[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE9[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE9[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE9[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE9[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE9[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE9[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE9[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select9 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE9[j]==Passnum9[j])||(PassE9[j]==Passurgent[j])){
            pass=1;
            select9='0';
          }
          else if((PassE9[j]!=Passnum9[j])&&(PassE9[j]!=Passurgent[j]))
          {
          pass=0;
          select9='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=90;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(90);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  
   else if(Press_S==10)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE10[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE10[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE10[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE10[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE10[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE10[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE10[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE10[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE10[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE10[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select10 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE10[j]==Passnum10[j])||(PassE10[j]==Passurgent[j])){
            pass=1;
            select10='0';
          }
          else if((PassE10[j]!=Passnum10[j])&&(PassE10[j]!=Passurgent[j]))
          {
          pass=0;
          select10='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=90;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(90);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==11)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE11[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE11[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE11[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE11[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE11[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE11[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE11[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE11[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE11[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE11[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select11 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE11[j]==Passnum11[j])||(PassE11[j]==Passurgent[j])){
            pass=1;
            select11='0';
          }
          else if((PassE11[j]!=Passnum11[j])&&(PassE11[j]!=Passurgent[j]))
          {
          pass=0;
          select11='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=90;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(90);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==12)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE12[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE12[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE12[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE12[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE12[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE12[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE12[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE12[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE12[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE12[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select12 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE12[j]==Passnum12[j])||(PassE12[j]==Passurgent[j])){
            pass=1;
            select12='0';
          }
          else if((PassE12[j]!=Passnum12[j])&&(PassE12[j]!=Passurgent[j]))
          {
          pass=0;
          select12='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=90;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==135)
          {
            for(int j=angle;j>=90;j--)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(90);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==13)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE13[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE13[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE13[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE13[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE13[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE13[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE13[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE13[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE13[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE13[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select13 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE13[j]==Passnum13[j])||(PassE13[j]==Passurgent[j])){
            pass=1;
            select13='0';
          }
          else if((PassE13[j]!=Passnum13[j])&&(PassE13[j]!=Passurgent[j]))
          {
          pass=0;
          select13='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(135);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
   else if(Press_S==14)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE14[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE14[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE14[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE14[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE14[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE14[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE14[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE14[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE14[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE14[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select14 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE14[j]==Passnum14[j])||(PassE14[j]==Passurgent[j])){
            pass=1;
            select14='0';
          }
          else if((PassE14[j]!=Passnum14[j])&&(PassE14[j]!=Passurgent[j]))
          {
          pass=0;
          select14='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(135);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
  else if(Press_S==15)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE15[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE15[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE15[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE15[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE15[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE15[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE15[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE15[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE15[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE15[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select15 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE15[j]==Passnum15[j])||(PassE15[j]==Passurgent[j])){
            pass=1;
            select15='0';
          }
          else if((PassE15[j]!=Passnum15[j])&&(PassE15[j]!=Passurgent[j]))
          {
          pass=0;
          select15='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(135);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
   else if(Press_S==16)
        {
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE&& i<4){
          delay(500);
        y1 = map(p.x, 30, 960, 0, 320);
        x1 = map(p.y, 970, 20, 0, 480);
       
        if((x1>=29) && (x1<=63) && (y1>=140) && (y1<=172))
       {
        PassE16[i]=1;
        i++;
       }
       else if((x1>=74) && (x1<=104) && (y1>=142) && (y1<=170))
       {
        PassE16[i]=2;
        i++;
       }
       else if((x1>=118) && (x1<=154) && (y1>=137) && (y1<=171))
       {
        PassE16[i]=3;
        i++;
       }
       else if((x1>=28) && (x1<=62) && (y1>=185) && (y1<=217))
       {
        PassE16[i]=4;
        i++;
       }
       else if((x1>=76) && (x1<=106) && (y1>=189) && (y1<=216))
       {
        PassE16[i]=5;
        i++;
       }
       else if((x1>=121) && (x1<=151) && (y1>=185) && (y1<=215))
       {
        PassE16[i]=6;
        i++;
       }
       else if((x1>=33) && (x1<=62) && (y1>=229) && (y1<=261))
       {
        PassE16[i]=7;
        i++;
       }
       else if((x1>=75) && (x1<=108) && (y1>=231) && (y1<=260))
       {
        PassE16[i]=8;
        i++;
       }
       else if((x1>=119) && (x1<=154) && (y1>=234) && (y1<=262))
       {
        PassE16[i]=9;
        i++;
       }
       else if((x1>=77) && (x1<=105) && (y1>=276) && (y1<=298))
       {
        PassE16[i]=0;
        i++;
       }
       else if((x1>=121) && (x1<=213) && (y1>=273) && (y1<=298))
       {
          Page = '0';
          select16 = '0'; 
          myGLCD.clrScr();
          drawHomeScreen();
       }
        if((x1>=31) && (x1<=64) && (y1>=273) && (y1<=296))
       {
        i--;
       }
       if(i>=4)
       {
        for(int j=0;j<4;j++)
        {
          if((PassE16[j]==Passnum16[j])||(PassE16[j]==Passurgent[j])){
            pass=1;
            select16='0';
          }
          else if((PassE16[j]!=Passnum16[j])&&(PassE16[j]!=Passurgent[j]))
          {
          pass=0;
          select16='1';
          }
        }
          i=0;
          myGLCD.clrScr();
          drawAffichageCorrect();
          delay(2000);
          if(pass==1)
          {
            angle=myServo.read();
          if(angle==0)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==45)
          {
            for(int j=angle;j<=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          else if(angle==90)
          {
            for(int j=angle;j>=135;j++)
            {
              myServo.write(j);
              delay(degree);
            }
          }
          myServo.write(135);
          }
          Page = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          
       }
     }
  }
}
}
