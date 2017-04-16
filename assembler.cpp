#include<bits/stdc++.h>
#define vec(i) vector<(i)>
#define pb push_back
#define forn(i,n) for(int (i) = 0 ; (i) < (n) ; (i)++ )

using namespace std;

struct MOT
{
	string str;
	string op;
	string cls;	
};

struct REG
{
	string str;
	int ind;
};

struct CON
{
	string str;
	int ind;
};

struct SYMTAB
{
	int index;
	string str;
	int add;
};

struct LITTAB
{
	int index;
	string str;
	int add;
};


MOT mot[18];
REG reg[4];
CON con[7];
LITTAB lit[30];
SYMTAB sym[30];


void init()
{
	forn(i,17)
		cin>>mot[i].str>>mot[i].op>>mot[i].cls;
	forn(i,4)
		cin>>reg[i].str>>reg[i].ind;
	forn(i,6)
		cin>>con[i].str>>reg[i].ind;
}

int stoi_dc(string ss)
{
	int ans = 0;
	for(int i = 1 ; i < ss.size() -1 ; i++)
	{
		ans = ans * 10 + ss[i] - '0';
	}
	return ans;
}

int is_mot(string str)
{
	for(int i = 1 ; i <= 17 ; i++)
		if(mot[i].str == str)
			return i;
	return 0;
}

int is_reg(string str)
{
	for(int i = 1 ; i <= 4 ; i++)
		if(reg[i].str == str)
			return i;
	return 0;
}

int is_con(string str)
{
	for(int i = 1 ; i <= 6 ; i++)
		if(con[i].str == str)
			return i;
	return 0;
}

int is_sym(string str,int n)
{
	for(int i = 1 ; i <= n ; i++)
		if(sym[i].str == str)
			return i;
	return 0;
}

bool Valid(int n)
{
	for(int i = 1 ; i <= n ; i++)
		if(sym[i].add == -1)
			return false;
	return true;
}

int is_lit(string str,int n)
{
	for(int i = 1 ; i <= n ; i++)
		if(lit[i].str == str)
			return i;
	return 0;
}

void sym_print(int n)
{
	for(int i = 1 ; i < n ; i++)
		cout<<sym[i].index<<" "<<sym[i].str<<" "<<sym[i].add<<endl;
}

void lit_print(int n)
{
	for(int i = 1 ; i < n ; i++)
		cout<<lit[i].index<<" "<<lit[i].str<<" "<<lit[i].add<<endl;
}

bool is_AD(vector<string> v)
{
	forn(i,v.size())
		if(v[i] == "START" || v[i] == "END" || v[i] == "LTORG" || v[i] == "EQU" || v[i] == "ORIGIN")
			return true;
	return false;
}

int main()
{
	freopen("Mot_input","r",stdin);
	freopen("pass1_out","w",stdout);
	init();
	cin.clear();
	freopen("pass1_input","r",stdin);
	int LC = 0 ,n ,index = 0,sc = 1,lc = 1;
	string ss;
	while(getline(cin,ss))
	{
		vector<string> v;
		istringstream iss(ss);
		copy(istream_iterator<string>(iss),istream_iterator<string>(), back_inserter(v));
		if(!is_AD(v))
			cout<<++LC<<" ";
		for(int i = 0 ; i < v.size() ; i++)
		{ 
			if(v[i] != ",")
			{
				index = is_mot(v[i]);
				if(!index)
				{
					index = is_reg(v[i]);
					if(!index)
					{
						index = is_con(v[i]);
						if(!index)
						{
							index = is_lit(v[i],lc);
							if(v[i][0] == '=' && (!index || lit[index].index != -1))
							{
								lit[lc].index = lc;
								lit[lc].str = v[i];
								lit[lc].add = -1;
								lc++;
							}
							index = is_sym(v[i],sc);
							if(isalpha(v[i][0]) && (!index) && (i == 0 || i == v.size()-1 ))
							{
								sym[sc].index = sc;
								sym[sc].str = v[i];
								if(i == 0)
									sym[sc].add = LC ;
								else
								{
									sym[sc].add = -1;
								}
								sc++;
							}
						}
						else
							cout<<con[index].ind <<" ";
					} 
					else
						cout<<reg[index].ind<<" ";
				}
				else
					cout<<"("<<mot[index].cls<<","<<mot[index].op<<")"<<" ";
				if(i > 0 && v[i-1] == "START" && isdigit(v[i][0]))
				{
					cout<<"(C,"<<v[i]<<")"<<" ";
					LC = stoi(v[i]) - 1;
				}
				if(v[i] == "LTORG" || v[i] == "END")
				{
					for(int i = 1 ; i <= lc ; i++)
					{
						if(lit[i].add == -1)
							lit[i].add = LC++;
					}
				}
				
				index = is_sym(v[i],sc);
				if( index )
				{
					if(i == 0)
						sym[index].add = LC ;
					else
						cout<<"(S,"<<sym[index].index<<")"<<" ";
				}
				
				index = is_lit(v[i],lc);
				if(index)
				{
					cout<<"(L,"<<lit[index].index<<")"<<" ";
				}
				if(i > 0 && v[i - 1] == "DC" && isdigit(v[i][1]))
				{
					cout<<"(C,"<<v[i]<<")"<<" ";
					LC += stoi_dc(v[i]) - 1; 
				}
				if(i > 0 && v[i - 1] == "DS" && isdigit(v[i][0]))
				{
					cout<<"(C,"<<v[i]<<")"<<" "; 
				}
				if(v[i] == "EQU")
				{
					int right = is_sym(v[i+1],sc),left = is_sym(v[i-1],sc);
					if(right && left)
						sym[left].add = sym[right].add;
				}
			}
				
		}
		cout<<endl;		
	}	
	cin.clear();cout.clear();
	freopen("pass2_input","w",stdout);
	sym_print(sc);
	lit_print(lc);
	cin.clear();cout.clear();
	freopen("pass1_out","r+",stdin);
	freopen("pass2_out","w",stdout);
	while(getline(cin,ss))
	{
		vector<string> v;
		istringstream iss(ss);
		copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(v));
		for(int i = 0 ; i < v.size() ; i++)
		{
			if(isdigit(v[i][0]))
				cout<<v[i]<<" ";
			else if(v[i][1] == 'D' || v[i][1] == 'I')
				cout<<v[i][4]<<v[i][5]<<" ";
			else if(v[i][1] == 'L')
				cout<<lit[v[i][3] - '0'].add<<" ";
			else if(v[i][1] == 'S')
				cout<<sym[v[i][3] - '0'].add<<" ";
			else
				cout<<"---"<<" ";
		}
		cout<<endl;
	}
	return 0;
}

