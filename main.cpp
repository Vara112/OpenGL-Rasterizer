#include <cmath>
#include <cstdlib>
#include <ctime>
#include "tgaimage.h"
#include "model.h"

#define LINESTEP    0.02         //Step size of bresenham's line algo


constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};



void basic_line(int ax, int bx, int ay, int by, TGAImage &framebuffer, TGAColor color);
void line(int ax, int bx, int ay, int by, TGAImage &framebuffer, TGAColor color);
void triangle(vec3 vecA, vec3 vecB, vec3 vecC, TGAImage &framebuffer, TGAColor color, int width, int height);

int main(int argc, char** argv) {
    constexpr int width  = 1024;
    constexpr int height = 1024;
    TGAImage framebuffer(width, height, TGAImage::RGB);

 /*  
    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);

    //draw lines

    line(ax, bx, ay, by, framebuffer, green);
    line(bx, cx, by, cy, framebuffer, red);   
    line(cx, ax, cy, ay, framebuffer, blue);       
    
*/

//model.cpp testing:

    Model myModel("./obj/diablo3_pose/diablo3_pose.obj");

    
/*
    std::srand(std::time({}));
    for (int i=0; i<(1<<24); i++) {
        int ax = rand()%width, ay = rand()%height;
        int bx = rand()%width, by = rand()%height;
        line(ax, ay, bx, by, framebuffer, { rand()%255, rand()%255, rand()%255, rand()%255 });
    }

*/


    for (int i = 0; i < myModel.nverts(); i++){
        vec3 vecA = myModel.vert(i); 
        int ax = std::round((vecA.x * width/2 ) + width/2);
        int ay = std::round((vecA.y * height/2 ) + height/2);

        framebuffer.set(ax, ay, white);
    }
    for(int i = 0; i < myModel.nfaces(); i ++){
        vec3 vecA = myModel.vert(i, 0);
        vec3 vecB = myModel.vert(i, 1);
        vec3 vecC = myModel.vert(i, 2);

        triangle(vecA, vecB, vecC, framebuffer, red, width, height);

    }
    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}



void basic_line(int ax, int bx, int ay, int by, TGAImage &framebuffer, TGAColor color){
    //Using Bresenham's line drawing algorithmn to draw lines between point A to point B

    //Storage variables
    int cx;   
    int cy;

    for(float t = 0 ; t < 1; t+= LINESTEP){
        
        cx = std::round (ax + t * (bx - ax));
        cy = std::round (ay + t * (by - ay));

        framebuffer.set(cx, cy, color);
    }

}

void line(int ax, int bx, int ay, int by, TGAImage &framebuffer, TGAColor color){

    //Version iterates over x or y (depending on which one is steeper) for a function of T.
    //Guarantees smooth lines as step size is the largest distance (either between x values or y values)


    int y;
    int iError = 0;


    bool transpose = abs(ax-bx) < abs(ay-by);

    //Check if we need to transpose (y is steeper then x) 
    if (transpose){

        std::swap(ax, ay);
        std::swap(bx, by);

    }

    //Ensure we are always drawing left to right
    if(ax>bx){

        std::swap(ax, bx);
        std::swap(ay, by);

    }
    
    y = ay;   
    
    //NOT USED ANYMORE DUE TO INT OPTIMISATION. 
    //float slope = static_cast<float>(by - ay)/static_cast<float>(bx - ax);  //Check line 46 in README.md (optimisation) for explanation

    for(int x = ax; x <= bx; x++){

        
        if(!transpose){
            framebuffer.set(x, y, color);
        }
        else{
            //de-transpose
            framebuffer.set(y, x, color);
        }

        iError += 2 * std::abs(by-ay);  // We are checking  ierror > 1/2, but since we are working with int's
        //                                  multiply by 2 e.g  2 * ierror > 1

        y += (by > ay ? 1 : -1) * (iError > bx - ax);
        iError -= 2 * (bx-ax) * (iError > bx - ax);

    }



    

}

void triangle(vec3 vecA, vec3 vecB, vec3 vecC, TGAImage &framebuffer, TGAColor color, int width, int height){
 
    int ax = std::round((vecA.x * width/2 ) + width/2);
    int ay = std::round((vecA.y * height/2 ) + height/2);

    int bx = std::round((vecB.x * width/2 ) + width/2);
    int by = std::round((vecB.y * height/2 ) + height/2);

    int cx = std::round((vecC.x * width/2 ) + width/2);
    int cy = std::round((vecC.y * height/2 ) + height/2);
    
    line(ax, bx, ay, by, framebuffer, color);
    line(bx, cx, by, cy, framebuffer, color);   
    line(cx, ax, cy, ay, framebuffer, color);    

}