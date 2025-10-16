#ifndef DRINK_HPP
#define DRINK_HPP

#include <string>

using String = std::string;

enum class DrinkType {small, medium, large};

class Drink{
   public:
      Drink(DrinkType type=DrinkType::small): type_(type){}
      virtual ~Drink() {};

      virtual int getPrice() const {return   (type_ == DrinkType::small) ? 5 : 
                                             (type_ == DrinkType::medium) ? 7 : 
                                             (type_ == DrinkType::large) ? 15 : 0;};
      virtual String getType() const {return (type_ == DrinkType::small) ? "small" : 
                                             (type_ == DrinkType::medium) ? "medium" : 
                                             (type_ == DrinkType::large) ? "large" : "";};
      virtual String getIngredient() const {return "";};
      String getName() const {return name_;};

      void setName(String name) {name_ = name;};
   private: 
      int price_;
      DrinkType type_;
      String name_;
};

class Sugar : public Drink {
   public:
      Sugar(const Drink* wrapper) : wrapper_(wrapper) {};

      virtual int getPrice() const override {return wrapper_->getPrice() + defaultprice_;};
      virtual String getType() const override {return wrapper_->getType();};
      virtual String getIngredient() const override { return wrapper_->getIngredient() + " " + defaultIngredient_;};
   private:
      const int defaultprice_ = 1;
      const String defaultIngredient_ = "sugar";
      const Drink* wrapper_;
};

class Cream : public Drink {
   public:
      Cream(const Drink* wrapper) : wrapper_(wrapper) {};

      virtual int getPrice() const override {return wrapper_->getPrice() + defaultprice_;};
      virtual String getType() const override {return wrapper_->getType();};
      virtual String getIngredient() const override { return wrapper_->getIngredient() + " " + defaultIngredient_;};
   private:
      const int defaultprice_ = 2;
      const String defaultIngredient_ = "cream";
      const Drink* wrapper_;
};

class Honey : public Drink {
   public:
      Honey(const Drink* wrapper) : wrapper_(wrapper) {};

      virtual int getPrice() const override {return wrapper_->getPrice() + defaultprice_;};
      virtual String getType() const override {return wrapper_->getType();};
      virtual String getIngredient() const override { return wrapper_->getIngredient() + " " + defaultIngredient_;};
   private:
      const int defaultprice_ = 3;
      const String defaultIngredient_ = "honey";
      const Drink* wrapper_;
};

#endif
