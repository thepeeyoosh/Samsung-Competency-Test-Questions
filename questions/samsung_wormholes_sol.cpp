//=================================================================================================
//				Coded By Peeyoosh Kumar Gupta					===
//=================================================================================================

//=================================================================================================
//			Samsung Wormholes spaceship Problem and Solution			===
//=================================================================================================
//Question::
// There is a source (S) and destination (D) and a spacecraft has to go from S to D. There are N number of wormholes in between
// which has following properties:
//  Each wormhole has an entry and an exit.
//  Each wormhole is bi-directional i.e. one can enter and exit from any of the ends.
// The time to cross the wormhole is given and the spacecraft may or may not use the wormhole to reach D.
// The time taken to travel outside wormhole between two points (x1, y1) and (x2, y2) is given  
// by a formula |x1 - x2| + |y1 - y2| where, (x1, y1) and (x2, y2) are the coordinates of two points.
// The coordinates of S and D are given and we have to find the minimum time to reach D from S.
// Note: It’s not mandatory to consider all the wormholes
// Example : 
//source=(0,0), destination(100,100), wormholes=3
// coordinates are:          
// (1,2),(120,120) Cost = 5
// (4,5),(120,100) Cost = 21
// (6,8),(150,180) Cost = 23
//
// Sample output=48
//
// Explanation:
// Cost from (0,0) to (1,2) is 3
// Cost of wormhole 1 is 5
// Cost from (120,120) to (100,100) is 40
// So, total 48 


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
