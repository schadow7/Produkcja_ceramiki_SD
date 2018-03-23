//Dane
double M = 1000.0;             //[kg]
double c = 800.0;              //[J/(kg*K)]
double m = 300.0;              //[kg/m]
double n = 7.0;                //[1]
double v = 1.0;                //[m/h]
double T0 = 20.0;              //[^oC]
double Tp = 1500.0;            //[^oC]
double cs = 1000.0;            //[J/(kg*K)]
double gs = 1.0;               //[kg/m^3]

//dTemp = a0 + a1*Temp + a2*q + a3*q*Temp;
double a0 = m*v*T0/M;
double a1 = -m*v/M;
double a2 = (n+1)*gs*cs*Tp/M/c;
double a3 = -(n+1)*gs*cs/M/c;

double q = 10.0; //placeholder sterowanie
double Temp = 0.0; //wyjscie
double dTemp = 0.0; //zmiana wyjscia
double h = 1.0; //krok calkowania

bool flaga = false;


void setup(){
  CCTL0 = CCIE;
  TACCR0 = 15540;
  TACTL = TASSEL_1 + MC_2;
  Serial.begin(9600);
}


void loop(){
  if(flaga){
    flaga = false;
    Serial.print(String(Temp));
  }
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void){
    flaga = true;
    dTemp = a0 + a1*Temp + a2*q + a3*q*Temp;
    Temp = Temp + dTemp*h;
    TACCR0 += 15540;
}
