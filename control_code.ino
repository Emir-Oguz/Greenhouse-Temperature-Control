#define sicaklikOkumaPin A5
#define pwmPin 10
float okunanVoltaj;
float sicaklikDeger, sicaklikGerilim;
float kp = 10,  kd = 1.5, ki=3, zamanDegisimi = 0.01;
int ref = 25, pwm, pidValue;
double sampleTime, sample;
void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(A5, INPUT);
}
void loop() {
  if (Serial.available()) {
    ref = Serial.parseInt();
  }
  okunanVoltaj = analogRead(sicaklikOkumaPin);
  sicaklikDeger = okunanVoltaj / 20.48;
  sampleTime = millis() - sample;
  if (sampleTime > 250) {
    sample = millis();
    sampleTime = 0;
    Serial.println(sicaklikDeger);
  }
  pidValue = pid(ref, sicaklikDeger);
  if (ref > 0) {
    analogWrite(pwmPin, pidValue);
  }
  else {
    analogWrite(pwmPin, 0);
  }
}

int pid(int ref, int out) {
  int hata;
  static int sonHata;
  static int toplamHata;
  hata = ref - out;
  if (hata > 0) {
    pwm=hata*kp+((hata-sonHata)/zamanDegisimi)*kd+toplamHata*zamanDegisimi*ki;
    sonHata = hata;
    if (pwm > 255) {
      pwm = 255;
    }
    return pwm;
  }
  if (hata <= 0) {
    pwm = 0;
    return pwm;
  }
}
