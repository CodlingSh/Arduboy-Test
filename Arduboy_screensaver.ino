#include <Arduboy.h>
#include <Arduboy2.h>

Arduboy2 arduboy;

int state;
float x_inc, y_inc, x_pos, y_pos;

void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  Serial.begin(9600);
  arduboy.clear();
  state = 0;
  x_pos = 0;
  y_pos = 0;
  arduboy.setFrameRate(60);
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }

  arduboy.pollButtons();
  arduboy.clear();

  switch (state) {
    case 0:
      arduboy.setCursor(0, 0);
      arduboy.println("Press the A button");
      if (arduboy.justPressed(A_BUTTON)) {
        arduboy.initRandomSeed();
        x_inc = (1 - float(random(5)) / 10);
        y_inc = (1 - float(random(5)) / 10);
        state = 1;
      }
      break;
    case 1:
      start_movement();
      break;
  }

  Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
  arduboy.display();
}

void start_movement() {
  // put your main code here, to run repeatedly:
  arduboy.setCursor(x_pos, y_pos);
  arduboy.println("ARDUBOY");
  /*arduboy.setCursor(0, 0);
  arduboy.println(x_inc);
  arduboy.println(y_inc);*/
  x_pos += x_inc;
  y_pos += y_inc;

  if (x_pos <= 0) {
    x_inc = (1 - float(random(5)) / 10);
  }
  else if (x_pos >= 87) {
    x_inc = (1 - float(random(5)) / 10) * -1;
  }

  if (y_pos <= 0) {
    y_inc = (1 - float(random(5)) / 10);
  }
  else if (y_pos >= 57) {
    y_inc = (1 - float(random(5)) / 10) * -1;
  }
}
