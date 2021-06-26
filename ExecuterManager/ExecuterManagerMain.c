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

	int i, flag, index; //i: for문, flag: 탈출 조건, index: 검색 위치
	int total = 0, check, idx = 0; //total: 총 개수, check: 문법 이상 확인, idx: 새로 추가할 프로그램 인덱스
	char input;

	fp = fopen(defaultpath, "rt");
	if (fp != NULL) {
		fgets(from_txt, 1000, fp);
		fclose(fp);
	}
	else {
		printf("해당 파일이 없어 D:\\ 경로에 파일을 만들었습니다.");
		fp = fopen(defaultpath, "wt");
		fclose(fp);
	}

	if (from_txt != NULL) {
		total = collectingList(from_txt, strlen(from_txt));
	}

	if (total == -1) {
		printf("파일에 저장된 값에 오류가 있습니다. 파일을 삭제합니다.\n관리 프로그램을 사용하여 프로그램을 등록하여 주세요.");
		total = 0;
		memset(pro, 0, sizeof(pro));
		remove(defaultpath);
	}

	for (i = 0; i < total; i++) {
		if (checkpath(pro[i].exelistPath, strlen(pro[i].exelistPath)) == -1) {
			printf("파일에 저장된 값에 오류가 있습니다. 파일을 삭제합니다.\n관리 프로그램을 사용하여 프로그램을 등록하여 주세요.");
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
		printf("\n\n프로그램 실행[0] 프로그램 추가[1] 프로그램 수정[2] 프로그램 삭제[3] 종료[4] 저장하지 않고 종료[5]를 입력하세요: ");
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
						printf("%s을(를) 실행했습니다\n", pro[i].exelistName);
						ShellExecuteA(NULL, NULL, pro[i].exelistPath, NULL, NULL, SW_SHOW);
					}
				}
			}
			else {
				printf("ExecuterManager 프로그램에 문제가 발생하였습니다. 종료 후 다시 실행시켜주세요.\n\n");
			}
			if (total > 0)
				printf("\n%d개의 프로그램을 실행했습니다.\n", total);
			else
				printf("실행할 프로그램이 없습니다.\n");
			break;
		case '1':
			if (idx > 19) {
				printf("프로그램은 20개까지 등록 가능합니다\n");
			}
			else {
				while (flag == 0) {

					printf("추가로 등록할 프로그램의 이름과 경로를 입력하세요(취소하려면 -1 -1을 입력하세요.): ");
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
						printf("잘못된 경로입니다.\n");
						memset(tempName, 0, sizeof(tempName));
						memset(tempPath, 0, sizeof(tempPath));
					}
				}
			}
			break;

		case '2':

			showList(total, idx);
			index = -1;
			printf("\n수정할 프로그램의 이름을 입력해주세요(취소하려면 -1을 입력하세요.): ");
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
				printf("입력한 이름의 프로그램이 존재하지 않습니다\n");
			}
			else {
				while (flag == 0) {
					printf("%s의 새로운 경로를 입력해주세요(취소하려면 -1을 입력하세요.): ", pro[index].exelistName);
					scanf(" %[^\n]", editPath);
					if (strcmp(editPath, "-1") == 0) {
						break;
					}
					if (checkpath(editPath, strlen(editPath)) == 1) {
						strcpy(pro[index].exelistPath, editPath);
						flag = 1;
					}
					else {
						printf("잘못된 경로입니다.\n");
					}
					memset(editPath, 0, sizeof(editPath));
				}
				break;

			}
			break;
		case '3':
			showList(total, idx);

			printf("\n삭제할 프로그램의 이름을 입력해주세요: ");
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
				printf("입력한 이름의 프로그램이 존재하지 않습니다\n");
			}
			else {
				printf("%s이(가) 삭제 되었습니다.\n ", pro[index].exelistName);
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
			printf("저장되었습니다. 프로그램을 종료합니다\n");
			system("pause");
			return 0;

		case '5':
			printf("저장하지 않고 프로그램을 종료합니다\n");
			system("pause");
			return 0;
		default:
			printf("잘못된 입력입니다\n");
		}
	}

	return 0;
}