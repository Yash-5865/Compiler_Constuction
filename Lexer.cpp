#include<bits/stdc++.h>
using namespace std;

//Keyword vector
vector<string> keywords={"int", "char", "float", "boolean", "string", "void", "include", "while", "until", "if", "else", "true", "false", "for", "do", "and", "or", "continue", "break", "cin", "cout", "double", "vector", "return", "endl", "main", "bool", "namespace", "define"};
unordered_map<string,int>tokenno,identifiers;
int id1=14,id=0;

//Keyword checking
int keyword(string s)
{
    int check=0;
    int i=0;
    while(s[i]==' ' || s[i]=='\t')
    {
        i++;
    }
    string s1=s.substr(i);
    for(int i=0;i<keywords.size();i++)
    {
        if(!strcmp(s1.c_str(),keywords[i].c_str()))
        {
            check=1;
            break;
        }
    }
    return check;
}

// Operator or delimiter check for line break
int operator_or_delimiter(char s)
{
    if(s=='+' || s=='-' || s==':' || s==';' || s=='*' || s=='/' || s=='%' || s=='&' || s=='|' || s=='?' || s=='!' || s=='(' || s==')' || s=='[' || s==']' || s=='{' || s=='}' || s=='=' || s==',' || s=='<' || s=='>' || s==' ' || s=='#' || s=='^')
    {
        return 1;
    }
    return 0;
}

int main()
{

    // Assigning id to all keywords
    for(int i=0;i<keywords.size();i++)
    {
        id1++;
        string t=keywords[i];
        tokenno[t]=id1;
    }

    int lineno=0,multiline=0,temp=0;
    string s;


    // File streams
    ifstream input("test1.txt");
    ofstream output("output1.txt");


    //Reading input line by line
    while(getline(input,s))
    {
        int quotes=0,backslashcount=0,definer=0;
        //cout<<s[s.length()-1]<<"-printed";
        lineno++;

        //bracket sequence checker (only single line bracket sequence checked)
        stack<char>bracket;
        int start=0;

        //Removing initial white spaces
        while(s[start]==' ' || s[start]=='\t')
        {
            start++;
        }
        s=s.substr(start);

        //Handling single line comments
        if(s[0]=='/' && s[1]=='/')
        {
            continue;
        }

        //Handling multi-line comments
        if(s[0]=='/' && s[1]=='*')
        {
            multiline=1;
        }
        //if(s[s.length()-1]=='/' && s[s.length()-2]=='*')
        //{
            //multiline=0;
            //continue;
        //}
        //if(multiline==1)
        //{
            //continue;
        //}
        string line;
        string prev_token="";
        int p=1;

        //Char by char treversal

        for(int i=0;i<s.length();i++)
        {
            //Skip line if it is a comment

            if(multiline==1)
            {
                if(s[i]=='*' && s[i+1]=='/')
                {
                    multiline=0;
                    i++;
                    continue;
                }
                else
                {
                    continue;
                }
            }
            if(quotes==0)
            {
                //Quotes pairing checked

                if(s[i]=='\"')
                {
                    quotes=1;
                }
                //Line break if current char is operator or delimiter
                //Classify the string stored in line variable as a literal of keyword

                if(operator_or_delimiter(s[i])==1 && (id!=12 || s[i]=='>'))
                {
                    //cout<<line<<" "<<s[i]<<endl;
                    int state=0,breaker=1;
                    //prev_token=line;

                    //Keyword check
                    if(keyword(line)==1)
                    {
                        if(line=="include")
                        {
                            //Header file check
                            output<<"Token "<<temp<<" Preprocessing directive"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                            cout<<"Token "<<temp<<" Preprocessing directive"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                            prev_token=line;
                        }
                        else if(line=="define")
                        {
                            definer=1;
                            output<<"Token "<<temp<<" Preprocessing directive"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                            cout<<"Token "<<temp<<" Preprocessing directive"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                            prev_token=line;
                        }
                        else
                        {
                            //Matching current string with keyword vector
                            temp=0;
                            if(tokenno.find(line)!=tokenno.end())
                            {
                                temp=tokenno[line];
                            }
                            else
                            {
                                id1++;
                                temp=id1;
                                tokenno[line]=id1;
                            }
                            output<<"Token "<<temp<<" Keyword"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                            cout<<"Token "<<temp<<" Keyword"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                            prev_token=line;
                        }
                    }
                    else
                    {
                        //cout<<line<<"first"<<endl;

                        //Extra white space removed
                        int j=0;
                        while(line[j]==' ' || line[j]=='\t')
                        {
                            j++;
                        }
                        line=line.substr(j);
                        //cout<<line.size()<<endl;
                        //cout<<line<<"second"<<endl;
                        //cout<<"prev token:"<<prev_token<<endl;
                        if(line.size()>0)
                        {
                            //Integer literal check
                            breaker=1;
                            if(line[0]>='0' && line[0]<='9')
                            {
                                state=22;
                                int flo=0;
                                if(line[0]=='0')
                                {
                                    //Number starts with 0
                                    if(line.length()==1)
                                    {
                                        //The number is 0
                                        temp=0;
                                        state=-1;
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            temp=tokenno[line];
                                        }
                                        else
                                        {
                                            id=2;
                                            temp=id;
                                            tokenno[line]=id;
                                        }
                                        output<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    }
                                    else if(line[1]=='.')
                                    {
                                        //Floating point
                                        state=24;
                                    }
                                    else
                                    {
                                        //Number starts with 0 and is not equal to 0, Invalid
                                        state=-1;
                                        //p=0;
                                        output<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                        cout<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                        break;
                                    }
                                }
                                else
                                {
                                    //Integer/Float dfa
                                    int j=1;
                                    while(breaker==1 && j<line.length())
                                    {
                                        switch(state)
                                        {
                                            case 22:
                                                if(line[j]>='0' && line[j]<='9')
                                                {
                                                    j++;
                                                    state=22;
                                                    break;
                                                }
                                                else if(line[j]=='.')
                                                {
                                                    //Floating point
                                                    j++;
                                                    flo=1;
                                                    state=24;
                                                    break;
                                                }
                                                else
                                                {
                                                    //Invalid character encountered


                                                    //p=0;
                                                    //while(s[i]!=' ' && s[i]!='\t' && s[i]!=';' && s[i]!='(' && s[i]!=',' && s[i]!=')' && s[i]!='[' && s[i]!=']' && s[i]!='{' && s[i]!='}' && s[i]!='<' && s[i]!='>' && s[i]!='=' && s[i]!='+' && s[i]!='-' && s[i]!='*' && s[i]!='/' && s[i]!='|' && s[i]!='&' && s[i]!='^' && s[i]!='%')
                                                    //{
                                                        //line+=s[i];
                                                        //i++;
                                                    //}
                                                    //i--;
                                                    state=-1;
                                                    output<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                                    cout<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                                    break;
                                                }
                                            case 24:
                                                //Floating point dfa
                                                if(line[j]>='0' && line[j]<='9')
                                                {
                                                    j++;
                                                    state=24;
                                                    break;
                                                }
                                                else
                                                {
                                                    //Invalid character encountered


                                                    //p=0;
                                                    //while(s[i]!=' ' && s[i]!='\t' && s[i]!=';' && s[i]!='(' && s[i]!=',' && s[i]!=')' && s[i]!='[' && s[i]!=']' && s[i]!='{' && s[i]!='}' && s[i]!='<' && s[i]!='>' && s[i]!='=' && s[i]!='+' && s[i]!='-' && s[i]!='*' && s[i]!='/' && s[i]!='|' && s[i]!='&' && s[i]!='^' && s[i]!='%')
                                                    //{
                                                        //line+=s[i];
                                                        //i++;
                                                    //}
                                                    //i--;
                                                    state=-1;
                                                    output<<"Error at line number: "<<lineno<<". Invalid floating point representation\n";
                                                    cout<<"Error at line number: "<<lineno<<". Invalid floating point representation\n";
                                                    break;
                                                }
                                            default:
                                                breaker=0;
                                                break;
                                        }
                                    }
                                    //loop exit condition

                                    if(breaker==1)
                                    {
                                        //Floating point check

                                        if(flo==0)
                                        {
                                            temp=0;
                                            if(tokenno.find(line)!=tokenno.end())
                                            {
                                                temp=tokenno[line];
                                            }
                                            else
                                            {
                                                id=2;
                                                temp=id;
                                                tokenno[line]=id;
                                            }
                                            output<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            cout<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        }
                                        else
                                        {
                                            temp=0;
                                            if(tokenno.find(line)!=tokenno.end())
                                            {
                                                temp=tokenno[line];
                                            }
                                            else
                                            {
                                                id=2;
                                                temp=id;
                                                tokenno[line]=id;
                                            }
                                            output<<"Token "<<temp<<" Floating Point literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            cout<<"Token "<<temp<<" Floating Point literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        }
                                    }
                                }
                            }
                            else if(line[0]=='\"')
                            {
                                //String literal check, always starts with a double quote

                                state=25;
                                breaker=1;
                                int invalid=0;
                                int startindex=1;
                                //cout<<"line"<<line;

                                //String literal dfa
                                while(breaker==1 && startindex<line.length())
                                {
                                    switch(state)
                                    {
                                        case 25:
                                            //Special backslash cases handled

                                            if(line[startindex]=='\\')
                                            {
                                                state=26;
                                                break;
                                            }
                                            else if(line[startindex]=='\"')
                                            {
                                                //Closing double quotes
                                                if(startindex==line.length()-1)
                                                {
                                                    //If we find closing quotes at the end of the line
                                                    startindex++;
                                                    break;
                                                }
                                                else
                                                {
                                                    //If we find closing quotes before the end of the line

                                                    invalid=1;
                                                    //p=0;
                                                    state=-1;
                                                    output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                    cout<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                startindex++;
                                                state=25;
                                                break;
                                            }
                                        case 26:
                                            if(startindex==line.length()-1)
                                            {
                                                //We reach the end of line and don't find closing quotes
                                                invalid=1;
                                                //p=0;
                                                state=-1;
                                                output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                cout<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                break;
                                            }
                                            else if(line[startindex+1]=='\"')
                                            {
                                                //Closing quotes checking
                                                if(startindex==line.length()-2)
                                                {
                                                    invalid=1;
                                                    //p=0;
                                                    state=-1;
                                                    output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                    cout<<"Error at line number: "<<lineno<<". Invalid string representation\nline:"<<line<<" "<<startindex<<endl;
                                                    break;
                                                }
                                                else
                                                {
                                                    startindex+=2;
                                                    state=25;
                                                    break;
                                                }
                                            }
                                            else if(line[startindex+1]=='n' || line[startindex+1]=='t' || line[startindex+1]=='r' || line[startindex+1]=='\\')
                                            {
                                                //Checking for characters following a backslash
                                                //Only the above mentioned characters are allowed
                                                startindex+=2;
                                                state=25;
                                                break;
                                            }
                                            else
                                            {
                                                invalid=1;
                                                //p=0;
                                                state=-1;
                                                output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                cout<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                break;
                                            }
                                        default:
                                            breaker=0;
                                            break;
                                    }
                                }
                                if(invalid==0)
                                {
                                    //If the string is valid
                                    if(line[line.length()-1]=='\"')
                                    {
                                        //Ends with a quote
                                        temp=0;
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            temp=tokenno[line];
                                        }
                                        else
                                        {
                                            id=2;
                                            temp=id;
                                            tokenno[line]=id;
                                        }
                                        output<<"Token "<<temp<<" String literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" String literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    }
                                    else
                                    {
                                        //No quote found

                                        //p=0;
                                        output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                        cout<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                    }
                                }
                            }
                            else if((line[0]>='a' && line[0]<='z') || (line[0]>='A' && line[0]<='Z'))
                            {
                                //Character checking

                                int starter=1;
                                state=27;
                                breaker=1;
                                int invalider=0;
                                while(breaker==1 && starter<line.length())
                                {
                                    switch(state)
                                    {
                                        case 27:
                                            if((line[starter]>='a' && line[starter]<='z') || (line[starter]>='A' && line[starter]<='Z') || (line[starter]>='0' && line[starter]<='9') || line[starter]=='_')
                                            {
                                                starter++;
                                                state=27;
                                                break;
                                            }
                                            else
                                            {
                                                //If we find any invalid character
                                                if(id==12)
                                                {
                                                    //If we find "." and id==12 suggests that this is an #include statement
                                                    starter++;
                                                    state=27;
                                                    break;
                                                }
                                                invalider=1;
                                                //p=0;
                                                state=-1;
                                                output<<"Error at line number: "<<lineno<<". Invalid identifier representation\n";
                                                cout<<"Error at line number: "<<lineno<<". Invalid identifier representation\n"<<id<<endl;
                                                break;
                                            }
                                        default:
                                            breaker=0;
                                            break;
                                    }
                                }
                                if(invalider==0)
                                {
                                    if(prev_token=="int" || prev_token=="float" || prev_token=="char" || prev_token=="string" || prev_token=="boolean" || prev_token=="double" || prev_token=="bool")
                                    {
                                        //Variable declaration checked

                                        //cout<<"YES"<<endl;
                                        temp=0;
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            id=1;
                                            temp=tokenno[line];
                                            output<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            cout<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        }
                                        else
                                        {
                                            //New variable without proper type declared
                                            identifiers[line]=1;
                                            id=1;
                                            temp=id;
                                            tokenno[line]=id;
                                            output<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            cout<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        }
                                    }
                                    else
                                    {
                                        if(prev_token=="void")
                                        {
                                            // void function found

                                            if(s[i]=='(')
                                            {
                                                identifiers[line]=1;
                                                id=1;
                                                temp=id;
                                                tokenno[line]=id;
                                                output<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                                cout<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            }
                                            else
                                            {
                                                //p=0;
                                                output<<"Error at line number: "<<lineno<<". Invalid variable initialization\n";
                                                cout<<"Error at line number: "<<lineno<<". Invalid variable initialization\n";
                                            }
                                        }
                                        else
                                        {
                                            if(id==12)
                                            {
                                                //Header file name check
                                                id=11;
                                                temp=id;
                                                tokenno[line]=id;
                                                output<<"Token "<<temp<<" Library Name"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                                cout<<"Token "<<temp<<" Library Name"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            }
                                            else
                                            {
                                                //checking if current identifier was encountered before

                                                if(identifiers.find(line)!=identifiers.end())
                                                {
                                                    temp=0;
                                                    if(tokenno.find(line)!=tokenno.end())
                                                    {
                                                        temp=tokenno[line];
                                                    }
                                                    else
                                                    {
                                                        id=1;
                                                        temp=id;
                                                        tokenno[line]=id;
                                                    }
                                                    output<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                                    cout<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                                }
                                                else
                                                {
                                                    //p=0;
                                                    //cout<<"temp and id:"<<temp<<" "<<id<<" ";
                                                    if(prev_token=="define")
                                                    {
                                                        identifiers[line]=1;
                                                        id=1;
                                                        temp=id;
                                                        tokenno[line]=id;
                                                        output<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                                        cout<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                                    }
                                                    else
                                                    {
                                                        output<<"Error at line number: "<<lineno<<". Undefined identifier\nToken string: "<<line<<endl;
                                                        cout<<"Error at line number: "<<lineno<<". Undefined identifier\nToken string: "<<line<<endl;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                //p=0;
                                output<<"Error at line number: "<<lineno<<". Invalid start character for token\n";
                                cout<<"Error at line number: "<<lineno<<". Invalid start character for token\n";
                            }
                            prev_token=line;
                        }
                    }
                    //prev_token=line;

                    line="";
                    if(s[i]==' ' || s[i]=='\t')
                    {
                        continue;
                    }
                    line+=s[i];

                    //cout<<line<<" "<<s[i]<<endl;
                    //cout<<"prev_token: "<<prev_token<<endl;

                    //Operator/delimiter dfa

                    state=0;
                    breaker=1;
                    while(breaker==1)
                    {
                        switch(state)
                        {
                            case 0:
                                //cout<<i<<" "<<s[i]<<" "<<s[i+1]<<endl;

                                if(s[i]=='%' || s[i]=='*' || s[i]=='/')
                                {
                                    // mod,multiply,divide
                                    state=1;
                                    break;
                                }
                                else if(s[i]=='+')
                                {
                                    // +,+=,++
                                    state=2;
                                    break;
                                }
                                else if(s[i]=='-')
                                {
                                    //-,-=,--
                                    state=4;
                                    break;
                                }
                                else if(s[i]=='=')
                                {
                                    //=,==
                                    state=7;
                                    break;
                                }
                                else if(s[i]=='#')
                                {
                                    //# include
                                    state=8;
                                    break;
                                }
                                else if(s[i]=='!')
                                {
                                    // bitwise not, not equals
                                    state=9;
                                    break;
                                }
                                else if(s[i]=='&')
                                {
                                    //bitwise and, &&
                                    state=10;
                                    break;
                                }
                                else if(s[i]=='|')
                                {
                                    //bitwise or,||
                                    state=12;
                                    break;
                                }
                                else if(s[i]=='^')
                                {
                                    //bitwise xor
                                    state=14;
                                    break;
                                }
                                else if(s[i]=='>')
                                {
                                    //>,>=,>>
                                    state=15;
                                    break;
                                }
                                else if(s[i]=='<')
                                {
                                    //<,<=,<<
                                    state=17;
                                    break;
                                }
                                /*else if(s[i]=='?')
                                {
                                    state=19;
                                    break;
                                }*/
                                else
                                {
                                    //brackets
                                    state=20;
                                    break;
                                }
                            case 1:
                                if(s[i]=='/' && s[i+1]=='/')
                                {
                                    // double backslash  = single line comment

                                    state=-1;
                                    p=0;
                                    i++;
                                    break;
                                }
                                else if(s[i]=='/' && s[i+1]=='*')
                                {
                                    // /* = multi line comment start

                                    state=-1;
                                    //p=0;
                                    i++;
                                    multiline=1;
                                    break;
                                }
                                else
                                {
                                    // /= or *=

                                    if(s[i+1]=='=')
                                    {
                                        state=6;
                                        line+=s[i+1];
                                        break;
                                    }
                                    else
                                    {
                                        temp=0;
                                        state=-1;
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            temp=tokenno[line];
                                        }
                                        else
                                        {
                                            id=3;
                                            temp=id;
                                            tokenno[line]=id;
                                        }
                                        output<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        prev_token=line;
                                        break;
                                    }
                                }
                            case 2:
                                if(s[i+1]=='+')
                                {
                                    // ++
                                    state=3;
                                    line+=s[i+1];
                                    break;
                                }
                                else if(s[i+1]=='=')
                                {
                                    // +=
                                    state=6;
                                    line+=s[i+1];
                                    break;
                                }
                                else if(temp==5 || prev_token=="+=" || prev_token=="-=" || prev_token=="*=" || prev_token=="==" || prev_token=="/=" || prev_token=="<=" || prev_token=="!=" || prev_token==">=" || prev_token=="%=" || prev_token=="(" || prev_token=="[")
                                {
                                    // + denotes sign of the integer or float number

                                    if(s[i+1]=='0')
                                    {
                                        if(i+1>=s.length()-3)
                                        {
                                            state=-1;
                                            //p=0;
                                            output<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                            cout<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                            break;
                                        }
                                        else if(s[i+2]=='.')
                                        {
                                            line+=s[i+1];
                                            line+=s[i+2];
                                            i+=3;
                                            state=24;
                                            break;
                                        }
                                        else
                                        {
                                            output<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                            cout<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                            state=-1;
                                            //p=0;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        if(s[i+1]>='1' && s[i+1]<='9')
                                        {
                                            i++;
                                            state=22;
                                            break;
                                        }
                                        else
                                        {
                                            temp=0;
                                            state=-1;
                                            if(tokenno.find(line)!=tokenno.end())
                                            {
                                                temp=tokenno[line];
                                            }
                                            else
                                            {
                                                id=3;
                                                temp=id;
                                                tokenno[line]=id;
                                            }
                                            output<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            cout<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            prev_token=line;
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    temp=0;
                                    state=-1;
                                    if(tokenno.find(line)!=tokenno.end())
                                    {
                                        temp=tokenno[line];
                                    }
                                    else
                                    {
                                        id=3;
                                        temp=id;
                                        tokenno[line]=id;
                                    }
                                    output<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    cout<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    prev_token=line;
                                    break;
                                }
                            case 3:
                                temp=0;
                                state=-1;
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=9;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" Incremental operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" Incremental operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                i++;
                                break;
                            case 4:
                                //cout<<"id: "<<id<<" temp: "<<temp<<endl;

                                if(s[i+1]=='-')
                                {
                                    // --
                                    state=5;
                                    line+=s[i+1];
                                    break;
                                }
                                else if(s[i+1]=='=')
                                {
                                    // -=
                                    state=6;
                                    line+=s[i+1];
                                    break;
                                }
                                else if(temp==5 || prev_token=="+=" || prev_token=="-=" || prev_token=="*=" || prev_token=="==" || prev_token=="/=" || prev_token=="<=" || prev_token=="!=" || prev_token==">=" || prev_token=="%=" || prev_token=="(" || prev_token=="[")
                                {
                                    // - denotes the sign of the integer or float number
                                    if(s[i+1]=='0')
                                    {
                                        //number starting with 0
                                        // number is 0 or 0.
                                        // number is not 0 or 0. , error
                                        if(i+1>=s.length()-3)
                                        {
                                            state=-1;
                                            //p=0;

                                            output<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                            cout<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                            break;
                                        }
                                        else if(s[i+2]=='.')
                                        {
                                            line+=s[i+1];
                                            line+=s[i+2];
                                            i+=3;
                                            state=24;
                                            break;
                                        }
                                        else
                                        {
                                            output<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                            cout<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                            state=-1;
                                            //p=0;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        if(s[i+1]>='1' && s[i+1]<='9')
                                        {
                                            i++;
                                            state=22;
                                            break;
                                        }
                                        else
                                        {
                                            temp=0;
                                            state=-1;
                                            if(tokenno.find(line)!=tokenno.end())
                                            {
                                                temp=tokenno[line];
                                            }
                                            else
                                            {
                                                id=3;
                                                temp=id;
                                                tokenno[line]=id;
                                            }
                                            output<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            cout<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            prev_token=line;
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    temp=0;
                                    state=-1;
                                    if(tokenno.find(line)!=tokenno.end())
                                    {
                                        temp=tokenno[line];
                                    }
                                    else
                                    {
                                        id=3;
                                        temp=id;
                                        tokenno[line]=id;
                                    }
                                    output<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    cout<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n"<<prev_token<<endl;
                                    prev_token=line;
                                    break;
                                }
                            case 5:
                                temp=0;
                                state=-1;
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=9;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" Decremental operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" Decremental operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                i++;
                                break;
                            case 6:
                                temp=0;
                                state=-1;
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=3;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" Arithmetic operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                i++;
                                break;
                            case 7:
                                if(s[i+1]=='=')
                                {
                                    // ==
                                    state=21;
                                    line+=s[i+1];
                                    break;
                                }
                                else
                                {
                                    temp=0;
                                    state=-1;
                                    if(tokenno.find(line)!=tokenno.end())
                                    {
                                        temp=tokenno[line];
                                    }
                                    else
                                    {
                                        id=5;
                                        temp=id;
                                        tokenno[line]=id;
                                    }
                                    output<<"Token "<<temp<<" Relational operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    cout<<"Token "<<temp<<" Relational operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    prev_token=line;
                                    break;
                                }
                            case 8:
                                // # include operator
                                temp=0;
                                state=-1;
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=10;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" Preprocessing directive opener"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" Preprocessing directive opener"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                break;
                            case 9:
                                if(s[i+1]=='=')
                                {
                                    // !=
                                    state=21;
                                    line+=s[i+1];
                                    break;
                                }
                                else
                                {
                                    temp=0;
                                    state=-1;
                                    if(tokenno.find(line)!=tokenno.end())
                                    {
                                        temp=tokenno[line];
                                    }
                                    else
                                    {
                                        id=6;
                                        temp=id;
                                        tokenno[line]=id;
                                    }
                                    output<<"Token "<<temp<<" Bitwise operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    cout<<"Token "<<temp<<" Bitwise operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    prev_token=line;
                                    break;
                                }
                            case 10:
                                if(s[i+1]=='&')
                                {
                                    //&&
                                    state=11;
                                    line+=s[i+1];
                                    break;
                                }
                                else
                                {
                                    temp=0;
                                    state=-1;
                                    if(tokenno.find(line)!=tokenno.end())
                                    {
                                        temp=tokenno[line];
                                    }
                                    else
                                    {
                                        id=6;
                                        temp=id;
                                        tokenno[line]=id;
                                    }
                                    output<<"Token "<<temp<<" Bitwise operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    cout<<"Token "<<temp<<" Bitwise operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    prev_token=line;
                                    break;
                                }
                            case 11:
                                temp=0;
                                state=-1;
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=4;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" Logical operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" Logical operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                i++;
                                break;
                            case 12:
                                if(s[i+1]=='|')
                                {
                                    // ||
                                    state=13;
                                    line+=s[i+1];
                                    break;
                                }
                                else
                                {
                                    int temp=0;
                                    state=-1;
                                    if(tokenno.find(line)!=tokenno.end())
                                    {
                                        temp=tokenno[line];
                                    }
                                    else
                                    {
                                        id=6;
                                        temp=id;
                                        tokenno[line]=id;
                                    }
                                    output<<"Token "<<temp<<" Bitwise operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    cout<<"Token "<<temp<<" Bitwise operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    prev_token=line;
                                    break;
                                }
                            case 13:
                                temp=0;
                                state=-1;
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=4;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" Logical operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" Logical operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                i++;
                                break;
                            case 14:
                                temp=0;
                                state=-1;
                                //xor
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=4;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" Logical operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" Logical operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                break;
                            case 15:
                                if(s[i+1]=='>')
                                {
                                    // >>
                                    state=16;
                                    line+=s[i+1];
                                    break;
                                }
                                else if(s[i+1]=='=')
                                {
                                    // >=
                                    state=21;
                                    line+=s[i+1];
                                    break;
                                }
                                else
                                {
                                    // > as closing bracket for #include statements
                                    temp=0;
                                    state=-1;
                                    if(id==11)
                                    {
                                        id=13;
                                        temp=id;
                                        tokenno[line]=id;
                                        output<<"Token "<<temp<<" include closer"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" include closer"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        prev_token=line;
                                        break;
                                    }
                                    else
                                    {
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            temp=tokenno[line];
                                        }
                                        else
                                        {
                                            id=5;
                                            temp=id;
                                            tokenno[line]=id;
                                        }
                                        output<<"Token "<<temp<<" Relational operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Relational operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        prev_token=line;
                                        break;
                                    }
                                }
                            case 16:
                                temp=0;
                                state=-1;
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=7;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" cin operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" cin operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                i++;
                                break;
                            case 17:
                                //i++;
                                //cout<<i<<" "<<endl;
                                if(s[i+1]=='<')
                                {
                                    //<<
                                    state=18;
                                    line+=s[i+1];
                                    break;
                                }
                                else if(s[i+1]=='=')
                                {
                                    //<=
                                    state=21;
                                    line+=s[i+1];
                                    break;
                                }
                                else
                                {
                                    temp=0;
                                    state=-1;
                                    // > as opening bracket for #include statements
                                    if(prev_token=="include")
                                    {
                                        id=12;
                                        temp=id;
                                        tokenno[line]=id;
                                        output<<"Token "<<temp<<" include opener"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" include opener"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        prev_token=line;
                                        break;
                                    }
                                    else
                                    {
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            temp=tokenno[line];
                                        }
                                        else
                                        {
                                            id=5;
                                            temp=id;
                                            tokenno[line]=id;
                                        }
                                        output<<"Token "<<temp<<" Relational operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Relational operator"<<", string: "<<line<<", line number: "<<lineno<<"\n"<<prev_token<<endl;
                                        prev_token=line;
                                        break;
                                    }
                                }
                            case 18:
                                temp=0;
                                state=-1;
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=8;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" cout operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" cout operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                i++;
                                break;
                            case 20:
                                temp=0;
                                state=-1;

                                //brackets
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=14;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" Delimiter"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" Delimiter"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                if(line=="(" || line=="[")
                                {
                                    //checking if bracket sequence is correct
                                    // only for single line brackets
                                    bracket.push(line[0]);
                                }
                                else if(line==")")
                                {
                                    if(bracket.top()!='(')
                                    {
                                        output<<"Error at line number: "<<lineno<<". Invalid bracket sequence\n";
                                        cout<<"Error at line number: "<<lineno<<". Invalid bracket sequence\n";
                                        //p=0;
                                        state=-1;
                                        break;
                                    }
                                    else
                                    {
                                        bracket.pop();
                                    }
                                }
                                else if(line=="]")
                                {
                                    if(bracket.top()!='[')
                                    {
                                        output<<"Error at line number: "<<lineno<<". Invalid bracket sequence\n";
                                        cout<<"Error at line number: "<<lineno<<". Invalid bracket sequence\n";
                                        //p=0;
                                        state=-1;
                                        break;
                                    }
                                    else
                                    {
                                        bracket.pop();
                                    }
                                }
                                break;
                            case 21:
                                temp=0;
                                state=-1;
                                if(tokenno.find(line)!=tokenno.end())
                                {
                                    temp=tokenno[line];
                                }
                                else
                                {
                                    id=5;
                                    temp=id;
                                    tokenno[line]=id;
                                }
                                output<<"Token "<<temp<<" Relational operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                cout<<"Token "<<temp<<" Relational operator"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                prev_token=line;
                                i++;
                                break;
                            case 22:
                                while(s[i]==' ' || s[i]=='\t')
                                {
                                    i++;
                                }
                                //Integer check
                                if(s[i]>='0' && s[i]<='9')
                                {
                                    line+=s[i];
                                    i++;
                                    state=22;
                                    break;
                                }
                                else if(s[i]=='.')
                                {
                                    line+=s[i];
                                    i++;
                                    //Float
                                    state=24;
                                    break;
                                }
                                else
                                {
                                    while(s[i]==' ' || s[i]=='\t')
                                    {
                                        i++;
                                    }
                                    if(s[i]==';' || s[i]==')' || s[i]==',')
                                    {
                                        temp=0;
                                        state=-1;
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            temp=tokenno[line];
                                        }
                                        else
                                        {
                                            id=2;
                                            temp=id;
                                            tokenno[line]=id;
                                        }
                                        output<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        prev_token=line;
                                        break;
                                    }
                                    else
                                    {
                                        //p=0;
                                        state=-1;
                                        while(s[i]!=' ' && s[i]!='\t' && s[i]!=';' && s[i]!='(' && s[i]!=',' && s[i]!=')' && s[i]!='[' && s[i]!=']' && s[i]!='{' && s[i]!='}' && s[i]!='<' && s[i]!='>' && s[i]!='=' && s[i]!='+' && s[i]!='-' && s[i]!='*' && s[i]!='/' && s[i]!='|' && s[i]!='&' && s[i]!='^' && s[i]!='%')
                                        {
                                            line+=s[i];
                                            i++;
                                        }
                                        i--;
                                        output<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                        cout<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                        break;
                                    }
                            case 24:
                                //Floating point

                                if(s[i]>='0' && s[i]<='9')
                                {
                                    line+=s[i];
                                    i++;
                                    state=24;
                                    break;
                                }
                                else
                                {
                                    while(s[i]==' ' || s[i]=='\t')
                                    {
                                        i++;
                                    }
                                    if(s[i]==';' || s[i]==')')
                                    {
                                        temp=0;
                                        state=-1;
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            temp=tokenno[line];
                                        }
                                        else
                                        {
                                            id=2;
                                            temp=id;
                                            tokenno[line]=id;
                                        }
                                        output<<"Token "<<temp<<" Floating Point literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Floating Point literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        prev_token=line;
                                        break;
                                    }
                                    else
                                    {
                                        //p=0;
                                        while(s[i]!=' ' && s[i]!='\t' && s[i]!=';' && s[i]!='(' && s[i]!=',' && s[i]!=')' && s[i]!='[' && s[i]!=']' && s[i]!='{' && s[i]!='}' && s[i]!='<' && s[i]!='>' && s[i]!='=' && s[i]!='+' && s[i]!='-' && s[i]!='*' && s[i]!='/' && s[i]!='|' && s[i]!='&' && s[i]!='^' && s[i]!='%')
                                        {
                                            line+=s[i];
                                            i++;
                                        }
                                        i--;
                                        state=-1;
                                        output<<"Error at line number: "<<lineno<<". Invalid floating point representation\n";
                                        cout<<"Error at line number: "<<lineno<<". Invalid floating point representation\n";
                                        break;
                                    }
                                }
                            default:
                                breaker=0;
                                break;
                            }
                        }
                    }
                    line="";
                    if(p==0)
                    {
                        break;
                    }
                }
                else
                {
                    // add the current character to string of read character yet to be classified.
                    // classify when we encounter an operator or delimiter or end of line
                    line+=s[i];
                }
            }
            else
            {
                if(s[i]=='\"')
                {
                    // special case for "\"" in a string
                    // \" preceded by even backslashes is correct, else error
                    if(s[i-1]=='\\')
                    {
                        if(backslashcount%2==0 && backslashcount>0)
                        {
                            quotes=0;
                        }
                    }
                    else
                    {
                        quotes=0;
                    }
                }
                if(s[i]=='\\' && s[i-1]=='\\')
                {
                    if(backslashcount==0)
                    {
                        backslashcount+=2;
                    }
                    else
                    {
                        backslashcount+=1;
                    }
                }
                else if(s[i]=='\\')
                {
                    backslashcount++;
                }
                else
                {
                    backslashcount=0;
                }
                line+=s[i];
            }
        }
        if(quotes==1)
        {
            output<<"Error at line number: "<<lineno<<". String does not terminate\n";
            cout<<"Error at line number: "<<lineno<<". String does not terminate\n";
        }
        if(bracket.size()!=0)
        {
            output<<"Error at line number: "<<lineno<<". Invalid bracket sequence\n";
            cout<<"Error at line number: "<<lineno<<". Invalid bracket sequence\n";
        }
        if(line.length()>0)
        {
            if(keyword(line)==1)
            {
                temp=0;
                if(tokenno.find(line)!=tokenno.end())
                {
                    temp=tokenno[line];
                }
                else
                {
                    id1++;
                    temp=id1;
                    tokenno[line]=id1;
                }
                output<<"Token "<<temp<<" Keyword"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                cout<<"Token "<<temp<<" Keyword"<<", string: "<<line<<", line number: "<<lineno<<"\n";
            }
            else
            {
                // If the line ends without any delimiter
                // classify the line variable using the same dfa for integer/float/string/identifier
                int state=0,breaker=1;
                //prev_token=line;
                if(keyword(line)==1)
                {
                    temp=0;
                    if(tokenno.find(line)!=tokenno.end())
                    {
                        temp=tokenno[line];
                    }
                    else
                    {
                        id1++;
                        temp=id1;
                        tokenno[line]=id1;
                    }
                    output<<"Token "<<temp<<" Keyword"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                    cout<<"Token "<<temp<<" Keyword"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                    prev_token=line;
                }
                else
                {
                    //cout<<line<<"first"<<endl;
                    int j=0;
                    while(line[j]==' ' || line[j]=='\t')
                    {
                        j++;
                    }
                    line=line.substr(j);
                    //cout<<line.size()<<endl;
                    //cout<<line<<"second"<<endl;
                    //cout<<"prev token:"<<prev_token<<endl;
                    if(line.size()>0)
                    {
                        breaker=1;
                        if(line[0]>='0' && line[0]<='9')
                        {
                            state=22;
                            int flo=0;
                            if(line[0]=='0')
                            {
                                if(line.length()==1)
                                {
                                    temp=0;
                                    state=-1;
                                    if(tokenno.find(line)!=tokenno.end())
                                    {
                                        temp=tokenno[line];
                                    }
                                    else
                                    {
                                        id=2;
                                        temp=id;
                                        tokenno[line]=id;
                                    }
                                    output<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    cout<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                }
                                else if(line[1]=='.')
                                {
                                    state=24;
                                }
                                else
                                {
                                    state=-1;
                                    //p=0;
                                    output<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                    cout<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                    break;
                                }
                            }
                            else
                            {
                                int j=1;
                                while(breaker==1 && j<line.length())
                                {
                                    switch(state)
                                    {
                                        case 22:
                                            if(line[j]>='0' && line[j]<='9')
                                            {
                                                j++;
                                                state=22;
                                                break;
                                            }
                                            else if(line[j]=='.')
                                            {
                                                j++;
                                                flo=1;
                                                state=24;
                                                break;
                                            }
                                            else
                                            {
                                                //p=0;
                                                //while(s[i]!=' ' && s[i]!='\t' && s[i]!=';' && s[i]!='(' && s[i]!=',' && s[i]!=')' && s[i]!='[' && s[i]!=']' && s[i]!='{' && s[i]!='}' && s[i]!='<' && s[i]!='>' && s[i]!='=' && s[i]!='+' && s[i]!='-' && s[i]!='*' && s[i]!='/' && s[i]!='|' && s[i]!='&' && s[i]!='^' && s[i]!='%')
                                                //{
                                                    //line+=s[i];
                                                    //i++;
                                                //}
                                                //i--;
                                                state=-1;
                                                output<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                                cout<<"Error at line number: "<<lineno<<". Invalid integer representation\n";
                                                break;
                                            }
                                        case 24:
                                            if(line[j]>='0' && line[j]<='9')
                                            {
                                                j++;
                                                state=24;
                                                break;
                                            }
                                            else
                                            {
                                                //p=0;
                                                //while(s[i]!=' ' && s[i]!='\t' && s[i]!=';' && s[i]!='(' && s[i]!=',' && s[i]!=')' && s[i]!='[' && s[i]!=']' && s[i]!='{' && s[i]!='}' && s[i]!='<' && s[i]!='>' && s[i]!='=' && s[i]!='+' && s[i]!='-' && s[i]!='*' && s[i]!='/' && s[i]!='|' && s[i]!='&' && s[i]!='^' && s[i]!='%')
                                                //{
                                                    //line+=s[i];
                                                    //i++;
                                                //}
                                                //i--;
                                                state=-1;
                                                output<<"Error at line number: "<<lineno<<". Invalid floating point representation\n";
                                                cout<<"Error at line number: "<<lineno<<". Invalid floating point representation\n";
                                                break;
                                            }
                                        default:
                                            breaker=0;
                                            break;
                                    }
                                }
                                if(breaker==1)
                                {
                                    if(flo==0)
                                    {
                                        temp=0;
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            temp=tokenno[line];
                                        }
                                        else
                                        {
                                            id=2;
                                            temp=id;
                                            tokenno[line]=id;
                                        }
                                        output<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Integer literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    }
                                    else
                                    {
                                        temp=0;
                                        if(tokenno.find(line)!=tokenno.end())
                                        {
                                            temp=tokenno[line];
                                        }
                                        else
                                        {
                                            id=2;
                                            temp=id;
                                            tokenno[line]=id;
                                        }
                                        output<<"Token "<<temp<<" Floating Point literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Floating Point literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    }
                                }
                            }
                        }
                        else if(line[0]=='\"')
                        {
                            state=25;
                            breaker=1;
                            int invalid=0;
                            int startindex=1;
                            //cout<<"line"<<line;
                            while(breaker==1 && startindex<line.length())
                            {
                                switch(state)
                                {
                                    case 25:
                                        if(line[startindex]=='\\')
                                        {
                                            state=26;
                                            break;
                                        }
                                        else if(line[startindex]=='\"')
                                        {
                                            if(startindex==line.length()-1)
                                            {
                                                startindex++;
                                                break;
                                            }
                                            else
                                            {
                                                invalid=1;
                                                //p=0;
                                                state=-1;
                                                output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                cout<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            startindex++;
                                            state=25;
                                            break;
                                        }
                                    case 26:
                                        if(startindex==line.length()-1)
                                        {
                                            invalid=1;
                                            //p=0;
                                            state=-1;
                                            output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                            cout<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                            break;
                                        }
                                        else if(line[startindex+1]=='\"')
                                        {
                                            if(startindex==line.length()-2)
                                            {
                                                invalid=1;
                                                //p=0;
                                                state=-1;
                                                output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                                cout<<"Error at line number: "<<lineno<<". Invalid string representation\nline:"<<line<<" "<<startindex<<endl;
                                                break;
                                            }
                                            else
                                            {
                                                startindex+=2;
                                                state=25;
                                                break;
                                            }
                                        }
                                        else if(line[startindex+1]=='n' || line[startindex+1]=='t' || line[startindex+1]=='r' || line[startindex+1]=='\\')
                                        {
                                            startindex+=2;
                                            state=25;
                                            break;
                                        }
                                        else
                                        {
                                            invalid=1;
                                            //p=0;
                                            state=-1;
                                            output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                            cout<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                            break;
                                        }
                                    default:
                                        breaker=0;
                                        break;
                                }
                            }
                            if(invalid==0)
                            {
                                if(line[line.length()-1]=='\"')
                                {
                                    temp=0;
                                    if(tokenno.find(line)!=tokenno.end())
                                    {
                                        temp=tokenno[line];
                                    }
                                    else
                                    {
                                        id=2;
                                        temp=id;
                                        tokenno[line]=id;
                                    }
                                    output<<"Token "<<temp<<" String literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    cout<<"Token "<<temp<<" String literal"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                }
                                else
                                {
                                    //p=0;
                                    output<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                    cout<<"Error at line number: "<<lineno<<". Invalid string representation\n";
                                }
                            }
                        }
                        else if((line[0]>='a' && line[0]<='z') || (line[0]>='A' && line[0]<='Z'))
                        {
                            int starter=1;
                            state=27;
                            breaker=1;
                            int invalider=0;
                            while(breaker==1 && starter<line.length())
                            {
                                switch(state)
                                {
                                    case 27:
                                        if((line[starter]>='a' && line[starter]<='z') || (line[starter]>='A' && line[starter]<='Z') || (line[starter]>='0' && line[starter]<='9') || line[starter]=='_')
                                        {
                                            starter++;
                                            state=27;
                                            break;
                                        }
                                        else
                                        {
                                            if(id==12)
                                            {
                                                starter++;
                                                state=27;
                                                break;
                                            }
                                            invalider=1;
                                            //p=0;
                                            state=-1;
                                            output<<"Error at line number: "<<lineno<<". Invalid identifier representation\n";
                                            cout<<"Error at line number: "<<lineno<<". Invalid identifier representation\n";
                                            break;
                                        }
                                    default:
                                        breaker=0;
                                        break;
                                }
                            }
                            if(invalider==0)
                            {
                                if(prev_token=="int" || prev_token=="float" || prev_token=="char" || prev_token=="string" || prev_token=="boolean" || prev_token=="double" || prev_token=="bool")
                                {
                                    //cout<<"YES"<<endl;
                                    temp=0;
                                    if(tokenno.find(line)!=tokenno.end())
                                    {
                                        id=1;
                                        temp=tokenno[line];
                                        output<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    }
                                    else
                                    {
                                        identifiers[line]=1;
                                        id=1;
                                        temp=id;
                                        tokenno[line]=id;
                                        output<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        cout<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                    }
                                }
                                else
                                {
                                    if(prev_token=="void")
                                    {
                                        //p=0;
                                        output<<"Error at line number: "<<lineno<<". Invalid variable initialization\n";
                                        cout<<"Error at line number: "<<lineno<<". Invalid variable initialization\n";
                                    }
                                    else
                                    {
                                        if(id==12)
                                        {
                                            id=11;
                                            temp=id;
                                            tokenno[line]=id;
                                            output<<"Token "<<temp<<" Library Name"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            cout<<"Token "<<temp<<" Library Name"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                        }
                                        else
                                        {
                                            if(identifiers.find(line)!=identifiers.end())
                                            {
                                                temp=0;
                                                if(tokenno.find(line)!=tokenno.end())
                                                {
                                                    temp=tokenno[line];
                                                }
                                                else
                                                {
                                                    id=1;
                                                    temp=id;
                                                    tokenno[line]=id;
                                                }
                                                output<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                                cout<<"Token "<<temp<<" Identifier"<<", string: "<<line<<", line number: "<<lineno<<"\n";
                                            }
                                            else
                                            {
                                                //p=0;
                                                //cout<<"temp and id:"<<temp<<" "<<id<<" ";
                                                output<<"Error at line number: "<<lineno<<". Undefined identifier\nToken string: "<<line<<endl;
                                                cout<<"Error at line number: "<<lineno<<". Undefined identifier\nToken string: "<<line<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            //p=0;
                            output<<"Error at line number: "<<lineno<<". Invalid start character for token\n";
                            cout<<"Error at line number: "<<lineno<<". Invalid start character for token\n";
                        }
                        prev_token=line;
                    }
                }
                if(definer==0 && id!=2)
                {
                    output<<"Error at line number: "<<lineno<<". Expected semicolon at the end of the statement\nEnds with: "<<line<<endl;
                    cout<<"Error at line number: "<<lineno<<". Expected semicolon at the end of the statement\nEnds with: "<<line<<endl;
                }
            }
        }
    }
    return 0;
}
