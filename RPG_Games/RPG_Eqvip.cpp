#pragma once
#include <iostream>
#include <string>

#include "RPG_zaxvat.cpp"
#include "RPG_item.cpp"

using namespace std;

/*Класс экипировки */
class equipment :public zaxvat {
protected:	

	/*Доступ к эквипу*/
	
	/*Статут с экипировкой*/
	int atka_base = 1;	int atka_eq = 0;	int atka_bones = 0; int atka_full = 0;
	int deff_base = 1;	int deff_eq = 0;	int deff_bones = 0; int deff_full = 0;
	/*Экипированные предметы*/
	bool item_eq_if[5] = { 0,0,0,0,0 };
	item_Wep weopon_eq;		
	item_Def def_head_eq; /*Голова*/	
	item_Def def_body_eq; /*Тело*/	
	item_Def def_legs_eq; /*Ноги*/	
	item_Def def_arms_eq; /*Руки*/
	string menu_eqvip[5] = { "ПУСТО","ПУСТО", "ПУСТО", "ПУСТО" ,"ПУСТО" };
	string menu_eqvip_if[5] = { "Оружие:\n","Голова:\n", "Тело:\n", "Ноги:\n" ,"Руки:\n" };
	/*Запуск процедуры снятия*/	
public:
	int& set_full_attak() {
		atka_full = atka_base + atka_eq + atka_bones;
		return atka_full;
	}
	int& set_full_deff() {
		deff_full = deff_base + deff_eq + deff_bones;
		return deff_full;
	}

	/*"Экипирка - номер снимаемой*/
	int val_un_put_item = -1;
	bool& acssec_equp() { return send_c; }
	

	void print_eqvip_ststus(bool& new_day) {
		if (new_day) { atka_bones = 0; deff_bones = 0; new_day = 0; }
		atka_full = atka_base + atka_eq + atka_bones;
		deff_full = deff_base + deff_eq + deff_bones;
		
		cout << "АТАТКА: ";
		videlenie_stroki_RED(to_string(atka_full), 2);			
		cout << " = " << atka_base << "(базовая) + " << atka_eq << "(экипировка) + " << atka_bones << "(бонус);" << endl;

		cout << "ЗАЩИТА: ";
		videlenie_stroki_RED(to_string(deff_full), 2);
		cout << " = " << deff_base << "(базовая) + " << deff_eq << "(экипировка) + " << deff_bones << "(бонус);" << endl;
			
	}
	int set_eq_attka() {return atka_eq;}
	int set_eq_deff() { return deff_eq; }
	int& set_base_attka() { return atka_base; }
	int& set_base_deff() { return deff_base; }

	/* Надевам предметы оружия*/
	void put_eq(const item_Wep& tmpWep){
		if (!item_eq_if[0]) {
			/*Фискируем одевание*/
			weopon_eq = tmpWep;	item_eq_if[0] = 1;
			/*Изменяем атаку на актуальную*/
			atka_eq = weopon_eq.set_attak();
			menu_eqvip[0] = weopon_eq.set_str_item();
			max_niz--;
		}
	}
	/* Надевам предметы брони*/
	void put_eq(item_Def& tmpDeff) {
		/*Проверяем тип шмотки*/	
		if (tmpDeff.set_type_def() == 1) {
			/*Фискируем одевание*/
			def_head_eq = tmpDeff;	item_eq_if[1] = 1;
			/*Изменяем атаку на актуальную*/
			deff_eq += tmpDeff.set_deff();
			menu_eqvip[1] = tmpDeff.set_str_item();
			max_niz--;
		}
		else if (tmpDeff.set_type_def() == 2) {
			/*Фискируем одевание*/
			def_body_eq = tmpDeff;	item_eq_if[2] = 1;
			/*Изменяем атаку на актуальную*/
			deff_eq += tmpDeff.set_deff();
			menu_eqvip[2] = tmpDeff.set_str_item();
			max_niz--;
		}
		else if (tmpDeff.set_type_def() == 3) {
			/*Фискируем одевание*/
			def_legs_eq	= tmpDeff;	item_eq_if[3] = 1;
			/*Изменяем атаку на актуальную*/
			deff_eq += tmpDeff.set_deff();
			menu_eqvip[3] = tmpDeff.set_str_item();
			max_niz--;
		}
		else if (tmpDeff.set_type_def() == 4) {
			/*Фискируем одевание*/
			def_arms_eq = tmpDeff;	item_eq_if[4] = 1;
			/*Изменяем атаку на актуальную*/
			deff_eq += tmpDeff.set_deff();
			menu_eqvip[4] = tmpDeff.set_str_item();
			max_niz--;
		}	
	}
};