// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

#include <iostream>
#include <cstdlib>
#include <vector>

using std::cout; using std::endl; using std::cin; using std::vector;

// abstract body 
class Fill{
public:
   Fill(char fillChar, char borderChar = ' '): fillChar_(fillChar), borderChar_(borderChar==' ' ? fillChar : borderChar) {};
   virtual char getBorder()=0;
   virtual char getInternal()=0;
   virtual ~Fill() {}
protected:
   char fillChar_;
   char borderChar_;
};

// concrete body
class Hollow: public Fill{
public:
   Hollow(char fillChar):Fill(fillChar){}
   char getBorder() override {return fillChar_;}
   char getInternal() override {return ' ';}
   ~Hollow() override {}
};


// another concrete body
class Filled: public Fill {
public:
   Filled(char fillChar):Fill(fillChar){}
   char getBorder() override {return fillChar_;}
   char getInternal() override {return borderChar_;}
   ~Filled() override {}
};

class FullyFilled: public Fill{
   public:
      FullyFilled(char fillChar, char borderChar) : Fill(fillChar, borderChar) {};
      char getBorder() override {return fillChar_;};
      char getInternal() override {return borderChar_;};
      ~FullyFilled() override {};
};

class RandomFilled: public Fill{
   public:
      RandomFilled(vector<char> charList) : charList_(charList), Fill(' ') {};
      char getBorder() override {return getRandomChar();};
      char getInternal() override {return getRandomChar();};
      ~RandomFilled() override {}
   private:
      vector<char> charList_;
      char getRandomChar() { return charList_[rand() % charList_.size()];};
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};

void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}

class Triangle: public Figure {
public:
   Triangle(int size, Fill *fill): Figure(size, fill) {}
   void draw() override {
      for (int i = 0; i < size_; ++i) {
         for (int j = 0; j <= i; ++j) {
            if (i == size_ - 1 || j == 0 || j == i)
               cout << fill_->getBorder();
            else
               cout << fill_->getInternal();
         }
         cout << endl;
      }
   };
};

int main(){

  
   Fill* hollowPaintJ = new Hollow('&');
   Fill* filledPaintStar = new Filled('@');
   Fill* filledborder = new FullyFilled('8', '/');
   vector<char> charList = {'*', '#', '$', '%', '&', '@', '!', '^', '+', '~', '<', '>', '/', '\\', '|', '-', '=', '?', '`', ':', ';', ',', '.', '(', ')', '{', '}', '[', ']', '_', '\'', '"'};
   Fill* random = new RandomFilled(charList);

   
   Figure *smallBox = new Square(6, hollowPaintJ);
   Figure *bigBox = new Square(15, filledPaintStar);
   Figure *filledBox = new Square(10, filledborder);
   Figure *randomBox = new Square(8, random);
   
   smallBox->draw();
   cout << endl;
   bigBox -> draw();
   cout << endl;
   filledBox -> draw();
   cout << endl;
   randomBox -> draw();

   cout << endl;
   Figure* ahhah = new Triangle(8,filledborder);
   ahhah->draw();
   
   
   /*
   // ask user for figure parameters
   cout << "Enter fill character: "; 
            char fchar; cin >> fchar;
   cout << "Filled or hollow? [f/h] "; 
           char ifFilled; cin >> ifFilled;
   cout << "Enter size: "; int size; cin >> size;
   */
   /*
   Figure *userBox = new Square(size, ifFilled == 'f'? 
	       static_cast<Fill *>(new Filled(fchar)):
	       static_cast<Fill *>(new Hollow(fchar))
	       ); 
   */
      
   /*
   Figure *userBox = ifFilled == 'f'?
      new Square(size, new Filled(fchar)):
      new Square(size, new Hollow(fchar));
   
   
   userBox -> draw();
   cout << endl;
   */
}
