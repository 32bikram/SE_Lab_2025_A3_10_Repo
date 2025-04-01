#include<iostream>
#include<vector>
#include<cstdlib>
#include <unistd.h>
#include<fstream>
using namespace std;

class Todo{
    int Id;
    static int id;
    string taskname;
    string taskstatus;
    public:
    Todo(string task="", string status="Pending"){
        taskname= task;
        taskstatus= status;
        Id = id++;
    }
    int getid(){
        return id;
    }
    int getId(){
        return Id;
    }
    string gettaskname(){
        return taskname;
    }
    string gettaskstatus(){
        return taskstatus;
    }
    void settaskname(string str){
        taskname= str;
    }
    void settaskstatus(string str){
        taskstatus = str;
    }
};
int Todo:: id = 1;
int main(){
    cout<<"***********TASK MANAGEMENT CLI TOOL**************"<<endl<<endl;
    vector<Todo> taskarr;
    
       
        while(1){
            if(taskarr.size()==0) cout<<"NO PENDING TASK"<<endl<<endl;
            else{
                cout<<"\nHERE IS YOUR PENDING TASKS\n"<<endl;
                for(auto it = taskarr.begin(); it!= taskarr.end(); it++){
                    cout<<it->getId()<<" | "<<it->gettaskname()<<" | "<<it->gettaskstatus()<<endl;
                }
                cout<<"______________________________________________________________________"<<endl;
                usleep(2000000);
            }


        cout<<"\nEnter The Operation To Be Performed"<<endl;
        cout<<"1.Enter [a] to add new Task\n"<<"2.Enter [c] to mark a task complete\n"<<"3.Enter [e] to edit a task\n"<<"4.Enter [q] to quit the program"<<endl;
        cout<<"PLEASE PROVIDE YOUR INPUT:";
        char input;
        cin>>input;
        while(input!='a' && input!='c' && input!='e' && input!='q') {
            system("clear");
            cout<<"________________PLEASE ENTER VALID INPUT_______________"<<endl<<endl;
            cout<<"1.Enter [a] to add new Task\n"<<"2.Enter [c] to mark a task complete\n"<<"3.Enter [e] to edit a task\n"<<"4.Enter [q] to quit the program"<<endl;
            cout<<"PLEASE PROVIDE A VALID INPUT:";
            cin>>input;
        }
        if(input=='a'){
            cout<<"\nPlease Specify The Task:";
            string task;
            cin.clear();
            cin.ignore();
            getline(cin, task);
            Todo newTask;
            newTask.settaskname(task);
            taskarr.push_back(newTask);
        }
        else if(input=='c'){
            cout<<"Enter the Id of completed Task: ";
            int temp;
            cin>>temp;
            while(temp>taskarr.size()){
                system("clear");
                cout<<"No Task Exist With This Id, Please give valid input:";
                cin>>temp;
               }
            for(auto it = taskarr.begin(); it != taskarr.end(); it++){
                if(it->getId()==temp) it->settaskstatus("Completed");
            }
        }
        else if(input=='e'){
            cout<<"Enter the Id of the Task you wanna edit: ";
            int temp;
            cin>>temp;
            while(temp>taskarr[0].getid()){
                system("clear");
                 cout<<"No Task Exist With This Id, Please give valid input:";
                 cin>>temp;
                }
            string str;
            cout<<"Enter new Task Details: ";
            cin.clear();
            cin.ignore();
            getline(cin, str);
            for(auto it = taskarr.begin(); it != taskarr.end(); it++){
               
                if(it->getId()==temp) {
                    it->settaskname(str);
                }
            }
        }
        else if(input=='q'){
            cout<<"Thank You For Using Task Management Tool, Have A Nice Day"<<endl<<endl;
            
            ofstream outfile("tasklist.txt");
            if(outfile.is_open()){
                outfile << "TaskID | TaskName | TaskStatus" << endl;
                for(auto it = taskarr.begin(); it != taskarr.end(); it++){
                    outfile << it->getId() << " | "
                            << it->gettaskname() << " | "
                            << it->gettaskstatus() << endl;
                }
                outfile.close();
            }

            // Push only the task list file to GitHub
 
            system("git add tasklist.txt");
            system("git commit -m \"Task List Has Been Updated\"");
            system("git push origin main");
            break;
        }
    }
    return 0;
}
