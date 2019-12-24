#include<iostream>
using namespace std;
#define size 5

//it is global variable to store the minimum final result
static int minimumTime = 3000;

//holes[][] 2-d array to store the two end points of a wormhole and cost/time
//to travel from it.
int holes[size][size];

//visited[] 1-d array tells the wormholes visited or not.
bool visited[size];

int abs(int x, int y){
	return ((x > y)? (x - y): (y - x));
}

int min(int a, int b){
	return ((a < b)? a : b);
}

void findMinTime(int sourceX, int sourceY, int destX, int destY, int distace, int wormholesCount){
	minimumTime = min(minimumTime, abs(sourceX, destX) + abs(sourceY, destY) + distace);

	// try to enter from all wormholes using back-tracking
	for(int i = 0; i < wormholesCount; i++){
		//if un-visited wormsholes then try to visit recursively and check minimum Time.
		if(!visited[i]){
			visited[i] = 1;	// Mark ith wormhole as visited

			//first try to enter from one end point and off from another end point of ith wormhole.
			//So total time required for that would be tempTime;
			int tempTime = abs(sourceX, holes[i][0]) + abs(sourceY, holes[i][1]) + distace + holes[i][4];
			findMinTime(holes[i][2], holes[i][3], destX, destY, tempTime, wormholesCount);

			//Now try for reverse end points that can also give minimum Time to reach to destination
			tempTime = abs(sourceX, holes[i][2]) + abs(sourceY, holes[i][3]) + distace + holes[i][4];
			findMinTime(holes[i][0], holes[i][1], destX, destY, tempTime, wormholesCount);

			visited[i] = 0;	// Mark ith wormhole as un-visited
		}
	}
}

int main(){

	//Spaceship source position in x-y plane is (sourceX, sourceY)
	int sourceX, sourceY;
	cin >> sourceX >> sourceY;

	//Spaceship Destination position in x-y plane is (destX, destY)
	int destX, destY;
	cin >> destX >> destY;

	//Spaceship can use wormholes to reach from source to destination
	int wormholesCount;
	cin >> wormholesCount;

	for(int i = 0; i < wormholesCount; ++i){
		//wormholes end points, (e1x, e1y) <-----Cost-----> (e2x, e2y)
		cin >> holes[i][0] >> holes[i][1]
			>> holes[i][2] >> holes[i][3]
			>>holes[i][4]; 
	}

	findMinTime(sourceX, sourceY, destX, destY, 0, wormholesCount);

	cout<< minimumTime <<"\n";

	return 0;
}
