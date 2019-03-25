#include <Windows.h>;
#include "res.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  return DefWindowProc(hwnd, message, wParam, lParam); //wywo³¹nie procedury okna
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, NULL);
  ShowWindow(hwndMainWindow, iCmdShow);
  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = (WNDPROC) WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = 0;
  wc.hCursor = 0;
  wc.hbrBackground = 0;
  wc.lpszMenuName = TEXT("Pierwsza klasa");
  //rejestracja klasy okna
  if (!RegisterClass( &wc )) return (FALSE);
  HWND hWnd = CreateWindow(TEXT("First Class"), TEXT("okno1"), WS_OVERLAPPEDWINDOW
    , 0, 0, 200, 200, NULL, NULL, hInstance, NULL);
  if (hWnd = NULL) return (FALSE);
  MessageBox(0, TEXT("nazwa1"), TEXT("info"), MB_OK);
  while (1) {

  }
  //do zrobienia:
  /*
  upiêkszyæ aplikacjê (wstawiæ przyciski, obrazek itp...)
  */
  return 0;
}