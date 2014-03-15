#pragma once

class Grid
{
public:
  Grid(float xStart = -100.0, float xEnd = 100.0, int xLines = 20,
       float yStart = -100.0, float yEnd = 100.0, int yLines = 20,
       float zStart = -100.0, float zEnd = 100.0, int zLines = 20);
  ~Grid(void);
  
  void Draw();

protected:
    float m_xStart;
    float m_xEnd;
    int m_xLines;
    float m_yStart;
    float m_yEnd;
    int m_yLines;
    float m_zStart;
    float m_zEnd;
    int m_zLines;
};
