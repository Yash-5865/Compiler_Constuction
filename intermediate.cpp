#include<bits/stdc++.h>
#include "parser.h"
using namespace std;


int inc4=0,inc5=0,inc6=0,inc7=0;
void parsetree(struct node* root, struct node* newnode[1000], unordered_map<string, int> &indexer, vector<string> &productions, string ids[], string nums[],string nxt,int ct)
{
	ct=0;
	/*cout<<root->data<<"ROOT "<<endl;
    for(int i=0;i<productions.size();i++)
    {
    	cout<<productions[i]<<endl;
    }*/
    nxt="";
	if(root->term==1 || root->data=="NULL")
	{
	    if(root->data=="id")
        {
            newnode[inc5]=create(ids[inc6],indexer);
            root->adj.push_back(newnode[inc5]);
            inc5++;
            inc6++;
        }
        if(root->data=="num")
        {
            newnode[inc5]=create(nums[inc7],indexer);
            root->adj.push_back(newnode[inc5]);
            inc5++;
            inc7++;
        }
		return;
	}
	else
	{
		nxt="";
		for(int i=0;i<productions[inc4].length();i++)
		{
			if(productions[inc4][i]==' ')
			{
				ct++;
				if(ct>2)
				{
                    newnode[inc5]=create(nxt,indexer);
					root->adj.push_back(newnode[inc5]);
                    inc5++;
				}
				nxt="";
			}
			else
			{
				nxt+=productions[inc4][i];
			}
		}
        newnode[inc5]=create(nxt,indexer);
        root->adj.push_back(newnode[inc5]);
        inc5++;
		nxt="";
		inc4++;
		for(int i=0;i<root->adj.size();i++)
		{
			parsetree(root->adj[i],newnode,indexer,productions,ids,nums,nxt,ct);
		}
	}
}

vector<pair<string,pair<string,pair<string,string>>>>quadruples;

void sdt(struct node* root)
{
    queue<struct node*>q;
    q.push(root);
    while(!q.empty())
    {
        struct node* temp=q.front();
        q.pop();
        if(temp->data=="stmt")
        {
            if(temp->adj.size()==2)
            {
                if(temp->adj[0]->data=="id" && temp->adj[1]->data=="stmt3")
                {
                    string id1=temp->adj[0]->adj[0]->data;
                    if(temp->adj[1]->adj.size()>0 && temp->adj[1]->adj[0]->data=="arrayAssign1" && temp->adj[1]->adj[0]->adj[0]->data=="=" && temp->adj[1]->adj[0]->adj[1]->data=="arrayAssign2")
                    {
                        string op="";
                        string id2="";
                        if(temp->adj[1]->adj[0]->adj[1]->adj[0]->data=="id" && temp->adj[1]->adj[0]->adj[1]->adj[1]->data=="arrayAssign5")
                        {
                            id2=temp->adj[1]->adj[0]->adj[1]->adj[0]->adj[0]->data;
                        }
                        if(temp->adj[1]->adj[0]->adj[1]->adj[0]->data=="num" && temp->adj[1]->adj[0]->adj[1]->adj[1]->data=="arrayAssign8")
                        {
                            id2=temp->adj[1]->adj[0]->adj[1]->adj[0]->adj[0]->data;
                        }
                        if(id2!="")
                        {
                            if(temp->adj[1]->adj[0]->adj[1]->adj[1]->adj.size()>0 && temp->adj[1]->adj[0]->adj[1]->adj[1]->adj[0]->data=="arithmetic_operator" && temp->adj[1]->adj[0]->adj[1]->adj[1]->adj[1]->data=="arrayAssign6")
                            {
                                string op=temp->adj[1]->adj[0]->adj[1]->adj[1]->adj[0]->adj[0]->data;
                                string id3=temp->adj[1]->adj[0]->adj[1]->adj[1]->adj[1]->adj[0]->adj[0]->data;
                                pair<string,pair<string,pair<string,string>>>temp2={op,{id2,{id3,id1}}};
                                quadruples.push_back(temp2);
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i<temp->adj.size();i++)
        {
            q.push(temp->adj[i]);
        }
    }
}

int main()
{
	unordered_map<string, string[50]> follows;
	unordered_map<string, int> indexer;
	unordered_map<string, string[50]> table;
	stack<string> st;
	int c=0,inc=0,inc2=0,inc3=0;
	int checker=0;
	string terms[41] = {"#", "include", "<", ">", "stdio.h", "math.h", "bits/stdc++.h", "id", "(", ")", "{", "return", ";", "}", ",", "[", "]", "num", "int", "float", "char", "boolean", "string", "=", "+", "-", "*", "/", "%", "true", "false", "&&", "||", "?", "!", "!=", "if", "else", "while", "for", "$"};
	string inp[1000];
	vector<string> productions;
	string ids[1000];
	string nums[1000];
	ofstream output("parser_output1.txt");
	ifstream input("output1.txt");
	struct node* newnode[1000];
	int k=0;


	follow_init(follows);
	indexer_init(c,indexer,terms);
	table_init(table,indexer);
	string s;
	string s1;
	int ch=0;
	int id1=0,num1=0;
    struct node* root;
    root=create("program",indexer);
	while(getline(input,s))
	{
		s1.clear();
		id1=0;
		num1=0;
		for(int i=0;i<s.length();i++)
		{
			if(s[i]==' ')
			{
				if(s1=="string:")
				{
					ch=1;
				}
				else if(s1=="Identifier,")
				{
					id1=1;
				}
				else if(s1=="Integer" || s1=="Floating")
				{
					num1=1;
				}
				else
				{
					if(ch==1)
					{
						if(id1==1 || s1=="main")
						{
							ids[inc2]=s1;
							inc2++;
						}
						if(num1==1)
						{
							nums[inc3]=s1;
							inc3++;
						}
						if(id1==1 || s1=="main")
						{
							inp[inc]="id";
						}
						else if(num1==1)
						{
							inp[inc]="num";
						}
						else
						{
							inp[inc]=s1;
						}
						inc++;
						ch=0;
					}
				}
				s1.clear();
			}
			else
			{
				if(ch!=1 || s[i]!=',' || s[i+1]!=' ')
				{
					s1+=s[i];
				}
			}
		}
	}
	inp[inc]="$";
	inc++;
	stack<string> st1;
	string add;
	string prod;
	string adders[1000];
	int inc1=0,search=0,curr=0;
	parse(0,root,st,st1,inc,inp,indexer,table,productions,checker,follows,add,prod,adders,inc1,search,curr);
	if(checker==0)
	{
		string nxt="";
		int ct=0;
		parsetree(root,newnode,indexer,productions,ids,nums,nxt,ct);
		/*queue<struct node*>q;
		levelorder(root,q);*/
	}
	sdt(root);
	cout<<quadruples.size()<<"\n";
	for(int i=0;i<quadruples.size();i++)
    {
        pair<string,pair<string,pair<string,string>>>temp=quadruples[i];
        cout<<temp.first<<" "<<temp.second.first<<" "<<temp.second.second.first<<" "<<temp.second.second.second<<"\n";
    }
	return 0;
}
