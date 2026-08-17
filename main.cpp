#include <cmath>
#include <cstdlib>
#include <ctime>
#include "tgaimage.h"
#include "model.h"
#include <utility> 

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
void scanline_fill(vec2 vecA, vec2 vecB, vec2 vecC, TGAImage &framebuffer, TGAColor red, TGAColor green);

int main(int argc, char** argv) {
    constexpr int width  = 128;
    constexpr int height = 128;
    TGAImage framebuffer(width, height, TGAImage::RGB);


    scanline_fill(vec2(7, 45), vec2(35, 100), vec2(45, 60), framebuffer, red, green);
    scanline_fill(vec2(120, 35), vec2(90, 5), vec2(45, 110), framebuffer, red, green);
    scanline_fill(vec2(115, 83), vec2(80, 90), vec2(85, 120), framebuffer, red, green);

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


void scanline_fill(vec2 vecA, vec2 vecB, vec2 vecC, TGAImage &framebuffer, TGAColor red, TGAColor green){
    /*
    *   We sort the y cords, and then draw a line left to right
    *   Since we know y cords are sequential we can use radix sort? This would ensure Theta(d * (n + b))
    */

   //Sort based on y value using bubble sort (ascending order):
    if (vecA.y > vecB.y) {std::swap(vecA, vecB);}
    if (vecA.y > vecC.y) {std::swap(vecA, vecC);}
    if (vecB.y > vecC.y) {std::swap(vecB, vecC);}

    //This splits each triangle into two sub triangles

    int height = vecC.y - vecA.y;
    if(vecA.y != vecB.y){
        int segment_height = vecB.y - vecA.y;
        //Sweeps from bottom up
        for (int y = vecA.y; y <= vecB.y; y++) {
            //basically at position y we want to calculate x1, x2, for the two lines coming from that point
            int x1 = vecA.x + ((y-vecA.y)*(vecC.x-vecA.x)) /height;
            int x2 = vecA.x + ((y-vecA.y)*(vecB.x-vecA.x)) / segment_height;

            framebuffer.set(x1, y, red);
            framebuffer.set(x2, y, green);            

        }

    }
}