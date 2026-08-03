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
void triangle2D(vec2 vecA, vec2 vecB, vec2 vecC, TGAImage &framebuffer, TGAColor color);
vec2 project2D(vec3 vec, int width, int height);

int main(int argc, char** argv) {
    constexpr int width  = 128;
    constexpr int height = 128;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    Model myModel("./obj/diablo3_pose/diablo3_pose.obj");



    for(int i = 0; i < myModel.nfaces(); i ++){
        vec3 vecA = myModel.vert(i, 0);
        vec3 vecB = myModel.vert(i, 1);
        vec3 vecC = myModel.vert(i, 2);

        triangle2D(project2D(vecA, width, height), project2D(vecB, width, height), project2D(vecC, width, height), framebuffer, red);

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


void triangle2D(vec2 vecA, vec2 vecB, vec2 vecC, TGAImage &framebuffer, TGAColor color){
    
    line(vecA.x, vecB.x, vecA.y, vecB.y, framebuffer, color);
    line(vecB.x, vecC.x, vecB.y, vecC.y, framebuffer, color);   
    line(vecC.x, vecA.x, vecC.y, vecA.y, framebuffer, color);    

}

vec2 project2D(vec3 vec, int width, int height){
    //Scales a vec3, and overwrites the original vec 
    //This will need to change when camera angle is not fixed

    return vec2 (((vec.x + 1.)  * width/2), ((vec.y + 1.)  * height/2));

}