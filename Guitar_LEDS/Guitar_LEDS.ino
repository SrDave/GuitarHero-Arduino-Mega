#include <Wire.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "pitches.h"
#include "lcdFunciones.h"

#define BUTTON_PIN 5
#define ROTARY_PIN1 8
#define ROTARY_PIN2 7

#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10
#define BOTON1_PIN 2
#define BOTON2_PIN 3
#define BOTON3_PIN 4
#define BOTON4_PIN 6
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW



MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, 4);  // mx para llamar a las funciones de la matriz de leds

//Variables como el tamaño de las canciones, los estados de los botones o auxiliares.
const int buzzerPin = 9;
int SizeMario = sizeof(MarioTheme) / sizeof(MarioTheme[0]);
int SizeEvangelion = sizeof(Evangelion) / sizeof(Evangelion[0]);
int SizeSlihouette = sizeof(Slihouette) / sizeof(Slihouette[0]);
int SizeHarryPotter = sizeof(HarryPotter) / sizeof(HarryPotter[0]);
int ScoreWin = 1;
int ScoreLose = 1;
int ultima_col = mx.getColumnCount();
unsigned long previousMillis = 0;
unsigned long previous_Millis = 0;

int prevState = LOW;
bool button1Pressed = false;
bool button2Pressed = false;
bool button3Pressed = false;
bool button4Pressed = false;

short modo = 0;

int pos = 0;

int lastButtonState = HIGH;
int buttonState = LOW;
int lastRotaryState;
int rotaryState;
int rotaryValue;

//Lista de las canciones disponibles
char* canciones[] = { "MarioTheme **", "Evangelion ***", "Slihouette ****", "HarryPotter *" };


//DO y DO#
int Fila1[16] = { NOTE_C1, NOTE_CS1, NOTE_C2, NOTE_CS2, NOTE_C3, NOTE_CS3, NOTE_C4, NOTE_CS4, NOTE_C5, NOTE_CS5, NOTE_C6, NOTE_CS6, NOTE_C7, NOTE_CS7, NOTE_C8, NOTE_CS8 };
//RE y RE#
int Fila2[16] = { NOTE_D1, NOTE_DS1, NOTE_D2, NOTE_DS2, NOTE_D3, NOTE_DS3, NOTE_D4, NOTE_DS4, NOTE_D5, NOTE_DS5, NOTE_D6, NOTE_DS6, NOTE_D7, NOTE_DS7, NOTE_D8, NOTE_DS8 };
//MI
int Fila3[7] = { NOTE_E1, NOTE_E2, NOTE_E3, NOTE_E4, NOTE_E5, NOTE_E6, NOTE_E7 };
//FA y FA#
int Fila4[14] = { NOTE_F1, NOTE_FS1, NOTE_F2, NOTE_FS2, NOTE_F3, NOTE_FS3, NOTE_F4, NOTE_FS4, NOTE_F5, NOTE_FS5, NOTE_F6, NOTE_FS6, NOTE_F7, NOTE_FS7 };
//SOL y SOL#
int Fila5[14] = { NOTE_G1, NOTE_GS1, NOTE_G2, NOTE_GS2, NOTE_G3, NOTE_GS3, NOTE_G4, NOTE_GS4, NOTE_G5, NOTE_GS5, NOTE_G6, NOTE_GS6, NOTE_G7, NOTE_GS7 };
//LA y LA#
int Fila6[14] = { NOTE_A1, NOTE_AS1, NOTE_A2, NOTE_AS2, NOTE_A3, NOTE_AS3, NOTE_A4, NOTE_AS4, NOTE_A5, NOTE_AS5, NOTE_A6, NOTE_AS6, NOTE_A7, NOTE_AS7 };
//SI
int Fila7[7] = { NOTE_B1, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5, NOTE_B6, NOTE_B7 };

/*  4000 / (1 << (6 - falling_notes[i].dur) transforma los valores del 0 al 6 en ms que se ajustan a las notas.
 Si ponemos en el array [NOTE_C5, 3], el 3 es falling_notes[i].dur. 1 << (x) es 2**x. La formula queda así:
4000/ 2**(6-3) => 4000/ 2**3 => 4000 / 8 = 500 ms. 3 es una corchea.

La relación queda así:

6 => 4000 ms (redonda)
5 => 2000 ms (blanca)
4 => 1000 ms (negra)
3 => 500 ms (corchea)
2 => 250 ms (semicorchea)
1 => 125 ms (fusa) 
0 => 62 ms (semifusa)
*/

typedef struct {  //Definimos la estructura de la lista que vamos a crear con las notas
  int frec;
  int dur;
  int fila;
  int col;
} falling_note;

#define MAX_FALLING_NOTES 197
#define T_LED 120  //  tiempo (ms) en la que caerán en cascada las notas, si lo pones muy alto no casan bien las notas

falling_note falling_notes[MAX_FALLING_NOTES];
int falling_notes_count = 0;

//Esta función crea la lista a partir de el array de la canción
void falling_note_add(int frec, int dur) {
  if (falling_notes_count < MAX_FALLING_NOTES) {
    falling_notes[falling_notes_count].frec = frec;
    falling_notes[falling_notes_count].dur = dur;
    falling_notes[falling_notes_count].fila = NOTA(frec);
    falling_notes[falling_notes_count].col = 1 - dur;
    falling_notes_count++;
  }
}

void Score() {

  char buf[17];
  for (int r = 0; r < 5; r++) {  //Lo repite 5 veces
    lcdClear();
    sprintf(buf, "%3d WINS ", ScoreWin);  // Imprime la posición actual como cadena de texto
    lcdSetCursor(0, 0);                   // Se ubica en la primera línea
    lcdPrint(buf);
    delay(1000);  // Espera 1s
    lcdClear();
    sprintf(buf, "%3d LOSE ", ScoreLose);  // Imprime la posición actual como cadena de texto
    lcdSetCursor(0, 1);                    // Se ubica en la segunda línea
    lcdPrint(buf);                         // Imprime el texto
    delay(1000);
  }
}

int song_finished = 0;


//Función que lee la lista, pinta las notas y las reproduce, además de llamar a la función de botones
void falling_note_task() {
  mx.setColumn(26, B11111111);  //La linea fija que separa la matriz
  unsigned long currentMillis = millis();
  if ((currentMillis - previous_Millis) >= T_LED) {
    previous_Millis = currentMillis;
    for (int i = 0; i < falling_notes_count; i++) {
      if (falling_notes[i].frec == -1 && falling_notes[i].col == 32) {
        song_finished = 1;

      } else {
        //Esta variable será lo que dure el pitido de la nota, dependerá de el valor
        //que le pongamos en el array. Puedes ponerle un valor fijo para que suene uniforme
        //por ejempplo 250;
        int noteDuration = 4000 / (1 << (6 - falling_notes[i].dur));

        // Pintar nota
        mx.setPoint(falling_notes[i].fila, falling_notes[i].col, false);
        mx.setPoint(falling_notes[i].fila + 1, falling_notes[i].col, false);

        falling_notes[i].col++;
        for (int j = 0; j < falling_notes[i].dur; j++) {  //Repetimos/alargamos la nota según se duración

          mx.setPoint(falling_notes[i].fila, falling_notes[i].col + j, true);
          mx.setPoint(falling_notes[i].fila + 1, falling_notes[i].col + j, true);
        }

        /* if (falling_notes[i].col == 31) {                      // Esto hace que suene en la columna 31, para ver si esta bien la canción
        tone(buzzerPin, falling_notes[i].frec, noteDuration);  //Descomentala si qieres reproducirla automaticamente.
      }*/
        pressBoton(falling_notes[i].frec, falling_notes[i].fila, noteDuration);
      }
    }
  }
}

// Esta función reproduce la canción convertida en lista y noteDuration + t_LED es la velocidad
// con la que caerán las notas. Muy importante este valor para que suene bien y esten sincronizadas
void playSong(int song[][2], int size) {

  falling_note_add(song[0][0], song[0][1]);  // Añadir la primera nota a lista notas cayendo.
  int noteDuration = 4000 / (1 << (6 - song[0][1]));
  unsigned long previousMillis = millis();
  int idx = 1;
  song_finished = 0;
  while (!song_finished) {
    unsigned long currentMillis = millis();

    noteDuration = 4000 / (1 << (6 - song[idx][1]));                 // La suma con T_LED dará la separación entre notas
    if ((currentMillis - previousMillis) >= T_LED + noteDuration) {  // AQUI EL MOMENTO CRITICO
      idx++;
      falling_note_add(song[idx][0], song[idx][1]);  // Añadir resto de notas a lista de notas cayendo.

      previousMillis = currentMillis;
    }
    falling_note_task();
  }
  if (song_finished) {
    falling_notes_count = 0;
    modo = 0;
    Score();
  }
}


// Esta función reconoce las notas y da un valor para que pinte los leds en la fila deseada según la nota
int NOTA(int nota) {
  int filaNota;
  for (int i = 0; i < 16; i++) {
    if (Fila1[i] == nota) {
      filaNota = 0;
    }
  }
  for (int i = 0; i < 16; i++) {
    if (Fila2[i] == nota) {
      filaNota = 2;
    }
  }
  for (int i = 0; i < 7; i++) {
    if (Fila3[i] == nota) {
      filaNota = 4;
    }
  }
  for (int i = 0; i < 14; i++) {
    if (Fila4[i] == nota) {
      filaNota = 6;
    }
  }
  for (int i = 0; i < 14; i++) {
    if (Fila5[i] == nota) {
      filaNota = 0;
    }
  }
  for (int i = 0; i < 14; i++) {
    if (Fila6[i] == nota) {
      filaNota = 4;
    }
  }
  for (int i = 0; i < 7; i++) {
    if (Fila7[i] == nota) {
      filaNota = 6;
    }
  }
  return filaNota;
}


//Función que reonoce los estados de los botones y que reconoce si se ha pulsado bien
void pressBoton(int nota, int fila, int duration) {
  char buf[17];

  if (digitalRead(BOTON1_PIN) == LOW) {
    if (!button1Pressed) {
      //Si el led se enciende en la columna 27, 28, 29 ó 30 y en la fila 0:
      if ((mx.getPoint(0, 27) || mx.getPoint(0, 28) || mx.getPoint(0, 29) || mx.getPoint(0, 30)) && (fila == 0)) {
        button1Pressed = true;
        mx.setPoint(0, 31, true);
        mx.setPoint(1, 31, true);
        tone(buzzerPin, nota, duration);      // Suena la nota correcta
        sprintf(buf, "%3d WIN", ScoreWin++);  // Imprime el nombre de la canción seleccionada
        lcdSetCursor(0, 0);                   // Se ubica en la segunda línea
        lcdPrint(buf);                        // Imprime el nombre de la canción seleccionada

      } else if ((!mx.getPoint(0, 27) || !mx.getPoint(0, 28) || !mx.getPoint(0, 29) || !mx.getPoint(0, 30)) && (fila == 0)) {
        button1Pressed = true;
        mx.setPoint(0, 31, true);
        mx.setPoint(1, 31, true);
        tone(buzzerPin, NOTE_C1, 250);          // Suena la nota incorrecta
        sprintf(buf, "%3d LOSE", ScoreLose++);  // Imprime el nombre de la canción seleccionada
        lcdSetCursor(0, 1);                     // Se ubica en la segunda línea
        lcdPrint(buf);                          // Imprime el nombre de la canción seleccionada
      }
    }
  } else {
    if (button1Pressed) {
      button1Pressed = false;
      mx.setPoint(0, 31, false);
      mx.setPoint(1, 31, false);
      noTone(buzzerPin);
    }
  }
  if (digitalRead(BOTON2_PIN) == LOW) {
    if (!button2Pressed) {
      //Si el led se enciende en la columna 27, 28, 29 ó 30 y en la fila 2:
      if ((mx.getPoint(2, 27) || mx.getPoint(2, 28) || mx.getPoint(2, 29) || mx.getPoint(2, 30)) && (fila == 2)) {
        button2Pressed = true;
        mx.setPoint(2, 31, true);
        mx.setPoint(3, 31, true);
        tone(buzzerPin, nota, duration);      // Suena la nota correcta
        sprintf(buf, "%3d WIN", ScoreWin++);  // Imprime el nombre de la canción seleccionada
        lcdSetCursor(0, 0);                   // Se ubica en la segunda línea
        lcdPrint(buf);                        // Imprime el nombre de la canción seleccionada

      } else if ((!mx.getPoint(2, 27) || !mx.getPoint(2, 28) || !mx.getPoint(2, 29) || !mx.getPoint(2, 30)) && (fila == 2)) {
        button2Pressed = true;
        mx.setPoint(2, 31, true);
        mx.setPoint(3, 31, true);
        tone(buzzerPin, NOTE_C1, 250);          // Suena la nota incorrecta
        sprintf(buf, "%3d LOSE", ScoreLose++);  // Imprime el nombre de la canción seleccionada
        lcdSetCursor(0, 1);                     // Se ubica en la segunda línea
        lcdPrint(buf);                          // Imprime el nombre de la canción seleccionada
      }
    }
  } else {
    if (button2Pressed) {
      button2Pressed = false;
      mx.setPoint(2, 31, false);
      mx.setPoint(3, 31, false);
      noTone(buzzerPin);
    }
  }
  if (digitalRead(BOTON3_PIN) == LOW) {
    if (!button3Pressed) {
      //Si el led se enciende en la columna 27, 28, 29 ó 30 y en la fila 4:
      if ((mx.getPoint(4, 27) || mx.getPoint(4, 28) || mx.getPoint(4, 29) || mx.getPoint(4, 30)) && (fila == 4)) {
        button3Pressed = true;
        mx.setPoint(4, 31, true);
        mx.setPoint(5, 31, true);
        tone(buzzerPin, nota, duration);      // Suena la nota correcta
        sprintf(buf, "%3d WIN", ScoreWin++);  // Imprime el nombre de la canción seleccionada
        lcdSetCursor(0, 0);                   // Se ubica en la segunda línea
        lcdPrint(buf);                        // Imprime el nombre de la canción seleccionada

      } else if ((!mx.getPoint(4, 27) || !mx.getPoint(4, 28) || !mx.getPoint(4, 29) || !mx.getPoint(4, 30)) && (fila == 4)) {
        button3Pressed = true;
        mx.setPoint(4, 31, true);
        mx.setPoint(5, 31, true);
        tone(buzzerPin, NOTE_C1, 250);          // Suena la nota incorrecta
        sprintf(buf, "%3d LOSE", ScoreLose++);  // Imprime el nombre de la canción seleccionada
        lcdSetCursor(0, 1);                     // Se ubica en la segunda línea
        lcdPrint(buf);                          // Imprime el nombre de la canción seleccionada
      }
    }
  } else {
    if (button3Pressed) {
      button3Pressed = false;
      mx.setPoint(4, 31, false);
      mx.setPoint(5, 31, false);
      noTone(buzzerPin);
    }
  }
  if (digitalRead(BOTON4_PIN) == LOW) {
    if (!button4Pressed) {
      //Si el led se enciende en la columna 27, 28, 29 ó 30 y en la fila 6:
      if ((mx.getPoint(6, 27) || mx.getPoint(6, 28) || mx.getPoint(6, 29) || mx.getPoint(6, 30)) && (fila == 6)) {
        button4Pressed = true;
        mx.setPoint(6, 31, true);
        mx.setPoint(7, 31, true);
        tone(buzzerPin, nota, duration);      // Suena la nota incorrecta
        sprintf(buf, "%3d WIN", ScoreWin++);  // Imprime el nombre de la canción seleccionada
        lcdSetCursor(0, 0);                   // Se ubica en la segunda línea
        lcdPrint(buf);                        // Imprime el nombre de la canción seleccionada

      } else if ((!mx.getPoint(6, 27) || !mx.getPoint(6, 28) || !mx.getPoint(6, 29) || !mx.getPoint(6, 30)) && (fila == 6)) {
        button4Pressed = true;
        mx.setPoint(6, 31, true);
        mx.setPoint(7, 31, true);
        tone(buzzerPin, NOTE_C1, 250);          // Suena la nota incorrecta
        sprintf(buf, "%3d LOSE", ScoreLose++);  // Imprime el nombre de la canción seleccionada
        lcdSetCursor(0, 1);                     // Se ubica en la segunda línea
        lcdPrint(buf);                          // Imprime el nombre de la canción seleccionada
      }
    }
  } else {
    if (button4Pressed) {
      button4Pressed = false;
      mx.setPoint(6, 31, false);
      mx.setPoint(7, 31, false);
      noTone(buzzerPin);
    }
  }
}



//Para el menú y selección de canciones. Si el menú se hace en la matriz de leds.
void menu() {
  buttonState = digitalRead(BUTTON_PIN);   // Lee el estado del botón
  rotaryState = digitalRead(ROTARY_PIN1);  // Lee el estado de uno de los pines del codificador

  if (rotaryState != lastRotaryState) {             // Si el estado de uno de los pines del codificador ha cambiado
    if (digitalRead(ROTARY_PIN2) != rotaryState) {  // Si el otro pin del codificador está en un estado diferente, entonces se está girando en un sentido
      lcdClear();
      if (pos == 3) {
        pos = 0;  // Si está en la última posición, vuelve a la primera posición
      } else {
        pos++;  // Avanza a la siguiente posición
      }
    } else {  // Si el otro pin del codificador está en el mismo estado, entonces se está girando en el sentido contrario
      lcdClear();
      if (pos == 0) {
        pos = 3;  // Si está en la primera posición, retrocede a la última posición
      } else {
        pos--;  // Retrocede a la posición anterior
      }
    }
    lastRotaryState = rotaryState;  // Actualiza el último estado del pin del codificador
  }
  if (buttonState != lastButtonState) {  // Si el estado del botón ha cambiado
    if (buttonState == LOW) {            // Si el botón ha sido pulsado
      if (canciones[pos] == "MarioTheme **") {
        modo = 1;
      } else if (canciones[pos] == "Evangelion ***") {
        modo = 2;
      } else if (canciones[pos] == "Slihouette ****") {
        modo = 3;
      } else if (canciones[pos] == "HarryPotter *") {
        modo = 4;
      }
    }
    lastButtonState = buttonState;  // Actualiza el último estado del botón
  }
  char buf[17];
  //sprintf(buf,"Escoge cancion: "); // Imprime la posición actual del servo como cadena de texto
  lcdSetCursor(0, 0);            // Se ubica en la primera línea
  lcdPrint("Escoge cancion: ");  // Imprime el texto

  //sprintf(buf, "%s", canciones[pos]); // Imprime el nombre de la canción seleccionada
  lcdSetCursor(0, 1);        // Se ubica en la segunda línea
  lcdPrint(canciones[pos]);  // Imprime el nombre de la canción seleccionada
}

void preinicio(int cancion, int dura) {
  lcdClear();  //Limpiamos la pantalla lcd
  mx.clear();  //Limpiamos la matriz leds
  ScoreLose = 1;
  ScoreWin = 1;  //Iniciamos los puntos
  lcdSetCursor(0, 0);
  lcdPrint("    WIN");  //Pintamos WIN
  lcdSetCursor(0, 1);
  lcdPrint("    LOSE");     //Pintamos LOSE
  playSong(cancion, dura);  //Llamamos a la función para jugar
}


void setup() {
  pinMode(BOTON1_PIN, INPUT_PULLUP);
  pinMode(BOTON2_PIN, INPUT_PULLUP);
  pinMode(BOTON3_PIN, INPUT_PULLUP);
  pinMode(BOTON4_PIN, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  lcdSetup();                          // Inicializa el LCD
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // Configura el pin del botón como entrada con resistencia pull-up
  pinMode(ROTARY_PIN1, INPUT_PULLUP);  // Configura los pines del codificador rotativo como entradas con resistencia pull-up
  pinMode(ROTARY_PIN2, INPUT_PULLUP);
  lastRotaryState = digitalRead(ROTARY_PIN1);
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 0);  // Ajustar el brillo (0-15)
  mx.clear();                            //Limpiamos la matriz de leds
}

void loop() {
  //playSong(Slihouette, SizeSlihouette);
  if (modo == 0) {
    menu();
  } else if (modo == 1) {
    preinicio(MarioTheme, SizeMario);
  } else if (modo == 2) {
    preinicio(Evangelion, SizeEvangelion);
  } else if (modo == 3) {
    preinicio(Slihouette, SizeSlihouette);
  } else if (modo == 4) {
    preinicio(HarryPotter, SizeHarryPotter);
  }
}