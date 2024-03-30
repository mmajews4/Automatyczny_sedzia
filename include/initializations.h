#ifndef INITIALIZATIONS_H
#define INITIALIZATIONS_H

#include <Arduino.h>
#include "structs.h"

// Przykladowe losowe wyniki
typ_wynik wyniki[255] = {{14,0},                           // Na miejscu 0 w wynikach jest zapisana ilość wyników aby można było dodać nowy, następny wynik    
                          {14.532, "Mateusz_M"},            // Nie zmieniając ich kolejności fajnie będzie też zobaczyć historię wyników   !!! Jest bug że w tabeli wyników ta nazwa wyswietla się dwa razy
                          {4.376, "Kuba"},
                          {8.844, "Karol"},
                          {6.278, "Kamil"},
                          {6.424, "a"},
                          {5.845, "Karol"},
                          {112.567, "gosciu"},
                          {7.844, "Karol"},
                          {11.053, "Jan_Pawel_Adamczewsk"},
                          {12.466, "kolejny_wynik"},
                          {9.844, "Karol"},
                          {10.844, "Karol"},
                          {11.844, "Karol"},
                          {7.424, "a"}};

uint16_t ranking_index[100] = {2,6,4,5,9,10,1,7};

uint8_t idz_do_rankingu = 0;
uint8_t miejsce = 1; // Miejsce na którym wyświetlić ranking
int16_t naladowanie;
uint64_t dummy_variable = 0; 

uint8_t czytaj_z_SD = 0, czytaj_z_flash = 1, wifi_on = 0;

//char odczyt_wynikow_flash[250];

uint8_t ok_flag = 0, right_flag = 0, down_flag = 0, left_flag = 0, up_flag = 0, esc_flag = 0; //Interrupty
/*
char ekran[2][17] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'},
                    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'}};

char prevEkran[2][17] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'}};
*/
char klawiatura[2][13] = {{'a','b','c','d','e','f','g','h','i','j','k','l','\0'},
                          {'m','n','o','p','r','s','t','u','w','y','z','_','\0'}};
                       
char klawiatura_m[2][13] = {{'a','b','c','d','e','f','g','h','i','j','k','l','\0'},
                            {'m','n','o','p','r','s','t','u','w','y','z','_','\0'}};

char klawiatura_D[2][13] = {{'A','B','C','D','E','F','G','H','I','J','K','L','\0'},
                            {'M','N','O','P','R','S','T','U','W','Y','Z','_','\0'}};


byte miganie[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
  
byte backspace[] = {                
  B00000,
  B00000,
  B01000,
  B11111,
  B01001,
  B00011,
  B00000,
  B00000
};

byte caps_lock[] = {                  
  B00000,
  B00000,
  B00100,
  B01110,
  B11011,
  B01010,
  B01110,
  B00000
};

byte zapis[] = {                         
  B00000,
  B00001,
  B00010,
  B00100,
  B10100,
  B01000,
  B01000,
  B00000
};

byte lej[] = {
  B11111,
  B11111,
  B01110,
  B00100,
  B00100,
  B00100,
  B10100,
  B01000
};

byte bateria[3][8] ={{
  B01110,
  B11011,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
  B11111
},{
  B01110,
  B11011,
  B10001,
  B10001,
  B11111,
  B11111,
  B11111,
  B11111
},{
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
}};

#endif