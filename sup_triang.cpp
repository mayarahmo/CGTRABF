#include "off_struct.cpp"
#include "che_struct.cpp"
#include <vector>

void sup_to_triang(off_set set){

	HalfEdgeMesh mesh;

	std::vector<std::vector<int> > adjacencias;
	adjacencias.resize(set.faces.size());

	int commonVertices;
	int i, j;

	for(int i = 0; i < (int)set.faces.size(); i++){

		for(int j = 0; j < (int)set.faces.size(); j++){

			commonVertices = 0;

			if(set.vertices[i][0] == set.vertices[j][0] || set.vertices[i][0] == set.vertices[j][1] || set.vertices[i][0] == set.vertices[j][2]){
				commonVertices++;
			}
			if(set.vertices[i][1] == set.vertices[j][0] || set.vertices[i][1] == set.vertices[j][1] || set.vertices[i][1] == set.vertices[j][2]){
				commonVertices++;
			}
			if(set.vertices[i][2] == set.vertices[j][0] || set.vertices[i][2] == set.vertices[j][1] || set.vertices[i][2] == set.vertices[j][2]){
				commonVertices++;
			}

			if(commonVertices == 2){
				adjacencias[i].push_back(j);
			}
		}
	}

	printf("---ADJACÊNCIAS---\n");
	for(int i = 0; i < (int)adjacencias.size(); i++){

		printf("face %d: ", i);
		for(int j = 0; j < (int)adjacencias[i].size(); j++){

			int face = adjacencias[i][j];
			printf("%d ", face);
		}
		printf("\n");
	}
}

int main(void){

	off_set cone = makeOffSet("cone.off");

	sup_to_triang(cone);

	return 0;
}