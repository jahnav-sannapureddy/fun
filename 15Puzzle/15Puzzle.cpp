#include <bits/stdc++.h>
#include <stdio.h>  
#include <conio.h>  
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
using namespace std;

class PuzzleGame{
	int n;
	vector<string> state;
	int empty;
	int moves = 0;
	int inverCount;
	
	int countInversions(){
		int inver = 0;
		
		for(int i=0; i<n*n-1; i++){
			if(state[i]=="_")	continue;
			for(int j=i+1; j<n*n; j++){
				if(state[j]=="_")	continue;
				if(stoi(state[i])>stoi(state[j])){
					inver++;
				}
			}
		}	
		
		return inver;
	}
	
	bool isPossibleToWin(){
		// from the GFG article source:
		// https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
		int inver = this->countInversions();
		if(n&1){
			return !(inver&1);
		}
		auto p = this->findEmpty();
		int emptyColFromBottom = n-p/n;
		if(emptyColFromBottom&1){
			return !(inver&1);
		}
		return inver&1;
	}
	
	int findEmpty(){
		for(int i=0; i<n*n; i++){
			if(state[i]=="_"){
				this->empty = i;
				return i;
			}
		}
		return -1;
	}
	
	void makeMove(int move){
		this->empty = this->findEmpty();
		switch(move){
			case UP:
				if(empty/n!=0){
					swap(state[empty-n], state[empty]);
					empty-=n;moves++;
				}
				break;
			case DOWN:
				if(empty/n!=n-1){
					swap(state[empty+n], state[empty]);
					empty+=n;moves++;
				}
				break;
			case LEFT:
				if(empty%n!=0){
					swap(state[empty-1], state[empty]);
					empty--;moves++;
				}
				break;
			case RIGHT:
				if(empty%n!=n-1){
					swap(state[empty+1], state[empty]);
					empty++;moves++;
				}
				break;
			default:
				cout<<"INVALID"<<endl;
		}
	}
	
	void makeInitialState(){
		for(int i=0; i<n*n; i++){
			state[i] = to_string(i+1);
		}
		state[n*n-1] = "_";
	}
	
	void makeShuffleState(int reps){
		shuffle(state.begin(), state.end(), default_random_engine(time(0)));
	}

	bool checkWinningState(bool check){
		for(int i=0; i<n*n; i++){
			if(state[i]!=to_string(i+1) && state[i]!="_"){
				return false;
			}
		}
		if(!check){
			cout<<"CONGRATULATIONS  \\^o^/  \n";
			cout<<"YOU HAVE COMPLETED THE PUZZLE IN "<<moves<<" MOVES"<<endl;
		}
		return true;
	}
	
	void printState(){
		for(int i=0; i<n*n; i++){
			cout<<setw(3)<<state[i]<<" ";
			if((i+1)%n==0)
				cout<<"\n";
		}
		cout<<"\nPercentage solved: "<<max((float)0, (float)100.0-(float)countInversions()*100/inverCount)<<"% \n";
		cout<<"Number of moves: "<<this->moves<<"\n";
	}
	
	public:
	PuzzleGame(int n){
		this->n = n;
		this->state.resize(n*n);
		this->makeInitialState();
		int cnt = 0;
		while((this->checkWinningState(true) || (!this->isPossibleToWin())) &&(cnt<10000)){
			this->printState();
			this->makeShuffleState(n*n);
			cnt++;
		}
		if(cnt>=9999){
			exit(0);
		}
	}
	void startGame(){
		this->inverCount = this->countInversions();
		system("cls");
		system("color 02");
		this->printState();
		int c = -1;
		while(c != 0){
			c = getch();
			if(c==224){
				c = getch();
				makeMove(c);
				system("cls");
				printState();
				if(checkWinningState(false)){
					return;
				}
			}
		}
	}
};

int main(){
	system("color 61");
	cout<<"----- USE ARROW KEYS FOR CONTROL IN PUZZLE AND OPEN IN COMMAND PROMPT -----"<<endl;
	cout<<"Enter the width of the puzzle (ex: 4 range: 2-8): ";
	int n;
	cin>>n;
	if(n<2 || n>8)	exit(1);
	PuzzleGame *pg = new PuzzleGame(n);
	pg->startGame();
	return 0;
}
