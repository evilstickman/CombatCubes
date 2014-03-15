#pragma once

#define KEYBOARD_SIZE 256

class KeyboardManager
{
public:
  KeyboardManager(void);
  ~KeyboardManager(void);

  void SetKeyPressed(int index);
  void SetKeyReleased(int index);

  bool IsKeyPressed(int index);

private:
  bool m_bKeysPressed[KEYBOARD_SIZE];
};
