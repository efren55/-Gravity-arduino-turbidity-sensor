
//MODELO SENSOR:  https://wiki.dfrobot.com/Turbidity_sensor_SKU__SEN0189



int sensorPin = A3; //PIN LECTURA
int sensorSalida = 7; //PIN PWM ARDUINO MEGA PARA CONTROLAR EL VOLTAJE DE SALIDA
float volt;
float ntu;
 
void setup()
{
  pinMode(sensorPin,INPUT);
  pinMode(sensorSalida,OUTPUT);
  Serial.begin(9600);

}
 
void loop()
{
    float volt1 = 0;
    float volt2=0,volt3=0;
    volt = 0;
    
    Serial.println("//////////////////////////////");
    for(int i=0; i<170; i+=34){ //i VA A IR INCREMENTANDO DE 0 HASTA LOS 170. ESTO PARA ES DEBIDO A QUE QUIERE SABER LA LECTURA DEL AGUA BAJO DISTINTAS INTENSIDADES DE LUZ. 0 = 0V, 170 = 3.3V
      analogWrite(sensorSalida,i); 
      for(int e=0; e<800; e++){
            volt += ((float)analogRead(sensorPin)/1023)*5; //SE SUMARA LA LECTURA LEIDA POR EL PIN A3 800 VECES
        }
      volt = volt/800; //SE DIVIDE EL VALOR FINAL ENTRE 800. SE DETERMINA EL PROMEDIO.
      volt2+=volt;    
      delay(300);
    }
    volt3=volt2/5; //SE DETERMINA EL PROMEDIO DE LAS DISTINTAS LECTURAS A DIFERENTES INTENSIDADES DE LUZ.
    //ntu=0.9788*square(volt3)-753.52*volt3+2772.8; 
    ntu=-753.52*volt3+2772.8; //ECUACION DETERMINADA POR REGRESION LINEAL.
    Serial.print(volt3,4);
    Serial.println("V");
    Serial.print(ntu,4); 
    Serial.println("NTU");
    delay(1000);
}
