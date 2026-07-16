# OpenGL-Rasterizer
Author: Elliott Varasdi

Creating a custom openGL rasterizer software



Reference Material: https://github.com/ssloy/tinyrenderer/tree/706b2dfecff65daeb93de568ee2c2bd87f277860 - Ssloy 




Documentation:

**Line Drawing**
    
    Objective:
        To draw a line between point a to point b
        Using a vector approach there are multiple methods.
        
    <Method 1>
        Using Barycentric coordinates we can create 2 functions for X and Y respectively, which exist with a variable t.
        This would look like:
            X(t) = a_x + t * (b_x - a_x)
            Y(t) = a_y + t * (b_y - a_y)
        
        As we iterate over t (t = 0->1) we these functions would return coordinates in the form (X(t), Y(t)) along the line we are trying to draw. 

        Issues with this method:
            The lines smoothness is determines by a step size of t. This can result in holes in the line, or even unnecessary computations as a step increase of t may be so small it cannot be rendered. 
        


 