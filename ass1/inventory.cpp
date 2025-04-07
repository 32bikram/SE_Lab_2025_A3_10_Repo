#include<iostream>
#include"mysql/mysql.h"
#include"mysql/mysqld_error.h"
#include<bits/stdc++.h>
using namespace std;

#define HOST "127.0.0.1"
#define USER "root"
#define DB "myDB"

int getQuantityById(MYSQL* conn, int productId) {       //getting quantity by id
    string query = "SELECT Quantity FROM PRODUCTS WHERE Id = " + to_string(productId) + ";";
    
    if (mysql_query(conn, query.c_str()) != 0) {
        cerr << "Query Failed: " << mysql_error(conn) << endl;
        return -1;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        cerr << "Error retrieving result: " << mysql_error(conn) << endl;
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int quantity = (row && row[0]) ? stoi(row[0]) : -1; // Convert string to int

    mysql_free_result(res);
    return quantity;
}

// Function to update the quantity (add or subtract)
bool updateQuantity(MYSQL* conn, int productId, int change) {  //func for updating the mysql database
    int currentQuantity = getQuantityById(conn, productId);
    if (currentQuantity == -1) {
        cout << "Product ID " << productId << " not found!" << endl;
        return false;
    }

    int newQuantity = currentQuantity + change;
    if (newQuantity < 0) {
        cout << "insufficient quantity" << endl;
        return false;
    }

    string updateQuery = "UPDATE PRODUCTS SET Quantity = " + to_string(newQuantity) + " WHERE Id = " + to_string(productId) + ";";
    
    if (mysql_query(conn, updateQuery.c_str()) != 0) {
        cerr << "purchase Failed: " << mysql_error(conn) << endl;
        return false;
    }

    cout << "purchase successfull"<< endl;
    return true;
}

void showresult(MYSQL* conn){       //this will print the table 
    string showres = "SELECT Id, Name, Quantity FROM PRODUCTS;";
    if(mysql_query(conn,showres.c_str())==0){
        MYSQL_RES *res= mysql_store_result(conn);
        MYSQL_ROW row;
        if(res==NULL){
            cout<<"failed to fetch";
            return;
        }
        while(row= mysql_fetch_row(res)){
            cout<<"****************"<<endl;
            cout<<"\t Id"<<"\t Name"<<"\t Quantity"<<endl;
            cout<<"\t "<<row[0]<<"\t"<<row[1]<<"\t    "<<row[2]<<endl;
        }
        mysql_free_result(res);
        return;
    }
    else{
        cout<<"QUERY FAILED PLEASE TRY AGIN"<<endl;
        return;
    }
}


void Sellerfun(MYSQL* conn){   //this function will handle all seller related issues
    int c2;
    
    while(true){
        cout<<"1. Show products\n2. update quantity\n3. add product\n4. quit\n:";
        cin>>c2;
        if(c2==1){
            //show product
            showresult(conn);
        }
        else if(c2==2){
            //update quantity
            int id;
            int qty;
            cout<<"enter the id of the product:";cin>>id;
            cout<<"enter updated quantity:";cin>>qty;
            string updt="UPDATE PRODUCTS SET Quantity = "+to_string(qty)+" WHERE Id = "+to_string(id)+";";
            if(mysql_query(conn,updt.c_str())){
                cout<<"error"<<endl;
            }
            else{
                cout<<"update successful"<<endl;
            }  
        }
        else if(c2==3){
            //add product
            int id;
            string name;
            int quantity;

            cout<<"enter id:";cin>>id;
            cout<<"enter name:";cin>>name;
            cout<<"enter quantity:";cin>>quantity;


            string insert1="INSERT INTO PRODUCTS (Id,Name,Quantity) VALUES ("+to_string(id)+",'"+name+"',"+to_string(quantity)+");";

            if(mysql_query(conn,insert1.c_str())){
                cout<<"error:duplicate entry"<<endl;
            }
            else{
                cout<<"inserted success"<<endl;
            }
        }
        else break;
    }


}


void Customerfun(MYSQL* conn){      //this function will handle all customer related issues

    int c2;
    while(true){
    cout<<"1. Show products\n2. purchase\n3. quit\n:";
    cin>>c2;
    if(c2==1){
        //show product
        showresult(conn);
    }
    else if(c2==2){
        //purchase
        int id,qnt;
        cout<<"enter product id:";cin>>id;
        cout<<"enter quantity you want to buy:";cin>>qnt;
        updateQuantity(conn,id,(0-qnt));

    }
    else break;
}
}


int main(){
   string PW;
	// char* PW=new char[100];
    cout<<"instruction ----\nmake sure you have imporeted the  database.sql  \n\ndatabase.sql-->myDB-->PRODUCTS(Id(int,primary_key),Name(varchar),Quantity(int))"<<endl;
    cout<<"enter mysql password:";
    cin>> PW;

    MYSQL* conn;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,HOST,USER,PW.c_str(),DB,3306,NULL,0)){
        cout<<"error: "<<mysql_error(conn)<<endl;
    }
    else{
        cout<<"Logged In Database"<<endl;
    }
    // sleep(3000);





    
    int ch1;
    
    while(true){
        cout<<"you are --\n1.Seller\n2.Customer\n3.quit\n:";
        cin>>ch1;
        if(ch1==1) Sellerfun(conn);
        else if(ch1 == 2) Customerfun(conn);
        else if(ch1==3) break;
    }

    //backup creation
	string command =  string("mysqldump -u root -p")+PW+" myDB > database.sql";
	int status = system(command.c_str());

    if (status == 0) {
        cout << "Database dump created successfully: " << "database.sql" << endl;
    } else {
        cerr << "Failed to create database dump!" << endl;
    }

    system("git add database.sql");
    system("git commit -m \"database is uploaded\"");
    system("git push origin main");


    mysql_close(conn);
    return 0;
}
