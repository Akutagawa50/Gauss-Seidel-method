#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int n=0;
double x[10];                    
double x0[10];                   
double A[10][10];
double b[10];      
double error = 0.0001;          //収束判定誤差
int main(){
    bool flag=false;            //狭義行対角優位行列の判定を1度のみ出力するためのフラグ
    double lside;               //左辺の合計を保存　x[i]==lsideになる 
    double sum=0.0;             //狭義行対角優位を判別するための合計値

    //nを入力
    cout << "n元連立1次方程式(1<n<=10)" << endl;
    cout << "n=";
    cin >> n;
    
    //Aを入力
    cout << "係数行列Aを入力" << endl;
    for(int i=0; i<n; i++){
        cout << i+1 << "行目:" << endl;
        for(int j=0; j<n; j++){
            cin >> A[i][j];
        }
    }

    //bを入力
    cout << "定数項ベクトルbを入力 " << endl;
    for(int i=0; i<n; i++){
            cin >> b[i];
    }
    cout << endl; //見栄えを気にして改行

    //x, x0を初期化
    for(int i=0; i<n; i++){     
        x[i]=1.0;
        x0[i]=0.0;
    }

    //ガウス＝ザイデル法で計算
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
        cout <<"x"<<i<<"="<< fixed << setprecision(10) << x[i] << endl;
    return 0;
}