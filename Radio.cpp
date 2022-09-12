
#include "Radio.h"

using namespace std;

void calcula(vector<tAntena>& Antenas, tResultado& Resultado) {
	double lat = 0, lon = 0, acum = 0;
	for (int i = 0; i < int(Antenas.size()); i++) {
		lat += Antenas[i].Lat * Antenas[i].watts;
		lon += Antenas[i].Long * Antenas[i].watts;
		acum += Antenas[i].watts;
	}
	Resultado.lat = lat / acum;
	Resultado.lon = lon / acum;
}

void calculaRadio(vector<tAntena>& Antenas, tResultado& Resultado) {
	int constante = 1;
	double tmp,pot;
	for (int i = 0; i < int(Antenas.size()); i++) {//Bucle para comprobar si la antena la hemos detectado.
		pot = pow(10,-Antenas[i].Power/10.)/1000;
		Antenas[i].watts = pot * 10000000000;
		Antenas[i].watts = Antenas[i].watts * 0.2;
		if (Antenas[i].watts == 0) {
			Antenas[i].watts = 1;
		}
		tmp = sqrt(constante * (1 / pot));
		Antenas[i].Radio = int(tmp*0.7);
		if (Antenas[i].Radio > 1000) {
			Antenas[i].Radio = 1000;
		}
	}
	calcula(Antenas, Resultado);
}
/*
10 m->recibida 0.8
20 m->recibida 0.4
1 / 2 = 0.5
1 / 7 = 0.14

Densidad = Power / (4pi r ^ 2)
densidad = 1000
power = 30

r = sqrt(Power / Densidad * 4 * pi)---> 0.047 m;
power = 50
0.063


r = sqrt(Power / Densidad * 4 * pi)---> 0.00228 m;


distancia

1 Pot=30 d =471
2 Pot=28 d = 200
3 Pot=25 d = 306
4 Pot=24 d = 256
5 Pot=40 d = 153
6 Pot=39 d = 156

*/
