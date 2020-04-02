//
// Created by Zilin Xiao on 2020/4/2.
//

#include "CircuitFinderGit.h"
#include <algorithm>
#include <vector>
#include <ctime>
#define DEBUG

using namespace std;

const int maxn = 6020;


// 离散化

// 离散化End


bool cmp(const vector<int>& a, const vector<int>& b){
    if(a == b) return false;
    if(a.size() != b.size()) return a.size() < b.size();
    int idx = 0;
    while(a[idx] == b[idx]) idx++;
    return a[idx] < b[idx];
}

inline void parseLine(char* line, int& from, int& to, int& amount){
    char* prev = line;
    while(*line != ',') line++;
    *line = '\0';
    from = atoi(prev);
    prev = line + 1;
    while(*line != ',') line++;
    *line = '\0';
    to = atoi(prev);
    prev = line + 1;
    amount = atoi(prev);
}

int main(){
    #ifdef DEBUG
    clock_t start, end;
    start = clock();
    #endif

    CircuitFinder<maxn> c;
    FILE *fp;
    char line[99]; // 3 * 32 + 2 + 1
    int from, to, amount;
    fp = fopen("test_data.txt", "r");
    assert(fp != nullptr);
    while(!feof(fp)){
        if(fgets(line, 99, fp) == nullptr) break;
        parseLine(line, from, to, amount);
        c.add(from, to);
    }

    c.run();
    sort(c.Ans.begin(), c.Ans.end(), cmp);
    FILE *wfp;
    char wline[256] = {0}; // 7 * 32 + 6 + 1 + 1 = 256
    char num[34];
    wfp = fopen("my_result.txt", "w");

    fprintf(wfp, "%d\n", int(c.Ans.size()));

    for(int i = 0; i < c.Ans.size(); i++){
        sprintf(num, "%d", c.Ans[i][0]);
        strcat(wline, num);
        for(int j = 1; j < c.Ans[i].size(); j++){
            sprintf(num, ",%d", c.Ans[i][j]);
            strcat(wline, num);
        }
        fprintf(wfp, "%s\n", wline);
        memset(wline, 0, sizeof(wline));
    }

    fclose(wfp);

    #ifdef DEBUG
    end = clock();
    printf("Time: %lf s\n", (double)(end - start) / CLOCKS_PER_SEC);
    #endif

    return 0;
}