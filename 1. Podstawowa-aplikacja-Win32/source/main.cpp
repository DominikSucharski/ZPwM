#include <Windows.h>;
#include "../make.visual/resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/* Punkt startowy programu */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
  // Ustawienie w³aœciwoœci okna
  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW;  // Styl rejestrowanej klasy (oœwie¿anie w³¹czone)
  wc.lpfnWndProc = (WNDPROC)WndProc;  // WskaŸnik na funkcjê obs³uguj¹c¹ komunikaty
  wc.cbClsExtra = 0;  // Liczba dodatkowych bajtów dodanych do klasy
  wc.cbWndExtra = 0;  // Liczba dodatkowych bajtów dodanych do okna
  wc.hInstance = hInstance;  // Uchwyt na aplikacjê
  wc.hIcon = 0;  // Uchwyt na ikonê okna
  wc.hCursor = 0;  // Uchwyt na kursor u¿yty w oknie
  wc.hbrBackground = 0;  // Uchwyt na pêdzel t³a
  wc.lpszMenuName = TEXT("Pierwsza klasa");  // Nazwa menu okna
  wc.lpszClassName = TEXT("FirstAppClass");  // Nazwa klasy okna

  // rejestracja klasy okna
  if (!RegisterClass(&wc)) {
    MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return (FALSE);
  }
  /*
  // Tworzenie okna
  HWND hWnd = CreateWindow(
    TEXT("FirstAppClass"),  // Nazwa zarejestrowanej klasy okna
    TEXT("okno1"),  // Nazwa okna
    WS_OVERLAPPEDWINDOW,  // Styl okna
    0, 0,  // Po³o¿enie okna
    200, 200,  // Rozmiar okna
    NULL,  // Brak okna nadrzêdnego
    NULL,  // Brak menu
    hInstance,  // Uchwyt realizacji
    NULL);

  if (hWnd = NULL) return (FALSE);  // sprawdzenie czy okno zosta³o utworzone
  */
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, WndProc);
  ShowWindow(hwndMainWindow, iCmdShow);  // wyœwietlenie okna
  //UpdateWindow(hWnd);

  /* Pêtla komunikatów */
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  MessageBox(0, TEXT("text w oknie"), TEXT("nag³ówek"), MB_OK);  // funkcja wyœwietlaj¹ca komunikat dla u¿ytkownika
  return 0;
}


/* Procedura okna */
INT_PTR CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_CREATE:  // tworzenie okna
    /*
    CreateWindow(
      TEXT("FirstAppClass"),        //Nazwa zarejestrowanej klasy okna
      TEXT("okno2"),                //Nazwa okna
      WS_OVERLAPPEDWINDOW,          //Styl okna
      20, 20,                         //Po³o¿enie okna
      50, 50,                     //Rozmiar okna
      hwnd,                         //Brak okna nadrzêdnego
      NULL,                         //Brak menu
      NULL,                    //Uchwyt realizacji
      NULL);
      */
    break;
  case WM_PAINT:  // rysowanie okna
    HDC hDC;  // uchwyt do kontekstu urz¹dzenia
    hDC = GetDC(hwnd);  // pobranie uchwytu do kontekstu okna
    SelectObject(hDC, GetStockObject(ANSI_VAR_FONT));  // pobranie i aktywacja czcionki
    SetTextColor(hDC, RGB(255, 0, 0));  // ustawienie koloru
    TextOut(hDC, 20, 20, TEXT("Text output to client area."), 27);  // c - liczba znaków
    ReleaseDC(hwnd, hDC); // zwolnienie kontekstu urz¹dzenia
    break;
  case WM_DESTROY:  // niszczenie okna
    PostQuitMessage(0);  // przes³anie informacji o zakoñczeniu dzia³ania programu
    break;
  }
  return DefWindowProc(hwnd, message, wParam, lParam); //Wywo³anie domyœlnej procedury okna
}