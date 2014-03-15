#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(void)
{
  for(int i = 0; i < KEYBOARD_SIZE; ++i)
  {
    m_bKeysPressed[i] = false;
  }
}

KeyboardManager::~KeyboardManager(void)
{

}

void KeyboardManager::SetKeyPressed(int index)
{
    m_bKeysPressed[index] = true;
}

void KeyboardManager::SetKeyReleased(int index)
{  
    m_bKeysPressed[index] = false;
}

bool KeyboardManager::IsKeyPressed(int index)
{
  
    return m_bKeysPressed[index];
}
