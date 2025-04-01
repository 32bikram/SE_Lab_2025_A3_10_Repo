#include<iostream>
#include"mysql/mysql.h"
#include"mysql/mysqld_error.h"
#include<bits/stdc++.h>
using namespace std;
#define HOST "127.0.0.1"
#define USER "root"
#define PW "030203"
#define DB "STUDENTS_MARKS"
int checkfordbconnection(){
    MYSQL* conn;
    conn= mysql_init(NULL);
    conn= mysql_real_connect(conn, HOST, USER, PW, DB,3306, NULL, 0);
    if(conn!=0){
            cout<<"DATABASE CONNECTED"<<endl;
            return 0;
    }
    else{
        cout<<"CONNECTION TO DATABASE FAILED, PLEASE TRY AGIN AFTER SOME TIME"<<endl;
        return 1;
    }
}
int showresult(MYSQL* conn){
    string showres = "SELECT roll_no, name, physics_marks, math_marks, math_marks + physics_marks AS total_marks FROM students;";
    if(mysql_query(conn,showres.c_str())==0){
        MYSQL_RES *res= mysql_store_result(conn);
        MYSQL_ROW row;
        if(res==NULL){
            cout<<"failed to fetch";
            return -1;
        }
        while(row= mysql_fetch_row(res)){
            cout<<"****************************************************************************"<<endl;
            cout<<"\t ROLL"<<"\t NAME"<<"\t PHYSICS"<<"     MATHEMATICS"<<"\tTOTAL MARKS"<<endl;
            cout<<"\t   "<<row[0]<<"\t"<<row[1]<<"\t    "<<row[2]<<"           "<<row[3]<<"                 "<<row[4]<<endl;
        }
        mysql_free_result(res);
        return 0;
    }
    else{
        cout<<"QUERY FAILED PLEASE TRY AGIN"<<endl;
        return 1;
    }
}
void markupdate(MYSQL* conn, int roll, int marks, int i){
    string qry;
    if(i==1){qry= "UPDATE students SET math_marks = "+to_string(marks)+" WHERE roll_no = "+to_string(roll)+";";}
    else{qry= "UPDATE students SET physics_marks = "+to_string(marks)+" WHERE roll_no = "+to_string(roll)+";";}
    if(mysql_query(conn,qry.c_str())==0){
        cout<<"MARKS HAS BEEN INSERTED"<<endl;
    }
    else{
        cout<<"PROBLEM CONNECTING TO DATABASE PLEASE TRY AGAIN"<<endl;
    }
}
int main(){
    MYSQL* conn;
    conn= mysql_init(NULL);
    conn= mysql_real_connect(conn, HOST, USER, PW, DB,3306, NULL, 0);
    if(checkfordbconnection()==1) return 1;
    int input;
    cout<<"1.Enter 1 for student\n2.Enter 2 for teacher \n";
    cin>>input;
    if(input==1){
            //show student their scorecard
            showresult(conn);
            return 0;
    }
    else if(input==2){
        cout<<"Please Enter your Teacher id:";
        string id;
        cin>>id;
        if(id=="M123"){
            //MATH TEACHER
            cout<<"1.View Scorecard \n2.Insert Marks\n";
            int mathteacherinput;
            cin>>mathteacherinput;
            if(mathteacherinput==1){
                //show marks
                showresult(conn);
                return 0;
            }
            else if(mathteacherinput==2){
                //update marks
                int i = 3;
                while(i--){
                    int studentroll;
                    cout<<"Enter Student Roll NO:"<<endl;
                    cin>>studentroll;
                    while(studentroll>3 || studentroll<1) {
                        cout<<"ENTER VALID ROLL NO"<<endl;
                        cin>>studentroll;
                    }
                    cout<<"Enter Marksd Obtained By the Student: \n";
                    int mark;
                    cin>>mark;
                    while(mark>100 || mark<0) {
                        cout<<"ENTER VALID MARK:"<<endl;
                        cin>>mark;
                    }
                    markupdate(conn, studentroll, mark,1);
                }
            }
            else{
                cout<<"Wrong Input";
                return 0;
            }

        }
        else if(id =="P123"){
            //PHYSICS TEACHER   
            cout<<"1.View Scorecard \n2.Insert Marks\n";
            int physicsteacherinput;
            cin>>physicsteacherinput;
            if(physicsteacherinput==1){
                //show the result
                showresult(conn);
                return 0;

            }
            else if(physicsteacherinput==2){
                //update physics marks
                int i = 3;
                while(i--){
                    int studentroll;
                    cout<<"Enter Student Roll NO:"<<endl;
                    while(studentroll>4 && studentroll<1) {
                        cout<<"ENTER VALID ROLL NO:"<<endl;
                        cin>>studentroll;
                    }
                    cin>>studentroll;
                    cout<<"Enter Marksd Obtained By the Student:\n";
                    int mark;
                    cin>>mark;
                    while(mark>100 || mark<0) {
                        cout<<"ENTER VALID MARK:"<<endl;
                        cin>>mark;
                    }
                    markupdate(conn,studentroll, mark,2);
                }
            }
            else{
                cout<<"Wong Input";
                return 0;
            }

        }
        else{
            cout<<"WRONG ID";
            return 0;
        }
    }
    else{
        cout<<"THANK YOU"<<endl;
    }

}