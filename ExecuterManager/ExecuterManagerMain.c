#include "ExecuterManager.h"

int main() {

	FILE* fp;
	char location[100] = { 0, };
	char from_txt[1000] = { 0, };
	char to_txt[1000] = { 0, };
	char tempName[1000] = { 0, };
	char tempPath[1000] = { 0, };
	char delName[100] = { 0, };
	char editName[100] = { 0, };
	char editPath[100] = { 0, };

	int i, flag, index; //i: for��, flag: Ż�� ����, index: �˻� ��ġ
	int total = 0, check, idx = 0; //total: �� ����, check: ���� �̻� Ȯ��, idx: ���� �߰��� ���α׷� �ε���
	char input;

	fp = fopen(defaultpath, "rt");
	if (fp != NULL) {
		fgets(from_txt, 1000, fp);
		fclose(fp);
	}
	else {
		printf("�ش� ������ ���� D:\\ ��ο� ������ ��������ϴ�.");
		fp = fopen(defaultpath, "wt");
		fclose(fp);
	}

	if (from_txt != NULL) {
		total = collectingList(from_txt, strlen(from_txt));
	}

	if (total == -1) {
		printf("���Ͽ� ����� ���� ������ �ֽ��ϴ�. ������ �����մϴ�.\n���� ���α׷��� ����Ͽ� ���α׷��� ����Ͽ� �ּ���.");
		total = 0;
		memset(pro, 0, sizeof(pro));
		remove(defaultpath);
	}

	for (i = 0; i < total; i++) {
		if (checkpath(pro[i].exelistPath, strlen(pro[i].exelistPath)) == -1) {
			printf("���Ͽ� ����� ���� ������ �ֽ��ϴ�. ������ �����մϴ�.\n���� ���α׷��� ����Ͽ� ���α׷��� ����Ͽ� �ּ���.");
			total = 0;
			memset(pro, 0, sizeof(pro));
			remove(defaultpath);
			break;
		}
	}

	idx = total;

	while (1) {
		printf("\n");
		showList(total, idx);
		flag = 0;
		index = -1;
		printf("\n\n���α׷� ����[0] ���α׷� �߰�[1] ���α׷� ����[2] ���α׷� ����[3] ����[4] �������� �ʰ� ����[5]�� �Է��ϼ���: ");
		scanf(" %c", &input);
		system("cls");
		switch (input) {
		case '0':
			check = 0;
			for (i = 0; i < idx; i++) {
				if (pro[i].useAt == 1) {
					if (checkpath(pro[i].exelistPath, strlen(pro[i].exelistPath)) == -1) {
						check = 1;
						break;
					}
				}
			}

			if (check == 0) {
				for (i = 0; i < idx; i++) {
					if (pro[i].useAt == 1) {
						printf("%s��(��) �����߽��ϴ�\n", pro[i].exelistName);
						ShellExecuteA(NULL, NULL, pro[i].exelistPath, NULL, NULL, SW_SHOW);
					}
				}
			}
			else {
				printf("ExecuterManager ���α׷��� ������ �߻��Ͽ����ϴ�. ���� �� �ٽ� ��������ּ���.\n\n");
			}
			if (total > 0)
				printf("\n%d���� ���α׷��� �����߽��ϴ�.\n", total);
			else
				printf("������ ���α׷��� �����ϴ�.\n");
			break;
		case '1':
			if (idx > 19) {
				printf("���α׷��� 20������ ��� �����մϴ�\n");
			}
			else {
				while (flag == 0) {

					printf("�߰��� ����� ���α׷��� �̸��� ��θ� �Է��ϼ���(����Ϸ��� -1 -1�� �Է��ϼ���.): ");
					scanf("%s %[^\n]", tempName, tempPath);
					if ((strcmp(tempName, "-1") == 0) && (strcmp(tempPath, "-1") == 0)) {
						break;
					}
					if (checkpath(tempPath, strlen(tempPath)) == 1) {
						pro[idx].useAt = 1;
						strcpy(pro[idx].exelistName, tempName);
						strcpy(pro[idx].exelistPath, tempPath);
						total++;
						idx++;
						flag = 1;
						memset(tempName, 0, sizeof(tempName));
						memset(tempPath, 0, sizeof(tempPath));
					}
					else {
						printf("�߸��� ����Դϴ�.\n");
						memset(tempName, 0, sizeof(tempName));
						memset(tempPath, 0, sizeof(tempPath));
					}
				}
			}
			break;

		case '2':

			showList(total, idx);
			index = -1;
			printf("\n������ ���α׷��� �̸��� �Է����ּ���(����Ϸ��� -1�� �Է��ϼ���.): ");
			scanf("%s", editName);
			if (strcmp(editName, "-1") == 0) {
				break;
			}
			for (i = 0; i < idx; i++) {
				if (pro[i].useAt == 1) {
					if (strcmp(pro[i].exelistName, editName) == 0) {
						index = i;
						break;
					}
				}
			}
			memset(editName, 0, sizeof(editName));
			if (index == -1) {
				printf("�Է��� �̸��� ���α׷��� �������� �ʽ��ϴ�\n");
			}
			else {
				while (flag == 0) {
					printf("%s�� ���ο� ��θ� �Է����ּ���(����Ϸ��� -1�� �Է��ϼ���.): ", pro[index].exelistName);
					scanf(" %[^\n]", editPath);
					if (strcmp(editPath, "-1") == 0) {
						break;
					}
					if (checkpath(editPath, strlen(editPath)) == 1) {
						strcpy(pro[index].exelistPath, editPath);
						flag = 1;
					}
					else {
						printf("�߸��� ����Դϴ�.\n");
					}
					memset(editPath, 0, sizeof(editPath));
				}
				break;

			}
			break;
		case '3':
			showList(total, idx);

			printf("\n������ ���α׷��� �̸��� �Է����ּ���: ");
			scanf("%s", delName);

			for (i = 0; i < idx; i++) {
				if (pro[i].useAt == 1) {
					if (strcmp(pro[i].exelistName, delName) == 0) {
						index = i;
						break;
					}
				}
			}
			memset(delName, 0, sizeof(delName));
			if (index == -1) {
				printf("�Է��� �̸��� ���α׷��� �������� �ʽ��ϴ�\n");
			}
			else {
				printf("%s��(��) ���� �Ǿ����ϴ�.\n ", pro[index].exelistName);
				pro[index].useAt = 0;
				total--;
			}

			break;
		case '4':

			for (i = 0; i < idx; i++) {

				if (pro[i].useAt == 1) {
					strcat(to_txt, "{");
					strcat(to_txt, pro[i].exelistName);
					strcat(to_txt, ",");
					strcat(to_txt, pro[i].exelistPath);
					strcat(to_txt, "}");
				}
			}

			fp = fopen(defaultpath, "w+");
			fprintf(fp, "%s", to_txt);
			fclose(fp);
			printf("����Ǿ����ϴ�. ���α׷��� �����մϴ�\n");
			system("pause");
			return 0;

		case '5':
			printf("�������� �ʰ� ���α׷��� �����մϴ�\n");
			system("pause");
			return 0;
		default:
			printf("�߸��� �Է��Դϴ�\n");
		}
	}

	return 0;
}