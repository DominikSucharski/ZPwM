#include <Windows.h>
#include "../source/resource.h"
#pragma comment(lib, "winmm.lib")  // playsound

INT_PTR CALLBACK MainWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int board[3][3] = { 0 };
int field_size = 80;  // rozmiar pola
int board_padding = 30;  // odstêp planszy do gry od krawêdzi okna
int current_player = 1;
int winner = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, MainWinProc);
  MSG msg = {};
  ShowWindow(hwndMainWindow, iCmdShow);
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  /*KONIEC GRY*/
  PlaySound((LPCSTR)"../source/win.wav", nullptr, SND_ASYNC);
  if (winner == 1) MessageBox(nullptr, TEXT("Wygra³ gracz 1"), TEXT("Koniec gry"), MB_OK);
  else if (winner == 2) MessageBox(nullptr, TEXT("Wygra³ gracz 2"), TEXT("Koniec gry"), MB_OK);
  else MessageBox(nullptr, TEXT("Remis"), TEXT("Koniec gry"), MB_OK);
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
    // rysowanie planszy
    for (auto i = 1; i < 3; i++)
    {
      MoveToEx(hDC, board_padding + i * field_size, board_padding, nullptr);  // pocz¹tek pionowej linii
      LineTo(hDC, board_padding + i * field_size, board_padding + 3 * field_size);  // pionowa linia
    }
    for (auto i = 1; i < 3; i++)
    {
      MoveToEx(hDC, board_padding, board_padding + i * field_size, nullptr);  // pocz¹tek poziomej linii
      LineTo(hDC, board_padding + 3 * field_size, board_padding + i * field_size);  // pozioma linia
    }
    auto free_fields = 0;
    // uzupe³nianie planszy
    for (auto i = 0; i < 3; i++)
    {
      for (auto j = 0; j < 3; j++)
      {
        if (board[i][j] == 1)
        {  // rysuj x
          MoveToEx(hDC, board_padding + i * field_size + 10, board_padding + j * field_size + 10, nullptr);
          LineTo(hDC, board_padding + (i + 1) * field_size - 10, board_padding + (j + 1) * field_size - 10);
          MoveToEx(hDC, board_padding + i * field_size + 10, board_padding + (j + 1) * field_size - 10, nullptr);
          LineTo(hDC, board_padding + (i + 1) * field_size - 10, board_padding + j * field_size + 10);
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
        else free_fields++;
      }
    }
    ReleaseDC(hwnd, hDC);
    // sprawdzanie poziome
    if ((board[0][0] == board[0][1]) && (board[0][1] == board[0][2])) winner = board[0][0];
    else if ((board[1][0] == board[1][1]) && (board[1][1] == board[1][2])) winner = board[1][0];
    else if ((board[2][0] == board[2][1]) && (board[2][1] == board[2][2])) winner = board[2][0];
    // sprawdzanie pionowe
    else if ((board[0][0] == board[1][0]) && (board[1][0] == board[2][0])) winner = board[0][0];
    else if ((board[0][1] == board[1][1]) && (board[1][1] == board[2][1])) winner = board[0][1];
    else if ((board[0][2] == board[1][2]) && (board[1][2] == board[2][2])) winner = board[0][2];
    // sprawdzanie skoœne
    else if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) winner = board[1][1];
    else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0])) winner = board[1][1];

    if (winner)
    {
      Sleep(200);
      DestroyWindow(hwnd);
      PostQuitMessage(0);
    }
    return TRUE;
  }
  case WM_LBUTTONDOWN:
  {
    const int click_y = HIWORD(lParam);  // wspó³rzêdna y miejsca klikniêcia
    const int click_x = LOWORD(lParam);  // wspó³rzêdna x miejsca klikniêcia
    const auto click_field_y = (click_y - board_padding) / field_size;
    const auto click_field_x = (click_x - board_padding) / field_size;

    //kontrola zmiennych odpowiadaj¹cych za wybrane pole
    if (click_field_x > 2 || click_field_y > 2) {
      PlaySound((LPCSTR)"../source/error.wav", nullptr, SND_ASYNC);
      return TRUE;
    }
    PlaySound((LPCSTR)"../source/smashing.wav", nullptr, SND_ASYNC);
    if (board[click_field_x][click_field_y] == 0)
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