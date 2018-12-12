#include <QCoreApplication>
#include <iostream>
#include <QVector>
#include <QPoint>

using namespace std;

#define ROWS 4
#define COLS 4

string m1 = "1000110101000111";
string m2 = "1000110111000111";

// R-D-L-U
int xdirs[4] = {1,0,-1,0};
int ydirs[4] = {0,1,0,-1};

bool is_safe(int x, int y, int matrix[ROWS][COLS], QVector<QPoint>& visited){

    return (x >=0) && (x < ROWS) && (y >= 0) && (y < COLS) && (matrix[x][y]) && (!visited.contains(QPoint(x, y)));
}

bool rat_go(int x, int y, int matrix[ROWS][COLS], QVector<QPoint>& visited){
    // base case
    if(visited.contains(QPoint(3,3))) return true;

    for (int i=0;i<ROWS;i++) {
        int cx = x + xdirs[i];
        int cy = y + ydirs[i];

        if(is_safe(cx, cy, matrix, visited)){
            visited.append(QPoint(cx,cy));
            if(rat_go(cx, cy, matrix, visited)){
                return true;
            }
        }
    }
    visited.pop_back();
    return false;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int maze1[ROWS][COLS];
    int maze2[ROWS][COLS];
    for (int i=0;i<ROWS;i++) {
        for (int j=0;j<COLS;j++) {
            maze1[j][i] = m1[i*ROWS+j] - '0';
            maze2[j][i] = m2[i*ROWS+j] - '0';
        }
    }
    cout <<endl<< "maze1:"<<endl;
    for (int i=0;i<ROWS;i++) {
        for (int j=0;j<COLS;j++) {
            cout<< maze1[j][i] << " ";
        }
        cout<<endl;
    }

    cout<<endl<<"maze2:"<<endl;
    for (int i=0;i<ROWS;i++) {
        for (int j=0;j<COLS;j++) {
            cout<< maze2[j][i] << " ";
        }
        cout<<endl;
    }
    cout<<endl;


    // driver function start
    QVector<QPoint> visited;
    // add source
    visited.append(QPoint(0,0));

    if(rat_go(0,0, maze1, visited)){
        cout<<visited.length()<<endl;
        for (int i = 0 ;i< visited.length();i++) {

            cout<<visited.at(i).x()<<"-"<<visited.at(i).y()<<endl;
        }
    }else{
        cout<<"no solution for maze 1"<<endl;
    }

    cout<<endl;
    // reset visited
    visited.clear();
    visited.append(QPoint(0,0));
    if(rat_go(0,0, maze2, visited)){
        cout<<visited.length()<<endl;
        for (int i = 0 ;i< visited.length();i++) {

            cout<<visited.at(i).x()<<"-"<<visited.at(i).y()<<endl;
        }
    }else{
        cout<<"no solution for maze 2"<<endl;
    }
    return a.exec();
}
