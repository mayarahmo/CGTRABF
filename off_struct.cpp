#include "LA3D.cpp"
#include <vector>
#include <stdio.h>
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
	std::cout << filename;
	std::ifstream infile(filename);

	std::string line;
	std::getline(infile, line);
	std::istringstream iss(line);
	int a, b, c;
	iss >> a >> b;
	printf("%d", a);

	/*while (std::getline(infile, line)){

	    std::istringstream iss(line);
	    int a, b;
	    if (!(iss >> a >> b)) { break; } // error

	    // process pair (a,b)
	}*/
}

int main(void){

	makeOffSet("cone.off");

	return 0;
}