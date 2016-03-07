#pragma once
#include<string>
class Shader
{
public:
	Shader(std::string vert_file, std::string frag_file);
  virtual ~Shader();

	virtual void load_and_compile_shaders() = 0;

  virtual unsigned int get_vertex_shader_handle() = 0;
  virtual unsigned int get_pixel_shader_handle() = 0;
  virtual unsigned int get_program_object_handle() = 0;
protected:
  std::string m_vertFileName;
  std::string m_fragFileName;
};

