#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "RPG_zaxvat.cpp"
#include "RPG_item.cpp"


class monstr :public zaxvat {
protected:
	string name = "�����-����";
	int LvL = 1;
	int XP = 15;
	int ataka = 5;	
	/*����� ����*/
	//int xp_plaer = 0;
	int deff_plaer =0;
	int attak_plaer=0;

	vector <string> log_flight;
	bool pobeg = 1;
	bool end_light = 1; //��������� ���
	int krit = 1;
public:
	int set_lvl() { return LvL; }

	/*�������, ��� �� 0 �� 3*/
	monstr(int level, int tip) :LvL (level) {
		if (tip == 1) {
			name = "�����-����";			
			XP = 16, ataka = 8;
		}
		else if (tip == 0) {
			name = "������� �����-�����";
			XP = 8, ataka = 4;
		}
		else if (tip == 2) {
			name = "���� �����-���� ";
			XP = 24, ataka = 12;
		}
		else if (tip == 10) {
			name = "K������� �����������";
			XP = 100, ataka = 16;
		}
		ataka += (ataka / 10)*level;
		XP += (XP / 50)*level;
	}
	/*���������� � �������� �������� ���*/
	void monstr_info() {cout << "����� ���� \"" << name << "(" << LvL <<")\" ������: " << XP << " �����: " << ataka+2 << endl;}
	/*�������� ����, ��� �������������� ��������� (4-�����)*/
	void mnojitel_sil (int a) {
		ataka = (ataka / 4)*a;
		XP = (XP / 4)*a;
	}

	/*������� ���, ��������� ������ ������� ��� �������*/
	string fast_flight(int& xp, int deff, int attak){
		deff_plaer = deff;	attak_plaer = attak;
		while (XP >= 0 && xp >= 0) {
			/*��� ����*/
			XP -= rand() % 4 + attak_plaer;
			/*���� �������*/
			int yron = deff_plaer - rand() % 4 + ataka;
			if (yron < 0)xp += (1 + yron);
			else xp-= 1;
		}
		string temp;
		/*����� ���*/
		if (xp <= 0) {
			temp ="�� ���������!"; xp = 0;
		}
		else {
			temp = "�� ��������! ���� ��: " + xp;
		}
		menu_move_cord(); control_zero();
	}


	/*         �����               */
	bool print_flight(int& xp, int deff, int attak, bool& po) {
		
		//send_enter = 1;
		if (end_light) {
			//system("cls");

			monstr_info(); cout << "\n";
			center("��� ���!");
			cout << "��� ���!\n";
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

			if (end_light) menu_flight(); /*������������ ��� ��� ������� ente*/
			//send_enter = 0; /*��������� ������ 0*/
			return 1;
		}
		else {
			info_end_flight(xp);
			return 0;
		}
	}



	/*���� �����*/
	void menu_flight() {
		/*����*/
		//while (!send_enter) {	
			//system("cls");
			vector <string> menu = { "������� ����", "�����������","�������" };
			max_niz = 2;
			center("��������� ��������:");
			cout << "��������� ��������: \n\n";			
			for (int i = 0; i < 3; i++) {							
				center(menu.at(i));
				if (i == cur_element) videlenie_stroki(menu.at(i));
				else cout << menu.at(i);
				cout << endl;
			}
			menu_move_cord(); 
		//}
	}

	/*����������� �������� � �����*/
	bool flight_move(int& xp, int deff, int attak) {
		attak_plaer = attak-1, deff_plaer = deff;
		send_enter = 0;	
		
		krit += rand() % 5 + 1;
		int shanc = rand() % 80 + 20;
		if (cur_element == 0) {
			
			int you_attak = rand() % 2 + attak_plaer;
			/*��� ����*/
			if (shanc < krit) {
				XP -= (you_attak*2);
				log_flight.push_back("�� ������� " + to_string(you_attak*2) + " ����� (����), XP ���������� " + to_string(XP));
				krit = 1;
			}
			else {
				XP -= you_attak;
				log_flight.push_back("�� ������� " + to_string(you_attak) + " ����� (���� ����� " + to_string(krit) +  "%), XP ���������� " + to_string(XP));
			}
		
			
		
		
			/*���� �������*/
			int yron = deff_plaer - (rand() % 4 + ataka);
			//cout << yron << endl;
			if (yron >= 0) yron = -1;
			xp += yron;
			log_flight.push_back("�� �������� " + to_string(yron*(-1)) + " �����, ���� XP  " + to_string(xp));			
		}
		if (cur_element == 1) {
			int val = rand() % 50 + 50;
			if (val > krit) {
				krit += rand() % 30 + 20;
				log_flight.push_back("�� ������� �������������� ������! (���� ����� " + to_string(krit) + "%)");
				/*���� �������*/
				int yron = (deff_plaer * 3) - (rand() % 4 + ataka);
				if (yron > 0) yron = 0; /*���� ���� ������ ��� ��� ����� �� ���� ������� � ����*/
				xp += yron;
				log_flight.push_back("�� �������� " + to_string(yron*(-1)) + " �����, ���� XP  " + to_string(xp));
			}
			else { /*���� �������*/
				krit = 1;
				log_flight.push_back("�� ���������� � �������� ����! (���� ����� " + to_string(krit) + "%)");
				int yron = deff_plaer - (rand() % 4 + ataka);
				//cout << yron << endl;
				if (yron >= 0) yron = -1;
				xp += yron;
				log_flight.push_back("�� �������� " + to_string(yron*(-1)) + " �����, ���� XP  " + to_string(xp));

			}
		}	
		if (cur_element == 2) {
			/*� ��� � ��� �����*/
			/*��� �� ���� ������� �� �������� ������� ������ � ���������� ������*/
			//int val = rand() % 100;
			if (shanc < krit) pobeg = 0;
			else {
				/*���� ����� �� ������ �������� ������*/
				log_flight.push_back("��� �� ������� ��������� �����");
				//cout << "��� �� ������� ��������� �����\n";
				int yron = deff_plaer - rand() % 4 + ataka;
				if (yron >= 0) yron = -1; /*���� ���� ������ ��� ��� ����� �� ���� ������� � ����*/
				xp += yron;
				log_flight.push_back("�� �������� " + to_string(yron*(-1)) + " �����, ���� XP  " + to_string(xp));
			}
		}
		if (XP <= 0 || xp <= 0 || !pobeg) return 0;
		return 1;
	}

	/*���������� � ����� ���, ��������� �� ������*/
	void info_end_flight(int& xp){
				/*����� ���*/		
		if (!pobeg) {
			string temp = "��� ������� ��������� �����! ���� ��: " +to_string(xp);
			cout << "\n\n\n\n";
			center(temp);
			cout << temp << endl;
		}
		else if (xp <= 0) {
			string temp = "�� ���������!";
			cout << "\n\n\n\n";
			center(temp);
			cout << temp << endl;				
		}
		else {	
			string temp = "�� ��������! ���� ��: "  + to_string(xp);
			cout << "\n\n\n\n";
			center(temp);
			cout << temp << endl;			
		}	
		menu_move_cord(); control_zero();
	}
};