#include "shader_handler.h"

// for various OpenGL #defines and typedefs
#include <glew-1.10.0\include\GL\glew.h>

// for reading shader text from files
#include <fstream>
#include <sstream>

// for printing to the console
#include <iostream>
using std::cout;
using std::endl;


bool check_shader_program_status(
   GLuint object_ID,
   PFNGLGETSHADERIVPROC object_property_getter_func_ptr,
   GLenum object_status_type,
   PFNGLGETSHADERINFOLOGPROC info_log_getter_func_ptr
   )
{
   bool this_ret_val = false;

   GLint status;
   object_property_getter_func_ptr(object_ID, object_status_type, &status);
   if (GL_TRUE == status)
   {
      this_ret_val = true;
   }
   else
   {
      // not true, so must be false; get the status error and print it
      this_ret_val = false;

      GLint err_log_len;
      object_property_getter_func_ptr(object_ID, GL_INFO_LOG_LENGTH, &err_log_len);
      GLchar* err_log_buffer = new GLchar[err_log_len];

      // this variable is left over from when people would put a magic number into the error log memory 
      //   allocation, and then the next function would put the actual lenght into this variable instead
      //   of returning anything
      GLsizei actual_err_log_len;
      info_log_getter_func_ptr(object_ID, err_log_len, &actual_err_log_len, err_log_buffer);
      std::cout << err_log_buffer << std::endl;

      delete[] err_log_buffer;
   }

   return this_ret_val;
}


bool check_shader_status(GLuint shader_ID)
{
   bool this_ret_val = false;

   this_ret_val = check_shader_program_status(shader_ID, glGetShaderiv, GL_COMPILE_STATUS, glGetShaderInfoLog);
   if (this_ret_val)
   {
      cout << "shader ID '" << shader_ID << "' compiled ok" << endl;
   }

   return this_ret_val;
}

bool check_program_status(GLuint program_ID)
{
   bool this_ret_val = false;

   this_ret_val = check_shader_program_status(program_ID, glGetProgramiv, GL_LINK_STATUS, glGetProgramInfoLog);
   if (this_ret_val)
   {
      cout << "program ID '" << program_ID << "' linked ok" << endl;
   }

   return this_ret_val;
}

bool read_text_from_file(const char* file_path, std::string &put_text_here)
{
   bool this_ret_val = false;

   std::ifstream in_file_stream;
   in_file_stream.open(file_path, std::ifstream::in);
   if (in_file_stream.is_open())
   {
      this_ret_val = true;

      // credit for the following code goes to "method rdbuf" at 
      // http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
      std::ostringstream contents;
      contents << in_file_stream.rdbuf();
      in_file_stream.close();

      //cout << "shader code in file '" << file_path << "':" << endl;
      //cout << contents.str() << endl;;

      put_text_here = contents.str();
   }
   else
   {
      this_ret_val = false;
      std::cout << "could not open file '" << file_path << "'" << std::endl;
   }

   return this_ret_val;
}


namespace Rendering
{

   bool shader_handler::initialize(std::string vertex_shader_path, std::string fragment_shader_path)
   {
      // TODO: wrap glCheckError() calls in #ifdef(DEBUG) statements

      const char* old_GL_double_pointer_adapter[1];

      bool success = false;

      // create shader objects
      m_vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
      m_fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

      // start with the vertex shader and give it the source material, then compile it into an object
      std::string shader_code_text;
      if (!read_text_from_file(vertex_shader_path.c_str(), shader_code_text)) return false;
      old_GL_double_pointer_adapter[0] = shader_code_text.c_str();
      glShaderSource(m_vertex_shader_ID, 1, old_GL_double_pointer_adapter, 0);
      glCompileShader(m_vertex_shader_ID);
      if (!check_shader_status(m_vertex_shader_ID)) return false;

      // repeat for the fragment shader
      if (!read_text_from_file(fragment_shader_path.c_str(), shader_code_text)) return false;
      old_GL_double_pointer_adapter[0] = shader_code_text.c_str();
      glShaderSource(m_fragment_shader_ID, 1, old_GL_double_pointer_adapter, 0);
      glCompileShader(m_fragment_shader_ID);
      if (!check_shader_status(m_fragment_shader_ID)) return false;

      // create a shader executable for the GPU and link the shader objects that have been compiled so far
      m_shader_program_ID = glCreateProgram();
      glAttachShader(m_shader_program_ID, m_vertex_shader_ID);
      glAttachShader(m_shader_program_ID, m_fragment_shader_ID);
      glLinkProgram(m_shader_program_ID);
      if (!check_program_status(m_shader_program_ID)) return false;

      // set the context to use the shader program that we just made
      glUseProgram(m_shader_program_ID);

      // don't need the shaders anymore, so clean them up 
      // Note: The program is still required.  Clean up that when this class disappears at program end.
      glDeleteShader(m_vertex_shader_ID);
      glDeleteShader(m_fragment_shader_ID);

      return true;
   }



   GLint shader_handler::get_shader_program_ID()
   {
      return m_shader_program_ID;
   }

   bool shader_handler::shutdown()
   {
      // tell the GL context to stop using its current program so that we can delete it
      // Note: Nothing will happen if we tell GL to delete a program that is bound to the context.
      glUseProgram(0);
      glDeleteProgram(m_shader_program_ID);

      // TODO: wrap glCheckError() calls in #ifdef(DEBUG) statements
      return true;
   }
}
