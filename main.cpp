#include <iostream>
#include <math.h>
using namespace std;

int n=3;
double A[3][3]={               //係数行列A
    {5, 1, 1},
    {1, 4, 1},
    {2, 1, 3}
};
double b[3]={10, 12, 13};       //ベクトルb

double x[3];                    //解ベクトルx
double x0[3];                   //解ベクトルの1つ前の値を保存する配列


double error = 0.0001;          //収束判定誤差

int main(){
    bool flag=false;            //狭義行対角優位行列の判定を1度のみ出力するためのフラグ
    double lside;               //左辺の合計を保存　x[i]==lsideになる 
    double sum=0.0;             //狭義行対角優位を判別するための合計値

    //nを入力
    cout << "n元連立1次方程式" << endl;
    cout << "n=:";
    cin >> n;

    //Aを入力
    



    for(int i=0; i<n; i++){     //x, x0を初期化
        x[i]=1.0;
        x0[i]=0.0;
    }

    for(int k=0; k<100; k++){    //100回繰り返すfor
        for(int i=0; i<n; i++){ //収束判定
            if(x[i]<x0[i]-error || x[i]>x0[i]+error)    //収束してなかったら抜ける
                break;
            else if(i==n-1){
                cout<<k+1<<"回目で収束しました"<<endl;
                goto output;    //最後まで確認したら2重ループを抜けて出力へ
            }
        }
        for(int i=0; i<n; i++){ //行のfor    
            lside = b[i];
            for(int j=0; j<n; j++){ //列のfor
                if(i==j)continue;    //対角成分のときは計算不用
                sum += fabs(A[i][j]);  //A[i][j]の絶対値を加算する
                lside -= A[i][j]*x[j]; //lsideを計算
            }
            if(!flag && fabs(A[i][i])<=sum){
                cout<<"狭義行対角優位行列ではない"<<endl;
                flag = true;
            }
            x0[i]=x[i];                //xをx0に代入
            x[i]=lside/A[i][i];        //xを計算
            sum=0.0;                   //sumを初期化
        }
    }
    cout<<"収束しませんでした"<<endl;
    for(int i=0; i<n; i++)  //結果を出力
        cout <<"x"<<i<<"="<< x[i] << endl;
    return 0;   //プログラム終了

    output:                 //収束したらここにくる
    for(int i=0; i<n; i++)  //結果を出力
        cout <<"x"<<i<<"="<< x[i] << endl;
    return 0;
}