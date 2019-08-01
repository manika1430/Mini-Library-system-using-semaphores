#include <iostream>
#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include<windows.h>
#include<sys/types.h>
#include <stdlib.h>
#include <semaphore.h>
using namespace std;

//void wait(int &x)
//{
//    while(x<0);
//    x--;
//}
//
//void signal(int &x)
//{
//    x++;
//}

sem_t en,ex,book_space,op,xp;
int temp1;
int s;
bool book[5]={false,false,false,false,false};
int book_number[10];
int index;
int temp_book;
int main()
{
    sem_init(&ex,0,1);
    sem_init(&en,0,1);
    sem_init(&op,0,1);
    sem_init(&xp,0,1);
    sem_init(&book_space,0,5);

    int input=1,i,flag;
    int temp;
int choice;
    cout<<"\n\n\n\n\n________________________________________________________________________________\n\n\n\n\t\t\t\tMINI LIBRARY SYSTEM";
    cout<<"\n\n\n\n\n________________________________________________________________________________\n\n\n";
    Sleep(2000);
    z:
    while(input)
    {
        system("cls");
        cout<<"\n\n\n________________________________________________________________________________\n\n";
        cout<<"\n\t\t\t\t1. Issue a book\n\n\t\t\t\t2. Return a book\n\n\t\t\t\t3. Exit Program\n\n";
        cout<<"\n\n________________________________________________________________________________\n\n";
        cout<<"Enter option- ";
        cin>>input;
        switch(input)
        {

            case 1: sem_wait(&en);
                    int val3,val4;
                    sem_getvalue(&xp,&val4);
                    if(val4==0)
                    {
                        cout<<"Complete process RETURN first."<<endl;
                        sem_post(&en);
                        goto r;
                    }
                   sem_getvalue(&op,&val3);
                   if(val3==0)
                   {
                       cout<<"complete the previous process first"<<endl;
                       sem_post(&en);
                       goto f;

                   }

                    cout<<"You are in Issue process"<<endl;
                    cout<<"To choose other process :press 5    else enter any other number."<<endl;
                    cin>>choice;
                    if(choice==5)
                        {
                         sem_wait(&op);
                         sem_post(&en);
                         goto z;
                         }
                  else
                    {
                    sem_post(&en);
                 f:
                    sem_wait(&en);
                    s=0;
                    if(book_space!=0)
                    {
                        cout<<"Enter the book id of the book to be issued : ";

                    for(int i=0;i<5;i++)
                        {
                            if(book[i]==false)
                            {
                                book[i]=true;
                                cin>>book_number[i];
                                 temp1=book_number[i];
                                index=i;
                                break;
                            }
                        }
                    for(int j=0;j<5&&j!=index;j++)
                                {
                                    if(book_number[j]==temp1)
                                        {cout<<"This book has already been issued . ";
                                //        wait(d);
                                         s=1;
                                        book[index]=false;
                                        Sleep(4000);
                                        break;
                                        }

                                }
                        if(s!=1)
                        {sem_wait(&book_space);
                        int val2;
                   sem_getvalue(&book_space,&val2);
                        cout<<"Book with id : "<<temp1<<" is issued now."<<endl<<endl<<val2<<" books left in the library ";
                        Sleep(4000);
                        }
                    }
                    //full
                    else
                    {
                        cout<<"There are no more books available. Please try again later.";
                        Sleep(4000);
                    }
                    sem_post(&en);
              //      sem_post(d);
              sem_post(&op);
                    break;}
            case 2:

                    sem_wait(&ex);
                    int val2,val5;
                   sem_getvalue(&op,&val2);
                   if(val2==0)
                   {
                       cout<<"Complete process 1 first."<<endl;
                    sem_post(&ex);
                    goto f;
                   }
                   sem_getvalue(&xp,&val5);
                    if(val5==0)
                    {
                        cout<<"Complete process previous process first."<<endl;
                        sem_post(&ex);
                        goto r;
                    }
                   cout<<"You are in Return process"<<endl;
                   cout<<"To choose other process, enter 5 else enter any other number."<<endl;
                    cin>>choice;
                   if(choice ==5)
                   {
                         sem_wait(&xp);
                         sem_post(&ex);
                         goto z;
                   }

                   else{
                    sem_post(&ex);
             r:
                    sem_wait(&ex);
                    int val;
                   sem_getvalue(&book_space,&val);
                    if(val==5)
                    {
                        cout<<"No books issued yet.";
                        Sleep(4000);
                    }
                    else
                    {
                        while(1)
                        {
                            cout<<"Enter the book id you want to return :";
                            flag=0;
                            cin>>temp;
                            for(i=0;i<5;i++)
                            {
                                if(book[i]==true)
                                {
                                    if(temp==book_number[i])
                                    {
                                        book[i]=false;
                                        flag=1;
                                        break;
                                    }
                                }
                            }
                            if(flag==1)
                                break;
                            cout<<"No such book has been issued from the library. Please re check the book id !!"<<endl;
                            sem_post(&en);
                            Sleep(4000);
                            goto z;
                        }
                            sem_post(&book_space);
                            int val1;
                   sem_getvalue(&book_space,&val1);
                            cout<<"Book with book id : "<<temp<<" is available now and can be issued"<<endl<<endl<<val1<<" book spaces are empty.";
                            Sleep(4000);
                    }
                    sem_post(&ex);
                    sem_post(&xp);
                    break;}
                    //-----------------------------------------------------------------------------------------------------------------------------
            case 3: input=0;
                    break;
            default:
                    cout<<"Invalid input!! ";
                    Sleep(1000);
                    break;


                    }
        }

    return 0;
}

