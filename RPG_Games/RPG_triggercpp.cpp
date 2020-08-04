#pragma once
#include <iostream>
#include <string>
#include <memory>//shared_ptr unique_ptr week_ptr
/*��������� �������� ����� ������������� ����� �������� ��� ��������*/



struct triggered_qw {
	/*��������� ��� ������ �������*/
	int day = 1;
	bool e_val = 0; //������ ��������

	/*�������� ����� - ���� ������*/
	bool prolog = 0; //�������� ������ � ������
	bool see_house = 0; //������� ���� ����������� ���
	bool acsses_trak = 0;
	bool acsses_plot= 0;
	bool acsses_kuz = 0;	
	bool acsses_shop_kuz = 0;
	bool acsses_shop_tr= 0;

	/*��������� ������� */
	bool helo_trakt = 0;
	bool helo_plot = 0;
	bool helo_kuz = 0;	

	/*������ - ������ � ������ ���*/
	bool acsses_podval_kuz = 0;
	bool find_krepkai_palka = 0;
	bool kill_kroto_kris = 0;
	bool end_qv_kuz = 0;

	/*������� - ����������� � ���*/
	bool start_qw_pod = 0;	
	bool acsecc_podval_tav = 0;
	bool acsecc_sleep = 0;

	/*������� - ������*/
	int kill_tav_kr = 0; //�������� �������� ������� �������
	bool qw_taverna_vin = 0; //����� ���� � ������� ������� �� ������
	

	/*����������� �������������*/
	/*����� ����� �� ������ ������ ��������� ���� ��� ��������*/
	bool quest_find_ochag = 0; //��������� ������ �����
	bool quest_find_ochag1 = 0; //����������� ���� �� �����
	bool quest_find_ochag2 = 0; //����������� ���� � �������
	bool quest_find_ochag3 = 0; //����������� ���� � �������
	bool tell_dogadka = 0; //���������� � ������� ��� ����� ��� ������ � �������� ���� ����
	//������� �������� ������
	void detect_if() { if (quest_find_ochag1 &&quest_find_ochag2 &&quest_find_ochag3) { quest_find_ochag = 0; tell_dogadka = 1; } }

	/*�������� �������*/
	bool acsecc_kol = 0; /*������ � �������*/
	bool dead_quen = 0;  /*�������� ����������*/
	bool tell_quen = 0; /*���������� � ������*/
	   	 	
	/*������������� ����!*/
	bool need_brevna = 0;
	bool need_bgbozdi = 0;
	int count_brevna = 20;
	int count_bgbozdi = 10;
	bool dom_postroen = 0;
	void if_complate_dom() {
		if (count_brevna <= 0) need_brevna=1;
		if (count_bgbozdi <= 0) need_bgbozdi = 1;
		if (need_brevna && need_bgbozdi) dom_postroen = 1;
	}
	bool say_postroen = 0;
	bool new_dom=0; /*��������� ����� �� ��������� ����*/
						
	/*������*/ /*dom_postroen == 1 new_dom*/
	//dead_quen ������ ==1, dom_postroen ==1
	bool dom_postroen_and_not_problem = 0; //��� ��������, ������ ���������
	bool vin() {	
		if (dom_postroen && dead_quen) return 1;
		return 0;
	}
};


/*��������� ������ �� ��� �����, ��� � ��� � ��������� ����*/
/*��������� ������� ������ �����*/
struct status{
	int xp;
	int max_xp;
	int vinos;
	int max_vinos;
	status() {
		xp=30;
		max_xp=30;
		vinos = 1590;
		max_vinos = 1599;
	}
	/*����� ��� �����, ��� ������*/
	void nul(){	xp = 0;	max_xp = 0;	vinos = 0;	max_vinos = 0;}
	/*�������� ����������*/
	status& operator=(const status& temp) {
		xp = temp.xp;
		max_xp = temp.max_xp;
		vinos = temp.vinos;
		max_vinos = temp.max_vinos;
		return *this;
	}
	/*����������� �����������*/
	status(const status& temp) {
		xp = temp.xp;
		max_xp = temp.max_xp;
		vinos = temp.vinos;
		max_vinos = temp.max_vinos;
	}
	// ������������� ����
	status& operator+=(const status& temp) {
		int val = temp.xp;
	
		while (val && xp < max_xp) {
			xp++; val--;
		}
		max_xp += temp.max_xp;
		vinos += temp.vinos;
		max_vinos += temp.max_vinos;		
		
		return *this;
	}
};



