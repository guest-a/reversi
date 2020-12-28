#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

bool flag=false;
int log_x[60];
int log_y[60];
int log_color[60];
int log_white[60];
int log_black[60];
int count=0;

//オセロ盤を表示する
int display(int coordinate[8][8],int skip){
    int x;
    int y;
    int black=0;
    int white=0;
    int can_put=0;
    int i;
    
    
     cout<<"　１　２　３　４　５　６　７　８\n";
    for (y=0;y<8;y++){
        cout<<" --------------------------------\n";
        for (x=0;x<8;x++){
            cout<<"｜";
            switch(coordinate[x][y]){
                case 1:
                    cout<<"○";
                    black++;
                    break;
                case 2:
                    cout<<"●";
                    white++;
                    break;
                case 3:
                    cout<<"・";
                    can_put++;
                    break;
                default:
                    cout<<"　";
             }
            
         }   
            cout<<"｜"<<y+1<<"\n";
    }
    log_black[count-1]=black;
    log_white[count-1]=white;
        cout<<" --------------------------------\n黒:"<<black<<"個　白:"<<white<<"個\n";
        if(black==0){
            cout<<"白の勝ちです。";
            flag=1;
        }else if(white==0){
            cout<<"黒の勝ちです。";
            flag=1;
        }
        if(black>white && flag==0 && black+white!=64){
            cout<<"黒が優勢です。\n";
        }else if(white>black && flag==0 && black+white!=64){
            cout<<"白が優勢です。\n";
        }
        if(black+white==64 || skip>=2){
            if(black>white){
                cout<<"黒の勝ちです。\n";
            }else if(white>black){
                cout<<"白の勝ちです。\n";
            }else if(black==white){
                cout<<"引き分けです。\n";
            }
            if(skip>=2){
                flag=true;
            }
            cout<<"--対戦棋譜--\n";
            for(i=0;i<60;i++){
                if(log_color[i]==1){
                    cout<<"△";
                }else if(log_color[i]==2){
                    cout<<"▲";
                }
                cout<<" "<<log_x[i]+1<<" "<<log_y[i]+1<<"  "<<log_black[i]<<"-"<<log_white[i]<<"\n";
            }
        }
        
        return can_put;
}


//目印をリセットする
int preparation(int coordinate[8][8]){
    int x;
    int y;
    for(y=0;y<8;y++){
        for(x=0;x<8;x++){
            if(coordinate[x][y]==3){
                coordinate[x][y]=0;
            }
        }
    }
    return 0;
}

//石が置ける座標に印をつける
int investigate(int coordinate[8][8],int scalar_x,int scalar_y,int x,int y,int color){
    int x2=scalar_x;
    int y2=scalar_y;
    while(x+scalar_x<8 && x+scalar_x>-1 && y+scalar_y<8 && y+scalar_y>-1){
        if(coordinate[x+scalar_x][y+scalar_y]==0 || coordinate[x+scalar_x][y+scalar_y]==3){
            coordinate[x-x2][y-y2]=0;
            break;
        }else if(coordinate[x+scalar_x][y+scalar_y]==color && x-x2>-1 && x-x2<8 && y-y2>-1 && y-y2<8){
             coordinate[x-x2][y-y2]=3;
             break;
        }
        scalar_x=scalar_x+x2;
        scalar_y=scalar_y+y2;
        
    }
   
    return 0;
}

//石が置ける場所を探す
int situation(int coordinate[8][8],int color){
    int x;
    int y;
    int scalar_x;
    int scalar_y;
    int enemy_color;
     preparation(coordinate);
    if(color==1){
        enemy_color=2;
    }else if(color==2){
        enemy_color=1;
    }
    for(y=0;y<8;y++){
        for(x=0;x<8;x++){
            if(coordinate[x][y]==enemy_color){
                if(coordinate[x+1][y]==0 && x+1<8){
                    scalar_x=-1;
                    scalar_y=0;
                    investigate(coordinate,scalar_x,scalar_y,x,y,color);
                }
                if(coordinate[x+1][y+1]==0 && x+1<8 && y+1<8){
                    scalar_x=-1;
                    scalar_y=-1;
                    investigate(coordinate,scalar_x,scalar_y,x,y,color);
                }
                if(coordinate[x+1][y-1]==0 && x+1<8 && y-1>-1){
                    scalar_x=-1;
                    scalar_y=1;
                    investigate(coordinate,scalar_x,scalar_y,x,y,color);
                }   
                if(coordinate[x][y-1]==0 && y-1>-1){
                    scalar_x=0;
                    scalar_y=1;
                    investigate(coordinate,scalar_x,scalar_y,x,y,color);
                }
                if(coordinate[x][y+1]==0 && y+1<8){
                    scalar_x=0;
                    scalar_y=-1;
                    investigate(coordinate,scalar_x,scalar_y,x,y,color);
                }
                if(coordinate[x-1][y]==0 && x-1>-1){
                    scalar_x=1;
                    scalar_y=0;
                    investigate(coordinate,scalar_x,scalar_y,x,y,color);
                }
                if(coordinate[x-1][y+1]==0 && x-1>-1 && y+1<8){
                    scalar_x=1;
                    scalar_y=-1;
                    investigate(coordinate,scalar_x,scalar_y,x,y,color);
                }
                if(coordinate[x-1][y-1]==0 && x-1>-1 && y-1>-1){
                    scalar_x=1;
                    scalar_y=1;
                    investigate(coordinate,scalar_x,scalar_y,x,y,color);
                }
            }
            
        }
    }
    return 0;
}

//エラーの数を数える
int error_count(int color,int put_x,int put_y,int coordinate[8][8]){
    int error=0;
    if(put_x<0 || put_x>7 || put_y<0 || put_y>7){
        error++;
    }else if(coordinate[put_x][put_y]==1 || coordinate[put_x][put_y]==2 ){
        error++;
    }else if(coordinate[put_x][put_y]!=3){
                error++;
        }
    return error;
}

//石をひっくり返す
int turn_over(int color,int coordinate [8][8],int scalar_x,int scalar_y,int x,int y){
    int x2=scalar_x;
    int y2=scalar_y;
    int i;
    while(x+scalar_x<8 && x+scalar_x>-1 && y+scalar_y<8 && y+scalar_y>-1){
        if(coordinate[x+scalar_x][y+scalar_y]==color){
            i=(x+scalar_x)*(10)+(y+scalar_y);
            scalar_x=x2;
            scalar_y=y2;
            while(i!=(x+scalar_x)*(10)+(y+scalar_y)){
                if(coordinate[x+scalar_x][y+scalar_y]==3 || coordinate[x+scalar_x][y+scalar_y]==0)
                break;
                coordinate[x+scalar_x][y+scalar_y]=color;
                 scalar_x=scalar_x+x2;
                 scalar_y=scalar_y+y2;
            }
            break;
        }
        scalar_x=scalar_x+x2;
        scalar_y=scalar_y+y2;
    }
    return 0;
}

//置かれた石の周りを調べる
int put(int color,int coordinate[8][8],int x,int y){
    int enemy_color;
    int scalar_x;
    int scalar_y;
    log_x[count]=x;
    log_y[count]=y;
    log_color[count]=color;
    if(color==1){
        enemy_color=2;
    }else if(color==2){
        enemy_color=1;
    }
    if(coordinate[x+1][y]==enemy_color && x+1<8){
        scalar_x=1;
        scalar_y=0;
        turn_over(color,coordinate,scalar_x,scalar_y,x,y);
    }
    if(coordinate[x+1][y+1]==enemy_color && x+1<8 && y+1<8){
        scalar_x=1;
        scalar_y=1;
        turn_over(color,coordinate,scalar_x,scalar_y,x,y);
    }
    if(coordinate[x+1][y-1]==enemy_color && x+1<8 && y-1>-1){
        scalar_x=1;
        scalar_y=-1;
        turn_over(color,coordinate,scalar_x,scalar_y,x,y);
    }
    if(coordinate[x][y-1]==enemy_color && y-1>-1){
        scalar_x=0;
        scalar_y=-1;
        turn_over(color,coordinate,scalar_x,scalar_y,x,y);
    }
    if(coordinate[x][y+1]==enemy_color && y+1<8){
        scalar_x=0;
        scalar_y=1;
        turn_over(color,coordinate,scalar_x,scalar_y,x,y);
    }
    if(coordinate[x-1][y]==enemy_color && x-1>-1){
        scalar_x=-1;
        scalar_y=0;
        turn_over(color,coordinate,scalar_x,scalar_y,x,y);
    }
    if(coordinate[x-1][y-1]==enemy_color && x-1>-1 && y-1>-1){
        scalar_x=-1;
        scalar_y=-1;
        turn_over(color,coordinate,scalar_x,scalar_y,x,y);
    }
    if(coordinate[x-1][y+1]==enemy_color && x-1>-1 && y+1<8){
        scalar_x=-1;
        scalar_y=1;
        turn_over(color,coordinate,scalar_x,scalar_y,x,y);
    }
    count++;
    
return 0;
}

int com_put(int coordinate[8][8],int priority[8][8],int com_color){
    int max=-100;
    int max_x[30];
    int max_y[30];
    int x;
    int y;
    int max_count=0;
    int i;
    int i2=0;
    system("clear");
    for(x=0;x<8;x++){
        for(y=0;y<8;y++){
            if(coordinate[x][y]==3){
                if(max<=priority[x][y]){
                    max=priority[x][y];
                    max_count++;
                    max_x[max_count]=x;
                    max_y[max_count]=y;
                }
            }
        }
    }
    if(max_count!=0){
    i=rand()%max_count+1;
    }else{
        i=1;
    }
    coordinate[max_x[i]][max_y[i]]=com_color;
    put(com_color,coordinate,max_x[i],max_y[i]);
    return 0;
}

int main (){
    int total=4;
    int x;
    int y;
    int coordinate[8][8];
    int color;
    int put_x;
    int put_y;
    int error;
    int can_put;
    int player;
    int turn;
    int com_color;
    int com_color2;
    int total_max=64;
    int skip;
    int priority[8][8] = {{120,-20,20,5,5,20,-20,120},
                            {-20,-40,-5,-5,-5,-5,-40,-20},
                            {20,-5,15,3,3,15,-5,20},
                            {5,-5,3,3,3,3,-5,5},
                            {5,-5,3,3,3,3,-5,5},
                            {20,-5,15,3,3,15,-5,20},
                            {-20,-40,-5,-5,-5,-5,-40,-20},
                            {120,-20,20,5,5,20,-20,120}};


    srand(time(NULL));

    system("clear");

//logをリセット
    for(x=0;x<64;x++){
       log_x[x]=0;
       log_y[x]=0;
       log_color[x]=0;
       log_white[x]=0;
       log_black[x]=0;
    }

    
//プレイ人数確認
    error=1;
    while(error>0){
        error=0;
        cout<<"対戦方法を選択してください。\nコンピューターと対戦する場合は１、二人で対戦する場合は２を、コンピューター同士で対戦させたい場合は３入力してください。\n";
        cin>>player;
        if(player<1 || player>3){
            error++;
        }
    }
    
//先攻後攻
    system("clear");
    if(player==1){
        cout<<"ランダムに先攻後攻を決定します。\n";
        turn=rand()%2+1;
        if(turn==1){
            com_color=2;
            cout<<"あなたは先攻の黒です。\n";
        }else if(turn==2){
            cout<<"あなたは後攻の白です。\n";
            com_color=1;
        }
    }else if(player==3){
        com_color=1;
        com_color2=2;
    }

//オセロ盤リセット
    for(y=0;y<8;y++){
        for (x=0;x<8;x++){
            coordinate[y][x] = 0;
        }
    }

//オセロ盤　最初の4つの石配置
    coordinate[3][4] = 1;
    coordinate[4][3] = 1;
    coordinate[3][3] = 2;
    coordinate[4][4] = 2;

//オセロ盤を表示
    color=1;
     situation(coordinate,color);
    can_put=display(coordinate,skip);
    
    //ゲームスタート
    while(total<total_max){
        error=1;
        if(can_put==0){
            system("clear");
            if(color==1){
                cout<<"黒の石を置ける場所がないため、黒はスキップしました。\n";
                skip++;
            }else if(color==2){
                cout<<"白の石を置ける場所がないため、白はスキップしました。\n";
                skip++;
            } 
        }else{
            skip=0;
            while(error>0){
                if(color==1){
                    cout<<"黒のターンです。\n石を置きたい場所の座標を入力してください。\n";
                }else if (color==2){
                    cout<<"白のターンです。\n石を置きたい場所の座標を入力してください。\n";
                }
                if(com_color==color && player==1){
                    com_put(coordinate,priority,com_color);
                    error=0;
                    total++;
                }else if(player==3){
                    com_put(coordinate,priority,color);
                    error=0;
                    total++;
                }else{
                error=0;
                cin>>put_x;
                cin>>put_y;
                system("clear");
                error=error_count(color,put_x-1,put_y-1,coordinate);
                if(error==0){
                    coordinate[put_x-1][put_y-1]=color;
                    put(color,coordinate,put_x-1,put_y-1);
                    total++;
                    break;
                }else if(error>0){
                    display(coordinate,skip);
                    cout<<"その位置に石を置くことはできません。\n再度、座標を入力してください。\n";
                } 
                }
            }
        }    
        cout<<"合計"<<total<<"個\n";
        if(color==1){
            color=2;
        }else if(color==2){
            color=1; 
        }
        situation(coordinate,color);
        can_put=display(coordinate,skip);
        if(flag==true){
            exit(0);
        }
    }
    exit(0);
    return 0;
 }