#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include <iostream>
#include <QByteArray>

using namespace std;

int rows = 5, cols = 7;
char matrix[] = "S..#....#...#..#.......##...#.#E.#.";

bool visited[5][7];

int sr = 0;
int sc = 0;

QList<int> rq;
QList<int> cq;

bool reach_end = false;
int move_cnt = 0;

int nodes_left = 1;
int nodes_in_next_step = 0;

void explore_neighbors(int r, int c){
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = { 0, 1, 0, -1};

    for(int i=0;i<4;i++){
        int rr = r+dr[i];
        int cc = c+dc[i];

        if(rr < 0 || rr >= rows) continue;
        if(cc < 0 || cc >= cols) continue;

        if(visited[rr][cc]) continue;
        if(matrix[rr*cols+cc] == '#') continue;

        rq.append(rr);
        cq.append(cc);
        visited[rr][cc] = true;
        nodes_in_next_step++;
    }
}

// return move cnt or -1[no path]
int solve(){
    rq.append(sr);
    cq.append(sc);
    visited[sr][sc] = true;

    while(rq.length() > 0){
        int cur_r = rq.takeFirst();
        int cur_c = cq.takeFirst();

        if(matrix[cur_r*cols+cur_c] == 'E'){
            reach_end = true;
            break;
        }

        explore_neighbors(cur_r, cur_c);

        nodes_left--;
        if(nodes_left == 0){
            nodes_left = nodes_in_next_step;
            nodes_in_next_step = 0;
        }
        move_cnt++;
    }

    if(reach_end){
        return move_cnt;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"BFS test";

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            visited[i][j] = false;
        }

    }

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            std::cout << matrix[i*cols+j]<<' ';
        }
        std::cout << std::endl;
    }

    qDebug()<<solve();

    return a.exec();
}
