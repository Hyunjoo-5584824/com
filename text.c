#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STR_LEN 255
#define MAX_MEMBER 1024

struct Member{
   char name[MAX_STR_LEN];
   int age;
   char email[MAX_STR_LEN];
};

int member_num = 0;

void register_member(struct Member *member_list);
void member_edit(struct Member *member_list);
void member_remove(struct Member *member_list);
void all_member_list(struct Member *member_list);
int searching_name(struct Member *member_list, char name);
int read_line(char str[], int n);

int main(int argc, char *argv[]){
   
   struct Member *member_list[MAX_MEMBER];
   int num_input;
   
   for(;;){
      
      printf("1. \n2. \n3. \n4. \n5.\n�Է��ϼ���>");
      scanf("%d", &num_input);
      
      switch(num_input){
         case 1:
            register_member(*member_list);
            break;
         case 2:
            member_edit(*member_list);
            break;
         case 3:
            member_remove(*member_list);
            break;
         case 4:
            all_member_list(*member_list);
            break;
         case 5:
            printf("�����մϴ�.\n\n");
            return 0;
         default:
            fprintf(stderr, "��ȿ���� ���� ������.\n\n");
            break;
      }
      
   }
      
}


void register_member(struct Member *member_list){
   FILE *fp;
   
   char 
   
   fp = fopen("manage.txt", "a");
   if(fp == NULL){
      fprintf(stderr, "��������\n");
      exit(0);
   }
   char ch;
   int result;
   
   do
   {
      printf("�̸�: ");
      read_line(member_list[member_num].name, sizeof(member_list[member_num].name));
      //gets(member_list[member_num].name);
      //fputs(member_list[member_num].name, fp);
      //fgets(member_list[member_num].name, MAX_STR_LEN), fp);
      
      printf("����: ");
      scanf("%d", &member_list[member_num].age); 
      
      printf("�̸���: ");
      read_line(member_list[member_num].email, sizeof(member_list[member_num].email));
      
      fprintf(fp, "%s %d %s", member_list[member_num].name, member_list[member_num].age, member_list[member_num].email);
      member_num++;
      
      printf("��� �Է� �ұ��? ");
      scanf("c", &ch);
      getchar() != '\n';
      
      if(ch == 'Y'){
         result = 1;
      }
      else if(ch == 'N'){
         result = 0;
      }
      
   }
   while(result);
   
   if(ch == 'N'){
      printf("�Է��� �Ϸ�Ǿ����ϴ�.\n");
   }
   
   printf("\n");
   
   fclose(fp);

}

void member_edit(struct Member *member_list){
   FILE *fp;
   fp = fopen("manage.txt", "");
   if(fp == NULL){
      fprintf(stderr, "��������\n");
      exit(0);
   }
   
   char input_name[MAX_STR_LEN];
   
   printf("�������̸�: ");
   scanf("%s", input_name);
   
   int name_index = searching_name(member_list, *input_name);
   //fseek���� ������ ��ġ �����ϰ� ���̸�ŭ �����ϰ�(member_remove �ҷ��͵� �ɵ�) ���ڸ��� �߰��ϱ�. �������� �ٽ� ���ڸ��� �̵�. 
   
   if(name_index != -1 && name_index >= 0){
      printf("�����%s ����\n", input_name);
      
      printf("�̸�: ");
      read_line(member_list[member_num].name, sizeof(member_list[member_num].name));
      
      printf("����: ");
      scanf("%d", &member_list[member_num].age); 
      
      printf("�̸���: ");
      read_line(member_list[member_num].email, sizeof(member_list[member_num].email));
      
      fprintf(fp, "%s %d %s", member_list[member_num].name, member_list[member_num].age, member_list[member_num].email);
   
      printf("�����Ϸ�\n"); 
   } 
   
   printf("\n");
   
   fclose(fp);
}


void member_remove(struct Member *member_list){
   
   FILE *fp;
   fp = fopen("manage.txt", "r+");
   if(fp == NULL){
      fprintf(stderr, "��������\n");
      exit(0);
   }
   
   char input_name[MAX_STR_LEN];
   
   printf("�������̸�: ");
   scanf("%s", input_name);
   
   int name_index = searching_name(member_list, *input_name);
   //�굵 fseek���� �ؾߵǳ� 
   
   //���ϻ���? ��� ����?
   //member_list[name_index] = NULL;
   
   printf("\n");
}


void all_member_list(struct Member *member_list){
   FILE *fp;
   fp = fopen("manage.txt", "r");
   if(fp == NULL){
      fprintf(stderr, "��������\n");
      exit(0);
   }
   
   for(int i = 0; i < member_num; i++){
      printf("%s / %d / %s\n", member_list[i].name, member_list[i].age, member_list[i].email);
   }
   
   printf("\n");
   
   fclose(fp);
   
}


int searching_name(struct Member *member_list, char input_name){
   
   for(int i = 0; i < member_num; i++){
      if(strcmp(member_list[i].name, &input_name)){
         return i;
      }
      else{
         fprintf(stderr, "��Ͼȵ� ȸ��\n");
         return -1;
      }
   }
   
}


int read_line(char str[], int n){
   int c, i = 0;
   while(isspace(c = getchar()));
   while(c != '\n' && c != EOF){
      if(i < n)
         str[i++] = c;
      c = getchar();
   }
   str[i] = '\0';
   return i;
}


