#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>

typedef struct{
    int s;
    char item[200];
    int instock;
    float price;
    char product_id[200];
}product;

product prod[20];

typedef struct{
    char name[200];
    long long contact;
    char date[20];
    int amount;
}dealer;

dealer buy[20];

typedef struct{
    int purchased;
    char product_id[200];
}product_history;

void addproduct();
void buyproduct();
void viewproducts();
void purchase_history();

int main(){
    char id[200];
    puts("Enter your ID");
    fgets(id,sizeof(id),stdin);
    if(id[0]=='2' && id[1]=='4' && id[2]=='0' && id[3]=='1'){
        printf("VERIFIED.\n");
        goto point;
    }
    else{
        printf("NOT VERIFIED");
            return 0;
    }
    point:
    puts("------------------------------------");
    puts("INVENTORY MANAGEMENT SYSTEM");
    puts("------------------------------------");
    puts("Which operation would you like to perform");
    puts("------------------------------------");
    int c=0;
    while(c!=5){
        puts("                                 ");
        printf("1.Add Products.\n");
        printf("2.Buy Products.\n");
        printf("3.View Product\n");
        printf("4.Purchase History\n");
        printf("5.Exit\n");
        printf("Enter choice: ");
        scanf("%d",&c);
        switch(c){
            case 1: addproduct(); break;
            case 2: buyproduct(); break;
            case 3: viewproducts(); break;
            case 4: purchase_history(); break;
            case 5: printf("--------------------\nExited successfully\n--------------------"); break;
            default: printf("-----------------\nEnter valid input.\n-----------------\n");
        }
    }
    return 0;
}

void addproduct(){
    int num;
    puts("------------------------------------");
    printf("Enter number of products you wish to add: ");
    scanf("%d",&num);
    puts("------------------------------------");
    FILE *fp=fopen("inventory.txt","a");
    if (fp == NULL) {
        puts("error occurred");
        return;
    }
    //5 prods add
    for(int i=0;i<num;i++){
        printf("Enter S.no: ");
        scanf("%d",&prod[i].s);
        printf("Enter the quantity of product %d: ",i+1);
        scanf("%d",&prod[i].instock);
        getchar();
        printf("Enter the name for %d: ",i+1);
        fgets(prod[i].item,sizeof(prod[i].item),stdin);
        printf("Enter the price for %d: ",i+1);
        scanf("%f",&prod[i].price);
        getchar(); //newline remove \n
        printf("Enter the product_id for %d: ",i+1);
        fgets(prod[i].product_id,sizeof(prod[i].product_id),stdin);
        puts("------------------------------------");
        fprintf(fp,"Product Name: %s\n",prod[i].item);
        fprintf(fp,"S.no: %d\n",prod[i].s);
        fprintf(fp,"Quantity: %d\n",prod[i].instock);
        fprintf(fp,"Price: %.2f\n",prod[i].price);
        fprintf(fp,"Product ID: %s\n",prod[i].product_id);
        fprintf(fp,"--------------------------\n");
    }
    printf("-------------------------------\nPRODUCTS ADDED SUCCESSFULLY\n-------------------\n");
        fclose(fp);
    }
    
void viewproducts(){
    FILE *ptr;
    char ch;
    ptr=fopen("inventory.txt","r");
    if(ptr==NULL) puts("Error\n");
    puts("-----------THE PRODUCTS IN THE INVENTORY-------------");
    while((ch=fgetc(ptr))!=EOF){
        putchar(ch);
    }
    puts("");
    puts("--------------END OF LIST-------------");
    puts("would you like to purchase a product?");
    int ce;
    puts("Enter 1 if yes and 0 if no:");
    scanf("%d",&ce);
    if(ce==1) buyproduct();
    else return ;
    fclose(ptr);
}

void buyproduct(){
    int ms;
    int choice;
    int num;
    int count=0;
    bool found=false;
    FILE *pt = fopen("inventory.txt", "r");
    while (!feof(pt) && count < 20) {
        fscanf(pt, " Product Name: %[^\n]\n", prod[count].item);
        fscanf(pt, " S.no: %d\n", &prod[count].s);
        fscanf(pt, " Quantity: %d\n", &prod[count].instock);
        fscanf(pt, " Price: %f\n", &prod[count].price);
        fscanf(pt, " Product ID: %[^\n]\n", prod[count].product_id);
        fscanf(pt, "\n--------------------------\n");
        count++;
    }
    fclose(pt);
    FILE *ptr=fopen("inventory.txt","r+");
    p:
    printf("Enter the serial number of the product you'd like to purchase: ");
    scanf("%d",&ms);
    printf("Enter the number of the products you'd like to purchase: \n");
    scanf("%d",&num);
    getchar();
    for(int i=0;i<20;i++){
        fscanf(ptr," Product Name: %[^\n]\n", prod[i].item);
        fscanf(ptr," S.no: %d\n", &prod[i].s);
        fscanf(ptr," Quantity: %d\n", &prod[i].instock);
        fscanf(ptr," Price: %f\n", &prod[i].price);
        fscanf(ptr," Product ID: %[^\n]\n", prod[i].product_id);
        fscanf(ptr,"\n--------------------------\n");
        count++;
        if(prod[i].s==ms){
            found=true;
            if(prod[i].instock==0){
                printf("product not available\n");
                return ;
            }
            else if(prod[i].instock<num){ printf("%d items are not available",num); return;}
            else{
                printf("Product is: %s",prod[i].item);
                puts("");
                printf("Price of the Product is: %.2f",prod[i].price);
                puts("");
                printf("Product id is: %s",prod[i].product_id);
                puts("");
                printf("Is this the product you would like to purchase.\n");
                puts("Print 1 if yes and 0 if no");
                scanf("%d",&choice);
                getchar();
                if(choice==1){
                    puts("Enter today's Date: ");
                    fgets(buy[i].date,sizeof(buy[i].date),stdin);

                    puts("Enter Your name: ");
                    fgets(buy[i].name,sizeof(buy[i].name),stdin);

                    puts("Enter Your Contact Number: ");
                    scanf("%lld",&buy[i].contact);

                    puts("Product purchased successfully");
                    prod[i].instock-=num;
                    printf("updated stock is : %d\n",prod[i].instock);

                    FILE *fp = fopen("inventory.txt", "w");
                    for(int i=0;i<count;i++) {
                    fprintf(fp,"Product Name: %s\n", prod[i].item);
                    puts("");
                    fprintf(fp,"S.no: %d\n", prod[i].s);
                    fprintf(fp,"Quantity: %d\n", prod[i].instock);
                    fprintf(fp,"Price: %.2f\n", prod[i].price);
                    fprintf(fp,"Product ID: %s", prod[i].product_id);
                    fprintf(fp,"--------------------------\n");
                    }
                    fclose(fp);

                    FILE *fpr=fopen("history.txt","a");
                    fprintf(fpr,"\n---------------------------------\n");
                    fprintf(fpr,"Name of the product: %s\n",prod[i].item);
                    fprintf(fpr,"Id of the product: %s\n",prod[i].product_id);
                    fprintf(fpr,"price of the product: %f\n",prod[i].price);
                    fprintf(fpr,"Name of dealer: %s\n",buy[i].name);
                    fprintf(fpr,"contact details of the dealer: %lld\n",buy[i].contact);
                    fprintf(fpr,"Date of the purchase: %s\n",buy[i].date);
                    fclose(fpr);

                }
                else goto p;
            } 
            break;      
        }
    } 
    if(!found){
        puts("Product not available");
        puts("-------------------------");
        goto p;
    }
    fclose(ptr);

}
void purchase_history(){
    FILE *p=fopen("history.txt","r+");
    char ch;
    while((ch=fgetc(p))!=EOF){
        putchar(ch);
    }
    puts("-------------------------------");
    puts("END");
    fclose(p);
}