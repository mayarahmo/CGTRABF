#include<GL/gl.h>
#include<cmath>

typedef struct t_ponto3 {
    GLfloat x,y,z;
} Ponto;
typedef Ponto Vetor;
typedef struct t_aresta3 {
    Ponto primeiro,segundo;
} Aresta;
typedef struct t_tri3{
    Ponto raiz,direito,esquerdo;
} Triangulo;

Ponto add(Ponto a, Ponto b){
    a.x+=b.x; a.y+=b.y; a.z+=b.z;
    return a;
}

Ponto sub(Ponto a, Ponto b){
    b.x-=a.x; b.y-=b.y; b.z-=a.z;
    return b;
}

Ponto makePonto(GLfloat x, GLfloat y, GLfloat z){
    Ponto p; p.x = x; p.y = y; p.z = z;
    return p;
}

Aresta makeAresta(Ponto primeiro, Ponto segundo){
    Aresta e; e.primeiro = primeiro; e.segundo = segundo;
    return e;
}

Ponto scale(GLfloat sc, Ponto p){
    p.x*=sc; p.y*=sc; p.z*=sc;
    return p;
}

GLfloat dot(Vetor v, Vetor u){
    return v.x*u.x+v.y*u.y+v.z*u.z;
}

void atrib(Ponto& p, GLfloat x, GLfloat y, GLfloat z){
    p.x = x; p.y = y; p.z = z;
}

GLfloat norm(Ponto p){
    return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}

Ponto normPonto(Ponto p){
    return scale(1/sqrt(p.x*p.x+p.y*p.y+p.z*p.z),p);
}

Ponto vectorial(Ponto primeiro, Ponto segundo){
    Ponto r;
    r.x = primeiro.y*segundo.z-primeiro.z*segundo.y;
    r.y = primeiro.z*segundo.x-primeiro.x*segundo.z;
    r.z = primeiro.x*segundo.y-primeiro.y*segundo.x;
    return r;
}

Ponto normalAt(Triangulo t){
    return vectorial(sub(t.direito,t.raiz),sub(t.esquerdo,t.raiz));
}