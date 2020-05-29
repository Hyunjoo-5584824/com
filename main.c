#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable 4996)

typedef struct {
	char name[BUFSIZ];
	int age;
	char email[BUFSIZ];
}member;

void start(int* answer) {
	fprintf(stdout, "1. 신규회원 저장\n");
	fprintf(stdout, "2. 회원정보 수정\n");
	fprintf(stdout, "3. 회원 삭제\n");
	fprintf(stdout, "4. 모든 회원 리스트\n");
	fprintf(stdout, "5. 종료\n");
	fprintf(stdout, "입력하세요>");
	fscanf(stdin, "%d", answer);
	fgetc(stdin);
}

int open_file(FILE* fp, member* member, int* count) {
	fp = fopen("member_list.txt", "r");
	if (fp == NULL) {
		fprintf(stdout, "file open error\n");
		exit(1);
	}

	while (!feof(fp)) {
		fgets(member[*count].name, BUFSIZ, fp);
		if (strcmp(member[*count].name, "\n") == 0) break;
		if (member[*count].name[strlen(member[*count].name) - 1] == '\n')
			member[*count].name[strlen(member[*count].name) - 1] = '\0';
		fscanf(fp, "%d\n", &member[*count].age);
		fgets(member[*count].email, BUFSIZ, fp);
		//printf("%s",member[*count].email);
		if (member[*count].email[strlen(member[*count].email) - 1] == '\n')
			member[*count].email[strlen(member[*count].email) - 1] = '\0';
		(*count)++;
	}
	fclose(fp);
}

void save_file(FILE* fp, member* member, int* count) {
	fp = fopen("member_list.txt", "w");
	int i;
	for (i = 0; i < 1; i++) {
		fprintf(fp, "%s\n", member[i].name);
		fprintf(fp, "%d\n", member[i].age);
		fprintf(fp, "%s", member[i].email);
	}
	for (i = 1; i < (*count); i++) {
		fprintf(fp, "\n%s\n", member[i].name);
		fprintf(fp, "%d\n", member[i].age);
		fprintf(fp, "%s", member[i].email);
	}

	fclose(fp);
}

void save_new(member* member, int* count) {

	while (1) {
		char ch[3] = { 0, };
		fprintf(stdout, "이름:");
		fgets(member[*count].name, BUFSIZ, stdin);
		if (member[*count].name[strlen(member[*count].name) - 1] == '\n')
			member[*count].name[strlen(member[*count].name) - 1] = '\0';

		fprintf(stdout, "나이:");
		fscanf(stdin, "%d", &member[*count].age);
		if (member[*count].age >= 200) {
			fprintf(stdout, "다시 입력하세요:");	
			fscanf(stdin, "%d", &member[*count].age);
		}

		fprintf(stdout, "이메일:");
		fscanf(stdin, "%s", member[*count].email);
		fgetc(stdin);
		(*count)++;

		fprintf(stdout, "계속 입력 할까요?(Y/N) ");
		fgets(ch,sizeof(ch),stdin);

		if (ch[0] == 'Y' || ch[0] == 'y') continue;
		else if (ch[0] == 'N' || ch[0] == 'n') {
			fprintf(stdout, "입력이 완료되었습니다.\n");
			break;
		}
		else {
			fprintf(stdout, "잘못된 입력입니다.\n");
			break;
		}
	}
}

void adjust_member(member* member, int* count) {
	char tmp[BUFSIZ] = { 0, };
	fprintf(stdout, "수정할 사람 이름을 입력해주세요:");
	fgets(tmp, sizeof(tmp), stdin);
	tmp[strlen(tmp) - 1] = '\0';

	int i;

	while (1) {
		for (i = 0; i < *count; i++) {
			if (!strcmp(tmp, member[i].name)) {
				fprintf(stdout, "사용자 %s을(를) 수정합니다.\n", tmp);
				fprintf(stdout, "이름:");
				fgets(member[i].name, BUFSIZ, stdin);
				//if (member[*count].name[strlen(member[*count].name) - 1] == '\n')
				member[i].name[strlen(member[i].name) - 1] = '\0';

				fprintf(stdout, "나이:");
				fscanf(stdin, "%d", &member[i].age);

				fprintf(stdout, "이메일:");
				fscanf(stdin, "%s", member[i].email);

				fprintf(stdout, "수정 완료 되었습니다.\n");
				return;
			}
		}
		fprintf(stdout, "사용자 %s은(는) 없습니다.\n", tmp);
		break;
	}

}

// 멤버 삭제 함수  
void delete_member(member* member, int* count) {
	char tmp[BUFSIZ] = { 0, };
	fprintf(stdout, "삭제할 사람 이름을 입력해주세요:");
	fgets(tmp, sizeof(tmp), stdin);
	tmp[strlen(tmp) - 1] = '\0';

	int i, num;
	while (1) {
		for (i = 0; i < (*count); i++) {
			if (strcmp(tmp, member[i].name) == 0) {
				num = i;
				for (num; num < (*count) - 1; num++) {
					member[num] = member[num + 1];
				}
				(*count)--;
				fprintf(stdout, "사용자 %s은(는) 삭제되었습니다.\n",tmp);
				return;
			}
		}
		fprintf(stdout, "사용자 %s은(는) 없습니다.\n", tmp);
		break;
	}
}


void show_member(member* member, int* count) {
	int i;
	for (i = 0; i < (*count); i++) {
		fprintf(stdout, "%s / %d / %s\n", member[i].name, member[i].age, member[i].email);
	}
}


int main(int argc, char* argv[]) {
	FILE* list = NULL;
	member member[BUFSIZ];
	int answer = 0;
	int count = 0;
	open_file(list, member, &count);

	while (1) {
		start(&answer);
		switch (answer) {
		case 1:
			save_new(member, &count);
			break;
		case 2:
			adjust_member(member, &count);
			break;
		case 3:
			delete_member(member, &count);
			break;
		case 4:
			show_member(member, &count);
			break;
		case 5:
			fprintf(stdout, "종료합니다.\n");
			exit(1);
		default:
			fprintf(stdout, "잘못된 번호 입니다.\n");
		}
		save_file(list, member, &count);
	}

	return 0;
}