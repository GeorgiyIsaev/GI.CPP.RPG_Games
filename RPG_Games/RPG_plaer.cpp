#pragma once
#include <iostream>
#include <string>
//#include <conio.h> //��� _getch();
//#include <Windows.h> //��� �����
#include "RPG_monstr.cpp"
#include "RPG_zaxvat.cpp"
#include "RPG_map.cpp"
#include "RPG_inventar.cpp"
#include "RPG_Events.cpp"
#include "RPG_triggercpp.cpp"
using namespace std;




class plaer :protected zaxvat {	
	/*���������*/
	string name_plaer = "���������";
	int mani;
	status status;

	triggered_qw trig;
	//std::shared_ptr<triggered_qw> trig;
	//triggered_qw trig;
	events EVENT;
	bool new_day=0;
	/*�������*/
	string name_map;
	int coord_x;
	int coord_y;
	int n_coord_x; /*��� �������� ������*/
	int n_coord_y;
	char simvol_map; /*������ �� ������� ����� ����, ��� �������� ��������� ��������*/
	string info_map_obj;
	RPG_map current_location;
	/*���������� �������� ��������� ��������*/
	/*���������, ���� ����� ������ � ���������� �� 3-4 ������ �������*/
	inventar backpack;
public:	
	plaer() {		
		status.xp = 30; status.max_xp = 30; mani = 500;
		info_map_obj = "\n��� ������������ ����������� WASD ��� �������";	

		/*����� ���������� c ������*/
		coord_x = 18; coord_y = 34; n_coord_x = 18; n_coord_y = 34;
		current_location.make_map_gorod(trig.new_dom);
		name_map = current_location.set_name_map(); /*����� ����� ��� �������� �� ����� ���� �������*/
	}
	void print_status() {
		system("cls");
		cout << setw(5) << "���: " << setw(9) << name_plaer
			<< setw(5) << " (��:" << setw(3) << status.xp << "/" << setw(3) << status.max_xp
			<< setw(7) << ") (���:" << setw(3) << status.vinos / 100 << "/" << setw(3) << status.max_vinos / 100 << ")"
			//<< ") (�����: "<< setw(5) << mani
			<< setw(12) << " �����.: " << coord_x << ":" << coord_y << endl;
	}


	/*  ����   */
	bool print_games(bool& end_games) {
		if (status.xp <= 0) { /*��������� ��������*/
			EVENT.m0001_info_need_dead();
			end_games = 1;
			return 1;
		}
		if (status.vinos <= 401 && status.vinos > 39 && (status.vinos % 30) == 0) { //��������� ��� �������� �����
			EVENT.m0001_info_need_sleep();
		}

		if (trig.e_val == 0)	info_map_obj_this();
		print_status();
		current_location.map_console(coord_x, coord_y);
		/*+���������� � ������� ���������*/
		cout << info_map_obj;
		move_cord();
		/*�������� �� ������, ���� ������, ��� �� ��������*/
		if (stenka_if()) {
			if (status.vinos >= 0) status.vinos--; else status.xp--;
			coord_x = n_coord_x; coord_y = n_coord_y;
		}
		else { /*�����*/ n_coord_x = coord_x; n_coord_y = coord_y; }
		if (send_esc) { send_esc = 0;  return 1; }
		else return 0;

	}
	void print_inventar() {
		while (backpack.accsec_invent()) {
			print_status(); cout << endl;
			backpack.ptint_inventar(status);
		}
		backpack.control_zero();
		//print_games();
	}
	void print_equip() {
		while (backpack.acssec_equp()) {	
			print_status(); //cout << endl;			
			videlenie_stroki_name(EVENT.quest_info(trig)); cout << endl;

			cout << "������� ���� " << trig.day <<setw(10)<< "    ����� � �������� " << mani << endl;			
			backpack.print_eqvip_ststus(new_day); cout << endl;
			backpack.print_eqvip();
						
		}
		backpack.control_zero();
		//print_games();
	}
	/*�������� � ���, ���������� ����� ������������ ��������*/
	int say_NPC(int nomer_NPC) {
		int what = 0;
		bool close = 1; /*��������� 0, �� ���������*/
		while (close) {
			print_status(); cout << endl;
			cout << "� ���: " << mani << " �����\n";
			close = backpack.say_NPC(what, nomer_NPC);
		}
		backpack.control_zero();
		return what; /*��������� �������� ��������*/
	}

	void print_sell(int nomer_NPC) {
		bool close_shop = 1; /*��������� 0, �� ���������*/
		while (close_shop) {
			print_status(); cout << endl;
			cout << "� ���: " << mani << " �����\n";
			close_shop = backpack.sell_inventar(nomer_NPC, mani);
		}
		backpack.control_zero();
	}
	void print_shop_kuzna(int NPC_val) {
		bool close_shop = 1; /*��������� 0, �� ���������*/
		while (close_shop) {
			print_status(); cout << endl;
			cout << "� ���: " << mani << " �����\n";
			if (NPC_val == 1) close_shop = backpack.ptint_shop_kuz(mani);
			else if (NPC_val == 2) close_shop = backpack.ptint_shop_tav(mani);
			else if (NPC_val == 3) close_shop = backpack.ptint_shop_plotnik(mani);
			else  close_shop = 0;
		}
		backpack.control_zero();
	}
	bool print_fight(monstr& new_monstr) {
		bool end_fight = 1; /*��������� 0, �� ���������*/
		bool pobeg = 1;
		while (end_fight) {
			print_status(); cout << endl;
			end_fight = new_monstr.print_flight(status.xp, backpack.set_full_deff(), backpack.set_full_attak(), pobeg);
		}
		new_monstr.control_zero();
		return pobeg;
	}


	/*��� ���������*/
	void sleep_plaeer() {
		trig.acsecc_sleep = 0; trig.acsses_shop_kuz = 1; trig.day++;	status.xp = status.max_xp; status.vinos = status.max_vinos;  new_day = 1; if (trig.dom_postroen) trig.new_dom = 1;   backpack.print_eqvip_ststus(new_day);
	if (trig.vin()) EVENT.m0009_info_game_VIN(trig);
	}
	bool stenka_if() {
		/*�������� �� ����� �� �������*/
		if (n_coord_x < 0 || n_coord_x > 19 || n_coord_y < 0 || n_coord_y >59) return false;
		/*�������� �� ������ �������*/
		simvol_map = current_location.set_simvol_coord(n_coord_x, n_coord_y);
		if (simvol_map == '|' || simvol_map == '*' || simvol_map == 'O'
			|| simvol_map == '�' || simvol_map == '_' || simvol_map == '�' || simvol_map == '�' ) return false;		
		return true;
	}
	void move_cord() {
		send_enter = 0;
		//backpack.keu_bag_enter_if() = 0;
		int val = key_enter();
		switch (val) {
		case 72: case -106: case -26: case 119: case 87:
			n_coord_x--; trig.e_val = 0; break;
		case 80: case -101: case -21: case 115: case 83:
			n_coord_x++;  trig.e_val = 0; break;
		case 75: case -108: case -28: case 97: case 65:
			n_coord_y--;  trig.e_val = 0; break;
		case 77: case -126: case -94: case 100: case 68:
			n_coord_y++;  trig.e_val = 0; break;
		case 13: case 69: case 101: case -45: case -13: case 211: case 243:
			//	�������� ENTER(13) ��� E (211 � 243 ������? ����� ����������)	
			/*backpack.keu_bag_enter_if() = 1;*/ send_enter = 1;
			enter_map_obj(); trig.e_val = 1; break;
		case 9: case 105: case 73: case -40: case -8:
			if (backpack.accsec_invent()) backpack.accsec_invent() = 0; else backpack.accsec_invent() = 1; print_inventar(); break;
			//	i I (� �) (9-Tab)
		case 32:  //������ �			
			if (backpack.acssec_equp()) backpack.acssec_equp() = 0; else  backpack.acssec_equp() = 1;
			send_c = 1;	print_equip(); break;
		case 27: //(esc - 27)
			send_esc = 1; send_inventar = 0; send_c = 0; backpack.accsec_invent() = 0;
			backpack.acssec_equp() = 0;
		}
	}

	/**********************/
	/*****������ �����*****/
	/**********************/

	void info_map_obj_this() {
		if (name_map == "map_kolodec") {
			if (simvol_map == '�') { info_map_obj = "\n�������������� ���� �����!"; }
			else if (simvol_map == '&') {
				int level = rand() % (trig.day + trig.day / 2) + 1;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					current_location.set_simvol_coord(coord_x, coord_y) = '`';
					info_map_obj = "\n�� ������� ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";
				}
				else info_map_obj = "\n��� ������� �������� ���!";
			}
			else if (simvol_map == 'Q') {
				if (!trig.dead_quen) {
					int level = rand() % (trig.day + trig.day / 2) + 1;
					monstr new_monstr(level, 10);
					if (print_fight(new_monstr)) {
						current_location.set_simvol_coord(coord_x, coord_y) = '`';
						trig.dead_quen = 1; 
						info_map_obj = "\n�� ������� ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";
					}
					else info_map_obj = "\n��� ������� �������� ���!";
				}
			}
			else if (coord_x == 3 && coord_y == 53) {
				n_coord_x = coord_x = 2; n_coord_y = coord_y = 54;
				current_location.make_map_gorod(trig.new_dom);
				name_map = current_location.set_name_map();
				info_map_obj = "\n�������� �� ����";
			}
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "map_les") {
			if (simvol_map == '�') {
				info_map_obj = "\n�������������� ���� �����!";
			}
			else if (simvol_map == '&') {
				int level = rand() % trig.day + (trig.day / 2) + 1;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					info_map_obj = "\n�� ������� ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";
					current_location.set_simvol_coord(coord_x, coord_y) = '`';
				}
				else info_map_obj = "\n��� ������� �������� ���!";
			}
			else if (simvol_map == '�') {
				info_map_obj = "\n��� ������� ����� ����� �������!";
			}
			else if (coord_x == 17 && coord_y == 57) {
				n_coord_x = coord_x = 11; n_coord_y = coord_y = 1;
				current_location.make_map_gorod(trig.new_dom);;
				name_map = current_location.set_name_map();
				info_map_obj = "\n�������� � �����";
			}
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "map_gorod" /*&& (*trig).e_val == 0*/) {
			if (coord_x == 17 && coord_y == 40) { info_map_obj = "\n��� ��� �����. ������ ������� � ����� ��� ��� ����������!"; }
			else if (coord_x == 11 && coord_y == 40) { info_map_obj = "\n��� ��� �����. ������ ������� � ����� ��� ��� ����������!"; }
			else if (coord_x == 15 && coord_y == 23) { info_map_obj = "\n��� �������. ����� ����� ���������� ������ � �������!"; }
			else if (coord_x == 8 && coord_y == 23) { info_map_obj = "\n��� �������. ����� ����� ������� � ������� � �������� ����"; }
			else if (coord_x == 11 && coord_y == 0) { info_map_obj = "\n��� ����� ���. ����� ���� �������� ��� �������� ����������"; }
			else if (coord_x == 1 && coord_y == 53) { info_map_obj = "\n������ �������!! �������� ������ � �������"; }
			else if (coord_x == 1 && coord_y == 55) { info_map_obj = "\n������ �������!! �������� ������ � �������"; }
			else if (simvol_map == '#') { info_map_obj = "\n���� �����. �������� ����� ����� ���-�� �����"; }
			else if (coord_x == 6 && coord_y == 46) { info_map_obj = "\n���� ��� ���. ����� � ����� ����� �����"; }
			else if ((coord_x >= 17 && coord_x <= 19) && (coord_y >= 33 && coord_y <= 34)) {
				if (!trig.prolog) { EVENT.m0000_prolog(); trig.prolog = 1; }
			}
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}

		else if (name_map == "kuzn_Maika") {
			if (coord_x == 13 && coord_y == 44) { info_map_obj = "\n�������� � ���������"; }
			else if ((coord_x >= 11 && coord_x <= 14) && (coord_y >= 29 && coord_y <= 33)) {
				if (trig.end_qv_kuz) {
					info_map_obj = "\n������� ������� - \"�������� �����\"";
					item_Wep wep;
					wep.crw_1_kinjal();
					backpack.add_item(wep);
					mani += 400;
				}
				EVENT.Q_kuz(trig);  info_map_obj = "\n������ �����. �� ������� ����������";
			}
			else if (coord_x == 9 && coord_y == 19) { info_map_obj = "\n�������� �������. �������� �������"; }
			else if (simvol_map == '[' || simvol_map == ']') { info_map_obj = "\n������ �������, ��� �� �����"; }
			else if (simvol_map == '�') { info_map_obj = "\n������� ����"; }
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "kuzn_podval") {
			if (coord_x == 9 && coord_y == 19) { info_map_obj = "\n�������� � �������"; }
			else if (simvol_map == '�') { info_map_obj = "\n��������� ����� �������"; }
			else if (!trig.kill_kroto_kris && (coord_x >= 7 && coord_x <= 9) && (coord_y >= 25 && coord_y <= 27)) {
				int level = rand() % trig.day + (trig.day / 2) + 1;
				monstr new_monstr(1, 0);
				if (print_fight(new_monstr)) {
					trig.kill_kroto_kris = 1;
					name_map = current_location.set_name_map();
					current_location.make_map_kuz_podval();
					info_map_obj = "\n�� ������� ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";
					trig.end_qv_kuz = 1; 
				}
				else info_map_obj = "\n��� ������� �������� ���!";
			}
			else if (coord_x == 9 && coord_y == 33) {
				info_map_obj = "\n�������� ��������� ����";
			}
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "taverna") {
			if (coord_x == 14 && coord_y == 30) { info_map_obj = "\n�������� � ��������"; }
			else if (coord_x == 2 && coord_y == 20) { info_map_obj = "\n�������� �� ����� ����"; }
			else if (coord_x == 8 && coord_y == 42) { info_map_obj = "\n��������� � ������"; }
			else if ((coord_x >= 5 && coord_x <= 9) && (coord_y >= 26 && coord_y <= 30)) {
				if ((trig).kill_tav_kr == 5 && !(trig).qw_taverna_vin) { mani += 900; }
				if (!(trig).tell_dogadka && (trig).quest_find_ochag1 && (trig).quest_find_ochag2 && (trig).quest_find_ochag3) { mani += 1900; }
				if ((trig).dead_quen && !(trig).tell_quen) { mani += 2900; }
				EVENT.Q_traktir(trig);				
				info_map_obj = "\n���������� � �������� ��������";
			}
			else if (simvol_map == '�') { info_map_obj = "\n��������� ����� �����������"; }
			else if (simvol_map == '�') { info_map_obj = "\n������� ����"; }
			else if (coord_x == 6 && coord_y == 19) { info_map_obj = "\n������� ����. ���� - �����"; }
			else if (coord_x == 7 && coord_y == 13) { info_map_obj = "\n������� ����. ���� - 21 ����"; }
			else if (coord_x == 3 && coord_y == 12) { info_map_obj = "\n������� ����. ���� - �����-���"; }
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "taverna_pod") {
			if ((coord_x >= 7 && coord_x <= 8) && (coord_y >= 40 && coord_y <= 42) && ((trig).kill_tav_kr == 0)) {
				int level = rand() % ((trig).day + (trig).day / 2) + 1 + 2;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					(trig).kill_tav_kr = 1;/*������ �������� ����� ������*/
					current_location.make_map_tav_pod_1_kr();
					info_map_obj = "\n�� ������ ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";

				}
				else info_map_obj = "\n��� ������� �������� ���!";
			}
			else if ((coord_x >= 2 && coord_x <= 3) && (coord_y >= 29 && coord_y <= 35) && ((trig).kill_tav_kr == 1)) {
				int level = rand() % ((trig).day + (trig).day / 2) + 1 + 2;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					(trig).kill_tav_kr = 2;
					current_location.make_map_tav_pod_2_kr();
					info_map_obj = "\n�� ������ ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";
				}
				else info_map_obj = "\n��� ������� �������� ���!";
			}
			else if ((coord_x >= 6 && coord_x <= 8) && (coord_y >= 12 && coord_y <= 16) &&
				(((trig).kill_tav_kr == 2) || ((trig).kill_tav_kr == 4))) {
				int level = rand() % (trig.day + (trig).day / 2) + 1 + 2;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					if ((trig).kill_tav_kr == 2) { current_location.make_map_tav_pod_3l_kr(); (trig).kill_tav_kr = 3; }
					else if ((trig).kill_tav_kr == 4) { current_location.make_map_tav_pod(); (trig).kill_tav_kr = 5; }
					info_map_obj = "\n�� ������ ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";

				}
				else info_map_obj = "\n��� ������� �������� ���!";
			}
			else if ((coord_x >= 6 && coord_x <= 8) && (coord_y >= 22 && coord_y <= 27) &&
				(((trig).kill_tav_kr == 2) || (trig.kill_tav_kr == 3))) {
				int level = rand() % ((trig).day + (trig).day / 2) + 1 + 2;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					if ((trig).kill_tav_kr == 2) { current_location.make_map_tav_pod_4r_kr(); (trig).kill_tav_kr = 4; }
					else if ((trig).kill_tav_kr == 3) { current_location.make_map_tav_pod(); (trig).kill_tav_kr = 5; }
					info_map_obj = "\n�� ������ ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";

				}
				else info_map_obj = "\n��� ������� �������� ���!";
			}
			else if (simvol_map == '�') { info_map_obj = "\n��������� ����� �����������"; }
			else if (coord_x == 8 && coord_y == 9) { info_map_obj = "\n�������� ������� ����"; }
			else if (coord_x == 8 && coord_y == 42) { info_map_obj = "\n�������� � �������"; }
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "taverna_2lv") {
			if ((coord_x == 4 && coord_y == 33) || (coord_x == 4 && coord_y == 34) || (coord_x == 6 && coord_y == 19) ||
				(coord_x == 7 && coord_y == 22) || (coord_x == 8 && coord_y == 19) ||
				(coord_x == 11 && coord_y == 20) || (coord_x == 11 && coord_y == 21)) {
				info_map_obj = "\n����� � �������";
			}
			else if (simvol_map == '[' || simvol_map == ']') { info_map_obj = "\n������ �������, ��� �� �����"; }
			else if (simvol_map == '�') { info_map_obj = "\n������� ����"; }
			else if (coord_x == 2 && coord_y == 20) {
				/*������� � �������*/
				info_map_obj = "\n��������� � �������";
			}
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "dom_Matoi") {
			if (coord_x == 9 && coord_y == 15) { info_map_obj = "\n�������� � �����"; }
			else if ((coord_x >= 6 && coord_x <= 8) && (coord_y >= 22 && coord_y <= 28)) { EVENT.Q_plotnik(trig); info_map_obj = "\n������� �����"; }
			else if (simvol_map == '�') { info_map_obj = "\n������� ����"; }
			else { info_map_obj = "\n��� ������������ ����������� WASD ��� �������"; }
		}
		else if (name_map == "moi_dom") {
			if (simvol_map == '[' || simvol_map == ']') { info_map_obj = "\n��� ��� �������"; }
			else if (simvol_map == '�') { info_map_obj = "\n��� y������ ����"; }
			else if (simvol_map == '�') { info_map_obj = "\n��������� �����"; }
			else if (coord_x == 13 && coord_y == 29) {
				info_map_obj = "\n�������� � �����";
			}
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
	}

	

	/*********************/
	/* �������� �� ����� */
	/*********************/

	void enter_map_obj() {
		/*����� ����� ������������� ���������� ��������*/ 
		if (name_map == "map_kolodec") {
			if (simvol_map == '�') {
				/*random_lamder() random_find() random_drop()*/
				backpack.random_find(info_map_obj);
				current_location.set_simvol_coord(coord_x, coord_y) = '`'; }
			else if (simvol_map == '&') {
				int level = rand() % (((trig).day + (trig).day/2)) + 1;
				monstr new_monstr(level, rand() % 2);
				print_fight(new_monstr);
				info_map_obj = "�� ������� ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";
				current_location.set_simvol_coord(coord_x, coord_y) = '`';
			}
			else if (simvol_map == 'Q') { current_location.set_simvol_coord(coord_x, coord_y) = '`'; info_map_obj = "\n�� ��������� � ���������� �����-������"; }
			else if (coord_x == 3 && coord_y == 53) {
				n_coord_x = coord_x = 2; n_coord_y = coord_y = 54;
				current_location.make_map_gorod((trig).new_dom);;
				name_map = current_location.set_name_map();
				info_map_obj = "\n�� ��������� � �����";
			}
		}
		else if (name_map == "map_les") {
			if (simvol_map == '�') {
				/*random_lamder() random_find() random_drop()*/
				backpack.random_find(info_map_obj);
				current_location.set_simvol_coord(coord_x, coord_y) = '`';
			}
			else if (simvol_map == '&') {
				int level = rand() % ((trig).day + (trig).day / 2) + 1;
				monstr new_monstr(level, rand() % 2);
				print_fight(new_monstr);
				info_map_obj = "�� ������� ������� �������� " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " ���������";
				current_location.set_simvol_coord(coord_x, coord_y) = '`';
			}
			else if (simvol_map == '�') {
				if (backpack.random_lamder(info_map_obj)) {	current_location.set_simvol_coord(coord_x, coord_y) = '`';	}
			}
			else if (coord_x == 17 && coord_y == 57) {
				n_coord_x = coord_x = 11; n_coord_y = coord_y = 1;
				current_location.make_map_gorod((trig).new_dom);
				name_map = current_location.set_name_map();
				info_map_obj = "\n�� ��������� � �����";
			}			
		}
		else if (name_map == "map_gorod") {
			if (coord_x == 11 && coord_y == 40) {
				/*��� �����*/
				if ((trig).acsses_plot) {
					n_coord_x = coord_x = 9; n_coord_y = coord_y = 16;
					current_location.make_dom_matoi();
					name_map = current_location.set_name_map();
				}
				else info_map_obj = "\n� ���� ���� ������ ����";
			}
			else if (coord_x == 17 && coord_y == 40) { info_map_obj = "\n������ ������� � ����� ��� ��� ����������"; }
			else if (coord_x == 15 && coord_y == 23) {
				if ((trig).acsses_kuz) {
					coord_x = 13; coord_y = 43; n_coord_x = 13; n_coord_y = 43;
					current_location.make_map_kuznia();
					name_map = current_location.set_name_map();
				}
				else info_map_obj = "\n� ���� ���� ������ ����";
			}
			else if (coord_x == 8 && coord_y == 23) {
				if ((trig).acsses_trak) {
					n_coord_x = coord_x = 14; n_coord_y = coord_y = 29;
					current_location.make_map_taverna();
					name_map = current_location.set_name_map();
				}
				else info_map_obj = "\n� ���� ���� ������ ����";
			}
			else if (coord_x == 11 && coord_y == 0) {
				if ((trig).day > 1) {
					n_coord_x = coord_x = 17; n_coord_y = coord_y = 56;
					current_location.make_map_les();
					name_map = current_location.set_name_map();
					info_map_obj = "\n�� ����� � ���";
				}
				else info_map_obj = "\n� ���� ���� ������ ����!";
			}
			else if (coord_x == 1 && (coord_y >= 53 && coord_y <= 55)) {
				/*�������*/
				if ((trig).quest_find_ochag && !(trig).quest_find_ochag3) {
					(trig).quest_find_ochag3 = 1;
					(trig).detect_if();
					EVENT.m0013_info_kro_kolod();

				}
				else {
					if ((trig).acsecc_kol) {
						if (backpack.find_verevka()) {
							n_coord_x = coord_x = 3; n_coord_y = coord_y = 52;
							current_location.make_map_koldec();
							if (!(trig).dead_quen) {
								current_location.set_simvol_coord(11, 13) = 'Q';
								current_location.set_simvol_coord(11, 14) = '&';
								current_location.set_simvol_coord(12, 14) = '&';
							}/*��������� �������� ���� ��� ����������*/
							name_map = current_location.set_name_map();
							info_map_obj = "\n�� ���������� � �������";
						}
						else info_map_obj = "\n��� �� ��������� ��� ����� �������";
					}
					else info_map_obj = "\n� ������� ��� ��� ����";
				}
			}
			else if (coord_x == 13 && coord_y == 55 && !(trig).find_krepkai_palka) {
				/*������ ������� ����� �� ����� ������*/
				info_map_obj = "\n������� ������� - \"�������� �����\"";
				item_Wep wep;
				wep.crw_0_palka();
				backpack.add_item(wep);
				(trig).find_krepkai_palka = 1;
			}
			else if (simvol_map == '#') { info_map_obj = "\n��� ������ ���"; }
			else if (coord_x == 6 && coord_y == 46) {
				if (!(trig).see_house) { EVENT.m0001_moi_dom(); (trig).see_house = 1; (trig).acsses_trak = 1; }
				if((trig).new_dom) {
				n_coord_x = coord_x = 13; n_coord_y = coord_y = 30;
				current_location.make_map_dom();
				name_map = current_location.set_name_map();
				}
				else	info_map_obj = "\n��� ��� ��������";			
			}
		}
		else if (name_map == "moi_dom") {
			if (simvol_map == '[' || simvol_map == ']') { 
				if (status.vinos < status.max_vinos - 100) {
					sleep_plaeer(); /*���*/
					info_map_obj = "\n�������� ����� ����! �� ����������� ����!";
				}
				else info_map_obj = "\n� ��� ������ ��������, � �� ���� ����� ���� �����!"; }
			else if (simvol_map == '�') { info_map_obj = "\n�� ��� ������������� y������ ����"; }
			else if (simvol_map == '�') { info_map_obj = "\n��� ��������� �����"; }
			else if (coord_x == 13 && coord_y == 29) {
				n_coord_x = coord_x = 6; n_coord_y = coord_y = 47;
				current_location.make_map_gorod((trig).new_dom);
				name_map = current_location.set_name_map();
				info_map_obj = "\n� �������� � �����"; }
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "kuzn_Maika") {
			if (coord_x == 13 && coord_y == 44) {
				n_coord_x = coord_x = 15; n_coord_y = coord_y = 24;
				current_location.make_map_gorod((trig).new_dom);;
				name_map = current_location.set_name_map();
			}
			else if ((coord_x >= 11 && coord_x <= 14) && (coord_y >= 29 && coord_y <= 33)) {
				/*�������*/
				if ((trig).acsses_shop_kuz) {
					int val = say_NPC(1);
					if (val == 1) { print_shop_kuzna(1); }
					else if (val == 2) { print_sell(1); }
					info_map_obj = "\n��������� ���!";
				}
				else info_map_obj = "\n��������� ������!";
			}
			else if (coord_x == 9 && coord_y == 19) {
				/*������ �������*/
				if ((trig).find_krepkai_palka) {
					n_coord_x = coord_x = 9; n_coord_y = coord_y = 20;// n_coord_x = 10; n_coord_y = 19;
					if ((trig).kill_kroto_kris)	current_location.make_map_kuz_podval();
					else current_location.make_map_kuz_podval_qw();
					name_map = current_location.set_name_map();
				}
				else info_map_obj = "\n����� ����� �� ����� ����� ������ ������!";
			}
			else if (simvol_map == '[' || simvol_map == ']') { info_map_obj = "\n������ ����� � ����� �������"; }
			else if (simvol_map == '�') { info_map_obj = "\n�� ��� ������������� y������ ����"; }
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "kuzn_podval") {
			if (coord_x == 9 && coord_y == 19) {
				n_coord_x = coord_x = 9; n_coord_y = coord_y = 20;
				current_location.make_map_kuznia();
				name_map = current_location.set_name_map();
			}			
			else if (simvol_map == '�') { info_map_obj = "\n��������� ����� �������"; }
			else if (coord_x == 9 && coord_y == 33) {
				if ((trig).quest_find_ochag && !(trig).quest_find_ochag2) {
					(trig).quest_find_ochag2 = 1;
					(trig).detect_if();
					EVENT.m0011_info_kro_tav();
				}
				else info_map_obj = "\n������ ����� ��� ���� ���� ��������� �����-����"; }
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}

		else if (name_map == "taverna") {
			if (coord_x == 14 && coord_y == 30) {
				/*������� � �����*/
				n_coord_x = coord_x = 8; n_coord_y = coord_y = 24;
				current_location.make_map_gorod((trig).new_dom);
				name_map = current_location.set_name_map();
			}
			else if (coord_x == 2 && coord_y == 20) {
				if ((trig).acsecc_sleep) {
					n_coord_x = coord_x = 2; n_coord_y = coord_y = 21;
					current_location.make_map_tavern_2lv();
					name_map = current_location.set_name_map();
					info_map_obj = "\n����������� ����!";
				}
				else info_map_obj = "\n������� ����� ��������� �� ���������!";
			}
			else if (coord_x == 8 && coord_y == 42) {
				/*����� � ������ �������*/
				if ((trig).acsecc_podval_tav) {
					n_coord_x = coord_x = 8; n_coord_y = coord_y = 41;
					if ((trig).kill_tav_kr == 0) current_location.make_map_tav_pod_0kr();
					else if ((trig).kill_tav_kr == 1) current_location.make_map_tav_pod_1_kr();
					else if ((trig).kill_tav_kr == 2) current_location.make_map_tav_pod_2_kr();
					else if ((trig).kill_tav_kr == 3) current_location.make_map_tav_pod_3l_kr();
					else if ((trig).kill_tav_kr == 4) current_location.make_map_tav_pod_4r_kr();
					else if ((trig).kill_tav_kr == 5) current_location.make_map_tav_pod();
					name_map = current_location.set_name_map();
				}
				else info_map_obj = "\n������ ������� ��� ����������";			
			}
			else if ((coord_x >= 5 && coord_x <= 9) && (coord_y >= 26 && coord_y <= 30)) {
				/*�������� � �������������*/
				if ((trig).acsses_shop_tr) {
					/*�������*/
					int val = say_NPC(2);
					if (val == 1) { print_shop_kuzna(2); }
					else if (val == 2) { print_sell(2); }
					else if (val == 3) EVENT.m0109_taverna_gde_bablo();
					else if (val == 4) {
						if (!(trig).acsecc_sleep) {
							if (mani >= 90) {
								info_map_obj = "\n��� 90 ���� �� �������!"; mani -= 90;
								(trig).acsecc_sleep = 1;
							}
							else info_map_obj = "\n� ���� ������������ �����!";
						
						}
						else info_map_obj = "\n�� ��� ������� �� �������!";
					}
					else info_map_obj = "\n��������� ���!";

					

				}
				else info_map_obj = "\n� ���� ���� ������ ����!";
			}
			else if (simvol_map == '�') { info_map_obj = "\n������ ����� ����� ����"; }
			else if (simvol_map == '�') { info_map_obj = "\n�� ��� ������������� ������� ����"; }
			else if (coord_x == 6 && coord_y == 19) { info_map_obj = "\n���� � ����� �����������, �� ��� �����"; }
			else if (coord_x == 7 && coord_y == 13) { info_map_obj = "\n���� - 21 ���� - �� �� �����"; }
			else if (coord_x == 3 && coord_y == 12) { info_map_obj = "\n���� - �����-��� ���� ������ � �������"; }
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		if (name_map == "taverna_2lv") {
			if ((coord_x == 4 && coord_y == 33) || (coord_x == 4 && coord_y == 34) ||
				(coord_x == 7 && coord_y == 22) || (coord_x == 8 && coord_y == 19) ||
				(coord_x == 11 && coord_y == 20) || (coord_x == 11 && coord_y == 21))
			{		info_map_obj = "\n������ ����� � ����� �������";}
			else if (simvol_map == '[' || simvol_map == ']') {
				if ((trig).acsecc_sleep) {
					sleep_plaeer(); /*���*/
					info_map_obj = "\n�������� ����� ����! �� ����������� ����!";
				}
				else info_map_obj = "\n� �� ���� ����� � ����� �������!";
			}
			else if (simvol_map == '�') { info_map_obj = "\n�� ��� ������������� ������� ����"; }
			else if (coord_x == 2 && coord_y == 20) {
				/*������� � �������*/
				n_coord_x = coord_x = 2; n_coord_y = coord_y = 19;
				current_location.make_map_taverna();
				name_map = current_location.set_name_map();
				info_map_obj = "\n��������� � �������";
			}		
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		if (name_map == "taverna_pod") {
			if (coord_x == 8 && coord_y == 42) {
				/*�������� � �������*/
				n_coord_x = coord_x = 8; n_coord_y = coord_y = 43;
				current_location.make_map_taverna();
				name_map = current_location.set_name_map();
			}			
			else if (simvol_map == '�') { info_map_obj = "\n��������� ����� �����������"; }
			else if (coord_x == 8 && coord_y == 9) {
				if ((trig).quest_find_ochag && !(trig).quest_find_ochag1) {
					(trig).quest_find_ochag1 = 1;
					(trig).detect_if();
					EVENT.m0012_info_kro_kuz();
				}
				else info_map_obj = "\n������ ��� ���� ����� � ������ ����. ��������"; }			
			else info_map_obj = "\n��� ������������ ����������� WASD ��� �������";
		}
		else if (name_map == "dom_Matoi") {
			if (coord_x == 9 && coord_y == 15) {
				/*��� �����*/
				n_coord_x = coord_x = 11; n_coord_y = coord_y = 39;
				current_location.make_map_gorod((trig).new_dom);
				name_map = current_location.set_name_map();
			}
			else if ((coord_x >= 6 && coord_x <= 8) && (coord_y >= 22 && coord_y <= 28)) {			
				int val;
				/*������� ��������*/
				if ((trig).dom_postroen) val = say_NPC(4); //������ ������ ������ ����� ���������
				else val = say_NPC(3);
				if (val == 1) { print_shop_kuzna(3); }
				else if (val == 2) { print_sell(3); }
				else if (val == 3) { 
					/*������*/
					if(!(trig).need_brevna){
						if (backpack.giv_brevna()) {
							(trig).count_brevna--;
							info_map_obj = "\n����� ������! ����� ��� " + to_string((trig).count_brevna);
							(trig).if_complate_dom();
						}
						else info_map_obj = "\n� ���� ��� ������! ����� ��� " + to_string((trig).count_brevna);
					}
					else info_map_obj = "\n��� ������������� ������ �� ����� ������!";
				}
				else if (val == 4) {
					/*������*/ 
					if (!(trig).need_bgbozdi) {
						if (backpack.giv_gvozdi()) {
							(trig).count_bgbozdi--;
							info_map_obj = "\n����� �������! ����� ��� " + to_string((trig).count_bgbozdi);
							(trig).if_complate_dom();
						}
						else info_map_obj = "\n� ���� ��� ������� �������! ����� ��� " + to_string((trig).count_bgbozdi);
					}
					else info_map_obj = "\n��� ������������� ������ �� ����� ������!";					
				}
				else info_map_obj = "\n��������� ���!";
			}
			else if (simvol_map == '�') { info_map_obj = "\n�� ��� ������������� ������� ����"; }
			else {info_map_obj = "\n��� ������������ ����������� WASD ��� �������";	}
		}
	}
};




