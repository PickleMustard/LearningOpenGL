#Learning OpenGL

The goal of this project is to get an understanding of the OpenGL API. The end product I'm aiming for is to be able to specify generic objects
and create them or to specify an object in a .obj file and be able to import and render it.

I am trying to minimize my use of existing libraries as I want to force myself to have a better grasp on the concepts and math behind graphics.
As such, I am avoiding using libraries that implement vectors, matrices, linear algebra, or anything else that hide away the math behind a blackbox.
In future, going back through and comparing what I build to the OpenGL GLM library might help to bridge gaps in understanding.

##1'st Attempt At Rendering
Following the transformation matrices in "Computer Graphics for Java Programmers," I've created a library called VectorMathAndObjects that is supposed to
create an object with a list of vertices and a list of faces comprised of vertex indices. From there, it should convert the faces into the best triangles
and transform the vertices 1st to viewing space than to clip-space. I've encountered issues transitioning from 2D to 3D in that I can get something to render
but I am unable to get a clear shape. It appears to render the shape but there is no perspective on it. It renders as a triangle (which makes sense as it's
viewpoint is at the corner) but is not entirely correct.

###Attempt at remedying:
Through research I found that OpenGL and its GLM library uses column-major matrices, not the row major that the textbook was using. Additionally,
all of the processing of the matrix math per vertex was passed to the GPU through the shader programme. So, what I plan to do is the following:
1. Create a library of structs for vectors and matrices to make the calculation of matrix math easier.
2. Reconfigure the eye-point transformation to be similar to the "LookAt"
3. Reconfigure the clip-space transformation to be column-major format.
4. Pass the transformation matrix for eye-point and clip-space into the vertex shader to allow delegating of the heavy matrix math to the more
optimal GPU.

###For Future Reference:
The library VectorMathAndObjects will be deprecated but still kept in the repository. It serves as a good reference point for what not to do.
