#include <Windows.h>;
#include "res.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, NULL);
  ShowWindow(hwndMainWindow, iCmdShow);
  while (1) {

  }
  //do zrobienia:
  /*
  upi�kszy� aplikacj� (wstawi� przyciski, obrazek itp...)
  */
  return 0;
}