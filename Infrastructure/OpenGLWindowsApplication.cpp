#include "OpenGLWindowsApplication.h"
/*****************************************************************************
 *
 *  Class: OpenGLWindowsApplication
 *  Date Created: 6-29-2009
 *
 *  Notes:
 *    Implementation file for OpenGLWindowsApplication
 *
 *  Change Log
 *  ----------
 *  - Class Created
 *    MBillock 06-29-2009
 *  
 *****************************************************************************/

/*****************************************************************************
 *  Method name: OpenGLWIndowsApplication
 *  Parameters:
 *    width - stores the width of the window
 *    height - stores the height of the window
 *    fullscreen - true if the window should be fullscreen, false otherwise
 *    hInstance - the window instance of this application (passed in via main)
 *    wproc - a function pointer to the windows message handler
 *    iCmdShow - specifies how the window is to be shown for windows
 *  Default values:
 *    hInstance - NULL
 *    wproc - NULL
 *    iCmdSHow - 0
 *  Notes:
 *    Standard constructor for the OpenGL windows application class.
 *****************************************************************************/
OpenGLWindowsApplication::OpenGLWindowsApplication(const int width, 
                                                   const int height, 
                                                   const bool fullscreen, 
                                                   const HINSTANCE hInstance,
                                                   WNDPROC wproc,
                                                   int iCmdShow,
                                                   std::wstring title) :
                                                      GraphicsApplication(width, height, fullscreen, hInstance, wproc, iCmdShow, title),
                                                      m_hInstance(hInstance),
                                                      m_wproc(wproc),
                                                      m_iCmdShow(iCmdShow)
{

  Initialize();
}

/*****************************************************************************
 *  Method name: ~OpenGLWIndowsApplication
 *  Parameters:
 *    none
 *  Notes:
 *    Standard destructor for the OpenGLWindowsApplication class
 *****************************************************************************/
OpenGLWindowsApplication::~OpenGLWindowsApplication(void)
{
   

}

/*****************************************************************************
 *  Method name: DestroyWindow
 *  Parameters:
 *    none
 *  Notes:
 *    Cleans up the window for this application.
 *****************************************************************************/
void OpenGLWindowsApplication::DestroyWindow()
{
  // UNmake your rendering context (make it 'uncurrent')
  wglMakeCurrent( NULL, NULL );

  // Delete the rendering context, we no longer need it.
  wglDeleteContext( m_hglrc );

  // release your window's DC
  ReleaseDC( m_hwnd, m_hdc );
}

/*****************************************************************************
 *  Method name: Initialize
 *  Parameters:
 *    none
 *  Notes:
 *    Handles the setup for this window
 *****************************************************************************/
void OpenGLWindowsApplication::Initialize(void)
{
  // Create a WNDCLASS that describes the properties of our window
  WNDCLASS wc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
  wc.hCursor = LoadCursor( NULL, IDC_ARROW );
  wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
  wc.hInstance = m_hInstance;
  wc.lpfnWndProc = m_wproc;
  wc.lpszClassName = TEXT("ESMGames");
  wc.lpszMenuName = 0;
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

  // Register that class with the Windows O/S
    RegisterClass(&wc);

  // Create a RECT object that will define our window's position and size
  RECT rect;
  SetRect( &rect, 20,  // left
                  20,  // top
                  m_width, // right
                  m_height ); // bottom

  // Adjust the window to reflect our desired position and size
  AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );
  
  // Create our window
  m_hwnd = CreateWindow(TEXT("ESMGames"),
                         ((LPCWSTR)m_title.c_str()),
                         WS_OVERLAPPEDWINDOW,
                         rect.left, rect.top,  // adjusted x, y positions
                         rect.right - rect.left, rect.bottom - rect.top,  // adjusted width and height
                         NULL, NULL,
                         m_hInstance, NULL);

  // check to see that the window
  // was created successfully
  if( m_hwnd == NULL )
  {
      FatalAppExit( NULL, TEXT("CreateWindow() failed!") );
  }

  // Show our window
  ShowWindow( m_hwnd, m_iCmdShow );

  // Get the device context for our window
  m_hdc = GetDC( m_hwnd );

  // Create our pixel format descriptor (describes the format of our drawing
  // surface) and initialize it to all 0
  PIXELFORMATDESCRIPTOR pfd = { 0 };
  
  // A good description of the PIXELFORMATDESCRIPTOR
  // struct is under the documentation
  // for the ChoosePixelFormat() function:
  // http://msdn2.microsoft.com/en-us/library/ms537556(VS.85).aspx

  // Set only the fields of the pfd we care about:
  pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );    // just its size
  pfd.nVersion = 1;   // always 1

  pfd.dwFlags = PFD_SUPPORT_OPENGL |  // OpenGL support - not DirectDraw
                PFD_DOUBLEBUFFER   |  // double buffering support
                PFD_DRAW_TO_WINDOW;   // draw to the app window, not to a bitmap image

  pfd.iPixelType = PFD_TYPE_RGBA ;    // red, green, blue, alpha for each pixel
  pfd.cColorBits = 24;                // 24 bit == 8 bits for red, 8 for green, 8 for blue.
                                      // This count of color bits EXCLUDES alpha.

  pfd.cDepthBits = 32;                // 32 bits to measure pixel depth

  // Try and get a pixel format
  int chosenPixelFormat = ChoosePixelFormat( m_hdc, &pfd );

  // Check for errors. This usually means that there is no analogue to the
  // format we want that is available on this system
  if( chosenPixelFormat == 0 )
  {
      FatalAppExit( NULL, TEXT("ChoosePixelFormat() failed!") );
  }

  
  // Set the pixel format of the window
  int result = SetPixelFormat( m_hdc, chosenPixelFormat, &pfd );

  // Check for errors. Not sure what could come up here
  if (result == NULL)
  {
      FatalAppExit( NULL, TEXT("SetPixelFormat() failed!") );
  }
  // Now, create our rendering context. This is essentially the target of our
  // draw calls.
  m_hglrc = wglCreateContext( m_hdc );

  // Make the renduring context the current target
  wglMakeCurrent( m_hdc, m_hglrc );
}

/*****************************************************************************
 *  Method name: DisplayWindow
 *  Parameters:
 *    none
 *  Notes:
 *    Displays the window.
 *****************************************************************************/
void OpenGLWindowsApplication::DisplayWindow(void)
{
  
}

Shader *OpenGLWindowsApplication::GetShaderObject(std::string vert_file, std::string frag_file)
{
  return new OpenGlShader(vert_file, frag_file);
}