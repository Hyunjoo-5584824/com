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
	fprintf(stdout, "1. �ű�ȸ�� ����\n");
	fprintf(stdout, "2. ȸ������ ����\n");
	fprintf(stdout, "3. ȸ�� ����\n");
	fprintf(stdout, "4. ��� ȸ�� ����Ʈ\n");
	fprintf(stdout, "5. ����\n");
	fprintf(stdout, "�Է��ϼ���>");
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
		fprintf(stdout, "�̸�:");
		fgets(member[*count].name, BUFSIZ, stdin);
		if (member[*count].name[strlen(member[*count].name) - 1] == '\n')
			member[*count].name[strlen(member[*count].name) - 1] = '\0';

		fprintf(stdout, "����:");
		fscanf(stdin, "%d", &member[*count].age);
		if (member[*count].age >= 200) {
			fprintf(stdout, "�ٽ� �Է��ϼ���:");	
			fscanf(stdin, "%d", &member[*count].age);
		}

		fprintf(stdout, "�̸���:");
		fscanf(stdin, "%s", member[*count].email);
		fgetc(stdin);
		(*count)++;

		fprintf(stdout, "��� �Է� �ұ��?(Y/N) ");
		fgets(ch,sizeof(ch),stdin);

		if (ch[0] == 'Y' || ch[0] == 'y') continue;
		else if (ch[0] == 'N' || ch[0] == 'n') {
			fprintf(stdout, "�Է��� �Ϸ�Ǿ����ϴ�.\n");
			break;
		}
		else {
			fprintf(stdout, "�߸��� �Է��Դϴ�.\n");
			break;
		}
	}
}

void adjust_member(member* member, int* count) {
	char tmp[BUFSIZ] = { 0, };
	fprintf(stdout, "������ ��� �̸��� �Է����ּ���:");
	fgets(tmp, sizeof(tmp), stdin);
	tmp[strlen(tmp) - 1] = '\0';

	int i;

	while (1) {
		for (i = 0; i < *count; i++) {
			if (!strcmp(tmp, member[i].name)) {
				fprintf(stdout, "����� %s��(��) �����մϴ�.\n", tmp);
				fprintf(stdout, "�̸�:");
				fgets(member[i].name, BUFSIZ, stdin);
				//if (member[*count].name[strlen(member[*count].name) - 1] == '\n')
				member[i].name[strlen(member[i].name) - 1] = '\0';

				fprintf(stdout, "����:");
				fscanf(stdin, "%d", &member[i].age);

				fprintf(stdout, "�̸���:");
				fscanf(stdin, "%s", member[i].email);

				fprintf(stdout, "���� �Ϸ� �Ǿ����ϴ�.\n");
				return;
			}
		}
		fprintf(stdout, "����� %s��(��) �����ϴ�.\n", tmp);
		break;
	}

}

// ��� ���� �Լ�  
void delete_member(member* member, int* count) {
	char tmp[BUFSIZ] = { 0, };
	fprintf(stdout, "������ ��� �̸��� �Է����ּ���:");
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
				fprintf(stdout, "����� %s��(��) �����Ǿ����ϴ�.\n",tmp);
				return;
			}
		}
		fprintf(stdout, "����� %s��(��) �����ϴ�.\n", tmp);
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
			fprintf(stdout, "�����մϴ�.\n");
			exit(1);
		default:
			fprintf(stdout, "�߸��� ��ȣ �Դϴ�.\n");
		}
		save_file(list, member, &count);
	}

	return 0;
}