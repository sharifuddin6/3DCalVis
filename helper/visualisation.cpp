#include "visualisation.h"
#include <stdio.h>
#include <cmath>

Visualisation::Visualisation() { 
  mode = 1;

  tile_dimension = 0.5f;
  days = 7;
  weeks = 25;

}

void Visualisation::prototype_1() {
  // prototype_1: Flat perspective view
  float scale = 0.75;
  float gap = 1.0-scale;
  float center = (0.5*tile_dimension) -(tile_dimension)*((float)days*0.5f) -gap;

  // DRAW GRID
  glPushMatrix();
    glTranslatef(center,-1.25, -3.75);
  
//    for(int i=0; i<days; i++) {
//      for(int j=0; j<weeks; j++) {
//        
//        // tiles for days
//        glPushMatrix();
//          glTranslatef(i*tile_dimension+gap,0,j*tile_dimension*1.1);
//          //glRotatef(5.0, 1.0, 0.0, 0.0);
//          glScalef(1.0, 0.05, 1.0);
//          glColor3f(1.0,1.0,1.0);
//          drawTile((j*i)+i);
//        glPopMatrix();        
//      
//      }   
//    }

// TESTING INDIVIDUAL DAYS
    // SUNDAY TILE
    int weekday = 0;
    int week = 0;
    glPushMatrix();
      glTranslatef(weekday*tile_dimension+gap,0,week*tile_dimension);
      glScalef(1.0, 0.05, 1.0);
      glColor3f(1.0,1.0,1.0);
      drawTile(weekday,1);
    glPopMatrix();

    // FRIDAY TILE
    weekday = 5;
    week = 0;
    glPushMatrix();
      glTranslatef(weekday*tile_dimension+gap,0,week*tile_dimension);
      glScalef(1.0, 0.05, 1.0);
      glColor3f(1.0,1.0,1.0);
      drawTile(weekday,5);
    glPopMatrix();

  glPopMatrix();
}

void Visualisation::prototype_2() { 
  // prototype_2: Time tunnel view
  int segments = 7;
  float radius = 0.3;
  float height = 0.3;

  // guide lines
  for (float i = 0.0; i < segments; i += 1.0) {
    float angle = M_PI * i * 2.0 / segments ;
    float nextAngle = M_PI * (i + 1.0) * 2.0 / segments;

    /* compute sin & cosine */
    float x1 = radius * sin(angle), y1 = radius * cos(angle);
    float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);

    glBegin(GL_LINE_LOOP);

      glColor3f(1.0,1.0,1.0);
      
      // near
      glVertex3f(x1, y1, -1.0);
      glVertex3f(x2, y2, -1.0);
      glVertex3f(0, 0, -1.0);

      // far
      glVertex3f(x1, y1, -25.0);
      glVertex3f(x2, y2, -25.0);
      glVertex3f(0, 0, -25.0);

    glEnd();
   }

  // points
  glPointSize(10.0f);
  glBegin(GL_POINTS);
  for (float i = 0.0; i < segments+1; i += 1.0) {
    float angle = M_PI * i * 2.0 / segments ;
    float nextAngle = M_PI * (i + 1.0) * 2.0 / segments;

    /* compute sin & cosine */
    float x1 = radius * sin(angle), y1 = radius * cos(angle);
    float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);

    glColor3f(1.0,0.0,0.0);
      
    // near
    //glVertex3f(x1, y1, -1.0);
    //glVertex3f(x2, y2, -1.0);

    // mid point
    glVertex3f((x1+x2)*0.5, (y1+y2)*0.5, -1.0);
   
  }
  glEnd();

}

void Visualisation::prototype_3() { 
  // prototype_3: Lexis Pencil

}

void Visualisation::prototype_4() {
  // prototype_4: Fibonacci spiral view
  float rotations = 5; //How many times the spiral rotates around until it stops.
  float theta, nextTheta;
  float epsilon = 0.1f * 2.0f * M_PI;
  float x1, y1, z1;
  float x2, y2, z2;


  glBegin(GL_LINES);
  for(theta = 0.0f; theta < rotations * 2.0f * M_PI; theta += epsilon) {
    x1 = sin(theta) * theta;
    y1 = cos(theta) * theta;
    z1 = theta;

    nextTheta = theta+epsilon;    
    x2 = sin(nextTheta) * nextTheta;
    y2 = cos(nextTheta) * nextTheta;
    z2 = nextTheta;

    glVertex3f(x1,y1,z1-10);
    glVertex3f(x2,y2,z2-10);

  }
  glEnd();
}

void Visualisation::draw(int frame) {
  switch(mode) {
    case 1:
      prototype_1();
      break;
    case 2:
      prototype_2();
      break;
    case 3:
      prototype_3();
      break;
    case 4:
      prototype_4();
      break;
    default:
      break;  
  } 

}

void Visualisation::drawTile(int weekday, int day) {
  float scale = 0.75;
  float limit = tile_dimension*0.5;
  //glutSolidCube(tile_dimension*scale);

  glBegin(GL_QUADS);
    // top face
    glVertex3f(-limit, 0, -limit);
    glVertex3f(-limit, 0, limit);
    glVertex3f(limit, 0, limit);
    glVertex3f(limit, 0, -limit);

    // side left
    glVertex3f(-limit, 0, limit);
    glVertex3f(-limit, 0, -limit);
    glVertex3f(-limit, -2, -limit);
    glVertex3f(-limit, -2, limit);
    
    // side right
    glVertex3f(limit, 0, limit);
    glVertex3f(limit, 0, -limit);
    glVertex3f(limit, -2, -limit);
    glVertex3f(limit, -2, limit);

    // front face
    glColor3f(1.0, 0.5, 0.5);
    glVertex3f(-limit, 0, limit);
    glVertex3f(-limit, -2, limit);
    glVertex3f(limit-0.15, -2, limit);
    glVertex3f(limit-0.15, 0, limit);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(limit-0.15, 0, limit);
    glVertex3f(limit-0.15, -2, limit);
    glVertex3f(limit, -2, limit);
    glVertex3f(limit, 0, limit);

  glEnd();

}

// getter
char* Visualisation::getPrototypeName() {
  switch(mode) {
    case 1: 
      prototype_name = "Prototype 1: Flat Perspective view";
      break;
    case 2:
      prototype_name = "Prototype 2: Time Tunnel view";
      break;
    case 3:
      prototype_name = "Prototype 3: 3D Lexis Pencil";
      break;
    case 4: 
      prototype_name = "Prototype 4: 3D Fibonacci Spiral";
      break;
    default:
      break;
  }  
  return prototype_name;
}

// setter
void Visualisation::setPrototype(int newMode) {
  mode = newMode;
}

