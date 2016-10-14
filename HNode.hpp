#include <iostream>
#include <GL/glut.h>
#include <vector>

#ifndef _HNODE_HPP_
#define _HNODE_HPP_

void vertexcopy(float *src,float *dest);

// A simple class that represents a node in the hierarchy tree
class HNode {
private:
  
  // int num_vertices;		//no of vertices
  // float **vertex_pos;	//pointer to array of all vertices
  // float **vertex_col;	//pointer to array of colors of vertices

  std::vector<HNode*> children;		//vector containing pointers to children nodes
  HNode* parent;					//pointer to parent node
  
  //default = -1
  //0 - cylinder
  //1 - cuboid
  //2 - torus
  //3 - triangle

public:

  float tx,ty,tz;   //translation from its origin
  float rx,ry,rz;   //rotation about x, y, z
  float ptx,pty,ptz;  //translation before rotation needed in some cases simplifies stuff
  float R,G,B;
  
  GLUquadric* quad;
  GLdouble base;
  GLdouble inRadius;
  GLdouble top;
  GLdouble outRadius;
  GLdouble height;
  GLint slices;
  GLint nsides;
  GLint stacks;
  GLint rings;
  float cuboid_height, cuboid_length, cuboid_breadth;
  int obj_type;
  float triangle_x1, triangle_y1, triangle_x2, triangle_y2;


  // HNode (HNode* parent, int num_vertices, float pos_v4[][4],  float col_v4[][4]);		//default constructor of the node
  HNode (HNode* par);
  void add_child(HNode*);		//function to add a child node to this node
  void render();				//function to render(create) this node
  void change_parameters(float tx,float ty,float tz,float rx,float ry,float rz);		//change parameters of this node - rotate/translate it
  void change_preparameters(float ptx, float pty, float ptz);
  void render_tree();			//function to render the whole tree - this + children (NOT parents)
  void set_color(float R, float G, float B);
  // void (*render_function)();

  // void make_cuboid();
  // void make_cylinder();
  // void make_torus();
  
  //increment/decrement parameters
  void inc_rx();
  void inc_ry();
  void inc_rz();
  void dec_rx();
  void dec_ry();
  void dec_rz();
  void dec_ty();
  void inc_tx();
  void inc_ty();
  void dec_tx();
  void inc_tz();
  void dec_tz();
};

#endif