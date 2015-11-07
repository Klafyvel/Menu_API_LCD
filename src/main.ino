#include <stdlib.h>
#include <stdio.h>

#include "menu.h"
#include "LiquidCrystal.h"


void riri();
void fifi();
void loulou();
void donald();
void picsou();
void clignoteLed();

LiquidCrystal lcd(11,10,5,4,3,2);
const char BP_UP = 6;
const char BP_DOWN = 7;
const char BP_OK = 8;

const char LED = 9;

Menu myMenu("Menu principal", &lcd, BP_UP, BP_DOWN, BP_OK);
Menu mySubMenu("Sous Menu", &lcd, BP_UP, BP_DOWN, BP_OK);

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);

    pinMode(LED, OUTPUT);

    pinMode(BP_OK, INPUT);
    pinMode(BP_UP, INPUT);
    pinMode(BP_DOWN, INPUT);
    digitalWrite(BP_OK, HIGH);
    digitalWrite(BP_UP, HIGH);
    digitalWrite(BP_DOWN, HIGH);

    myMenu.addItem(&riri, "riri");
    myMenu.addItem(&fifi, "fifi");
    myMenu.addItem(&loulou, "loulou");
    myMenu.addItem(&donald, "donald");
    myMenu.addItem(&clignoteLed, "Clignote led");
    myMenu.addSubMenu(&mySubMenu, "Mon sous Menu");
    myMenu.addItem(&picsou, "picsou");

    mySubMenu.addItem(&donald, "donald");
}

void loop()
{
    int action = myMenu.choose();
    if(action == -1)
    {
        lcd.clear();
        lcd.print("Vous avez quitte");
        lcd.setCursor(0,1);
        lcd.print("le menu.");
        delay(3000);
    }
    else
    {
        myMenu.action(action);
    }
}


void riri() 
{
    lcd.clear();
    lcd.print("RIRI !");
    delay(1000);
}
void fifi() 
{
    lcd.clear();
    lcd.print("FIFI !");
    delay(1000);
}
void loulou() 
{
    lcd.clear();
    lcd.print("LOULOU !");
    delay(1000);
}
void donald() 
{
    lcd.clear();
    lcd.print("DONALD !");
    delay(1000);
}
void picsou() 
{
    lcd.clear();
    lcd.print("PICSOU !");
    delay(1000);
}
void clignoteLed()
{
    Menu menu("Choix vitesse", &lcd, BP_UP, BP_DOWN, BP_OK);
    menu.addItem(NULL, "Mode 1");
    menu.addItem(NULL, "Mode 2");
    menu.addItem(NULL, "Mode 3");
    menu.addItem(NULL, "Mode 4");
    menu.addItem(NULL, "Mode 5");
    int v = menu.choose();
    while(v >= 0)
    {
        unsigned long fin = millis() + 5000;
        while (millis() < fin)
        {
            digitalWrite(LED, HIGH);
            delay((unsigned long)(v*100));
            digitalWrite(LED, LOW);
            delay((unsigned long)(v*100));
        }
        v = menu.choose();
    }
}
// void listMenu()
// {
//     char* items [] = {
//         "Foo",
//         "Bar",
//         "Thing"
//     };
//     int v;
//     Menu menu(items, 3);
//     do{
//         v = menu.choose();
//         lcd.print(v);
//     } while (v >= 0);
// }