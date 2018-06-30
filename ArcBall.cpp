//
//  ArcBall.cpp
//  geom_model
//
//  Created by tomlew on 9/18/14.
//  Copyright (c) 2014 tomlew. All rights reserved.
//

#include <math.h>
#include "ArcBall.h"


ArcBall::ArcBall ()
{
  _a = 1.0 ;
  _b = 0.0 ;
  _c = 0.0 ;
  _d = 0.0 ;

  _m[ 3] = 0.0 ;
  _m[ 7] = 0.0 ;
  _m[11] = 0.0 ;
  _m[12] = 0.0 ;
  _m[13] = 0.0 ;
  _m[14] = 0.0 ;
  _m[15] = 1.0 ;
  
  _m_needs_update = true ;
}

bool ArcBall::click( double ux, double uy, double vx, double vy )
{
  // compute quaternion -qv.qu
  double uz = ux*ux + uy*uy ;
  if( uz > 1.0 )
  {
    uz = 1.0 / sqrt(uz) ;
    ux *= uz ;
    uy *= uz ;
    uz = 0.0 ;
  }
  else
    uz = sqrt( 1.0 - uz ) ;

  double vz = vx*vx + vy*vy ;
  if( vz > 1.0 )
  {
    vz = 1.0 / sqrt(vz) ;
    vx *= vz ;
    vy *= vz ;
    vz = 0.0 ;
  }
  else
    vz = sqrt( 1.0 - vz ) ;

//  double uz = 1.0 - (fabs(ux)<fabs(uy) ? fabs(uy) : fabs(ux) ) ;
//  double vz = 1.0 - (fabs(vx)<fabs(vy) ? fabs(vy) : fabs(vx) ) ;
 
  double qa = ux*vx + uy*vy + uz*vz ;
  double qb = uz*vy - uy*vz ;
  double qc = ux*vz - uz*vx ;
  double qd = uy*vx - ux*vy ;

  // compute the square root of -qv.qu
  qa  = sqrt(0.5*qa + 0.5) ;
  if( qa > 1.0e-6 ) // otherwise qb=qc=qd=0
  {
    qb /= 2.0*qa ;
    qc /= 2.0*qa ;
    qd /= 2.0*qa ;
  }
  
  // multiply with previous quaternion
  double a = _a ;
  double b = _b ;
  double c = _c ;
  double d = _d ;
  _a = qa*a - qb*b - qc*c - qd*d ;
  _b = qa*b + qb*a + qc*d - qd*c ;
  _c = qa*c + qc*a + qd*b - qb*d ;
  _d = qa*d + qd*a + qb*c - qc*b ;
  
//  _a = qa ;
//  _b = qb ;
//  _c = qc ;
//  _d = qd ;
  
  // normalize once in a while
  static int count = 0 ;
  if( ++count > 77 )
  {
    count = 0 ;
    double nrm = hypot( hypot(_a,_b) , hypot(_c,_d) ) ;
    if( nrm < 1.0e-6 ) return false ;
    nrm = 1.0/nrm ;
    _a *= nrm ;
    _b *= nrm ;
    _c *= nrm ;
    _d *= nrm ;
  }
  
  _m_needs_update = true ;
  
  return true ;
}

double *ArcBall::get_rotation_matrix()
{
  if( _m_needs_update )
  {
    _m[ 0] = _a*_a + _b*_b - _c*_c - _d*_d ;
    _m[ 5] = _a*_a - _b*_b + _c*_c - _d*_d ;
    _m[10] = _a*_a - _b*_b - _c*_c + _d*_d ;
    
    _m[ 1] = 2.0*(_b*_c + _a*_d ) ;
    _m[ 4] = 2.0*(_b*_c - _a*_d ) ;
    _m[ 8] = 2.0*(_b*_d + _a*_c ) ;
    _m[ 2] = 2.0*(_b*_d - _a*_c ) ;
    _m[ 6] = 2.0*(_c*_d + _a*_b ) ;
    _m[ 9] = 2.0*(_c*_d - _a*_b ) ;
    
    _m_needs_update = false ;
  }

  return _m ;
}
