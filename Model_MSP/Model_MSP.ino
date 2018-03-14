#define LEDR RED_LED
#define LEDG GREEN_LED
#define PB PUSH2

int buttonState = 0.0;
int LICZBA = 0.0;

//Dane
double M = 1000.0;             //[kg]
double c = 800.0;              //[J/(kg*K)]
double m = 300.0;              //[kg/m]
double n = 7.0;                //[1]
double v = 1.0;                //[m/h]
double T0 = 20.0;              //[^oC]
double Tp = 1200.0;            //[^oC]
double cs = 1000.0;            //[J/(kg*K)]
double gs = 1.15;              //[kg/m^3]

//dTemp = a0 + a1*Temp + a2*q + a3*q*Temp;
double a0 = m*v*T0/M;
double a1 = -m*v/M;
double a2 = (n+1)*gs*cs*Tp/M/c;
double a3 = -(n+1)*gs*cs/M/c;

double q = 10.0; //placeholder sterowanie
double Temp = 0.0; //wyjscie
double dTemp = 0.0; //zmiana wyjscia
double h = 0.01; //krok calkowania


void setup() {                
  pinMode(LEDR, OUTPUT); 
  pinMode(LEDG, OUTPUT);   
  pinMode(PB, INPUT_PULLUP);
  Serial.begin(9600); 
}


void loop() {

  dTemp = a0 + a1*Temp + a2*q + a3*q*Temp;
  Temp = Temp + dTemp*h;

  Serial.println(String("\nTemp = "));
  Serial.println(String(Temp));
  Serial.println(String("\n"));
  
  delay(10);
}
