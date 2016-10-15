#include "HNode.hpp"
using namespace std;

//GLuint textureId;  //will be generated - we dont have to create explicitly

void vertexcopy(float *src,float *dest){
  dest[0]=src[0];
  dest[1]=src[1];
  dest[2]=src[2];
  dest[3]=src[3];
}

//image type to load the texture
// struct Image {
//     unsigned long sizeX;
//     unsigned long sizeY;
//     char *data;
// };

// typedef struct Image Image;

//function to read the data from the image
// int ImageLoad(char *filename, Image *image) {
//     FILE *file;
//     unsigned long size; // size of the image in bytes.
//     unsigned long i; // standard counter.
//     unsigned short int planes; // number of planes in image (must be 1)
//     unsigned short int bpp; // number of bits per pixel (must be 24)
//     char temp; // temporary color storage for bgr-rgb conversion.
//     // make sure the file is there.
//     if ((file = fopen(filename, "rb"))==NULL){
//         printf("File Not Found : %s\n",filename);
//         return 0;
//     }

//     // seek through the bmp header, up to the width/height:
//     fseek(file, 18, SEEK_CUR);

//     // read the width
//     if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
//         printf("Error reading width from %s.\n", filename);
//         return 0;
//     }

//     //printf("Width of %s: %lu\n", filename, image->sizeX);

//     // read the height
//     if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
//         printf("Error reading height from %s.\n", filename);
//         return 0;
//     }

//     //printf("Height of %s: %lu\n", filename, image->sizeY);

//     // calculate the size (assuming 24 bits or 3 bytes per pixel).
//     size = image->sizeX * image->sizeY * 3;

//     // read the planes
//     if ((fread(&planes, 2, 1, file)) != 1) {
//         printf("Error reading planes from %s.\n", filename);
//         return 0;
//     }

//     if (planes != 1) {
//         printf("Planes from %s is not 1: %u\n", filename, planes);
//         return 0;
//     }

//     // read the bitsperpixel
//     if ((i = fread(&bpp, 2, 1, file)) != 1) {
//         printf("Error reading bpp from %s.\n", filename);
//         return 0;
//     }

//     if (bpp != 24) {
//         printf("Bpp from %s is not 24: %u\n", filename, bpp);
//         return 0;
//     }

//     // seek past the rest of the bitmap header.
//     fseek(file, 24, SEEK_CUR);

//     // read the data.
//     image->data = (char *) malloc(size);

//     if (image->data == NULL) {
//         printf("Error allocating memory for color-corrected image data");
//         return 0;
//     }

//     if ((i = fread(image->data, size, 1, file)) != 1) {
//         printf("Error reading image data from %s.\n", filename);
//         return 0;
//     }

//     for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
//         temp = image->data[i];
//         image->data[i] = image->data[i+2];
//         image->data[i+2] = temp;
//     }

//     //fclose(filename);

//     // we're done.
//     return 1;
// }

// //function to load the texture - return an image object
// Image * loadTexture(char* filename1){
//     Image *image1;

//     // allocate space for texture
//     image1 = (Image *) malloc(sizeof(Image));
//     std::cout<<"allocated mem"<<std::endl;

//     if (image1 == NULL) {
//         printf("Error allocating space for image");
//         exit(0);
//     }

//     //char filename1[] = {'f', 'l', 'o', 'o', 'r', '.', 'b', 'm', 'p'};
//     bool loaded = ImageLoad(filename1, image1);
//     std::cout<<"reached here - 1"<<std::endl;

//     //if (!ImageLoad(filename1, image1)) {
//     if (!loaded) {
//         std::cout<<"pain in image loading"<<std::endl;
//         exit(1);
//     }
//     else{
//         std::cout<<"image loaded"<<std::endl;
//     }

//     return image1;
// }

// void HNode::texMap_init(char* filename1){
//     //glClearColor (0, 0, 0, 1.0);
//     // glEnable(GL_DEPTH_TEST);
//     // glDepthFunc(GL_LESS);
//     std::cout<<"rendering floor 1"<<std::endl;
//     Image *image1 = loadTexture(filename1);
//     std::cout<<"rendering floor 2"<<std::endl;
//     if(image1 == NULL){
//         printf("Image was not returned from loadTexture\n");
//         exit(0);
//     }

//     // makeCheckImage();
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

//     // Create Texture
//     glGenTextures(1, &textureId);

//     ////bind the newly created texture; all future texture functions will modify this tecture
//     glBindTexture(GL_TEXTURE_2D, textureId);

//     //specify the texture image
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
   
//     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

//     // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
//     // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    
//     //specify texture environment parameters
//     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

//     //enable texturing
//     glEnable(GL_TEXTURE_2D);
//     //select flat or smooth shading
//     glShadeModel(GL_FLAT);
// }

/*dhruti*/
int HNode::loadBMP_custom(const char * imagepath){
    //data read from header of bmp file
    unsigned char header[54];       //each BMP file begins with by a 54 byte header
    unsigned int dataPos;       //position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;     //width*height*3
    //actual RGB data
    unsigned char * data1;
    //open the file
    FILE * file = fopen(imagepath, "rb");
    if(!file){
        cout<<"image could not be opened."<<endl;
        return 0;
    }
    if(fread(header, 1, 54, file) != 54){
        //if 54 bytes not read - problem
        cout<<"not a correct bmp file"<<endl;
        return 0;
    }
    if((header[0] != 'B') || header[1] != 'M'){
        cout<<"not a correct bmp file"<<endl;
        return 0;
    }

    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    //some BMP images are misformatted, guess missing info
    if(imageSize == 0){
        imageSize = width*height*3; //*3 =1 byte for each R,G,B
    }
    if(dataPos == 0){dataPos = 54;}

    //create a buffer
    data1 = new unsigned char [imageSize];

    //read the actual data from the file into the buffer
    fread(data1, 1, imageSize, file);

    //everything in memory now, can close file
    fclose(file);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // glGenTextures(2, textureId);
    glGenTextures(1, &textureId);
    //bind the newly created texture; all future texture functions will modify this tecture
    // glBindTexture(GL_TEXTURE_2D, textureId[0]);
    glBindTexture(GL_TEXTURE_2D, textureId);

    //give image to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    /*for 3D*/
    // glBindTexture(GL_TEXTURE_2D, textureId[1]);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data1);
}
/*dhruti*/

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

  texMapping = 0;
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

  // glEnable(GL_TEXTURE_2D);
  // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  // if(texMapping == 1){
    
  // }

  if(obj_type == 0){
    // glu
    if(texMapping == 1){
      loadBMP_custom(image_path);
      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

      //control the generation of texture coordinates
      // GLfloat param1[4] = {1.0, 0.0, 0.0, 0.0};
      // GLfloat param2[4] = {0.0, 0.0, 1.0, 0.0};

      /*
GLfloat param1[4] = {1.0, 0.0, 0.0, 0.0};
GLfloat param2[4] = {0.0, 0.0, 1.0, 0.0};
      */

      // glEnable(GL_TEXTURE_GEN_S);
      // glEnable(GL_TEXTURE_GEN_T);
      // glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
      // glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
      // glTexGenfv(GL_S, GL_OBJECT_PLANE, param1);
      // glTexGenfv(GL_T, GL_OBJECT_PLANE, param2);

      gluQuadricNormals(quad, GLU_SMOOTH);
      gluQuadricTexture(quad, GL_TRUE);
      glBindTexture(GL_TEXTURE_2D, textureId);

      gluCylinder(quad, base, top, height, slices, stacks);

      glDisable(GL_TEXTURE_2D);
    }
    else{
      gluQuadricNormals(quad, GLU_SMOOTH);
      gluCylinder(quad, base, top, height, slices, stacks);
    }
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
      glVertex3f(0.0f, 0.0f, cuboid_breadth);
      glVertex3f(cuboid_length, 0.0f, cuboid_breadth);
      glVertex3f(cuboid_length, cuboid_height, cuboid_breadth);
      glVertex3f(0.0f, cuboid_height, cuboid_breadth);
   
      //Right
      glNormal3f(1, 0, 0);
      glVertex3f(cuboid_length, 0.0f, cuboid_breadth);
      glVertex3f(cuboid_length, 0, 0);
      glVertex3f(cuboid_length, cuboid_height, 0);
      glVertex3f(cuboid_length, cuboid_height, cuboid_breadth);
   
      //Back
      glNormal3f(0.0f, 0.0f, -1.0f);
      glVertex3f(0, 0, 0);
      glVertex3f(0, cuboid_height, 0);
      glVertex3f(cuboid_length, cuboid_height, 0);
      glVertex3f(cuboid_length, 0, 0);
   
      //Left
      glNormal3f(-1.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0, 0.0f, cuboid_breadth);
      glVertex3f(0, cuboid_height, cuboid_breadth);
      glVertex3f(0, cuboid_height, 0);

      //top
      glNormal3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0, cuboid_height, 0);
      glVertex3f(0, cuboid_height, cuboid_breadth);
      glVertex3f(cuboid_length, cuboid_height, cuboid_breadth);
      glVertex3f(cuboid_length, cuboid_height, 0);
   
      //bottom
      glNormal3f(0.0f, -1.0f, 0.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(cuboid_length, 0.0f, 0.0f);
      glVertex3f(cuboid_length, 0.0f, cuboid_breadth);
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
  else if(obj_type == 4){
    if(texMapping == 1){
      //glBindTexture(GL_TEXTURE_2D, textureId); -- already did
      // texMap_init(file_name);
      loadBMP_custom(image_path);
      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
      glBindTexture(GL_TEXTURE_2D, textureId);


      glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(quad_vertices[0], quad_vertices[1], quad_vertices[2]);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(quad_vertices[3], quad_vertices[4], quad_vertices[5]);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(quad_vertices[6], quad_vertices[7], quad_vertices[8]);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(quad_vertices[9], quad_vertices[10], quad_vertices[11]);
      glEnd();
      glDisable(GL_TEXTURE_2D);
    }
    else{
      glBegin(GL_QUADS);
        glVertex3f(quad_vertices[0], quad_vertices[1], quad_vertices[2]);
        glVertex3f(quad_vertices[3], quad_vertices[4], quad_vertices[5]);
        glVertex3f(quad_vertices[6], quad_vertices[7], quad_vertices[8]);
        glVertex3f(quad_vertices[9], quad_vertices[10], quad_vertices[11]);
      glEnd();
    }
  }
  glutSwapBuffers();
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
  float surface_color[] = {R,G,B};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, surface_color); 
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