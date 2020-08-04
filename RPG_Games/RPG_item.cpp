#pragma once
#include <iostream>
#include <string>
#include <conio.h> //��� _getch();
#include <Windows.h> //��� �����
#include <sstream> //��������� ������
#include "RPG_triggercpp.cpp"
using namespace std;


class item {
protected:
	int tip;
	string name;
	string opisnie;	
	/*����������� ��������*/
	int total;
	int total_full;
	/*C��������*/
	int many_buy;
	int many_sell;

	/*kto ckupaet 1-������, 2-����������, 3-�������*/
	int skupshik = 0;	
public:
	
	virtual void print_item() = 0;

	/*���������� ��� ���� ������*/
	string set_info_str() {	return opisnie;}
	string set_name_item() {return name;}
	int set_many_buy() { return many_buy; }
	/*kto ckupaet 1-������, 2-����������, 3-�������*/
	int set_skupshik() { return skupshik; }
};


/* -- ����������� ������ -- */
class item_Wep : public item {
protected:
	int ataka;
public:
	item_Wep() {}
	void crw_0_palka() {
		tip = 1; /*count_item = 1;*/  name = "������� �����";
		opisnie = "���������� ������� ��� �� �������� �����";		
		total = 999; total_full = 999;
		many_buy = 100;
		/*����*/
		ataka = 3;

	}
	void crw_1_kinjal() {
		tip = 1; /*count_item = 1;*/ name = "������";
		opisnie = "������ ��� �����������";
		total = 150; total_full = 150;
		many_buy = 1500; skupshik = 1;
		/*����*/
		ataka = 5;
	}
	void crw_2_sword_10() {
		tip = 1;/* count_item = 1;*/ name = "������� ���";
		opisnie = "��� ���������� �����";
		total = 400; total_full = 400;
		many_buy = 3000; skupshik = 1;
		/*����*/
		ataka = 10;
	}
	void crw_3_sword_14() {
		tip = 1; /*count_item = 1;*/ name = "������� ���";
		opisnie = "��� ���������� �����";
		total = 600; total_full = 600;
		many_buy = 6000; skupshik = 1;
		/*����*/
		ataka = 14;
	}
	void crw_4_sword_20() {
		tip = 1; /*count_item = 1; id_sort = 100103; */name = "������������ ���";
		opisnie = "��� ���������� �����";
		total = 999; total_full = 999;
		many_buy = 15000;  skupshik = 1;
		/*����*/
		ataka = 20;
	}
	void crw_5_sword_30() {
		tip = 1;/* count_item = 1; id_sort = 100103;*/ name = "��� �����";
		opisnie = "��� ���������� �����";
		total = 999; total_full = 999;
		many_buy = 21000;  skupshik = 1;
		/*����*/
		ataka = 25;
	}

	/*���������*/
	void print_item() {
		cout.width(33);
		cout << std::left << name;
		cout.width(6);
		cout << std::left << "����:";
		cout.width(3);
		cout << std::left << ataka;
		cout.width(2);
		cout << std::left << " ";
		cout.width(6);
		cout << std::left << " ����: " << total / 10 << "/" << total_full / 10;
	}
	int set_attak() {return ataka;}
	string set_str_item() {
		/*���������� ������ ���������� ������ � �����, � ����� ����� ����������� � ������ �������.str()*/
		ostringstream out_p;				   
		out_p.width(33);
		out_p << std::left << name;
		out_p.width(6);
		out_p << std::left << "����:";
		out_p.width(3);
		out_p << std::left << ataka;
		out_p.width(2);
		out_p << std::left << " ";
		out_p.width(6);
		out_p << std::left << " ����: " << total / 10 << "/" << total_full / 10;
		string s = out_p.str(); //��������� �� ������ �������
		return s;
	}	
	/*�������� ����������*/
	item_Wep& operator=(const item_Wep& temp) {
		tip = temp.tip;/* count_item = temp.count_item; id_sort = temp.id_sort; */ name = temp.name;
		opisnie = temp.opisnie;
		total = temp.total; total_full = temp.total_full;
		many_buy = temp.many_buy; many_sell = temp.many_sell; skupshik = temp.skupshik;
		/*����*/
		ataka = temp.ataka;
		return *this;
	}
	/*����������� �����������*/
	item_Wep(const item_Wep& temp) { 
		tip = temp.tip; name = temp.name;
		opisnie = temp.opisnie;
		total = temp.total; total_full = temp.total_full;
		many_buy = temp.many_buy; many_sell = temp.many_sell; skupshik = temp.skupshik;
		/*����*/
		ataka = temp.ataka;		
	}		
};

class item_Def : public item {
protected:
	int vid_def; //1-������, 2 ��������, 3-���� 3-����
	string vid_def_s;
	int deff;
public:
	int set_type_def() { return vid_def; }
	int set_deff() { return deff; }
	item_Def() {}
	//item_Def(string tip_item) {
	//	if (tip_item == "��_��������_����") {
	//		tip = 1; count_item = 1; name = "������� �������� ����";
	//		opisnie = "����� �������� ������ �� ������ ������";
	//		total = 100; total_full = 100;
	//		many_buy = 10; many_sell = 100;
	//		/*����*/
	//		vid_def = 1; deff = 2; vid_def_s = " - ������ ";
	//	}
	//}
	void crw_0_golova() {
		tip = 1;/* count_item = 1; id_sort = 10101; */name = "��������_����";
		opisnie = "������� �������� ����";
		total = 100; total_full = 100;
		many_buy = 200; many_sell = 20; skupshik = 2;
		/*����*/
		vid_def = 1; deff = 2; vid_def_s = " - ������ ";
	}
	void crw_0_grud() {
		tip = 1; /*count_item = 1; id_sort = 10101;*/ name = "�������� ���������";
		opisnie = "������� �������� ���������";
		total = 100; total_full = 100;
		many_buy = 200; many_sell = 20; skupshik = 2;
		/*����*/
		vid_def = 2; deff = 2; vid_def_s = " - ����  ";
	}
	void crw_0_nogi() {
		tip = 1; /*count_item = 1; id_sort = 10101;*/ name = "�������� �����";
		opisnie = "������� �������� �����";
		total = 100; total_full = 100;
		many_buy = 200; many_sell = 20; skupshik = 2;
		/*����*/
		vid_def = 3; deff = 2; vid_def_s = " - ���� ";
	}
	void crw_0_arms() {
		tip = 1; /*count_item = 1; id_sort = 10101;*/ name = "�������� ������";
		opisnie = "������� �������� ������";
		total = 100; total_full = 100;
		many_buy = 200; many_sell = 10; skupshik = 2;
		/*����*/
		vid_def = 4; deff = 2; vid_def_s = " - ���� ";
	}

	void crw_1_golova() {
		tip = 1; /*count_item = 1; id_sort = 10101;*/ name = "���������� ����";
		opisnie = "���������� ����";
		total = 200; total_full = 200;
		many_buy = 8000; many_sell = 80; skupshik = 1;
		/*����*/
		vid_def = 1; deff = 3; vid_def_s = " - ������ ";
	}
	void crw_1_grud() {
		tip = 1; /*count_item = 1; id_sort = 10101;*/ name = "���������� ���������";
		opisnie = "���������� ���������";
		total = 200; total_full = 200;
		many_buy = 12000; many_sell = 2000; skupshik = 1;
		/*����*/
		vid_def = 2; deff = 4; vid_def_s = " - ����  ";
	}
	void crw_1_nogi() {
		tip = 1; /*count_item = 1; id_sort = 10101;*/ name = "���������� �����";
		opisnie = "���������� �����";
		total = 200; total_full = 200;
		many_buy = 10000; many_sell = 2000; skupshik = 1;
		/*����*/
		vid_def = 3; deff = 3; vid_def_s = " - ���� ";
	}
	void crw_1_arms() {
		tip = 1; /*count_item = 1; id_sort = 10101;*/ name = "���������� ������";
		opisnie = "���������� ������";
		total = 200; total_full = 200;
		many_buy = 10000; many_sell = 2000; skupshik = 1;
		/*����*/
		vid_def = 4; deff = 3; vid_def_s = " - ���� ";
	}

	void crw_2_golova() {
		tip = 1; /*count_item = 1; id_sort = 10101;*/ name = "��������  ����";
		opisnie = "��������  ����";
		total = 400; total_full = 400;
		many_buy = 20000; many_sell = 20000; skupshik = 1;
		/*����*/
		vid_def = 1; deff = 4; vid_def_s = " - ������ ";
	}
	void crw_2_grud() {
		tip = 1;/* count_item = 1; id_sort = 10101;*/ name = "��������  ���������";
		opisnie = "��������  ���������";
		total = 400; total_full = 400;
		many_buy = 34000; many_sell = 20000; skupshik = 1;
		/*����*/
		vid_def = 2; deff = 6; vid_def_s = " - ����  ";
	}
	void crw_2_nogi() {
		tip = 1;/* count_item = 1; id_sort = 10101;*/ name = "�������� �����";
		opisnie = "�������� �����";
		total = 400; total_full = 400; skupshik = 1;
		many_buy = 24000; /*many_sell = 20000;*/
		/*����*/
		vid_def = 3; deff = 5; vid_def_s = " - ���� ";
	}
	void crw_2_arms() {
		tip = 1;/* count_item = 1; id_sort = 10101;*/ name = "�������� ������";
		opisnie = "�������� ������";
		total = 400; total_full = 400; skupshik = 1;
		many_buy = 24000;/* many_sell = 20000;*/
		/*����*/
		vid_def = 4; deff = 5; vid_def_s = " - ���� ";
	}

	/*���������*/
	void print_item() {
		cout.width(33);
		cout << std::left << name;
		cout.width(6);
		cout << std::left << "���.:";
		cout.width(3);
		cout << std::left << deff;
		cout.width(2);
		cout << std::left << " ";
		cout.width(6);
		cout << std::left << " ����: " << total / 10 << "/" << total_full / 10;
	}
	string set_str_item() {
		/*���������� ������ ���������� ������ � �����, � ����� ����� ����������� � ������ �������.str()*/
		ostringstream out_p;				   
		out_p.width(33);
		out_p << std::left << name;
		out_p.width(6);
		out_p << std::left << "���.:";
		out_p.width(3);
		out_p << std::left << deff;
		out_p.width(2);
		out_p << std::left << " ";
		out_p.width(6);
		out_p << std::left << " ����: " << total / 10 << "/" << total_full / 10;
		string s = out_p.str(); //��������� �� ������ �������
		return s; /*� �� ��� ��������=)*/
	}

	/*�������� ����������*/
	item_Def& operator=(const item_Def& temp) {
		tip = temp.tip;/* count_item = temp.count_item; id_sort = temp.id_sort; */ name = temp.name;
		opisnie = temp.opisnie;
		total = temp.total; total_full = temp.total_full;
		many_buy = temp.many_buy; many_sell = temp.many_sell; skupshik = temp.skupshik;
		/*����*/
		deff = temp.deff; vid_def = temp.vid_def; vid_def_s = temp.vid_def_s;		
		return *this;
	}
	/*����������� �����������*/
	item_Def(const item_Def& temp) {
		tip = temp.tip; /*count_item = temp.count_item; id_sort = temp.id_sort; */ name = temp.name;
		opisnie = temp.opisnie;
		total = temp.total; total_full = temp.total_full;
		many_buy = temp.many_buy; many_sell = temp.many_sell; skupshik = temp.skupshik;
		/*����*/
		deff = temp.deff; vid_def = temp.vid_def; vid_def_s = temp.vid_def_s;
	}
};

class item_Use : public item {
protected:
	status st;
	int deff_bonus =0;
	int atak_bonus = 0;
	string mini_info = "";
public:
	status set_status() {return st;}
	int set_def_bon() { return deff_bonus; }
	int set_atk_bon() { return atak_bonus; }
	item_Use() {}
	void c_eda_cyp_1() {
		tip = 1; name = "������������� ������";
		opisnie = "������� �� ����� +1 �����";
		total = 400; total_full = 400;
		many_buy = 200; skupshik =2;
		/*����*/
		st.nul(); 
		deff_bonus = 0; mini_info = "����� (+1)";
		atak_bonus =1;
	}
	void c_eda_cyp_2() {
		tip = 1; name = "���� �� ����������";
		opisnie = "������� �� ����� +2 �����";
		total = 400; total_full = 400;
		many_buy = 600; skupshik = 2;
		/*����*/
		st.nul(); mini_info = "����� (+2)";
		deff_bonus = 0;
		atak_bonus = 2;
	}
	void c_eda_salst_1() {
		tip = 1; name = "������� �����";
		opisnie = "������� �� ����� +1 ������";
		total = 400; total_full = 400;
		many_buy = 400; skupshik = 2;
		/*����*/mini_info = "������ (+1)";
		st.nul();
		deff_bonus = 1;
		atak_bonus = 0;
	}
	void c_eda_salst_2() {
		tip = 1; name = "������� ����� �� ��������";
		opisnie = "������� �� ����� +2 ������";
		total = 400; total_full = 400; mini_info = "������ (+2)";
		many_buy = 900; skupshik = 2;
		/*����*/
		st.nul();
		deff_bonus = 2;
		atak_bonus = 0;
	}
	void c_eda_bint_1() {
		tip = 1; name = "������� ����";
		opisnie = "�������������� 5 ��";
		total = 1000; total_full = 400;
		many_buy = 1000; skupshik = 2;
		/*����*/
		st.nul(); st.xp = 5; mini_info = "����.�� (+5)";
		deff_bonus = 0;
		atak_bonus = 0;
	}
	void c_eda_bint_2() {
		tip = 1; name = "������� ����";
		opisnie = "�������������� 10 ��";
		total = 1500; total_full = 400;
		many_buy = 1500; skupshik = 2;
		/*����*/
		st.nul(); st.xp = 10;
		deff_bonus = 0; mini_info = "����.�� (+10)";
		atak_bonus = 0;
	}
	void c_zelie_vin() {
		tip = 1; name = "�������� ����";
		opisnie = "����������� ������������ ������������ �� 1";
		total = 1500; total_full = 400;
		many_buy = 5000; skupshik = 3;
		/*����*/
		st.nul(); st.max_vinos = 1;
		deff_bonus = 0; mini_info = "����.��� (+1)";
		atak_bonus = 0;
	}
	void c_zelie_xp() {
		tip = 1; name = "��������� ��������";
		opisnie = "����������� ������������ �� �� 1";
		total = 1500; total_full = 400;
		many_buy = 3500; skupshik = 3;
		/*����*/
		st.nul(); st.max_xp = 1;
		deff_bonus = 0; mini_info = "����.�� (+1)";
		atak_bonus = 0;
	}

	void print_item() {
		cout.width(33);
		cout << std::left << name;	
		cout << std::left <<" " << std::left << mini_info;
	}
	string set_str_item() {
		/*���������� ������ ���������� ������ � �����, � ����� ����� ����������� � ������ �������.str()*/
		ostringstream out_p;
		out_p.width(33);
		out_p << std::left << name;	
		out_p << std::left << mini_info;
		string s = out_p.str(); //��������� �� ������ �������
		return s;
	}
	/*�������� ����������*/
	item_Use& operator=(const item_Use& temp) {
		tip = temp.tip;/* count_item = temp.count_item; id_sort = temp.id_sort; */ name = temp.name;
		opisnie = temp.opisnie;
		total = temp.total; total_full = temp.total_full;
		many_buy = temp.many_buy; many_sell = temp.many_sell; skupshik = temp.skupshik;
		st = temp.st;
		deff_bonus = temp.deff_bonus;
		atak_bonus = temp.atak_bonus; mini_info = temp.mini_info;
		return *this;
	}
	/*����������� �����������*/
	item_Use(const item_Use& temp) {
		tip = temp.tip; /*count_item = temp.count_item; id_sort = temp.id_sort; */ name = temp.name;
		opisnie = temp.opisnie;
		total = temp.total; total_full = temp.total_full;
		many_buy = temp.many_buy; many_sell = temp.many_sell; skupshik = temp.skupshik;
		
		st = temp.st;
		deff_bonus = temp.deff_bonus; mini_info = temp.mini_info;
		atak_bonus = temp.atak_bonus;
	}
};

class item_No_Use : public item {
protected:
	/*������, ��� �������� ������ � ����� ����, ������� �� ��������� ����� 0*/

public:
	bool Eto_gvozd;
	bool Eto_brevno ;
	bool Eto_topor;
	bool Eto_verevka;
	bool if_gvozd() {return Eto_gvozd;}
	bool if_brevno() { return Eto_brevno; }
	bool if_topor() { return Eto_topor; }
	bool if_verevka() { return Eto_verevka; }

	item_No_Use() {		
	}
	void ruda_1() {
		tip = 1; name = "������� ����";
		opisnie = "����� ������� �������";
		total = 400; total_full = 400;
		many_buy = 200; skupshik = 1;
		/*����*/	Eto_gvozd = 0;		Eto_brevno = 0;
		Eto_topor = 0;		Eto_verevka = 0;
	}
	void ruda_2() {
		tip = 1; name = "���������� ����";
		opisnie = "����� ������� �������";
		total = 400; total_full = 400;
		many_buy = 1300; skupshik = 1;
		/*����*/	Eto_gvozd = 0;		Eto_brevno = 0;
		Eto_topor = 0;		Eto_verevka = 0;
	}
	void ruda_3() {
		tip = 1; name = "���� ����������� �����";
		opisnie = "����� ������� �������";
		total = 400; total_full = 400;
		many_buy = 2900; skupshik = 1;
		/*����*/	Eto_gvozd = 0;		Eto_brevno = 0;
		Eto_topor = 0;		Eto_verevka = 0;
	}
	void kogti() {
		tip = 1; name = "����� ����������";
		opisnie = "������� �� ������";
		total = 400; total_full = 400;
		many_buy = 1200; skupshik = 1;
		/*����*/	Eto_gvozd = 0;		Eto_brevno = 0;
		Eto_topor = 0;		Eto_verevka = 0;
	}
	void shkura() {
		tip = 1; name = "����� �����-�����";
		opisnie = "��������� �������";
		total = 400; total_full = 400;
		many_buy = 900; skupshik = 1;
		/*����*/	Eto_gvozd = 0;		Eto_brevno = 0;
		Eto_topor = 0;		Eto_verevka = 0;
	}
	void tushka() {
		tip = 1; name = "���� �����-�����";
		opisnie = "�������� ��������, �� ����� ��������";
		total = 400; total_full = 400;
		many_buy = 900; skupshik = 2;
		/*����*/	Eto_gvozd = 0;		Eto_brevno = 0;
		Eto_topor = 0;		Eto_verevka = 0;
	}
	void grib() {
		tip = 1; name = "��������t �����";
		opisnie = "�������� ��������, �� ����� ��������";
		total = 400; total_full = 400;
		many_buy = 500; skupshik = 2;
		/*����*/	Eto_gvozd = 0;		Eto_brevno = 0;
		Eto_topor = 0;		Eto_verevka = 0;
	}	

	void brevno_1() {
		tip = 1; name = "������� ������";
		opisnie = "����� ������� ��������";
		total = 400; total_full = 400;
		many_buy = 250; skupshik = 3;
		/*����*/Eto_brevno = 1;	Eto_gvozd = 0;		
		Eto_topor = 0;		Eto_verevka = 0;
	}
	void brevno_2() {
		tip = 1; name = "������ ������";
		opisnie = "����� ������� ��������";
		total = 400; total_full = 400;
		many_buy = 1900; skupshik = 3;
		/*����*/Eto_brevno = 1;	Eto_gvozd = 0;		
		Eto_topor = 0;		Eto_verevka = 0;
	}
	void verevka() {
		tip = 1; name = "�������";
		opisnie = "����� ����-������ ���������";
		total = 300; total_full = 400;
		many_buy = 320; skupshik = 3;
		/*����*/Eto_verevka = 1;	Eto_gvozd = 0;		Eto_brevno = 0;
		Eto_topor = 0;		
	}
	void korobka_gvozdei() {
		tip = 1; name = "������� �������";
		opisnie = "������ - ��������� ���������";
		total = 400; total_full = 400;
		many_buy = 1050; skupshik = 3;
		/*����*/ Eto_gvozd = 1;			Eto_brevno = 0;
		Eto_topor = 0;		Eto_verevka = 0;
	}
	void prostoi_topor() {
		tip = 1; name = "������� ����� ";
		opisnie = "�������� ��� �� ������ �������";
		total = 400; total_full = 400;
		many_buy = 110; skupshik = 3;
		/*����*/ Eto_topor = true;	Eto_gvozd = 0;		Eto_brevno = 0;
		Eto_verevka = 0;
	}


	void print_item() {
		cout.width(33);
		cout << std::left << name;
	}
	string set_str_item() {
		/*���������� ������ ���������� ������ � �����, � ����� ����� ����������� � ������ �������.str()*/
		ostringstream out_p;
		out_p.width(33);
		out_p << std::left << name;
		string s = out_p.str(); //��������� �� ������ �������
		return s;
	}
	/*�������� ����������*/
	item_No_Use& operator=(const item_No_Use& temp) {
		tip = temp.tip;/* count_item = temp.count_item; id_sort = temp.id_sort; */ name = temp.name;
		opisnie = temp.opisnie;
		total = temp.total; total_full = temp.total_full;
		many_buy = temp.many_buy; many_sell = temp.many_sell; skupshik = temp.skupshik;	
		Eto_topor = temp.Eto_topor;	Eto_gvozd = temp.Eto_gvozd;		Eto_brevno = temp.Eto_brevno;
		Eto_verevka = temp.Eto_verevka;
		return *this;
	}
	/*����������� �����������*/
	item_No_Use(const item_No_Use& temp) {
		tip = temp.tip; /*count_item = temp.count_item; id_sort = temp.id_sort; */ name = temp.name;
		opisnie = temp.opisnie;
		total = temp.total; total_full = temp.total_full;
		many_buy = temp.many_buy; many_sell = temp.many_sell; skupshik = temp.skupshik;	
		Eto_topor = temp.Eto_topor;	Eto_gvozd = temp.Eto_gvozd;		Eto_brevno = temp.Eto_brevno;
		Eto_verevka = temp.Eto_verevka;
	}
};