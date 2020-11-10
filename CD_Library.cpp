#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
class book
{
	char bno[50];
	char bname[50];
	char aname[50];
  public:
	void create_book()
	{
		cout<<"NEW BOOK ENTRY";
		cout<<"Enter The book no.";
		cin>>bno;
		cout<<"Enter The Name of The Book ";
		gets(bname);
		cout<<"Enter The Author's Name ";
		gets(aname);
	}
       
       void show_book()
	{
		cout<<"Book no:"<<bno;
		cout<<"Book Name:";
		puts(bname);
		cout<<"Author Name:";
		puts(aname);
	}

	void modify_book()
	{
		cout<<"Book no:"<<bno;
		cout<<"Modify Book Name:";
		gets(bname);
		cout<<"Modify Author's Name of Book:";
		gets(aname);
	}

	char* retbno()
	{
		return bno;
	}

	void report()
	{cout<<bno<<endl<<bname<<endl<<aname<<endl;}


};         




class member
{
	char admno[50];
	char name[50];
	char stbno[50];
	int token;
public:
	void create_member()
	{
		clrscr();
	 	cout<<"NEW MEMBER ENTRY";
		cout<<"Enter The admission no.";
		cin>>admno;
		cout<<"Enter The Name of The Student";
		gets(name);
		token=0;
		stbno[0]='/0';
		cout<<"Student Record Created";
	}

	void show_member()
	{
		cout<<"Admission no.: "<<admno;
		cout<<"Member Name:";
		puts(name);
		cout<<"No of Book issued:"<<token;
		if(token==1)
			cout<<"Book No"<<stbno;
	}

	void modify_member()
	{
		cout<<”Admission no.:"<<admno;
		cout<<"Modify Member Name:";
		gets(name);
	}

	char* retadmno()
	{
		return admno;
	}

	char* retstbno()
	{
		return stbno;
	}
       int rettoken()
	{
		return token;
	}
       void addtoken()
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}

	void report()
	{cout<<endl<<admno<<endl<<name<<endl<<token<<endl;}

};      
fstream fp,fp1;
book bk;
member st;

void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		clrscr();
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"Do you want to add more records(y/n?)";
		cin>>ch;
	}while(ch=='y');
	fp.close();
}

void write_member()
{
	char ch;
	fp.open("member.dat",ios::out|ios::app);
	do
	{
		st.create_member();
		fp.write((char*)&st,sizeof(member));
		cout<<"do you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y');
	fp.close();
}

void display_spb(char n[])
{
	cout<<"BOOK DETAILS";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
		 	flag=1;
		}
	}
	
	fp.close();
	if(flag==0)
		cout<<"Book does not exist";
	getch();
}

void display_sps(char n[])
{
	cout<<"MEMBER DETAILS";
	int flag=0;
	fp.open("member.dat",ios::in);
	while(fp.read((char*)&st,sizeof(member)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_member();
			flag=1;
		}
	}
	
	fp.close();
	if(flag==0)
    		cout<<"Member does not exist";
 	getch();
       
}

void modify_book()
{
	char n[50];
	int found=0;
	clrscr();
	cout<<"MODIFY BOOK REOCORD";
	cout<<"Enter The book no. of The book";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book))&&found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
		cout<<"Enter The New Details of book"<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
		    	fp.seekp(pos,ios::cur);
		    	fp.write((char*)&bk,sizeof(book));
		    	cout<<"Record Updated";
		    	found=1;
		}
	}

    	fp.close();
    	if(found==0)
    		cout<<"Record Not Found";
    	getch();
}


void modify_member()
{
	char n[50];
	int found=0;
	clrscr();
	cout<<"MODIFY MEMBER RECORD";
	cout<<"Enter The admission no. of the member";
	cin>>n;
	fp.open("member.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(member))&&found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_member();
		cout<<"Enter The New Details of member"<<endl;
			st.modify_member();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(member));
			cout<<"Record Updated";
			found=1;
		}
	}
	
	fp.close();
	if(found==0)
		cout<<"Record Not Found";
	getch();
}
void delete_member()
{
	char n[50];
	int flag=0;	
	clrscr();
    	cout<<"DELETE MEMBER";
    	cout<<"Enter The admission no. of the member You Want To      Delete";
    	cin>>n;
    	fp.open("member.dat",ios::in|ios::out);
    	fstream fp2;
    	fp2.open("Temp.dat",ios::out);
    	fp.seekg(0,ios::beg);
    	while(fp.read((char*)&st,sizeof(member)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
	     		fp2.write((char*)&st,sizeof(member));
		else
	   		flag=1;
	}
    	
	fp2.close();
    	fp.close();
    	remove("member.dat");
    	rename("Temp.dat","member.dat");
    	if(flag==1)
     		cout<<"Record Deleted";
    	else
     		cout<<"Record not found";
    	getch();
}
void delete_book()
{
	char n[50];
	clrscr();
	cout<<"DELETE BOOK";
cout<<"Enter The Book no. of the Book You Want To Delete:";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)  
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}
    	
	fp2.close();
    	fp.close();
    	remove("book.dat");
    	rename("Temp.dat","book.dat");
    	cout<<"Record Deleted";
    	getch();
}
void display_alls()
{
	clrscr();
     	fp.open("member.dat",ios::in);
     	if(!fp)
     	{
       		cout<<"ERROR FILE COULD NOT BE OPEN";
       		getch();
       		return;
     	}

	cout<<"MEMBER LIST";
	cout<<endl;
	cout<<"Admission No."<<endl<<"Name"<<endl<<"Book Issued";
	cout<<endl;

	while(fp.read((char*)&st,sizeof(member)))
	{
		st.report();
	}
     	
	fp.close();
	getch();
}
void display_allb()
{
	clrscr();
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR FILE COULD NOT BE OPEN";
       		getch();
       		return;
     	}

	cout<<"Book LIST";
	cout<<endl;
	cout<<"Book Number"<<endl<<"Book Name"<<endl<<"Author";
	cout<<endl;

	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
     	fp.close();
     	getch();
}
void book_issue()
{
	char sn[50],bn[50];
	int found=0,flag=0;
	clrscr();
	cout<<"BOOK ISSUE";
	cout<<"Enter The member's admission no.";
	cin>>sn;
	fp.open("member.dat",ios::in|ios::out);
    	fp1.open("book.dat",ios::in|ios::out);
    	while(fp.read((char*)&st,sizeof(member))&&found==0)
       	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
		      		cout<<"Enter the book no. ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&&flag==0)
				{
			   		if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
       					int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(member));
cout<<"Book issued successfully Please Note: Write current date 
in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
					}
		    		}
		  		if(flag==0)
		    			cout<<"Book no does not exist";
			}
	    		else
		  		cout<<"You have not returned the last book ";

		}
	}
      	if(found==0)
		cout<<"Member record does not exist";
	getch();
  	fp.close();
  	fp1.close();
}
void book_deposit()
{
    char sn[50],bn[50];
    int found=0,flag=0,days,fine;
    clrscr();
    cout<<"BOOK DEPOSIT";
    cout<<"Enter The member’s admission no.";
    cin>>sn;
    fp.open("member.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(member))&&found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
		while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				flag=1;
				cout<<"Book deposited in no. of days";
				cin>>days;
				if(days>15)
				{
				   fine=(days-15)*1;
			    cout<<"Fine to be deposited Rs."<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
                    fp.write((char*)&st,sizeof(member));
			cout<<"Book deposited successfully";
			}
		    }
		  if(flag==0)
		    cout<<"Book no does not exist";
		      }
		 else
			cout<<"No book is issued please check";
		}
	   }
      if(found==0)
	cout<<"Member record not exist";
	getch();
  fp.close();
  fp1.close();
  }
void search()
{
 char sn[50],bn[50];
 int found=0,flag=0;
 cout<<”enter admission number”;
 cin>>sn;
 fp.open(“member.dat”,ios::in|ios::out);
 fp1.open(“book.dat”,ios::in|ios::out);
 while(fp.read((char*)&st,sizeof(member))&&found==0)
 {
  if(strcmpi(st.retadmno(),sn)==0)
  {
    found=1;
    st.show_member();
    while(fp1.read((char*)bk,sizeof(book))&&flag==0)
     {
      if(strcmpi(bk.retbno(),st.retstbno())==0)
         { bk.show_book();
           flag=1;       
          } 
      }
     if(flag==0)
     cout<<”book not found”;
   } 
  }
if(found==0)  
cout<<”member does not exist”;
getch();
fp.close();
fp1.close();
}
void admin_menu()
{
	clrscr();
	int ch2;
	cout<<"ADMINISTRATOR MENU"<<endl;
	cout<<"1.CREATE MEMBER RECORD"<<endl;
	cout<<"2.DISPLAY ALL MEMBER RECORD"<<endl;
	cout<<"3.DISPLAY SPECIFIC MEMBER RECORD "<<endl;
	cout<<"4.MODIFY MEMBER RECORD"<<endl;
	cout<<"5.DELETE MEMBER RECORD"<<endl;
	cout<<"6.CREATE BOOK "<<endl;
	cout<<"7.DISPLAY ALL BOOKS "<<endl;
	cout<<"8.DISPLAY SPECIFIC BOOK "<<endl;
	cout<<"9.MODIFY BOOK "<<endl;
	cout<<"10.DELETE BOOK "<<endl;
	cout<<"11.BACK TO MAIN MENU"<<endl;
       cout<<”12.SEARCH MEMBER AND BOOK”<<endl;     
	cout<<"Please Enter Your Choice (1-12)"<<endl;
	cin>>ch2;
	switch(ch2)
	{
    		case 1: write_member();break;
    		case 2: display_alls();break;
    		case 3:char num[50];
	       	cout<<"Please Enter The Admission No. ";
	       	cin>>num;
	       	display_sps(num);
	       	break;
      		case 4: modify_member();break;
      		case 5: delete_member();break;
		case 6: write_book();break;
		case 7: display_allb();break;
		case 8: {
	       	char num[50];
	             cout<<"Please Enter The book No. ";
	       	cin>>num;
	       	display_spb(num);
	       	break;
			}
      		case 9: modify_book();break;
      		case 10: delete_book();break;
     		case 11: return;
             case 12:search();        
      		default:cout<<"Invalid";
   	}
 
}
void main()
{
	int ch;
	do
	{
		clrscr();
		cout<<"MAIN MENU";
		cout<<"1.BOOK ISSUE";
		cout<<"2.BOOK DEPOSIT";
	  	cout<<"3.ADMINISTRATOR MENU";
	  	cout<<"4.EXIT";
	  	cout<<"Please Select Your Option (1-4)";
	  	cin>>ch;
	  	switch(ch)
	  	{
			case 1:clrscr();
				 book_issue();
			   	 break;
		  	case 2:book_deposit();
			    	 break;
		  	case 3:admin_menu();
				 break;
		  	case 4:exit(0);
		}
    	}while(ch!='4');
}

