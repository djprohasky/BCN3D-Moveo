import guru.ttslib.*;

TTS tts;

void setup() {
  size(100, 100);
  smooth();
  tts = new TTS();
}

void draw() {
  background(255);
  fill(255);
  ellipse( 35, 30, 25, 35 );
  ellipse( 65, 30, 25, 35 );
  fill(0);
  ellipse( 40, 35, 10, 10 );
  ellipse( 60, 35, 10, 10 );
  noFill();
  arc(50, 50, 50, 50, 0, PI);
}

void mousePressed() {
  tts.setPitch(150);
  tts.setPitchRange(10);
  tts.speak("stick?");
  delay(1000);
  tts.speak("How did I do?");
  //tts.speakLeft("Hello from the left");
  //tts.speakRight("Hello from the Right");
}