//
// Created by Zilin Xiao on 2020/4/2.
//

#ifndef HUAWEICOMPETITION_CIRCUITFINDERGIT_H
#define HUAWEICOMPETITION_CIRCUITFINDERGIT_H

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

typedef std::list<int> NodeList;

template<int N>
class CircuitFinder
{
public:
    std::vector<NodeList> AK; // Graph
    std::vector<int> Stack;  // TODO: deque
    std::vector<bool> Blocked; // TODO: set maybe better
    std::vector<NodeList> B;  // TODO: map
    std::vector<std::vector<int> > Ans; // Answer
    int S;

    void unblock(int U);
    bool circuit(int V);
    void output();

public:
    CircuitFinder() : AK(N), Blocked(N), B(N) {}
    void add(int u, int v){
        AK[u].push_back(v);
    }
    void run();
};

template<int N>
void CircuitFinder<N>::unblock(int U)
{
    Blocked[U] = false;
    while (!B[U].empty()) {
        int W = B[U].front();
        B[U].pop_front();

        if (Blocked[W]) {
            unblock(W);
        }
    }
}

template<int N>
bool CircuitFinder<N>::circuit(int V)
{
    bool F = false;
    Stack.push_back(V);
    Blocked[V] = true;

    for (int W : AK[V]) {
        if (W == S) {
            output();
            F = true;
        } else if (!Blocked[W]) {
            if(circuit(W))
                F = true;
        }
    }

    if (F) {
        unblock(V);
    } else {
        for (int W : AK[V]) {
            auto IT = std::find(B[W].begin(), B[W].end(), V);
            if (IT == B[W].end()) {
                B[W].push_back(V);
            }
        }
    }

    Stack.pop_back();
    return F;
}

template<int N>
void CircuitFinder<N>::output()
{
//    std::cout << "circuit: ";
    if(Stack.size() < 3 || Stack.size() > 7) return; // 在查找过程中就可限定查找长度
    Ans.push_back(std::vector<int>(Stack.size()));

    for(int i = 0; i < Stack.size(); i++){
        Ans.back()[i] = Stack[i];
    }
}

template<int N>
void CircuitFinder<N>::run()
{
    Stack.clear();
    S = 1;

    while (S < N) {
        for (int I = S; I <= N; ++I) {
            Blocked[I] = false;
            B[I].clear();
        }
        circuit(S);
        for (int I = S+1; I <= N; ++I)
            AK[I-1].remove(S);
        ++S;
    }
}

#endif //HUAWEICOMPETITION_CIRCUITFINDERGIT_H
