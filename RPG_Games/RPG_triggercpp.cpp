#pragma once
#include <iostream>
#include <string>
#include <memory>//shared_ptr unique_ptr week_ptr
/*Структура тригеров будит перекидваться между классами как казаетль*/



struct triggered_qw {
	/*Структура для тригер квестов*/
	int day = 1;
	bool e_val = 0; //Запуск действия

	/*Вернутся домой - день первый*/
	bool prolog = 0; //показать пролог в начале
	bool see_house = 0; //Увидеть свой разрушенный дом
	bool acsses_trak = 0;
	bool acsses_plot= 0;
	bool acsses_kuz = 0;	
	bool acsses_shop_kuz = 0;
	bool acsses_shop_tr= 0;

	/*Стартовые диалога */
	bool helo_trakt = 0;
	bool helo_plot = 0;
	bool helo_kuz = 0;	

	/*КУЗНЕЦ - ПОДВАЛ и первый бой*/
	bool acsses_podval_kuz = 0;
	bool find_krepkai_palka = 0;
	bool kill_kroto_kris = 0;
	bool end_qv_kuz = 0;

	/*ТРАКТИР - возвращение и сон*/
	bool start_qw_pod = 0;	
	bool acsecc_podval_tav = 0;
	bool acsecc_sleep = 0;

	/*ТРАКТИР - ПОДВАЛ*/
	int kill_tav_kr = 0; //прогресс зачистки подвала таверны
	bool qw_taverna_vin = 0; //убить крыс в подвале таверны за деньги
	

	/*ДЕТЕКТИВНОЕ РАССЛЕДОВАНИЕ*/
	/*Взять мисию на поиски причин появления крыс под деревней*/
	bool quest_find_ochag = 0; //позволяет искать очаги
	bool quest_find_ochag1 = 0; //исследовать дыру за домом
	bool quest_find_ochag2 = 0; //исследовать дыру у кузница
	bool quest_find_ochag3 = 0; //исследовать дыру в таверне
	bool tell_dogadka = 0; //рассказать о догадке что крысы под землей и недолеко есть вход
	//провдит проверку поиска
	void detect_if() { if (quest_find_ochag1 &&quest_find_ochag2 &&quest_find_ochag3) { quest_find_ochag = 0; tell_dogadka = 1; } }

	/*ЗАЧИСТКА КОЛОДЦА*/
	bool acsecc_kol = 0; /*Доступ в колодец*/
	bool dead_quen = 0;  /*Королева уничтожена*/
	bool tell_quen = 0; /*Рассказать о победе*/
	   	 	
	/*СТРОИТЕЛЬСТВО ДОМА!*/
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
	bool new_dom=0; /*изменение карты на следующий день*/
						
	/*Победа*/ /*dom_postroen == 1 new_dom*/
	//dead_quen станет ==1, dom_postroen ==1
	bool dom_postroen_and_not_problem = 0; //дом построен, угроза устранена
	bool vin() {	
		if (dom_postroen && dead_quen) return 1;
		return 0;
	}
};


/*Впринципи статов не так много, деф и так в инвентаре есть*/
/*Структура которая хранит статы*/
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
	/*Нулит все статы, для итемок*/
	void nul(){	xp = 0;	max_xp = 0;	vinos = 0;	max_vinos = 0;}
	/*Оператор присвоения*/
	status& operator=(const status& temp) {
		xp = temp.xp;
		max_xp = temp.max_xp;
		vinos = temp.vinos;
		max_vinos = temp.max_vinos;
		return *this;
	}
	/*Конструктор копирования*/
	status(const status& temp) {
		xp = temp.xp;
		max_xp = temp.max_xp;
		vinos = temp.vinos;
		max_vinos = temp.max_vinos;
	}
	// присваивающий плюс
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



