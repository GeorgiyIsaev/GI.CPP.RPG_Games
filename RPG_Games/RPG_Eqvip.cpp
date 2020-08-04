#pragma once
#include <iostream>
#include <string>

#include "RPG_zaxvat.cpp"
#include "RPG_item.cpp"

using namespace std;

/*����� ���������� */
class equipment :public zaxvat {
protected:	

	/*������ � ������*/
	
	/*������ � �����������*/
	int atka_base = 1;	int atka_eq = 0;	int atka_bones = 0; int atka_full = 0;
	int deff_base = 1;	int deff_eq = 0;	int deff_bones = 0; int deff_full = 0;
	/*������������� ��������*/
	bool item_eq_if[5] = { 0,0,0,0,0 };
	item_Wep weopon_eq;		
	item_Def def_head_eq; /*������*/	
	item_Def def_body_eq; /*����*/	
	item_Def def_legs_eq; /*����*/	
	item_Def def_arms_eq; /*����*/
	string menu_eqvip[5] = { "�����","�����", "�����", "�����" ,"�����" };
	string menu_eqvip_if[5] = { "������:\n","������:\n", "����:\n", "����:\n" ,"����:\n" };
	/*������ ��������� ������*/	
public:
	int& set_full_attak() {
		atka_full = atka_base + atka_eq + atka_bones;
		return atka_full;
	}
	int& set_full_deff() {
		deff_full = deff_base + deff_eq + deff_bones;
		return deff_full;
	}

	/*"�������� - ����� ���������*/
	int val_un_put_item = -1;
	bool& acssec_equp() { return send_c; }
	

	void print_eqvip_ststus(bool& new_day) {
		if (new_day) { atka_bones = 0; deff_bones = 0; new_day = 0; }
		atka_full = atka_base + atka_eq + atka_bones;
		deff_full = deff_base + deff_eq + deff_bones;
		
		cout << "������: ";
		videlenie_stroki_RED(to_string(atka_full), 2);			
		cout << " = " << atka_base << "(�������) + " << atka_eq << "(����������) + " << atka_bones << "(�����);" << endl;

		cout << "������: ";
		videlenie_stroki_RED(to_string(deff_full), 2);
		cout << " = " << deff_base << "(�������) + " << deff_eq << "(����������) + " << deff_bones << "(�����);" << endl;
			
	}
	int set_eq_attka() {return atka_eq;}
	int set_eq_deff() { return deff_eq; }
	int& set_base_attka() { return atka_base; }
	int& set_base_deff() { return deff_base; }

	/* ������� �������� ������*/
	void put_eq(const item_Wep& tmpWep){
		if (!item_eq_if[0]) {
			/*��������� ��������*/
			weopon_eq = tmpWep;	item_eq_if[0] = 1;
			/*�������� ����� �� ����������*/
			atka_eq = weopon_eq.set_attak();
			menu_eqvip[0] = weopon_eq.set_str_item();
			max_niz--;
		}
	}
	/* ������� �������� �����*/
	void put_eq(item_Def& tmpDeff) {
		/*��������� ��� ������*/	
		if (tmpDeff.set_type_def() == 1) {
			/*��������� ��������*/
			def_head_eq = tmpDeff;	item_eq_if[1] = 1;
			/*�������� ����� �� ����������*/
			deff_eq += tmpDeff.set_deff();
			menu_eqvip[1] = tmpDeff.set_str_item();
			max_niz--;
		}
		else if (tmpDeff.set_type_def() == 2) {
			/*��������� ��������*/
			def_body_eq = tmpDeff;	item_eq_if[2] = 1;
			/*�������� ����� �� ����������*/
			deff_eq += tmpDeff.set_deff();
			menu_eqvip[2] = tmpDeff.set_str_item();
			max_niz--;
		}
		else if (tmpDeff.set_type_def() == 3) {
			/*��������� ��������*/
			def_legs_eq	= tmpDeff;	item_eq_if[3] = 1;
			/*�������� ����� �� ����������*/
			deff_eq += tmpDeff.set_deff();
			menu_eqvip[3] = tmpDeff.set_str_item();
			max_niz--;
		}
		else if (tmpDeff.set_type_def() == 4) {
			/*��������� ��������*/
			def_arms_eq = tmpDeff;	item_eq_if[4] = 1;
			/*�������� ����� �� ����������*/
			deff_eq += tmpDeff.set_deff();
			menu_eqvip[4] = tmpDeff.set_str_item();
			max_niz--;
		}	
	}
};