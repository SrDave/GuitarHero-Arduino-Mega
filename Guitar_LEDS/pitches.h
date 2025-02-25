/*************************************************
   Public Constants
 *************************************************/

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

/*  4000 / (1 << (6 - falling_notes[i].dur) transforma los valores del 1 al 6 en ms que se ajustan a las notas.
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


//Silhouette

const int Slihouette[][2] = {
  { NOTE_B4, 1}, 
  { NOTE_A4, 1 },
  { NOTE_B4, 1 },
  { NOTE_D5, 2 },
  { NOTE_A4, 1 },
  { NOTE_B4, 1 },
  { NOTE_A4, 1 },
  { NOTE_B4, 1 },
  { NOTE_D5, 2 },
  { NOTE_A4, 1 },
  { NOTE_B4, 2 },
  //{ NOTE_G4, 4, 0 }, 
  { NOTE_D5, 3},
  { NOTE_A4, 3 },
  { NOTE_D5, 2 },
  { NOTE_E5, 3 },
  { NOTE_A4, 3},
  { NOTE_E5, 2},
  { NOTE_FS5, 3 },
  { NOTE_G5, 3 },
  { NOTE_FS5, 1 },
  { NOTE_E5, 1 },
  { NOTE_D5, 2 },
  { NOTE_G5, 2 },
  { NOTE_FS5, 2},
//
  { NOTE_D5, 2 },
  { NOTE_G5, 2 },
  { NOTE_FS5, 2 },
  { NOTE_D5, 4 },
  { NOTE_G5, 2 },
  { NOTE_FS5, 3 },
  { NOTE_D5, 2 },
  { NOTE_E5, 3 },
  { NOTE_FS5, 3 },
  { NOTE_CS5, 2 },

  { NOTE_FS5, 2  },
  { NOTE_D5, 2 },
  { NOTE_E5, 2 },
  { NOTE_FS5, 4 },

  //{ NOTE_D5, 1, 0 },

  { NOTE_D5, 2 },
  { NOTE_FS5, 1 },
  { NOTE_FS5, 1 },
  { NOTE_E5, 1 },
  { NOTE_D5, 1 },
  { NOTE_E5, 2 },
  { NOTE_A5, 1 },
  { NOTE_A5, 3 },

  //{ NOTE_D5, 4, 0 },

  { NOTE_E5, 2 },
  { NOTE_CS5, 2 },
  { NOTE_E5, 2 },
  { NOTE_D5, 2 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2  },
  { NOTE_D5, 2 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2 },
  { NOTE_D5, 3},

  //{ NOTE_E4, 3, 0 },

  { NOTE_D5, 3 },
  { NOTE_CS5, 2 },
  { NOTE_D5, 2 },
  { NOTE_E5, 2 },
  { NOTE_D5, 2 },
  { NOTE_FS5, 2 },
  { NOTE_D5, 2 },
  { NOTE_E5, 2 },
  { NOTE_FS5, 4 },

  //{ NOTE_D5, 3, 0 },

  { NOTE_D5, 1 },
  { NOTE_D5, 1 },
  { NOTE_FS5, 2 },
  { NOTE_E5, 1 },
  { NOTE_D5, 1 },
  { NOTE_E5, 2 },
  { NOTE_A5, 1 },
  { NOTE_A5, 3 },

  //{ NOTE_D5, 4, 0 },

  { NOTE_E5, 2 },
  { NOTE_CS5, 2 },
  { NOTE_E5, 2 },
  { NOTE_D5, 2 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2 },
  { NOTE_D5, 3 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2 },

  { NOTE_D5, 2},

  // { NOTE_CS4, 3, 0 },

  { NOTE_D5, 3  },
  { NOTE_CS5, 2  },
  { NOTE_D5, 2 },
  { NOTE_E5, 2 },
  { NOTE_D5, 2 },
  
  //{ NOTE_CS5, 4, 0 },

  { NOTE_B4, 1 },
  { NOTE_FS5, 1 },
  { NOTE_FS5, 2 },
  { NOTE_D5, 1 },

  //{ NOTE_CS5, 4, 0 },

  { NOTE_D5, 1 },
  { NOTE_FS5, 1 },
  { NOTE_FS5, 2 },
  { NOTE_D5, 1 },

  //{ NOTE_FS4, 4, 0 },

  { NOTE_D5, 1 },
  { NOTE_B5, 1 },
  { NOTE_FS5, 2 },
  { NOTE_D5, 2 },
  { NOTE_B4, 2 },
  { NOTE_CS5, 2 },
//
  //{ NOTE_FS4, 4, 0 },

  { NOTE_D5, 3 },
  { NOTE_D5, 3 },
  { NOTE_CS5, 2},
  { NOTE_D5, 2},
  //{ NOTE_B3, 4, 0 },
  { NOTE_E5, 2 },
  { NOTE_E5, 3 },
  { NOTE_E5, 3 },
  { NOTE_FS5, 2},
  { NOTE_E5, 2 },
  { NOTE_D5, 2 },
  { NOTE_E5, 2 },
  { NOTE_D5, 2 },
  { NOTE_A4, 2 },
  { NOTE_D5, 2 },
  { NOTE_FS5, 1 },
  { NOTE_FS5, 2 },
  { NOTE_E5, 1 },
  { NOTE_D5, 1 },
  { NOTE_E5, 3 },
  { NOTE_E5, 2 },
  { NOTE_A4, 2 },
  { NOTE_CS5, 2 },
  { NOTE_E5, 2 },
  { NOTE_G5, 2 },
  { NOTE_FS5, 1 },
  { NOTE_E5, 1 },
  { NOTE_FS5, 2 },
  { NOTE_E5, 2 },
  { NOTE_D5, 2 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2 },
  { NOTE_D5, 3 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2 },
  { NOTE_D5, 2 },
  { NOTE_D5, 3 },

  { NOTE_CS5, 2 },
  { NOTE_D5, 2 },
  { NOTE_E5, 2 },
  { NOTE_FS5, 2 },
  { NOTE_D5, 2 },
  { NOTE_A4, 2 },
  { NOTE_D5, 2 },
  { NOTE_FS5, 1 },
  { NOTE_FS5, 2 },
  { NOTE_E5, 1 },
  { NOTE_D5, 1 },
  { NOTE_E5, 2 },
  { NOTE_E5, 2},
  { NOTE_A4, 2 },
  { NOTE_CS5, 2 },
  { NOTE_E5, 2 },
  { NOTE_G5, 2 },
  { NOTE_FS5, 1},
  { NOTE_FS5, 1},
  { NOTE_FS5, 2 },
  { NOTE_E5, 2 },
  { NOTE_D5, 2 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2 },
  { NOTE_D5, 2 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2 },
  { NOTE_D5, 2 },
  { NOTE_D5, 3 },

  { NOTE_CS5, 1 },
  { NOTE_A5, 2 },
  { NOTE_E5, 2 },
  { NOTE_FS5, 2 },
  { NOTE_D5, 2 },
  { NOTE_A5, 2 },
  
  //{ NOTE_FS4, 4, 0 },

  { NOTE_D5, 2 },
  { NOTE_FS5, 1 },
  { NOTE_FS5, 2 },
  { NOTE_E5, 1  },
  { NOTE_D5, 1  },
  { NOTE_E5, 2 },
  { NOTE_E5, 2  },
  { NOTE_A4, 2},
  { NOTE_CS5, 2 },
  { NOTE_E5, 2 },
  { NOTE_G5, 2 },
  { NOTE_A5, 2 },
  { NOTE_FS5, 2 },
  { NOTE_E5, 2 },
  { NOTE_D5, 2 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2 },
  { NOTE_D5, 2 },
  { NOTE_B5, 2 },
  { NOTE_A5, 2 },
  { NOTE_D5, 2},
  { NOTE_D5, 3 },
  { -1, 6 },
};

//Canción Mario Bros.

const int MarioTheme[][2] = {
  { NOTE_E5, 1},
  { NOTE_E5, 2},
  { NOTE_E5, 2},
  { NOTE_C5, 1},
  { NOTE_E5, 2},
  { NOTE_G5, 3},
  { NOTE_G4, 3},

  { NOTE_C5, 3},
  { NOTE_G4, 3},
  { NOTE_E4, 3},
  { NOTE_A4, 2},
  { NOTE_B4, 2},
  { NOTE_AS4, 1},
  { NOTE_A4, 2},
  { NOTE_G4, 1},
  { NOTE_E5, 1},
  { NOTE_G5, 1},
  { NOTE_A5, 2},
  { NOTE_F5, 1},
  { NOTE_G5, 2},
  { NOTE_E5, 2},
  { NOTE_C5, 1},
  { NOTE_D5, 1},
  { NOTE_B4, 3},

  { NOTE_C5, 3},
  { NOTE_G4, 3},
  { NOTE_E4, 3},
  { NOTE_A4, 2},
  { NOTE_B4, 2},
  { NOTE_AS4, 1},
  { NOTE_A4, 2},
  { NOTE_G4, 1},
  { NOTE_E5, 1},
  { NOTE_G5, 1},
  { NOTE_A5, 2},
  { NOTE_F5, 1},
  { NOTE_G5, 2},
  { NOTE_E5, 2},
  { NOTE_C5, 1},
  { NOTE_D5, 1},
  { NOTE_B4, 3},

  { NOTE_G5, 1},
  { NOTE_FS5, 1},
  { NOTE_F5, 2},
  { NOTE_DS5, 1},
  { NOTE_E5, 2},
  { NOTE_GS4, 1},
  { NOTE_A4, 2},
  { NOTE_C5, 2},
  { NOTE_A4, 1},
  { NOTE_C5, 1},
  { NOTE_D5, 3},
  { NOTE_G5, 1},
  { NOTE_FS5, 2},
  { NOTE_F5, 2},
  { NOTE_DS5, 1},
  { NOTE_E5, 2},
  { NOTE_C6, 1},
  { NOTE_C6, 2},
  { NOTE_C6, 4},

  { NOTE_G5, 1},
  { NOTE_FS5, 1},
  { NOTE_F5, 2},
  { NOTE_DS5, 1},
  { NOTE_E5, 2},
  { NOTE_GS4, 1},
  { NOTE_A4, 2},
  { NOTE_C5, 2},
  { NOTE_A4, 1},
  { NOTE_C5, 1},
  { NOTE_D5, 2},
  { NOTE_DS5, 2},
  { NOTE_D5, 3},
  { NOTE_C5, 4},

  { NOTE_E5, 1},
  { NOTE_C5, 2},
  { NOTE_G4, 3},
  { NOTE_GS4, 2},
  { NOTE_A4, 1},
  { NOTE_F5, 2},
  { NOTE_F5, 1},
  { NOTE_A4, 3},
  { NOTE_B4, 1},
  { NOTE_A5, 2},
  { NOTE_A5, 1},
  { NOTE_A5, 1},
  { NOTE_G5, 1},
  { NOTE_F5, 2},
  { NOTE_E5, 1},
  { NOTE_C5, 2},
  { NOTE_A4, 1},
  { NOTE_G4, 3},
  { NOTE_E5, 1},
  { NOTE_C5, 2},
  { NOTE_G4, 3},
  { NOTE_GS4, 2},
  { NOTE_A4, 1},
  { NOTE_F5, 2},
  { NOTE_F5, 1},
  { NOTE_A4, 3},
  { NOTE_B4, 1},
  { NOTE_F5, 2},
  { NOTE_F5, 1},
  { NOTE_F5, 1},
  { NOTE_E5, 2},
  { NOTE_D5, 1},
  { NOTE_C5, 1},
  { NOTE_E4, 1},
  { NOTE_E4, 2},
  { NOTE_C4, 3},
  { -1, 3},

};

//Evangelion

const int Evangelion[][2] = {

  { NOTE_C5, 3},
  { NOTE_DS5, 3},
  { NOTE_F5, 3},
  { NOTE_DS5, 2},
  { NOTE_F5, 1},
  { NOTE_F5, 3},
  { NOTE_AS5, 1},
  { NOTE_GS5, 1},
  { NOTE_G5, 2},
  { NOTE_F5, 3},
  { NOTE_G5, 2},
  { NOTE_G5, 3},
  { NOTE_AS5, 3},
  { NOTE_C6, 2},
  { NOTE_F5, 2},
  { NOTE_DS5, 1},
  { NOTE_AS5, 3},
  { NOTE_G5, 1},
  { NOTE_AS5, 1},
  { NOTE_AS5, 3},
  { NOTE_C6, 4},
   
  { NOTE_DS5, 2}, //SEMI
  { NOTE_AS4, 1},
  { NOTE_AS4, 3},
  { NOTE_DS5, 2},
  { NOTE_DS5, 2},
  { NOTE_F5, 2},
  { NOTE_AS4, 2},
  { NOTE_AS4, 3},
  { NOTE_AS4, 2},
  { NOTE_G5, 2},
  { NOTE_GS5, 3},
  { NOTE_G5, 2},
  { NOTE_F5, 3},
  { NOTE_DS5, 2},
  { NOTE_F5, 1},
  { NOTE_G5, 2},
  { NOTE_GS5, 3},
  { NOTE_G5, 1},
  { NOTE_C5, 3},
  { NOTE_C5, 1},
  { NOTE_D5, 1},
  { NOTE_DS5, 3},
  { NOTE_DS5, 3},
  { NOTE_D5, 2},
  { NOTE_D5, 3},
  { NOTE_DS5, 1},
  { NOTE_F5, 1},
  { NOTE_GS5, 3},
  { NOTE_G5, 3},
  { NOTE_F5, 2},
  { NOTE_DS5,3},
  { NOTE_G5, 1},
  { NOTE_G5, 2},
  { NOTE_F5, 2},
  { NOTE_E5, 1},
  { NOTE_F5, 3},
  { NOTE_C5, 2},
  { NOTE_C5, 3},
  { NOTE_D5, 1},
  { NOTE_D5, 3},

  { NOTE_DS5, 1},
  { NOTE_AS4, 1},
  { NOTE_AS4, 3},
  { NOTE_DS5, 2},
  { NOTE_DS5, 3},
  { NOTE_F5, 2},
  { NOTE_AS4, 2},
  { NOTE_AS4, 3},
  { NOTE_AS4, 1},
  { NOTE_G5, 2},
  { NOTE_GS5, 3},
  { NOTE_G5, 1},
  { NOTE_F5, 2},
  { NOTE_DS5, 2},
  { NOTE_F5, 2},
  { NOTE_G5, 2},
  { NOTE_GS5, 3},
  { NOTE_G5, 1},
  { NOTE_C5, 3},
  { NOTE_C5, 1},
  { NOTE_D5, 1},
  { NOTE_DS5, 3},
  { NOTE_DS5, 3},
  { NOTE_D5, 1},
  { NOTE_D5, 3},
  { NOTE_DS5, 1},
  { NOTE_F5, 1},
  { NOTE_GS5, 3},
  { NOTE_G5, 3},
  { NOTE_F5, 2},
  { NOTE_DS5, 3},
  { NOTE_G5, 2},
  { NOTE_G5, 3},
  { NOTE_F5, 3},
  { NOTE_E5, 2},
  { NOTE_F5, 3},
  { NOTE_G5, 2},
  { NOTE_GS5, 2},
  { NOTE_G5, 3},
  { NOTE_B4, 2},
  { NOTE_A4, 1},
  { NOTE_B4, 2},

  { NOTE_DS5, 2},
  { NOTE_DS5, 2},
  { NOTE_D5, 1},
  { NOTE_DS5, 2},
  { NOTE_DS5, 2},
  { NOTE_D5, 2},
  { NOTE_F5, 2},
  { NOTE_F5, 2},
  { NOTE_DS5, 1},
  { NOTE_D5, 2},
  { NOTE_C5, 2},
  { NOTE_D5, 1},
  { NOTE_DS5, 2},
  { NOTE_DS5, 2},
  { NOTE_D5, 1},
  { NOTE_F5, 2},
  { NOTE_D5, 2},
  { NOTE_C5, 1},
  { NOTE_AS4, 4},
  { NOTE_DS5, 2},
  { NOTE_DS5, 2},
  { NOTE_D5, 1},
  { NOTE_DS5, 2},
  { NOTE_DS5, 2},
  { NOTE_D5, 1},
  { NOTE_F5, 2},
  { NOTE_F5, 2},
  { NOTE_DS5, 1},
  { NOTE_D5, 2},
  { NOTE_DS5, 2},
  { NOTE_F5, 1},
  { NOTE_G5, 2},
  { NOTE_GS5, 2},
  { NOTE_G5, 1},
  { NOTE_F5, 2},
  { NOTE_DS5, 2},
  { NOTE_F5, 1},
  { NOTE_G5, 2},
  { NOTE_G4, 3},
  { NOTE_G4, 2},
  { NOTE_A4, 2},
  { NOTE_B4, 1},

  { NOTE_C5, 3},
  { NOTE_DS5, 3},
  { NOTE_F5, 2},
  { NOTE_DS5, 2},
  { NOTE_F5, 1},
  { NOTE_F5, 1},
  { NOTE_F5, 1},
  { NOTE_AS5, 1},
  { NOTE_GS5, 1},
  { NOTE_G5, 1},
  { NOTE_F5, 1},
  { NOTE_G5, 2},
  { NOTE_G5, 3},
  { NOTE_AS5, 3},
  { NOTE_C6, 2},
  { NOTE_F5, 2},
  { NOTE_DS5, 1},
  { NOTE_D5, 1},
  { NOTE_D5, 1},
  { NOTE_C5, 1},
  { NOTE_D5, 1},
  { NOTE_F5, 1},
  { NOTE_DS5, 2},
  { NOTE_DS5, 3},

  { NOTE_C5, 2},
  { NOTE_DS5, 3},
  { NOTE_F5, 2},
  { NOTE_DS5, 3},
  { NOTE_F5, 1},
  { NOTE_F5, 1},
  { NOTE_F5, 1},
  { NOTE_AS5, 1},
  { NOTE_GS5, 1},
  { NOTE_G5, 1},
  { NOTE_F5, 1},
  { NOTE_G5, 2},
  { NOTE_G5, 3},
  { NOTE_AS5, 3},
  { NOTE_C6, 2},
  { NOTE_F5, 2},
  { NOTE_DS5, 1},
  { NOTE_AS5, 1},
  { NOTE_AS5, 1},
  { NOTE_G5, 1},
  { NOTE_AS5,2},
  { NOTE_AS5,2},
  { NOTE_C6, 4},
  { -1, 4},

};

//Harry_Potter

const int HarryPotter[][2] = {

  {NOTE_B4, 2},
  {NOTE_E5, 3},
  {NOTE_G5, 2},
  {NOTE_FS5, 1},
  {NOTE_E5, 3},
  {NOTE_B5, 2},
  {NOTE_A5, 4},
  {NOTE_FS5, 4},
  {NOTE_E5, 3},
  {NOTE_G5, 1},
  {NOTE_FS5, 1},
  {NOTE_DS5, 3},
  {NOTE_F5, 2},
  {NOTE_B4, 4},
  {NOTE_B4, 2},
  {NOTE_E5, 3},
  {NOTE_G5, 1},
  {NOTE_FS5, 1},
  {NOTE_E5, 3},
  {NOTE_B5, 2},
  {NOTE_D6, 3},
  {NOTE_CS6, 2},
  {NOTE_C6, 3},
  {NOTE_GS5, 2},
  {NOTE_C6, 3},
  {NOTE_B5, 1},
  {NOTE_AS5, 1},
  {NOTE_AS4, 3},
  {NOTE_G5, 2},
  {NOTE_E5, 5},
  {NOTE_G5, 2},
  {NOTE_B5, 3},
  {NOTE_G5, 2},
  {NOTE_B5, 3},
  {NOTE_G5, 2},
  {NOTE_C6, 3},
  {NOTE_B5, 2},
  {NOTE_AS5, 3},
  {NOTE_FS5, 2},
  {NOTE_G5, 3},
  {NOTE_B5, 1},
  {NOTE_AS5, 2},
  {NOTE_AS4, 3},
  {NOTE_B4, 2},
  {NOTE_B5, 5},
  {NOTE_G5, 2},
  {NOTE_B5, 3},
  {NOTE_G5, 2},
  {NOTE_B5, 3},
  {NOTE_G5, 2},
  {NOTE_D6, 3},
  {NOTE_CS6, 2},
  {NOTE_C6, 3},
  {NOTE_GS5, 2},
  {NOTE_C6, 3},
  {NOTE_B5, 1},
  {NOTE_AS5, 1},
  {NOTE_AS4, 3},
  {NOTE_G5, 2},
  {NOTE_E5, 4},
  {NOTE_E5, 4},
  {-1, 2},



};