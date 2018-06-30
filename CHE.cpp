//
//  CHE.cpp
//  geom_model
//
//  Created by tomlew on 10/9/14.
//  Copyright (c) 2014 tomlew. All rights reserved.
//

#include "CHE.h"

/****************************************************/
bool CHE::fit_to_bbox()
{
  if( nverts < 1 ) return false ;
  
  coord xm, xM, ym, yM, zm, zM ;
  xm = xM = verts[0] ;
  ym = yM = verts[1] ;
  zm = zM = verts[2] ;
  
  for( Vid v = 1 ; v < nverts ; ++v )
  {
    coord x = verts[ 3*v+0 ] ;
    coord y = verts[ 3*v+1 ] ;
    coord z = verts[ 3*v+2 ] ;
    
    if( x < xm ) xm = x ;
    if( x > xM ) xM = x ;
    if( y < ym ) ym = y ;
    if( y > yM ) yM = y ;
    if( z < zm ) zm = z ;
    if( z > zM ) zM = z ;
  }
  
  coord s = xM-xm ;
  if( yM-ym > s ) s = yM-ym ;
  if( zM-zm > s ) s = zM-zm ;
  if( s < 0.0000001 ) return false ;
  s = 2.0 / s ;
  
  coord xmed = 0.5*(xm+xM) ;
  coord ymed = 0.5*(ym+yM) ;
  coord zmed = 0.5*(zm+zM) ;
  
  for( Vid v = 0 ; v < nverts ; ++v )
  {
    verts[ 3*v+0 ] = s * (verts[ 3*v+0 ] - xmed ) ;
    verts[ 3*v+1 ] = s * (verts[ 3*v+1 ] - ymed ) ;
    verts[ 3*v+2 ] = s * (verts[ 3*v+2 ] - zmed ) ;
  }
  
  return true ;
}
/****************************************************/


/****************************************************/
#include <strings.h>
#include <math.h>
bool CHE::compute_normals()
{
  memset( norms, 0, 3*nverts*sizeof(coord) ) ;
  
  for( Tid t = 0 ; t < ntrigs ; ++t )
  {
    Vid v0 = trigs[ 3*t+0 ] ;
    Vid v1 = trigs[ 3*t+1 ] ;
    Vid v2 = trigs[ 3*t+2 ] ;
    
    coord x01 = verts[ 3*v1 + 0 ] - verts[ 3*v0 + 0 ] ;
    coord y01 = verts[ 3*v1 + 1 ] - verts[ 3*v0 + 1 ] ;
    coord z01 = verts[ 3*v1 + 2 ] - verts[ 3*v0 + 2 ] ;
    
    coord x02 = verts[ 3*v2 + 0 ] - verts[ 3*v0 + 0 ] ;
    coord y02 = verts[ 3*v2 + 1 ] - verts[ 3*v0 + 1 ] ;
    coord z02 = verts[ 3*v2 + 2 ] - verts[ 3*v0 + 2 ] ;
    
    coord nx = y01 * z02 - y02 * z01 ;
    coord ny = z01 * x02 - z02 * x01 ;
    coord nz = x01 * y02 - x02 * y01 ;
    
    norms[ 3*v0 + 0 ] += nx ;
    norms[ 3*v0 + 1 ] += ny ;
    norms[ 3*v0 + 2 ] += nz ;
    
    norms[ 3*v1 + 0 ] += nx ;
    norms[ 3*v1 + 1 ] += ny ;
    norms[ 3*v1 + 2 ] += nz ;
    
    norms[ 3*v2 + 0 ] += nx ;
    norms[ 3*v2 + 1 ] += ny ;
    norms[ 3*v2 + 2 ] += nz ;
  }
  
  for( Vid v = 0 ; v < nverts ; ++v )
  {
    coord &nx = norms[ 3*v + 0 ] ;
    coord &ny = norms[ 3*v + 1 ] ;
    coord &nz = norms[ 3*v + 2 ] ;
    
    coord nrm = hypot( nx, hypot(ny,nz) ) ;
    if( nrm < 0.000001 ) continue ;
    nrm = -1.0 / nrm ;
    nx *= nrm ;
    ny *= nrm ;
    nz *= nrm ;
  }
  
  return true ;
}
/****************************************************/


/****************************************************/
#include <map>
bool CHE::compute_opps()
{
  memset( opps, -1, 3*ntrigs*sizeof(HEid) ) ;
  
  std::map< std::pair<Vid,Vid> , HEid > m ;
  for( HEid he = 0 ; he < 3*ntrigs ; ++he )
  {
    Vid v1 = ori (he) ;
    Vid v2 = dest(he) ;
    
    std::pair<Vid,Vid> p = v1 < v2 ? std::make_pair( v1,v2 ) : std::make_pair( v2,v1 ) ;
    
    std::map< std::pair<Vid,Vid> , HEid >::iterator it = m.find(p) ;
    if( it == m.end() ) m[p] = he ;
    else
    {
      HEid o_he = it->second ;
      opps[he] = o_he ;
      opps[o_he] = he ;
      
      // could avoid that to detect non-pseudo-manifold
      m.erase(it) ;
    }
  }
  
  return true ;
}
/****************************************************/


/****************************************************/
#include <queue>
bool CHE::orient()
{
  bool *visited = new bool[ntrigs] ;
  memset( visited, 0, ntrigs*sizeof(bool) ) ;
  
  std::queue<HEid> q ;
  
  for( Tid t = 0 ; t < ntrigs ; ++t )
  {
    if( visited[t] ) continue ;
    
    visited[t] = true ;
    HEid he0 = opps[3*t+0] ;
    if( he0 > -1 ) q.push( he0 ) ;
    HEid he1 = opps[3*t+1] ;
    if( he1 > -1 ) q.push( he1 ) ;
    HEid he2 = opps[3*t+2] ;
    if( he2 > -1 ) q.push( he2 ) ;
    
    while( !q.empty() )
    {
      HEid he = q.front() ;
      q.pop() ;
      if( visited[he2t(he)] ) continue ;
      visited[he2t(he)] = true ;
      
      HEid he_o = opp(he) ;
      if( ori(he) != dest(he_o) /* || dest(he) != ori(he_o) */ ) // mush change the orientation
      {
        HEid he_n = next(he) ;
        HEid he_p = prev(he) ;
        Vid v   = trigs[ he ] ;
        Vid v_n = trigs[he_n] ;
        trigs[ he ] = v_n ;
        trigs[he_n] =  v  ;
        
        HEid ohe_n = opps[he_n] ;
        HEid ohe_p = opps[he_p] ;
        opps[he_p] = ohe_n ;
        opps[he_n] = ohe_p ;
        if( ohe_n > -1 ) opps[ohe_n] = he_p ;
        if( ohe_p > -1 ) opps[ohe_p] = he_n ;
      }
      
      // could check for non-orientability here
      HEid he_n = opp(next(he)) ;
      if( he_n > -1 && !visited[he2t(he_n)] ) q.push( he_n ) ;
      HEid he_p = opp(prev(he)) ;
      if( he_p > -1 && !visited[he2t(he_p)]) q.push( he_p ) ;
    }
    
    // could count connected components
  }
  
  delete visited ;
  return true ;
}
/****************************************************/


/****************************************************/
bool CHE::compute_hes()
{
  memset( hes, -1, nverts*sizeof(HEid) ) ;
  for( HEid he = 0 ; he < 3*ntrigs ; ++he )
  {
    HEid &v_he = hes[ ori(he) ] ;
    if( v_he == -1 || opp(he) == -1 ) v_he = he ;
  }

  return true ;
}
/****************************************************/


/****************************************************/
#include <stdio.h>
bool CHE::read_off( const char *filename )
{
  FILE *fp = fopen( filename, "r" ) ;
  if( !fp ) { printf( "file not found: %s!\n", filename ) ; return false ; }
  
  int nv, nt ;
  if( fscanf( fp, "OFF %d %d 0 ", &nv, &nt ) != 2 ) { printf( "file %s not in OFF format!\n", filename ) ; fclose(fp) ; return false ; }
  
  if( nv < 1 || nt < 1 ) { printf( "invalid mesh with %d vertices and %d triangles!\n", nv, nt ) ; fclose(fp) ; return false ; }
  
  nverts = nv ;
  delete verts ;
  verts = new coord[ 3*nverts ] ;
  delete norms ;
  norms = new coord[ 3*nverts ] ;
  delete hes ;
  hes = new HEid[ nverts ] ;
  
  for( Vid v = 0 ; v < nv ; ++v )
  {
    float x,y,z ;
    if( fscanf( fp, "%f %f %f ", &x, &y, &z ) != 3 )
    {
      printf( "invalid coordinates for vertex %d!\n", v ) ;
      clear() ;
      fclose(fp) ;
      return false ;
    }
    
    verts[ 3*v+0 ] = x ;
    verts[ 3*v+1 ] = y ;
    verts[ 3*v+2 ] = z ;
  }
  
  ntrigs = nt ;
  delete trigs ;
  trigs = new Vid  [ 3*ntrigs ] ;
  delete opps  ;
  opps  = new HEid [ 3*ntrigs ] ;
  for( Tid t = 0 ; t < nt ; ++t )
  {
    int n, v0,v1,v2 ;
    if( fscanf( fp, "%d %d %d %d ", &n, &v0, &v1, &v2 ) != 4 || n != 3 )
    {
      printf( "invalid triangle %d with %d vertices!\n", t, n ) ;
      clear() ;
      fclose(fp) ;
      return false ;
    }
    
    trigs[ 3*t+0 ] = v0 ;
    trigs[ 3*t+1 ] = v1 ;
    trigs[ 3*t+2 ] = v2 ;
  }
  
  fclose( fp ) ;
  
  printf( "triangle mesh %s read with %d vertices and %d triangles!\n", filename, nverts, ntrigs ) ;
  
  return compute_opps() && orient() && compute_hes() && fit_to_bbox() && compute_normals() ;
}
/****************************************************/
