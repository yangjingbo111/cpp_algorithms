#include <QCoreApplication>

#define ROWS    8
#define COLS    8

int step = 0;
int xdirs[8] = { 1,  2, 2, 1, -1, -2, -2, -1};
int ydirs[8] = {-2, -1, 1, 2,  2,  1, -1, -2};

bool is_safe(int x, int y, int matrix[ROWS][COLS]){
    return (x >= 0) && (x <= ROWS-1) && (y >= 0) && (y <= COLS-1) && (matrix[x][y] == 0);
}

bool knight_tour(int x, int y, int matrix[ROWS][COLS]){
    // base case
    if(step == 63) return true;

    for (int i=0;i<8;i++) {
        int cx = x + xdirs[i];
        int cy = y + ydirs[i];
        if(is_safe(cx, cy, matrix)){
            step += 1;
            matrix[cx][cy]=step;
            bool res = knight_tour(cx, cy, matrix);
            if(res) return true;
        }
    }

    // try all directions, none satisfied
    step -= 1;
    matrix[x][y] = 0;
    return false;
}

#include <QDebug>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int matrix[ROWS][COLS];
    for (int i=0;i<ROWS;i++) {
        for (int j=0;j<COLS;j++) {
            matrix[i][j]=0;
        }
    }

    // print the initial matrix
    for (int i=0;i<ROWS;i++) {
        for (int j=0;j<COLS;j++) {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    if(knight_tour(0,0, matrix)){
        for (int i=0;i<ROWS;i++) {
            for (int j=0;j<COLS;j++) {
                cout<<matrix[i][j]<<"\t";
            }
            cout<<endl;
        }
    }else{
        qDebug()<<"no solution";
    }

    return a.exec();
}
