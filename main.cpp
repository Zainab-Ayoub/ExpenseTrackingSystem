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

void updateExpense(Category* head, int id){
    while(head){
        Expense* expenseNode = head->expenses;
        while(expenseNode){
            if(expenseNode->id == id){
                float newAmount;
                cout<<"New Amount: ";
                cin>>newAmount;
                cin.ignore();
              
                string newDescription;
                cout<<"New Description: ";
                getline(cin,newDescription);

                string newDate;
                cout<<"New Date: ";
                getline(cin,newDate);

                head->totalSpent -= expenseNode->amount;
                expenseNode->amount = newAmount;
                expenseNode->description = newDescription;
                expenseNode->date = newDate;
                head->totalSpent += newAmount;

                cout<<"Expense updated.\n";
                return;
            }
            expenseNode = expenseNode->next;
        }
        head = head->next;
    }
    cout<<"Expense not found!\n";
}

void deleteExpense(Category* head, int id){
    while(head){
        Expense* prev = nullptr;
        Expense* curr = head->expenses;
        while(curr){
            if (curr->id == id){
                if(prev){
                    prev->next = curr->next;
                } else{
                    head->expenses = curr->next;
                }
                head->totalSpent -= curr->amount;
                delete curr;
                
                cout<<"Expense deleted.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        } 
        head = head->next;
    }
    cout<<"Expense not found.\n";
}

void mostExpensiveExpense(Category* head){
    Expense* mostExp = nullptr;
    while(head){
        Expense* expenseNode = head->expenses;
        while(expenseNode){
            if(!mostExp || expenseNode->amount > mostExp->amount){
                mostExp = expenseNode;
            }   expenseNode = expenseNode->next;
        }
        head = head->next;
    }
    if(mostExp){
        cout<<"Most expensive: [ID: "<<mostExp->id<<"] $"<<mostExp->amount<<" - "<<mostExp->description<<" ("<<mostExp->date<<")\n";
    } else{
        cout<<"No expenses found.\n";
    }
}

void showAllCategories(Category* head){
    while(head){
        cout<<"- "<<head->name<<" ($"<<head->totalSpent<<")\n";
        head = head->next;
    }
}

void cleanup(Category* head){
    while(head){
        Expense* expenseNode = head->expenses;
        while(expenseNode){
            Expense* temp = expenseNode;
            expenseNode = expenseNode->next;
            delete temp;
        }
        Category* temp = head;
        head = head->next;
        delete temp;
    }
}

int main(){
    Category* categories = nullptr;
    int choice;
    do{
        cout<<"\n--- Expense Tracker ---\n";
        cout<<"1. Add Category\n2. Add Expense\n3. View Expenses\n4. Update Expense\n5. Delete Expense\n6. Most Expensive Expense\n7. Show All Categories\n0. Exit\nEnter Choice: ";
        cin>>choice;

        cin.ignore();

        string name, description, date;
        float amount;
        int id;

        switch(choice){
            case 1:
                cout<<"Category Name: ";
                getline(cin, name);

                addCategory(categories, name);
                break;

            case 2:
                cout<<"Category: ";
                getline(cin, name);

                cout<<"Amount: ";
                cin>>amount;
                cin.ignore();

                cout<<"Description: ";
                getline(cin, description);

                cout<<"Date: ";
                getline(cin, date);

                addExpense(categories, name, amount, description, date);
                break;    

            case 3:
                cout<<"Category: ";
                getline(cin, name);

                viewExpenses(categories, name);
                break;

            case 4:
                cout<<"Expense ID to Update: ";
                cin>>id;
                cin.ignore();

                updateExpense(categories, id);
                break;

            case 5:
                cout<<"Expense ID to Delete: ";
                cin>>id;
                cin.ignore();

                deleteExpense(categories, id);
                break;  

            case 6:
                mostExpensiveExpense(categories);
                break;

            case 7:
                showAllCategories(categories);
                break;
        }
    } while(choice != 0);

    cleanup(categories);
}