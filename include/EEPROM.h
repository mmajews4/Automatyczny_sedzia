//#include "FS.h"
//#include <LittleFS.h>
//#include "variables.h"

void inicjuj_LittleFS(){

  if(!LittleFS.begin(FORMAT_LittleFS_IF_FAILED)){
    Serial.println("LittleFS Mount Failed");
    return;
  }
}

void zapisz_we_flashu(){

/*
  Zapis 15 wyników trwa około sekundy, co gdyby zapisać trzeba było 150 wyników...
  trzeba to jakoś skrócić np patrząc co się zmienia od ostatniego zapisu lub może jakieś inne pomysły
*/
 
  writeFile(LittleFS, "/wyniki.csv", (String(wyniki[0].czas)+ ",0\n").c_str()); 

  for(int i = 1; i <= wyniki[0].czas; i++)
  {
    appendFile(LittleFS, "/wyniki.csv", (String(wyniki[i].czas)+','+ String(wyniki[i].nazwa)+'\n').c_str());
    //appendFile(LittleFS, "/wyniki.csv", (String(wyniki[i].nazwa)+ '\n').c_str());
  }


  writeFile(LittleFS, "/ranking.txt", (String(ranking_index[0])+ ',').c_str());

  for(int j = 1; ranking_index[j] != 0; j++)
  {
    appendFile(LittleFS, "/ranking.txt", (String(ranking_index[j])+ ',').c_str());
  }
  appendFile(LittleFS, "/ranking.txt", "0,");

  //readFile(LittleFS, "/wyniki.csv");
  //listDir(LittleFS, "/", 3);

  //Serial.println(odczyt_wynikow_flash);

/*  listDir(LittleFS, "/", 3);
	writeFile(LittleFS, "/hello2.txt", "Hello2");
	listDir(LittleFS, "/", 1);
	deleteFile(LittleFS, "/mydir/hello2.txt");
	removeDir(LittleFS, "/mydir");*/
/*	listDir(LittleFS, "/", 1);
  writeFile(LittleFS, "/hello.txt", "Hello ");
  appendFile(LittleFS, "/hello.txt", "World!\r\n");
  readFile(LittleFS, "/hello.txt");*/
/*  renameFile(LittleFS, "/hello.txt", "/foo.txt");
  readFile(LittleFS, "/foo.txt");
  deleteFile(LittleFS, "/foo.txt");
  testFileIO(LittleFS, "/test.txt");
  deleteFile(LittleFS, "/test.txt");*/
}

void czytaj_z_flashu(){

  fs::FS &fs = LittleFS; 
  char* path = "/wyniki.csv";

  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return;
  }

  Serial.println("- read from file:");

  int lineCount = 0;                              // Wczytenie pliku od razu do tablicy wyników
  char bufor[8] = "";
  char* endptr;

  while (lineCount <= wyniki[0].czas && file.available()) {                    

    String line = file.readStringUntil(',');                                        // Czytam część przed przecinkiem, zamieniam ją na float i wpisuję do czasu
    line.toCharArray(bufor, sizeof(bufor));
    wyniki[lineCount].czas = strtof(bufor, &endptr);

    String line2 = file.readStringUntil('\n');
    line2.toCharArray(wyniki[lineCount].nazwa, sizeof(wyniki[lineCount].nazwa));

    lineCount++;
  }

  file.close();

  char* path2 = "/ranking.txt";

  Serial.printf("Reading file: %s\r\n", path2);

  File file2 = fs.open(path2);
  if(!file2 || file2.isDirectory()){
    Serial.println("- failed to open file for reading");
    return;
  }

  Serial.println("- read from file:");

  lineCount = 0;                              // Wczytenie pliku od razu do tablicy wyników
  char bufor2[5] = "";

  while (file2.available()) {                    

    String line = file2.readStringUntil(',');                                        // Czytam część przed przecinkiem, zamieniam ją na float i wpisuję do czasu
    line.toCharArray(bufor2, sizeof(bufor2));
    if(!strcmp(bufor2, "0,") || !strcmp(bufor2, "0,")){
      Serial.println("Doszedłem do ostatnego wpisu w rankingu");
      break;
    }
    ranking_index[lineCount] = atoi(bufor2);

    lineCount++;
  }
  Serial.println("Wyszedłem z while");

  file2.close();
}
