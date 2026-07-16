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
        
    <Method 2>
        Instead of having functions x and y of variable t, we can rearrange to have 

        X(t) = a_x + t * (b_x - a_x)
        becomes
        T(x) = (x - a_x) / (b_x - a_x)

        Using this we can iterate over X and compute for t, which we can plug into the Y(t) function to return the y value. 

        The issue with this method is the quality is dictates by the gradient of x(t). For example if y's distance is large, but x only steps 3 pixels to the right, only 3 points will be drawn. (Basically just transpose the image)


        I will stick with this method

    <Optimisation>

        Starting with the our equation for t(x) which then gets plugged into y(t), we can simplify this by doing:
            y(x(t)) = a_y + ((x - a_x)*(b_y - a_y)) / (b_x - a_x)

        A characteristic of this new equation is that the (x - a_x) part sweeps over 0, 1, 2, ..., (b_x - a_x) as the domain (dictated by our for loop for x) is x subset of (ax to bx).
        So lets write a proof.
        At loop Initialisation
        x = ax, meaning (x - a_x) = (a_x - a_x) = 0
        so:
            y_0 = a_y + 0 * (b_y - a_y) / (b_x - a_x)
                = a_y
        Next iteration x += 1
        This would give us the equation:
            y_1 = a_y + ( 1 *(b_y - a_y)) / (b_x - a_x)
            but remember we said y_0 = a_y, so the equation becomes:

            y_1 = y_0 + (b_y - a_y) / (b_x - a_x)

        Next iteration :
            (Im expanding the equation a bit e.g 2x = x + x)
            y_2 = y_0  + (b_y - a_y) / (b_x - a_x)  +  (b_y - a_y) / (b_x - a_x)
            We notice a pattern.
            This part of the equation: y_0  + (b_y - a_y) / (b_x - a_x) is equal to y_1
            So the equation becomes
            y_2 = y_1 + (b_y - a_y) / (b_x - a_x)
        
        The recurrence relation of our equations becomes:
            y_n = y_{n - 1} + (b_y - a_y) / (b_x - a_x)
