#include "LA3D.cpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace::std;

typedef struct t_off_set {
    std::vector<Ponto> pontos;
    std::vector<Triangulo> faces;
} off_set;

void insertPoint(off_set & set, Ponto p){

    set.pontos.push_back(p);
}

void insertFace(off_set & set, int idx1, int idx2, int idx3){

	Triangulo t;

	t.raiz = set.pontos[idx1];
	t.direito = set.pontos[idx2];
	t.esquerdo = set.pontos[idx3];

	set.faces.push_back(t);
}

off_set makeOffSet(std::string filename){

	off_set set;
	int i;
	int vertices, faces, arestas;
	float x, y, z;
	Ponto p;
	int numVert, idx1, idx2, idx3;
	
	std::ifstream infile(filename.c_str());

	std::string line;
	std::getline(infile,line);
	std::getline(infile,line);	
	std::istringstream iss(line);
	iss >> vertices >> faces >> arestas;

	for(i = 0; i < vertices; i++){

		std::getline(infile,line);
	    std::istringstream iss(line);
	    iss >> x >> y >>z;

	    p = makePonto(x, y, z);
		insertPoint(set, p);
	}

	for(i = 0; i < faces; i++){

		std::getline(infile,line);
	    std::istringstream iss(line);
	    iss >> numVert >> idx1 >> idx2 >>idx3;

	    insertFace(set, idx1, idx2, idx3);
	}

	return set;
}
