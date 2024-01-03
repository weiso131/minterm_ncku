#include<stdio.h>

//字串處理
struct string{
    char str[50];
    int index;
};

void add_str(struct string* minterm_str, char c){
    minterm_str -> str[minterm_str -> index] = c;
    minterm_str -> index++;
}

void output_minterm(struct string* minterm_str, int input_num){
    int not_take = (1 << input_num) - 1;//存這個minterm少掉的東西
    int minterm_value = 0;              //存這個minterm拿的東西

    for (int i = 0;i < (minterm_str -> index);i++){
        not_take ^= 1 << (input_num - (minterm_str -> str[i] - 'a') - 1);
        if (minterm_str -> str[i + 1] == '\'') i++;
        else minterm_value += 1 << (input_num - (minterm_str -> str[i] - 'a') - 1);
    }
    find_minterm(not_take, minterm_value , 0, input_num);

}

void find_minterm(int not_take, int minterm_value, int check, int input_num){
    if (check == input_num){
        printf("m%d\n", minterm_value);
        return;
    }
    if ((not_take >> check) & 1)find_minterm(not_take, minterm_value + (1 << check), check + 1, input_num);//x

    find_minterm(not_take, minterm_value , check + 1, input_num);//x'或沒事
}


int main(){
    //儲存每個minterm的字串
    struct string* minterm_str;
    minterm_str -> index = 0;

    //會有多少個輸入(a,b,c,d就是4個)
    int input_num;
    scanf("%d", & input_num);

    //邏輯函數
    char* logic = malloc(3 * input_num * 50 * sizeof(char));
    scanf("%s", logic);

    int i = -1;

    do{
        i++;
        if (logic[i] == '+' || logic[i] == '\0' || logic[i] == '\n'){
            output_minterm(minterm_str, input_num);
            minterm_str -> index = 0;
            continue;
        }
        add_str(minterm_str, logic[i]);

    }while(logic[i] != '\0' && logic[i] != '\n');
    printf("%d", ((0 & 1) == (0 & 1)));

}
