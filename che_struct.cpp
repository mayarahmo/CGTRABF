#ifndef CHE_LIB
#define CHE_LIB
#include "LA3D.cpp"
#include <set>
#include <queue>
#include <cstdlib>

struct half_edge_struct ;
typedef half_edge_struct HalfEdge;

typedef struct he_point {
    Ponto p;
    HalfEdge* edge;
} HE_Point;

typedef HalfEdge Face;

struct half_edge_struct {
    HE_Point sc;
    HalfEdge* next, *twin;
    Face* f;
};

bool compareHE_Points(const HE_Point& a, const HE_Point& b){
    if(a.p.x == b.p.x){
        if(a.p.y == b.p.y) return a.p.z < b.p.z;
        return a.p.y < b.p.y;
    }
    return a.p.x < b.p.x;
    //return a.p.x < b.p.x || a.p.y < b.p.y || a.p.z < b.p.z;
}

HalfEdge makeHalfEdge(Ponto p, HalfEdge* next, HalfEdge* twin, Face* face){
    HalfEdge edge;// = (HalfEdge*) malloc(sizeof(HalfEdge));

    HE_Point he_p;
    he_p.p = p;
    he_p.edge = &edge;

    edge.sc = he_p;

    edge.next = next;
    edge.twin = twin;

    edge.f = face;

    return edge;
}

struct CompareHE {
    Ponto p; HalfEdge origem; int originCreated=0;
    inline bool operator()(const HalfEdge& a, const HalfEdge& b){
        if(!originCreated){
            p.x = 0; p.y = 0; p.z = 0;
            origem = makeHalfEdge(p,NULL,NULL,NULL);
            originCreated = 1;
        }
        if(equals(a.sc.p,b.sc.p)){
            HalfEdge c,d;
            d = (b.next == NULL)? origem:*b.next;
            c = (a.next == NULL)? origem:*a.next;
            return compareHE_Points(c.sc,d.sc);
        }
        return compareHE_Points(a.sc,b.sc);
    }
};

/*
bool compareFaces(const Face& a, const Face& b){
    return compareHalfEdges(a,b);
}*/

//typedef std::set<HE_Point> v_points;
//typedef std::set<Face> v_faces;
typedef std::set<HalfEdge,CompareHE> v_h_edges;
typedef std::queue<HalfEdge> h_e_stack;

typedef struct t_half_edge_mesh {
    //v_points points(compareHE_Points);
    //v_faces faces(compareFaces);
    v_h_edges h_edges;
} HalfEdgeMesh;

bool addHalfEdge(HalfEdgeMesh& mesh, HalfEdge he){
    mesh.h_edges.insert(he);
    //mesh.faces.insert(*he.f);
    //mesh.points.insert(he.sc);
    return true;
}

bool addSurface(HalfEdgeMesh& mesh,HalfEdge start){
    h_e_stack stackhe;
    stackhe.push(start);
    HalfEdge he;
    int count = 0;
    while(!stackhe.empty()){
        he = stackhe.front();
        stackhe.pop();
        //printf("%d %f %f %f ",mesh.h_edges.size(),he.sc.p.x,he.sc.p.y,he.sc.p.z);
        //printf("%d %d\n",he.next!=NULL,he.twin!=NULL);
        if(he.next != NULL){
            //printf("%f %f %f\n",(*he.next).sc.p.x,(*he.next).sc.p.y,(*he.next).sc.p.z);
        }
        if(he.twin != NULL){
            //printf("%f %f %f\n",(*he.twin).sc.p.x,(*he.twin).sc.p.y,(*he.twin).sc.p.z);
        }
        addHalfEdge(mesh,he);
        if(he.next != NULL) if(mesh.h_edges.find(*he.next) == mesh.h_edges.end() ) stackhe.push(*he.next);
        if(he.twin != NULL) if(mesh.h_edges.find(*he.twin) == mesh.h_edges.end() ) stackhe.push(*he.twin);
    }
    return true;
}
#endif