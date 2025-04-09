#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define STATUS_SIZE 4
void print_pika();
int* choose_my_monster();
void show_my_monster();
void show_current_tier();
int check_boss_battle();
int monster_appear(int *,int ,int);
void introduce_apear_monster(int*);
int* battle_boss_monster(int * ,int * ,int );
int* battle_normal_monster(int *, int*, int);
void call_a_song();
int hit_hp(int hp, int ad);
// int* update_status(int *, int ,int);         // 전투 후 복켓몬의 상태를 업데이트한다.
// float calc_exp(my_exp);
bool player_die = false;

int main()
{
    // potion[30] = {1,}; 구문이 안먹어서 울며겨자먹기 타이핑!
    int  potion[30]={1,1,1,1,1,1,1,1,1,1,11,1,1,1,1,1,1,1,1,1,11,1,1,1,1,1,1,1,1,1,1}; //층수 / 포션 유무
    int is_boss=0;
    int cnt_battle=0;
    int c_tier=1;
    char answer;
    int *current_tier;
    int *my_status;                          //mon_name,hp,ad,lv,exp      
    int *nomal_status;   //mon_name,hp,ad,lv,exp  
    
    
    // 몬스터 선택 / 내 포켓몬 상태를 초기화 | 사용자 입력
    my_status = choose_my_monster();    

    // 내 포켓몬 상태 hp 공격력 현재 층수 정보 표출  |bm_hp,bm_ad,bm_exp,tier_lv 4
    show_my_monster(my_status);
    
    while(c_tier <31)
    {      
        
        //플레이어가 죽으면 1층부터 다시간다. status 정보 리셋
        if(player_die)
        {
            c_tier = 1;
            cnt_battle=1;
        }

        show_current_tier(c_tier);
        //이번 전투 횟수 가져와서 보스판인지 확인  bs_mon_name, bs_mon_hp,bs_mon_ad, bs_mon_lv
        cnt_battle+=1;
        is_boss =  monster_appear(my_status,cnt_battle, c_tier); //일반몹 등장 가능성을 이미 처리함
        
        // printf("보스인지 일반인지 보스면 2/일반1/아무것도안나옴0 )%d\n", is_boss);
        
        if(is_boss==2)
        {
            //int *boss_status;    //mon_name,hp,ad,lv,exp  보스 전투도 구현해야함!
            my_status =battle_boss_monster(my_status,potion, c_tier);
            // 보스몬스터 상태계산 메서드, 출현 알림 
        }else if(is_boss==1)
        {
            // 일반 몬스터와 대결후 포션을 사용했으면 다음전투에서 사용불가 potion[c_tier] = 0 ; 처리 하면 됨!
            my_status = battle_normal_monster(my_status,potion,c_tier); 

            //my_status 상태를 다시 확인해보고 
            
            // 그리고 한번더 싸우시겠습니까 사용자 입력을 받아야 한다. - 원하면 한번더 싸움
            printf("다음층으로 올라가시겠습니까? y:다음층 n:전투 ) :\n");
            scanf("%c",&answer);
            getchar();
            if(answer == 'n')
            {
                my_status = battle_normal_monster(my_status,potion,c_tier);  
                // c_tier -=1; 
                c_tier--;
            }
            
        }
        c_tier +=1;        
    }
}

int* battle_normal_monster(int *my_status,int *potion,int c_tier)
{
    int gain_exp,randint;
    int turn=0;
    char answer;
    int levelup=0;   
    char my_monsters[][20]={"이상해씨","파이리","꼬부기","피카츄"};

    char monsters_name[][20]= {"이상해씨","이상해풀","메가리자몽","메가거북왕","메가독침붕","피죤투","아보크","모래두지","니드리나","식스테일","나인테일","골뱃","냄새꼬","파라스","파라섹트","도나리","디그다","닥트리오","페르시온","페르시온","고라파덕","성원숭","슈륙챙이","메가후딘","괴력몬","우츠동","데구리","딱구리","야돈","야도란"};
    
    //일반몬스터 상태 계산 
    randint = (-1 +rand() %5);
    //일반몬스터이다. 내 레벨을 가져와야한다. 
    int mon_lv = my_status[1]+randint;
    // 몬스터의 hp
    int mon_hp = mon_lv*5;
    //공격력
    int mon_ad = mon_lv *0.6;
    int pick = my_status[0];
    int my_lv = my_status[1];
    int init_hp = my_status[2];
    int my_hp = my_status[2];
    int my_ad = my_status[3]; 
    int my_exp = my_status[4]; 
    srand((unsigned int)time(NULL));   

    printf("<<%s 레벨은 %d이며 현재 hp는 %d 공격력은 %d 입니다.>>\n",my_monsters[pick-1],my_lv, my_hp, my_ad);
    printf("<<트레이너의 레벨은 %d이며 현재 hp는 %d 공격력은 %d 입니다.>>\n",c_tier*2, mon_hp*2, mon_ad*2);
    printf("<< %s 의 레벨은 %d이며 현재 hp는 %d 공격력은 %d 입니다.>>\n",monsters_name[c_tier-1],mon_lv, mon_hp, mon_ad);

    while(1)
    {
        printf("===================================================================================\n");
    
        printf("[System!] %d 층의 %d 턴이 시작되었습니다..복켓몬의 렙은 %d 몬스터의 렙은 %d입니다.\n",c_tier, turn +1, my_lv, mon_lv); //추후 시스템 프린트 함수로 묶어서 출력
        printf("===================================================================================\n");

        //굳이 선택지를 넣으려면 여기 넣어야한다.
        printf("행동을 선택하세요.\n");
        printf("1.공격한다 2.물약을 마신다[있다면] 3.기술[있다면]\n");
        scanf("%d", &answer);
        if(answer==2){            
            if(potion[c_tier-1]==0)
            {
                printf("아쉽지만 물약이 없어 아무행동도 하지않습니다 -이번층은 틀렸어\n");
            }else{
                printf("물약을 마십니다.. %d\n", potion[c_tier-1]);            
                my_hp = init_hp;
                potion[c_tier-1]= 0;//으로 초기화
            }
        }else if(answer==3)
        {
            //스킬이 있다면 스킬을 수행!  아직은 아무것도 하지 않는다.
            printf("기술을 시전했으나 아직 게으른 개발자가 머리를짜내지 않았습니다.");
            //아쉬운대로 포켓몬 주제가라도 불러봅니다.
            call_a_song(); 
        }else if(answer==1)
        {
            // user의 hp가 0밑으로 떨어지거나 몬스터의 hp가 0으로 떨어지면 게임 종료
        mon_hp = hit_hp(mon_hp, my_ad);
        printf("[System!] 복켓몬이 상대몬스터에게 %d만큼의 피해를 입혔습니다, 몬스터의 hp는 %d입니다..\n",my_ad,mon_hp); //추후 시스템 프린트 함수로 묶어서 출력
        my_hp = hit_hp(my_hp, mon_ad);
        printf("[System!] 몬스터가 복켓몬 몬스터에게 %d만큼의 피해를 입혔습니다, 복켓몬의 hp는 %d입니다.\n",mon_ad,my_hp);
        printf("===================================================================================\n");        
        
        if(mon_hp<=0)
        {
            //유저가 이긴상황이다.
            printf("유저 복켓몬이 미약한 힘으로 %d 턴만에 상대 몬스터를 제압했습니다. 남은 hp는 %d입니다.\n",turn+1, my_hp);

            // 30~50 렌덤하게 수치를 넣는다. 100이 넘어가면 레벨이 1씩증가하고 나머지를 exp에저장하는 구조가 좋을듯
            gain_exp = (30 +rand() %50);
            printf("[System!] 현재 경험치는 %d이며 획득 경험치는 %d입니다.\n",my_exp, gain_exp);

            if((my_exp+gain_exp)>=100){           
                levelup  = (my_exp+gain_exp) /100; // 레벨업 숫자
                gain_exp = (my_exp+gain_exp) % 100; // 남은 exp    
                printf("[System!] 축하합니다. Level up!\n"); 
                //레벨업 했을때에만 수치의 변화가 생겨야한다. 그 외에는 변화가 있어선 안된다.
                my_status[1] = my_status[1] + levelup;
                my_status[2] = my_status[1] * 25;
                my_status[3] = my_status[1] *3.5;
                my_status[4] = gain_exp;
              
            } else {
                //레벨업을 안한 상태이다.
                levelup = 0;
                my_exp = my_exp + gain_exp;         // 경험치만 추가된상태이다.       
                my_status[4] = my_exp;
            }
            return my_status;

            break;
        }else if(my_hp<=0)
        {
            
            // 사실 포션을 이용해서 부활시켜야할거같다.  c_tier 정보도 리셋해야한다.
            printf("유저 복켓몬이 상대 몬스터에게 %d턴만에 제압당하여 갖고있는 돈과 명예를 모두 잃었습니다 -game over 몬스터의 남은 체력 :%d",turn, mon_hp);
            // 리셋후 게임재시작은 추후구현
            printf("게임을 다시 진행하시겠습니까?");
            scanf("%c", &answer);
            if(answer='y')
            {
                my_status = choose_my_monster();
                c_tier=1; // 
                return my_status;
            }

            break;
        }

        scanf("",&answer); //엔터를 쳐야 턴을 넘기는 기능
        getchar();

        turn++;
        }

        
    }

    return my_status;
}

int hit_hp(int hp, int ad)
{
    int health_point;
    health_point = hp-ad;
    return health_point;
}

int* battle_boss_monster(int *my_status,int *potion,int c_tier)
{
    int gain_exp,randint;
    int turn=0;
    char answer;
    int levelup=0;   

    
    // 보스몬스터레벨= 층*2
    int mon_lv =c_tier *2;
    // 몬스터의 hp
    int mon_hp = mon_lv*7;
    //공격력
    int mon_ad = mon_lv *0.6;      
    char my_monsters[][20]={"이상해씨","파이리","꼬부기","피카츄"};

    char monsters_name[][20]= {"이상해씨","이상해풀","메가리자몽","메가거북왕","메가독침붕","피죤투","아보크","모래두지","니드리나","식스테일","나인테일","골뱃","냄새꼬","파라스","파라섹트","도나리","디그다","닥트리오","페르시온","페르시온","고라파덕","성원숭","슈륙챙이","메가후딘","괴력몬","우츠동","데구리","딱구리","야돈","야도란"};
    int pick =  my_status[0];
    int my_lv = my_status[1];
    int init_hp =my_status[2];
    int my_hp = my_status[2];
    int my_ad = my_status[3]; 
    int my_exp = my_status[4]; 
    srand((unsigned int)time(NULL));
    
    printf("<<%s 레벨은 %d이며 현재 hp는 %d 공격력은 %d 입니다.>>\n",my_monsters[pick-1],my_lv, my_hp, my_ad);
    printf("<<트레이너의 레벨은 %d이며 현재 hp는 %d 공격력은 %d 입니다.>>\n",c_tier*2, mon_hp*2, mon_ad*2);
    printf("<< %s 의 레벨은 %d이며 현재 hp는 %d 공격력은 %d 입니다.>>\n",monsters_name[c_tier-1],mon_lv, mon_hp, mon_ad);
    while(1)
    {     
    
        printf("===================================================================================\n");
    
        printf("[System!] %d 층의 %d 턴이 시작되었습니다..복켓몬의 렙은 %d 몬스터의 렙은 %d입니다.\n",c_tier, turn +1, my_lv, mon_lv); //추후 시스템 프린트 함수로 묶어서 출력
        printf("===================================================================================\n");

        //굳이 선택지를 넣으려면 여기 넣어야한다.
        printf("행동을 선택하세요.\n");
        printf("1.공격한다 2.물약을 마신다[있다면] 3.기술[있다면]\n");
        scanf("%d", &answer);
        if(answer==2){

            if(potion[c_tier-1]==0)
            {
                printf("아쉽지만 물약이 없어 아무행동도 하지않습니다 -이번층은 틀렸어\n");
            }else{
                printf("물약을 마십니다.. %d\n", potion[c_tier-1]);            
                my_hp = init_hp;
                potion[c_tier-1]= 0;//으로 초기화
            }
            // potion 배열의 [c_tier-1]인덱스의 값을 0으로 변경 - 해당층의 물약은 이제없다 다시 마실수 없도록 
        }else if(answer==3)
        {
            //스킬이 있다면 스킬을 수행!  아직은 아무것도 하지 않는다.
            printf("기술을 시전했으나 아직 게으른 개발자가 머리를짜내지 않았습니다.");
             //아쉬운대로 포켓몬 주제가라도 불러봅니다.
            call_a_song(); 
        
        }else if(answer==1)
        {
            // user의 hp가 0밑으로 떨어지거나 몬스터의 hp가 0으로 떨어지면 게임 종료
        mon_hp = hit_hp(mon_hp, my_ad);
        printf("[System!] 복켓몬이 상대몬스터에게 %d만큼의 피해를 입혔습니다, 몬스터의 hp는 %d입니다..\n",my_ad,mon_hp); //추후 시스템 프린트 함수로 묶어서 출력
        my_hp = hit_hp(my_hp, mon_ad);
        printf("[System!] 몬스터가 복켓몬 몬스터에게 %d만큼의 피해를 입혔습니다, 복켓몬의 hp는 %d입니다.\n",mon_ad,my_hp);
        printf("===================================================================================\n");        
        
        
     

        if(mon_hp<=0)
        {
            //유저가 이긴상황이다.
            printf("유저 복켓몬이 미약한 힘으로 %d 턴만에 상대 몬스터를 제압했습니다. 남은 hp는 %d입니다.\n",turn+1, my_hp);

            // 30~50 렌덤하게 수치를 넣는다. 100이 넘어가면 레벨이 1씩증가하고 나머지를 exp에저장하는 구조가 좋을듯
            gain_exp = (30 +rand() %50);
            printf("[System!] 현재 경험치는 %d이며 획득 경험치는 %d입니다.\n",my_exp, gain_exp);

            if((my_exp+gain_exp)>=100){           
                levelup  = (my_exp+gain_exp) /100; // 레벨업 숫자
                gain_exp = (my_exp+gain_exp) % 100; // 남은 exp    
                printf("[System!] 축하합니다. Level up!\n"); 
                //레벨업 했을때에만 수치의 변화가 생겨야한다. 그 외에는 변화가 있어선 안된다.
                my_status[1] = my_status[1] + levelup;
                my_status[2] = my_status[1] * 25;
                my_status[3] = my_status[1] *3.5;
                my_status[4] = gain_exp;
              
            } else {
                //레벨업을 안한 상태이다.
                levelup = 0;
                my_exp = my_exp + gain_exp;         // 경험치만 추가된상태이다.       
                my_status[4] = my_exp;
            }
            return my_status;

            break;
        }else if(my_hp<=0)
        {
            
            // 사실 포션을 이용해서 부활시켜야할거같다.  c_tier 정보도 리셋해야한다.
            printf("유저 복켓몬이 상대 몬스터에게 %d턴만에 제압당하여 갖고있는 돈과 명예를 모두 잃었습니다 -game over 몬스터의 남은 체력 :%d",turn, mon_hp);
            // 리셋후 게임재시작은 추후구현
            printf("게임을 다시 진행하시겠습니까?");
            scanf("%c", &answer);
            if(answer='y')
            {
                my_status = choose_my_monster();
                c_tier=1; // 
                return my_status;
            }

            break;
        }

        scanf("",&answer); //엔터를 쳐야 턴을 넘기는 기능
        getchar();

        turn++;
        }

        
    }
    return my_status;
}
 
//보스 배틀인치 체크해서 보스면 2 일반이면 1 아무것도 없으면 0
int monster_appear(int *mystatus,int cnt_battle,int c_tier)
{    
    
    //check is boss? 
    int cnt;
    int randint;
    cnt = cnt_battle;
    srand((unsigned int)time(NULL));
    randint = rand() %10;
    if(cnt%5 ==0)
    {
        int *boss_status;
        // 보스몬스터이다       

        printf("보스 몬스터가 나타났습니다.\n");
        // printf("레벨은 %d이며 현재 hp는 %d입니다.\n ",boss_status[1],boss_status[2]);
        // printf("공격력은은 %d입니다. \n ", boss_status[3]);

        return 2;
        
    }else{
        //일반몬스터는 50%확율로 등장한다. randint <5
        if(1){
            printf("일반 몬스터가 나타났습니다.\n");
            return 1;
        }else{
            printf("아무것도 나타나지 않았습니다.. 서운한 정적만 감돕니다.\n");
            return 0;
        }        
    }
}

void show_current_tier(int c_tier)
{
    int tier = c_tier;
    printf("현재 %d층 진입했습니다.\n",tier);
    
}

void show_my_monster(int* status)
{
    char monsters[][20]={"이상해씨","파이리","꼬부기","피카츄"};
    
    
    int lv,hp,ad,exp;
    lv=status[1];
    hp=status[2];
    ad=status[3];
    exp=status[4];
    int pick = status[0];
    //내 몬스터의 상태를 보여준다.mon_name,lv,hp,ad,exp 
    printf("현재 육성중인 몬스터는 %s 입니다.\n ",monsters[pick-1]);
    printf("레벨은 %d이며 현재 hp는 %d입니다.\n ", lv, hp);
    printf("공격력은은 %d이며 경험치는는 %d입니다.\n ", ad,exp);
}

int * choose_my_monster()
{
    int static my_status[5];
    int num;

    //사용자입력을 받는다
    printf("몬스터를 선택해주세요 번호입력)\n");
    printf("1.이상해씨\n");
    printf("2.파이리\n");
    printf("3.꼬부기\n");
    printf("4.피카츄\n");
    printf("===========================\n");
    printf("   :) ");

    scanf("%d", &num);
    getchar();
    //mon_name,lv,hp,ad,exp    첫 값 ? lv5 hp50 ad10 

    my_status[0]= num;
    my_status[1] = 5;
    my_status[2] = my_status[1] * 10;
    my_status[3] = my_status[1] * 2;
    my_status[4] = 0;
  
    return my_status;

}

void call_a_song()
{
    //스킬이 있다면 스킬을 수행!  아직은 아무것도 하지 않는다.
    printf("아쉬운대로 포켓몬 주제가 부릅니다.\n");
    printf("우리는 모두 친구\n");
    printf("\n");
    printf("피카츄 라이츄 파이리 꼬부기\n");
    printf("버터플 야도란 피죤투 또가스\n");
    printf("서로 생긴 모습은 달라도 우리는 모두 친구 (맞아)\n");
    printf("\n");
    printf("산에서 들에서 때리고 뒹굴고\n");
    printf("사막에서 정글에서 울다가 웃다가\n");
    printf("서로 만나기까지 힘들었어도 우리는 모두 친구 (피카피카)\n");
    printf("\n");
    printf("울랄랄라 내가 원하는 건 너도 원하고\n");
    printf("마주 잡은 두 손에 맹세해\n");
    printf("힘을 내봐 그래 힘을 내봐\n");
    printf("용기를 내봐 그래 용기를 내봐 \n");
    printf("\n");
    printf("피카피카피카츄 피카피카피카츄\n");
    printf("아름다운 우리 추억 기억해\n");
    printf("\n");
    printf("피카피카피카츄 피카피카피카츄\n");
    printf("너와 나 꿈을 위해\n");
}
