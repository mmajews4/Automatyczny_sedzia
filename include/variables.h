#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//#include <String.h>
#include <stdlib.h>

#define OK 13                                 // Podmienić na interupty i flagi
#define RIGHT 14
#define DOWN 27
#define UP 26
#define LEFT 25
#define ESC 33
#define VALVE 4
#define BATTERY 35
#define CZAS_MIGANIA 550
#define HISTEREZA_MIGANIA 70
#define CZAS_PRZES_RANK 200
#define DLG_PRZES_NAZWY 8                   // Długość przesuwanej nazwy

#define FORMAT_LITTLEFS_IF_FAILED false     // Potrzebne do LittleFS gdy jest uruchomione za pierwszym razem

extern LiquidCrystal_I2C lcd;         // Set the LCD address to 0x27 for a 16 chars and 2 line display
//hw_timer_t *tim_cursor = NULL;


extern typ_wynik wyniki[255];

extern uint16_t ranking_index[100];

extern uint8_t miejsce; // Miejsce na którym wyświetlić ranking
extern int16_t naladowanie;

extern uint8_t czytaj_z_SD, czytaj_z_flash, wifi_on;

//char odczyt_wynikow_flash[250];

extern uint8_t ok_flag, right_flag, down_flag, left_flag, up_flag, esc_flag;
extern char klawiatura[2][13];                     
extern char klawiatura_m[2][13];
extern char klawiatura_D[2][13];
extern byte miganie[8];
extern byte backspace[8];
extern byte caps_lock[8];
extern byte zapis[8];
extern byte lej[8];
extern byte bateria[3][8];