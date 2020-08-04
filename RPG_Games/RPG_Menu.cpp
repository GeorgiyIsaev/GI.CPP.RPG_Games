#pragma once
#include <iostream>
#include <string>
#include "RPG_zaxvat.cpp"
#include "RPG_plaer.cpp"
//#include "RPG_inventar.cpp"
//RPG_Menu.cpp
#include <fstream> // �������� ������
#include <sstream> //��������� ������
#include "RPG_triggercpp.cpp"

class RPG_menu :protected zaxvat {
	string main_menu[6] = { "����������-->","�����  ����", "���������", "���������", "����������!", "�����" };
	string info_menu[6] = { "�������� � ������� ����",
		"��������� ���� � ������",
		"��������� ��������� ����������",
		"��������� ������� ����",
		"���������� �� ���������� � ����",
		"����� �� ���� ��� ����������!" };
	plaer igrok;
	string info = "";
	bool game_new_start = 1;
	bool game_over = 0;
public:
	RPG_menu() {	
		/*����� ����������� ������ ��������� ���������*/
		menu_if = 1;
		/*������ � ������� ���������� ����*/
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
		menu_move_cord(); /*������������ �� ���� ����������*/
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
		else if (cur_element == 2) { load_games();/*����*/ }
		else if (cur_element == 3) { save_games();/*����*/ }
		else if (cur_element == 4) { print_info_control(); }
		//else if (cur_element == 5) {/*�����*/ }
	}
	void print_info_control() {

		while (!send_esc) {
			system("cls");
			cout << "\n\n����������: \n\n"
				"WASD � ��������� - ��� ����������� �� ���� � ������ ����.\n"
				"ESC � ������� � ����, ������� � ����.\n"
				"Enter(E) � ��������� ��������.\n"
				"Tab(I) � ���������.\n"
				"Space(C) � ���� ���������.\n"
				"\n\n������� ESC ��� Enter, ��� �� �������� � ����.\n";
			menu_move_cord();
			if (send_enter) { send_enter = send_esc = 1; }
		}
		send_esc = 0;
	}
	void new_games() {
		if (acsess_main_menu[0]) new_games_danger();/*���� ���� ���� ��������, �������� �� ���������� �������*/
		//else game_new_start = 1;
		if (game_new_start) {
			igrok = plaer();
			game_over = 0;
			acsess_main_menu[0] = 1; acsess_main_menu[3] = 1; max_verx = var_cur_element = cur_element = 0; /*�������� ���� ����������*/
			/*����� ����*/
			games_continue();
		}
		send_esc = 0;
	}
	void new_games_danger() {
		send_esc = 0;
		while (!send_esc) {
			system("cls");
			cout << "\n\n\n\n"
				"                         ��������!\n\n\n"
				"   ��� ������� ����� ����, ������� �������� ����� ������!\n\n\n"

				"   ESC - �������� � ����!      Enter - ������ ����� ����!\n";
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
				"                         ��������!\n\n\n"
				"  ���� �� ������� �� ����, ������� �������� ����� ������!\n\n\n"

				"  ESC - �������� � ����!       Enter - ����� �� ����!\n";
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

	/*C���������*/
	void save_games() {
		ofstream from_file("save.txt", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
		if (from_file.is_open()) {			
			from_file.write((char*)&igrok, sizeof(igrok));
			from_file.close();
			info = "���� ������� ���������";			
		}
		else info = "C��� ����������";
	}
	/*��������*/
	void load_games() {
		ifstream from_file("save.txt", std::ios_base::in | std::ios_base::binary);
		if (from_file.is_open()) {
			from_file.read((char*)&igrok, sizeof(igrok));
			from_file.close();
			info = "���� ������� ���������";	
			
			acsess_main_menu[0] = 1; acsess_main_menu[3] = 1;
			max_verx = var_cur_element = cur_element = 0;			
		}
		else info = "C��� ��������";
	}
};
		




