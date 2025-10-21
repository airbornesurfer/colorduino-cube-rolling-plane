# 4x4x4 LED Cube Rolling Plane Animation

This repository contains the Arduino code for generating a smooth, mesmerizing **"rolling plane" animation** on a 4x4x4 LED cube driven by a Colorduino board. The animation simulates a solid plane of light rolling continuously over the cube's faces in a cycle, with each pixel randomly changing color in every frame.

The final animation runs through a sequence of 18 frames, looping seamlessly at a fluid rate of 40 milliseconds per frame.

This project was originally just going to be a solder project with a SeeedStudio RainbowDuino cube kit that @rc2014 sent me a few years ago, but the RainbowDuino has been sold out for some time, and then *TARIFFS!!!*, so I figured a Colorduino clone from eBay would work. It did, but it took a lot of tedious reverse-engineering to map all the pixels. I had Gemini write the code for the mapping because I'm lazy.

---

## 🛠️ Hardware & Libraries

### Hardware
* **LED Cube:** A 4x4x4 LED cube.
* **LED Driver Shield:** A **Colorduino** board (or similar HT1632C-based driver shield) for managing the cube's 64 tri-color RGB LEDs.

### Libraries
* **Colorduino Library:** Required for interfacing with the Colorduino driver board.

---

## 💻 The Code: How it Works

The core challenge of this project is translating the cube's physical 3D coordinates ($X, Y, Z$) into the 2D pixel coordinates ($x, y$) required by the Colorduino driver board.

### 1. Coordinate Mapping (`cubeMap`)
The `cubeMap` is a static lookup table that stores the physical $X, Y, Z$ coordinates for every logical pixel position on the 8x8 Colorduino matrix.

```cpp
int cubeMap[8][8][3] = {
  // ... a static array defining the (X, Y, Z) for each physical LED position (0-7, 0-7)
};
````

### 2\. The Pixel Function (`setCubePixel`)

The custom `setCubePixel(X, Y, Z, R, G, B)` function abstracts the coordinate translation. When you call it with a logical cube position (e.g., $X=1, Y=2, Z=3$), it searches the `cubeMap` to find the corresponding physical $x, y$ coordinates and then calls the standard `Colorduino.SetPixel(x, y, R, G, B)`.

### 3\. The Animation Logic (`drawFrame`)

The `drawFrame(int frameNumber)` function contains the entire animation sequence. It consists of 18 meticulously defined frames (1 through 18) that control which pixels are turned **ON** and which are turned **OFF** to create the illusion of a rolling motion.

The color is generated randomly for every active pixel in every frame using the `random(256)` function for Red, Green, and Blue intensity values:

```cpp
// Example of a frame with random color applied:
setCubePixel(x, y, 3, random(256), random(256), random(256));
```

### 4\. The Loop (`loop`)

The main loop runs the 18-frame sequence continuously with a short delay:

```cpp
void loop() {
  int frameDelay = 40; // Fluid animation at 40ms per frame
  
  for (int i = 1; i <= 18; i++) {
    drawFrame(i);
    delay(frameDelay);
  }
}
```

-----

## 🚀 Getting Started

1.  **Clone the Repository:** Download the code to your computer.
2.  **Install Library:** Ensure you have the **Colorduino library** installed in your Arduino IDE.
3.  **Setup Cube:** Assemble and connect your 4x4x4 cube to the Colorduino shield, and the shield to your Arduino board.
4.  **Upload:** Open the sketch in the Arduino IDE and upload it to your board.

The animation should begin playing immediately, rolling the plane over and over across your LED cube\!
