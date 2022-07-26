#include<bits/stdc++.h>
using namespace std;
string str;				//输入的原始字符
vector<string> out;		//存放转化完成的后缀表达式 
stack<char> st1;		//存放操作符

bool isop(char c);		//判断是否是运算符 
int prior(char c);		//判断优先级 
void mid();				//中缀表达式判断正误及存入栈中 
void calcu();			//后缀栈计算结果  
void menu();			//选择菜单(美化) 
void chose();			//选择功能 
void back();			//输入的后缀表达式存入栈中 
int isok(string c);		//判断中缀表达式正误 
int isok1(string c);	//判断后缀表达式正误，出现了非运算符及数字的字符 

int main()
{
    chose();
}

void menu()
{
	printf("***********************************************************************************************************************\n");
    printf("***                                                                                                                 ***\n");
	printf("**                                         1.中缀表达式                                                              **\n");
	printf("*                                          2.后缀表达式                                                               *\n");
    printf("**                                         0.退出                                                                    **\n");
    printf("***                                                                                                                 ***\n");
	printf("***********************************************************************************************************************\n");
}

void chose()
{
    char c1[20];			//用户的输入，用字符数组防止输入的式字符串 
	int c;					//用户的选择功能 
	menu();
    printf("\n您想使用哪个功能，请输入相应数字：");
	while(1)
	{
		scanf("%s",c1);
		//把正确输入转为int型 
		if(strcmp(c1,"0")==0)
            c=0;
        else if(strcmp(c1,"1")==0)
            c=1;
        else if(strcmp(c1,"2")==0)
            c=2;
        else
            c=-1;
		if(c==0)
		{
			break;
		}
		switch(c)
	    {
		case 1:
			mid();			//中缀表达式 
			break;
		case 2:
			back();			//后缀表达式 
	        break;
		default:
			printf("您输入的有误！\n");
			break;
        }
        system("pause");	//按任意键进行 
        system("cls");		//清屏 
        menu();
        printf("\n您想使用哪个功能，请输入相应数字：");
	}
}
void mid()
{
	cout<<"请输入中缀表达式:";
	cin>>str;
	if(!isok(str))			//判断输入的正误 
	{
		cout<<"您输入的表达式有误"<<endl;
		return; 
	}
	out.clear();			//清空存放后缀表达式的栈 
	int i=0;				//遍历的作用 
	/*
	第一个字符为正负号时 
		当后一个字符为'(',正负号相当于单目运算符,将0存入栈中 
		当后面为数字时将正负号包含的数字存入栈中 
	*/ 
	if(str[0]=='-'||str[0]=='+') 
	{
		if(str[1]=='(')
		{
			string temp="0";
			out.push_back(temp);
		}
		else
		{
			string temp; 
			if(str[0]=='-')
				temp="-";//临时存放操作数字符串
			else
				temp="+";//临时存放操作数字符串
			i++;
	        for(; !isop(str[i]) && i < str.length(); i++)
			{
	            temp += str[i];
	        }
	        out.push_back(temp);
		}
	}
	for(; i < str.length();)
	{
		if(str[i-1]=='('&&(str[i]=='-'||str[i]=='+'))
		{
			string temp;
			if(str[i]=='-')
				temp="-";		//临时存放操作数字符串
			else
				temp="+";		//临时存放操作数字符串
			i++;
            for(; !isop(str[i]) && i < str.length(); i++)
			{
                temp += str[i];
            }
            out.push_back(temp);
		}
        if(!isop(str[i]))		//不是操作符
		{
            string temp="";		//临时存放操作数字符串
            //保存完整数字 
            for(; !isop(str[i]) && i < str.length(); i++)
			{
                temp += str[i];
            }
            out.push_back(temp);
        }
		else
		{
			//'('直接入栈 
            if('(' == str[i])
                st1.push(str[i]);
            /*
            当前操作符为')'
			直到遍历到操作符栈顶为'('之前的操作符都出栈 
			*/ 
            else if(')' == str[i])
			{
                while(!st1.empty() && (st1.top() != '('))
				{
                    char c = st1.top();
                    char cc[2];
                    cc[0] = c;
                    cc[1] = 0;
                    string tempstr(cc,1);//把操作符转换为string型存入存放后缀表达式的栈中 
                    out.push_back(tempstr);
                    st1.pop();
                }
                //把栈顶的'('出栈 
                st1.pop();
            }
			else
			{//其它操作符
                if(!st1.empty())
				{//栈非空，先比较
                    if(prior(str[i]) > prior(st1.top()))//高于栈顶元素,入栈
                            st1.push(str[i]);
                    else
					{//相等或小于
                        while((!st1.empty()) && (prior(str[i]) <= prior(st1.top())))
						{//一直弹到比栈顶高
                            char c = st1.top();
                            char cc[2];
                            cc[0] = c;
                            cc[1] = 0;
                            string tempstr(cc,1);
                            out.push_back(tempstr);
                            st1.pop();
                        }
                        //自己入栈 
                        st1.push(str[i]);
                    }
                }
				else
				{//栈为空，直接入栈
                    st1.push(str[i]);
                }
            }
            i++;
        }
    }
    while(!st1.empty())
	{
        char c = st1.top();
        char cc[2];
        cc[0] = c;
        cc[1] = 0;
        string tempstr(cc,1);
        out.push_back(tempstr);
        st1.pop();
    }
    calcu();
}
void back()
{
	cout<<"请输入后缀表达式:";
	cin.sync();cin.clear();
	getline(cin,str);
	if(!isok1(str))
	{
		cout<<"您输入的表达式有误"<<endl;
		return; 
	}
	out.clear();
	int i = 0;
	if(str[0]=='-')
	{
		string temp="-";//临时存放操作数字符串
		i++;
        for(; !isop(str[i]) && i < str.length() && str[i]!=' '; i++)
		{
            temp += str[i];
        }
        out.push_back(temp);
	}
	for(; i < str.length();)
	{
		if(str[i]==' ')
		{
			i++;
			continue; 
		}
		if(str[i-1]==' '&&str[i]=='-'&&i+1<str.length()&&((int)str[i+1]<=57&&(int)str[i+1]>=48))
		{
			string temp="-";//临时存放操作数字符串
			i++;
            for(; !isop(str[i]) && i < str.length() && str[i]!=' '; i++)
			{
                temp += str[i];
            }
            out.push_back(temp);
		}
		if(str[i]==' ')
		{
			i++;
			continue; 
		}
        if(!isop(str[i]))
		{//不是操作符
            string temp="";//临时存放操作数字符串
            for(; !isop(str[i]) && i < str.length(); i++)
			{
				if(str[i]==' ')
					break;
                temp += str[i];
            }
            out.push_back(temp);
        }
		else
		{
			char cc[2];
            cc[0] = str[i];
            cc[1] = 0;
            i++;
            string tempstr(cc,1);
            out.push_back(tempstr);
		}
	}
	calcu();
}
void calcu()
{
	stack<double> st2;
    for(int i = 0; i < out.size(); i++)
	{
        string str = out[i];
        int cnt = str.length();
        if(!isop(str[cnt-1]))
		{
            const char* p = str.c_str();
            double ff = atof(p);
            st2.push(ff);
        }
		else
		{
			if(st2.size()<2){			//运算时栈中数字少于两个则表达式有误 
				cout << "您输入的表达式有误！" << endl;
				return; 
			} 
            double a = st2.top();
            st2.pop();
            double b = st2.top();
            st2.pop();
            char c = str[0];
            switch(c){
                case '+':
                    st2.push(b + a);
                    break;
                case '-':
                    st2.push(b - a);
                    break;
                case '*':
                    st2.push(b * a);
                    break;
                case '/':
                    st2.push(b / a);
                    break;
                case '%':
                    st2.push((int)b % (int)a);
                    break;
                case '^':
                    st2.push(pow(b,a));
                    break;
            }
        }
    }
    cout << "答案是：" << st2.top() << endl << endl;
}
int prior(char c)
{
    if(c == '+' || c == '-')
        return 0;
    if(c == '*' || c == '/' || c == '%')
        return 1;
    if(c == '^')
        return 2;
    if(c == '(' || c == ')')
        return -1;
    return -1;
}
bool isop(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '(' || c == ')')
        return true;
    return false;
}
int isok(string c)
{
	int isfind=0, cnt=0;
	//如果最后一个元素是非 ) 的运算符 和 第一个字符是非+、-、(的运算符 则非法 
	if((c[c.length()-1]!=')'&&isop(c[c.length()-1])) || (c[0]!='('&&c[0]!='+'&&c[0]!='-'&&isop(c[0])))
		return 0;
    for(int i=0;i<c.length();i++)
    {
    	
    	if(c[i]=='(')	cnt++;
    	else if(c[i]==')')	cnt--;
    	if(isfind==0 && c[0]=='(' && ((c[1]>=48&&c[1]<=57)||c[1]=='('||c[1]=='+'||c[1]=='-'))
    	{
    		isfind=1;
    		continue;
		}
		/*
		非法的情况： 
		当前元素是非数字或运算符
		或'('是最后的元素 或'('的前一个元素是数字 或'('的后一个元素是运算符
		或当前的字符是除'('、')'之外的运算符 且后一个元素也是除'('、')'之外的运算符
		或 当前元素是')'且后一个元素是数字 或 前一个元素是除'('外的运算符
		*/ 
        if(!(c[i]=='.'||c[i]=='+'||c[i]=='-'||c[i]=='*'||c[i]=='/'||c[i]=='('||c[i]==')'||c[i]=='%'||c[i]=='^'||(c[i]>=48&&c[i]<=57)) || 
			(c[i]=='('&&(i+1==c.length()||(c[i-1]>=48&&c[i-1]<=57)||(c[i+1]=='*'||c[i+1]=='/'||c[i+1]==')'||c[i+1]=='%'||c[i+1]=='^'))) || 
			(c[i]!='('&&c[i]!=')'&&isop(c[i])&&c[i+1]!='('&&c[i+1]!=')'&&isop(c[i+1])) || 
			(c[i]==')'&&((i+1<c.length()&&c[i+1]>=48&&c[i+1]<=57)||(c[i-1]!=')'&&isop(c[i-1])))))
        {
             return 0;
        }
    }
    if(cnt!=0)				//判断（）是否配对 
    	return 0;
    return 1;
}
int isok1(string c)
{
	//后缀表达式中有非法字符 则非法 
	for(int i=0;i<c.length();i++)
	{
		if(!(c[i]=='.'||c[i]==' '||c[i]=='+'||c[i]=='-'||c[i]=='*'||c[i]=='/'||c[i]=='('||c[i]==')'||c[i]=='%'||c[i]=='^'||(c[i]>=48&&c[i]<=57)))
			return 0;
	}
	return 1;
}