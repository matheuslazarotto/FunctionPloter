#!/bin/bash

######################################
#       Function ploter script       #
###################################### 
# This code evaluates a given set of 
# real values functions and returns a 
# figure with the plot plot.
#
# Instructions:
# The functions expressions (strings) 
# must be provided in a external file
# (preferably name 'setup.txt') along 
# with any defined constat, plot limits 
# and number of points to plot.
#
# Example
# f = sin(a * pi * x)
# var = x
# cte = a = 2.0
# x_min = -6.0
# x_max =  6.0
# y_min = -0.01
# y_max = 1.05
# nPts = 1200
#
# !NOTE! The setup flags names (f, cte, var...)
# CANNOT be altered, only the right side of it  
# that is the function expression, constant name 
# and value, limits value and number of points.
#
# -> In case more than function is desired, or more 
# constants are required, it just required to add 
# a new line with the new expression (constant name)
# with the same flag name.
#
# -> The function expressions must be 
# given by a string (following C/C++ syntax)
# 
# -> In case any change to main.cpp code
# is made, the flag [compile] must be 
# selected as true, otherwise it can be 
# setted to false in order to save compilation
# time.
#
# Credits:
# This code heavily relies on the remarkable 
# string parser code Exprtk made by Arash
# Partow. The code, manual and files can be 
# found at:
# http://www.partow.net/programming/exprtk/
#
# Implemented by: M. Lazarotto (30/09/2020 -- 28/12/2020)

######################################
#              Settings              #
######################################
file="setup.txt"                     # File with function and data
compile=false                        # Select to compile
######################################
#                                    #
######################################

if [ "$compile" = true ] || [ ! -e "./func_ploter" ]
then
    if [ -e "./func_ploter" ]
    then
        make clean
    fi
    make
fi

if [ -e "./func_ploter" ]
then
    clear
    date
    
    rm output_**.dat
    ./func_ploter $file

    python3.6 python/plot.py -file $file

    date
fi