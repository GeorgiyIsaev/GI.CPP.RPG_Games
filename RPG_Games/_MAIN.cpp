#include <iostream>
#include <Windows.h> 
#include <string>
#include "RPG_plaer.cpp"
#include "RPG_inventar.cpp"

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
void nastoika_consoli() {
	srand(time(0));
	/*Расскладка*/
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*Граници консоли*/
	system("mode con cols=60 lines=24");
	/*Цвет консоли*/
	system("color F0"); //Белый фон
	/*РАЗМЕР ШРИФТ КОНСОЛИ*/
	/*#define _CRT_SECURE_NO_WARNINGS	
	#include <Windows.h>*/	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;

	// эта строка нужна
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	
	/*ВЫБОР Нужного шрифта*/
	// старый вариант
	//wcsncpy(L"Lucida Console", fontInfo.FaceName, LF_FACESIZE);
	// новый вариант
	//wcscpy(fontInfo.FaceName, L"Lucida Console"); //L"Lucida Console"
	/*ХЗ почему не работает. Тогда при запуске сделаю предприждение латинецей о необходимости выбора шрифта в ручную*/
	
	fontInfo.dwFontSize.Y = 24;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);	
}

//RPG_Menu.cpp
#include "RPG_Menu.cpp"
#include "RPG_Eqvip.cpp"
#include "RPG_Events.cpp"
#include "RPG_monstr.cpp"


int main()
{
	nastoika_consoli();
	RPG_menu menu;

	bool end = 0;	
	while (!end) {
		end = menu.print_menu();
	}
	system("cls");
}

