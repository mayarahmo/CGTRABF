// ...

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#	include <windows.h>
#include <GL/glut.h>

#include "CHE.cpp"
#include "ArcBall.cpp"


ArcBall arcball ;
CHE che ;


/****************************************************/
void display_cb(void)
{
  // Clear frame buffer and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  glMultMatrixd( arcball.get_rotation_matrix() ) ;
  
  
  {
    glColor3f(1,1,1);
    glutWireSphere( 2.0, 8, 6 ) ;
  }
  
  
  glDisable(GL_BLEND) ;
  glColor4f(1,1,0,1);
  glBegin( GL_TRIANGLES ) ;
  {
    for( CHE::t_iterator it = che.t_begin() ; it() ; ++it )
    {
      CHE::v_iterator v0 = che.v_begin(it.v0() ) ;
      CHE::v_iterator v1 = che.v_begin(it.v1() ) ;
      CHE::v_iterator v2 = che.v_begin(it.v2() ) ;

      glNormal3fv( v0.nxyz() ) ;
      glVertex3fv( v0. xyz() ) ;

      glNormal3fv( v1.nxyz() ) ;
      glVertex3fv( v1. xyz() ) ;

      glNormal3fv( v2.nxyz() ) ;
      glVertex3fv( v2. xyz() ) ;
}
  }
  glEnd() ;

  glDisable(GL_BLEND) ;
  glColor4f(0.5,0.5,0.5,0.5);
  glLineWidth(1.0);
  glBegin( GL_LINES ) ;
  {
    for( CHE::t_iterator it = che.t_begin() ; it() ; ++it )
    {
      CHE::v_iterator v0 = che.v_begin(it.v0() ) ;
      CHE::v_iterator v1 = che.v_begin(it.v1() ) ;
      CHE::v_iterator v2 = che.v_begin(it.v2() ) ;
      
      glVertex3fv( v0.xyz() ) ;
      glVertex3fv( v1.xyz() ) ;

      glVertex3fv( v1.xyz() ) ;
      glVertex3fv( v2.xyz() ) ;

      glVertex3fv( v2.xyz() ) ;
      glVertex3fv( v0.xyz() ) ;
    }
  }
  glEnd() ;

  // Make sure changes appear onscreen
  glutSwapBuffers();
}
/****************************************************/



/****************************************************/
void reshape_cb(GLint width, GLint height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
//  if(width > height)  // check height=0
//    glOrtho(-((GLdouble)width/height), ((GLdouble)width/height), -1, 1, -1, 1);
//  else
//    glOrtho(-1, 1, -((GLdouble)height/width), ((GLdouble)height/width), -1, 1);
  gluPerspective( 60.0, (GLdouble)width/height, 0.1, 8.0) ;
  gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0) ;
  
  
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay() ;
}
/****************************************************/



// Respond to mouse button presses.
GLint viewport[4];
//GLdouble modelview[16];
//GLdouble projection[16];
//GLfloat winZ;
double ux, uy ;


/****************************************************/
void mouse_cb(int button, int state, int x, int y)
{
  if( state == GLUT_DOWN )
  {
    glGetIntegerv( GL_VIEWPORT, viewport );
    ux = (2.0*(x - viewport[0]))/viewport[2] - 1.0 ;
    uy = 1.0 - (2.0*(y - viewport[1]))/viewport[3] ;
  }
  else if( state == GLUT_UP )
  {
    double vx = (2.0*(x - viewport[0]))/viewport[2] - 1.0 ;
    double vy = 1.0 - (2.0*(y - viewport[1]))/viewport[3] ;
    
    arcball.click( ux,uy , vx,vy ) ;

    glutPostRedisplay() ;
  }
}
/****************************************************/


/****************************************************/
void motion_cb(int x, int y)
{
  double vx = (2.0*(x - viewport[0]))/viewport[2] - 1.0 ;
  double vy = 1.0 - (2.0*(y - viewport[1]))/viewport[3] ;
  arcball.click( ux,uy , vx,vy ) ;
  ux = vx ;
  uy = vy ;
  
  glutPostRedisplay() ;
}
/****************************************************/


/****************************************************/
void idle_cb(void)
{
  // Force redraw
//  glutPostRedisplay();
}
/****************************************************/




/****************************************************/
void keyboard_cb(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27:             // ESCAPE key
      exit (0);
      break;
      
    case 'b': che.read_off( "bunny.off" ) ;
      break ;

    case 't': che.read_off( "tetra.off" ) ;
      break ;

    case 'c': che.read_off( "cone.off" );
      break;
  }
  
  glutPostRedisplay();
}
/****************************************************/



/****************************************************/
int main(int argc, char** argv)
{
  // GLUT Window Initialization:
  glutInit (&argc, argv);
  glutInitWindowSize (800, 600);
  glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA );
  glutCreateWindow ("Geometric Modeling");
  
  // Set up OpenGL lights
  GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
  GLfloat light0_diffuse[] =  {0.6f, 0.6f, 1.0f, 1.0f};
  GLfloat light0_position[] = {1.0f, 1.0f, 1.0f, 0.0f};
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glEnable( GL_COLOR_MATERIAL ) ;
  glEnable( GL_AUTO_NORMAL ) ;

  // anti-aliasing
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST) ;
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT , GL_NICEST) ;

  // openGL init
  glEnable(GL_DEPTH_TEST);
  
  // Register callbacks:
  glutDisplayFunc (display_cb);
  glutReshapeFunc (reshape_cb);
  glutKeyboardFunc(keyboard_cb);
  glutMouseFunc   (mouse_cb);
  glutMotionFunc  (motion_cb);
//  glutIdleFunc (idle_cb);

  // Turn the flow of control over to GLUT
  glutMainLoop ();

  return 0;
}
/****************************************************/
