#include <Windows.h>;
#include "string";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
  /**
  Na poniedzia�ek: przygotowa� gr� w kt�rej komputer zgaduje liczb� (u�ytkownik odpowiada tak lub nie)
  najpierw komunikat wybierz liczb�
  przygotowa� obrazek w bmp i ikonk� .ico
  */
  int minUserNumber = 0;
  int maxUserNumber = 40;
  int diff, guessing_number;
  char buffer[60];

while(minUserNumber != (maxUserNumber-1)) {
    diff = maxUserNumber - minUserNumber;
    guessing_number = minUserNumber + (ceil(diff / 2));
    sprintf_s(buffer, "Czy Twoja liczba jest < %d \nzakres %d : %d", guessing_number, minUserNumber, maxUserNumber);
    int iRetKey = MessageBox(0, buffer, "Zgadywanie liczby", MB_YESNO);
    if (iRetKey == IDYES) {
      //mniejsza
      maxUserNumber -= diff / 2;
    }
    else {
      //wieksza lub r�wna
      minUserNumber += ceil(diff / 2);
      if (ceil(diff / 2) == 0) break;
    }
  }
  sprintf_s(buffer, "Twoja liczba to %d", minUserNumber);
  int iRetKey = MessageBox(0, buffer, "Zgadywanie liczby", MB_OK);
  return 0;
}