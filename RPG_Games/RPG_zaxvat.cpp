#pragma once
#include <iostream>
#include <string>
#include <conio.h> //для _getch();
#include <Windows.h> //для цвета
#include <sstream> //строковые потоки
#include <iomanip> //Выравнивание вывод setw(оступ)
using namespace std;


/*Данный класс, будит родительским для всех остальных классов, он будит захватывать действия*/
class zaxvat {
protected:
	bool send_enter = 0;
	bool send_inventar = 0;
	bool send_esc = 0;
	bool send_c = 0;
	int max_verx = 0; /*Максимальная верхняя строчка по умолчанию 0*/
	int max_niz = 0;/*Максимальная нижняя строчка (количество предмеото или меню)*/
	int cur_element = 0; /*Текущий эл-т*/
	int var_cur_element =0; /*Выбераемый эл-т*/
	int str_begin = 0; /*Начало страници*/
	int str_end = 10; /*Конец страници*/
	bool page_next = 0;
	bool page_prei = 0;
	void move_contol() {/*Проверка на выход за раници*/
		/*Особая провека для главного меню*/	
		if (menu_if && (!acsess_main_menu[var_cur_element])) {
			if (var_cur_element < cur_element) {
				var_cur_element--;
			}		
			else { var_cur_element++; } 
			move_contol(); /*Проверка следубщего итема до первого выхода*/
		}


		if (var_cur_element < max_verx || var_cur_element > max_niz) {
			/*откат действия*/
			var_cur_element = cur_element;			
		}
		else {
			cur_element = var_cur_element;
			/*Проверка на переход страници (вправо в лево)*/
			if (page_next) {str_begin += 10; str_end += 10; page_next = 0;}
			if (page_prei) {str_begin -= 10; str_end -= 10; page_prei = 0;}

			/*Выбор области просмотра инвентаря (вниз вверх)*/
			if (cur_element < 10) { str_begin = 0; str_end = 10; }
			else if (cur_element % 10 == 0) { str_begin = cur_element; str_end = cur_element + 10; }
		}
	}
	bool menu_if = 0;
	bool acsess_main_menu[6] = { 0,1,1,0,1,1 };
public:
void control_zero() {
		/*все настройки по нулям!*/
		cur_element = 0; send_enter = 0; send_esc = 0; send_inventar = 0; send_c = 0;
		str_begin = 0; str_end = 10; 
	}
protected: 
	void menu_move_cord() {
		send_enter = 0;
		
		int val = key_enter();		
		switch (val) {
		case 72: case -106: case -26: case 119: case 87:
			var_cur_element--; send_enter = 0; break;
		case 80: case -101: case -21: case 115: case 83:
			var_cur_element++;  send_enter = 0; break;
		case 75: case -108: case -28: case 97: case 65:
			var_cur_element -= 10; page_prei = 1;  send_enter = 0; break;
		case 77: case -126: case -94: case 100: case 68:
			var_cur_element += 10; page_next = 1; send_enter = 0; break;
		case 13: case 69: case 101: case -45: case -13: //ентер или E
			cur_element = 0; send_enter = 1; break;
		case 9: case 105: case 73: case -40: case -8: //таб или I
			cur_element = 0; if (send_inventar != 0) send_inventar = 0; else send_inventar = 1; break;
		case 32: case 99: case 47: case -15: case -47:
			cur_element = 0; if (send_c)send_c = 0; else send_c = 1; break; //пробел С
		case 27: //ескейп
			cur_element = 0; send_esc = 1; send_inventar = 0; send_c = 0;
			break;
		}
		move_contol();
	}	

	
	int key_enter() {
		//функция для отлова нажатия клавиш
		char ch;
		int code;
		while (1)
		{
			ch = _getch();
			//cout << "COD  ch " << ch << endl;
			code = static_cast<int>(ch);
			//cout << "COD int " << code << endl;
			switch (code) {
			case 72: case (-106): case (-26): case 119: case 87:
				// 72 стрелка ввверх, и все вариатции WwЦц
				code = 72;  return code; break;
			case 80: case (-101): case (-21): case 115: case 83:
				//	80 Стрелка вниз S - 21
				code = 80;  return code; break;
			case 75: case (-108): case (-28): case 97: case 65:
				//	75 Стрелка влево A - 28
				code = 75;  return code; break;
			case 77: case (-126): case (-94): case 100: case 68:
				//	75 Стрелка влево D - 68		
				code = 77;  return code; break;
			case 13: case 69: case 101: case (-45): case (-13):
				//	ДЕЙСТВИЕ ENTER(13) или E
				code = 13;  return code; break;
			case 9: case 105: case 73: case (-40): case (-8): 
				//	i I (Ш ш) (9-Tab)
				code = 9;  return code; break;
			case 32: case 99: case 47: case (-15): case (-47):
				//	(32-Пробел) Клавиша C
				code = 32;  return code; break;
			case 27: //(esc - 27)
				return code; break;
			}
		}
		/*	0 - 48;	7 - 55;*/
		//	72 Стрелка вверх w - 26
		//	80 Стрелка вниз s - 21
		//	75 Стрелка влево a - 28
		//	75 Стрелка влево a - 28
		//  enter -13 e-69
		//  esc - 27
		//  i- 73
	}
protected:
	void videlenie_stroki(string stroka) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		//system("color F1");
		SetConsoleTextAttribute(hConsole, (WORD)((9 << 4) | 1));
		cout << stroka;
		//system("color F0");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		cout << "";
	}
	void videlenie_stroki_un(string stroka) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		//system("color F1");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 7));
		cout << stroka;
		//system("color F0");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		cout << "";
	}

	void videlenie_stroki_name(string stroka) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		//system("color F1");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 9));
		cout << setw(17) << stroka;
		//system("color F0");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		cout << "";
	}
	void videlenie_stroki_RED(string stroka, int calor = 12) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		//system("color F1");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | calor));
		cout << stroka;
		//system("color F0");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		cout << "";
	}
	void center(string stroka) {	
		//cout << "размер отступа " << 33 - (stroka.size() / 2) << " размер полуслова " << stroka.size() / 2 << endl;
		cout << setw(30 - (stroka.size() / 2));
		cout << "";
	}
};