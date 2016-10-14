#include "HNode.hpp"

void vertexcopy(float *src,float *dest){
  dest[0]=src[0];
  dest[1]=src[1];
  dest[2]=src[2];
  dest[3]=src[3];
}

HNode::HNode(HNode* par){
  tx = 0;
  ty = 0;
  tz = 0;
  rx = 0;
  ry = 0;
  rz = 0;
  ptx=pty=ptz=0;

  R=G=B=0;

  if(par!=NULL){
    parent=par;
    parent->add_child(this);
  }

  obj_type = -1;
  quad  = gluNewQuadric();
  base = inRadius = 0;
  top = outRadius = 0;
  height = 0;
  slices = 50;
  nsides = 0;
  stacks = 10;
  rings = 0;
  cuboid_height = cuboid_length = cuboid_breadth = 0;
  triangle_x1, triangle_y1, triangle_x2, triangle_y2 = 0;
}

void HNode::add_child(HNode *child){
  children.push_back(child);
}

void HNode::render(){
  //Translate the origin
  glTranslatef(tx,ty,tz);
  //Rotate at translated origin
  glRotatef(rx, 1.0, 0.0, 0.0);
  glRotatef(ry, 0.0, 1.0, 0.0);
  glRotatef(rz, 0.0, 0.0, 1.0);
  //Translate before rotation(if any)
  glTranslatef(ptx,pty,ptz);

  if(obj_type == 0){
    // glu
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluCylinder(quad, base, top, height, slices, stacks);
  }
  else if(obj_type == 1){
    //cuboid

    // //to draw unfilled cuboid
    // glClear(GL_COLOR_BUFFER_BIT);
    // glMatrixMode( GL_PROJECTION );
    // glLineWidth(5);

    glBegin(GL_QUADS);
 
      //Front
      glNormal3f(0.0f, 0.0f, 1.0f);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, 0.0f, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, cuboid_height, cuboid_breadth);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, cuboid_height, cuboid_breadth);
   
      //Right
      glNormal3f(1, 0, 0);
      glVertex3f(cuboid_length, 0.0f, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, 0, 0);
      //glNormal3f(1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, cuboid_height, 0);
      //glNormal3f(1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, cuboid_height, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, 1.0f);
   
      //Back
      glNormal3f(0.0f, 0.0f, -1.0f);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, 0, 0);
      glVertex3f(0, cuboid_height, 0);
      glVertex3f(cuboid_length, cuboid_height, 0);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, 0, 0);
   
      //Left
      glNormal3f(-1.0f, 0.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(0, 0.0f, cuboid_breadth);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(0, cuboid_height, cuboid_breadth);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, cuboid_height, 0);

      //top
      glNormal3f(0.0f, 1.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, cuboid_height, 0);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, cuboid_height, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, cuboid_height, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, cuboid_height, 0);
   
      //bottom
      glNormal3f(0.0f, -1.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, 0.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, 0.0f, cuboid_breadth);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, 0, cuboid_breadth);
 
    glEnd();
    glFlush();
  }
  else if(obj_type == 2){
    glutSolidTorus(inRadius, outRadius, nsides, rings);
  }
  else if(obj_type == 3){
    glBegin(GL_TRIANGLES);
      glVertex3f(tx, ty, tz);
      glVertex3f(triangle_x1, triangle_y1, tz);
      glVertex3f(triangle_x2, triangle_y2, tz);
    glEnd();
  }
  else{
    //do nothing
  }
}

void HNode::set_color(float R, float G, float B){
  this->R = R;
  this->G = G;
  this->B = B;
}

void HNode::change_parameters(float tx,float ty,float tz,float rx,float ry,float rz){
  this->tx=tx;
  this->ty=ty;
  this->tz=tz;
  this->rx=rx;
  this->ry=ry;
  this->rz=rz;
}

void HNode::change_preparameters(float ptx, float pty, float ptz){
  this->ptx = ptx;
  this->pty = pty;
  this->ptz = ptz;
}

void HNode::render_tree(){
  glPushMatrix();
  // glBegin(GL_POINTS);
  //   // glVertex3f(0.0f, 0.5f, 0.0f);
  //   // glVertex3f(0.5f, -0.5f, 0.0f);
  //   // glVertex3f(-0.5f, -0.5f, 0.0f);
  //   glVertex3f(0,0,0);
  // glEnd();
  glColor3f(R,G,B);
  render();
  for(int i=0;i<children.size();i++){
    children[i]->render_tree();
  }
  glPopMatrix();
}

void HNode::inc_rx(){
  rx++;
  if(rx>360)
  rx-=360;
}
void HNode::inc_ry(){
  ry++;
  if(ry>360)
  ry-=360;
}
void HNode::inc_rz(){
  rz++;
  if(rz>360)
  rz-=360;
}
void HNode::dec_rx(){
  rx--;
  if(rx<0)
  rx+=360;
}
void HNode::dec_ry(){
  ry--;
  if(ry<0)
  ry+=360;
}
void HNode::dec_rz(){
  rz--;
  if(rz<0)
  rz+=360;
}

void HNode::dec_ty(){
  ty--;
}

void HNode::inc_tx(){
  tx++;
}

void HNode::inc_ty(){
  ty++;
}

void HNode::dec_tx(){
  tx--;
}

void HNode::inc_tz(){
  tz++;
}

void HNode::dec_tz(){
  tz--;
}