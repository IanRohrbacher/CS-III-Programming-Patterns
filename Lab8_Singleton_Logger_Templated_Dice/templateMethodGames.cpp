// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;
using String = std::string;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
         makeMove(i);
         if (i==playersCount_-1) 
	      ++movesCount_; 
      }
      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	      const int chance = (rand() % maxMoves_) / experience_[player];
	      if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 5; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};

class RockPaperScissors: public Game {
   public:
      void initializeGame() {
         firstPlayer_ = ' ';
         secondPlayer_ = ' ';         
      }
      void makeMove(int player) {
         if(player == 0) {
            int computer = rand() % 3;
            switch (computer) {
               case 0:
                  firstPlayer_ = 'r';
                  break;
               
               case 1:
                  firstPlayer_ = 'p';
                  break;
               
               case 2:
                  firstPlayer_ = 's';
                  break;
            }
         } else if(player == 1) {
            char human;
            do {
               std::cout << "Human, (r)ock, (p)aper, or (s)cissors? ";
               std::cin >> human;
            } while (human != 'r' && human != 'p' && human != 's');
            secondPlayer_ = human;
         }
         if(firstPlayer_ != ' ' and secondPlayer_ != ' ') {
            cout << "Computer selected ";
            if (firstPlayer_ == 'r') {
               cout << "rock. ";
            } else if (firstPlayer_ == 'p') {
               cout << "paper. ";
            } else if (firstPlayer_ == 's') {
               cout << "scissors. ";
            }
            if(firstPlayer_ == secondPlayer_) {
               cout << "It's a tie!" << endl;
               playerWon_ = -1;
               initializeGame();
            } else if((firstPlayer_ == 'r' && secondPlayer_ == 's') || (firstPlayer_ == 'p' && secondPlayer_ == 'r') || (firstPlayer_ == 's' && secondPlayer_ == 'p')) {
               playerWon_ = 0;
            } else {
               playerWon_ = 1;
            }
         }
      }
      void printWinner() {
         if(playerWon_ == 0) {
            cout << "Computer wins!" << endl;
         } else if (playerWon_ == 1) {
            cout << "Human wins!" << endl;
         }
      }

   private:
      char firstPlayer_;
      char secondPlayer_;

};

int main(int argc, char* argv[]) {
   bool argvBool = ("1" == String(argv[1]));

   srand(time(nullptr));

   Game* gp = nullptr;

   if(!argvBool) {
      // play chess 7 times
      for (int i = 0; i < 7; ++i){ 
         gp = new Chess;
         gp -> playGame(2); 
         delete gp;
      }
         
   
      // play monopoly 7 times
      for (int i = 0; i < 7; ++i){
         gp = new Monopoly;
         gp -> playGame(); 
         delete gp;
      }
   }
   // play rock paper scissors until game is won
   gp = new RockPaperScissors;
   gp -> playGame(2); 
   delete gp;
}
