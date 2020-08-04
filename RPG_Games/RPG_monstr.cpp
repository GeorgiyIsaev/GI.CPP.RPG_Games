#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "RPG_zaxvat.cpp"
#include "RPG_item.cpp"


class monstr :public zaxvat {
protected:
	string name = "Крото-крыс";
	int LvL = 1;
	int XP = 15;
	int ataka = 5;	
	/*Плаер инфо*/
	//int xp_plaer = 0;
	int deff_plaer =0;
	int attak_plaer=0;

	vector <string> log_flight;
	bool pobeg = 1;
	bool end_light = 1; //состояние боя
	int krit = 1;
public:
	int set_lvl() { return LvL; }

	/*Уровень, тип от 0 до 3*/
	monstr(int level, int tip) :LvL (level) {
		if (tip == 1) {
			name = "Крото-крыс";			
			XP = 16, ataka = 8;
		}
		else if (tip == 0) {
			name = "Детеныш крото-крыса";
			XP = 8, ataka = 4;
		}
		else if (tip == 2) {
			name = "Воин Крото-крыс ";
			XP = 24, ataka = 12;
		}
		else if (tip == 10) {
			name = "Kоролева кротокрысов";
			XP = 100, ataka = 16;
		}
		ataka += (ataka / 10)*level;
		XP += (XP / 50)*level;
	}
	/*Информация о монстсре текущего боя*/
	void monstr_info() {cout << "Перед вами \"" << name << "(" << LvL <<")\" Жизней: " << XP << " Атака: " << ataka+2 << endl;}
	/*Множитль силы, для редактирования сложности (4-норма)*/
	void mnojitel_sil (int a) {
		ataka = (ataka / 4)*a;
		XP = (XP / 4)*a;
	}

	/*Быстрый бой, возвращет стринг строчку для вставки*/
	string fast_flight(int& xp, int deff, int attak){
		deff_plaer = deff;	attak_plaer = attak;
		while (XP >= 0 && xp >= 0) {
			/*Наш удар*/
			XP -= rand() % 4 + attak_plaer;
			/*Удар монстра*/
			int yron = deff_plaer - rand() % 4 + ataka;
			if (yron < 0)xp += (1 + yron);
			else xp-= 1;
		}
		string temp;
		/*Конец боя*/
		if (xp <= 0) {
			temp ="Вы проиграли!"; xp = 0;
		}
		else {
			temp = "Вы победили! Ваше ХП: " + xp;
		}
		menu_move_cord(); control_zero();
	}


	/*         БИТВА               */
	bool print_flight(int& xp, int deff, int attak, bool& po) {
		
		//send_enter = 1;
		if (end_light) {
			//system("cls");

			monstr_info(); cout << "\n";
			center("ЛОГ БОЯ!");
			cout << "ЛОГ БОЯ!\n";
			if(send_enter) end_light = flight_move(xp, deff, attak);
			po = pobeg;
			int mo_n = 7;			
			if (log_flight.size() >= 6) { 
				mo_n -= 2;
				center(*(log_flight.end() - 6));	cout << *(log_flight.end() - 6) << "\n";
				center(*(log_flight.end() - 5));	cout << *(log_flight.end() - 5) << "\n";			
			}
			if (log_flight.size() >= 4) { 
				mo_n -= 2;
				center(*(log_flight.end() - 4));	cout << *(log_flight.end() - 4) << "\n"; 
				center(*(log_flight.end() - 3));	cout << *(log_flight.end() - 3) << "\n";			
			}
			if (log_flight.size() >= 2) {
				mo_n -= 2;
				center(*(log_flight.end() - 2));	cout << *(log_flight.end() - 2) << "\n"; 
				center(*(log_flight.end() - 1));	cout << *(log_flight.end() - 1) << "\n";
			}
		
			while (mo_n--)cout << "\n";

			if (end_light) menu_flight(); /*пробрасывает кур при нажатии ente*/
			//send_enter = 0; /*возвращем ентеру 0*/
			return 1;
		}
		else {
			info_end_flight(xp);
			return 0;
		}
	}



	/*МЕНЮ БИТВЫ*/
	void menu_flight() {
		/*МЕНЮ*/
		//while (!send_enter) {	
			//system("cls");
			vector <string> menu = { "Нанести Удар", "Блокировать","Сбежать" };
			max_niz = 2;
			center("Доступные действия:");
			cout << "Доступные действия: \n\n";			
			for (int i = 0; i < 3; i++) {							
				center(menu.at(i));
				if (i == cur_element) videlenie_stroki(menu.at(i));
				else cout << menu.at(i);
				cout << endl;
			}
			menu_move_cord(); 
		//}
	}

	/*Выполняемое Действие в битве*/
	bool flight_move(int& xp, int deff, int attak) {
		attak_plaer = attak-1, deff_plaer = deff;
		send_enter = 0;	
		
		krit += rand() % 5 + 1;
		int shanc = rand() % 80 + 20;
		if (cur_element == 0) {
			
			int you_attak = rand() % 2 + attak_plaer;
			/*Наш удар*/
			if (shanc < krit) {
				XP -= (you_attak*2);
				log_flight.push_back("Вы нанесли " + to_string(you_attak*2) + " урона (КРИТ), XP противкнка " + to_string(XP));
				krit = 1;
			}
			else {
				XP -= you_attak;
				log_flight.push_back("Вы нанесли " + to_string(you_attak) + " урона (шанс крита " + to_string(krit) +  "%), XP противкнка " + to_string(XP));
			}
		
			
		
		
			/*Удар монстра*/
			int yron = deff_plaer - (rand() % 4 + ataka);
			//cout << yron << endl;
			if (yron >= 0) yron = -1;
			xp += yron;
			log_flight.push_back("Вы получили " + to_string(yron*(-1)) + " урона, Ваше XP  " + to_string(xp));			
		}
		if (cur_element == 1) {
			int val = rand() % 50 + 50;
			if (val > krit) {
				krit += rand() % 30 + 20;
				log_flight.push_back("Вы приняли оборонительную стойку! (шанс крита " + to_string(krit) + "%)");
				/*Удар монстра*/
				int yron = (deff_plaer * 3) - (rand() % 4 + ataka);
				if (yron > 0) yron = 0; /*Если урон меньше чем три брони то урон проходи в ноль*/
				xp += yron;
				log_flight.push_back("Вы получили " + to_string(yron*(-1)) + " урона, Ваше XP  " + to_string(xp));
			}
			else { /*Удар монстра*/
				krit = 1;
				log_flight.push_back("Вы отвлеклись и получили удар! (шанс крита " + to_string(krit) + "%)");
				int yron = deff_plaer - (rand() % 4 + ataka);
				//cout << yron << endl;
				if (yron >= 0) yron = -1;
				xp += yron;
				log_flight.push_back("Вы получили " + to_string(yron*(-1)) + " урона, Ваше XP  " + to_string(xp));

			}
		}	
		if (cur_element == 2) {
			/*а тут у нас побег*/
			/*что бы жизь сахором не казалось добавим рандом в успешность побега*/
			//int val = rand() % 100;
			if (shanc < krit) pobeg = 0;
			else {
				/*Если побег не успешн поулчаем уроном*/
				log_flight.push_back("Вам не удалось совершить побег");
				//cout << "Вам не удалось совершить побег\n";
				int yron = deff_plaer - rand() % 4 + ataka;
				if (yron >= 0) yron = -1; /*Если урон меньше чем три брони то урон проходи в ноль*/
				xp += yron;
				log_flight.push_back("Вы получили " + to_string(yron*(-1)) + " урона, Ваше XP  " + to_string(xp));
			}
		}
		if (XP <= 0 || xp <= 0 || !pobeg) return 0;
		return 1;
	}

	/*Информация о конце боя, принимает хп игрока*/
	void info_end_flight(int& xp){
				/*Конец боя*/		
		if (!pobeg) {
			string temp = "Вам удалось совершить побег! Ваше ХП: " +to_string(xp);
			cout << "\n\n\n\n";
			center(temp);
			cout << temp << endl;
		}
		else if (xp <= 0) {
			string temp = "Вы проиграли!";
			cout << "\n\n\n\n";
			center(temp);
			cout << temp << endl;				
		}
		else {	
			string temp = "Вы победили! Ваше ХП: "  + to_string(xp);
			cout << "\n\n\n\n";
			center(temp);
			cout << temp << endl;			
		}	
		menu_move_cord(); control_zero();
	}
};