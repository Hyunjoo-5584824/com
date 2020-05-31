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
      
      printf("1. \n2. \n3. \n4. \n5.\n입력하세요>");
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
            printf("종료합니다.\n\n");
            return 0;
         default:
            fprintf(stderr, "유효하지 않은 숫자임.\n\n");
            break;
      }
      
   }
      
}


void register_member(struct Member *member_list){
   FILE *fp;
   
   char 
   
   fp = fopen("manage.txt", "a");
   if(fp == NULL){
      fprintf(stderr, "열수없음\n");
      exit(0);
   }
   char ch;
   int result;
   
   do
   {
      printf("이름: ");
      read_line(member_list[member_num].name, sizeof(member_list[member_num].name));
      //gets(member_list[member_num].name);
      //fputs(member_list[member_num].name, fp);
      //fgets(member_list[member_num].name, MAX_STR_LEN), fp);
      
      printf("나이: ");
      scanf("%d", &member_list[member_num].age); 
      
      printf("이메일: ");
      read_line(member_list[member_num].email, sizeof(member_list[member_num].email));
      
      fprintf(fp, "%s %d %s", member_list[member_num].name, member_list[member_num].age, member_list[member_num].email);
      member_num++;
      
      printf("계속 입력 할까요? ");
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
      printf("입력이 완료되었습니다.\n");
   }
   
   printf("\n");
   
   fclose(fp);

}

void member_edit(struct Member *member_list){
   FILE *fp;
   fp = fopen("manage.txt", "");
   if(fp == NULL){
      fprintf(stderr, "열수없음\n");
      exit(0);
   }
   
   char input_name[MAX_STR_LEN];
   
   printf("수정할이름: ");
   scanf("%s", input_name);
   
   int name_index = searching_name(member_list, *input_name);
   //fseek으로 수정할 위치 설정하고 길이만큼 삭제하고(member_remove 불러와도 될듯) 그자리에 추가하기. 마지막에 다시 끝자리로 이동. 
   
   if(name_index != -1 && name_index >= 0){
      printf("사용자%s 수정\n", input_name);
      
      printf("이름: ");
      read_line(member_list[member_num].name, sizeof(member_list[member_num].name));
      
      printf("나이: ");
      scanf("%d", &member_list[member_num].age); 
      
      printf("이메일: ");
      read_line(member_list[member_num].email, sizeof(member_list[member_num].email));
      
      fprintf(fp, "%s %d %s", member_list[member_num].name, member_list[member_num].age, member_list[member_num].email);
   
      printf("수정완료\n"); 
   } 
   
   printf("\n");
   
   fclose(fp);
}


void member_remove(struct Member *member_list){
   
   FILE *fp;
   fp = fopen("manage.txt", "r+");
   if(fp == NULL){
      fprintf(stderr, "열수없음\n");
      exit(0);
   }
   
   char input_name[MAX_STR_LEN];
   
   printf("삭제할이름: ");
   scanf("%s", input_name);
   
   int name_index = searching_name(member_list, *input_name);
   //얘도 fseek으로 해야되나 
   
   //파일삭제? 어떻게 하지?
   //member_list[name_index] = NULL;
   
   printf("\n");
}


void all_member_list(struct Member *member_list){
   FILE *fp;
   fp = fopen("manage.txt", "r");
   if(fp == NULL){
      fprintf(stderr, "열수없음\n");
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
         fprintf(stderr, "등록안된 회원\n");
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


