#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>

class song
	{
	int sid,noa;
	long noc;
	char song[20], singer[20], album[20], genre[20], lang[20];
	float inc;

	public:

	void getdata()
		{
		cout<<endl<<"Enter song ID: ";
		cin>>sid;
		cout<<"Enter song name: ";
		gets(song);
		cout<<"Enter singer name: ";
		gets(singer);
		cout<<"Enter album name: ";
		gets(album);
		cout<<"Enter genre: ";
		gets(genre);
		cout<<"Enter language: ";
		gets(lang);
		cout<<"Enter number of copies sold: ";
		cin>>noc;
		cout<<"Enter number of awards received: ";
		cin>>noa;
		cout<<"Enter gross income($): ";
		cin>>inc;
		}

	void display()
		{
		cout<<endl<<"Song ID: "<<sid;
		cout<<endl<<"Song name: "<<song;
		cout<<endl<<"Singer name: "<<singer;
		cout<<endl<<"Album name: "<<album;
		cout<<endl<<"Genre: "<<genre;
		cout<<endl<<"Language: "<<lang;
		cout<<endl<<"Number of copies sold: "<<noc;
		cout<<endl<<"Number of awards received: "<<noa;
		cout<<endl<<"Gross income: $"<<inc<<endl;
		}

	int ret_sid()
		{
		return sid;
		}

	char* ret_song()
		{
		return song;
		}

	char* ret_singer()
		{
		return singer;
		}

	char* ret_album()
		{
		return album;
		}

	char* ret_genre()
		{
		return genre;
		}

	char* ret_lang()
		{
		return lang;
		}

	long ret_noc()
		{
		return noc;
		}
	int ret_noa()
		{
		return noa;
		}

	float ret_inc()
		{
		return inc;
		}
	};

char ans;
fstream file,temp;
song s1,s2;

void create()
	{
	file.open("song.dat", ios::out|ios::binary);

	do
		{
		s1.getdata();
		file.write((char*)&s1,sizeof(s1));

		cout<<endl<<"Do you want to enter another record? y/n: ";
		cin>>ans;
		}
	while(ans=='Y'||ans=='y');

	file.close();
	}

void read()
	{
	file.open("song.dat", ios::in|ios::binary);

	while(file.read((char*)&s1,sizeof(s1)))
		s1.display();

	file.close();
	}

void search()
	{
	int ch;

	file.open("song.dat", ios::in|ios::binary);

	cout<<endl<<"1: On the basis of song ID";
	cout<<endl<<"2: On the basis of singer";
	cout<<endl<<"3: On the basis of language";
	cout<<endl<<"Enter choice: ";
	cin>>ch;

	switch(ch)
		{
		case 1: int s;

			cout<<endl<<"Enter song ID to be searched: ";
			cin>>s;

			while(file.read((char*)&s1,sizeof(s1)))
				if(s==s1.ret_sid())
					s1.display();
			break;

		case 2: char sn[20];

			cout<<endl<<"Enter singer name to be searched: ";
			gets(sn);

			while(file.read((char*)&s1,sizeof(s1)))
				if(strcmp(sn,s1.ret_singer())==0)
					s1.display();
			break;

		case 3: char l[20];

			cout<<endl<<"Enter language to be searched: ";				gets(l);

			while(file.read((char*)&s1,sizeof(s1)))
				if(strcmp(l,s1.ret_lang())==0)
					s1.display();
			break;

		default: cout<<endl<<"Wrong choice";
		}

	file.close();
	}

void edit()
	{
	int ch;

	file.open("song.dat", ios::in|ios::binary);
	temp.open("new.dat", ios::out|ios::binary);

	cout<<endl<<"1: On the basis of record number";
	cout<<endl<<"2: Edit on the basis of number of copies sold";
	cout<<endl<<"3: On the basis of album name";
	cout<<endl<<"Enter choice: ";
	cin>>ch;

	switch(ch)
		{
		case 1: int r=0,rn;

			cout<<endl<<"Enter record number: ";
			cin>>rn;

			while(file.read((char*)&s1,sizeof(s1)))
				{
				r++;
				if(r==rn)
					s1.getdata();

				temp.write((char*)&s1,sizeof(s1));
				}
			break;

		case 2: int n;

			cout<<endl<<"Enter number of copies sold: ";
			cin>>n;

			file.seekg(0);

			while(file.read((char*)&s1,sizeof(s1)))
				{
				if(s1.ret_noc()==n)
					s1.getdata();

				temp.write((char*)&s1,sizeof(s1));
				}
			break;

		case 3: char a[20];

			cout<<endl<<"Enter album name: ";
			gets(a);

			file.seekg(0);

			while(file.read((char*)&s1,sizeof(s1)))
				{
				if(strcmp(s1.ret_album(),a)==0)
					s1.getdata();

				temp.write((char*)&s1,sizeof(s1));
				}
			break;

		default: cout<<endl<<"Wrong choice";
		}

	temp.close();
	file.close();
	remove("song.dat");
	rename("new.dat","song.dat");
	}

void count()
	{
	int ch,cnt=0;

	file.open("song.dat", ios::in|ios::binary);

	cout<<endl<<"1: Total number of records";
	cout<<endl<<"2: Whose gross income > user entered value";
	cout<<endl<<"3: On the basis of user entered genre";
	cout<<endl<<"Enter choice: ";
	cin>>ch;

	switch(ch)
		{
		case 1: while(file.read((char*)&s1,sizeof(s1)))
				cnt++;

			cout<<endl<<"Total number of records: "<<cnt;

			break;

		case 2: float i;

			cout<<endl<<"Enter gross income($): ";
			cin>>i;

			while(file.read((char*)&s1,sizeof(s1)))
				if(s1.ret_inc()>i)
					cnt++;

			cout<<endl<<"Total number of records with gross income>$"<<i<<": "<<cnt;

			break;

		case 3: char g[20];

			cout<<endl<<"Enter genre: ";
			gets(g);

			while(file.read((char*)&s1,sizeof(s1)))
				if(strcmp(s1.ret_genre(),g)==0)
					cnt++;

			cout<<endl<<"Number of records with user entered genre: "<<cnt;

			break;

		default: cout<<endl<<"Wrong choice";
		}

	file.close();
	}

void insert()
	{
	int ch;

	file.open("song.dat", ios::in|ios::binary);
	temp.open("new.dat", ios::out|ios::binary);

	cout<<endl<<"1: Insert at first position";
	cout<<endl<<"2: Insert at last position";
	cout<<endl<<"3: Insert at nth position";
	cout<<endl<<"4: Insert after user given song name";
	cout<<endl<<"Enter choice: ";
	cin>>ch;

	switch(ch)
		{
		case 1: s1.getdata();
			temp.write((char*)&s1,sizeof(s1));

			while(file.read((char*)&s1,sizeof(s1)))
				temp.write((char*)&s1,sizeof(s1));
			break;

		case 2: while(file.read((char*)&s1,sizeof(s1)))
				temp.write((char*)&s1,sizeof(s1));

			s1.getdata();
			temp.write((char*)&s1,sizeof(s1));

			break;

		case 3: int r=0, rn;

			cout<<endl<<"Enter record number after which you want to insert new record: ";
			cin>>rn;

			while(file.read((char*)&s1,sizeof(s1)))
				{
				r++;

				temp.write((char*)&s1,sizeof(s1));

				if(r==rn)
					{
					s1.getdata();
					temp.write((char*)&s1,sizeof(s1));
					}
				}
			break;

		case 4: char name[20];

			cout<<endl<<"Enter song name after which you want to enter record: ";
			gets(name);

			file.seekg(0);

			while(file.read((char*)&s1,sizeof(s1)))
				{
				temp.write((char*)&s1,sizeof(s1));

				if(strcmp(s1.ret_song(),name)==0)
					{
					s1.getdata();
					temp.write((char*)&s1,sizeof(s1));
					}
				}
			break;

		default: cout<<endl<<"Wrong choice";
		}

	temp.close();
	file.close();
	remove("song.dat");
	rename("new.dat","song.dat");
	}

void del()
	{
	int ch, r=0;

	file.open("song.dat", ios::in|ios::binary);
	temp.open("new.dat", ios::out|ios::binary);

	cout<<endl<<"1: Delete first record";
	cout<<endl<<"2: Delete last record";
	cout<<endl<<"3: Delete nth record";
	cout<<endl<<"4: On the basis of number of awards";
	cout<<endl<<"Enter choice: ";
	cin>>ch;

	switch(ch)
		{
		case 1: file.read((char*)&s1,sizeof(s1));

			while(file.read((char*)&s1,sizeof(s1)))
				temp.write((char*)&s1,sizeof(s1));

			break;

		case 2: int lp,lr,s;

			file.seekg(0,ios::end);

			lp=file.tellg();
			s=sizeof(s1);
			lr=lp/s;

			file.seekg(0);

			while(file.read((char*)&s1,sizeof(s1)))
				{
				r++;

				if(r!=lr)
					temp.write((char*)&s1,sizeof(s1));
				}
			break;

		case 3: int rn;

			cout<<endl<<"Enter record number to delete: ";
			cin>>rn;

			file.seekg(0);

			while(file.read((char*)&s1,sizeof(s1)))
				{
				r++;

				if(r!=rn)
					temp.write((char*)&s1,sizeof(s1));
				}
			break;

		case 4: int awards;

			cout<<endl<<"Enter the number of awards of record to be deleted: ";
			cin>>awards;

			file.seekg(0);

			while(file.read((char*)&s1,sizeof(s1)))
				if(s1.ret_noa()!=awards)
					temp.write((char*)&s1,sizeof(s1));
			break;

		default: cout<<endl<<"Wrong choice";
		}

	temp.close();
	file.close();
	remove("song.dat");
	rename("new.dat","song.dat");
	}

void main()
	{
	clrscr();

	int ch;
	char ans;

	do
		{
		clrscr();

		cout<<endl<<"1: Create";
		cout<<endl<<"2: Read";
		cout<<endl<<"3: Search";
		cout<<endl<<"4: Edit";
		cout<<endl<<"5: Count";
		cout<<endl<<"6: Insert";
		cout<<endl<<"7: Delete";
		cout<<endl<<"Enter choice: ";
		cin>>ch;

		switch(ch)
			{
			case 1: create();
				break;

			case 2: read();
				break;

			case 3: search();
				break;

			case 4: edit();
				break;

			case 5: count();
				break;

			case 6: insert();
				break;

			case 7: del();
				break;

			default: cout<<endl<<"Wrong choice";
			}

		cout<<endl<<"Do you want to return to main menu? y/n: ";
		cin>>ans;
		}
	while(ans=='Y'||ans=='y');

	getche();
	}