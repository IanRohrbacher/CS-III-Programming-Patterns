// figures: object adapter pattern
// Mikhail Nesterenko
// 11/7/2022

#include <iostream>

using std::cout;
using std::endl;

// implementer/adaptee
class LegacyRectangle {
   public: LegacyRectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) : topLeftX_(topLeftX), topLeftY_(topLeftY), bottomRightX_(bottomRightX), bottomRightY_(bottomRightY) {}

      void oldDraw() const {
         for (int i = 0; i < bottomRightY_; ++i)
         {
            for (int j = 0; j < bottomRightX_; ++j)
               if (i >= topLeftY_ && j >= topLeftX_)
                  cout << '#';
               else
                  cout << ' ';
            cout << endl;
         }
      };
      void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
         topLeftX_ = topLeftX;
         topLeftY_ = topLeftY;
         bottomRightX_ = bottomRightX;
         bottomRightY_ = bottomRightY;
      }; //implements generic repositioning and resizing of the figure;
      int getTopLeftX() const {return topLeftX_;};
      int getTopLeftY() const {return topLeftY_;};
      int getBottomRightX() const {return bottomRightX_;};
      int getBottomRightY() const {return bottomRightY_;};

   private: // defining top/left and bottom/right coordinates
      int topLeftX_;
      int topLeftY_;
      int bottomRightX_;
      int bottomRightY_;
};

// target interface
class Square {
   public:
      virtual void draw() const = 0;
      virtual ~Square() {};
      virtual void resize(int newSize) {};
};

// adapter uses composition to delegate
// requests to adaptee
class SquareAdapter : public Square {
   public:
      SquareAdapter(int size) {
         adaptee_ = new LegacyRectangle(0, 0, size, size);
      }
      void draw() const override {
         adaptee_->oldDraw();
      }
      int size() const {
         return (adaptee_->getBottomRightX() - adaptee_->getTopLeftX()) * (adaptee_->getBottomRightY() - adaptee_->getTopLeftY());
      }
      void resize(int newSize) {
         adaptee_->move(adaptee_->getTopLeftX(), adaptee_->getTopLeftY(), newSize, newSize);
      }

   private:
      LegacyRectangle *adaptee_;
};

int main() {
   Square *square = new SquareAdapter(15);
   square->draw();
   std::cout << "Enter new size: ";
   int newSize;
   std::cin >> newSize;
   square->resize(newSize);
   square->draw();
   delete square;
   return 0;
}
