# FunctionPloter
A simple application to plot functions (wrapper for ExprTkr)

## Instructions:
The functions expressions (strings) must be provided in an external file (preferably name 'setup.txt') along with any defined constat, plot limits and 
number of points to plot.

## Example
`f = sin(a * pi * x)`

 `var = x`
 
 `cte = pi = 3.14159265359`
 
 `cte = a = 2.0`
 
 `x_min = -6.0`
 
 `x_max =  6.0`
 
 `y_min = -0.01`
 
 `y_max = 1.05`
 
 `nPts = 1200`

!NOTE! The setup flags names (f, cte, var...) CANNOT be altered, otherwise requiring changes in the code, only the right side of it, i.e. the function 
expressions, constant names and its values, limits value and number of points.

In case more than function is desired, or more constants are required, it just required to add a new line with the new expression (constant name) with 
the same flag name.

The function expressions must be given by a string (following C/C++ syntax)

In case any change to main.cpp code is made, the flag [compile] must be selected as true, otherwise it can be setted to false in order to save compilation
time.

# Credits:
This code heavily relies on the remarkable string parser code Exprtk made by Arash Partow. The original code, manual and files can be found at:
http://www.partow.net/programming/exprtk/

Implemented by: M. Lazarotto (28/12/2020)
