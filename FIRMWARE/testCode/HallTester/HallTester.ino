void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 4; i++) {
    if (i < 3) {
      Serial.print(digitalRead(i + 2));
      Serial.print("\t");
    } else {
      Serial.println(digitalRead(i + 2));
    }
  }
}
