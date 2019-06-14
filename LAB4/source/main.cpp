#include <Windows.h>
#include <atlstr.h>
#include "res.h"
#include <stdlib.h>
#include <ctime>
int LosowaLiczba,licznik;
HINSTANCE hInst;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  switch (uMsg)
  {

  case WM_CREATE: //tworzenie okna
    break;
  case WM_PAINT:  //rysowanie okna
    HDC hDC;    // uchwyt do kontekstu urz�dzenia
    hDC = GetDC(hwndDlg);  //pobranie uchwytu do kontekstu okna

   // BitBlt(hDC, 0, 00, 800, 600, GetDC(0), 50, 60, SRCCOPY); //GetDC(0) pobranie kontekstu ekranu (screen)
    HBITMAP hBitmap;
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    HDC hDCBitmap;
    hDCBitmap = CreateCompatibleDC(hDC);  //utworzenie kompatybilnego kontekstu
    SelectObject(hDCBitmap, hBitmap); // wybranie bitmapy w kontek�cie
    LPRECT lpRect;
    GetWindowRect(hwndDlg, lpRect);
    BitBlt(hDC, 0, 0, 900, 400, hDCBitmap, 0,0, SRCCOPY); // skopiowanie obj
    DeleteDC(hDCBitmap); //Usuni�cie kontekstu
    DeleteObject(hBitmap);

    SelectObject(hDC, GetStockObject(ANSI_VAR_FONT));    //Pobranie i aktywacja czcionki
    SetTextColor(hDC, RGB(255, 0, 0));
    TextOut(hDC, 0, 0, TEXT("Text output to client area."), 27);    //ost arg - ilo�� znak�w do wy�wietlenia
    ReleaseDC(hwndDlg, hDC);   // zwolnienie kontekstu urz�dzenia
    break;

  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    
    case BN_CLICKED://zdarzenie klikniecia na UI
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1: // klikniecie na przycisk
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);// poranie uchwytu kontrolki IDC_EDIT1

        int iTextLength = GetWindowTextLength(hwndEditBox);//pobranie dl tekstu
        CHAR szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1);//pobranie tekstu
        SetWindowText((HWND)IParam, szText);
        int WpisanaLiczba = atoi(szText); // przypisanie liczby z CHAR szText
        if (WpisanaLiczba >= 0 && WpisanaLiczba <= 100) {
          if (WpisanaLiczba == LosowaLiczba)
          {
            CString sMessage = TEXT("");
            sMessage.Format(TEXT("Uda�o Ci si� trafi� po %d pr�bach"), licznik);
            int iRetKey = MessageBox(0, sMessage, "BRAWO!!!", MB_OK);
          }
          else if (WpisanaLiczba > LosowaLiczba)
          {
            SetWindowText((HWND)IParam, "wpisana liczba jest za du�a");
            licznik++;
          }
          else if (WpisanaLiczba < LosowaLiczba) {
            SetWindowText((HWND)IParam, "wpisana liczba jest za ma�a");
            licznik++;
          }
        }
        else int iRetKey = MessageBox(0, "Co� posz�o nie tak...", "...........", MB_OK);
       

        return TRUE;
      }
    }
    return FALSE;
   case WM_CLOSE:
      DestroyWindow(hwndDlg);//zniszczenie okna
      PostQuitMessage(0);//Umieszczenie w petli komunikatow polecenia zakonczenia aplikacji
      return TRUE;
   
  }
return FALSE;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  hInst = hInstance;
  int iRetKey = MessageBox(0, "zagrajmy w gr�! wylosuje dla Ciebie liczbe z przedzia�u od 1-100 a ty zgadnij co to za liczba!", "GRA", MB_OK);
    srand((time(NULL)));
    LosowaLiczba = rand() % 100 + 1;

    HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
    ShowWindow(hwndMainWindow, iCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    

  return 0;
  

  /**
  Zrobi� funkcjonalno�� lupy
  
  
  */
}
