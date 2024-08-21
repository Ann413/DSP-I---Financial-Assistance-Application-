#include<stdio.h>

void TopUpInfo ();
int RewardPoint (char*claimReward, int point);
double NormalPlan ();
void FokusPlan (double*cost);
void personalPostpaidPlan ();
double FamilyPlan (int*postpaidType);
void FamilyBundle (int familyUnlimitedBundle);
char AddOns ();


char *internet, *hotspot, *planName, *boosterPromo,*postPaidPlan, redeem, specialPlan, *dayName, claimReward, wishReward;
char  name[20], addOns, *add_ons, *fibreName, *validity, *familyLines;
int prepaidType[5], fokusPlan[5], topUp[5], point, reward, postpaidType[5], customer, purchase, i, j;
int addOnsPlan[5], fibre, familyUnlimitedBundle, input[3], exit, rpoint;
double cost, balance, total_balance, totalAmount, addOnsCost;


int main()
{
    int phoneNum[customer][purchase][30];

    printf("Number of customer: ");
    scanf("%d", &customer);


       for (i=0; i<customer; i++){

            fflush(stdin);
            FILE *info = fopen ("userInfo.txt", "w");

            if (info == NULL){
                printf("\nFile does not exists\n");
                return;}

            printf("\nCustomer %d \n", i+1);
            fprintf(info, "\nCustomer %d", i+1);

            fflush(stdin);
            printf("\nEnter your name: ");
            gets(name);
            fprintf(info, "\nName: %s", name);

            printf("Purchase how many time for internet plan: ");
            scanf("%d", &purchase);

            fclose(info);

            fflush(stdin);
            for (j=0; j<purchase; j++){

                printf("\nEnter phone number %d: ", j+1);
                scanf("%s", &phoneNum[i][j]);}

            fflush(stdin);


    for(j=0; j<purchase; j++){

    printf("\nPhone Number %d: %s\n", j+1, phoneNum[i][j]);

    printf("\nEnter Type of plan [1: Prepaid, 2: PostPaid]: ");
    scanf("%d", &input[1]);

    if (input[1] == 1){ // Top-up amount, validity and reward point

        printf("\nEnter your amount of top-up\n1-RM5\n2-RM10\n3-RM15\n4-RM20\n5-RM30\n6-RM50\n7-RM100\n8-RM200 : ");
        scanf("%d",&topUp[1]);

        TopUpInfo ();

        printf("\nRewards points:%d\n",point);


        fflush(stdin);

        RewardPoint (&claimReward, point);

        planName = "PrePaid";

        printf("\nAre you using Fokus Plan? [y:Yes, n:No]: ");
        scanf(" %c", &specialPlan);

        fflush(stdin);
        if (specialPlan == 'n' || specialPlan=='N'){ // normal internet plan (prepaid)

            printf("\nSelect Periodical [1:Daily, 2:Weekly, 3:Monthly, 4:Yearly]: ");
            scanf("%d", &prepaidType[3]);

            NormalPlan ();}


        fflush(stdin);
        if (specialPlan == 'y' || specialPlan == 'Y') { // fokus plan (prepaid)

            printf("\nSelect Fokus Plan [1: Fokus 33, 2: Fokus 40, 3: Bebas 55]: ");
            scanf("%d", &fokusPlan[2]);

            FokusPlan (&cost);}}


        fflush(stdin);

    if (input[1] == 2){ //postpaid plan

        printf("\nPlease enter your plan [1:Personal plans, 2:Family plan, 3:Family Unlimited Bundle]: ");
        scanf("%i",&postpaidType[3]);


        if(postpaidType[3]==1){

            printf("\nPlease enter the package you want [1:PostPaid 40, 2:PostPaid 60, 3:PostPaid 90, 4:PostPaid 120, 5:PostPaid 150]: ");
            scanf("%i",&postpaidType[1]);
            personalPostpaidPlan ();}


        else if ( postpaidType[3] == 2 ){

            printf("\nPlease enter your plan [1:Family 20, 2:Family 30, 3:Family 40]: ");
            scanf("%i",&postpaidType[2]);
            FamilyPlan (&postpaidType);}


        else {
            printf("\nPlease enter your Family lines\n1:Family lines 3\n2:Family lines 4\n3:Family lines 5\n4:Family lines 6\n5:Family lines 7 : ");
            scanf("%i",&familyUnlimitedBundle);

            FamilyBundle (familyUnlimitedBundle);}}


        AddOns ();



        // output
        info = fopen("userInfo.txt", "r");
        char line[200];
        fflush(stdin);
        while(!feof(info)){
            fgets(line, 200, info);
            puts(line);}
        fclose(info);
        printf("\nPhone Number %d: %s\n", j+1, phoneNum[i][j]);

        if (input[1] == 1){

            printf("Type of Plan = %s\n", planName);
            printf("Total Amount of Top-up = RM%d\n", topUp[2]);
            printf("Validity days: %s\n", validity);
            printf("Total Reward point = %d\n", rpoint);


            totalAmount = cost + addOnsCost;
            balance = topUp[2] - totalAmount;

            printf("Periodical = %s \n", dayName);
            printf("Internet = %s\n", internet);
            fflush(stdin);
            if(fokusPlan[2] == 1 || fokusPlan[2] == 2 || fokusPlan[2] == 3 || prepaidType[1] == 5 || prepaidType[1] == 6 || prepaidType[1] == 7){
                printf("Hotspot = %s\n", hotspot);}
            if(fokusPlan[2] == 1 || fokusPlan[2] == 2 ||fokusPlan[2] == 3 ){
                printf("Booster Promotion = %s\n", boosterPromo);}
            if(addOns == 'y' || addOns == 'Y'){
                printf("Add-Ons Package = %s\n", add_ons);
                printf("Add-Ons Internet = %s\n", internet);
                printf("Add-Ons Validity = %s\n", validity);}

            printf("Total Cost = RM%.2lf \n", totalAmount);
            printf("Balance = RM%.2lf\n", balance);

            while(balance<0){

                printf("\nYour balance is insufficient");
                printf("\nEnter your amount of top-up\n1-RM5\n2-RM10\n3-RM15\n4-RM20\n5-RM30\n6-RM50\n7-RM100\n8-RM200 : ");
                scanf("%d",&topUp[1]);
                TopUpInfo ();
                balance = balance + topUp[2];
                printf("Balance = RM%.2lf\n", balance);
                fflush(stdin);}
        }

        if (input[1] == 2){

                totalAmount = cost + addOnsCost;
                if (postpaidType[3] == 1 || postpaidType[3] == 2){

                printf("\nPostPaid Package = %s\n", postPaidPlan);
                printf("Internet = %s\n", internet);

                if(addOns == 'y' || addOns == 'Y'){
                printf("Add-Ons Package = %s\n", add_ons);
                printf("Add-Ons Internet = %s\n", internet);
                printf("Add-Ons Validity = %s\n", validity);}

                printf("Total amount that needs to be paid = RM%.2lf\n", totalAmount);}

            else {

                printf("\nPostPaid Package = %s\n", familyLines);
                printf("Fibre = %s\n", fibreName);

                if(addOns == 'y' || addOns == 'Y'){
                printf("Add-Ons Package = %s\n", add_ons);
                printf("Add-Ons Internet = %s\n", internet);
                printf("Add-Ons Validity = %s\n", validity);}

                printf("Total amount that needs to be paid = RM%.2lf\n", totalAmount);}}



    }}



    return 0;}


    void TopUpInfo (){

        if(topUp[1] == 1){
            topUp[2] = 5;
            validity = "5 days";
            point = 8;}
        else if (topUp[1] == 2){
            topUp[2] = 10;
            validity = "10 days";
            point=20;}
        else if (topUp[1] == 3){
            topUp[2] = 15;
            validity = "20 days";
            point=30;}
        else if (topUp[1] == 4){
            topUp[2] = 20;
            validity = "20 days";
            point=40;}
        else if (topUp[1] == 5){
            topUp[2] = 30;
            validity = "30 days";
            point=70;}
        else if (topUp[1] == 6){
            topUp[2] = 50;
            validity = "50 days";
            point=120;}
        else if (topUp[1] == 7){
            topUp[2] = 100;
            validity = "100 days";
            point=240;}
        else if (topUp[1] == 8){
            topUp[2] = 200;
            validity = "200 days";
            point=480;}
        else {
            printf("Invalid");}}

    int RewardPoint (char*claimReward, int point){

        if (point >= 100){

        printf("\nDo you want to claim your reward (y-yes,n-No): "); // claim reward points
        scanf(" %c",&*claimReward);}

        if (*claimReward=='Y' || *claimReward=='y'){
        if (point>=100)
        {
            printf("\nReward:\n1-300MB valid for 1 day\n2-3 days validity(valid for 3 days)\n3-Unlimited Calls(valid for 1 day)\n");
            printf("\nDo you want to claim your reward (y-yes,n-No): ");
            scanf(" %c",&wishReward);
        if (wishReward=='y')
        {   printf("\nChoose your reward: ");
            scanf("%d",&reward);
            rpoint=point-100;
        }
        }
        if(point>=150 && wishReward == 'n')
        {
            printf("\n4-Get 35% OFF and 35% cashback for bus and ferry ticket when using ‘RedBus’ app\n5-Get 10% OFF with minimum purchase RM50 capped at RM8 when using ‘YouBeli'app\n");
            printf("\nDo you want to claim your reward (y-yes,n-No): ");
            scanf(" %c",&wishReward);
        if (wishReward=='y')
        {   printf("\nChoose your reward: ");
            scanf("%d",&reward);
            rpoint=point-150;
        }
        }
        if(point>=200 && wishReward == 'n')
        {
            printf("\n6-Get 10% OFF total bill at ‘NinJaz’ store\n7-Get RM5 OFF with minimum spend RM50 when purchase at ‘Caring’ Pharmacy\n");
            printf("\nDo you want to claim your reward (y-yes,n-No): ");
            scanf(" %c",&wishReward);
        if (wishReward=='y')
        {   printf("\nChoose your reward: ");
            scanf("%d",&reward);
            rpoint=point-200;
        }
        }
        if(point>=300 && wishReward == 'n')
        {
            printf("\n8-Enjoy RM8 OFF storewide for a minimum spend of RM80 at Pensonic online\n9-Enjoy 10% off your total bill at Tealive\n10-Can switching to Fokus plan\n");
            printf("\nDo you want to claim your reward (y-yes,n-No): ");
            scanf(" %c",&wishReward);
        if (wishReward=='y')
        {   printf("\nChoose your reward: ");
            scanf("%d",&reward);
            rpoint=point-300;
        }
        }
        if(point>=500 && wishReward == 'n')
        {
            printf("\n11-2GB valid for 3 days\n12-10GB YouTube valid for 1 day\n");
            printf("\nDo you want to claim your reward (y-yes,n-No): ");
            scanf(" %c",&wishReward);
        if (wishReward=='y')
        {   printf("\nChoose your reward: ");
            scanf("%d",&reward);
            rpoint=point-500;
        }
        }
        if(point>=2000 && wishReward == 'n')
        {
            printf("\n13GB valid for 15 days\n");
            printf("\nDo you want to claim your reward (y-yes,n-No): ");
            scanf(" %c",&wishReward);
        if (wishReward=='y')
        {
            rpoint=point-2000;
        }
        }
        if(point>=3000 && wishReward == 'n')
        {
            printf("\n14-1 year validity\n");
            printf("\nDo you want to claim your reward (y-yes,n-No): ");
            scanf(" %c",&wishReward);
        if (wishReward=='y')
        {
            rpoint=point-3000;
        }
        }
        if(point>=10000 && wishReward == 'n')
        {
            printf("\n15-120GB Data (10GB/month) valid for 1 year\n");
            printf("\nDo you want to claim your reward (y-yes,n-No): ");
            scanf(" %c",&wishReward);
        if (wishReward=='y')
        {
            rpoint=point-10000;}}}

    return reward;}

    double NormalPlan (){

            if (prepaidType[3] == 1){
                dayName = "Daily";
                internet = "500MB";
                cost = 1;}
            else if (prepaidType[3] == 2){
                dayName = "Weekly";
                internet = "Unlimited";
                cost = 12;}
            else if (prepaidType[3] == 3){
                dayName = "Monthly";
                printf("\nSelect monthly package\n[1: 3GB\n2: 10GB\n3: 30GB\n4: 35GB\n5: Unlimited Internet with 3GB hotspots\n6: Unlimited Internet with 5GB hotspots\n7: Unlimited Internet with 18GB hotspots]: ");
                scanf("%d", &prepaidType[1]);
                if (prepaidType[1] == 1){
                    internet = "3GB";
                    cost = 15;}
                else if (prepaidType[1] == 2){
                    internet = "10GB";
                    cost = 20;}
                else if (prepaidType[1] == 3){
                    internet = "30GB";
                    cost = 30;}
                else if (prepaidType[1] == 4){
                    internet = "35GB";
                    cost = 35;}
                else if (prepaidType[1] == 5){
                    internet = "Unlimited";
                    hotspot = "3GB";
                    cost = 38;}
                else if (prepaidType[1] == 6){
                    internet = "Unlimited";
                    hotspot = "5GB";
                    cost = 48;}
                else {
                    internet = "Unlimited";
                    hotspot = "18GB";
                    cost = 68;}}
            else{

                dayName = "yearly";
                printf("\nSelect yearly package [1:2GB/month, 2:10GB/month]: ");
                scanf("%d", &prepaidType[2]);

                if (prepaidType[2] == 1){
                    internet = "2GB";
                    cost = 99;}
                else {
                    internet = "10GB";
                    cost = 200;}}

        return cost;}

        void FokusPlan (double*cost){

            if(fokusPlan[2] == 1){

                dayName = "Monthly";
                printf("\nSelect plan [1: RM33/12 months, 2: RM35/3 months, 3: RM38/1 month]: ");
                scanf("%d", &fokusPlan[1]);
                boosterPromo = "10GB";
                internet = "Unlimited";
                hotspot = "4GB";

                if (fokusPlan[1] == 1){
                    *cost = 33*12;}
                else if (fokusPlan[1] == 2){
                    *cost = 35*3;}
                else {
                    *cost = 38;}}

            else if (fokusPlan[2] == 2){

                dayName = "Monthly";
                printf("\nSelect plan [4: RM40/12 months, 5: RM43/3 months, 6: RM48/1 month]: ");
                scanf("%d", &fokusPlan[1]);
                boosterPromo = "20GB";
                internet = "Unlimited";
                hotspot = "6GB";

                if (fokusPlan[1]== 4){
                    *cost = 40*12;}
                else if (fokusPlan[1] == 5){
                    *cost = 43*3;}
                else {
                    *cost = 48;}}

           else {

                fflush(stdin);
                dayName = "Monthly";
                printf("\nSelect plan [7: RM55/12 months, 8: RM60/3 months, 9: RM68/1 month]: ");
                scanf("%d", &fokusPlan[1]);
                boosterPromo = "20GB";
                internet = "Unlimited";
                hotspot = "Unlimited";

                if (fokusPlan[1] == 7){
                    *cost = 55*12;}
                else if (fokusPlan[1] == 8){
                    *cost = 60*3;}
                else {
                    *cost = 68;}}}

        void personalPostpaidPlan (){

            if(postpaidType[1]==1){
                cost=40;
                internet="30GB";
                postPaidPlan = "PostPaid 40";}
            else if(postpaidType[1]==2){
                cost=60;
                internet="50GB";
                postPaidPlan = "PostPaid 60";}
            else if(postpaidType[1]==3){
                cost=90;
                internet= "60GB";
                postPaidPlan = "PostPaid 90";}
            else if(postpaidType[1]==4){
                cost=120;
                internet= "105GB";
                postPaidPlan = "PostPaid 120";}
            else{
                cost=150;
                internet="135GB";
                postPaidPlan = "PostPaid 150";}}

        double FamilyPlan (int*postpaidType){

            if(postpaidType[2]==1){
                cost=20;
                internet= "10GB";
                postPaidPlan = "Family 20";}
            else if(postpaidType[2]==2){
                cost=30;
                internet= "25GB";
                postPaidPlan = "Family 30";}
            else{
                cost=45;
                internet= "50GB";
                postPaidPlan = "Family 40";}
        return cost;}

        void FamilyBundle (int familyUnlimitedBundle){

            if(familyUnlimitedBundle == 1){

                familyLines = "Family Lines 3";
                printf("\nSelect Fibre [1:100Mbps, 2:500Mbps, 3:1000Mbps]: ");
                scanf("%d", &fibre);

                if (fibre == 1){
                   fibreName = "100Mbps";
                   cost = 290;}
                else if (fibre == 2){
                   fibreName = "500Mbps";
                   cost = 330;}
                else {
                    fibreName = "1000Mbps";
                    cost = 430;}}

            else if (familyUnlimitedBundle == 2){

                familyLines = "Family Lines 4";
                printf("\nSelect Fibre [1:100Mbps, 2:500Mbps, 3:1000Mbps]: ");
                scanf("%d", &fibre);

                if (fibre == 1){
                   fibreName = "100Mbps";
                   cost = 335;}
                else if (fibre == 2){
                   fibreName = "500Mbps";
                   cost = 375;}
                else {
                    fibreName = "1000Mbps";
                    cost = 475;}}

            else if (familyUnlimitedBundle == 3){

                familyLines = "Family Lines 5";
                printf("\nSelect Fibre [1:100Mbps, 2:500Mbps, 3:1000Mbps]: ");
                scanf("%d", &fibre);

                if (fibre == 1){
                   fibreName = "100Mbps";
                   cost = 380;}
                else if (fibre == 2){
                   fibreName = "500Mbps";
                   cost = 420;}
                else {
                    fibreName = "1000Mbps";
                    cost = 520;}}

            else if (familyUnlimitedBundle == 4){

                familyLines = "Family Lines 6";
                printf("\nSelect Fibre [1:100Mbps, 2:500Mbps, 3:1000Mbps]: ");
                scanf("%d", &fibre);

                if (fibre == 1){
                   fibreName = "100Mbps";
                   cost = 425;}
                else if (fibre == 2){
                   fibreName = "500Mbps";
                   cost = 465;}
                else {
                    fibreName = "1000Mbps";
                    cost = 565;}}

            else {

                familyLines = "Family Lines 7";
                printf("\nSelect Fibre [1:100Mbps, 2:500Mbps, 3:1000Mbps]: ");
                scanf("%d", &fibre);

                if (fibre == 1){
                   fibreName = "100Mbps";
                   cost = 470;}
                else if (fibre == 2){
                   fibreName = "500Mbps";
                   cost = 510;}
                else {
                    fibreName = "1000Mbps";
                    cost = 610;}}}

     char AddOns (){

        printf("\nDo you want to Add-ons? [y:Yes, n:No]: ");
        scanf(" %c", &addOns);

        fflush(stdin);
        if (addOns == 'y' || addOns == 'Y') { // Add-Ons plan (prepaid)

            printf("\nSelect Add-Ons Plan [1: Boosters, 2: Hotspots]: ");
            scanf("%d", &addOnsPlan[2]);

            if(addOnsPlan[2] == 1){

                add_ons = "Boosters";
                printf("\nSelect Internet [1:1GB, 2:1.5GB, 3:10GB]: ");
                scanf("%d", &addOnsPlan[1]);

                if (addOnsPlan[1] == 1){
                    internet = "1GB";
                    validity = "1 hours";
                    addOnsCost = 1;}
                else if (addOnsPlan[1] == 2){
                    internet = "1.5GB";
                    validity = "1 day";
                    addOnsCost = 3;}
                else {
                    internet = "10GB";
                    validity = "7 days";
                    addOnsCost = 10;}}

           else {

                printf("\nSelect Internet [4:60GB, 5:100GB, 6:1000GB]: ");
                scanf("%d", &addOnsPlan[1]);
                add_ons = "Hotspot";

                if (addOnsPlan[1] == 4){
                    internet = "60GB";
                    validity = "1 hours";
                    addOnsCost = 1;}
                else if (addOnsPlan[1] == 5){
                    internet = "100GB";
                    validity = "1 day";
                    addOnsCost = 3;}
                else {
                    internet = "1000GB";
                    validity = "7 days";
                    addOnsCost = 10;}}}

    return validity;}

