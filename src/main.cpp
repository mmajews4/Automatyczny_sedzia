#include "FS.h"
#include <LittleFS.h>
#include "structs.h"
#include "variables.h"
#include "INTERRUPTS.h"
#include "FUNKCJE.h"
#include "SD_.h"  
#include "LITTLEFS_FUNC.h"
#include "EEPROM.h"
#include "POMIAR.h"
#include "RANKING.h"
#include "initializations.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);         // Set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {

  Serial.begin(115200);

  Serial.println("Program wgrany");

  inicjuj_lcd();
  inicjuj_interrupty();
  inicjuj_LittleFS();

  //SD_test();


  //test_LittleFS();  // Test, usunac później
  //zapisz_we_flashu();
  //readFile(LITTLEFS, "/wyniki.csv");
  //readFile(LITTLEFS, "/ranking.txt");
  czytaj_z_flashu();
  
}

void loop() {

  while(1)                    // Wszystko jest w pętli aby można było wyjść z kodu za pomocą esc
  {                           // ------------------------------------------------------------------------    E K R A N   G L O W N Y   -----------
    if(idz_do_rankingu == 0){     // Flaga jest potrzebna aby można było przejść do rankingu po pomiarze
      wypisz_ekran_startowy();
      idz_do_rankingu = wybor("pomiar", "ranking", 1, 8, 6, 7, 0, 1);
      miejsce = 1;                                // Zmienna do trzymania wartości miejca wyświetlanego na górze LCD
    }

    if(idz_do_rankingu == 2)                      // -------------------------------------------------------   U S T A W I E N I A   -------------
    {
      lcd.clear();
      wyswietl_ustawienia();
      idz_do_rankingu = 0;
    }
    else if(idz_do_rankingu == 1)                 // ----------------------------------------------------------   R A N K I N G   ----------------
    {
      idz_do_rankingu = 0;                        // Flaga przejścia do rankingu

      while(1)
      {
        sprawdz_naladowanie(0, 0, 0);             // Sprawdzenie naladowania baterii

        wyswietl_ranking(miejsce);                // Wyświetlenie miejsca i czasu

        // wyświetlenie ESC z wyswiwtlania rankingu, jeżeli 0 to usuwanie nazwy lub ruch
        if(przesuwanie_nazwy(ranking_index[miejsce-1], ranking_index[miejsce])) break;

        if(ok_flag){
          ok_flag = 0;
          menu_wynikow_gracza(miejsce-1);      // W nim jest także usuwanie
        }

        ruch_rankingu(&miejsce);                  // Funkcja do przemieszczania się po rankingu
      }
    }
    else                                          // ----------------------------------------------------------    P O M I A R    ----------------
    {
      if(krancowka_on())                          // Te if-y służą do wychodzenia do menu glownego
        if(blad_krancowki()) break;               // Informuje że urządzenie nie jest gotowe do pomiaru

      typ_wynik temp_wynik;                       // Struct który do czasu zapisu potrzyma w sobie wyniki
      if(zliczanie_czasu(&temp_wynik)) break;     // Zliczenie czasu, z możliwością wyjścia przed otwarciem zaworu

      while(!ok_flag && !esc_flag){               // Wyświetlaj wynik dopóki urzytkownik czegoś nie zrobi  
        dummy_variable = millis();                // Musi coś robić bo inaczej program się zacina
      }  
      
      if(czy_zapisac()) break;                    // 1 jeżeli nie chcemy zapisać, wykona się tylko po nacisniecuy ESC

      if(wpisz_nazwe(&temp_wynik)) break;

      Serial.println("Zapis");
      
      if(zapisz(&temp_wynik)) break;              // Zapisanie wyniku w tablicy wyniki, ustawienie indexu rankingu oraz zapisanie na SD/FLASHu

      zapisz_we_flashu();
      
      idz_do_rankingu = 1;                        // Po pomyślnym zapisaniu, wyświetl wynik w rankingu
    }
  }
}
