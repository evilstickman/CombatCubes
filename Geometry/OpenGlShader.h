#pragma once
#include "Shader.h"
#include <Windows.h>
#include "../external_libraries/glew-1.11.0/include/GL/glew.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <fstream>
using namespace std;
class OpenGlShader :
  public Shader
{
public:
  OpenGlShader(std::string vert_file, std::string frag_file);
  virtual ~OpenGlShader();

  virtual void load_and_compile_shaders();

  virtual unsigned int get_vertex_shader_handle();
  virtual unsigned int get_pixel_shader_handle();
  virtual unsigned int get_program_object_handle();
private:
  GLuint m_vert_handle;
  GLuint m_pixel_handle;
  GLuint m_program_object_handle;
};

