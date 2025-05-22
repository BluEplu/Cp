#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// 사용할 타일의 개수 정의 -> 9장
#define TileNum 9

// 색상 정의 (typedef = 예약어: 변수를 만들 때 사용, enum = 문자열을 수 체계로 변환하여 저장)
typedef enum { BLACK, WHITE } C;

// 숫자 타일 구조체 (struct = 묶음 변수 체계, bool = T/F 나타낼 때 사용 / used 이용하여 사용된 파일은 제거되게 설정)
typedef struct {
    int number;
    C color;
    bool used;
} T;

// 색상 문자열 반환
const char* getColorString(C color) {
    return color == BLACK ? "흑" : "백";
}

// 색상 판단 (홀수=흑, 짝수=백)
C determineColor(int number) {
    return (number % 2 == 1) ? BLACK : WHITE;
}

// 타일 초기화 (void = 함수 선언)
void initializeTiles(T tiles[]) {
    for (int i = 0; i < TileNum; i++) {
        tiles[i].number = i + 1;
        tiles[i].color = determineColor(i + 1);
        tiles[i].used = false;
    }
}

// 플레이어 타일 출력
void printTilesPlayer(T tiles[]) {
    printf("플레이어의 남은 타일: ");
    for (int i = 0; i < TileNum; i++) {
        if (!tiles[i].used)
            printf("[%d(%s)] ", tiles[i].number, getColorString(tiles[i].color));
    }
    printf("\n");
}

// 컴퓨터 타일 출력
    void printTilesCom(T tiles[]) {
        printf("컴퓨터의 남은 타일: ");
        for (int i = 0; i < TileNum; i++) {
            if (!tiles[i].used)
                printf("[%d(%s)] ", tiles[i].number, getColorString(tiles[i].color));
        }
        printf("\n");
    }

// 타일 사용 가능 여부 확인
bool isValidTile(T tiles[], int input) {
    for (int i = 0; i < TileNum; i++) {
        if (tiles[i].number == input && !tiles[i].used)
            return true;
    }
    return false;
}

// 타일 제거 처리
void UsedTiles(T tiles[], int number) {
    for (int i = 0; i < TileNum; i++) {
        if (tiles[i].number == number) {
            tiles[i].used = true;
            break;
        }
    }
}

int main() {
    T playerTiles[TileNum];
    T computerTiles[TileNum];
    int score = 0;

    initializeTiles(playerTiles);
    initializeTiles(computerTiles);
    srand((unsigned int)time(NULL));

    printf("=== '흑과 백' 게임을 시작합니다! ===\n");

    for (int round = 1; round <= TileNum; round++) {
        int computerNum;

        // 컴퓨터 타일 중 사용되지 않은 숫자 선택
        do {
            computerNum = rand() % 9 + 1;
        } while (!isValidTile(computerTiles, computerNum));

        C computerColor = determineColor(computerNum);

        printf("\n[%d 라운드]\n", round);
        printTilesPlayer(playerTiles);
        printTilesCom(computerTiles);
        printf("컴퓨터가 선택한 숫자의 색상은 '%s'입니다.\n", getColorString(computerColor));

        int playerNum;
        while (1) {
            printf("당신의 숫자를 입력하세요. (1~9): ");
            scanf("%d", &playerNum);

            if (playerNum < 1 || playerNum > 9 || !isValidTile(playerTiles, playerNum)) {
                printf("올바르지 않거나 이미 사용된 숫자입니다. 다시 입력하세요.\n");
            }
            else {
                break;
            }
        }

        // 점수 계산
        if (playerNum == computerNum) {
            score += 1;
            printf("동점입니다! +1점\n");
        }
        else if (playerNum > computerNum) {
            score += 2;
            printf("이겼습니다! +2점\n");
        }
        else {
            printf("졌습니다. +0점\n");
        }

        //경기 결과
        printf("컴퓨터가 선택한 숫자는 %d였습니다.\n", computerNum);

        UsedTiles(playerTiles, playerNum);
        UsedTiles(computerTiles, computerNum);
    }

    // 게임 결과
    printf("\n=== 게임 종료 ===\n총 점수: %d점\n", score);
    if (score > 8) {
        printf("승리하셨습니다!\n");
    }
    else {
        printf("패배하셨습니다.\n");
    }

    return 0;
}