#pragma once
#include <iostream>
#include <string>
#include <conio.h> //��� _getch();
#include <Windows.h> //��� �����
#include "RPG_item.cpp"
#include "RPG_zaxvat.cpp"
#include "vector"
#include "algorithm"
//#include "RPG_Eqvip.cpp"
//#include <functional>  /*������ ����� �� �������*/
#include "RPG_Eqvip.cpp"
using namespace std; ;



class inventar :public equipment /*, protected zaxvat*/ {
	/*���������� � ����� ��� �������� ��� ���� ������, �� ����� �������, �� ��� ��� ��� �����, ��� ����������� ����� �����*/
	/*vector <item*> inv_items;*/ /*��������� ������� �������� ���������, �� � ����� ���...*/
	
	/*����� ������ �� �����������*/
	vector <item_Wep> vec_item_Wep;
	vector <item_Def> vec_item_Def;
	vector <item_Use> vec_item_Use;
	vector <item_No_Use> vec_item_No_Use;
	int cur_item_val = 0;
	int max_item_val =0; // ��� ������ � �����

	string info_event = "";
	string info_eq = "\n����� ������� (Enter)\n";
	//equipment eqvip;

	/*������� �������*/
	vector <item_Wep> vec_shop_kuz_w;
	vector <item_Def> vec_shop_kuz_d;
	vector <item_No_Use> vec_shop_kuz_it;
	/*������� �����������*/	
	vector <item_Def> vec_shop_tav_d;
	vector <item_Use> vec_shop_tav_u;
	/*������� ��������*/
	vector <item_Use> vec_shop_pl_u;
	vector <item_No_Use> vec_shop_pl_n;

	void sotr_pac() {
		auto pr = [&](auto& tmp, auto& tmp2) {
			if (tmp.set_many_buy() > tmp2.set_many_buy()) return true;
			else return false;		
		};
		sort(vec_item_Wep.begin(), vec_item_Wep.end(), pr);
		sort(vec_item_Def.begin(), vec_item_Def.end(), pr);
		sort(vec_item_Use.begin(), vec_item_Use.end(), pr);
		sort(vec_item_No_Use.begin(), vec_item_No_Use.end(), pr);

		sort(vec_shop_kuz_d.begin(), vec_shop_kuz_d.end(), pr);
		sort(vec_shop_kuz_w.begin(), vec_shop_kuz_w.end(), pr);
		sort(vec_shop_kuz_it.begin(), vec_shop_kuz_it.end(), pr);

		sort(vec_shop_tav_d.begin(), vec_shop_tav_d.end(), pr);
		sort(vec_shop_tav_u.begin(), vec_shop_tav_u.end(), pr);

	
		sort(vec_shop_pl_u.begin(), vec_shop_pl_u.end(), pr);
		sort(vec_shop_pl_n.begin(), vec_shop_pl_n.end(), pr);
	}

public:	
	
	/*�������� �������*/
	bool& accsec_invent(){ return send_inventar; }
	inventar() {/*���� �������� ����������*/ /*test_zapolnenie();*/ 	zapolnenie_kuz(); }

	/*���������� ��������� 4 ����������*/
	void add_item(item_Wep& predmet) { vec_item_Wep.push_back(predmet); sotr_pac(); max_item_val++; }
	void add_item(item_Def& predmet) {vec_item_Def.push_back(predmet); sotr_pac();  max_item_val++;}
	void add_item(item_Use& predmet) {vec_item_Use.push_back(predmet); sotr_pac();  max_item_val++;}
	void add_item(item_No_Use& predmet) {vec_item_No_Use.push_back(predmet); sotr_pac(); max_item_val++;	}
	
	/*������ ������ �� ��������� �������� �����*/
	void un_put_actual() {
		send_enter = 0;
		if (val_un_put_item == 0) {
			/*��� �������� �� ������ ������*/
			if(item_eq_if[0]) add_item(weopon_eq);
			/*��������� ������*/
			item_eq_if[0] = 0; val_un_put_item = -1;
			/*�������� ����� �� ����������*/
			atka_eq = 0;
			menu_eqvip[0] = "�����";
			/*���������� ������ ������ � ������*/
		
		}	

		/*!!!!  ��� ����� ����������, ��� �� ��� �� ����� ��������, ������� ��� �������� � ������ ��� ������. �� ��� ����� ���� ����� �����*/

		/*C���� ������ ���� �� �����*/	
		else if (val_un_put_item == 1) {
			if (item_eq_if[1]) {
				add_item(def_head_eq);
				item_eq_if[1] = 0;	 val_un_put_item = -1;
				deff_eq -= def_head_eq.set_deff();
				menu_eqvip[1] = "�����";
			}
		}
		else if (val_un_put_item == 2) {
			if (item_eq_if[2]) {
				add_item(def_body_eq);
				item_eq_if[2] = 0; val_un_put_item = -1;
				deff_eq -= def_body_eq.set_deff();
				menu_eqvip[2] = "�����";
			}
		}
		else if (val_un_put_item == 3) {
			if (item_eq_if[3]) {
				add_item(def_legs_eq);
				item_eq_if[3] = 0; val_un_put_item = -1;
				deff_eq -= def_legs_eq.set_deff();
				menu_eqvip[3] = "�����";
			}
		}
		else if (val_un_put_item == 4 ) {
			if (item_eq_if[4]) {
				add_item(def_arms_eq);
				item_eq_if[4] = 0; val_un_put_item = -1;
				deff_eq -= def_arms_eq.set_deff();
				menu_eqvip[4] = "�����";
			}
		}
	}

	/*������ �������� ���������*/
	void print_eqvip() {
		max_niz = 4; //cur_element = 0;
		
		cout << "����������:\n\n";
		for (int i = 0; i < 5; i++) {
			cout << " - - " << menu_eqvip_if[i];
			if (i == cur_element) videlenie_stroki(menu_eqvip[i]);
			else	cout << menu_eqvip[i];
			cout << endl;

		}	
		cout << info_eq; info_eq = "\n����� ������� (Enter)\n";
		menu_move_cord(); /*������������ �� ���� ����������*/
		if (send_enter) {
			val_un_put_item = cur_element;
			un_put_actual();
			info_eq = "\n������� ����"; 
			send_enter = 0;
		}
	}



	/*������ �������� ���������*/
	void ptint_inventar(status& st) {		
		sotr_pac();
		max_niz = max_item_val-1; /*�������� ������!!!*/
		
		if(send_enter) enter_inventar(type_cur_item(cur_element), st); /*��������� �������� � ���������*/

		/*��������� ���������*/
		if (max_item_val)	cout << "	���������: " << cur_element+1 << "/"<< max_item_val <<" ���. " << (str_begin/10)+1 <<"\n\n";
		else cout << "	���������: " << cur_element << "/" << max_item_val << " ���. " << (str_begin / 10) + 1 << "\n\n";
		/*������� ��� ������� �� �����������*/
		int count = 0; /*����� � ��������������� ��-��*/
		auto pr = [&](auto& tmp) {
			if (count >= str_begin && count < str_end) {
			//if (str_begin<= count && str_end> count) {
				if (count == cur_element) videlenie_stroki(tmp.set_str_item());
				else cout << tmp.set_str_item(); 
				cout << endl;
				//cout << count << endl;
			}			
			count++;
		};		
		for_each(vec_item_Wep.begin(), vec_item_Wep.end(), pr);			
		for_each(vec_item_Def.begin(), vec_item_Def.end(), pr);			
		for_each(vec_item_Use.begin(), vec_item_Use.end(), pr);		
		for_each(vec_item_No_Use.begin(), vec_item_No_Use.end(), pr);		


		/*������� ���������� � ��������*/
		cout << "\n";	info_stroka(type_cur_item(cur_element));	
		/*������� ���������� � ���������� ��������*/
		cout << "\n";   cout << info_event << endl; info_event = "";
		
		/*������� ��� �� ����*/
		menu_move_cord();		
	}

	/*����� ���������� ��� �������� ����������, ����� ����������� cur_item_val*/
	int type_cur_item(int val_item) {	
		if (cur_element < vec_item_Wep.size()) { 
			/*cur_item_val - ����� ����� � ������� ����������*/
			cur_item_val = cur_element; return 1;
		}
		else if (cur_element < vec_item_Wep.size() + vec_item_Def.size()) {  
			cur_item_val = cur_element - vec_item_Wep.size(); return 2;
		}
		else if (cur_element < vec_item_Wep.size() + vec_item_Def.size() + vec_item_Use.size()) {
			cur_item_val = cur_element - (vec_item_Wep.size() + vec_item_Def.size()); return 3;
		}
		else if (cur_element < vec_item_Wep.size() + vec_item_Def.size() + vec_item_Use.size() + vec_item_No_Use.size()) {
			cur_item_val = cur_element - (vec_item_Wep.size() + vec_item_Def.size() + vec_item_Use.size()); return 4;
		}
		/*� ��� ���� ����� ����������, � ����� ����� ��-��, ��� ����� ����� � ���������� ����������*/
	}



	/*������� �������� �������������� ��������*/
	//void info_stroka_eq(int typ_item) {
	//	if (item_eq_if[0])		{cout << weopon_eq.set_info_str() << endl;	}
	//	else if (item_eq_if[1] || item_eq_if[2] || item_eq_if[3] || item_eq_if[4]) {
	//		//cout << vec_item_Def.at(cur_item_val).set_info_str() << endl;
	//	}
	//}
	   
	/*������� ������ � ��������� ��������� ��������*/
	void info_stroka(int typ_item) {		
		if (typ_item == 1) { cout << vec_item_Wep.at(cur_item_val).set_info_str() << endl; }
		else if (typ_item == 2) { cout << vec_item_Def.at(cur_item_val).set_info_str() << endl; }
		else if (typ_item == 3) cout << vec_item_Use.at(cur_item_val).set_info_str() << endl;
		else if (typ_item == 4) cout << vec_item_No_Use.at(cur_item_val).set_info_str() << endl;	
	}
	/*������� ������ � ���������� � �������, �������� ��� �������� � ����� �������� ���*/
	void sell_or_not_sell(int typ_item, int NPC_val) {
		if (typ_item == 1 && vec_item_Wep.at(cur_item_val).set_skupshik() == NPC_val) {
			cout << "� ����� ���� ������� �� " << vec_item_Wep.at(cur_item_val).set_many_buy() / 2 << " �����." << endl;
		}
		else if (typ_item == 2 && vec_item_Def.at(cur_item_val).set_skupshik() == NPC_val) {
			cout << "� ����� ���� ������� �� " << vec_item_Def.at(cur_item_val).set_many_buy() / 2 << " �����." << endl;
		}
		else if (typ_item == 3 && vec_item_Use.at(cur_item_val).set_skupshik() == NPC_val) {
			cout << "� ����� ���� ������� �� " << vec_item_Use.at(cur_item_val).set_many_buy() / 2 << " �����." << endl;
		}
		else if (typ_item == 4 && vec_item_No_Use.at(cur_item_val).set_skupshik() == NPC_val) {
			cout << "� ����� ���� ������� �� " << vec_item_No_Use.at(cur_item_val).set_many_buy() / 2 << " �����." << endl;
		}
		else { cout << "���� ������� ���� �� ���������� " << endl; }
	}

	/*������� ������� �� ���������*/
	void enter_inventar(int typ_item, status& st){
		send_enter = 0; /*����� ���������� ��������� ������� enter � 0*/
		/*��������� � ��� �������� ��������*/
		if (typ_item == 1) {
			/*�������� ��������� ���������, ���� ���� ���������� � ������*/
			if (item_eq_if[0]) {
				val_un_put_item = 0;/*��� �������*/
				un_put_actual(); /*���������� ������ ���� � ������*/
			}
			/*�������� �����*/
			put_eq(vec_item_Wep.at(cur_item_val));
			/*������� ������� �� ����*/
			//remove(vec_item_Wep.begin(), vec_item_Wep.end(), vec_item_Wep.at(cur_item_val));
			info_event = "������� \"" + (*(vec_item_Wep.begin() + cur_item_val)).set_name_item() + "\" ��������!";
			vec_item_Wep.erase(vec_item_Wep.begin() + cur_item_val); max_item_val--;
			//vec_item_Def.erase(vec_item_Wep.end()-1);				
		}
		else if (typ_item == 2) {
			/*�������� ��������� ���������, ���� ���� ���������� � ������*/
			vec_item_Def.at(cur_item_val).set_type_def();
			if ((vec_item_Def.at(cur_item_val).set_type_def() == 1) && item_eq_if[1]) {
				val_un_put_item = 1;
				un_put_actual(); /*���������� ������ ���� � ������*/
			}
			if ((vec_item_Def.at(cur_item_val).set_type_def() == 2) && item_eq_if[2]) {
				val_un_put_item = 2;
				un_put_actual(); /*���������� ������ ���� � ������*/
			}
			if ((vec_item_Def.at(cur_item_val).set_type_def() == 3) && item_eq_if[3]) {
				val_un_put_item = 3;
				un_put_actual(); /*���������� ������ ���� � ������*/
			}
			if ((vec_item_Def.at(cur_item_val).set_type_def() == 4) && item_eq_if[4]) {
				val_un_put_item = 4;
				un_put_actual(); /*���������� ������ ���� � ������*/
			}
			/*�������� �����*/
			put_eq(vec_item_Def.at(cur_item_val));
			/*������� ������� �� ����*/	
			info_event = "������� \"" + (*(vec_item_Def.begin() + cur_item_val)).set_name_item() + "\" ��������!";
			vec_item_Def.erase(vec_item_Def.begin() + cur_item_val);	max_item_val--;						
		}
		else if (typ_item == 3) {
			/*������������ ��������*/
			st += (*(vec_item_Use.begin() + cur_item_val)).set_status();
			if((*(vec_item_Use.begin() + cur_item_val)).set_atk_bon()>0)	atka_bones=(*(vec_item_Use.begin() + cur_item_val)).set_atk_bon(); /*�������� ������� ����� �� �����*/
			if ((*(vec_item_Use.begin() + cur_item_val)).set_def_bon() > 0)	deff_bones=(*(vec_item_Use.begin() + cur_item_val)).set_def_bon();
			/*��������� ������*/
			set_full_attak(); set_full_deff();
			/*������� ������� �� ����*/
			info_event = "������� \"" + (*(vec_item_Use.begin() + cur_item_val)).set_name_item() + "\" �����������!";
			vec_item_Use.erase(vec_item_Use.begin() + cur_item_val); max_item_val--;
		}
		
		/*���� �������� ����������� ��������� ��������� cur_element*/
		if (cur_element % 10 == 0 && cur_element >= 10) { str_begin -= 10; str_end -= 10; } /*�������� ��������*/
		if (cur_element) { var_cur_element--; cur_element--; } //������ ��� ����� ���� ��-� �� �������	
	}



	/*������� ������� �� ��������� (���, ���, &������)*/
	void enter_sell(int typ_item, int NPC_val, int& mani) {
		send_enter = 0; /*���������� ����� � ����*/
		/*��������� � ��� �������� ��������, � ����� �� ��� ��� ������*/
		if (typ_item == 1 && vec_item_Wep.at(cur_item_val).set_skupshik() == NPC_val) {
			/*���� ��? ��������� �� ���� �����*/
			mani += vec_item_Wep.at(cur_item_val).set_many_buy() / 2;		
			/*���������� ����������*/
			info_event = "������� \"" + (*(vec_item_Wep.begin() + cur_item_val)).set_name_item() + "\" ������ �� " + to_string(vec_item_Wep.at(cur_item_val).set_many_buy() / 2) + " �����!";
			/*������� ������� �� ���������*/
			vec_item_Wep.erase(vec_item_Wep.begin() + cur_item_val); max_item_val--;			
		}
		else if (typ_item == 2 && vec_item_Def.at(cur_item_val).set_skupshik() == NPC_val) {
			mani += vec_item_Def.at(cur_item_val).set_many_buy() / 2;
			info_event = "������� \"" + (*(vec_item_Def.begin() + cur_item_val)).set_name_item() + "\" ������ �� " + to_string(vec_item_Def.at(cur_item_val).set_many_buy() / 2) + " �����!";
			vec_item_Def.erase(vec_item_Def.begin() + cur_item_val); max_item_val--;
		}
		else if (typ_item == 3 && vec_item_Use.at(cur_item_val).set_skupshik() == NPC_val) {
			mani += vec_item_Use.at(cur_item_val).set_many_buy() / 2;
			info_event = "������� \"" + (*(vec_item_Use.begin() + cur_item_val)).set_name_item() + "\" ������ �� " + to_string(vec_item_Use.at(cur_item_val).set_many_buy() / 2) + " �����!";
			vec_item_Use.erase(vec_item_Use.begin() + cur_item_val); max_item_val--;
		}
		else if (typ_item == 4 && vec_item_No_Use.at(cur_item_val).set_skupshik() == NPC_val) {
			mani += vec_item_No_Use.at(cur_item_val).set_many_buy() / 2;
			info_event = "������� \"" + (*(vec_item_No_Use.begin() + cur_item_val)).set_name_item() + "\" ������ �� " + to_string(vec_item_No_Use.at(cur_item_val).set_many_buy() / 2) + " �����!";
			vec_item_No_Use.erase(vec_item_No_Use.begin() + cur_item_val); max_item_val--;
		
		}
		else { info_event = "��� �������, ��� ��� �� �����!"; return; }
		
		/*���� �������� ����������� ��������� ��������� cur_element*/
		if (cur_element % 10==0 && cur_element >= 10) { str_begin -= 10; str_end -= 10;} /*�������� ��������*/
		if (cur_element) {var_cur_element--; cur_element--;} //������ ��� ����� ���� ��-� �� �������		
	}


	/*���� �������� � ��� ��������� ����������, �������� �������� �������, � ����� ���(�� ��������� 0)*/
	bool say_NPC(int& what, int val_NPC) {	
		what = 0;
		vector<string> m = { "������", "�������" };
		/*����� ��� ����� ������������ ��� ��� ������� � ���������*/
		if (val_NPC == 2) {
			m.push_back("��� ����� ������?");
			m.push_back("����� ������� �� ���� (90 �����)!");
		}		
		if (val_NPC == 3) {
			m.push_back("������ ������");
			m.push_back("������ ������� �������?");
		}	
			
		max_niz = m.size() -1;
		for (int i = 0; i < m.size(); i++) {
			center(m[i]);
			if (i == cur_element) videlenie_stroki(m[i]);
			else cout << m[i];
			cout << endl;
		}
		menu_move_cord();
		if (send_esc) { control_zero(); return 0; }
		if (send_enter) { send_enter = 0; what = cur_element + 1; control_zero(); return 0; }
	}

	/*������ ������� ��������, ��������� ����� ���, � ������*/
	bool sell_inventar(int nomer_NPC, int& mani) {
		//max_item_val = 
		sotr_pac();
		max_niz = max_item_val-1; /*�������� ������!!!*/

		/*��������� ���������*/
		if (max_item_val)	cout << "	���������: " << cur_element + 1 << "/" << max_item_val << " ���. " << (str_begin / 10) + 1 << "\n\n";
		else cout << "	���������: " << cur_element << "/" << max_item_val << " ���. " << (str_begin / 10) + 1 << "\n\n";
		/*������� ��� ������� �� �����������*/
		int count = 0; /*����� � ��������������� ��-��*/
		auto pr = [&](auto& tmp) {
			if (count >= str_begin && count < str_end) {
				//if (str_begin<= count && str_end> count) {
				if (count == cur_element) videlenie_stroki(tmp.set_str_item());
				else cout << tmp.set_str_item();
				cout << endl;
				//cout << count << endl;
			}
			count++;
		};
		for_each(vec_item_Wep.begin(), vec_item_Wep.end(), pr);
		for_each(vec_item_Def.begin(), vec_item_Def.end(), pr);
		for_each(vec_item_Use.begin(), vec_item_Use.end(), pr);
		for_each(vec_item_No_Use.begin(), vec_item_No_Use.end(), pr);


		/*������� ���������� � ��������*/
		cout << "\n";	info_stroka(type_cur_item(cur_element));
		/*��������� � �������� ��������, ����� ������� ��� ������*/
		cout << "\n";	sell_or_not_sell(type_cur_item(cur_element), nomer_NPC);
		/*������� ���������� � ���������� ��������*/
		cout << "\n";   cout << info_event << endl; info_event = "";

		/*������� ��� �� ����*/
		menu_move_cord();
		if (send_enter) enter_sell(type_cur_item(cur_element), nomer_NPC, mani); /*��������� �������� � ���������*/
		if (send_esc) { send_esc = 0; return 0; }
		return 1;
	}






	   

	/*������ �������� �������� ��������*/
	int ptint_shop_plotnik(int& mani) {	
		/*� ��� ��� ��� ���� ���� �����... ���� (�� ��� ���� ����� �������-�, �������-� �������)*/
		/*����� ����� �������� �� ����������� ��� ��� ��������, �� ������� ������ ���*/
		//system("cls");
		max_niz = vec_shop_pl_n.size() + vec_shop_pl_u.size() - 1; /*�������� ������ ��������!!!*/
		//if (send_enter) enter_inventar(type_cur_item(cur_element)); /*��������� �������� � ���������*/

		/*��������� ���������*/
		cout << "		������� �����������: " << cur_element + 1 << "/" << max_niz + 1 << " ���. " << (str_begin / 10) + 1 << "\n\n";

		/*������� ��� ������� �� �����������*/
		int count = 0; /*����� � ��������������� ��-��*/
		auto pr = [&](auto& tmp) {
			if (count >= str_begin && count < str_end) {
				//if (str_begin<= count && str_end> count) {
				if (count == cur_element) videlenie_stroki(tmp.set_str_item());
				else cout << tmp.set_str_item();
				cout << endl;
				//cout << count << endl;
			}
			count++;
		};
		for_each(vec_shop_pl_n.begin(), vec_shop_pl_n.end(), pr);
		for_each(vec_shop_pl_u.begin(), vec_shop_pl_u.end(), pr);
	
		/*������� ���������� � �������� ��������*/
		if (cur_element < vec_shop_pl_n.size())
			cout << "\n������ \"" << vec_shop_pl_n.at(cur_element).set_name_item() << "\" �� " << vec_shop_pl_n.at(cur_element).set_many_buy()
			<< "\n[��� ������� ������� Enter(E)]";
		else
			cout << "\n������ \"" << vec_shop_pl_u.at(cur_element - vec_shop_pl_n.size()).set_name_item() << "\" �� " << vec_shop_pl_u.at(cur_element - vec_shop_pl_n.size()).set_many_buy()
			<< "\n[��� ������� ������� Enter(E)]";
		/*������� ���������� � ���������� ��������*/
		cout << "\n";   cout << info_event << endl; info_event = "";

		/*������� ��� �� ����*/
		menu_move_cord();
		if (send_esc) { control_zero(); return 0; } /*������� ���� ��� �������� ��������*/

		/*������� ��������*/
		if (send_enter) {
			/*������� ������*/
			if (cur_element < vec_shop_pl_n.size()) {
				if (mani > vec_shop_pl_n.at(cur_element).set_many_buy()) {
					mani -= vec_shop_pl_n.at(cur_element).set_many_buy();
					add_item(vec_shop_pl_n.at(cur_element));
					info_event = "������� \"" + vec_shop_pl_n.at(cur_element).set_name_item() + "\" ����������!";
				}
				else info_event = "\n� ��� ������������ ����� ��� ���� �������!\n";
			}
			else {
				if (mani > vec_shop_pl_u.at(cur_element - vec_shop_pl_n.size()).set_many_buy()) {
					mani -= vec_shop_pl_u.at(cur_element - vec_shop_pl_n.size()).set_many_buy();
					add_item(vec_shop_pl_u.at(cur_element - vec_shop_pl_n.size()));
					info_event = "������� \"" + vec_shop_pl_u.at(cur_element - vec_shop_pl_n.size()).set_name_item() + "\" ����������!";
				}
				else info_event = "\n� ��� ������������ ����� ��� ���� �������!\n";
			}
			send_enter = 0;
		}
	}

	/*������ �������� �������� �����������*/
	int ptint_shop_tav(int& mani) {
		//system("cls");
		max_niz = vec_shop_tav_d.size() + vec_shop_tav_u.size() - 1; /*�������� ������ ��������!!!*/	
		//if (send_enter) enter_inventar(type_cur_item(cur_element)); /*��������� �������� � ���������*/

		/*��������� ���������*/
		cout << "		������� �����������: " << cur_element + 1 << "/" << max_niz + 1 << " ���. " << (str_begin / 10) + 1 << "\n\n";

		/*������� ��� ������� �� �����������*/
		int count = 0; /*����� � ��������������� ��-��*/
		auto pr = [&](auto& tmp) {
			if (count >= str_begin && count < str_end) {
				//if (str_begin<= count && str_end> count) {
				if (count == cur_element) videlenie_stroki(tmp.set_str_item());
				else cout << tmp.set_str_item();
				cout << endl;
				//cout << count << endl;
			}
			count++;
		};		
		for_each(vec_shop_tav_u.begin(), vec_shop_tav_u.end(), pr);
		for_each(vec_shop_tav_d.begin(), vec_shop_tav_d.end(), pr);
	


		/*������� ���������� � �������� ��������*/
		if (cur_element < vec_shop_tav_u.size())
			cout << "\n������ \"" << vec_shop_tav_u.at(cur_element).set_name_item() << "\" �� " << vec_shop_tav_u.at(cur_element).set_many_buy()
			<< "\n[��� ������� ������� Enter(E)]";
		else
			cout << "\n������ \"" << vec_shop_tav_d.at(cur_element - vec_shop_tav_u.size()).set_name_item() << "\" �� " << vec_shop_tav_d.at(cur_element - vec_shop_tav_u.size()).set_many_buy()
			<< "\n[��� ������� ������� Enter(E)]";
		/*������� ���������� � ���������� ��������*/
		cout << "\n";   cout << info_event << endl; info_event = "";

		/*������� ��� �� ����*/
		menu_move_cord();
		if (send_esc) { control_zero(); return 0; } /*������� ���� ��� �������� ��������*/

		/*������� ��������*/
		if (send_enter) {
			/*������� ������*/
			if (cur_element < vec_shop_tav_u.size()) {
				if (mani > vec_shop_tav_u.at(cur_element).set_many_buy()) {
					mani -= vec_shop_tav_u.at(cur_element).set_many_buy();
					add_item(vec_shop_tav_u.at(cur_element));
					info_event = "������� \"" + vec_shop_tav_u.at(cur_element).set_name_item() + "\" ����������!";
				}
				else info_event = "\n� ��� ������������ ����� ��� ���� �������!\n";
			}
			else {
				if (mani > vec_shop_tav_d.at(cur_element - vec_shop_tav_u.size()).set_many_buy()) {
					mani -= vec_shop_tav_d.at(cur_element - vec_shop_tav_u.size()).set_many_buy();
					add_item(vec_shop_tav_d.at(cur_element - vec_shop_tav_u.size()));
					info_event = "������� \"" + vec_shop_tav_d.at(cur_element - vec_shop_tav_u.size()).set_name_item() + "\" ����������!";
				}
				else info_event = "\n� ��� ������������ ����� ��� ���� �������!\n";
			}
			send_enter = 0;
		}
		return 1;
	}


	/*������ �������� �������� �������*/
	int ptint_shop_kuz(int& mani) {
		//system("cls");
		max_niz = vec_shop_kuz_w.size() + vec_shop_kuz_d.size() + vec_shop_kuz_it.size() - 1; /*�������� ������ ��������!!!*/

		//if (send_enter) enter_inventar(type_cur_item(cur_element)); /*��������� �������� � ���������*/

		/*��������� ���������*/
		cout << "	������� �������: " << cur_element + 1 << "/" << max_niz + 1 << " ���. " << (str_begin / 10) + 1 << "\n\n";

		/*������� ��� ������� �� �����������*/
		int count = 0; /*����� � ��������������� ��-��*/
		auto pr = [&](auto& tmp) {
			if (count >= str_begin && count < str_end) {
				//if (str_begin<= count && str_end> count) {
				if (count == cur_element) videlenie_stroki(tmp.set_str_item());
				else cout << tmp.set_str_item();
				cout << endl;
				//cout << count << endl;
			}
			count++;
		};
		for_each(vec_shop_kuz_w.begin(), vec_shop_kuz_w.end(), pr);
		for_each(vec_shop_kuz_d.begin(), vec_shop_kuz_d.end(), pr);
		for_each(vec_shop_kuz_it.begin(), vec_shop_kuz_it.end(), pr);
	
		/*������� ���������� � �������� ��������*/
		if (cur_element < vec_shop_kuz_w.size())
			cout << "\n������ \"" << vec_shop_kuz_w.at(cur_element).set_name_item() << "\" �� " << vec_shop_kuz_w.at(cur_element).set_many_buy()
			<< "\n[��� ������� ������� Enter(E)]";
		else if (cur_element <( vec_shop_kuz_w.size() + vec_shop_kuz_d.size()))
			cout << "\n������ \"" << vec_shop_kuz_d.at(cur_element - vec_shop_kuz_w.size()).set_name_item() << "\" �� " << vec_shop_kuz_d.at(cur_element - vec_shop_kuz_w.size()).set_many_buy()
			<< "\n[��� ������� ������� Enter(E)]";
		else
			cout << "\n������ \"" << vec_shop_kuz_it.at(cur_element - vec_shop_kuz_w.size()- vec_shop_kuz_d.size()).set_name_item() << "\" �� " << vec_shop_kuz_it.at(cur_element - vec_shop_kuz_w.size() - vec_shop_kuz_d.size()).set_many_buy()
			<< "\n[��� ������� ������� Enter(E)]";

		/*������� ���������� � ���������� ��������*/
		cout << "\n";   cout << info_event << endl; info_event = "";

		/*������� ��� �� ����*/
		menu_move_cord();
		if (send_esc) { control_zero(); return 0; } /*������� ���� ��� �������� ��������*/

		/*������� ��������*/
		if (send_enter) {
			/*������� ������*/
			if (cur_element < vec_shop_kuz_w.size()) {
				if (mani > vec_shop_kuz_w.at(cur_element).set_many_buy()) {
					mani -= vec_shop_kuz_w.at(cur_element).set_many_buy();
					add_item(vec_shop_kuz_w.at(cur_element));
					info_event = "������� \"" + vec_shop_kuz_w.at(cur_element).set_name_item() + "\" ����������!";
				}
				else info_event = "\n� ��� ������������ ����� ��� ���� �������!\n";
			}
			else if (cur_element < (vec_shop_kuz_w.size() + vec_shop_kuz_d.size()))
			{
				if (mani > vec_shop_kuz_d.at(cur_element - vec_shop_kuz_w.size()).set_many_buy()) {
					mani -= vec_shop_kuz_d.at(cur_element - vec_shop_kuz_w.size()).set_many_buy();
					add_item(vec_shop_kuz_d.at(cur_element - vec_shop_kuz_w.size()));
					info_event = "������� \"" + vec_shop_kuz_d.at(cur_element - vec_shop_kuz_w.size()).set_name_item() + "\" ����������!";
				}
				else info_event = "\n� ��� ������������ ����� ��� ���� �������!\n";
			}
			else 
			{//vec_shop_kuz_it
				if (mani > vec_shop_kuz_it.at(cur_element - vec_shop_kuz_w.size()- vec_shop_kuz_d.size()).set_many_buy()) {
					mani -= vec_shop_kuz_it.at(cur_element - vec_shop_kuz_w.size()- vec_shop_kuz_d.size()).set_many_buy();
					add_item(vec_shop_kuz_it.at(cur_element - vec_shop_kuz_w.size()- vec_shop_kuz_d.size()));
					info_event = "������� \"" + vec_shop_kuz_it.at(cur_element - vec_shop_kuz_w.size()- vec_shop_kuz_d.size()).set_name_item() + "\" ����������!";
				}
				else info_event = "\n� ��� ������������ ����� ��� ���� �������!\n";
			}

			send_enter = 0;
		}
		return 1;
	}

	/*������ �������? ����������, �������� � �����������*/
	void zapolnenie_kuz(){			
		// vec_shop_kuz_w;
		// vec_shop_kuz_d;
		
		/*������*/
		item_Wep W;
		W.crw_1_kinjal();		vec_shop_kuz_w.push_back(W);
		W.crw_2_sword_10();		vec_shop_kuz_w.push_back(W);
		W.crw_3_sword_14();		vec_shop_kuz_w.push_back(W);
		W.crw_4_sword_20();		vec_shop_kuz_w.push_back(W);
		W.crw_5_sword_30();		vec_shop_kuz_w.push_back(W);

		/*�������*/
		item_Def D;	
		D.crw_1_arms();		vec_shop_kuz_d.push_back(D);
		D.crw_1_golova();	vec_shop_kuz_d.push_back(D);
		D.crw_1_nogi();		vec_shop_kuz_d.push_back(D);
		D.crw_1_grud();		vec_shop_kuz_d.push_back(D);
		D.crw_2_arms();		vec_shop_kuz_d.push_back(D);
		D.crw_2_golova();	vec_shop_kuz_d.push_back(D);
		D.crw_2_grud();		vec_shop_kuz_d.push_back(D);
		D.crw_2_nogi();		vec_shop_kuz_d.push_back(D);
		item_No_Use N;
		N.korobka_gvozdei(); vec_shop_kuz_it.push_back(N);

		/*���������� �������  vec_shop_tav_d;	 vec_shop_tav_u;*/
		D.crw_0_golova();	vec_shop_tav_d.push_back(D);
		D.crw_0_grud();		vec_shop_tav_d.push_back(D);
		D.crw_0_nogi();		vec_shop_tav_d.push_back(D);
		D.crw_0_arms();		vec_shop_tav_d.push_back(D);
		
		item_Use U;
		U.c_eda_bint_1();	vec_shop_tav_u.push_back(U);
		U.c_eda_bint_2();	vec_shop_tav_u.push_back(U);
		U.c_eda_cyp_1();	vec_shop_tav_u.push_back(U);
		U.c_eda_cyp_2();	vec_shop_tav_u.push_back(U);
		U.c_eda_salst_1();	vec_shop_tav_u.push_back(U);
		U.c_eda_salst_2();	vec_shop_tav_u.push_back(U);		

		/*���������� �������� (3 ����)*/
		//	vec_shop_pl_u;	 vec_shop_pl_n;
		N.prostoi_topor(); vec_shop_pl_n.push_back(N);

		U.c_zelie_vin(); vec_shop_pl_u.push_back(U);
		U.c_zelie_xp(); vec_shop_pl_u.push_back(U);
		/*����� ����� ��� ��� ���� ����������, �� ������� ����� ��������� ��� ��� ����� ������ ��, � ��� ����� ��� � ��� �����*/
	}	


	/*��������� ��������� ��������� � ����� ���������� ���������� ������� ���������*/
	int random_drop(int level) {
		item_No_Use N;
		int counter = 0;		
		int val = rand() % 100 + level;
		if (val > 20) { counter++; N.tushka();  add_item(N); }
		val = rand() % 100 + level;
		if (val > 45) { counter++; N.shkura(); add_item(N);}
		val = rand() % 100 + level;
		if (val > 60) { counter++; N.kogti(); add_item(N);}
		val = rand() % 100 + level;
		if (val > 90) { counter++; N.ruda_1(); add_item(N);}
		else if	(val > 100) { counter++; N.ruda_2(); add_item(N);}
		else if (val > 120) { counter++; N.ruda_3(); add_item(N);}		
		return counter;
	}
	/*����� ����� �����*/
	void random_find(string& info) {
		item_No_Use N; item_Wep W;	
		info = "�� ����� \"";
		int val = rand() % 100 + 1;
		if (val < 3) { N.ruda_3();			info += N.set_name_item(); 	add_item(N); }
		else if (val < 10) { N.ruda_2();	info += N.set_name_item(); 	add_item(N); }
		else if (val < 20) { N.ruda_1();	info += N.set_name_item(); 	add_item(N); }
		else if (val < 50) { N.grib();		info += N.set_name_item(); 	add_item(N); }
		else if (val < 75) { N.verevka();	info += N.set_name_item(); 	add_item(N); }
		else			{ W.crw_0_palka();	info += W.set_name_item();	add_item(W); }
		info += "\"!";
	}
	/*����� ��������, � ������ ������ ���������� 1*/
	bool random_lamder(string& info) {	
		if (find_topor()) {
			item_No_Use N;
			N.brevno_1();
			info = "�� ������� \"";
			int val = rand() % 100 + 1;
			if (val < 3) { N.brevno_2(); info += N.set_name_item(); 	add_item(N); }
			else { N.brevno_1();	info += N.set_name_item();	add_item(N); }
			info += "\"!";
			return 1;
		}
		else {
			info = "� ��� ��� ������!";
			return 0;
		}
	}
	/*����� ��� �������� ������ ������*/
	bool find_topor(){		
		auto it = find_if(vec_item_No_Use.begin(), vec_item_No_Use.end(), [](item_No_Use& N) {return  N.if_topor(); });
		if (it != vec_item_No_Use.end()) { return 1; }
		return 0;		
	}
	bool find_verevka() {
		auto it = find_if(vec_item_No_Use.begin(), vec_item_No_Use.end(), [](item_No_Use& N) {return  N.if_verevka(); });
		if (it != vec_item_No_Use.end()) { return 1; }
		return 0;
	}

	bool giv_brevna() {
		auto it = find_if(vec_item_No_Use.begin(), vec_item_No_Use.end(), [](item_No_Use& N) {return  N.if_brevno(); });
		if (it != vec_item_No_Use.end()) { 	vec_item_No_Use.erase(it); max_item_val--;	return 1; }
		return 0;
	}
	bool giv_gvozdi() {
		auto it = find_if(vec_item_No_Use.begin(), vec_item_No_Use.end(), [](item_No_Use& N) {return  N.if_gvozd(); });
		if (it != vec_item_No_Use.end()) {	vec_item_No_Use.erase(it); max_item_val--;	return 1; }
		return 0;
	}	
};



