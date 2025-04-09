#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>


#define UNIQUE_SIZE 1000
/**
 * 게임에 대한 모든 아이템과 몬스터들을 객체화? 구조체화 했다.
 * 
 * usage 
 * struct sword basic_sword;  선언 
 *  
 *  set_sword(basic_sword, '기본검', 10, 4, 1, 50, 0); 호출
 * 
 * 호출되어 리턴된 값으로 기본검이 생성됩니다. 
 * 
 */

// 랜덤 번호 생성
int make_unique_number()
{    
    // int rotto[SIZE];
    int r_number;
    int flag;
    int unique_number_list[UNIQUE_SIZE];

    r_number = (rand()% UNIQUE_SIZE) +1; 

    // 해당 하는 번호가 중복되었는지 체크

    
    for (int i=0; i<=sizeof(unique_number_list) ;i++)
    {
        if (r_number== unique_number_list[i])
            return 0;
    }
    return 1;

    return r_number;
}



struct sword  set_sword(struct sword p, char s_name[],int damage,int enforce, int attribute, int price, int mage_rate, int cri_rate);
struct amor set_amor(struct amor a, char a_name[],int damage_reduction,int damage_reduction_rate, int additional_damge_rate, int price, int mage_rage);
struct potion set_potion(struct potion p, char p_name[],int healing_hp_rate,int healing_mp_rate,int price,int quantity,int anti_posion,int blessing, int all_cure, int potal_scroll, int teleport_scroll);
struct refinery_material set_refinery_material(struct refinery_material r, char r_name[],int refinery_tier, int is_MTS, int quantity);
struct monster set_monster(struct monster m, char m_name[],int tier_info ,int hp,int atk,int def, int type, char drop_items[10][50] ,char special_effect[10][50]);
struct swordman set_swordman(struct swordman s, char s_name[],int lv ,int hp,int atk,int matk, int def, int ac,int cri, int str, int int_, int dex);
struct inven set_inven(struct inven i,int wallet, char bag[20][20], struct potion);

struct sword
{
    int tier;
    char name[30]; //칼의 이름
    int damage;
    int enforce; //강화
    int attribute; //속성 0 1 2 3 4
    int price;
    int cri_rate;
    int magic_rate; //마법배율? 뭐에쓰는 녀석인고?

};

struct sword  set_sword(struct sword s, char s_name[],int damage,int enforce, int attribute, int price,int cri_rate, int mage_rate)
{
    strcpy(s.name, s_name);
    s.damage = damage;
    s.enforce= enforce;
    s.attribute = attribute;
    s.price = price;
    s.magic_rate = mage_rate;
    s.cri_rate = cri_rate;
    return s;
}




// 갑옷/신발/장갑/망토/투구 공통이다.
struct amor
{
    int damage_reduction; //뎀감
    int damage_reduction_rate; //뎀감률 
    char name[30]; //방어구의 이름
    int price;
    int additional_damge_rate; //추뎀
};




struct potion
{
    char name[30]; //방어구의 이름
    int healing_hp_rate; //회복율
    int healing_mp_rate; //회복율
    int price;
    int quantity;   //수량99개 제한
    // char special[5][30];
    int anti_posion;    //해독제
    int blessing;        //축복
    int all_cure;        //만병통치약
    int potal_scroll;    // 마을로감
    int teleport_scroll; // 지정된 던전으로감

};

struct potion set_potion(struct potion p, char p_name[],int healing_hp_rate,int healing_mp_rate,int price,int quantity,int anti_posion,int blessing, int all_cure, int potal_scroll, int teleport_scroll)
{
    strcpy(p.name, p_name);
    p.healing_hp_rate = healing_hp_rate;
    p.healing_mp_rate= healing_mp_rate;
    p.price = price;
    p.quantity = quantity;
    p.anti_posion = anti_posion;
    p.blessing = blessing;
    p.all_cure = all_cure;
    p.potal_scroll = potal_scroll;
    p.teleport_scroll =teleport_scroll;
    // strcpy(p.special[5][30], special[5][30]);

    return p;
}

struct refinery_material
{
    char name[30];
    int refinery_tier;
    int is_MTS; //마력응축석 Magic Condensate Stone
    int quantity;
};

struct refinery_material set_refinery_material(struct refinery_material r, char r_name[],int refinery_tier, int is_MTS, int quantity)
{
    strcpy(r.name, r_name);
    r.refinery_tier = refinery_tier;
    r.is_MTS= is_MTS;    
    r.quantity = quantity;
    return r;
}
struct skill
{
    char name[30];
    int get_level;
    int type; // 1 불 2 물 3자연
    int magic_rate;
    int use_mp;
};

struct skill set_skill(struct skill s, char s_name[],int get_level ,int type,int magic_rate,int use_mp)
{
    strcpy(s.name, s_name);
    s.get_level = get_level;
    s.type= type;    
    s.magic_rate = magic_rate;
    s.use_mp= use_mp;
    return s;
}

struct monster
{
    char name[30];
    int tier_info;
    int hp;
    int atk;
    int def;
    int type; //  불은 물에 약하고 물은 자연에 약하고 자연은 불에 약함
    char drop_items[10][50];    // 드랍아이템
    char special_effect[10][50]; //특수효과
};  
struct monster set_monster(struct monster m, char m_name[],int tier_info ,int hp,int atk,int def, int type, char drop_items[10][50] ,char special_effect[10][50])
{
    strcpy(m.name, m_name);
    m.tier_info = tier_info;
    m.hp= hp;    
    m.atk = atk;
    m.def= def;
    m.type= type;
    m.drop_items[10][50]= drop_items[10][50];
    m.special_effect[10][50] = special_effect[10][50];
    return m;
}


struct swordman
{
    int lv;
    char name[30];
    int exp;
    int hp;
    int mp;
    int atk;
    int matk;
    int def;
    int ac;
    int cri;
    int str;
    int int_; 
    int dex;
};

struct swordman set_swordman(struct swordman s, char s_name[],int lv ,int hp,int atk,int matk, int def, int ac,int cri, int str, int int_, int dex)
{
    strcpy(s.name, s_name);
    s.lv = lv;
    s.hp= hp;    
    s.atk = atk;
    s.def= def;
    s.ac =ac;
    s.cri =cri;
    s.str =str;
    s.int_ = int_;
    s.dex = dex;
    return s;
}


struct inven
{
    int wallet;    
    char bag[20][20]; //캐릭터의 배낭이다. 
    //struct potion 을 구현하고 싶었는데 어떻게 하는지 모르겠다.
};

struct inven set_inven(struct inven i,int wallet, char bag[20][20], struct potion)
{
    i.wallet = wallet;
    i.bag[20][20] = bag[20][20];    
    
}

int main()
{
    /* 
    구조체에대한 설명https://dojang.io/mod/page/view.php?id=571
    주영님의 설명 https://cafe.naver.com/f-e/cafes/28969626/articles/54579?boardtype=L&menuid=777&referrerAllArticles=false
    책 712
    */
    
    // struct sword  set_sword(struct sword s, char s_name[],int damage,int enforce, int attribute, int price,int cri_rate, int mage_rate)
    // {
    //     strcpy(s.name, s_name);
    //     s.damage = damage;
    //     s.enforce= enforce;
    //     s.attribute = attribute;
    //     s.price = price;
    //     s.magic_rate = mage_rate;
    //     s.cri_rate = cri_rate;
    //     return s;
    // }

    struct sword sword1_basic;
    struct sword sword2_longsword;
    struct sword sword3_japanese;
    struct sword sword4_ssaulabi;
    struct sword sword5_sword_Of_Chaos;
    struct sword sword6_world_Best;
    struct sword sword7_s;
    struct sword sword8_operaters;
    // 이름, 공격력, 강화, 속성, 가격, 마법, 치명타 칼을 초기화
    sword1_basic =set_sword(sword1_basic,"기본검", 2,0,0,50,0,0);
    sword2_longsword= set_sword(sword2_longsword,"장검", 10,0,0,500,0,0);
    sword3_japanese= set_sword(sword3_japanese,"일본도", 20,0,0,1000,0,0);
    sword4_ssaulabi= set_sword(sword4_ssaulabi,"싸울아비장검", 40,0,0,0,0,0);
    sword5_sword_Of_Chaos= set_sword(sword5_sword_Of_Chaos,"혼돈의검", 50,0,0,0,0,30);
    sword6_world_Best= set_sword(sword6_world_Best,"천상천하제일무쌍도", 100,0,0,0,0,0);    
    sword7_s= set_sword(sword7_s,"마왕을 멸하는 마검", 50,0,0,0,50,0);
    sword8_operaters=set_sword(sword8_operaters,"운영자검",1111,0,0,0,0,0);

    // struct amor set_amor(struct amor a, char a_name[],int damage_reduction,int damage_reduction_rate, int additional_damge_rate, int price, int mage_rage)
    // {
    //     strcpy(a.name, a_name);
    //     a.damage_reduction = damage_reduction;
    //     a.damage_reduction_rate= damage_reduction_rate;
    //     a.price = price;
    //     a.additional_damge_rate = additional_damge_rate;
    
    //     return a;
    // }
    struct amor amor1_leather;
    struct amor amor2_leather;
    struct amor amor3_leather;
    struct amor amor4_leather;
    struct amor amor5_leather;
    struct amor amor6_leather;
    struct amor amor7_leather;


    return 0;
    
}




    


   