#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int IsValidInputNum(const char *text, int min, int max) {
    char inputBuffer[1000]; // 儲存輸入
    int input;

    while (1) {
        printf("%s", text);

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
            printf("Invalid input! Please enter again.\n");
            continue;
        }

        inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; // 移除換行符號
        if (strlen(inputBuffer) == 0) { // 檢查是否為空
            printf("Invalid input! Please enter again.\n");
            continue;
        }

        char extraChar;
        if (sscanf(inputBuffer, "%d %c", &input, &extraChar) != 1) { // 檢查輸入是否為有效的整數與多餘的字元
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }


        if (input < min || input > max) { // 檢查輸入是否在指定範圍內
            printf("Invalid input! Please enter a number between %d and %d.\n", min, max);
            continue;
        }

        return input;
    }
}

void IsValidInputGuess(int *guess,int size,int allowDuplicate){ // 偵測猜測輸入是否正常
    while(1){
        char input[1000]; // 接收输入
        int guessError = 0; // 標記是否有輸入錯誤

        printf("Enter your guess : ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Invalid input! Please try again.\n");
            continue;
        }

        input[strcspn(input, "\n")] = '\0'; // 處理換行輸入

        int count = 0;
        if (strlen(input) == 4) { //是否為正確格式
            for (int i = 0; i < 4; i++) {
                if (input[i] < '0' || input[i] > '0'+size) { 
                    guessError = 1;
                    printf("Invalid input! Please enter a number between 0 and %d.\n",size-1);
                    break;
                }
                guess[i] = input[i] - '0'; // char轉int
                count++;
            }
        }
        else{
            guessError = 1;
            printf("Invalid input! Please enter exactly 4 numbers.\n");
        }

        if (guessError) {
            continue;
        }

        int duplicateCount = 0;
            for(int i = 0; i < 3;i++){ // 檢測重複數字
                for(int j = i+1; j < 4;j++){
                    if(guess[i] == guess[j]){
                    duplicateCount++;
                    }
                }
            }

        if (!allowDuplicate && duplicateCount > 0) { // 不允許重複
            printf("Invalid input! Please enter 4 numbers without duplicates.\n");
            guessError = 1;
        }

        else if (allowDuplicate && duplicateCount > 1) { // 允許最多一個重複數字
            printf("Invalid input! Only one number can appear twice.\n");
            guessError = 1;
        }

        if(!guessError){ // 輸入完整
            break;
        }
    }

}

void generateAnswer(int *number, int size, int allowDuplicate){ //生成1A2B答案

    srand(time(0)); // 初始化隨機數種子
    int used[10] = {0}; // 記錄數字是否已使用
    int count = 0;

    while (count < 4) {
        int num = rand() % size ; // 隨機生成 0~size-1 的數字

        if ((!allowDuplicate &&used[num] == 0) || (allowDuplicate && used[num] < 2)) { // 檢查該數字是否未使用 並使用後標記
            number[count] = num;
            used[num] = 1;
            count++;
        }
    }
}

void generateAllCombination(int combination[5040][4]) { //生成所有組合
    int index = 0;
    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 10; b++) {
            if (b == a) continue;
            for (int c = 0; c < 10; c++) {
                if (c == a || c == b) continue;
                for (int d = 0; d < 10; d++) {
                    if (d == a || d == b || d == c) continue;
                    combination[index][0] = a;
                    combination[index][1] = b;
                    combination[index][2] = c;
                    combination[index][3] = d;
                    index++;
                }
            }
        }
    }
}

void checkAB(int *A, int *B, int guess[4], int answer[4]) {
    int usedAnswer[4] = {0}; // 記錄數字與位置均正確的位置
    int usedGuess[4] = {0};  // 記錄數字與位置均正確的位置

    
    for (int i = 0; i < 4; i++) { // 計算 A
        if (guess[i] == answer[i]) {
            (*A)++;
            usedAnswer[i] = 1; // 標記均正確的位置
            usedGuess[i] = 1;  // 標記均正確的位置
        }
    }

    
    for (int i = 0; i < 4; i++) { // 計算 B
        if (usedGuess[i]) continue; // 跳過均正確的位置

        for (int j = 0; j < 4; j++) {
            if (!usedAnswer[j] && guess[i] == answer[j]) { // 確保數字未被使用過
                (*B)++;
                usedAnswer[j] = 1; // 標記該答案數字已使用
                break;
            }
        }
    }
}

void play(int size,int allowDuplicate){ // size=數字範圍0~(size-1) 共size個數字 allowDuplicate=是否允許重複數字

    int answer[4]; //儲存1A2B答案
    generateAnswer(answer,size,allowDuplicate); // 生成1A2B答案
    printf("Game starts!\n");
    printf("your guess must be 4 digits between 0 and %d(ex:0123)\n",size-1);

    int guess[4]; // 儲存玩家猜測
    int attempts = 0; // 猜測次數統計

    while (1) {
        attempts++;
        IsValidInputGuess(guess,size,allowDuplicate); // 輸入4個數並偵測選擇輸入是否正常
        int A = 0, B = 0;
        checkAB(&A,&B,guess,answer); // 檢測幾A幾B
        printf("%dA%dB\n", A, B);
        if (A == 4) { // 若4A則獲勝
            printf("YOU WIN! You guessed the number in %d attempts.\n", attempts);
            break;
        }
    }
}

void quest() {
    int combination[5040][4];
    generateAllCombination(combination);
    printf("Please think of a 4-digit number (digits are 0~9, no duplicates).\n");

    int count = 5040;
    while (count > 0) {
        int guess[4] = {combination[0][0], combination[0][1], combination[0][2], combination[0][3]};
        printf("My guess: %d%d%d%d, please enter the feedback\n", guess[0], guess[1], guess[2], guess[3]);

        int A, B;
        A = IsValidInputNum("A: ",0,4);
        B = IsValidInputNum("B: ",0,4);

        if (A + B > 4) {
            printf("YOU CHEAT!\n");
            return;
        }

        if (A == 4) {
            printf("PC WIN!\n");
            return;
        }

        int newCount = 0;
        for (int i = 0; i < count; i++) { //淘汰不符合的組合
            int tempA = 0, tempB = 0;
            checkAB(&tempA, &tempB, guess, combination[i]);
            if (tempA == A && tempB == B) {
                memcpy(combination[newCount++], combination[i], 4 * sizeof(int));
            }
        }
        count = newCount;

        if (count == 0) { //feedback有矛盾
            printf("YOU CHEAT!\n");
            return;
        }
    }
}

int main(){
    int play_again,player_setting,game_setting;

    printf("welcome 1A2B\n");

    while(1){

        player_setting = IsValidInputNum("guesser press 1, questioner press 2 : ",1,2); // 選擇玩法並偵測輸入是否正常

        if(player_setting == 1){ //答題者
            printf("Easy mode: 8 number and no duplicate\nNormal mode: 10 number and no duplicate\nHard mode: 6 number and one number can appear twice\nUltimate mode: 8 number and one number can appear twice\n");
            game_setting = IsValidInputNum("Easy press 1, Normal press 2, Hard press 3, Ultimate press 4 : ",1,4); // 選擇玩法並偵測輸入是否正常
            switch (game_setting){
            case 1:
                play(8,0);
                break;
            case 2:
                play(10,0);
                break;
            case 3:
                play(6,1);
                break;
            case 4:
                play(8,1);
                break;
            }
        }
        if(player_setting == 2){ // 出題者
            quest();
        }

        play_again = IsValidInputNum("play again press 1, quit press 2 : ",1,2); //是否還要再玩並偵測輸入是否正常

        if(play_again == 1){ // 再玩一次
            printf("Have fun!\n");
        }

        if(play_again == 2){ // 離開
            printf("Thanks for playing!");
            break; // 結束程式
        }
    }
}
