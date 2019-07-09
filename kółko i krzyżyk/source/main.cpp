#include <Windows.h>
#include "../source/resource.h"
#pragma comment(lib, "winmm.lib")  // playsound

INT_PTR CALLBACK MainWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int board[3][3] = { 0 };
int field_size = 80;  // rozmiar pola
int board_padding = 30;  // odstêp planszy do gry od krawêdzi okna
int current_player = 1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, MainWinProc);
  MSG msg = {};
  ShowWindow(hwndMainWindow, iCmdShow);
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  /*KONIEC GRY*/

	return 0;
}

INT_PTR CALLBACK MainWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {
  case WM_CREATE:  // tworzenie okna
    break;

  case WM_PAINT:  // rysowanie okna
  {
    HDC hDC = GetDC(hwnd);
    for (auto i = 0; i < 4; i++)
    {
      MoveToEx(hDC, board_padding + i * field_size, board_padding, nullptr);  // pocz¹tek pionowej linii
      LineTo(hDC, board_padding + i * field_size, board_padding + 3 * field_size);  // pionowa linia
    }
    for (auto i = 0; i < 4; i++)
    {
      MoveToEx(hDC, board_padding, board_padding + i * field_size, nullptr);  // pocz¹tek poziomej linii
      LineTo(hDC, board_padding + 3 * field_size, board_padding + i * field_size);  // pozioma linia
    }
    // uzupe³nianie planszy
    for (auto i = 0; i < 3; i++)
    {
      for (auto j = 0; j < 3; j++)
      {
        if (board[i][j] == 1)
        {  // rysuj x
          MoveToEx(hDC, board_padding + i * field_size, board_padding + j * field_size, nullptr);
          LineTo(hDC, board_padding + (i + 1) * field_size, board_padding + (j+1) * field_size);
          MoveToEx(hDC, board_padding + i * field_size, board_padding + (j+1) * field_size, nullptr);
          LineTo(hDC, board_padding + (i+1) * field_size, board_padding + j * field_size);
        }
        else if (board[i][j] == 2)
        {  // rysuj o
          Ellipse(hDC,
            i*field_size + board_padding + 10,  // lewy górny róg prostok¹ta ograniczaj¹cego - x
            j * field_size + board_padding + 10,  // lewy górny róg prostok¹ta ograniczaj¹cego - y
            (i + 1) * field_size + board_padding - 10,  // prawy dolny róg prostok¹ta ograniczaj¹cego - x
            (j + 1) * field_size + board_padding - 10  // prawy dolny róg prostok¹ta ograniczaj¹cego - y
          );
        }
      }
    }
    ReleaseDC(hwnd, hDC);
    return TRUE;
  }
  case WM_LBUTTONDOWN:
  {
    const int click_y = HIWORD(lParam);  // wspó³rzêdna y miejsca klikniêcia
    const int click_x = LOWORD(lParam);  // wspó³rzêdna x miejsca klikniêcia
    const auto click_field_y = (click_y - board_padding) / field_size;
    const auto click_field_x = (click_x - board_padding) / field_size;

    //kontrola zmiennych odpowiadaj¹cych za wybrane pole
    if (click_field_x > 2 || click_field_y > 2) return TRUE;

    if(board[click_field_x][click_field_y] == 0)
    {
      board[click_field_x][click_field_y] = current_player;  // zapisanie wyboru gracza
      if (current_player == 2) current_player = 1;  // zmiana gracza
      else current_player = 2;  // zmiana gracza
    }
    break;
  }
  case WM_CLOSE:  // zamykanie okna
    DestroyWindow(hwnd);  // niszczenie okna
    PostQuitMessage(0);
    return TRUE;
  default:
    return FALSE;
  }

  return FALSE;
}