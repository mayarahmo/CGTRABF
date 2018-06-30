#ifndef TRANSFORM_LIB
#define TRANSFORM_LIB

#include "CHE.cpp"
#include "LA3D.cpp"
#include <queue>
#include <set>
#include <cmath>

void linearTransform(GLfloat a, GLfloat b, GLfloat c, CHE::v_iterator& vit){
    Vetor normal = makePonto(vit.nx(),vit.ny(),vit.nz());
    Ponto p = makePonto(vit.x(),vit.y(),vit.z());
    GLfloat func = a*p.x+b*p.y+c*p.z;
    //if(func < 0) func = - func;
    //printf("%f\n",func);
    p = add(p,scale(func,normal));
    coord* vertex = vit.xyz();
    vertex[0] = p.x;
    vertex[1] = p.y;
    vertex[2] = p.z;
}

void linear(GLfloat a, GLfloat b, GLfloat c, CHE& mesh){
    std::set<Vid> vids;
    for(CHE::t_iterator it = mesh.t_begin(); it(); ++it){
        CHE::v_iterator v0 = mesh.v_begin(it.v0());
        CHE::v_iterator v1 = mesh.v_begin(it.v1());
        CHE::v_iterator v2 = mesh.v_begin(it.v2());

        if(vids.find(it.v0()) == vids.end() ) linearTransform(a,b,c,v0);
        if(vids.find(it.v1()) == vids.end() ) linearTransform(a,b,c,v1);
        if(vids.find(it.v2()) == vids.end() ) linearTransform(a,b,c,v2);

        vids.insert(it.v0()); vids.insert(it.v1()); vids.insert(it.v2());
    }
    if(!mesh.fit_to_bbox()) printf("Deu ruim no bbox\n");
    if(!mesh.compute_normals()) printf("Deu ruim nas normais!\n");
}

void sineTransform(GLfloat a, GLfloat b, GLfloat c, CHE::v_iterator& vit){
    Vetor normal = makePonto(vit.nx(),vit.ny(),vit.nz());
    Ponto p = makePonto(vit.x(),vit.y(),vit.z());
    GLfloat func = sin(a*p.x+b*p.y+c*p.z);
    //if(func < 0) func = - func;
    //printf("%f\n",norm(normal));
    p = add(p,scale(func,normal));
    coord* vertex = vit.xyz();
    vertex[0] = p.x;
    vertex[1] = p.y;
    vertex[2] = p.z;
}

void sine(GLfloat a, GLfloat b, GLfloat c, CHE& mesh){
    std::set<Vid> vids;
    for(CHE::t_iterator it = mesh.t_begin(); it(); ++it){
        CHE::v_iterator v0 = mesh.v_begin(it.v0());
        CHE::v_iterator v1 = mesh.v_begin(it.v1());
        CHE::v_iterator v2 = mesh.v_begin(it.v2());

        if(vids.find(it.v0()) == vids.end() ) sineTransform(a,b,c,v0);
        if(vids.find(it.v1()) == vids.end() ) sineTransform(a,b,c,v1);
        if(vids.find(it.v2()) == vids.end() ) sineTransform(a,b,c,v2);

        vids.insert(it.v0()); vids.insert(it.v1()); vids.insert(it.v2());
    }
    if(!mesh.fit_to_bbox()) printf("Deu ruim no bbox\n");
    if(!mesh.compute_normals()) printf("Deu ruim nas normais!\n");
}

void cosineTransform(GLfloat a, GLfloat b, GLfloat c, CHE::v_iterator& vit){
    Vetor normal = makePonto(vit.nx(),vit.ny(),vit.nz());
    Ponto p = makePonto(vit.x(),vit.y(),vit.z());
    GLfloat func = cos(a*p.x+b*p.y+c*p.z);
    //if(func < 0) func = - func;
    //printf("%f\n",norm(normal));
    p = add(p,scale(func,normal));
    coord* vertex = vit.xyz();
    vertex[0] = p.x;
    vertex[1] = p.y;
    vertex[2] = p.z;
}

void cosine(GLfloat a, GLfloat b, GLfloat c, CHE& mesh){
    std::set<Vid> vids;
    for(CHE::t_iterator it = mesh.t_begin(); it(); ++it){
        CHE::v_iterator v0 = mesh.v_begin(it.v0());
        CHE::v_iterator v1 = mesh.v_begin(it.v1());
        CHE::v_iterator v2 = mesh.v_begin(it.v2());

        if(vids.find(it.v0()) == vids.end() ) cosineTransform(a,b,c,v0);
        if(vids.find(it.v1()) == vids.end() ) cosineTransform(a,b,c,v1);
        if(vids.find(it.v2()) == vids.end() ) cosineTransform(a,b,c,v2);

        vids.insert(it.v0()); vids.insert(it.v1()); vids.insert(it.v2());
    }
    if(!mesh.fit_to_bbox()) printf("Deu ruim no bbox\n");
    if(!mesh.compute_normals()) printf("Deu ruim nas normais!\n");
}

void quadraticTransform(GLfloat a, GLfloat b, GLfloat c, CHE::v_iterator& vit){
    Vetor normal = makePonto(vit.nx(),vit.ny(),vit.nz());
    Ponto p = makePonto(vit.x(),vit.y(),vit.z());
    GLfloat func = a*p.x*p.x+b*p.y*p.y+c*p.z*p.z;
    //if(func < 0) func = - func;
    //printf("%f\n",norm(normal));
    p = add(p,scale(func,normal));
    coord* vertex = vit.xyz();
    vertex[0] = p.x;
    vertex[1] = p.y;
    vertex[2] = p.z;
}

void quadratic(GLfloat a, GLfloat b, GLfloat c, CHE& mesh){
    std::set<Vid> vids;
    for(CHE::t_iterator it = mesh.t_begin(); it(); ++it){
        CHE::v_iterator v0 = mesh.v_begin(it.v0());
        CHE::v_iterator v1 = mesh.v_begin(it.v1());
        CHE::v_iterator v2 = mesh.v_begin(it.v2());

        if(vids.find(it.v0()) == vids.end()) quadraticTransform(a,b,c,v0);
        if(vids.find(it.v1()) == vids.end()) quadraticTransform(a,b,c,v1);
        if(vids.find(it.v2()) == vids.end()) quadraticTransform(a,b,c,v2);

        vids.insert(it.v0()); vids.insert(it.v1()); vids.insert(it.v2());
    }
    if(!mesh.fit_to_bbox()) printf("Deu ruim no bbox\n");
    if(!mesh.compute_normals()) printf("Deu ruim nas normais!\n");
}

Ponto vit_to_point(CHE::v_iterator vit){
    Ponto p = makePonto(vit.x(),vit.y(),vit.z());
    return p;
}

GLfloat kfunc(HEid itt, CHE& mesh){
    CHE::v_iterator next = mesh.v_begin(mesh.next(itt));;
    CHE::v_iterator prev = mesh.v_begin(mesh.prev(itt));
    CHE::v_iterator he = mesh.v_begin(mesh.ori(itt));
    Vid start = mesh.next(itt);;
    
    GLfloat sum = 4*atan(1.0);
    do{
        next = mesh.v_begin(mesh.next(itt));
        prev = mesh.v_begin(mesh.prev(itt));
        he =   mesh.v_begin(mesh.ori(itt));

        Ponto praiz, pnext, pprev;
        praiz = vit_to_point(he);
        pnext = vit_to_point(next);
        pprev = vit_to_point(prev);

        Vetor a, b;
        a = sub(praiz,pnext);
        b = sub(praiz,pprev);
        printf("%f %f %f\n",a.x,a.y,a.z);
        printf("%f %f %f\n",b.x,b.y,b.z);
        sum = sum - acos( dot(a,b)/(norm(a)*norm(b)) );
        itt = mesh.opp(mesh.prev(itt));
    }while(start != mesh.next(itt));
    return sum;
}

void KTransform(HEid heid, CHE& mesh){
    CHE::v_iterator vit = mesh.v_begin(mesh.ori(heid));
    Vetor normal = makePonto(vit.nx(),vit.ny(),vit.nz());
    Ponto p = makePonto(vit.x(),vit.y(),vit.z());
    GLfloat func = kfunc(heid,mesh);
    printf("%f\n",func);
    p = add(p,scale(func,normal));
    coord* vertex = vit.xyz();
    vertex[0] = p.x;
    vertex[1] = p.y;
    vertex[2] = p.z;
}

void kfunction(CHE& mesh){
    for(HEid it = 0; it < mesh.n_trigs(); ++it){
        KTransform(it,mesh);
    }
    if(!mesh.fit_to_bbox()) printf("Deu ruim no bbox\n");
    if(!mesh.compute_normals()) printf("Deu ruim nas normais!\n");
}
#endif