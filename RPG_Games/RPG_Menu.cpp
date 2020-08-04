#pragma once
#include <iostream>
#include <string>
#include "RPG_zaxvat.cpp"
#include "RPG_plaer.cpp"
//#include "RPG_inventar.cpp"
//RPG_Menu.cpp
#include <fstream> // файловые потоки
#include <sstream> //строковые потоки
#include "RPG_triggercpp.cpp"

class RPG_menu :protected zaxvat {
	string main_menu[6] = { "Продолжить-->","Новая  игра", "Загрузить", "Сохранить", "Управление!", "Выход" };
	string info_menu[6] = { "Вернутся в текущую игру",
		"Запустить игру с начала",
		"Загрузить доступное сохранение",
		"Сохранить текущую игру",
		"Информация об управлении в игре",
		"Выйти из игры без сохранения!" };
	plaer igrok;
	string info = "";
	bool game_new_start = 1;
	bool game_over = 0;
public:
	RPG_menu() {	
		/*Через конструктор задаем стартовые параметры*/
		menu_if = 1;
		/*Начнет с первого доступного меню*/
		for (int i = 0; i < 6; i++) {
			if (acsess_main_menu[i]) { max_verx = i; var_cur_element = cur_element = i; break; }
		}
		max_niz = 5;
	}
	bool print_menu() {
		system("cls");
		cout << "\n\n\n\n";
		send_esc = 0;
		for (int i = 0; i < 6; i++) {
			center(main_menu[i]);
			if (!acsess_main_menu[i]) { videlenie_stroki_un(main_menu[i]); /*continue;*/ }
			else {/*max_niz++;*/
				if (i == cur_element) videlenie_stroki(main_menu[i]);
				else cout << main_menu[i];
			}
			/*cout << " " << i << " " << var_cur_element << " " << cur_element <<" "<< max_niz;*/
			cout << endl;
		}

		cout << endl;
		center(info_menu[cur_element]);
		cout << info_menu[cur_element] << endl;
		center(info); 	cout << info << endl; info = "";
		menu_move_cord(); /*Передвижение по меню выделением*/
		if (send_enter) {
			if (cur_element == 5 && exit_game()) return 1;
			send_enter = 0; start_menu();
		}
		return 0;
	}
	void start_menu() {
		//control_zero();
		if (cur_element == 0) { send_esc = 0; games_continue(); }
		else if (cur_element == 1) { new_games(); }
		else if (cur_element == 2) { load_games();/*загр*/ }
		else if (cur_element == 3) { save_games();/*сохр*/ }
		else if (cur_element == 4) { print_info_control(); }
		//else if (cur_element == 5) {/*ВЫХОД*/ }
	}
	void print_info_control() {

		while (!send_esc) {
			system("cls");
			cout << "\n\nУправление: \n\n"
				"WASD и Стрелочки - для перемещения по меню и внутри игры.\n"
				"ESC – Возврат в меню, возврат в игры.\n"
				"Enter(E) – Запустить действие.\n"
				"Tab(I) – Инвентарь.\n"
				"Space(C) – Окно персонажа.\n"
				"\n\nНажмите ESC или Enter, что бы вернутся в меню.\n";
			menu_move_cord();
			if (send_enter) { send_enter = send_esc = 1; }
		}
		send_esc = 0;
	}
	void new_games() {
		if (acsess_main_menu[0]) new_games_danger();/*Если игра было запущена, защитить от повторного запуска*/
		//else game_new_start = 1;
		if (game_new_start) {
			igrok = plaer();
			game_over = 0;
			acsess_main_menu[0] = 1; acsess_main_menu[3] = 1; max_verx = var_cur_element = cur_element = 0; /*Включаем меню продолжить*/
			/*Страт игры*/
			games_continue();
		}
		send_esc = 0;
	}
	void new_games_danger() {
		send_esc = 0;
		while (!send_esc) {
			system("cls");
			cout << "\n\n\n\n"
				"                         ВНИМАНИЕ!\n\n\n"
				"   При запуске новой игры, текущий прогресс будит утерян!\n\n\n"

				"   ESC - Вернутся в меню!      Enter - Начать новую игру!\n";
			;
			menu_move_cord();
			if (send_esc) { game_new_start = 0; }
			if (send_enter) { send_esc = 1; game_new_start = 1; }
			//cout << "game_new_start" << game_new_start << endl; menu_move_cord();
		}
		control_zero();
	}
	bool exit_game() {
		send_esc = 0;
		while (!send_esc) {
			system("cls");
			cout << "\n\n\n\n"
				"                         ВНИМАНИЕ!\n\n\n"
				"  Если вы выйдите из игры, текущий прогресс будит утерян!\n\n\n"

				"  ESC - Вернутся в меню!       Enter - ВЫЙТИ ИЗ ИГРЫ!\n";
			;
			menu_move_cord();
			if (send_esc) { return 0; }
			if (send_enter) { send_esc = 1; return 1; }
			//cout << "game_new_start" << game_new_start << endl; menu_move_cord();
		}
		control_zero();
		return 0;
	}
	void games_continue() {
		while (!send_esc) {
			send_esc = igrok.print_games(game_over);
		}
		send_esc = 0; send_enter = 0;
		if (game_over) { acsess_main_menu[0] = 0; acsess_main_menu[3] = 0; max_verx = var_cur_element = cur_element = 1; game_over = 0; }
	}

	/*CОХРАНЕНИЕ*/
	void save_games() {
		ofstream from_file("save.txt", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
		if (from_file.is_open()) {			
			from_file.write((char*)&igrok, sizeof(igrok));
			from_file.close();
			info = "Игра успешно сохранена";			
		}
		else info = "Cбой сохранения";
	}
	/*ЗАГРУЗКА*/
	void load_games() {
		ifstream from_file("save.txt", std::ios_base::in | std::ios_base::binary);
		if (from_file.is_open()) {
			from_file.read((char*)&igrok, sizeof(igrok));
			from_file.close();
			info = "Игра успешно загружена";	
			
			acsess_main_menu[0] = 1; acsess_main_menu[3] = 1;
			max_verx = var_cur_element = cur_element = 0;			
		}
		else info = "Cбой загрузки";
	}
};
		




