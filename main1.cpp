#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "HNode.hpp"
#include <cmath>

using namespace std;


HNode *node[10];
HNode *frame[8];
HNode *wheel_front;
HNode *wheel_back;
HNode *spoke_front[9];
HNode *spoke_back[9];
HNode *spoke_front2[9];
HNode *spoke_back2[9];
HNode *spoke_front_extra[9];
HNode *spoke_back_extra[9];
HNode *spoke_front2_extra[9];
HNode *spoke_back2_extra[9];
HNode *wheel_axis_f, *wheel_axis_b;
HNode *pedal_cuboid[2];
HNode *gear[2];
HNode *gear_spokes[5];
HNode *seat[2];
HNode *pedal_rod[2];
HNode *pedal_rod_across;
HNode *axle;
HNode *across_gear;


HNode *handle_connect_with_frame, *handle_connect_front_wheel_across, 
      *handle_connect_front_wheel_left, *handle_connect_front_wheel_right,
      *handlebar_connector, *handlebar_connector_across, *handlebar_left, *handlebar_right;

  //static variables
  float wheel_outer_radius = 24;
  float wheel_tyre_radius = 1;
  float bar_radius = 2;
  float handlebar_connector_across_length = 23;
  float handlebar_connector_length = 15;
  float spoke_length = 21;
  float spoke_radius = 0.3;
  float extra_spoke_length = 2;
  float extra_spoke_radius = 0.4;
  float handle_connect_with_frame_length = 23;
  float handle_connect_front_wheel_across_length = 8;
  float handle_connect_front_wheel_length = wheel_outer_radius + bar_radius + 0.5;
  float handlebar_handle_length = 10;
  float wheel_axis_length = handle_connect_front_wheel_across_length - 2*bar_radius;

  float frame_upper_horizontal_len = 50;  //123
  float frame_lower_horizontal_len = 55;
  float frame_right_vertical_len = 48;
  float frame_upper_right_horizontal_len = 40;
  float frame_lower_right_horizontal_len = 35;
  float outer_gear_inRadius = 1;
  float inner_gear_radius = 1.5;

  float axle_length = 8;
  float across_gear_length = 4;

  //dynamic variables  
  float handle_rotation = 0;
  float wheel_rotation = 0;


//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 'X':
      glRotatef(1,1,0,0);
      glutPostRedisplay();
      break;
    case 'Y':
      glRotatef(1,0,1,0);
      glutPostRedisplay();
      break;      
    case 'Z':
      glRotatef(1,0,0,1);
      glutPostRedisplay();
      break;     
    case 'x':
      glRotatef(1,-1,0,0);
      glutPostRedisplay();
      break;
    case 'y':
      glRotatef(1,0,-1,0);
      glutPostRedisplay();
      break;      
    case 'z':
      glRotatef(1,0,0,-1);
      glutPostRedisplay();
      break;     
    case 'H':
      handle_rotation++;
      handle_connect_with_frame->rz++;
      glutPostRedisplay();
      break;
    case 'h':
      handle_rotation--;
      handle_connect_with_frame->rz--;
      glutPostRedisplay();
      break;
    case 'F':
      wheel_rotation++;
      wheel_front->rz++;
      wheel_back->rz++;
      glutPostRedisplay();
      break;
    case 'B':
      wheel_rotation--;
      wheel_front->rz--;
      wheel_back->rz--;
      glutPostRedisplay();
      break;
    case 'P':
      gear[0]->rz++;
      pedal_cuboid[0]->change_parameters(0,1,0,0,45+gear[0]->rz,0);
      pedal_cuboid[1]->change_parameters(0,-pedal_cuboid[1]->cuboid_height - 1,0,0,45+gear[0]->rz,0);
      glutPostRedisplay();
      break;
    case 'p':
      gear[0]->rz--;
      pedal_cuboid[0]->change_parameters(0,1,0,0,45+gear[0]->rz,0);
      pedal_cuboid[1]->change_parameters(0,-pedal_cuboid[1]->cuboid_height - 1,0,0,45+gear[0]->rz,0);
      glutPostRedisplay();
      break;
  }
  if (key == 27)
  exit(0);
}

void display(void){
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  node[0]->render_tree();
  glutSwapBuffers();
}

void init(void){
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);
  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);
  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(80.0, 1.0, 1.0, 200.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 100.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{

  // of the first node - vetical cylinder containing the front handle
  node[0] = new HNode(NULL);
  
  frame[0] = new HNode(NULL);
  node[0]->add_child(frame[0]);

  wheel_front = new HNode(NULL);
  wheel_back = new HNode(NULL);
  node[0]->add_child(wheel_back);

  for(int i=0; i<9; i++){
    spoke_back[i] = new HNode(NULL);
    spoke_front[i] = new HNode(NULL);
    wheel_front->add_child(spoke_front[i]);
    wheel_back->add_child(spoke_back[i]);

    spoke_back2[i] = new HNode(NULL);
    spoke_front2[i] = new HNode(NULL);
    wheel_front->add_child(spoke_front2[i]);
    wheel_back->add_child(spoke_back2[i]);

    spoke_back2_extra[i] = new HNode(NULL);
    spoke_back_extra[i] = new HNode(NULL);
    spoke_front_extra[i] = new HNode(NULL);
    spoke_front2_extra[i] = new HNode(NULL);
    spoke_back[i]->add_child(spoke_back_extra[i]);
    spoke_back2[i]->add_child(spoke_back2_extra[i]);
    spoke_front[i]->add_child(spoke_front_extra[i]);
    spoke_front2[i]->add_child(spoke_front2_extra[i]);
  }

  wheel_axis_f = new HNode(NULL);
  wheel_axis_b = new HNode(NULL);
  wheel_front->add_child(wheel_axis_f);
  wheel_back->add_child(wheel_axis_b);

  //handle
  handle_connect_with_frame = new HNode(NULL);
  node[0]->add_child(handle_connect_with_frame);

  handle_connect_front_wheel_across = new HNode(NULL);
  handle_connect_front_wheel_across->add_child(wheel_front);
  handle_connect_front_wheel_right = new HNode(NULL);
  handle_connect_front_wheel_left = new HNode(NULL);
  handle_connect_with_frame->add_child(handle_connect_front_wheel_across);
  handle_connect_front_wheel_across->add_child(handle_connect_front_wheel_left);
  handle_connect_front_wheel_across->add_child(handle_connect_front_wheel_right);

  handlebar_connector = new HNode(NULL);
  handle_connect_with_frame->add_child(handlebar_connector);
  handlebar_connector_across = new HNode(NULL);
  handlebar_connector->add_child(handlebar_connector_across);
  handlebar_left = new HNode(NULL);
  handlebar_right = new HNode(NULL);
  handlebar_connector_across->add_child(handlebar_left);
  handlebar_connector_across->add_child(handlebar_right);

  //front wheel...this is child of handle_with_wheel_across!
  wheel_front->obj_type = 2;
  wheel_front->inRadius=wheel_tyre_radius;
  wheel_front->outRadius=wheel_outer_radius;
  wheel_front->nsides=50;
  wheel_front->rings=50;
  wheel_front->change_parameters(0,-26.5, handle_connect_front_wheel_across_length/2, 0, 0, 0);

  //back wheel...this is child of nothing as of now
  wheel_back->obj_type = 2;
  wheel_back->inRadius=wheel_tyre_radius;
  wheel_back->outRadius=wheel_outer_radius;
  wheel_back->nsides=50;  
  wheel_back->rings=50;
  wheel_back->change_parameters(50, 0, 0, 0, 0, 0);

  //the spokes
  for(int i=0; i<9; i++){
    spoke_front[i]->obj_type = 0;
    spoke_front[i]->base=spoke_radius;
    spoke_front[i]->top=spoke_radius;
    spoke_front[i]->height=spoke_length;
    spoke_front[i]->slices=50;
    spoke_front[i]->stacks=10;
    spoke_front[i]->change_preparameters(2,0,0);
    spoke_front[i]->change_parameters(0,0,0,90,40*i,0);
    spoke_front[i]->set_color(0.6,0.6,0.6);             //silverish color

    spoke_front_extra[i]->obj_type = 0;
    spoke_front_extra[i]->base=extra_spoke_radius;
    spoke_front_extra[i]->top=extra_spoke_radius;
    spoke_front_extra[i]->height=extra_spoke_length;
    spoke_front_extra[i]->slices=50;
    spoke_front_extra[i]->stacks=10;
    //spoke_front_extra[i]->change_preparameters(2,0,0);
    spoke_front_extra[i]->change_parameters(0,0,21,0,0,0);
    spoke_front_extra[i]->set_color(0.855,0.647,0.125);       //goldenrod color

    spoke_back[i]->obj_type = 0;
    spoke_back[i]->base=spoke_radius;
    spoke_back[i]->top=spoke_radius;
    spoke_back[i]->height=spoke_length;
    spoke_back[i]->slices=50;
    spoke_back[i]->stacks=10;
    spoke_back[i]->change_preparameters(2,0,0);
    spoke_back[i]->change_parameters(0,0,0,90,40*i,0);
    spoke_back[i]->set_color(0.6,0.6,0.6);

    spoke_back_extra[i]->obj_type = 0;
    spoke_back_extra[i]->base=extra_spoke_radius;
    spoke_back_extra[i]->top=extra_spoke_radius;
    spoke_back_extra[i]->height=extra_spoke_length;
    spoke_back_extra[i]->slices=50;
    spoke_back_extra[i]->stacks=10;
    //spoke_back_extra[i]->change_preparameters(2,0,0);
    spoke_back_extra[i]->change_parameters(0,0,21,0,0,0);
    spoke_back_extra[i]->set_color(0.855,0.647,0.125);

    spoke_front2[i]->obj_type = 0;
    spoke_front2[i]->base=spoke_radius;
    spoke_front2[i]->top=spoke_radius;
    spoke_front2[i]->height=spoke_length;
    spoke_front2[i]->slices=50;
    spoke_front2[i]->stacks=10;
    spoke_front2[i]->change_preparameters(-2,0,0);
    spoke_front2[i]->change_parameters(0,0,0,90,40*i-10,0);
    spoke_front2[i]->set_color(0.6,0.6,0.6);

    spoke_front2_extra[i]->obj_type = 0;
    spoke_front2_extra[i]->base=extra_spoke_radius;
    spoke_front2_extra[i]->top=extra_spoke_radius;
    spoke_front2_extra[i]->height=extra_spoke_length;
    spoke_front2_extra[i]->slices=50;
    spoke_front2_extra[i]->stacks=10;
    //spoke_front2_extra[i]->change_preparameters(2,0,0);
    spoke_front2_extra[i]->change_parameters(0,0,21,0,0,0);
    spoke_front2_extra[i]->set_color(0.855,0.647,0.125);

    spoke_back2[i]->obj_type = 0;
    spoke_back2[i]->base=spoke_radius;
    spoke_back2[i]->top=spoke_radius;
    spoke_back2[i]->height=spoke_length;
    spoke_back2[i]->slices=50;
    spoke_back2[i]->stacks=10;
    spoke_back2[i]->change_preparameters(-2,0,0);
    spoke_back2[i]->change_parameters(0,0,0,90,40*i-10,0);
    spoke_back2[i]->set_color(0.6,0.6,0.6);

    spoke_back2_extra[i]->obj_type = 0;
    spoke_back2_extra[i]->base=extra_spoke_radius;
    spoke_back2_extra[i]->top=extra_spoke_radius;
    spoke_back2_extra[i]->height=extra_spoke_length;
    spoke_back2_extra[i]->slices=50;
    spoke_back2_extra[i]->stacks=10;
    //spoke_back2_extra[i]->change_preparameters(2,0,0);
    spoke_back2_extra[i]->change_parameters(0,0,21,0,0,0);
    spoke_back2_extra[i]->set_color(0.855,0.647,0.125);
  }

  //the wheel axes
  wheel_axis_f->obj_type=0;
  wheel_axis_f->base=bar_radius;
  wheel_axis_f->top=bar_radius;
  wheel_axis_f->height=wheel_axis_length;
  wheel_axis_f->slices=50;
  wheel_axis_f->stacks=10;
  wheel_axis_f->change_parameters(0,0,-wheel_axis_length/2,0,0,0);

  wheel_axis_b->obj_type=0;
  wheel_axis_b->base=bar_radius;
  wheel_axis_b->top=bar_radius;
  wheel_axis_b->height=wheel_axis_length;
  wheel_axis_b->slices=50;
  wheel_axis_b->stacks=10;
  wheel_axis_b->change_parameters(0,0,-wheel_axis_length/2,0,0,0);

  //handle of the cycle
  handle_connect_with_frame->obj_type=0;
  handle_connect_with_frame->base=bar_radius;
  handle_connect_with_frame->top=bar_radius;
  handle_connect_with_frame->height=handle_connect_with_frame_length;
  handle_connect_with_frame->slices=50;
  handle_connect_with_frame->stacks=10;
  handle_connect_with_frame->change_parameters(-30,26.5,0,-90,25,0);
  handle_connect_with_frame->set_color(1,0,0);    

  handlebar_connector->obj_type=0;
  handlebar_connector->base=bar_radius;
  handlebar_connector->top=bar_radius;
  handlebar_connector->height=handlebar_connector_length;
  handlebar_connector->slices=50;
  handlebar_connector->stacks=10;
  handlebar_connector->change_preparameters(0,0,0);
  handlebar_connector->change_parameters(0,0,handle_connect_with_frame->height,0,-90,0);
  handlebar_connector->set_color(0.7,0.7,0.7);  

  handlebar_connector_across->obj_type=0;
  handlebar_connector_across->base=bar_radius;
  handlebar_connector_across->top=bar_radius;
  handlebar_connector_across->height=handlebar_connector_across_length;
  handlebar_connector_across->slices=50;
  handlebar_connector_across->stacks=10;
  handlebar_connector_across->change_preparameters(0,0,-handlebar_connector_across->height/2);
  handlebar_connector_across->change_parameters(0,0,handlebar_connector->height,90,0,0);
  handlebar_connector_across->set_color(0.7,0.7,0.7);

  handlebar_left->obj_type=0;
  handlebar_left->base=bar_radius;
  handlebar_left->top=bar_radius;
  handlebar_left->height=handlebar_handle_length;
  handlebar_left->slices=50;
  handlebar_left->stacks=10;
  handlebar_left->change_parameters(0,0,handlebar_connector_across->height,0,0,0);
  handlebar_left->set_color(0,0,0);

  handlebar_right->obj_type=0;
  handlebar_right->base=bar_radius;
  handlebar_right->top=bar_radius;
  handlebar_right->height=handlebar_handle_length;
  handlebar_right->slices=50;
  handlebar_right->stacks=10;
  handlebar_right->change_parameters(0,0,-handlebar_right->height,0,0,0);
  handlebar_right->set_color(0,0,0);

  handle_connect_front_wheel_across->obj_type=0;
  handle_connect_front_wheel_across->base=bar_radius;
  handle_connect_front_wheel_across->top=bar_radius;
  handle_connect_front_wheel_across->height=handle_connect_front_wheel_across_length;
  handle_connect_front_wheel_across->slices=50;
  handle_connect_front_wheel_across->stacks=10;
  handle_connect_front_wheel_across->change_preparameters(0,0,-handle_connect_front_wheel_across->height/2);
  handle_connect_front_wheel_across->change_parameters(0,0,0,90,0,0);
  handle_connect_front_wheel_across->set_color(0,0,0);  

  handle_connect_front_wheel_left->obj_type=0;
  handle_connect_front_wheel_left->base=bar_radius;
  handle_connect_front_wheel_left->top=bar_radius;
  handle_connect_front_wheel_left->height=handle_connect_front_wheel_length;
  handle_connect_front_wheel_left->slices=50;
  handle_connect_front_wheel_left->stacks=10;
  handle_connect_front_wheel_left->change_parameters(0,0,handle_connect_front_wheel_across->height,90,0,0);
  handle_connect_front_wheel_left->set_color(0.5,0.5,0.5); 

  handle_connect_front_wheel_right->obj_type=0;
  handle_connect_front_wheel_right->base=bar_radius;
  handle_connect_front_wheel_right->top=bar_radius;
  handle_connect_front_wheel_right->height=25.5;
  handle_connect_front_wheel_right->slices=50;
  handle_connect_front_wheel_right->stacks=10;
  handle_connect_front_wheel_right->change_parameters(0,0,0,90,0,0);
  handle_connect_front_wheel_right->set_color(0.5,0.5,0.5);


  /********the main frame****************/

  //frame[0] = frame_upper_horizontal
  frame[0]-> obj_type=0;
  frame[0]->base=bar_radius;
  frame[0]->top=bar_radius;
  frame[0]->height=frame_upper_horizontal_len;
  frame[0]->slices=50;
  frame[0]->stacks=10;
  frame[0]->change_parameters(-25,40,0,-90,105,0);
  frame[0]->set_color(1,0,0);
  node[0]->add_child(frame[0]);

  //frame[1] = frame_lower_horizontal
  frame[1] = new HNode(NULL);
  frame[1]-> obj_type=0;
  frame[1]->base=bar_radius;
  frame[1]->top=bar_radius;
  frame[1]->height=frame_lower_horizontal_len;
  frame[1]->slices=50;
  frame[1]->stacks=10;
  frame[1]->change_parameters(-26,35,0,-90,130,0);
  frame[1]->set_color(1,0,0);
  // node[0]->add_child(frame[1]);

  //frame[2] = frame_right_vertical
  frame[2] = new HNode(NULL);
  frame[2]->obj_type=0;
  frame[2]->base=bar_radius;
  frame[2]->top=bar_radius;
  frame[2]->height=frame_right_vertical_len;
  frame[2]->slices=50;
  frame[2]->stacks=10;
  frame[2]->change_parameters(17,-1,0,-90,12,0);
  frame[2]->set_color(1,0,0);
  //node[0]->add_child(frame[2]);

  //frame upper right horizontal
  frame[3] = new HNode(NULL);
  frame[3]->obj_type=0;
  frame[3]->base=bar_radius;
  frame[3]->top=bar_radius;
  frame[3]->height=frame_upper_right_horizontal_len*3/8;
  frame[3]->slices=50;
  frame[3]->stacks=10;
  frame[3]->change_parameters(22,28,0,-90,135,0);
  frame[3]->set_color(1,0,0);
  node[0]->add_child(frame[3]);

  //axle
  axle = new HNode(NULL);
  axle->obj_type=0;
  axle->base=bar_radius;
  axle->top=bar_radius;
  axle->height=axle_length;
  axle->change_preparameters(0,14,-axle_length/2);
  axle->change_parameters(0,0,0,90,0,0);
  axle->set_color(0,0,0);
  frame[3]->add_child(axle);

  //rear wheel front upper
  frame[4] = new HNode(NULL);
  frame[4]->obj_type=0;
  frame[4]->base=bar_radius;
  frame[4]->top=bar_radius;
  frame[4]->height=(frame_upper_right_horizontal_len)*5/8;
  frame[4]->change_parameters(0,0,axle_length,-90,0,0);
  frame[4]->set_color(0.5,0.5,0.5);
  axle->add_child(frame[4]);

  //rear wheel back upper
  frame[5] = new HNode(NULL);
  frame[5]->obj_type=0;
  frame[5]->base=bar_radius;
  frame[5]->top=bar_radius;
  frame[5]->height=(frame_upper_right_horizontal_len)*5/8;
  frame[5]->change_parameters(0,0,0,-90,0,0);
  frame[5]->set_color(0.5,0.5,0.5);
  axle->add_child(frame[5]);

  //seat
  seat[0] = new HNode(NULL);
  seat[0]->obj_type=3;
  seat[0]->triangle_x1=30;
  seat[0]->triangle_y1=23;
  seat[0]->triangle_x2=30;
  seat[0]->triangle_y2=30;
  seat[0]->change_parameters(10,23,0,0,0,0);
  seat[0]->set_color(0,0,0);
  node[0]->add_child(seat[0]);

  seat[1] = new HNode(NULL);
  seat[1]->obj_type=3;
  seat[1]->triangle_x1=10;
  seat[1]->triangle_y1=26;
  seat[1]->triangle_x2=25;
  seat[1]->triangle_y2=26;
  seat[1]->change_parameters(10,23,0,0,0,0);
  seat[1]->set_color(0,0,0);
  node[0]->add_child(seat[1]);

  //gear
  gear[0] = new HNode(NULL);
  gear[0]->obj_type=2;
  gear[0]->change_parameters(15,0,2+2.5,0,0,0);
  gear[0]->inRadius=outer_gear_inRadius;
  gear[0]->outRadius=6.5;
  gear[0]->nsides=10;
  gear[0]->rings=50;
  gear[0]->set_color(0.6, 0.6, 0.6);
  node[0]->add_child(gear[0]);
  node[0]->add_child(frame[1]);
  node[0]->add_child(frame[2]);

  gear[1] = new HNode(NULL);
  gear[1]->obj_type=2;
  gear[1]->set_color(0.6, 0.6, 0.6);
  gear[1]->inRadius=inner_gear_radius;
  gear[1]->outRadius=inner_gear_radius;
  gear[1]->nsides=10;
  gear[1]->rings=50;
  gear[0]->add_child(gear[1]);

  // spokes in gear
  for(int i=0;i<5;i++){
    gear_spokes[i] = new HNode(NULL);
    gear_spokes[i]->obj_type=3;
    gear_spokes[i]->triangle_x1=(6.5 - outer_gear_inRadius)*(cos(0.31416 + (1.26*i)));
    gear_spokes[i]->triangle_y1=(6.5 - outer_gear_inRadius)*(sin(0.31416 + (1.26*i)));
    gear_spokes[i]->triangle_x2 = 1.5*(sin(1.26*(i+2)));
    gear_spokes[i]->triangle_y2 = -(1.5*(cos(1.26*(i+2))));
    gear_spokes[i]->change_parameters((1.5*(sin(1.26*(i+1)))),(-(1.5*(cos(1.26*(i+1))))),1,0,0,0);
    gear_spokes[i]->set_color(0.6, 0.6, 0.6);
    gear[0]->add_child(gear_spokes[i]);
  }

  //pedals
  //pedal rods
  pedal_rod_across = new HNode(NULL);
  pedal_rod_across->obj_type=0;
  pedal_rod_across->base=1;
  pedal_rod_across->top=1;
  pedal_rod_across->height=13;
  pedal_rod_across->slices=50;
  pedal_rod_across->stacks=10;
  pedal_rod_across->change_parameters(0, 0, -11, 0, 0, 0);
  pedal_rod_across->set_color(0.5,0.5,0.5);
  gear[0]->add_child(pedal_rod_across);

  pedal_rod[0] = new HNode(NULL);
  pedal_rod[0]->obj_type=0;
  pedal_rod[0]->base=1;
  pedal_rod[0]->top=1;
  pedal_rod[0]->height=15;
  pedal_rod[0]->slices=50;
  pedal_rod[0]->stacks=10;
  pedal_rod[0]->change_parameters(10, 10, 0, -90, -135, 0);
  pedal_rod[0]->set_color(0.5,0.5,0.5);
  pedal_rod_across->add_child(pedal_rod[0]);

  pedal_rod[1] = new HNode(NULL);
  pedal_rod[1]->obj_type=0;
  pedal_rod[1]->base=1;
  pedal_rod[1]->top=1;
  pedal_rod[1]->height=15;
  pedal_rod[1]->slices=50;
  pedal_rod[1]->stacks=10;
  pedal_rod[1]->change_parameters(-10, -10, 13, -90, 45, 0);
  pedal_rod[1]->set_color(0.5,0.5,0.5);
  pedal_rod_across->add_child(pedal_rod[1]);

  //pedal cuboids
  pedal_cuboid[0] = new HNode(NULL);
  pedal_cuboid[0]->obj_type=1;
  pedal_cuboid[0]->cuboid_breadth=7;
  pedal_cuboid[0]->cuboid_height=4;
  pedal_cuboid[0]->cuboid_length=3.5;
  pedal_cuboid[0]->set_color(0.3,0.3,0.3);
  pedal_cuboid[0]->change_preparameters(-pedal_cuboid[0]->cuboid_length/2,0,-pedal_cuboid[0]->cuboid_breadth/2);
  pedal_cuboid[0]->change_parameters(0,1,0,0,45-gear[0]->rz,0);  //1 is pedal_rod radius
  pedal_rod[0]->add_child(pedal_cuboid[0]);       //backside pedal

  pedal_cuboid[1] = new HNode(NULL);
  pedal_cuboid[1]->obj_type=1;
  pedal_cuboid[1]->cuboid_breadth=7;
  pedal_cuboid[1]->cuboid_height=4;
  pedal_cuboid[1]->cuboid_length=3.5;
  pedal_cuboid[1]->set_color(0.3,0.3,0.3);
  pedal_cuboid[1]->change_preparameters(-pedal_cuboid[1]->cuboid_length/2,0,-pedal_cuboid[1]->cuboid_breadth/2);
  pedal_cuboid[1]->change_parameters(0,-pedal_cuboid[1]->cuboid_height - 1,0,0,45-gear[0]->rz,0);
  pedal_rod[1]->add_child(pedal_cuboid[1]);       //frontside pedal

  // //rod across gear
  // across_gear = new HNode(NULL);
  // across_gear->obj_type=0;
  // across_gear->base=bar_radius;
  // across_gear->top=bar_radius;
  // across_gear->height=across_gear_length;
  // across_gear->change_parameters(0,0,-2,0,0,0);
  // across_gear->set_color(0.3,0.3,0.3);
  // gear[1]->add_child(across_gear);
  // wheel_axis_f->change_parameters(0,0,-wheel_axis_length/2,0,0,0);

  //frame lower right horizontal -- front
  frame[6] = new HNode(NULL);
  frame[6]->obj_type=0;
  frame[6]->base=bar_radius/2;
  frame[6]->top=bar_radius;
  frame[6]->height=frame_lower_right_horizontal_len;
  frame[6]->change_parameters(15,0,across_gear_length-bar_radius,0,90-4,0);
  frame[6]->set_color(1,0,0);
  node[0]->add_child(frame[6]);

  //frame lower right horizontal -- back
  frame[7] = new HNode(NULL);
  frame[7]->obj_type=0;
  frame[7]->base=bar_radius/2;
  frame[7]->top=bar_radius;
  frame[7]->height=frame_lower_right_horizontal_len;
  frame[7]->change_parameters(15,0,-across_gear_length+bar_radius,0,90+4,0);
  frame[7]->set_color(1,0,0);
  node[0]->add_child(frame[7]);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512,512);
  glutCreateWindow("Hierarchical Modeling");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  init();
  glutMainLoop();
  return 0;
}