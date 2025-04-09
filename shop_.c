
    // system("clear");
    printf("\t\t\t현재 보유금액: %d\n",user_money);
    printf("구매하실 물건의 카테고리를 선택하세요\n\n");
    printf("1. 무기\n2. 갑옷\n3. 신발\n4. 장갑\n5. 망토\n6. 투구\n7. 물약\n8. 귀환서\n**이동 키 눌러 나가기**\n");
    scanf("%d",&shop_list_choice);
    system("clear");

    while(1)
    {
        if (shop_list_choice == 1){  //무기
            for (int i = 0; i< 3; i++){
                printf("%d. %s:\t\t(%d GOLD)\n",i,shop_list[i],shop_price[i]);
            }
        }
        else if (shop_list_choice == 2){ //갑옷
            for (int i = 3; i< 5; i++){
                printf("%d. %s:\t\t(%d GOLD)\n",i,shop_list[i],shop_price[i]);
            }
        }
        else if (shop_list_choice == 3){
            for (int i = 5; i< 7; i++){
                printf("%d. %s:\t\t(%d GOLD)\n",i,shop_list[i],shop_price[i]);
            }
        }
        else if (shop_list_choice == 4){
            for (int i = 7; i< 9; i++){
                printf("%d. %s:\t\t(%d GOLD)\n",i,shop_list[i],shop_price[i]);
            }
        }
        else if (shop_list_choice == 5){
            for (int i = 9; i< 11; i++){
                printf("%d. %s:\t\t(%d GOLD)\n",i,shop_list[i],shop_price[i]);
            }
        }
        else if (shop_list_choice == 6){
            for (int i = 11; i< 13; i++){
                printf("%d. %s:\t\t(%d GOLD)\n",i,shop_list[i],shop_price[i]);
            }
        }        
        else if (shop_list_choice == 7){
            for (int i = 13; i< 21; i++){
                printf("%d. %s:\t\t(%d GOLD)\n",i,shop_list[i],shop_price[i]);
            }
        }
        else if (shop_list_choice == 8){
            for (int i = 21; i< 23; i++){
                printf("%d. %s:\t\t(%d GOLD)\n",i,shop_list[i],shop_price[i]);
            }
        }
        else
            break;
        printf("\n구매하실 상품의 번호를 입력하세요: (나가기: 23)");
        scanf("%d",&item_choice);
        
        if (item_choice ==23){
            break;
        }
        if (item_choice < 0 || item_choice >= 23) {
            printf("유효하지 않은 번호입니다.\n");
            continue;
        }

        printf("수량을 입력하세요: ");
        scanf("%d",&item_count);


        if ((shop_price[item_choice])*item_count > user_money)
            printf("잔액이 부족합니다.\n");
        else{
            printf("%s %d개 구매하였습니다.\n\n",shop_list[item_choice],item_count);
            user_money -= (shop_price[item_choice])*item_count;
            printf("현재 보유금액: %d\n",user_money);
        }

        printf("더 구매 하시겠습니까?: \n0.예\n1.아니오\n");
        scanf("%d",&quit_shop);
        if (quit_shop == 1)
        {
            break;
        }               
    }