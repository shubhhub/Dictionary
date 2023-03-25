#include <bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
COORD coord = {0, 0};
void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//STRUCTURE OF THE NODE


class node
{
    public:

        string word; //word to be inserted or searched
        string mean; //meaning of word to be inserted or searched
        node* next;  //next pointer
        node* prev;  // previous pointer

};
node* head=NULL;
node* tail=NULL;


//FUNCTION TO WRITE IN THE FILE

void write()
{
    node * temp = head;
    ofstream out("dictionary.txt");
    while(temp!= NULL)
    {
        string s;
        s+=temp->word;
        s.push_back('-');
        s.push_back('>');
        s+=temp->mean;
        s.append("\n");
        out << s;
       temp= temp->next;
    }
}


// UTILITY FUNCTION TO CHECK FOR DUPLICATES IN THE LINKED LIST


bool duplicate(string w,string m)
{
    node* temp=head;
    if(head==NULL){return false;}
    while(temp!=NULL)
    {
        if(w==temp->word && m==temp->mean)
            return true;
        temp=temp->next;
    }
    return false;
}

// FUNCTION TO INSERT IN THE LINKED LIST IN SORTED FASHION


void sortedInsert(string w,string m)
{
    node* newNode =new node;
    newNode->word = w;
    newNode->mean = m;
    newNode->prev = newNode->next = NULL;
    node* temp;
    if (head == NULL)
        head= newNode;

        // CHECKING FOR LARGER WORD AT THE HEAD NODE
    else if (head->word > newNode->word) {
        newNode->next = head;
        newNode->next->prev = newNode;
        head = newNode;
    }
    // CHECKING THE WHOLE LINKED LIST FOR THE LARGER WORD
    else if(head->word < newNode->word) {
        temp = head;
        while (temp->next != NULL &&temp->next->word < newNode->word)
            temp = temp->next;
        newNode->next = temp->next;
        if (temp->next != NULL)
            newNode->next->prev = newNode;
        temp->next = newNode;
        newNode->prev = temp;
    }
}


//FUNCTION TO READ FROM THE FILE AND INSERT THE STRING IN THE LINKED LIST

void read(){
    ifstream file;
    vector<string> e;// for taking both word and meaning from the file
	file.open("dictionary.txt");//opening file
	string line;
	while(getline(file, line)){
		e.push_back(line);//reading from file
    }
    for(int i=0;i<e.size();i++)
    {
        string w,m;
        auto it=find(e[i].begin(),e[i].end(),'-');
        w=e[i].substr(0,it-e[i].begin());
        int pos= e[i].find(">");
        m=e[i].substr(pos+1);
            sortedInsert(w,m);//inserting word and meaning in the list
    }

}


// FUNCTION TO CONVERT TEXT TO SPEECH AND FOR PRONOUNCIATION OF EACH WORD


void textospeech(string w)
{
    string phrase=w;
    string command="espeak \""+phrase+"\"";
    const char* charCommand=command.c_str();
    system(charCommand);
}

//FUNCTION TO DELETE FROM THE LIST


 void Delete()
 {
     system("cls");
     string d;
     bool flag=0;
     cout<<"Enter the word you want to delete ";
     cin>>d;
     node* temp=head;
     if(head==NULL)
     {
         cout<<"Dictionary is empty";
         return;
     }
     while(temp!=NULL)
     {
         if(temp->word==d)
         {
             flag=1;
             if (temp->next != NULL)
                temp->next->prev=temp->prev;
             if (temp->prev != NULL)
                temp->prev->next=temp->next;
             break;
         }
         temp=temp->next;
     }
     delete(temp);//DELETE WORD
     if(flag==0){
     cout<<"Word not found\n";
    }
    else
    {
        cout<<d<<" has been deleted successfully"<<endl;
        textospeech(d);
        textospeech("has been deleted successfully");
            write();// WRITING THE NEW LIST AGAIN
    }
    cout<<"press any key";
     getch();
 }


//FOR SEARCHING SUBSTRINGS OF A WORD


void search_string(string y)
{
    int flag=0,flag1=0;
    int l=y.length();
    for(l;l>0;l--)
    {
        y=y.substr(0,l);
        node *temp=head;
    while(temp!=NULL)
    {
        if(temp->word.length()>=l){
        string str=temp->word.substr(0,l);
        if(str==y)
        {
            flag1=1;
            cout<<temp->word<<"->"<<temp->mean<<endl;
            textospeech(temp->word);//for pronounciation
            flag=1;
        }
        }
        temp=temp->next;
    }
    if(flag1==1)
        break;
    }
    if(flag==0)
    cout<<"Similar word not exists";
}


//FUNCTION TO SEARCH FOR A WORD


void search()
{
    system("cls");
    system("color C7");
    string word2;
    cout<<"Enter The Word You Want To Search"<<endl;
    cin>>word2;
    int flag=0;
    node*temp=head;
    while(temp!=NULL)
    {
        if(temp->word==word2)
        {
            cout<<temp->word<<"->"<<temp->mean<<endl;
            textospeech(temp->word);
            flag=1;
        }
         temp=temp->next;
    }
    //FOR SUGGESTION OF INCORRECT INPUT WORD
    if(flag==0){
        cout<<"\nDo you mean\n";
        textospeech("do you mean");
        search_string(word2);
    }
     cout<<"press any key ";
    getch();
}



///////////////ADDING WORD TO LINK LIST AT LAST/////////////////////////
void add_to_dictionary()
{
    system("cls");
    system("color 87");
    string word1;
    string mean1;
    cout<<"ALERT! Use '/_'/ For Spaces"<<endl;
    cout<<"Enter Your Word"<<endl;
    cin>>word1;
    cout<<"Enter The Meaning Of Your Word"<<endl;
    cin.ignore();
    getline(cin,mean1);
    if(duplicate(word1,mean1))
    {
        cout<<"ALREADY EXISTS";
        return;
    }
    sortedInsert(word1,mean1);
    write();
     cout<<"press any key ";
    getch();
}

//FOR DISPLAY CONTENT FROM FILE


void display()
{
    system("cls");
    system("color 02");
    if(head==NULL)
    {
        cout<<"ERROR IN INSERTION";
        return;
    }
    node* temp=head;
    while(temp!=NULL)
    {

        cout<<temp->word<<"->"<<temp->mean<<endl;
        temp=temp->next;
    }
    cout<<"press any key ";
    getch();
}

//DRIVER CODE
int main()
{
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////WELCOME AGE/////////////////////////
    ///////////////////////////////////////////////////////////////////


    system("cls");
    system("color A0");
    for(int j=0;j<4;j++)
    {
    system("cls");
    gotoxy(j,6); cout<<"        ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ";
    gotoxy(j,7); cout<<"            ÜÜÜÜÜ   ÜÜÜÜÜ  ÜÜÜÜÜ ÜÜÜÜÜÜÜ ÜÜÜÜÜÜÜ" ;
    gotoxy(j,8); cout<<"            Û    Û    Û   Û         Û       Û   " ;
    gotoxy(j,9); cout<<"            Û    Û    Û   Û         Û       Û   " ;
    gotoxy(j,10);cout<<"            Û    Û    Û   Û         Û       Û   ";
    gotoxy(j,11);cout<<"            ÛÛÛÛÛ   ÜÜÛÜÜ  ÛÜÜÛÛ    Û    ÜÜÜÛÜÜÜ";
    gotoxy(j,12); cout<<"        ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ";

    gotoxy(53-j,6);cout<<"ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ ";
    gotoxy(53-j,7);cout<<"   ÜÜÜÜ  Ü    Ü     Ü     ÜÜÜÜÜ  Ü     Ü ";
    gotoxy(53-j,8);cout<<"  Û    Û ÛÛ   Û    Û Û    Û   Û   Û   Û   ";
    gotoxy(53-j,9);cout<<"  Û    Û Û Û  Û   ÛÜÜÜÛ   ÛÜÜÜÛ    ÛÜÛ    ";
    gotoxy(53-j,10);cout<<"  Û    Û Û  Û Û  Û     Û  Û  Û      Û     ";
    gotoxy(53-j,11);cout<<"   ÛÛÛÛ  Û   ÛÛ Û       Û Û   Û     Û     ";
    gotoxy(53-j,12);cout<<"ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ ";

    }
    gotoxy(25,25);
    textospeech("WELCOME TO DICTIONARY");
    cout<<"press any key to continue...";
    getch();


    int ch;

    read();
    while(1)
    {
        system("cls");
        system("color 57");

        //TEXT FORMATTING


        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = 0;
        cfi.dwFontSize.Y = 28;
        wcscpy(cfi.FaceName, L"Bahnschrift");
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
        cout<< "\n\t\tDictionary"<<endl ;
        cout<<"\n\t\t 1.Add A Word At Last." <<endl;
        cout<<"\t\t 2.Search A Word."<<endl ;
        cout<<"\t\t 3.Show Dictionary."<<endl ;
        cout<<"\t\t 4.Delete."<<endl ;
        cout<<"\t\t 0.Exit."<<endl;
        cout<< "\n\n\t\t Your Choice From 1 2 3 4 0"<<endl;
       cin>>ch;
       switch(ch)
       {
        case 1:
           add_to_dictionary();// TO ADD WORDS
           break;
       case 2 :
            search();// TO SEARCH A WORD
           break;
       case 3 :
            display();// TO DISPLAY THE LIST
           break;
        case 4 :
           Delete();// TO DELETE THE WORD
           break;
        case 0:
            {
                break;
            }

       default:
        cout<<"Wrong CHOICE Buddy\n"<<endl;
        break;
        }

        ///////// ON EXIT//////////

        if(ch == 0)
        {
            system("cls");
            cout<<"Thanks For Using Dictionary!"<<endl;
            textospeech("Thanks for using dictionary");
            mciSendString("open \"claps1.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
            mciSendString("play mp3", NULL, 0, NULL);
            textospeech("This page has been created by");
            cout<<"\nMuskan";
            textospeech("Muuskaan");
            cout<<"\nAditi";
            textospeech("aditi");
            cout<<"\nShubh";
            textospeech("Shuubh");
            cout<<"\nManika";
            textospeech("manika");


            break;
        }
    }
/////////////////////////////////MENU END//////////////////////

    return 0;
}


