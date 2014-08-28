void writeTimeToScratchpad(byte* address){
  ow.reset();
  ow.select(address);
  ow.write(0x44,1);
  delay(10);        
}
 
void readTimeFromScratchpad(byte* address, byte* data){
  byte i;
  ow.reset();
  ow.select(address);
  ow.write(0xBE);
  for (i = 0;i<9;i++){
    data[i] = ow.read();
  }
}
 
float getTemperature(byte* address){
  int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;
  byte data[12];
  float tc;
 
  writeTimeToScratchpad(address);
 
  readTimeFromScratchpad(address,data);
 //tr = data[0];
 
    LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit
  if (SignBit) // negative
  {
    TReading = (TReading ^ 0xffff) + 1; // 2's comp
  }
 Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25


   tc =(float(Tc_100) / 100);

 if (SignBit) // If its negative
 {
     tc = tc*-1;
  }
return tc;
}
 
//fahrenheit to celsius conversion
float f2c(float val){
  float aux = val - 32;
  return (aux * 5 / 9);
}
 
//celsius to fahrenheit conversion
float c2f(float val){
  float aux = (val * 9 / 5);
  return (aux + 32);
}
