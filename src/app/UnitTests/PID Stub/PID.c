// Constantes del controlador
const float Ts = 0.5f;
const float Kp = 0.4f;
const float Ki = 0.1f;
const float Kd = 0.4f;

// Variables globales
float y, y_old=0.0;
float error, error_old=0.0;
float yp, yi, yd, yi_old=0;

// Variables auxiliares
int i;
uint8_t buff;

// Union utilizado para pasar de 4 bytes a float y viceversa
union {
byte by[4];
float fl;
} fval;

// Inicializacion
void setup(){
  Serial.begin(115200);
}

// Loop task
void loop(){

  // Espero recibir 4 caracteres que componente un float
  if (Serial.available()>=4){

    // Una vez recibidos los guardo como un float
    for (i=0;i<4;i++){
      buff = Serial.read();
      fval.by[i] = buff;
    }
    error = fval.fl;
    //Aca esta el dato recibido desde MATLAB en la variable error

    // Calculo de los coeficientes P, I, D
    yp = Kp*error;
    yi = yi_old + (Ki*Ts)*error_old;
    yd = (Kd/Ts)*(error-error_old);

    // La salida se compone de la suma de los tres coeficientes
    y = yi + yp + yd;

    // Guardo los estados como viejos
    y_old = y;
    yi_old = yi;
    error_old = error;

    // Devuelvo a matlab el valro de y
    fval.fl = y;
    Serial.write((uint8_t *)&fval,4);
  }
}

