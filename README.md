# Key Framing
## Goal
The goal of this repo is to provide a simple framework for an animator to do key frame animation. This is done by
specifying orientation (both translation and orientation) of a rigid object.

## Things to Note
In `main.cpp`, the variable definition for `keyFrames` is commented out. If you would like to see an animation that
has been created by me, comment out the `input()` line. This will show a teapot moving and rotating around the screen.
In order to input your own values, you will have to enable the `input()` function. It is important to note that if 
you are inputing your own value, the number of frames you specify MUST be at least 4. The interpolation method uses
splines, and tangents need to be calculated at each of the interpolated points. If there are less than 4 key frame values,
these tangent calculations will not happen.
