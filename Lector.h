#pragma once
#ifndef __LECTOR_H
#define __LECTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Data.h"




using namespace std;


/*
typedef struct {
	int CID;
	int LAC;
	int MCC;
	int MNC;
	int Power;
	int Range;
	float Long;
	float Lat;
}tAntena;*/


//vector<tAntena> Antenas;



using namespace std;


void leerDatos(vector<tAntena>& Antenas);
void salida(vector<tAntena> Antenas,tResultado Resultado);


#endif // __STACK_H