#include <Arduino.h>
#include <Wire.h>
#include <Colorduino.h>

// A lookup table for the coordinate mapping we built.
int cubeMap[8][8][3] = {
  // Colorduino col = 0
  {{0,0,3}, {0,0,2}, {0,0,1}, {0,0,0}, {2,0,3}, {2,0,2}, {2,0,1}, {2,0,0}},
  // Colorduino col = 1
  {{0,1,3}, {0,1,2}, {0,1,1}, {0,1,0}, {2,1,3}, {2,1,2}, {2,1,1}, {2,1,0}},
  // Colorduino col = 2
  {{0,2,3}, {0,2,2}, {0,2,1}, {0,2,0}, {2,2,3}, {2,2,2}, {2,2,1}, {2,2,0}},
  // Colorduino col = 3
  {{0,3,3}, {0,3,2}, {0,3,1}, {0,3,0}, {2,3,3}, {2,3,2}, {2,3,1}, {2,3,0}},
  // Colorduino col = 4
  {{1,3,3}, {1,3,2}, {1,3,1}, {1,3,0}, {3,3,3}, {3,3,2}, {3,3,1}, {3,3,0}},
  // Colorduino col = 5
  {{1,2,3}, {1,2,2}, {1,2,1}, {1,2,0}, {3,2,3}, {3,2,2}, {3,2,1}, {3,2,0}},
  // Colorduino col = 6
  {{1,1,3}, {1,1,2}, {1,1,1}, {1,1,0}, {3,1,3}, {3,1,2}, {3,1,1}, {3,1,0}},
  // Colorduino col = 7
  {{1,0,3}, {1,0,2}, {1,0,1}, {1,0,0}, {3,0,3}, {3,0,2}, {3,0,1}, {3,0,0}}
};

void setCubePixel(int X, int Y, int Z, int R, int G, int B) {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (cubeMap[x][y][0] == X && cubeMap[x][y][1] == Y && cubeMap[x][y][2] == Z) {
        Colorduino.SetPixel(x, y, R, G, B);
        return;
      }
    }
  }
}

void clearCube() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      Colorduino.SetPixel(x, y, 0, 0, 0);
    }
  }
}

void drawFrame(int frameNumber) {
  clearCube();
  
  if (frameNumber == 1) { // 1: (xy3) on
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        setCubePixel(x, y, 3, random(256), random(256), random(256));
      }
    }
  } else if (frameNumber == 2) { // 2: (0y3) off (3y2) on
    for (int x = 1; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        setCubePixel(x, y, 3, random(256), random(256), random(256));
      }
    }
    for (int y = 0; y < 4; y++) {
      setCubePixel(3, y, 2, random(256), random(256), random(256));
    }
  } else if (frameNumber == 3) { // 3: (1y3) off (3y1) on
    for (int x = 2; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        setCubePixel(x, y, 3, random(256), random(256), random(256));
      }
    }
    for (int y = 0; y < 4; y++) {
      setCubePixel(3, y, 2, random(256), random(256), random(256));
      setCubePixel(3, y, 1, random(256), random(256), random(256));
    }
  } else if (frameNumber == 4) { // 4: (2y3) off (3y0) on
    for (int x = 3; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        setCubePixel(x, y, 3, random(256), random(256), random(256));
      }
    }
    for (int y = 0; y < 4; y++) {
      setCubePixel(3, y, 2, random(256), random(256), random(256));
      setCubePixel(3, y, 1, random(256), random(256), random(256));
      setCubePixel(3, y, 0, random(256), random(256), random(256));
    }
  } else if (frameNumber == 5) { // 5: (33z) off (20z) on
    for (int y = 0; y < 3; y++) {
      for (int z = 0; z < 4; z++) {
        setCubePixel(3, y, z, random(256), random(256), random(256));
      }
    }
    for (int x = 2; x < 4; x++) {
      for (int z = 0; z < 4; z++) {
        setCubePixel(x, 0, z, random(256), random(256), random(256));
      }
    }
  } else if (frameNumber == 6) { // 6: (32z) off (10z) on
    for (int y = 0; y < 2; y++) {
      for (int z = 0; z < 4; z++) {
        setCubePixel(3, y, z, random(256), random(256), random(256));
      }
    }
    for (int x = 1; x < 4; x++) {
      for (int z = 0; z < 4; z++) {
        setCubePixel(x, 0, z, random(256), random(256), random(256));
      }
    }
  } else if (frameNumber == 7) { // 7: (31z) off (00z) on
    for (int y = 0; y < 1; y++) {
      for (int z = 0; z < 4; z++) {
        setCubePixel(3, y, z, random(256), random(256), random(256));
      }
    }
    for (int x = 0; x < 4; x++) {
      for (int z = 0; z < 4; z++) {
        setCubePixel(x, 0, z, random(256), random(256), random(256));
      }
    }
  } else if (frameNumber == 8) { // 8: (x03) off (x10) on
    for (int x = 0; x < 4; x++) {
      for (int z = 0; z < 3; z++) {
        setCubePixel(x, 0, z, random(256), random(256), random(256));
      }
    }
    for (int x = 0; x < 4; x++) {
      setCubePixel(x, 1, 0, random(256), random(256), random(256));
    }
  } else if (frameNumber == 9) { // 9: (x02) off (x20) on
    for (int x = 0; x < 4; x++) {
      for (int z = 0; z < 2; z++) {
        setCubePixel(x, 0, z, random(256), random(256), random(256));
      }
    }
    for (int x = 0; x < 4; x++) {
      setCubePixel(x, 1, 0, random(256), random(256), random(256));
      setCubePixel(x, 2, 0, random(256), random(256), random(256));
    }
  } else if (frameNumber == 10) { // 10: (x01) off (x30) on
    for (int x = 0; x < 4; x++) {
      setCubePixel(x, 0, 0, random(256), random(256), random(256));
    }
    for (int x = 0; x < 4; x++) {
      setCubePixel(x, 1, 0, random(256), random(256), random(256));
      setCubePixel(x, 2, 0, random(256), random(256), random(256));
      setCubePixel(x, 3, 0, random(256), random(256), random(256));
    }
  } else if (frameNumber == 11) { // 11: (x00) off (x31) on
    for (int x = 0; x < 4; x++) {
      for (int y = 1; y < 4; y++) {
        setCubePixel(x, y, 0, random(256), random(256), random(256));
      }
    }
    for (int x = 0; x < 4; x++) {
      setCubePixel(x, 3, 1, random(256), random(256), random(256));
    }
  } else if (frameNumber == 12) { // 12: (x10) off (x32) on
    for (int x = 0; x < 4; x++) {
      for (int y = 2; y < 4; y++) {
        setCubePixel(x, y, 0, random(256), random(256), random(256));
      }
    }
    for (int x = 0; x < 4; x++) {
      setCubePixel(x, 3, 1, random(256), random(256), random(256));
      setCubePixel(x, 3, 2, random(256), random(256), random(256));
    }
  } else if (frameNumber == 13) { // 13: (x20) off (x33) on
    for (int x = 0; x < 4; x++) {
      setCubePixel(x, 3, 0, random(256), random(256), random(256));
    }
    for (int x = 0; x < 4; x++) {
      setCubePixel(x, 3, 1, random(256), random(256), random(256));
      setCubePixel(x, 3, 2, random(256), random(256), random(256));
      setCubePixel(x, 3, 3, random(256), random(256), random(256));
    }
  } else if (frameNumber == 14) { // 14: (33z) off (02z) on
    for (int x = 0; x < 3; x++) {
      for (int z = 0; z < 4; z++) {
        setCubePixel(x, 3, z, random(256), random(256), random(256));
      }
    }
    for (int z = 0; z < 4; z++) {
      setCubePixel(0, 2, z, random(256), random(256), random(256));
    }
  } else if (frameNumber == 15) { // 15: (23z) off (01z) on
    for (int x = 0; x < 2; x++) {
      for (int z = 0; z < 4; z++) {
        setCubePixel(x, 3, z, random(256), random(256), random(256));
      }
    }
    for (int z = 0; z < 4; z++) {
      setCubePixel(0, 2, z, random(256), random(256), random(256));
      setCubePixel(0, 1, z, random(256), random(256), random(256));
    }
  } else if (frameNumber == 16) { // 16: (13z) off (00z) on
    for (int x = 0; x < 1; x++) {
      for (int z = 0; z < 4; z++) {
        setCubePixel(x, 3, z, random(256), random(256), random(256));
      }
    }
    for (int z = 0; z < 4; z++) {
      setCubePixel(0, 2, z, random(256), random(256), random(256));
      setCubePixel(0, 1, z, random(256), random(256), random(256));
      setCubePixel(0, 0, z, random(256), random(256), random(256));
    }
  } else if (frameNumber == 17) { // 17: turn off (0,y,0) layer, turn on (1,y,3) column
    for (int y = 0; y < 4; y++) {
      for (int z = 1; z < 4; z++) {
        setCubePixel(0, y, z, random(256), random(256), random(256));
      }
      setCubePixel(1, y, 3, random(256), random(256), random(256));
    }
  } else if (frameNumber == 18) { // 18: turn off (0,y,1) layer, turn on (2,y,3) column
    for (int y = 0; y < 4; y++) {
      for (int z = 2; z < 4; z++) {
        setCubePixel(0, y, z, random(256), random(256), random(256));
      }
      setCubePixel(1, y, 3, random(256), random(256), random(256));
      setCubePixel(2, y, 3, random(256), random(256), random(256));
    }
  }

  Colorduino.FlipPage();
}

void setup() {
  Serial.begin(9600);
  Colorduino.Init();
  randomSeed(analogRead(A0));
}

void loop() {
  int frameDelay = 40;
  
  for (int i = 1; i <= 18; i++) {
    drawFrame(i);
    delay(frameDelay);
  }
}
