
#include "Lector.h"

using namespace std;


void intenta(string cadena, vector<string> &Antenas){
	string delimiter = ",";
	size_t pos = cadena.find(delimiter);

	if (cadena != "" && cadena != "Args= ") {
		pos = cadena.find(delimiter);
		cadena.erase(0, pos + delimiter.length());
		pos = cadena.find(delimiter);
		cadena.erase(0, pos + delimiter.length());
		Antenas.push_back(cadena);
	}
}


void llenar(vector<string> stringAntenas, vector<tAntena>& Antenas) {
	string stringAntena,numero;
	tAntena  antena = tAntena();
	bool enc = false;
	int i = 0, cont = 0, var = 0;;

	while (!stringAntenas.empty()) {
		Antenas.push_back(antena);
		stringAntena = stringAntenas.back();
		while (cont < int(stringAntena.size())) {
			if (isdigit(stringAntena[cont])) {
				numero += stringAntena[cont];
				enc = true;
			}
			else if (enc == true && !isdigit(stringAntena[cont])) {
				if (var == 0) {
					Antenas[i].CID = stoi(numero);
				}
				else if (var == 1) {
					Antenas[i].LAC = stoi(numero);
				}
				else if (var == 2) {
					Antenas[i].MCC = stoi(numero);
				}
				else if (var == 3) {
					Antenas[i].MNC = stoi(numero);
				}
				var++;
				numero = "";
				enc = false;
			}
			cont++;
		}
		Antenas[i].Power = stoi(numero);
		numero = "";
		enc = false;
		var = 0;
		cont = 0;

		stringAntenas.pop_back();
		i++;

	}
}



void leerDatosSalida(vector<tAntena>& Antenas) {
	ifstream fe("Antenas.txt");
	string cadena;
	vector<string> stringAntenas;

	while (!fe.eof()) {
		getline(fe, cadena);
		intenta(cadena, stringAntenas);
	}
	fe.close();
	llenar(stringAntenas, Antenas);
}


void leerDatosBBDD(vector<tAntena>& Antenas){//Funci�n encargada de buscar la Informacion de la posici�n y el rango de las antenas 
	ifstream archivo("BBDD.csv");//BBDD
	string linea;
	char delimitador = ',';
	// Leemos la primer l�nea para descartarla, pues es el encabezado
	getline(archivo, linea);
	// Leemos todas las l�neas
	while (getline(archivo, linea))
	{
		stringstream stream(linea); // Convertir la cadena a un stream
		string radio, mcc, net, area, cell, unit, lon,lat,range,samples,changeable,created,upddated,average,signal;
		// Extraer todos los valores de esa fila
		getline(stream, radio, delimitador);
		getline(stream, mcc, delimitador);
		getline(stream, net, delimitador);
		getline(stream, area, delimitador);
		getline(stream, cell, delimitador);
		getline(stream, unit, delimitador);
		getline(stream, lon, delimitador);
		getline(stream, lat, delimitador);
		getline(stream, range, delimitador);
		for (int i = 0;i <int(Antenas.size()) ; i++) {//Bucle para comprobar si la antena la hemos detectado.
			if (Antenas[i].MCC == stoi(mcc) && Antenas[i].MNC == stoi(net)
				&& Antenas[i].LAC == stoi(area) && Antenas[i].CID == stoi(cell)) {//Si la antena la hemos recibido la actualizamos
				Antenas[i].Range = stoi(range);
				Antenas[i].Lat = stof(lat);
				Antenas[i].Long = stof(lon);
			}
		}

	}
	archivo.close();
}


void borraSobrantes(vector<tAntena>& Antenas) {
	for (int i = 0; i < int(Antenas.size()); i++) {//Bucle para comprobar si la antena la hemos detectado.
		if (Antenas[i].Long == 0) {//Si la antena la hemos recibido la actualizamos
			Antenas[i] = Antenas.back();
			Antenas.pop_back();
		}
	}
}

static bool compareCpusByValue(tAntena& a, tAntena& b) {
	return a.Power < b.Power;
}

void Ordena(vector<tAntena>& Antenas) {
		sort(Antenas.begin(), Antenas.end(), compareCpusByValue);
}






void leerDatos(vector<tAntena>& Antenas) {
	//vector<tAntena> Antenas;
	leerDatosSalida(Antenas);
	leerDatosBBDD(Antenas);
	borraSobrantes(Antenas);
	Ordena(Antenas);
	
}

/*
void salida(vector<tAntena>& Antenas) {
	std::ofstream myfile;
	myfile.open("example.csv");

	myfile << "MCC,MNC,LAC,CID,Lat,Long,Radio,Power\n";
	for (int i = 0; i < Antenas.size(); i++) {//Bucle para comprobar si la antena la hemos detectado.
		myfile << Antenas[i].MCC <<","<< Antenas[i].MNC<<","<< Antenas[i].LAC << "," << Antenas[i].CID << "," << setprecision(8) << Antenas[i].Lat << ","<< setprecision(8) << Antenas[i].Long << "," << Antenas[i].Radio  << "," << Antenas[i].Power <<"\n";
	}
	myfile.close();
}*/
void salida(vector<tAntena> Antenas, tResultado Resultado) {
	std::ofstream myfile;
	myfile.open("./Representacion/js/Antenas.js");
	string js;

	for (int i = 0; i < int(Antenas.size()); i++) {//Bucle para comprobar si la antena la hemos detectado.
		js += " L.marker([";
		js += to_string(Antenas[i].Lat);// << setprecision(8)
		js += ",";
		js += to_string(Antenas[i].Long);//<< setprecision(8)
		js += "], {icon: greenIcon}).bindPopup(\"<b> Antena </b> <br>";
		js += "Lat:";
		js += to_string(Antenas[i].Lat);
		js += "<br>";
		js += "Lon:";
		js += to_string(Antenas[i].Long);
		js += "<br>";
		js += "RSSI:";
		js += to_string(Antenas[i].Power);
		js += "<br>";
		js += "Distance:";
		js += to_string(Antenas[i].Radio);
		js += "\").openPopup().addTo(map); \n";
	}
	js += " L.marker([";
	js += to_string(Resultado.lat);// << setprecision(8)
	js += ",";
	js += to_string(Resultado.lon);//<< setprecision(8)
	js += "] , { draggable: true }).bindPopup(\"<b> CM </b> <br>";
	js += "Lat:";
	js += to_string(Resultado.lat);
	js += "<br>";
	js += "Lon:";
	js += to_string(Resultado.lon);
	js += "\").openPopup().addTo(map); \n";


	js += " map.setView(new L.LatLng(";
	js += to_string(Resultado.lat);// << setprecision(8)
	js += ",";
	js += to_string(Resultado.lon);//<< setprecision(8)
	js += "), 16);";




	myfile << js ;
	myfile.close();
}
