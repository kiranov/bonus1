#include <iostream>
#include <cmath>
#include "bonus4.cpp"
#include "stdint.h"

using namespace std;

typedef struct Subsets{
    //int;
    int flag;
}Subsets;


class Search_kliks {
public:
    uint64_t* adj_m1, adj_m2; // матрица смежности
    Graph G1, G2;
    Subsets *subset1, *subset2;
    size_t size, sub_size;
    Search_kliks(Graph G1){
        // temp
        size = G1.size;
        this->G1 = G1;
        adj_m1 = new uint64_t[G1.size];	
        massive(G1, adj_m1);
        //
        
        sub_size = (int)pow(2, size);
        this->inizialise_subset(&subset1);
        this->inizialise_subset(&subset2);
        //
        subset1[0].flag = 1;
        tree_search(0, size-1);
        print_kliks();
    }

    void inizialise_subset(Subsets **subset) {
        *subset = new Subsets[sub_size];
    }


    void tree_search(uint64_t i, int level) {
        if(!(level >= 0)) return;
        
        uint64_t right_c = (i|(((uint64_t)1)<<level));
        if((right_c & adj_m1[size-level-1]) == right_c) {
            subset1[right_c].flag = 1;
            tree_search(right_c, level-1);
        }
        subset1[i].flag = 1;
        tree_search(i, level-1);
    }


    void print_kliks() {
        for(uint64_t i = 0; i < sub_size; i++) {
            if(subset1[i].flag == 1)
                cout << i << " ";
        }
        //cout << sub_size;
    }
};
int main() {

    Graph G(5);
    G.AddEdge(0,1);
	G.AddEdge(0,2);
	G.AddEdge(0,4);
    G.AddEdge(1,2);
	G.AddEdge(1,3);
	//G.AddEdge(2,4);

    for(size_t i = 0; i < G.size; i++){
        for(size_t j = 0; j < G.size; j++){
            cout << G.matrix[i][j] << " ";
        }
        cout << endl;
    }
    Search_kliks search(G);
}
