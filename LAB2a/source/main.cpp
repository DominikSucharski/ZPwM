#include <Windows.h>;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
  //MessageBox(0, "Test", "Aplikacja_tytu�", MB_OK);
  int iRetKey = MessageBox(0, "Test", "Aplikacja1", MB_YESNO);
  if (iRetKey == IDYES) {
    MessageBox(0, "Jeszcze jak", "Aplikacja1", MB_OK);
  }
  else {
    MessageBox(0, "wybrano nie", "Aplikacja1", MB_OK | MB_ICONQUESTION);
  }

  /**
  Na poniedzia�ek: przygotowa� gr� w kt�rej komputer zgaduje liczb� (u�ytkownik odpowiada tak lub nie)
  najpierw komunikat wybierz liczb�
  przygotowa� obrazek w bmp i ikonk� .ico
  */

  return 0;
}