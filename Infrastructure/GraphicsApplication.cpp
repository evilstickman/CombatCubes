#include "GraphicsApplication.h"
/*****************************************************************************
 *
 *  Class: GraphicsApplication
 *  Date Created: 6-25-2009
 *
 *  Notes:
 *    Implementation file for GraphicsApplication
 *
 *  Change Log
 *  ----------
 *  - Class Created
 *    MBillock 06-25-2009
 *  
 *****************************************************************************/



/*****************************************************************************
 *  Method name: GraphicsApplication
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
 *    Standard constructor for the graphics application class.
 *****************************************************************************/
GraphicsApplication::GraphicsApplication(const int width, const int height, 
                                         const bool fullscreen, 
                                         const HINSTANCE hInstance,
                                         WNDPROC wproc,
                                         int iCmdShow,
                                         std::wstring title)
                                         : m_width(width),
                                           m_height(height),
                                           m_fullscreen(fullscreen),
                                           m_title(title)
{
}

/*****************************************************************************
 *  Method name: ~GraphicsApplication
 *  Parameters:
 *    none
 *  Notes:
 *    Standard destructor for the graphics application class.
 *****************************************************************************/
GraphicsApplication::~GraphicsApplication(void)
{
}


/*****************************************************************************
 *  Method name: DestroyWindow
 *  Parameters:
 *    none
 *  Notes:
 *    Destroys/cleans up the application window
 *****************************************************************************/
void GraphicsApplication::DestroyWindow()
{
  
}

/*****************************************************************************
 *  Method name: DisplayWindow
 *  Parameters:
 *    none
 *  Notes:
 *    Displays the application window
 *****************************************************************************/
void GraphicsApplication::DisplayWindow()
{

}

/*****************************************************************************
 *  Method name: Initialize
 *  Parameters:
 *    none
 *  Notes:
 *    Typically called by the constructor. Initializes the window app.
 *****************************************************************************/
void GraphicsApplication::Initialize()
{

}