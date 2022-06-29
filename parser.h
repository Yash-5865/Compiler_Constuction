#include <bits/stdc++.h>
using namespace std;
struct node
{
	int term;
	string data;
	vector<node*> adj;
};
void parsetree(struct node* root);
void bfs(struct node* root);
void levelorder(struct node* root);

struct node* create(string data, unordered_map<string, int> &indexer)
{
    struct node* temp=new node;
    temp->term=0;
    if(indexer.find(data)!=indexer.end())
    {
        temp->term=1;
    }
    temp->data=data;
    return temp;
}

void follow_init(unordered_map<string, string[50]> &follows)
{
	follows["program"][0]="$";
    follows["preprocessor"][0]="$";
    follows["preprocessor"][1]="int";
    follows["preprocessor"][2]="float";
    follows["preprocessor"][3]="char";
    follows["preprocessor"][4]="boolean";
    follows["preprocessor"][5]="string";
    follows["library"][0]=">";
    follows["functions"][0]="$";
    follows["function"][0]="$";
    follows["function"][1]="int";
    follows["function"][2]="float";
    follows["function"][3]="char";
    follows["function"][4]="boolean";
    follows["function"][5]="string";
    follows["params"][0]=")";
    follows["params1"][0]=")";
    follows["param"][0]=",";
    follows["param"][1]=")";
    follows["param1"][0]=",";
    follows["param1"][1]=")";
    follows["stmts"][0]="return";
    follows["stmts"][1]="}";
    follows["stmts1"][0]="return";
    follows["stmts1"][1]="}";
    follows["stmt"][0]=";";
    follows["stmt2"][0]=";";
    follows["stmt3"][0]=";";
    follows["declaration"][0]=";";
    follows["arrayDecl"][0]=";";
    follows["arrayDecl1"][0]=";";
    follows["type"][0]="id";
    follows["Idlist"][0]="[";
    follows["Idlist"][1]=";";
    follows["Idlist"][2]=")";
    follows["Idlist1"][0]="[";
    follows["Idlist1"][1]=";";
    follows["Idlist1"][2]=")";
    follows["arrayAssign1"][0]=";";
    follows["arrayAssign2"][0]=";";
    follows["arrayAssign3"][0]=";";
    follows["arrayAssign4"][0]=";";
    follows["arrayAssign5"][0]=";";
    follows["arrayAssign6"][0]=";";
    follows["arrayAssign7"][0]=";";
    follows["arrayAssign8"][0]=";";
    follows["expression1"][0]=";";
    follows["expression2"][0]=";";
    follows["arithmetic_operator"][0]="num";
    follows["arithmetic_operator"][1]="id";
    follows["arithmetic_operator"][2]=";";
    follows["arithmetic_operator"][3]="+";
    follows["arithmetic_operator"][4]="-";
    follows["arithmetic_operator"][5]="*";
    follows["arithmetic_operator"][6]="/";
    follows["arithmetic_operator"][7]="%";
    follows["booleanExpr"][0]=";";
    follows["booleanExpr1"][0]=";";
    follows["booleanExpr2"][0]=";";
    follows["logical_operator"][0]=";";
    follows["logical_operator"][1]="&&";
    follows["logical_operator"][2]="||";
    follows["logical_operator"][3]="?";
    follows["logical_operator"][4]="!";
    follows["logical_operator"][5]="true";
    follows["logical_operator"][6]="false";
    follows["logical_operator"][7]="num";
    follows["relational_operator"][0]="num";
    follows["relational_operator"][1]="id";
    follows["args"][0]=")";
    follows["conditional"][0]=";";
    follows["if1"][0]=";";
    follows["if2"][0]=";";
    follows["if3"][0]=";";
    follows["if_else"][0]=";";
    follows["loop"][0]=";";
    follows["while1"][0]=";";
    follows["while2"][0]=";";
    follows["for1"][0]=";";
    follows["for2"][0]=";";
}

void indexer_init(int c, unordered_map<string, int> &indexer, string terms[41])
{
	while(c<41)
    {
    	indexer[terms[c]]=c;
    	c++;
    }
}

void table_init(unordered_map<string, string[50]> &table, unordered_map<string, int> &indexer)
{
	table["program"][indexer["#"]]="preprocessor functions";
    table["program"][indexer["int"]]="preprocessor functions";
    table["program"][indexer["float"]]="preprocessor functions";
    table["program"][indexer["char"]]="preprocessor functions";
    table["program"][indexer["boolean"]]="preprocessor functions";
    table["program"][indexer["string"]]="preprocessor functions";
    table["program"][indexer["$"]]="preprocessor functions";
    table["preprocessor"][indexer["#"]]="# include < library > preprocessor";
    table["preprocessor"][indexer["int"]]="NULL";
    table["preprocessor"][indexer["float"]]="NULL";
    table["preprocessor"][indexer["char"]]="NULL";
    table["preprocessor"][indexer["boolean"]]="NULL";
    table["preprocessor"][indexer["string"]]="NULL";
    table["preprocessor"][indexer["$"]]="NULL";
    table["library"][indexer["stdio.h"]]="stdio.h";
    table["library"][indexer["math.h"]]="math.h";
    table["library"][indexer["bits/stdc++.h"]]="bits/stdc++.h";
    table["functions"][indexer["int"]]="function functions";
    table["functions"][indexer["float"]]="function functions";
    table["functions"][indexer["char"]]="function functions";
    table["functions"][indexer["boolean"]]="function functions";
    table["functions"][indexer["string"]]="function functions";
    table["functions"][indexer["$"]]="NULL";
    table["function"][indexer["int"]]="type id ( params ) { stmts return expression1 ; }";
    table["function"][indexer["float"]]="type id ( params ) { stmts return expression1 ; }";
    table["function"][indexer["char"]]="type id ( params ) { stmts return expression1 ; }";
    table["function"][indexer["boolean"]]="type id ( params ) { stmts return expression1 ; }";
    table["function"][indexer["string"]]="type id ( params ) { stmts return expression1 ; }";
    table["params"][indexer[")"]]="param params1";
    table["params"][indexer[","]]="param params1";
    table["params"][indexer["int"]]="param params1";
    table["params"][indexer["float"]]="param params1";
    table["params"][indexer["char"]]="param params1";
    table["params"][indexer["boolean"]]="param params1";
    table["params"][indexer["string"]]="param params1";
    table["params1"][indexer[")"]]="NULL";
    table["params1"][indexer[","]]=", params";
    table["param"][indexer[")"]]="NULL";
    table["param"][indexer[","]]="NULL";
    table["param"][indexer["int"]]="type id param1";
    table["param"][indexer["float"]]="type id param1";
    table["param"][indexer["char"]]="type id param1";
    table["param"][indexer["boolean"]]="type id param1";
    table["param"][indexer["string"]]="type id param1";
    table["param1"][indexer[")"]]="NULL";
    table["param1"][indexer[","]]="NULL";
    table["param1"][indexer["["]]="[ ]";
    table["stmts"][indexer["id"]]="stmt ; stmts1";
    table["stmts"][indexer["num"]]="stmt ; stmts1";
    table["stmts"][indexer["int"]]="stmt ; stmts1";
    table["stmts"][indexer["float"]]="stmt ; stmts1";
    table["stmts"][indexer["char"]]="stmt ; stmts1";
    table["stmts"][indexer["boolean"]]="stmt ; stmts1";
    table["stmts"][indexer["string"]]="stmt ; stmts1";
    table["stmts"][indexer["true"]]="stmt ; stmts1";
    table["stmts"][indexer["false"]]="stmt ; stmts1";
    table["stmts"][indexer["if"]]="stmt ; stmts1";
    table["stmts"][indexer["while"]]="stmt ; stmts1";
    table["stmts"][indexer["for"]]="stmt ; stmts1";
    table["stmts1"][indexer["id"]]="stmts";
    table["stmts1"][indexer["return"]]="NULL";
    table["stmts1"][indexer["}"]]="NULL";
    table["stmts1"][indexer["num"]]="stmts";
    table["stmts1"][indexer["int"]]="stmts";
    table["stmts1"][indexer["float"]]="stmts";
    table["stmts1"][indexer["char"]]="stmts";
    table["stmts1"][indexer["boolean"]]="stmts";
    table["stmts1"][indexer["string"]]="stmts";
    table["stmts1"][indexer["true"]]="stmts";
    table["stmts1"][indexer["false"]]="stmts";
    table["stmts1"][indexer["if"]]="stmts";
    table["stmts1"][indexer["while"]]="stmts";
    table["stmts1"][indexer["for"]]="stmts";
    table["stmt"][indexer["id"]]="id stmt3";
    table["stmt"][indexer["num"]]="num stmt2";
    table["stmt"][indexer["int"]]="declaration";
    table["stmt"][indexer["float"]]="declaration";
    table["stmt"][indexer["char"]]="declaration";
    table["stmt"][indexer["boolean"]]="declaration";
    table["stmt"][indexer["string"]]="declaration";
    table["stmt"][indexer["true"]]="booleanExpr";
    table["stmt"][indexer["false"]]="booleanExpr";
    table["stmt"][indexer["if"]]="conditional";
    table["stmt"][indexer["while"]]="loop";
    table["stmt"][indexer["for"]]="loop";
    table["stmt2"][indexer["<"]]="relational_operator num booleanExpr1";
    table["stmt2"][indexer[">"]]="relational_operator num booleanExpr1";
    table["stmt2"][indexer["id"]]="expression1";
    table["stmt2"][indexer[";"]]="expression1";
    table["stmt2"][indexer["num"]]="expression1";
    table["stmt2"][indexer["+"]]="expression1";
    table["stmt2"][indexer["-"]]="expression1";
    table["stmt2"][indexer["*"]]="expression1";
    table["stmt2"][indexer["/"]]="expression1";
    table["stmt2"][indexer["%"]]="expression1";
    table["stmt2"][indexer["!="]]="relational_operator num booleanExpr1";
    table["stmt3"][indexer["id"]]="expression1";
    table["stmt3"][indexer[";"]]="expression1";
    table["stmt3"][indexer["["]]="arrayAssign1";
    table["stmt3"][indexer["num"]]="expression1";
    table["stmt3"][indexer["="]]="arrayAssign1";
    table["stmt3"][indexer["+"]]="expression1";
    table["stmt3"][indexer["-"]]="expression1";
    table["stmt3"][indexer["*"]]="expression1";
    table["stmt3"][indexer["/"]]="expression1";
    table["stmt3"][indexer["%"]]="expression1";
    table["declaration"][indexer["int"]]="arrayDecl";
    table["declaration"][indexer["float"]]="arrayDecl";
    table["declaration"][indexer["char"]]="arrayDecl";
    table["declaration"][indexer["boolean"]]="arrayDecl";
    table["declaration"][indexer["string"]]="arrayDecl";
    table["arrayDecl"][indexer["int"]]="type Idlist arrayDecl1";
    table["arrayDecl"][indexer["float"]]="type Idlist arrayDecl1";
    table["arrayDecl"][indexer["char"]]="type Idlist arrayDecl1";
    table["arrayDecl"][indexer["boolean"]]="type Idlist arrayDecl1";
    table["arrayDecl"][indexer["string"]]="type Idlist arrayDecl1";
    table["arrayDecl1"][indexer[";"]]="NULL";
    table["arrayDecl1"][indexer["["]]="[ num ]";
    table["type"][indexer["int"]]="int";
    table["type"][indexer["float"]]="float";
    table["type"][indexer["char"]]="char";
    table["type"][indexer["boolean"]]="boolean";
    table["type"][indexer["string"]]="string";
    table["Idlist"][indexer["id"]]="id Idlist1";
    table["Idlist1"][indexer[")"]]="NULL";
    table["Idlist1"][indexer[";"]]="NULL";
    table["Idlist1"][indexer[")"]]="NULL";
    table["Idlist1"][indexer[","]]=", Idlist";
    table["Idlist1"][indexer["["]]="NULL";
    table["arrayAssign1"][indexer["["]]="[ num ] = arrayAssign7";
    table["arrayAssign1"][indexer["="]]="= arrayAssign2";
    table["arrayAssign7"][indexer["id"]]="id arrayAssign3";
    table["arrayAssign7"][indexer["num"]]="num arrayAssign3";
    table["arrayAssign3"][indexer[";"]]="NULL";
    table["arrayAssign3"][indexer["+"]]="arithmetic_operator arrayAssign4";
    table["arrayAssign3"][indexer["-"]]="arithmetic_operator arrayAssign4";
    table["arrayAssign3"][indexer["*"]]="arithmetic_operator arrayAssign4";
    table["arrayAssign3"][indexer["/"]]="arithmetic_operator arrayAssign4";
    table["arrayAssign3"][indexer["%"]]="arithmetic_operator arrayAssign4";
    table["arrayAssign4"][indexer["id"]]="id";
    table["arrayAssign4"][indexer["num"]]="num";
    table["arrayAssign2"][indexer["id"]]="id arrayAssign5";
    table["arrayAssign2"][indexer["num"]]="num arrayAssign8";
    table["arrayAssign8"][indexer[";"]]="NULL";
    table["arrayAssign8"][indexer["+"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign8"][indexer["-"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign8"][indexer["*"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign8"][indexer["/"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign8"][indexer["%"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign5"][indexer["("]]="( args )";
    table["arrayAssign5"][indexer[";"]]="NULL";
    table["arrayAssign5"][indexer["+"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign5"][indexer["-"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign5"][indexer["*"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign5"][indexer["/"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign5"][indexer["%"]]="arithmetic_operator arrayAssign6";
    table["arrayAssign6"][indexer["id"]]="id";
    table["arrayAssign6"][indexer["num"]]="num";
    table["expression1"][indexer["id"]]="expression2";
    table["expression1"][indexer[";"]]="NULL";
    table["expression1"][indexer["num"]]="expression2";
    table["expression1"][indexer["+"]]="arithmetic_operator expression1";
    table["expression1"][indexer["-"]]="arithmetic_operator expression1";
    table["expression1"][indexer["*"]]="arithmetic_operator expression1";
    table["expression1"][indexer["/"]]="arithmetic_operator expression1";
    table["expression1"][indexer["%"]]="arithmetic_operator expression1";
    table["expression2"][indexer["id"]]="id";
    table["expression2"][indexer["num"]]="num";
    table["arithmetic_operator"][indexer["+"]]="+";
    table["arithmetic_operator"][indexer["-"]]="-";
    table["arithmetic_operator"][indexer["*"]]="*";
    table["arithmetic_operator"][indexer["/"]]="/";
    table["arithmetic_operator"][indexer["%"]]="%";
    table["booleanExpr"][indexer["true"]]="true booleanExpr1";
    table["booleanExpr"][indexer["false"]]="false booleanExpr1";
    table["booleanExpr1"][indexer[";"]]="NULL";
    table["booleanExpr1"][indexer["num"]]="booleanExpr2";
    table["booleanExpr1"][indexer["true"]]="booleanExpr2";
    table["booleanExpr1"][indexer["false"]]="booleanExpr2";
    table["booleanExpr1"][indexer["&&"]]="logical_operator booleanExpr1";
    table["booleanExpr1"][indexer["||"]]="logical_operator booleanExpr1";
    table["booleanExpr1"][indexer["?"]]="logical_operator booleanExpr1";
    table["booleanExpr1"][indexer["!"]]="logical_operator booleanExpr1";
    table["booleanExpr2"][indexer["num"]]="num relational_operator num";
    table["booleanExpr2"][indexer["true"]]="true";
    table["booleanExpr2"][indexer["false"]]="false";
    table["logical_operator"][indexer["&&"]]="&&";
    table["logical_operator"][indexer["||"]]="||";
    table["logical_operator"][indexer["?"]]="?";
    table["logical_operator"][indexer["!"]]="!";
    table["relational_operator"][indexer["<"]]="<";
    table["relational_operator"][indexer[">"]]=">";
    table["relational_operator"][indexer["!="]]="!=";
    table["args"][indexer["id"]]="Idlist";
    table["args"][indexer[")"]]="NULL";
    table["conditional"][indexer["if"]]="if1";
    table["if1"][indexer["if"]]="if ( if2";
    table["if2"][indexer["id"]]="id relational_operator if3";
    table["if2"][indexer["num"]]="num relational_operator num ) { stmts } if_else";
    table["if3"][indexer["id"]]="id ) { stmts } if_else";
    table["if3"][indexer["num"]]="num ) { stmts } if_else";
    table["if_else"][indexer[";"]]="NULL";
    table["if_else"][indexer["else"]]="else ( ) { stmts }";
    table["loop"][indexer["while"]]="while1";
    table["loop"][indexer["for"]]="for1";
    table["while1"][indexer["while"]]="while ( id relational_operator while2";
    table["while2"][indexer["id"]]="id ) { stmts }";
    table["while2"][indexer["num"]]="num ) { stmts }";
    table["for1"][indexer["for"]]="for ( id = num ; id relational_operator for2";
    table["for2"][indexer["id"]]="id ; id = id arithmetic_operator num ) { stmts }";
    table["for2"][indexer["num"]]="num ; id = id arithmetic_operator num ) { stmts }";
}

void printstack(stack<string> &st,stack<string> &st1)
{
    cout<<"-------------START-------------"<<endl;
    while(!st.empty())
    {
        st1.push(st.top());
        cout<<st.top()<<endl;
        st.pop();
    }
    while(!st1.empty())
    {
        st.push(st1.top());
        st1.pop();
    }
    cout<<"-------------END-------------"<<endl;
}

void parse(int pr,struct node* root, stack<string> &st, stack<string> &st1, int inc, string inp[1000], unordered_map<string, int> &indexer, unordered_map<string, string[50]> &table, vector<string> &productions,int checker, unordered_map<string, string[50]> &follows,string add,string prod,string adders[1000],int inc1,int search,int curr)
{

	st.push("$");
	st.push("program");
	while(curr<inc && st.top()!="$")
	{
	    if(pr>0)
        {
            printstack(st,st1);
        }
		if(st.top()==inp[curr])
		{
			st.pop();
			curr++;
		}
		else
		{
			add.clear();
			prod=table[st.top()][indexer[inp[curr]]];
			string prodarray=st.top()+" prod "+prod;
			productions.push_back(prodarray);
			if(prod=="NULL")
			{
				st.pop();
			}
			else if(prod=="")
			{
                checker=1;
				search=0;
				for(int i=0;i<50;i++)
				{
					if(follows[st.top()][i]==inp[curr])
					{
						search=1;
						break;
					}
				}
				if(search==1)
				{
					st.pop();
				}
				else
				{
					curr++;
				}
			}
			else
			{
				for(int i=0;i<1000;i++)
				{
					adders[i].clear();
				}
				inc1=0;
				for(int i=0;i<prod.length();i++)
				{
					if(prod[i]==' ')
					{
						adders[inc1]=add;
						inc1++;
						add.clear();
					}
					else
					{
						add+=prod[i];
					}
				}
				adders[inc1]=add;
				inc1++;
				st.pop();
				for(int i=inc1-1;i>=0;i--)
				{
					st.push(adders[i]);
				}
			}
		}
	}
    if(pr>0)
    {
        printstack(st,st1);
    }
}


void levelorder(struct node* root,queue<struct node*>q)
{
	q.push(root);
	int cnt=1,cnt2=0;
	while(!q.empty())
	{
		while(cnt>0)
		{
			struct node* temp=q.front();
			q.pop();
			cout<<temp->data<<" ";
			if(temp->adj.size()>0)
			{
				for(int i=0;i<temp->adj.size();i++)
				{
					q.push(temp->adj[i]);
					cnt2++;
				}
			}
			cnt--;
		}
		cnt=cnt2;
		cnt2=0;
        cout<<"\n";
	}
}

void bfs(struct node* root,queue<struct node*>q)
{
    q.push(root);
    int cnt=1,cnt2=0;
    while(!q.empty())
    {
        struct node* temp=q.front();
        cout<<temp->data<<" ";
        q.pop();
        if(temp->term==1)
        {
            continue;
        }
        for(int i=0;i<temp->adj.size();i++)
        {
            q.push(temp->adj[i]);
        }
    }
}

