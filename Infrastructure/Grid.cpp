#include "Grid.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

Grid::Grid(float xStart, float xEnd, int xLines,
           float yStart, float yEnd, int yLines,
           float zStart, float zEnd, int zLines) : m_xStart(xStart), m_xEnd(xEnd), m_xLines(xLines),
                                                   m_yStart(yStart), m_yEnd(yEnd), m_yLines(yLines),
                                                   m_zStart(zStart), m_zEnd(zEnd), m_zLines(zLines)
{
    // Eventually, generate VBOs here and do everything in non-deprecated code. 
    // For now, though, it's just faster to draw lines using the old way.
}

Grid::~Grid(void)
{
}

  
void Grid::Draw()
{
    float xDist = (m_xEnd - m_xStart) / (float)m_xLines;
    float yDist = (m_yEnd - m_yStart) / (float)m_yLines;
    float zDist = (m_zEnd - m_zStart) / (float)m_zLines;
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 10);
  glBegin (GL_LINES);
    // xy plane lines
    for(int x = m_xStart; x <= m_xEnd; x+=xDist)
    {
      for(int y = m_yStart; y <= m_yEnd; y += yDist)
      {
        glColor3d(((x < 0) ? 0.0 : 1.0), ((y < 0) ? 0.0 : 1.0), 0.0);
        glVertex3d(x, y, m_zStart);
        glVertex3d(x, y, 0.0);
        glColor3d(((x < 0) ? 0.0 : 1.0), ((y < 0) ? 0.0 : 1.0), 1.0);
        glVertex3d(x, y, 0.0);
        glVertex3d(x, y, m_zEnd);
      }
    }
    
    // xz plane lines
    for(int x = m_xStart; x <= m_xEnd; x += xDist)
    {
        for(int z = m_zStart; z <= m_zEnd; z += zDist)
        {
          glColor3d(((x < 0) ? 0.0 : 1.0), 0.0, ((z < 0) ? 0.0 : 1.0));
          glVertex3d(x, m_yStart, z);
          glVertex3d(x, 0.0,z);
          glColor3d(((x < 0) ? 0.0 : 1.0), 1.0, ((z < 0) ? 0.0 : 1.0));
          glVertex3d(x, 0.0, z);
          glVertex3d(x, m_yEnd, z);
        }
    }

    // yz plane lines
    for(int y = m_yStart; y <= m_yEnd; y += yDist)
    {
        for(int z = m_zStart; z <= m_zEnd; z += zDist)
        {
          glColor3d(0.0, ((y < 0) ? 0.0 : 1.0), ((z < 0) ? 0.0 : 1.0));
          glVertex3d(m_xStart, y, z);
          glVertex3d(0.0, y, z);
          glColor3d(1.0, ((y < 0) ? 0.0 : 1.0), ((z < 0) ? 0.0 : 1.0));
          glVertex3d(0.0, y, z);
          glVertex3d(m_xEnd, y, z);
        }
    }
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}
