#include <cmath>
#include "tgaimage.h"

#define LINESTEP    0.02         //Step size of bresenham's line algo


constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};



void line_method1(int ax, int bx, int ay, int by, TGAImage &framebuffer, TGAColor color);
void line_method2(int ax, int bx, int ay, int by, TGAImage &framebuffer, TGAColor color);

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);

    //draw lines

    line_method2(ax, bx, ay, by, framebuffer, green);
    line_method2(bx, cx, by, cy, framebuffer, red);   
    line_method2(cx, ax, cy, ay, framebuffer, blue);       



    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}



void line_method1(int ax, int bx, int ay, int by, TGAImage &framebuffer, TGAColor color){
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

void line_method2(int ax, int bx, int ay, int by, TGAImage &framebuffer, TGAColor color){

    float t;
    int cx;
    int cy;
    

    if((abs(bx - ax) > abs(by - bx))){  //We want to choose



        for(int x = ax; x <= bx; x++){
            t = (x - ax) / static_cast<float>(bx - ax);
            cy = std::round (ay + t * (by - ay));

            cx = x;

            framebuffer.set(cx, cy, color);
        }

    }else{

        for(int y = ay; y <= by; y++){
            t = (y - ay) / static_cast<float>(by - ay);
            cx = std::round (ax + t * (bx - ax));

            cy = y;

            framebuffer.set(cx, cy, color);
        }

    }

}