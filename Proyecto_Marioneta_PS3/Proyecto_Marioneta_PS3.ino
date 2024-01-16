//Librerías del programa
#include <ESP32Servo.h>
#include <Ps3Controller.h>

//definir servos
Servo srvmtr1;
Servo srvmtr2;
Servo srvmtr3;
Servo srvmtr4;
Servo srvmtr5;
Servo srvmtr6;

//valores de controles
int leftx;
int lefty;
int rightx;
int righty;

int player = 0;

//Posiciones de servos
int servoPos1 = 90;
int servoPos2 = 90;

void notify()
{
  //Valor de Joystick Izquierdo
  leftx = (Ps3.data.analog.stick.lx);
  lefty = (Ps3.data.analog.stick.ly);

  //Valor de Joystick Derecho
  rightx = (Ps3.data.analog.stick.rx);
  righty = (Ps3.data.analog.stick.ry);

  //Movimiento de Joystick Izquierdo
  if(lefty < -100){
    servoPos1 = 90;
    srvmtr1.write(servoPos1);
    delay(10);
  }else{
    if(leftx < -10 && servoPos1 < 180){
      servoPos1++;
      srvmtr1.write(servoPos1);
      delay(10);
    }
    if(leftx > 10 && servoPos1 > 0){
      servoPos1--;
      srvmtr1.write(servoPos1);
      delay(10);
    }
  }
  //Movimiento de Joystick Derecho
  if(righty < -100){
    servoPos2 = 90;
    srvmtr2.write(servoPos2);
    delay(10);
  }else{
    if(rightx < -10 && servoPos2 < 180){
      servoPos2++;
      srvmtr2.write(servoPos2);
      delay(10);
    }
    if(rightx > 10 && servoPos2 > 0){
      servoPos2--;
      srvmtr2.write(servoPos2);
      delay(10);
    }
  }
  
  //Pulsado de botón L2
    if( Ps3.event.analog_changed.button.l2){
        srvmtr3.write(45);
        delay(10);}

        if( Ps3.event.analog_changed.button.l1){
        srvmtr3.write(0);
        delay(10);}

  //Pulsado de botón R2
    if( Ps3.event.analog_changed.button.r2){
        srvmtr4.write(45);
        delay(10);}

    if( Ps3.event.analog_changed.button.r1){
        srvmtr4.write(0);
        delay(10);}

  //Pulsado de Círculo
    if( Ps3.event.button_down.circle ){
        srvmtr5.write(100);
        delay(10);}
    if( Ps3.event.button_up.circle ){
        srvmtr5.write(90);
        delay(10);}

  //Pulsado de Cuadrado
    if( Ps3.event.button_down.square ){
        srvmtr5.write(80);
        delay(10);}
    if( Ps3.event.button_up.square ){
        srvmtr5.write(90);
        delay(10);}

  //Pulsado de D-Pad Derecha
        if( Ps3.event.button_down.right ){        
        srvmtr6.write(100);
        delay(10);}
    if( Ps3.event.button_up.right ){
        srvmtr6.write(90);
        delay(10);}

  //Pulsado de D-Pad Izquierda 
    if( Ps3.event.button_down.left ){        
        srvmtr6.write(80);
        delay(10);}
    if( Ps3.event.button_up.left ){
        srvmtr6.write(90);
        delay(10);}

}

void onConnect()
{   Serial.println("Connected.");}


void setup()
{
    Serial.begin(115200);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("b0:b2:1c:96:cf:c4");

    Serial.println("Ready.");

    srvmtr1.attach(2);
    srvmtr1.write(servoPos1);

    srvmtr2.attach(12);
    srvmtr2.write(servoPos2);

    srvmtr3.attach(23);

    srvmtr4.attach(25);

    srvmtr5.attach(18);

    srvmtr6.attach(21);
}

void loop()
{
    if(!Ps3.isConnected())
        return;

    //-------------------- Player LEDs -------------------
    Serial.print("Setting LEDs to player "); Serial.println(player, DEC);
    Ps3.setPlayer(player);

    player += 1;
    if(player > 10) player = 0;

    delay(2000);
}
