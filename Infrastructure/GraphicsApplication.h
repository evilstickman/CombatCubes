#ifndef __GRAPHICSAPPLICATION_H
#define __GRAPHICSAPPLICATION_H
/*****************************************************************************
 *
 *  Class: GraphicsApplication
 *  Date Created: 6-25-2009
 *
 *  Notes:
 *    This class is intended to serve as the basis for any graphical 
 *    application. The intent is that we interface with this class in order to
 *    create our window, and subclass out the platform-specific stuff. So, for
 *    example, if we were trying to create a Windows OpenGL app, we'd do 
 *    something like this:
 *
 *    int main(const int& argc, const char **argv)
 *    {
 *      #ifdef __WIN32
 *        #ifdef OPENGL
 *          GraphicsApplication *app = new OpenGLWinApp(width, height, full);
 *        #end
 *      #end
 *      while(!done)
 *      {
 *        app->DisplayWindow();
 *      }
 *      return 0;
 *    }
 *
 *    If done properly, we should be able to encapsulate away all the platform
 *    specific BS. It is created as an abstract class in order to enforce this
 *    pattern
 *
 *  Change Log
 *  ----------
 *  - Class Created
 *    MBillock 06-25-2009
 *  - Modified constructor to include defaulted parameters necessary for
 *    creating a window. Unfortunately I had to do it this way to avoid having
 *    way too much window-specific code in the main function (there's too much
 *    there already)
 *    MBillock  06-29-2009
 *  
 *****************************************************************************/
#ifdef _WIN32
#include <windows.h>
#else
#define HINSTANCE int
#define WNDPROC int
#endif

#include "Geometry/Shader.h"
#include <String>

class GraphicsApplication
{
public:
    GraphicsApplication(const int width, const int height, 
                      const bool fullscreen, const HINSTANCE hInstance = NULL,
                      WNDPROC wproc = NULL, int iCmdShow = 0,
                      std::wstring title = L"");
    virtual ~GraphicsApplication(void) = 0;

  virtual void DisplayWindow() = 0;

  virtual void DestroyWindow() = 0;

  // Defined inline because this is pretty much a basic mask
  virtual inline void SwapAppBuffers() = 0;

  virtual Shader *GetShaderObject(std::string vert_file, std::string frag_file) = 0;

protected:
  virtual void Initialize() = 0;
  int m_width;
  int m_height;
  bool m_fullscreen;

  std::wstring m_title;


};

#endif __GRAPHICSAPPLICATION_H