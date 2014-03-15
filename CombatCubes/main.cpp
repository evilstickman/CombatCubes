#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include "Infrastructure/GraphicsApplication.h"
#ifdef _WIN32
#include "Infrastructure/OpenGLWindowsApplication.h"
#endif


using namespace std;

// TODO for now, draw directly in here. This code will be abstracted away into 
// a renderer in the future.
#include <gl/gl.h>
#include <gl/glu.h>
#include "Infrastructure/Camera.h"
#include "Infrastructure/Grid.h"
#include "Infrastructure/KeyboardManager.h"
#include "Infrastructure/LevelMap.h"
#include "Geometry\Mesh.h"

// Set our default window to 640x480. This will eventually be set via 
// configuration
#define WIDTH (640)
#define HEIGHT (480)

// Function prototype for the windows message loop interface
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );

// TODO Function prototype for the draw call. This will eventually be 
// abstracted away into a renderer
void draw();

// TODO function prototype for input manager. Eventually to be refactored
void ProcessInput();

// Keyboard manager for preliminary input tracking. This is bad, but will be
// better later.
KeyboardManager kbm;

// Camera. Later, refactoring.
Camera c(Point(-20,10,-20.0), Point(0,0,0), Point(0.0,1.0,0.0));

Mesh testObject;
LevelMap * testMap = new LevelMap();

  Grid g;


// Windows uses WinMain for its entry point. So for windows, give it what it
// wants. The standard main should be just fine for other operating systems
// (at least for linux, that is).
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int iCmdShow)
{

  // TODO this will become a config later
  bool fullscreen = false;

  // Create our application. This does all the initialization and displays
  // the resulting window.
  GraphicsApplication *gApp = new OpenGLWindowsApplication(WIDTH, HEIGHT,
    fullscreen, hInstance,
    WndProc, iCmdShow, L"Combat Cubes");

  // TODO: load game resources here
  // - load geometry
  //testObject.LoadFromFile("C:\\Users\\Evil Stick Man\\Documents\\Visual Studio 2010\\Projects\\CombatCubes\\bin\\forest.txt");
  //testObject.LoadFromFile("forest.txt");
  //testObject.LoadFromFile("forest4.txt");
  testMap->LoadFromFile("level.txt");

  //   - create geometry object
  //   - load vertices from file
  //   - load faces from file
  //   - load alternate vertex info (normal map coords, tex coords, etc)
  //   - create mesh
  // - load sound
  // - initialize geometry, sound

  // Used for catching windows messages
  MSG msg;

  while( 1 )
  {
    // Watch for a quit message
    if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
    {
      // If we get a quit signal, break out of the loop
      if( msg.message == WM_QUIT )
      {
        break;
      }

      // We also may want to track input here. That is, if the api we end up 
      // using for input doesn't handle the message nastiness by itself (like 
      // DirectInput kind of does)

      // Send the message onward
      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }

    // Here is the core of any game loop. Three steps: Process Input, Run Logic,
    // then Draw. Ideally these will be abstracted away to a high degree - the 
    // functions themselves should be pretty thin interfaces. We'd also want to 
    // add in any frame-limiting stuff here as this is essentially how fast our 
    // engine runs. If we want to limit output to 60 FPS, we do that here.

    // Process the latest input
    ProcessInput();

    // Draw the scene to the backbuffer
    draw();

    // Swap buffers so that we can see the scene
    gApp->SwapAppBuffers();

  }
  // Clean up the application before we exit. The application class handles
  // all the fun stuff like releasing device context and rendering context
  gApp->DestroyWindow();
  delete gApp;
  gApp = NULL;
  return 0;
}
#else
int main(const int &argc, const char **argv)
{
  int c;
  cout<< "Hello  game \n";
  cin >>c ;
  return 0;
}
#endif

#ifdef _WIN32
/*****************************************************************************
*  Method name: WndProc
*  Parameters:
*    See the MSDN documentation for a description
*  Returns:
*    Returns the LRESULT of processing the message
*  Notes:
*    This is your basic windows message loop handler. It doesn't really do
*    much of anything as we'll be handling the majority of the functionality
*    ourselves
*****************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
  switch( message )
  {
    // Signal on creation
  case WM_CREATE:
    Beep( 50, 10 );
    return 0;
    break;

    // Redraw the window. Ignored because we do our own drawing
  case WM_PAINT:
    {
      HDC hdc;
      PAINTSTRUCT ps;
      hdc = BeginPaint( hwnd, &ps );
      // don't draw here.  would be waaay too slow.
      // draw in the draw() function instead.
      EndPaint( hwnd, &ps );
    }
    return 0;
    break;

  case WM_KEYUP:
    kbm.SetKeyReleased(wparam);
    return 0;
    break;

    // Exit on escape
  case WM_KEYDOWN:
    switch( wparam )
    {
    case VK_ESCAPE:
      PostQuitMessage( 0 );
      break;
    default:
      kbm.SetKeyPressed(wparam);
      break;
    }
    return 0;

    // Check for a window closure
  case WM_DESTROY:
    PostQuitMessage( 0 ) ;
    return 0;
    break;
  }

  return DefWindowProc( hwnd, message, wparam, lparam );
}

void ProcessInput()
{
  if(kbm.IsKeyPressed(VK_UP))
  {
    c.m_eye.m_vert[1] += 0.1;
    c.m_lookAt.m_vert[1] += 0.1;
  }
  if(kbm.IsKeyPressed(VK_DOWN))
  {
    c.m_eye.m_vert[1] -= 0.1;
    c.m_lookAt.m_vert[1] -= 0.1;
  }
  if(kbm.IsKeyPressed(VK_LEFT))
  {
    c.m_eye.m_vert[0] -= 0.1;
    c.m_lookAt.m_vert[0] -= 0.1;
  }
  if(kbm.IsKeyPressed(VK_RIGHT))
  {
    c.m_eye.m_vert[0] += 0.1;
    c.m_lookAt.m_vert[0] += 0.1;
  }
  if(kbm.IsKeyPressed(VK_INSERT))
  {
    c.m_eye.m_vert[2] += 0.1;
    c.m_lookAt.m_vert[2] += 0.1;
  }
  if(kbm.IsKeyPressed(VK_DELETE))
  {
    c.m_eye.m_vert[2] -= 0.1;
    c.m_lookAt.m_vert[2] -= 0.1;
  }
}


// TODO for now, draw directly in here. This code will be abstracted away into 
// a renderer in the future.
void draw()
{

  // Ok, so this is the meat of the game loop - the display. In here I basically 
  // need to do three things:
  // 
  // 1 - set up the projection
  // 2 - set up the camera space
  // 3 - render the geometry
  //
  // Obviously things will be a little more complex than that eventually. For 
  // instance, the above doesn't really incorporate any shader code. I'll cross
  // those bridges when I come to them, but for now we have the implied basic 
  // structure of our rendering engine: a viewport for the perspective 
  // transform, a camera for the world transform, and a geometry manager for the
  // display of objects. These classes will take a bit of careful design if I 
  // wish to do them properly - I need to beware of getting too generalized at 
  // the expense of obtuse code. I guess what I'm worried about is spending too 
  // much time architecting the ultimate solution, and too little time 
  // developing something that people want to play. Shit, I'd be happy with 
  // something I want to play.

  // For now, get the viewport set up and draw a triangle. A lot of this will
  // be abstracted into subclasses in the future (viewport will live in 
  // a renderer, projection and lookat matrices in a camera class, etc)
  Vertex light_position(10.0,1.0,20.0);
  glViewport(0, 0, WIDTH, HEIGHT); // set viewport

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-20, 20, -20, 20, 1, 1000);
  //gluPerspective(45.0,(float)WIDTH/(float)HEIGHT, 1, 1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_DEPTH_TEST);
  //glCullFace(GL_BACK);
  //glEnable(GL_CULL_FACE);


  // This... doesn't belong here. It would serve a better purpose sitting in a 
  // scenegraph, or some immaterial representation of "the world". I worry 
  // though that this is too much of an abstraction. For now, make it work. 
  // Then, make it pretty.
  c.SetCameraMatrix();

  glClearColor( 0.5, 0.5, 0.5, 0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // welcome to geometry land, where everything we choose to draw is displayed 
  // to the user with the utmost alacrity. For now I want to create a grid that
  // makes it easy to see one's location in the world. I'll move it into a 
  // controlling object later, enabled only for debug or something.

  g.Draw();
  
  glLightfv(GL_LIGHT0, GL_POSITION, c.m_eye.m_vert);
  
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_LIGHT0);

  //testObject.Draw();
  testMap->Draw();
}

#endif
