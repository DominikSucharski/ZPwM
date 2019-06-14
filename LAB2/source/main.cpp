/** Podstawowa aplikacja Win32 */
#include <Windows.h>;
#include "res.h"

//Nazwa funkcji jest nieostotnia, liczy si� typ parametr�w i zwracanej warto�ci
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_CREATE:         //Tworzenie okna
      CreateWindow(
        TEXT("FirstAppClass"),        //Nazwa zarejestrowanej klasy okna
        TEXT("okno2"),                //Nazwa okna
        WS_OVERLAPPEDWINDOW,          //Styl okna
        20, 20,                         //Po�o�enie okna
        50, 50,                     //Rozmiar okna
        hwnd,                         //Brak okna nadrz�dnego
        NULL,                         //Brak menu
        NULL,                    //Uchwyt realizacji
        NULL);
     break;
    case WM_PAINT:          //Rysowanie okna
      break;
    case WM_DESTROY:        //Niszczenie okna
      PostQuitMessage(0);   //Przes�anie informacji o zako�czeniu dzia�ania programu
      break;
  }
  return DefWindowProc(hwnd, message, wParam, lParam); //wywo�anie procedury okna
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, NULL);
  ShowWindow(hwndMainWindow, iCmdShow);
  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW;             //Styl rejestrowanej klasy (o�wie�anie w��czone)
  wc.lpfnWndProc = (WNDPROC) WndProc;             //Wska�nik na funkcj� obs�uguj�c� komunikaty
  wc.cbClsExtra = 0;                              //Liczba dodatkowych bajt�w dodanych do klasy
  wc.cbWndExtra = 0;                              //Liczba dodatkowych bajt�w dodanych do okna
  wc.hInstance = hInstance;                       //Uchwyt na aplikacj�
  wc.hIcon = 0;                                   //Uchwyt na ikon� okna
  wc.hCursor = 0;                                 //Uchwyt na kursor u�yty w oknie
  wc.hbrBackground = 0;                           //Uchwyt na p�dzel t�a
  wc.lpszMenuName = TEXT("Pierwsza klasa");       //Nazwa menu okna
  wc.lpszClassName = TEXT("FirstAppClass");       //Nazwa klasy okna
  
  //rejestracja klasy okna
  if (!RegisterClass( &wc )) return (FALSE);
  HWND hWnd = CreateWindow(
    TEXT("FirstAppClass"),        //Nazwa zarejestrowanej klasy okna
    TEXT("okno1"),                //Nazwa okna
    WS_OVERLAPPEDWINDOW,          //Styl okna
    0, 0,                         //Po�o�enie okna
    200, 200,                     //Rozmiar okna
    NULL,                         //Brak okna nadrz�dnego
    NULL,                         //Brak menu
    hInstance,                    //Uchwyt realizacji
    NULL);

  if (hWnd = NULL) return (FALSE);

  ShowWindow(hWnd, iCmdShow);

  MSG msg;
  while(GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  MessageBox(0, TEXT("nazwa1"), TEXT("info"), MB_OK);
  //while (1) {}
  //do zrobienia:
  /*
  upi�kszy� aplikacj� (wstawi� przyciski, obrazek itp...)
  */
  return 0;
}