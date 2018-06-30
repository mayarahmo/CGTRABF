//
//  ArcBall.h
//  geom_model
//
//  Created by tomlew on 9/18/14.
//  Copyright (c) 2014 tomlew. All rights reserved.
//

#ifndef __geom_model__ArcBall__
#define __geom_model__ArcBall__

class ArcBall {
  double _a, _b, _c, _d ; // quaternion
  double _m[16] ;
  bool   _m_needs_update ;

public:
  ArcBall ()  ;
  ~ArcBall() {}
  
  bool click( double ux, double uy, double vx, double vy ) ;
  
  double *get_rotation_matrix() ;
};

#endif /* defined(__geom_model__ArcBall__) */
