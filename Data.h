#pragma once

#ifndef __DATA_H
#define __DATA_H

typedef struct {
	int CID;
	int LAC;
	int MCC;
	int MNC;
	int Power;
	int Range;
	double Long;
	double Lat;
	int Radio;
	int watts;
}tAntena;

typedef struct {
	double lon;
	double lat;
}tResultado;

#endif 
