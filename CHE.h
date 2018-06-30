//
//  CHE.h
//  geom_model
//
//  Created by tomlew on 10/9/14.
//  Copyright (c) 2014 tomlew. All rights reserved.
//

#ifndef __geom_model__CHE__
#define __geom_model__CHE__

#include <stdlib.h>

typedef float coord ;
typedef int   Vid   ;
typedef int  HEid   ;
typedef int   Tid   ;

class CHE
{
  protected :
  Vid nverts ;
  coord *verts ; // 3*nv: x,y,z
  coord *norms ; // 3*nv: nx,ny,nz
  HEid  *hes   ; // nv
    
  Tid ntrigs ;
  Vid   *trigs ; // 3*nt: v0,v1,v2
  HEid  *opps  ; // 3*nt
  

  public :
  CHE() : nverts(0), verts(NULL), norms(NULL), hes(NULL), ntrigs(0), trigs(NULL), opps(NULL) {}
  
  ~CHE() { clear() ; }
  
  bool clear()
  {
    delete verts ; verts = NULL ; nverts = 0 ;
    delete norms ; norms = NULL ;
    delete hes   ; hes   = NULL ;
    delete trigs ; trigs = NULL ; ntrigs = 0 ;
    delete opps  ; opps  = NULL ;
    return true ;
  }
  
  public :
  Tid n_trigs() const { return ntrigs ; } ;
  Vid n_verts() const { return nverts ; } ;

  Tid  he2t( HEid he ) const { return he/3 ; }
  HEid next( HEid he ) const { return (he%3==2) ? he-2 : he+1 ; }
  HEid prev( HEid he ) const { return (he%3==0) ? he+2 : he-1 ; }
  Vid  ori ( HEid he ) const { return trigs[he] ; }
  Vid  dest( HEid he ) const { return ori(next(he)) ; }
  HEid opp ( HEid he ) const { return opps[he] ; }
  
  public :
  bool read_off( const char *filename ) ;
  
  bool fit_to_bbox    () ;
  bool compute_normals() ;
  bool compute_opps   () ;
  bool orient         () ;
  bool compute_hes    () ;
  
public:
  class t_iterator
  {
    protected :
    Tid  t     ;
    Tid  t_end ;
    Vid *ptr   ;
    
    public :
    t_iterator( CHE &che, Tid t_ini ) : t(t_ini), t_end(che.n_trigs()), ptr(che.trigs+3*t_ini) {}
    ~t_iterator() {}
    
    bool operator() () { return t < t_end ; }
    t_iterator &operator++ () { ++t ; ptr += 3 ; return *this ; }
    
    Vid v0() { return ptr[0] ; }
    Vid v1() { return ptr[1] ; }
    Vid v2() { return ptr[2] ; }
  } ;
  t_iterator t_begin( Tid t_ini=0 ) { return t_iterator(*this,t_ini) ; }
  
  
  class v_iterator
  {
    protected :
    Vid  v     ;
    Vid  v_end ;
    coord *v_ptr   ;
    coord *n_ptr   ;
    
    public :
    v_iterator( CHE &che, Vid v_ini ) : v(v_ini), v_end(che.n_verts()), v_ptr(che.verts+3*v_ini), n_ptr(che.norms+3*v_ini) {}
    ~v_iterator() {}
    
    bool operator() () { return v < v_end ; }
    v_iterator &operator++ () { ++v ; v_ptr += 3 ; n_ptr += 3 ; return *this ; }
    
    coord *xyz() { return v_ptr ; }
    coord  x() { return v_ptr[0] ; }
    coord  y() { return v_ptr[1] ; }
    coord  z() { return v_ptr[2] ; }

    coord *nxyz() { return n_ptr ; }
    coord nx() { return n_ptr[0] ; }
    coord ny() { return n_ptr[1] ; }
    coord nz() { return n_ptr[2] ; }
  } ;
  v_iterator v_begin( Vid v_ini=0 ) { return v_iterator(*this,v_ini) ; }
};

#endif /* defined(__geom_model__CHE__) */
