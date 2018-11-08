#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "ArgumentManager.h"

using namespace std;

class Product{
private:
    string item;
    double price;
    
public:
    Product(){
        item = " ";
        price = 0.0;
    }
    
    void setItem(string name){
        item = name;
    }
    
    void setPrice(double value)
    {
        price = value;
    }
    
    string getItem(){
        return item;
    }
    
    double getPrice(){
        return price;
    }
};

struct Node{
    Product info;
    Node *link;
};

class List{
private:
    Node *head;
    Node *current;
public:
    List(){
        head = NULL;
    }
    
    int counter = 0;
    int getCounter(){
        return counter;
    }
    
     double totalCost(){

        double cost = head->info.getPrice();
    
        Node *current;
        current = head;
        
        
        while(current->link != NULL)
        {
            current = current ->link;
            cost += current->info.getPrice();
            
        }
        return cost;
    }
    
    void add(string name, double price){
        Node *p = new Node;
        p->link = NULL;
        p->info.setItem(name);
        p->info.setPrice(price);
        if (head == NULL)
        {
            head = p;
            current = p;
            counter++;
            return;
        }
        while (current->link != NULL)
        {
            current = current->link;
            
        }
        current->link = p;
        counter++;
        
    }
    
    Node *getMostExpensive(){
        Node *current = head;
        Node *mostExpensive = current;
        current = current->link;
        
        while (current != NULL){
            double currentPrice = current->info.getPrice();
            if(currentPrice >= mostExpensive->info.getPrice()){
                mostExpensive = current;
            }
            current = current->link;
        }
        return mostExpensive;
    }
    
    void Sort(){
        Node *lastInOrder;
        Node *firstOutOfOrder;
        Node *current;
        Node *trailCurrent;
        
        lastInOrder = head;
        
        while(lastInOrder->link !=NULL){
            firstOutOfOrder = lastInOrder->link;
            
            if(firstOutOfOrder->info.getItem() < head->info.getItem()){
                lastInOrder->link = firstOutOfOrder->link;
                firstOutOfOrder->link = head;
                head = firstOutOfOrder;
            }
            else{
                trailCurrent = head;
                current = head->link;
            
            while(current->info.getItem() < firstOutOfOrder->info.getItem()){
                trailCurrent = current;
                current = current->link;
            }
            if (current != firstOutOfOrder){
                lastInOrder->link = firstOutOfOrder->link;
                firstOutOfOrder->link = current;
                trailCurrent->link = firstOutOfOrder;
            }
            else{
                lastInOrder = lastInOrder->link;
                }
            }
        }
        
        //print();
    }
    
    void remove(Node *p)
    {
       
        Node *current = head;
        Node *prev = head;
        Sort();
        while(current != NULL){
            if(current== p)
            {
                prev->link = current->link;
                delete p;
                return;
            }
            prev = current;
            current = current->link;
        }
    }
    
    
    void print(){
        Node *test;
        test = head;
        //Sort();
        while (test != NULL)
        {
        cout << test->info.getItem()<< ", " << test->info.getPrice() << endl;
            test = test->link;
        }
        cout << "Number of Items: " << getCounter() << endl;
        cout << "Total cost: " << totalCost() << endl;
    }
};




int main(int argc, char* argv[]){
    
    ArgumentManager am(argc, argv);
    string infilename = am.get("A");
    string outfilename = am.get("C");
    
    Product prod;
    List L;
    double maxCost;


    
    ifstream file;
    file.open(infilename.c_str());
    string fullRow;             //used to extract entire line
    string tmpPrice;            //used to strore string version of the double price
    double readInPrice;
    if (!(file.is_open())){
        cout << "could not find";
    }
    
    file >> maxCost;
    if (maxCost < 0){  //
        
        
    }
    file.ignore(UINT_MAX, '\n');
    
    
    cout << fixed << setprecision(2)<< maxCost << endl;
    
    string name;
    while( getline(file, fullRow)){
        if(fullRow.find(",") == -1)
            continue;
        name = fullRow.substr(0,fullRow.find(","));
        
        
        tmpPrice = fullRow.substr(fullRow.find(",")+1, fullRow.length()-1);
        readInPrice = stod(tmpPrice);
        if(readInPrice < 0)
            continue;
        L.add(name, readInPrice);
    }
    
    L.Sort();
    while (L.totalCost() > maxCost)
    {

        Node *p = L.getMostExpensive();
        L.remove(p);
        L.counter--;
    }
    L.print();
    
    return 0;
}

