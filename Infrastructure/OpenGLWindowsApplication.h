
#ifndef __OPENGLWINDOWSAPPLICATION_H
#define __OPENGLWINDOWSAPPLICATION_H
/*****************************************************************************
 *
 *  Class: OpenGLWindowsApplication
 *  Date Created: 6-25-2009
 *
 *  Notes:
 *    This class implements the basic tasks of setting up and managing an
 *    OpenGL windows application. Proper usage is as follows:
 *  
 *      GraphicsApplication *gApp = new OpenGLWindowsApplication(w, h,...);
 *      while(1)
 *      {
 *        // draw that thang
 *        
 *        // swap me some buffers
 *        gApp->SwapAppBuffers();
 *      }
 *      // be a good little app and clean up after ourselves
 *      gApp->DestroyWindow();
 *      delete gApp;
 *      gApp = NULL;
 *
 *  A lot of the setup code is taken from 
 *  http://bobobobo.wordpress.com/2008/02/11/opengl-in-a-proper-windows-app-no-glut/
 *  This shouldn't be a big deal, as I just used it as a refresher (this is the
 *  kind of crap you do once and then forget completely about).
 *
 *  Change Log
 *  ----------
 *  - Class Created
 *    MBillock 06-29-2009
 *  
 *****************************************************************************/
#include "graphicsapplication.h"
#include "Geometry\OpenGlShader.h"
#include <windows.h>
#include "external_libraries\glew-1.11.0\include\GL\glew.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <string>

class OpenGLWindowsApplication :
  public GraphicsApplication
{
public:
  OpenGLWindowsApplication(const int width, const int height, 
                           const bool fullscreen, const HINSTANCE hInstance,
                           WNDPROC wproc, int iCmdShow, std::wstring title);
  virtual ~OpenGLWindowsApplication(void);

  virtual void DisplayWindow();
  virtual void DestroyWindow();

  // Defined inline because this is pretty much a basic mask
  virtual inline void SwapAppBuffers() { SwapBuffers(m_hdc);}


  virtual Shader *GetShaderObject(std::string vert_file, std::string frag_file);

protected:
  virtual void Initialize();
  
  HINSTANCE m_hInstance;    // window app instance
  HWND m_hwnd;      // handle for the window
  HDC   m_hdc;      // handle to device context
  HGLRC m_hglrc;    // handle to OpenGL rendering context
  WNDPROC m_wproc;    // main windows message loop interface
  int m_iCmdShow;   //windows show command

};

#endif //__OPENGLWINDOWSAPPLICATION_H