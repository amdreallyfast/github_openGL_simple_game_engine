// MUST include before Qt's GL libraries
#include "glew-1.10.0\include\GL\glew.h"

// could do assertion or exception (??change to exception??)
#include <cassert>

#include "my_GL_window.h"


void my_GL_window::initializeGL()
{
   GLenum err_code = glewInit();
   assert(err_code == 0);

}
