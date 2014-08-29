#ifndef ENGINE_SHADER_HANDLER_H
#define ENGINE_SHADER_HANDLER_H

// these inclusions are for parameter typing
//#include <glew-1.10.0\include\GL\glew.h>
#include <Misc\Typedefs.h>
#include <string>

namespace Rendering
{
   class shader_handler
   {
   public:
      bool initialize(std::string vertex_shader_path, std::string fragment_shader_path);
      bool shutdown();
      //GLint get_shader_program_ID();
      int get_shader_program_ID();

   private:

      //bool check_shader_program_status(
      //   GLuint object_ID,
      //   PFNGLGETSHADERIVPROC object_property_getter_func_ptr,
      //   GLenum object_status_type,
      //   PFNGLGETSHADERINFOLOGPROC info_log_getter_func_ptr
      //   );
      //bool check_shader_status(GLuint shader_ID);
      //bool check_program_status(GLuint program_ID);
      //bool read_text_from_file(const char* file_path, std::string &put_text_here);

      //GLuint m_vertex_shader_ID;
      //GLuint m_fragment_shader_ID;
      //GLuint m_shader_program_ID;
      uint m_vertex_shader_ID;
      uint m_fragment_shader_ID;
      uint m_shader_program_ID;

   };

}

#endif
