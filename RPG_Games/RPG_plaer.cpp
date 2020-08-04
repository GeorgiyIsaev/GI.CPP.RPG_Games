#pragma once
#include <iostream>
#include <string>
//#include <conio.h> //для _getch();
//#include <Windows.h> //для цвета
#include "RPG_monstr.cpp"
#include "RPG_zaxvat.cpp"
#include "RPG_map.cpp"
#include "RPG_inventar.cpp"
#include "RPG_Events.cpp"
#include "RPG_triggercpp.cpp"
using namespace std;




class plaer :protected zaxvat {	
	/*Состояние*/
	string name_plaer = "Гильвестр";
	int mani;
	status status;

	triggered_qw trig;
	//std::shared_ptr<triggered_qw> trig;
	//triggered_qw trig;
	events EVENT;
	bool new_day=0;
	/*Локация*/
	string name_map;
	int coord_x;
	int coord_y;
	int n_coord_x; /*Для проверки клетки*/
	int n_coord_y;
	char simvol_map; /*Символ на котором стоит перс, для проверки достпного действия*/
	string info_map_obj;
	RPG_map current_location;
	/*Снаряжение отдельно несколько предетов*/
	/*Инвентарь, туту будит список с предметами из 3-4 разных списков*/
	inventar backpack;
public:	
	plaer() {		
		status.xp = 30; status.max_xp = 30; mani = 500;
		info_map_obj = "\nДля передвижения используйте WASD или стрелки";	

		/*Карта начинается c начала*/
		coord_x = 18; coord_y = 34; n_coord_x = 18; n_coord_y = 34;
		current_location.make_map_gorod(trig.new_dom);
		name_map = current_location.set_name_map(); /*нужно будит для проверки из какой локи выходим*/
	}
	void print_status() {
		system("cls");
		cout << setw(5) << "Имя: " << setw(9) << name_plaer
			<< setw(5) << " (ХП:" << setw(3) << status.xp << "/" << setw(3) << status.max_xp
			<< setw(7) << ") (ВЫН:" << setw(3) << status.vinos / 100 << "/" << setw(3) << status.max_vinos / 100 << ")"
			//<< ") (Денег: "<< setw(5) << mani
			<< setw(12) << " Коорд.: " << coord_x << ":" << coord_y << endl;
	}


	/*  ИГРА   */
	bool print_games(bool& end_games) {
		if (status.xp <= 0) { /*Запускаем умирание*/
			EVENT.m0001_info_need_dead();
			end_games = 1;
			return 1;
		}
		if (status.vinos <= 401 && status.vinos > 39 && (status.vinos % 30) == 0) { //сообщение что персонаж устал
			EVENT.m0001_info_need_sleep();
		}

		if (trig.e_val == 0)	info_map_obj_this();
		print_status();
		current_location.map_console(coord_x, coord_y);
		/*+информация о текущем дейтсивии*/
		cout << info_map_obj;
		move_cord();
		/*Проверка на стенку, если стенка, ход не делается*/
		if (stenka_if()) {
			if (status.vinos >= 0) status.vinos--; else status.xp--;
			coord_x = n_coord_x; coord_y = n_coord_y;
		}
		else { /*откат*/ n_coord_x = coord_x; n_coord_y = coord_y; }
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

			cout << "Игровой день " << trig.day <<setw(10)<< "    Монет в кошельке " << mani << endl;			
			backpack.print_eqvip_ststus(new_day); cout << endl;
			backpack.print_eqvip();
						
		}
		backpack.control_zero();
		//print_games();
	}
	/*Разговор с НПС, возвращает номер выполняемого действия*/
	int say_NPC(int nomer_NPC) {
		int what = 0;
		bool close = 1; /*Пробросит 0, из инвентаря*/
		while (close) {
			print_status(); cout << endl;
			cout << "У вас: " << mani << " монет\n";
			close = backpack.say_NPC(what, nomer_NPC);
		}
		backpack.control_zero();
		return what; /*возаращем выбраное действие*/
	}

	void print_sell(int nomer_NPC) {
		bool close_shop = 1; /*Пробросит 0, из инвентаря*/
		while (close_shop) {
			print_status(); cout << endl;
			cout << "У вас: " << mani << " монет\n";
			close_shop = backpack.sell_inventar(nomer_NPC, mani);
		}
		backpack.control_zero();
	}
	void print_shop_kuzna(int NPC_val) {
		bool close_shop = 1; /*Пробросит 0, из инвентаря*/
		while (close_shop) {
			print_status(); cout << endl;
			cout << "У вас: " << mani << " монет\n";
			if (NPC_val == 1) close_shop = backpack.ptint_shop_kuz(mani);
			else if (NPC_val == 2) close_shop = backpack.ptint_shop_tav(mani);
			else if (NPC_val == 3) close_shop = backpack.ptint_shop_plotnik(mani);
			else  close_shop = 0;
		}
		backpack.control_zero();
	}
	bool print_fight(monstr& new_monstr) {
		bool end_fight = 1; /*Пробросит 0, из инвентаря*/
		bool pobeg = 1;
		while (end_fight) {
			print_status(); cout << endl;
			end_fight = new_monstr.print_flight(status.xp, backpack.set_full_deff(), backpack.set_full_attak(), pobeg);
		}
		new_monstr.control_zero();
		return pobeg;
	}


	/*сон персонажа*/
	void sleep_plaeer() {
		trig.acsecc_sleep = 0; trig.acsses_shop_kuz = 1; trig.day++;	status.xp = status.max_xp; status.vinos = status.max_vinos;  new_day = 1; if (trig.dom_postroen) trig.new_dom = 1;   backpack.print_eqvip_ststus(new_day);
	if (trig.vin()) EVENT.m0009_info_game_VIN(trig);
	}
	bool stenka_if() {
		/*Проверка на выход за граници*/
		if (n_coord_x < 0 || n_coord_x > 19 || n_coord_y < 0 || n_coord_y >59) return false;
		/*Проверка на символ прохода*/
		simvol_map = current_location.set_simvol_coord(n_coord_x, n_coord_y);
		if (simvol_map == '|' || simvol_map == '*' || simvol_map == 'O'
			|| simvol_map == '¶' || simvol_map == '_' || simvol_map == 'Ґ' || simvol_map == '—' ) return false;		
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
			//	ДЕЙСТВИЕ ENTER(13) или E (211 и 243 откуда? потом разобратся)	
			/*backpack.keu_bag_enter_if() = 1;*/ send_enter = 1;
			enter_map_obj(); trig.e_val = 1; break;
		case 9: case 105: case 73: case -40: case -8:
			if (backpack.accsec_invent()) backpack.accsec_invent() = 0; else backpack.accsec_invent() = 1; print_inventar(); break;
			//	i I (Ш ш) (9-Tab)
		case 32:  //пробел С			
			if (backpack.acssec_equp()) backpack.acssec_equp() = 0; else  backpack.acssec_equp() = 1;
			send_c = 1;	print_equip(); break;
		case 27: //(esc - 27)
			send_esc = 1; send_inventar = 0; send_c = 0; backpack.accsec_invent() = 0;
			backpack.acssec_equp() = 0;
		}
	}

	/**********************/
	/*****Объеты карты*****/
	/**********************/

	void info_map_obj_this() {
		if (name_map == "map_kolodec") {
			if (simvol_map == '®') { info_map_obj = "\nПодозрительная куча хлама!"; }
			else if (simvol_map == '&') {
				int level = rand() % (trig.day + trig.day / 2) + 1;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					current_location.set_simvol_coord(coord_x, coord_y) = '`';
					info_map_obj = "\nИз убитого монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";
				}
				else info_map_obj = "\nВам удалось покинуть бой!";
			}
			else if (simvol_map == 'Q') {
				if (!trig.dead_quen) {
					int level = rand() % (trig.day + trig.day / 2) + 1;
					monstr new_monstr(level, 10);
					if (print_fight(new_monstr)) {
						current_location.set_simvol_coord(coord_x, coord_y) = '`';
						trig.dead_quen = 1; 
						info_map_obj = "\nИз убитого монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";
					}
					else info_map_obj = "\nВам удалось покинуть бой!";
				}
			}
			else if (coord_x == 3 && coord_y == 53) {
				n_coord_x = coord_x = 2; n_coord_y = coord_y = 54;
				current_location.make_map_gorod(trig.new_dom);
				name_map = current_location.set_name_map();
				info_map_obj = "\nПоднятся на верх";
			}
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "map_les") {
			if (simvol_map == '®') {
				info_map_obj = "\nПодозрительная куча хлама!";
			}
			else if (simvol_map == '&') {
				int level = rand() % trig.day + (trig.day / 2) + 1;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					info_map_obj = "\nИз убитого монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";
					current_location.set_simvol_coord(coord_x, coord_y) = '`';
				}
				else info_map_obj = "\nВам удалось покинуть бой!";
			}
			else if (simvol_map == '¤') {
				info_map_obj = "\nПри наличии топра можно срубить!";
			}
			else if (coord_x == 17 && coord_y == 57) {
				n_coord_x = coord_x = 11; n_coord_y = coord_y = 1;
				current_location.make_map_gorod(trig.new_dom);;
				name_map = current_location.set_name_map();
				info_map_obj = "\nВернутся в город";
			}
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "map_gorod" /*&& (*trig).e_val == 0*/) {
			if (coord_x == 17 && coord_y == 40) { info_map_obj = "\nЭто дом Хелен. Нельзя входить в чужой дом без разрешения!"; }
			else if (coord_x == 11 && coord_y == 40) { info_map_obj = "\nЭто дом Матой. Нельзя входить в чужой дом без разрешения!"; }
			else if (coord_x == 15 && coord_y == 23) { info_map_obj = "\nЭто Кузница. Здесь можно преобрести оружие и доспехи!"; }
			else if (coord_x == 8 && coord_y == 23) { info_map_obj = "\nЭто Таверна. Здесь можно напится и сыграть в азартные игры"; }
			else if (coord_x == 11 && coord_y == 0) { info_map_obj = "\nТам дикий лес. Лучше туда неходить без хорошого снаряжения"; }
			else if (coord_x == 1 && coord_y == 53) { info_map_obj = "\nСтарый колодец!! Выглядит опасно и глубоко"; }
			else if (coord_x == 1 && coord_y == 55) { info_map_obj = "\nСтарый колодец!! Выглядит опасно и глубоко"; }
			else if (simvol_map == '#') { info_map_obj = "\nКуча хлама. Возможно здесь можно что-то найти"; }
			else if (coord_x == 6 && coord_y == 46) { info_map_obj = "\nЭтой мой дом. Здесь я начну новую жизнь"; }
			else if ((coord_x >= 17 && coord_x <= 19) && (coord_y >= 33 && coord_y <= 34)) {
				if (!trig.prolog) { EVENT.m0000_prolog(); trig.prolog = 1; }
			}
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}

		else if (name_map == "kuzn_Maika") {
			if (coord_x == 13 && coord_y == 44) { info_map_obj = "\nВернутся в поселение"; }
			else if ((coord_x >= 11 && coord_x <= 14) && (coord_y >= 29 && coord_y <= 33)) {
				if (trig.end_qv_kuz) {
					info_map_obj = "\nПолучен предмет - \"Крепакая палка\"";
					item_Wep wep;
					wep.crw_1_kinjal();
					backpack.add_item(wep);
					mani += 400;
				}
				EVENT.Q_kuz(trig);  info_map_obj = "\nКузнец Матой. Он продает снаряжение";
			}
			else if (coord_x == 9 && coord_y == 19) { info_map_obj = "\nКладавая кузница. Выгделит зловеще"; }
			else if (simvol_map == '[' || simvol_map == ']') { info_map_obj = "\nМягкая кровать, что бы спать"; }
			else if (simvol_map == 'Ћ') { info_map_obj = "\nУдобный стул"; }
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "kuzn_podval") {
			if (coord_x == 9 && coord_y == 19) { info_map_obj = "\nВернутся в кузницу"; }
			else if (simvol_map == 'Џ') { info_map_obj = "\nСкладские ящики кузница"; }
			else if (!trig.kill_kroto_kris && (coord_x >= 7 && coord_x <= 9) && (coord_y >= 25 && coord_y <= 27)) {
				int level = rand() % trig.day + (trig.day / 2) + 1;
				monstr new_monstr(1, 0);
				if (print_fight(new_monstr)) {
					trig.kill_kroto_kris = 1;
					name_map = current_location.set_name_map();
					current_location.make_map_kuz_podval();
					info_map_obj = "\nИз убитого монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";
					trig.end_qv_kuz = 1; 
				}
				else info_map_obj = "\nВам удалось покинуть бой!";
			}
			else if (coord_x == 9 && coord_y == 33) {
				info_map_obj = "\nСтранная небольшая нора";
			}
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "taverna") {
			if (coord_x == 14 && coord_y == 30) { info_map_obj = "\nВернутся в посление"; }
			else if (coord_x == 2 && coord_y == 20) { info_map_obj = "\nЛестница на втрой этаж"; }
			else if (coord_x == 8 && coord_y == 42) { info_map_obj = "\nСпустится в подвал"; }
			else if ((coord_x >= 5 && coord_x <= 9) && (coord_y >= 26 && coord_y <= 30)) {
				if ((trig).kill_tav_kr == 5 && !(trig).qw_taverna_vin) { mani += 900; }
				if (!(trig).tell_dogadka && (trig).quest_find_ochag1 && (trig).quest_find_ochag2 && (trig).quest_find_ochag3) { mani += 1900; }
				if ((trig).dead_quen && !(trig).tell_quen) { mani += 2900; }
				EVENT.Q_traktir(trig);				
				info_map_obj = "\nПоговорить с хозяином трактира";
			}
			else if (simvol_map == 'Џ') { info_map_obj = "\nСкладские ящики трактирщика"; }
			else if (simvol_map == 'Ћ') { info_map_obj = "\nУдобный стул"; }
			else if (coord_x == 6 && coord_y == 19) { info_map_obj = "\nИгровой стол. Игра - Кости"; }
			else if (coord_x == 7 && coord_y == 13) { info_map_obj = "\nИгровой стол. Игра - 21 Очко"; }
			else if (coord_x == 3 && coord_y == 12) { info_map_obj = "\nИгровой стол. Игра - Цифро-Бой"; }
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "taverna_pod") {
			if ((coord_x >= 7 && coord_x <= 8) && (coord_y >= 40 && coord_y <= 42) && ((trig).kill_tav_kr == 0)) {
				int level = rand() % ((trig).day + (trig).day / 2) + 1 + 2;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					(trig).kill_tav_kr = 1;/*Тригер меняется после победы*/
					current_location.make_map_tav_pod_1_kr();
					info_map_obj = "\nИз убитых монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";

				}
				else info_map_obj = "\nВам удалось покинуть бой!";
			}
			else if ((coord_x >= 2 && coord_x <= 3) && (coord_y >= 29 && coord_y <= 35) && ((trig).kill_tav_kr == 1)) {
				int level = rand() % ((trig).day + (trig).day / 2) + 1 + 2;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					(trig).kill_tav_kr = 2;
					current_location.make_map_tav_pod_2_kr();
					info_map_obj = "\nИз убитых монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";
				}
				else info_map_obj = "\nВам удалось покинуть бой!";
			}
			else if ((coord_x >= 6 && coord_x <= 8) && (coord_y >= 12 && coord_y <= 16) &&
				(((trig).kill_tav_kr == 2) || ((trig).kill_tav_kr == 4))) {
				int level = rand() % (trig.day + (trig).day / 2) + 1 + 2;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					if ((trig).kill_tav_kr == 2) { current_location.make_map_tav_pod_3l_kr(); (trig).kill_tav_kr = 3; }
					else if ((trig).kill_tav_kr == 4) { current_location.make_map_tav_pod(); (trig).kill_tav_kr = 5; }
					info_map_obj = "\nИз убитых монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";

				}
				else info_map_obj = "\nВам удалось покинуть бой!";
			}
			else if ((coord_x >= 6 && coord_x <= 8) && (coord_y >= 22 && coord_y <= 27) &&
				(((trig).kill_tav_kr == 2) || (trig.kill_tav_kr == 3))) {
				int level = rand() % ((trig).day + (trig).day / 2) + 1 + 2;
				monstr new_monstr(level, rand() % 2);
				if (print_fight(new_monstr)) {
					if ((trig).kill_tav_kr == 2) { current_location.make_map_tav_pod_4r_kr(); (trig).kill_tav_kr = 4; }
					else if ((trig).kill_tav_kr == 3) { current_location.make_map_tav_pod(); (trig).kill_tav_kr = 5; }
					info_map_obj = "\nИз убитых монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";

				}
				else info_map_obj = "\nВам удалось покинуть бой!";
			}
			else if (simvol_map == 'Џ') { info_map_obj = "\nСкладские ящики трактирщика"; }
			else if (coord_x == 8 && coord_y == 9) { info_map_obj = "\nДовольно большая нора"; }
			else if (coord_x == 8 && coord_y == 42) { info_map_obj = "\nВернутся в трактир"; }
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "taverna_2lv") {
			if ((coord_x == 4 && coord_y == 33) || (coord_x == 4 && coord_y == 34) || (coord_x == 6 && coord_y == 19) ||
				(coord_x == 7 && coord_y == 22) || (coord_x == 8 && coord_y == 19) ||
				(coord_x == 11 && coord_y == 20) || (coord_x == 11 && coord_y == 21)) {
				info_map_obj = "\nДверь в команту";
			}
			else if (simvol_map == '[' || simvol_map == ']') { info_map_obj = "\nМягкая кровать, что бы спать"; }
			else if (simvol_map == 'Ћ') { info_map_obj = "\nУдобный стул"; }
			else if (coord_x == 2 && coord_y == 20) {
				/*Возврат в таверну*/
				info_map_obj = "\nВернуться в таверну";
			}
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "dom_Matoi") {
			if (coord_x == 9 && coord_y == 15) { info_map_obj = "\nВернутся в город"; }
			else if ((coord_x >= 6 && coord_x <= 8) && (coord_y >= 22 && coord_y <= 28)) { EVENT.Q_plotnik(trig); info_map_obj = "\nПлотник Матой"; }
			else if (simvol_map == 'Ћ') { info_map_obj = "\nУдобный стул"; }
			else { info_map_obj = "\nДля передвижения используйте WASD или стрелки"; }
		}
		else if (name_map == "moi_dom") {
			if (simvol_map == '[' || simvol_map == ']') { info_map_obj = "\nЭто моя кровать"; }
			else if (simvol_map == 'Ћ') { info_map_obj = "\nЭто yдобный стул"; }
			else if (simvol_map == 'Џ') { info_map_obj = "\nСкладские ящики"; }
			else if (coord_x == 13 && coord_y == 29) {
				info_map_obj = "\nВернутся в город";
			}
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
	}

	

	/*********************/
	/* Действия на карте */
	/*********************/

	void enter_map_obj() {
		/*здесь будит осуществлятся выполнение дейтсивй*/ 
		if (name_map == "map_kolodec") {
			if (simvol_map == '®') {
				/*random_lamder() random_find() random_drop()*/
				backpack.random_find(info_map_obj);
				current_location.set_simvol_coord(coord_x, coord_y) = '`'; }
			else if (simvol_map == '&') {
				int level = rand() % (((trig).day + (trig).day/2)) + 1;
				monstr new_monstr(level, rand() % 2);
				print_fight(new_monstr);
				info_map_obj = "Из убитого монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";
				current_location.set_simvol_coord(coord_x, coord_y) = '`';
			}
			else if (simvol_map == 'Q') { current_location.set_simvol_coord(coord_x, coord_y) = '`'; info_map_obj = "\nВы сразились с королейвой крото-крысов"; }
			else if (coord_x == 3 && coord_y == 53) {
				n_coord_x = coord_x = 2; n_coord_y = coord_y = 54;
				current_location.make_map_gorod((trig).new_dom);;
				name_map = current_location.set_name_map();
				info_map_obj = "\nВы вернулись в город";
			}
		}
		else if (name_map == "map_les") {
			if (simvol_map == '®') {
				/*random_lamder() random_find() random_drop()*/
				backpack.random_find(info_map_obj);
				current_location.set_simvol_coord(coord_x, coord_y) = '`';
			}
			else if (simvol_map == '&') {
				int level = rand() % ((trig).day + (trig).day / 2) + 1;
				monstr new_monstr(level, rand() % 2);
				print_fight(new_monstr);
				info_map_obj = "Из убитого монстра получено " + to_string(backpack.random_drop(new_monstr.set_lvl())) + " предметов";
				current_location.set_simvol_coord(coord_x, coord_y) = '`';
			}
			else if (simvol_map == '¤') {
				if (backpack.random_lamder(info_map_obj)) {	current_location.set_simvol_coord(coord_x, coord_y) = '`';	}
			}
			else if (coord_x == 17 && coord_y == 57) {
				n_coord_x = coord_x = 11; n_coord_y = coord_y = 1;
				current_location.make_map_gorod((trig).new_dom);
				name_map = current_location.set_name_map();
				info_map_obj = "\nВы вернулись в город";
			}			
		}
		else if (name_map == "map_gorod") {
			if (coord_x == 11 && coord_y == 40) {
				/*ДОМ МАТОЙ*/
				if ((trig).acsses_plot) {
					n_coord_x = coord_x = 9; n_coord_y = coord_y = 16;
					current_location.make_dom_matoi();
					name_map = current_location.set_name_map();
				}
				else info_map_obj = "\nУ меня есть другие дела";
			}
			else if (coord_x == 17 && coord_y == 40) { info_map_obj = "\nНельзя входить в чужой дом без разрешения"; }
			else if (coord_x == 15 && coord_y == 23) {
				if ((trig).acsses_kuz) {
					coord_x = 13; coord_y = 43; n_coord_x = 13; n_coord_y = 43;
					current_location.make_map_kuznia();
					name_map = current_location.set_name_map();
				}
				else info_map_obj = "\nУ меня есть другие дела";
			}
			else if (coord_x == 8 && coord_y == 23) {
				if ((trig).acsses_trak) {
					n_coord_x = coord_x = 14; n_coord_y = coord_y = 29;
					current_location.make_map_taverna();
					name_map = current_location.set_name_map();
				}
				else info_map_obj = "\nУ меня есть другие дела";
			}
			else if (coord_x == 11 && coord_y == 0) {
				if ((trig).day > 1) {
					n_coord_x = coord_x = 17; n_coord_y = coord_y = 56;
					current_location.make_map_les();
					name_map = current_location.set_name_map();
					info_map_obj = "\nВы вошли в лес";
				}
				else info_map_obj = "\nУ меня есть другие дела!";
			}
			else if (coord_x == 1 && (coord_y >= 53 && coord_y <= 55)) {
				/*Колодец*/
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
							}/*Поставить королеву если еще существует*/
							name_map = current_location.set_name_map();
							info_map_obj = "\nВы спустились в колодец";
						}
						else info_map_obj = "\nЧто бы спустится вам нужна веревка";
					}
					else info_map_obj = "\nВ колодце уже нет воды";
				}
			}
			else if (coord_x == 13 && coord_y == 55 && !(trig).find_krepkai_palka) {
				/*Найдем крепкую палку на карте города*/
				info_map_obj = "\nПолучен предмет - \"Крепакая палка\"";
				item_Wep wep;
				wep.crw_0_palka();
				backpack.add_item(wep);
				(trig).find_krepkai_palka = 1;
			}
			else if (simvol_map == '#') { info_map_obj = "\nТут ничего нет"; }
			else if (coord_x == 6 && coord_y == 46) {
				if (!(trig).see_house) { EVENT.m0001_moi_dom(); (trig).see_house = 1; (trig).acsses_trak = 1; }
				if((trig).new_dom) {
				n_coord_x = coord_x = 13; n_coord_y = coord_y = 30;
				current_location.make_map_dom();
				name_map = current_location.set_name_map();
				}
				else	info_map_obj = "\nМой дом разрушен";			
			}
		}
		else if (name_map == "moi_dom") {
			if (simvol_map == '[' || simvol_map == ']') { 
				if (status.vinos < status.max_vinos - 100) {
					sleep_plaeer(); /*сон*/
					info_map_obj = "\nНаступил новый день! Вы востановили силы!";
				}
				else info_map_obj = "\nЯ уже хорошо выспался, и не могу сново лечь спать!"; }
			else if (simvol_map == 'Ћ') { info_map_obj = "\nДа это действительно yдобный стул"; }
			else if (simvol_map == 'Џ') { info_map_obj = "\nМои складские ящики"; }
			else if (coord_x == 13 && coord_y == 29) {
				n_coord_x = coord_x = 6; n_coord_y = coord_y = 47;
				current_location.make_map_gorod((trig).new_dom);
				name_map = current_location.set_name_map();
				info_map_obj = "\nЯ вернулся в город"; }
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "kuzn_Maika") {
			if (coord_x == 13 && coord_y == 44) {
				n_coord_x = coord_x = 15; n_coord_y = coord_y = 24;
				current_location.make_map_gorod((trig).new_dom);;
				name_map = current_location.set_name_map();
			}
			else if ((coord_x >= 11 && coord_x <= 14) && (coord_y >= 29 && coord_y <= 33)) {
				/*Магазин*/
				if ((trig).acsses_shop_kuz) {
					int val = say_NPC(1);
					if (val == 1) { print_shop_kuzna(1); }
					else if (val == 2) { print_sell(1); }
					info_map_obj = "\nПриходите еще!";
				}
				else info_map_obj = "\nПриходите завтра!";
			}
			else if (coord_x == 9 && coord_y == 19) {
				/*Подвал кузнеца*/
				if ((trig).find_krepkai_palka) {
					n_coord_x = coord_x = 9; n_coord_y = coord_y = 20;// n_coord_x = 10; n_coord_y = 19;
					if ((trig).kill_kroto_kris)	current_location.make_map_kuz_podval();
					else current_location.make_map_kuz_podval_qw();
					name_map = current_location.set_name_map();
				}
				else info_map_obj = "\nНужно найти на улице какое нибудь оружие!";
			}
			else if (simvol_map == '[' || simvol_map == ']') { info_map_obj = "\nНельзя спать в чужой кровати"; }
			else if (simvol_map == 'Ћ') { info_map_obj = "\nДа это действительно yдобный стул"; }
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "kuzn_podval") {
			if (coord_x == 9 && coord_y == 19) {
				n_coord_x = coord_x = 9; n_coord_y = coord_y = 20;
				current_location.make_map_kuznia();
				name_map = current_location.set_name_map();
			}			
			else if (simvol_map == 'Џ') { info_map_obj = "\nСкладские ящики кузница"; }
			else if (coord_x == 9 && coord_y == 33) {
				if ((trig).quest_find_ochag && !(trig).quest_find_ochag2) {
					(trig).quest_find_ochag2 = 1;
					(trig).detect_if();
					EVENT.m0011_info_kro_tav();
				}
				else info_map_obj = "\nПохоже через эту нору сюда пробрался крото-крыс"; }
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}

		else if (name_map == "taverna") {
			if (coord_x == 14 && coord_y == 30) {
				/*Возврат в город*/
				n_coord_x = coord_x = 8; n_coord_y = coord_y = 24;
				current_location.make_map_gorod((trig).new_dom);
				name_map = current_location.set_name_map();
			}
			else if (coord_x == 2 && coord_y == 20) {
				if ((trig).acsecc_sleep) {
					n_coord_x = coord_x = 2; n_coord_y = coord_y = 21;
					current_location.make_map_tavern_2lv();
					name_map = current_location.set_name_map();
					info_map_obj = "\nГостиничный этаж!";
				}
				else info_map_obj = "\nСначала нужно заплатить за гостиницу!";
			}
			else if (coord_x == 8 && coord_y == 42) {
				/*Спуск в подвал таверны*/
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
				else info_map_obj = "\nНельзя входить без разрешения";			
			}
			else if ((coord_x >= 5 && coord_x <= 9) && (coord_y >= 26 && coord_y <= 30)) {
				/*Разговор с тратктрищиком*/
				if ((trig).acsses_shop_tr) {
					/*Магазин*/
					int val = say_NPC(2);
					if (val == 1) { print_shop_kuzna(2); }
					else if (val == 2) { print_sell(2); }
					else if (val == 3) EVENT.m0109_taverna_gde_bablo();
					else if (val == 4) {
						if (!(trig).acsecc_sleep) {
							if (mani >= 90) {
								info_map_obj = "\nВот 90 монт за комнату!"; mani -= 90;
								(trig).acsecc_sleep = 1;
							}
							else info_map_obj = "\nУ меня недостаточно денег!";
						
						}
						else info_map_obj = "\nТы уже заплатл за комнату!";
					}
					else info_map_obj = "\nПриходите еще!";

					

				}
				else info_map_obj = "\nУ меня есть другие дела!";
			}
			else if (simvol_map == 'Џ') { info_map_obj = "\nНельзя брать чужие вещи"; }
			else if (simvol_map == 'Ћ') { info_map_obj = "\nДа это действительно Удобный стул"; }
			else if (coord_x == 6 && coord_y == 19) { info_map_obj = "\nИгра в Кости запускается, но это потом"; }
			else if (coord_x == 7 && coord_y == 13) { info_map_obj = "\nИгра - 21 Очко - то же потом"; }
			else if (coord_x == 3 && coord_y == 12) { info_map_obj = "\nИгра - Цифро-Бой пока только в проекте"; }
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		if (name_map == "taverna_2lv") {
			if ((coord_x == 4 && coord_y == 33) || (coord_x == 4 && coord_y == 34) ||
				(coord_x == 7 && coord_y == 22) || (coord_x == 8 && coord_y == 19) ||
				(coord_x == 11 && coord_y == 20) || (coord_x == 11 && coord_y == 21))
			{		info_map_obj = "\nНельзя войти в чужую комнату";}
			else if (simvol_map == '[' || simvol_map == ']') {
				if ((trig).acsecc_sleep) {
					sleep_plaeer(); /*сон*/
					info_map_obj = "\nНаступил новый день! Вы востановили силы!";
				}
				else info_map_obj = "\nЯ не могу спать в чужой постеле!";
			}
			else if (simvol_map == 'Ћ') { info_map_obj = "\nДа это действительно Удобный стул"; }
			else if (coord_x == 2 && coord_y == 20) {
				/*Возврат в таверну*/
				n_coord_x = coord_x = 2; n_coord_y = coord_y = 19;
				current_location.make_map_taverna();
				name_map = current_location.set_name_map();
				info_map_obj = "\nВернулись в таверну";
			}		
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		if (name_map == "taverna_pod") {
			if (coord_x == 8 && coord_y == 42) {
				/*Вернутся в таверну*/
				n_coord_x = coord_x = 8; n_coord_y = coord_y = 43;
				current_location.make_map_taverna();
				name_map = current_location.set_name_map();
			}			
			else if (simvol_map == 'Џ') { info_map_obj = "\nСкладские ящики трактирщика"; }
			else if (coord_x == 8 && coord_y == 9) {
				if ((trig).quest_find_ochag && !(trig).quest_find_ochag1) {
					(trig).quest_find_ochag1 = 1;
					(trig).detect_if();
					EVENT.m0012_info_kro_kuz();
				}
				else info_map_obj = "\nПохоже эта нара ведет к логову крыс. Маловата"; }			
			else info_map_obj = "\nДля передвижения используйте WASD или стрелки";
		}
		else if (name_map == "dom_Matoi") {
			if (coord_x == 9 && coord_y == 15) {
				/*ДОМ МАТОЙ*/
				n_coord_x = coord_x = 11; n_coord_y = coord_y = 39;
				current_location.make_map_gorod((trig).new_dom);
				name_map = current_location.set_name_map();
			}
			else if ((coord_x >= 6 && coord_x <= 8) && (coord_y >= 22 && coord_y <= 28)) {			
				int val;
				/*Магазин ПЛОТНИКА*/
				if ((trig).dom_postroen) val = say_NPC(4); //уберем купиле проджу после постройки
				else val = say_NPC(3);
				if (val == 1) { print_shop_kuzna(3); }
				else if (val == 2) { print_sell(3); }
				else if (val == 3) { 
					/*бревна*/
					if(!(trig).need_brevna){
						if (backpack.giv_brevna()) {
							(trig).count_brevna--;
							info_map_obj = "\nОтдал бревно! нужно еще " + to_string((trig).count_brevna);
							(trig).if_complate_dom();
						}
						else info_map_obj = "\nУ меня нет бревен! нужно еще " + to_string((trig).count_brevna);
					}
					else info_map_obj = "\nДля строительства больше не нужны бревна!";
				}
				else if (val == 4) {
					/*гвозди*/ 
					if (!(trig).need_bgbozdi) {
						if (backpack.giv_gvozdi()) {
							(trig).count_bgbozdi--;
							info_map_obj = "\nОтдал коробку! нужно еще " + to_string((trig).count_bgbozdi);
							(trig).if_complate_dom();
						}
						else info_map_obj = "\nУ меня нет коробки гвоздей! нужно еще " + to_string((trig).count_bgbozdi);
					}
					else info_map_obj = "\nДля строительства больше не нужны гвозди!";					
				}
				else info_map_obj = "\nПриходите еще!";
			}
			else if (simvol_map == 'Ћ') { info_map_obj = "\nДа это действительно Удобный стул"; }
			else {info_map_obj = "\nДля передвижения используйте WASD или стрелки";	}
		}
	}
};




