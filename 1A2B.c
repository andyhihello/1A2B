#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Isvaildinputchoose(const char *text,int min,int max){ // 偵測選擇輸入是否正常
    int input;
    while (1) {
        printf("%s", text);
        if (scanf("%d", &input) == 1 && input >= min && input <= max) { // 偵測是否輸入數字且在有效範圍裡
            return input;
        }
        else {
            printf("Invalid input! Please enter again\n");
            while (getchar() != '\n'); // 丟棄所有無效輸入
        }
    }
}

int Isvaildinputguess(int *guess,int size){ // 偵測猜測輸入是否正常
    while(1){
        int finishguessing = 1; //檢測是否完成猜測輸入
        printf("Enter your guess (4 digits, separated by space): ");

        for (int i = 0; i < 4; i++) {
                if (scanf("%d", & guess[i]) != 1 || guess[i] < 1 || guess[i] > size) { // 偵測是否輸入數字且在有效範圍裡
                    printf("Invalid input! Please enter 4 numbers between 1 and %d.\n",size);
                    while (getchar() != '\n'); // 清除輸入緩衝區
                    finishguessing = 0;//未完成輸入
                    break;
                }
            }
        if(finishguessing){ // 輸入成功
            break; //終止輸入數字
        }
    }
  
}

void generate1A2B(int *number,int size){ 
    srand(time(0)); // 初始化隨機數種子
    int used[10] = {0}; // 記錄數字是否已使用
    int count = 0;

    while (count < 4) {
        int num = rand() % size + 1; // 隨機生成 1~size 的數字

        if (used[num] == 0) { // 檢查該數字是否未使用 並使用後標記
            number[count] = num; 
            used[num] = 1;        
            count++;
        }
    }
}


int play(){
    int number[4]; //儲存1A2B答案
    generate1A2B(number,6); // 生成1A2B答案
    printf("Game starts!\n");

    int guess[4]; // 儲存玩家猜測
    int attempts = 0; // 猜測次數統計

    while (1) {
        attempts++;
        Isvaildinputguess(guess,6); // 輸入4個數並偵測選擇輸入是否正常
        int A = 0, B = 0;
        for (int i = 0; i < 4; i++) { // 偵測幾A幾B
            if (guess[i] == number[i]) {
                A++;
            } 
            else {
                for (int j = 0; j < 4; j++) {
                    if (guess[i] == number[j]) {
                        B++;
                        break;
                    }
                }
            }
        }
        printf("%dA%dB\n", A, B);
        if (A == 4) {
            printf("Congratulations! You guessed the number in %d attempts.\n", attempts);
            break;
        }
    }
}

int quest(){

}

int main(){

    printf("welcome 1A2B\n");
    int play_again,player_setting; 

    while(1){

        player_setting = Isvaildinputchoose("guesser press 1, question maker press 2 : ",1,2); // 選擇玩法並偵測輸入是否正常
        
        if(player_setting == 1){ //答題者
            play();
        }
        if(player_setting == 2){ // 出題者
            quest();
        }

        play_again = Isvaildinputchoose("play again press 1, quit press 2 : ",1,2); //是否還要再玩並偵測輸入是否正常

        if(play_again == 1){ // 再玩一次
            printf("Have fun!\n");
        }

        if(play_again == 2){ // 離開
            printf("Thanks for playing!");
            break; // 結束程式
        }

        
                
            
    }

        
    

    


}