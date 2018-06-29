#ifndef ALGORITHM_CHE_H
#define ALGORITHM_CHE_H
#include "LA3D.cpp"
#include "che_struct.cpp"

Vetor normalToHE_Point(HalfEdge he){
    HalfEdge next, prev, *start;
    start = he.next;
    Vetor normal_r = makePonto(0,0,0);
    do{
        next = *he.next;
        prev = *next.next;
        
        Vetor a, b, c;
        a = sub(he.sc.p,next.sc.p);
        b = sub(he.sc.p,prev.sc.p);
        c = vectorial(a,b);
        //printf("%f %f %f\n",next.sc.p.x,next.sc.p.y,next.sc.p.z);
        //printf("%f %f %f e ",a.x,a.y,a.z);
        //printf("%f %f %f -> ",b.x,b.y,b.z);
        //printf("%f %f %f\n",c.x,c.y,c.z);
        normal_r = add(normal_r,normPonto(c));

        he = *prev.twin;
    }while(start != he.next);
    return normPonto(normal_r);
}

#endif