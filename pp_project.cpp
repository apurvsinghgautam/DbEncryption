    //AllSafe Database Management System//
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<conio.h>
#include<process.h>
#include<windows.h>
using namespace std;
ostream &nm(ostream &strname)
{
	strname<<" * WELCOME TO ALLSAFE EMPLOYEE DATABASE MANAGEMENT SYSTEM * ";
	return strname;
}
fstream f;
fstream file;
int count=0;
class allsafe
{
	int empid;
	int age;
	string passwd;
	char name[20];
	double mob_no;
	float salary;
	char sector[50];
	int yr_of_wrk;
	char gender[10];
	char desig[50];
	public:
		void choice();
		void login();
		void read();
		void write();
		void modify();
		void modifydata();
		void getdata();
		void search();
		void deleted();	
		void display();		
		void displaydata();	
		void displayall();
		void encrypt();
		void decrypt();
		void gotoxy(short,short);
		int getempid()
		{
			return empid;
		}
		void end();
}c,temp[100],temp1[100];
void allsafe::gotoxy(short x,short y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void allsafe::display()
{
	system("cls");
	Sleep(1500);	
	gotoxy(42,12);	
	system("COLOR B4");
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(45,14);
	Sleep(1500);
	cout<<nm;
	gotoxy(42,16);
	Sleep(1500);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	Sleep(1500);
}
void allsafe::read()
{
	f.open("input.dat",ios::app | ios::out | ios::binary | ios::in);
    char ans='y';
	while(ans=='y')
	{
		c.getdata();
		count++;
	 	f.write((char*)&c,sizeof(c));
	 	gotoxy(45,35);
	 	cout<<" Do you want to add more records? (y/n) : ";
	 	cin>>ans;
	}
	f.close();	
}
void allsafe::write()
{
	system("cls");
	f.open("input.dat",ios::in);
    system("COLOR 2");
	gotoxy(56,5);
	cout<<"$ ALLSAFE CYBERSPACE $ ";
	gotoxy(58,7);
	cout<<" * EMPLOYEE DETAILS * ";
	gotoxy(30,8);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";    
    gotoxy(37,9);
	cout<<"Employee ID";
	gotoxy(56,9);
	cout<<"Name";
	gotoxy(71,9);
	cout<<"Gender";
	gotoxy(81,9);
	cout<<"Sector";
	gotoxy(94,9);
	cout<<"Designation";
	gotoxy(30,10);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;     	
	while(f.read((char*)&c,sizeof(c)))
	{
		if(f.eof())
		break;
		c.displaydata();
	}
	f.close();
	getch();
}	
void allsafe::modify()
{
	system("cls");
	int id,pos;
	char found='f';
	f.open("input.dat",ios::out | ios::binary | ios::in);
	system("COLOR C1");
	gotoxy(56,5);
	cout<<"* $ ALLSAFE CYBERSPACE $";
	gotoxy(59,8);
	cout<<"* MODIFICATION *";
	gotoxy(31,10);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(42,15);	
   	cout<<"Enter the Employee ID whose data is to be modified :";
   	gotoxy(95,15);
   	cin>>id;
   	while(!f.eof())
	{
		pos=f.tellg();
		f.read((char*)&c,sizeof(c));
		if(c.getempid()==id)
		{
			c.modifydata();
			f.seekg(pos);
			f.write((char*)&c,sizeof(c));
			found='t';
			gotoxy(45,33);
			cout<<"YOUR DATA HAS BEEN SUCCESFULLY MODIFIED"<<endl;
			break;
		}	
	}
	if(found=='f')
	{
		gotoxy(55,20);
		cout<<" Invalid Employee ID ";
	}
	f.close();
	getch();
}
void allsafe::search()
{
	system("cls");
	int id;
	char found='f';
	system("COLOR C1");
	gotoxy(56,5);
	cout<<"* $ ALLSAFE CYBERSPACE $";
	gotoxy(64,8);
	cout<<"* SEARCH *";
	gotoxy(31,10);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(42,15);	
   	cout<<" Enter the Employee ID whose data is to be searched : ";
   	f.open("input.dat",ios::out | ios::binary | ios::in);
	gotoxy(95,15);    	
   	cin>>id;  	
   	while(!f.eof())
	{
		f.read((char*)&c,sizeof(c));
		if(c.getempid()==id)
		{
			displayall();
			found='t';
			break;
		}	
	}
	if(found=='f')
	{
		gotoxy(55,20);
		cout<<" Invalid Employee ID ";
	}
	f.close();
	getch();
}
void allsafe::deleted()
{
	system("cls");
	int id;
	char found='f',confirm='n';
	f.open("input.dat",ios::in);
	file.open("temp.dat",ios::out);
	gotoxy(40,12);
	system("COLOR C1");
	gotoxy(56,5);
	cout<<"* $ ALLSAFE CYBERSPACE $";
	gotoxy(64,8);
	cout<<"* DELETE *";
	gotoxy(31,10);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(42,15);	
   	cout<<" Enter the Employee ID whose data is to be deleted : ";
   	gotoxy(95,15);
   	cin>>id;
   	while(f.read((char*)&c,sizeof(c)))
	{
		if(c.getempid()==id)
		{
			gotoxy(37,19);
			cout<<"Employee ID";
			gotoxy(56,19);
			cout<<"Name";
			gotoxy(71,19);
			cout<<"Gender";
			gotoxy(81,19);
			cout<<"Sector";
			gotoxy(94,19);
			cout<<"Designation"<<endl;
			displaydata();
			found='t';
			gotoxy(48,25);
			cout<<" Are you sure you want to delete this record (y/n) : ";
			cin>>confirm;
			if(confirm=='n')
				file.write((char*)&c,sizeof(c));
			else
			{
				gotoxy(45,33);
				cout<<"YOUR DATA HAS BEEN SUCCESFULLY DELETED"<<endl;
			}
		}
		else
		{
			file.write((char*)&c,sizeof(c));
		}
	}
	if(found=='f')
	{
		gotoxy(55,20);
		cout<<" Invalid Employee ID ";
		getch();
	}
	f.close();
	file.close();
	remove("input.dat");
	rename("temp.dat","input.dat");
	getch();
}
void allsafe::modifydata()
{
	system("cls");
	system("COLOR E7");
	gotoxy(57,5);
	cout<<" $ ALLSAFE CYBERSPACE $ ";
	gotoxy(55,8);
	cout<<"* EMPLOYEE DETAILS * ";
	gotoxy(30,10);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(40,14);
	cout<<"Employee ID : ";
	gotoxy(40,16);
	cout<<"Name : ";
	gotoxy(40,18);
	cout<<"Age : ";
	gotoxy(40,20);
	cout<<"Gender : ";
	gotoxy(40,22);
	cout<<"Mobile No. : ";
	gotoxy(40,24);
	cout<<"Salary (p.a) : ";
	gotoxy(40,26);
	cout<<"Year of Working : ";
	gotoxy(40,28);
	cout<<"Sector : ";
	gotoxy(40,30);
	cout<<"Designation : ";
	gotoxy(60,14);
	cin>>empid;
	gotoxy(60,16);
	cin>>name;
	gotoxy(60,18);	
	cin>>age;	
	gotoxy(60,20);
	cin>>gender;
	gotoxy(60,22);
	cin>>mob_no;
	gotoxy(60,24);
	cin>>salary;
	gotoxy(60,26);
	cin>>yr_of_wrk;
	gotoxy(60,28);
	cin>>sector;
	gotoxy(60,30);
	cin>>desig;			
}
void allsafe::getdata()
{
	system("cls");
	system("COLOR C0");
	gotoxy(57,5);
	cout<<"$ ALLSAFE CYBERSPACE $ ";
	gotoxy(56,8);
	cout<<"* EMPLOYEE DETAILS * ";
	gotoxy(30,10);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(55,15);	
	cout<<" Employee ID : ";
	gotoxy(70,15);
	cin>>empid;
	int var=empid;
	int flag=0;	
	while(f.read((char*)&c,sizeof(c)))
	{
		if(f.eof())
			break;
		if(var==empid)
			flag=1;
	}
	f.close();
	f.open("input.dat",ios::app | ios::out | ios::binary | ios::in);
	if(flag==0)
	{
		system("cls");
		system("COLOR E7");
		gotoxy(57,5);
		cout<<"$ ALLSAFE CYBERSPACE $ ";
		gotoxy(56,8);
		cout<<"* EMPLOYEE DETAILS * ";
		gotoxy(30,10);
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		gotoxy(40,14);
		cout<<"Employee ID : ";
		gotoxy(40,16);
		cout<<"Name : ";
		gotoxy(40,18);
		cout<<"Age : ";
		gotoxy(40,20);
		cout<<"Gender : ";
		gotoxy(40,22);
		cout<<"Mobile No. : ";
		gotoxy(40,24);
		cout<<"Salary (p.a) : ";
		gotoxy(40,26);
		cout<<"Year of Working : ";
		gotoxy(40,28);
		cout<<"Sector : ";
		gotoxy(40,30);
		cout<<"Designation : ";
		gotoxy(30,32);
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		gotoxy(60,14);
		cin>>empid;
		gotoxy(60,16);
		cin>>name;
		gotoxy(60,18);	
		cin>>age;	
		gotoxy(60,20);
		cin>>gender;
		gotoxy(60,22);
		cin>>mob_no;
		gotoxy(60,24);
		cin>>salary;
		gotoxy(60,26);
		cin>>yr_of_wrk;
		gotoxy(60,28);
		cin>>sector;
		gotoxy(60,30);
		cin>>desig;	
		gotoxy(45,33);
		cout<<"YOUR DATA HAS BEEN SUCCESFULLY CREATED"<<endl;
    }
    else
    {
    	gotoxy(57,5);
		cout<<" $ ALLSAFE CYBERSPACE $ ";
		gotoxy(30,10);
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";	
    	gotoxy(53,18);
    	cout<<" Record Already Exists ";
    	getch();
    }
}
void allsafe::displaydata()
{
	cout<<"\t\t\t\t\t"<<empid<<"\t\t"<<name<<"\t\t"<<gender<<"\t"<<sector<<"\t"<<desig<<endl;
}
void allsafe::displayall()
{
	system("cls");
	system("COLOR C1");
	gotoxy(57,7);
	cout<<"* Employee Details *";	
	gotoxy(31,8);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(45,10);
	cout<<"Searching...";
	Sleep(1000);	
	gotoxy(45,10);
	cout<<"Searched!!!!";
	gotoxy(52,12);
	cout<<"Employee ID : "<<empid;
	gotoxy(52,14);
	cout<<"Name : "<<name;
	gotoxy(52,16);
	cout<<"Gender : "<<gender;
	gotoxy(52,18);
	cout<<"Mobile No. : "<<mob_no;
	gotoxy(52,20);
	cout<<"Salary (lpa) : "<<salary;
	gotoxy(52,22);
	cout<<"Year of Working : "<<yr_of_wrk;
	gotoxy(52,24);
	cout<<"Sector : "<<sector;
	gotoxy(52,26);
	cout<<"Designation : "<<desig;
	gotoxy(31,28);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";	
}
void allsafe::encrypt()
{
	system("cls");
	char fname[20],ch;
	gotoxy(57,5);
	cout<<"$ ALLSAFE CYBERSPACE $";
	gotoxy(59,7);
	cout<<"* ENCRYPTION *";
	gotoxy(31,8);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(48,12);	
	cout<<" Enter file name (with extension) to encrypt : ";
	gotoxy(96,12);
	cin>>fname;
	f.open(fname);
	file.open("temp.dat",ios::out);
	while(f.eof()==0)
	{
		f>>ch;
		ch=ch+122;
		file<<ch;			
	}
	f.close();
	file.close();
	f.open(fname);
	file.open("temp.dat");
	while(file.eof()==0)
	{
		file>>ch;
		f<<ch;
	}
	gotoxy(49,18);
	cout<<"File "<<fname<<" encrypted successfully..!!";
	f.close();
	file.close();
	getch();
}
void allsafe::decrypt()
{
	system("cls");
	char fname[20],ch;
	gotoxy(57,5);
	cout<<"$ ALLSAFE CYBERSPACE $";
	gotoxy(59,7);
	cout<<"* DECRYPTION *";
	gotoxy(31,8);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(48,12);		
	cout<<" Enter file name (with extension) to decrypt : ";
	gotoxy(96,12);
	cin>>fname;
	f.open(fname);
	file.open("temp.dat");
	while(file.eof()==0)
	{
		file>>ch;
		ch=ch-122;
		f<<ch;
	}
	gotoxy(49,18);
	cout<<"File "<<fname<<" decrypted successfully..!!";
	f.close();
	file.close();
	getch();	
}
void allsafe::login()
{
	system("cls");
	int in;
	char ch;
	string lid;
	passwd="";
	system("COLOR F8");
	gotoxy(56,5);
	cout<<"$ ALLSAFE CYBERSPACE $";
	gotoxy(31,7);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";		
	gotoxy(53,10);
	cout<<"Welcome to Login Screen";
	gotoxy(55,13);
	cout<<"Login ID : ";
	gotoxy(55,15);
	cout<<"Password : ";
	gotoxy(65,13);
	getline(cin,lid);
	gotoxy(65,15);
	ch = _getch();
   	while(ch != 13)
	{
      passwd.push_back(ch);
      cout << '*';
      ch = _getch();
	}
}
void allsafe::choice()
{
	int z;
	if(passwd.compare("allsafe")!=0 && passwd.compare("coldfire")!=0)
	{
		gotoxy(55,18);
		cout<<"Wrong Login Credentials! :P";
		gotoxy(55,20);
		cout<<"Press Enter To Retry";
		getch();
		login();
		choice();
	}
	else
	{
		system("cls");
		if(passwd.compare("allsafe")==0)
		{
			gotoxy(55,2);
			cout<<"Welcome Apurv Singh Gautam ! ";
			getch();
		}
		else if(passwd.compare("coldfire")==0)
		{
			gotoxy(56,2);
			cout<<"Welcome Rushin Tilva ! ";
			getch();		 
		}
		while(2)
		{
			system("cls");
			system("COLOR A9");
			gotoxy(57,5);
			cout<<" $ ALLSAFE CYBERSPACE $ ";
			gotoxy(55,8);
			cout<<"$$ EMPLOYEE MANAGMENT $$";
			gotoxy(30,10);
			cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			gotoxy(55,12);
			cout<<" 1. NEW CUSTOMER ";
			gotoxy(55,14);
			cout<<" 2. MODIFY A RECORD ";
			gotoxy(55,16);
			cout<<" 3. SEARCH A RECORD ";
			gotoxy(55,18);
			cout<<" 4. DELETE A RECORD ";
			gotoxy(55,20);
			cout<<" 5. DISPLAY ALL RECORDS ";
			gotoxy(55,22);
			cout<<" 6. ENCRYPT FILE ";
			gotoxy(55,24);
			cout<<" 7. DECRYPT FILE ";
			gotoxy(55,26);
			cout<<" 0. Exit";
			gotoxy(30,28);
			cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";						
			gotoxy(50,32);
			cout<<"ENTER CHOICE : ";
			cin>>z;		
			switch(z)
			{
				case 1: c.read();
				  		break;
	   			case 2: c.modify();
						break;
				case 3: c.search();
						break;
				case 4: c.deleted();
						break;	
				case 5: c.write();
						break;		
				case 6: c.encrypt();
						break;
				case 7: c.decrypt();
						break;					
				case 0: c.end();				
   			}
		}
	}
	getch();
}
void allsafe::end()
{
 system("cls");
 system("COLOR 84");
 gotoxy(60,15);
 cout<<"-- THANK YOU --";
 getch();
 exit(0);
}
int main()
{
	c.display(); 
	c.login();
	c.choice();
}
