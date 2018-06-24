#include "LA3D.cpp"
#include <set>
#include <stack>

typedef struct he_point {
    Ponto p;
    HalfEdge edge;
} HE_Point;

bool compareHE_Points(const HE_Point& a, const HE_Point& b){
    return a.p.x < b.p.x || a.p.y < b.p.y || a.p.z < b.p.z;
}

typedef struct t_face {
    HalfEdge own;
} Face;

typedef struct half_edge_struct {
    HE_Point sc;
    half_edge_struct* next, twin;
    Face f;
} HalfEdge;

bool compareHalfEdges(const HalfEdge& a, const HalfEdge& b){
    if(equals(a.sc.p,b.sc.p)){
        int cnta = ((a.next == null)? 1:0)+((a.twin == null)?1:0) ;
        int cntb = ((b.next == null)? 1:0)+((b.twin == null)?1:0) ;
        if(cnta >= cntb) return true;
        else return false;
    }
    return compareHE_Points(a.sc,b.sc);
}

bool compareFaces(const Face& a, const Face& b){
    return compareHalfEdges(a.own,b.own);
}

typedef std::set<HE_Point,compareHE_Points> v_points;
typedef std::set<Face,compareFaces> v_faces;
typedef std::set<HalfEdge,compareHalfEdges> v_h_edges;
typedef std::stack<HalfEdge> h_e_stack;

typedef struct t_half_edge_mesh {
    v_points points;
    v_faces faces;
    v_h_edges h_edges;
} HalfEdgeMesh;

bool addHalfEdge(HalfEdgeMesh mesh, HalfEdge he){
    mesh.h_edges.insert(he);
    mesh.faces.insert(he.f);
    mesh.points.insert(he);
    return true;
}

bool addSurface(HalfEdgeMesh mesh,HalfEdge he){
    h_e_stack stackhe;
    stackhe.push(he);
    while(!stackhe.empty()){
        he = stackhe.top();
        stackhe.pop();
        addHalfEdge(mesh,he);
        if(he.*next == null) stackhe.push(he->next);
        if(he.*twin == null) stackhe.push(he->twin);
    }
    return true;
}
