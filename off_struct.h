#include "LA3D.cpp"
#include<vector>

typedef struct t_off_set {
    std::vector<Ponto> pontos;
    std::vector<Triangulo> faces;
} off_set;

void insertPoint(off_set& set, Ponto p){
	
	set.pontos.push_back(p);
	
}

void insertFace(off_set& set, int idx1, int idx2, int idx3){
	
	Triangulo t;

	t.raiz = set.pontos[idx1];
	t.direito = set.pontos[idx2];
	t.esquerdo = set.pontos[idx3];

	set.faces.push_back(t);
	
}



