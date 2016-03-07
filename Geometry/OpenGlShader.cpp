#include "OpenGlShader.h"



OpenGlShader::OpenGlShader(std::string vert_file, std::string frag_file) : Shader(vert_file, frag_file)
{
}


OpenGlShader::~OpenGlShader()
{
}


void OpenGlShader::load_and_compile_shaders()
{
  glewInit();
  m_vert_handle = glCreateShaderObjectARB(GL_VERTEX_SHADER);
  m_pixel_handle = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);

  GLchar *VertexShaderSource = 0;
  GLchar *PixelShaderSource = 0;
  unsigned long vlen = 0;
  unsigned long flen = 0;

  std::ifstream t(m_vertFileName);
  std::string vert_str((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());
  std::ifstream t2(m_fragFileName);
  std::string frag_str((std::istreambuf_iterator<char>(t2)),
                        std::istreambuf_iterator<char>());
  const char *vert_content = vert_str.c_str();
  const char *frag_content = frag_str.c_str();
  glShaderSourceARB(m_vert_handle, 1, &vert_content, 0);
  glShaderSourceARB(m_pixel_handle, 1, &frag_content,0);

  glCompileShader(m_vert_handle);
  glCompileShader(m_pixel_handle);


  GLint compiled;

  glGetObjectParameterivARB(m_vert_handle, GL_COMPILE_STATUS, &compiled);
  if (!compiled)
  {
    GLint blen = 0;
    GLsizei slen = 0;

    glGetShaderiv(m_vert_handle, GL_INFO_LOG_LENGTH, &blen);
    if (blen > 1)
    {
      GLchar* compiler_log = (GLchar*)malloc(blen);
      glGetInfoLogARB(m_vert_handle, blen, &slen, compiler_log);
      std::cout << "compiler_log:\n" << compiler_log;
      _asm int 3; // vert compile failed
      free(compiler_log);
    }
  }

  glGetObjectParameterivARB(m_pixel_handle, GL_COMPILE_STATUS, &compiled);
  if (!compiled)
  {
    GLint blen = 0;
    GLsizei slen = 0;

    glGetShaderiv(m_pixel_handle, GL_INFO_LOG_LENGTH, &blen);
    if (blen > 1)
    {
      GLchar* compiler_log = (GLchar*)malloc(blen);
      glGetInfoLogARB(m_pixel_handle, blen, &slen, compiler_log);
      std::cout << "compiler_log:\n" << compiler_log;
      _asm int 3; // frag compile failed
      free(compiler_log);
    }
  }


  m_program_object_handle = glCreateProgram();

  glAttachShader(m_program_object_handle, m_vert_handle);
  glAttachShader(m_program_object_handle, m_pixel_handle);

  glLinkProgram(m_program_object_handle);
  
  GLint linked;
  glGetProgramiv(m_program_object_handle, GL_LINK_STATUS, &linked);
  if (!linked)
  {
    GLint blen = 0;
    GLsizei slen = 0;
    char *mess = new char[GL_INFO_LOG_LENGTH];

    glGetProgramInfoLog(m_program_object_handle, GL_INFO_LOG_LENGTH, &slen, mess);
    if (blen > 1)
    {
      GLchar* compiler_log = (GLchar*)malloc(blen);
      glGetInfoLogARB(m_program_object_handle, blen, &slen, compiler_log);
      //cout << "compiler_log:\n", compiler_log);
      free(compiler_log);
    }
    _asm int 3; // link failed
  }
}

unsigned int OpenGlShader::get_vertex_shader_handle()
{
  return m_vert_handle;
}

unsigned int OpenGlShader::get_pixel_shader_handle()
{
  return m_pixel_handle;
}

unsigned int OpenGlShader::get_program_object_handle()
{
  return m_program_object_handle;
}
