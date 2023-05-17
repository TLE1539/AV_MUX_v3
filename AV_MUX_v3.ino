#define pin_sdi 9
#define pin_clk 2
#define pin_ss 8
#define pin_latch 7

#define d 1

void writeToRegister(uint16_t chIn1, uint16_t chIn2, uint16_t chIn3, uint16_t chIn4){
  uint16_t ch_addr = chIn4;
  ch_addr |= (chIn3 << 4);
  ch_addr |= (chIn2 << 8);
  ch_addr |= (chIn1 << 12);

  Serial.print("Issued Command (int): ");
  Serial.println(ch_addr);

  digitalWrite(pin_ss, HIGH);
  delay(d);

  Serial.print("Issued Command (D3-D0, OUT0-OUT3): ");
  for(int i = 15; i >= 0; i--){
    
    digitalWrite(pin_sdi, (ch_addr & (1 << i)) >> i);
    delay(d);
    digitalWrite(pin_clk, HIGH);
    delay(d);
    digitalWrite(pin_clk, LOW);
    delay(d);

    Serial.print((ch_addr & (1 << i)) >> i);
  }

  delay(d);
  digitalWrite(pin_ss, LOW);
  delay(d);
  digitalWrite(pin_latch, LOW);
  delay(d);
  digitalWrite(pin_latch, HIGH);

  Serial.println();
}

void configChannelInputs(uint16_t chIn1, uint16_t chIn2, uint16_t chIn3, uint16_t chIn4){
  Serial.println("------------Configuring channel inputs------------");
  Serial.print("What you entered: ");
  Serial.print(chIn1); Serial.print(" | ");
  Serial.print(chIn2); Serial.print(" | ");
  Serial.print(chIn3); Serial.print(" | ");
  Serial.print(chIn4);
  Serial.println();
  
  if(chIn1 > 7 || chIn2 > 7 || chIn3 > 7 || chIn4 > 7){
    Serial.println("One or more channel inputs are out of bounds!");
    return;
  }

  writeToRegister(chIn1, chIn2, chIn3, chIn4);
}

void resetAllBuffers(){
  Serial.println("------------Reseting all buffers!------------");
  writeToRegister(8, 8, 8, 8);
}

void enableAllBuffers(){
  Serial.println("------------Enabling all buffers!------------");
  writeToRegister(9, 9, 9, 9);
}

void disableAllBuffers(){
  Serial.println("------------Disabling all buffers!------------");
  writeToRegister(10, 10, 10, 10);
}

void setup() {
  pinMode(pin_sdi, OUTPUT);
  pinMode(pin_clk, OUTPUT);
  pinMode(pin_ss, OUTPUT);
  pinMode(pin_latch, OUTPUT);

  // all pins are active HIGH
  digitalWrite(pin_sdi, LOW);
  digitalWrite(pin_clk, LOW);
  digitalWrite(pin_ss, LOW);
  digitalWrite(pin_latch, HIGH);

  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    String str = Serial.readString();
    if(str.toInt() >= 0) configChannelInputs(str.substring(0,1).toInt(), str.substring(1,2).toInt(), str.substring(2,3).toInt(), str.substring(3,4).toInt());
    if(str.toInt() == -1) resetAllBuffers();
    if(str.toInt() == -2) enableAllBuffers();
    if(str.toInt() == -3) disableAllBuffers();
  }

}
