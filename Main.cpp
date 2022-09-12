#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Data.h"
#include "Lector.h"
#include "Radio.h"
#include <stdio.h>



using namespace std;


int main() {

	vector<tAntena> Antenas;
	tResultado Resultado;
	leerDatos(Antenas);
		if (Antenas.size() < 2) {
		cout << "Pocas antenas para triangular" << endl;
	}else{
		calculaRadio(Antenas, Resultado);
		salida(Antenas, Resultado);
		return 0;
	}

}


