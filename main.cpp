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
    string name;
    float totalSpent = 0;
    Expense* expenses;
    Category* next;

    Category(string n){
        n = name;
        expenses = nullptr;
        next = nullptr;
    }
};

Category* findCategory(Category* head, string name){
    while(head){
        if(head->name == name){
            return head;
        }
        head = head->next;    
    }
    return nullptr;
}

void addCategory(Category* head, string name){
    if(findCategory(head, name)){
        cout<<"Category already exists.\n";
        return;
    } 
    Category* newnode = new Category(name);
    newnode->next = head;
    head = newnode;
    cout<<"Category Added!\n";
}

void addExpense(Category* head, string categoryName, float amount, string description, string date){
    Category* categoryNode = findCategory(head, categoryName);
    if(!categoryNode){
        cout<<"Category not found!\n";
        return;
    } 
    Expense* expenseNode = new Expense(amount, description, date);
    expenseNode->next = categoryNode->expenses;
    categoryNode->expenses = expenseNode;
    categoryNode->totalSpent += amount;
    cout<<"Expense added.\n";
}

void viewExpenses(Category* head, string categoryName){
    Category* categoryNode = findCategory(head, categoryName);
    if(!categoryNode){
        cout<<"Category not found!\n";
    }
    Expense* expenseNode = categoryNode->expenses;
    if(!expenseNode){
        cout<<"No expenses.\n";
    }
    while(expenseNode){
        cout<<"[ID: "<<expenseNode->id
            <<"] $"<<expenseNode->amount
            <<" - "<<expenseNode->description
            <<" ("<<expenseNode->date<<")\n";
        expenseNode = expenseNode->next;    
    }
    cout<<"Total spent in "<<categoryName<<": $"<<categoryNode->totalSpent<<endl;
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