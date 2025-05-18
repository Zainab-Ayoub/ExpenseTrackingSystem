#include<iostream>
using namespace std;

struct Expense{
    int id;
    float amount;
    string description;
    string date;
    Expense* next;
    static int idCounter;

    Expense(float amt, string desc, string dt){
        amt = amount;
        desc = description;
        date = dt;
        next = nullptr;
        id = idCounter++;
    }
};
int Expense::idCounter = 0;

struct Category{

};

Category* findCategory(Category* head, string name){

}

void addCategory(){

}

void addExpense(){

}

void viewExpense(){

}

void updateExpense(){

}

void deleteExpense(){

}

void mostExpensiveExpense(){

}

void showAllCategories(){

}

void cleanup(){

}

int main(){

}