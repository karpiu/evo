#include <iostream>
#include <vector>

#include "permutation.hpp"
#include "crossover.hpp"

using namespace std;

int main(void) {
	srand(time(0));	
	int t1[10] = {1,2,3,4,5,6,7,8,9,0};
	int t2[10] = {0,2,4,6,8,1,3,5,7,9};
	vector<int> v1(t1,t1+10), v2(t2,t2+10);
	permutation p1(v1), p2(v2);
	pair<permutation, permutation> para = crossover::random_cx(p1,p2);
	cout<<para.first<<" "<<para.second<<"i\n";
	return 0;
}
