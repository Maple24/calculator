#include<iostream>
#include<stack>
#include<math.h>
using namespace std;

stack<float> NumStack; //数字栈
stack<char> CharStack; //运算符栈

int pre(char flag){  //运算符优先级
  switch (flag){
    case '+':
    case '-':
	return 0;
    case '*':
    case '/':
	return 1;
    default:
	return -1;
  }
}
void Calculate(){ //单步计算 
  float negative = NumStack.top();
  float positive;
  NumStack.pop();
  if (NumStack.empty()){
      positive = 0;
}
  else{
      positive = NumStack.top();
      NumStack.pop();
 }
  switch(CharStack.top()){
	case '+':
	   NumStack.push(positive+negative);
	   break;
	case '-':
	   NumStack.push(positive-negative);
	   break;
	case '*':
	   NumStack.push(positive*negative);
	   break;
  	case '/':
	   NumStack.push(positive/negative);
	   break;	
  }
  CharStack.pop();
}

int  ChangeFormat(char* format) //将中缀表达式转为逆波兰后缀表达式
{
  for(int i = 0;format[i]!='=';i++)
  {
	if (format[i+1] == '\0' && format[i]!='=')
	{
		cout<<"请以等号结尾"<<endl;
		return 0;
	}
	if(format[i]=='+' || format[i]=='-' || format[i]=='*' || format[i]=='/' || format[i] == '(' || format[i] == ')')
	{
	        if (format[i] == '('){   //遇到(直接入运算符栈
			CharStack.push(format[i]);
		}	
   		else if (format[i] == ')'){  // 右括号匹配左括号 完成括号内的计算
			if(CharStack.empty())
			{
				cout<<"非法输入"<<endl;
			}
			else
			{
				while(CharStack.top()!='(')
				{
					Calculate();
					if(CharStack.empty())
					{
						cout<<"非法输入"<<endl;
					}
				}
				CharStack.pop();
			}
		}
		else if(CharStack.empty() || pre(CharStack.top())<pre(format[i]))  //栈为空或当前栈内运算符优先级低，则直接入栈
		{
			CharStack.push(format[i]);
		}
		else{  //否则先计算栈内结果
			Calculate();
			CharStack.push(format[i]);
		}
	}
	else if(format[i]>='0' && format[i]<='9') //数字直接入数字栈
	{
		float number = float(format[i])-48;
		if(format[i+1] == '.') //小数点处理
		{
		   i=i+2;
		   for(int count = 1;format[i]>='0'||format[i]<='9';count++)
		   {
			number = number+(float(format[i])-48)*pow(10,-count);
			if(format[i+1]>='0' && format[i+1]<'9')
			{
				i++;
			}
			else
			{
				break;
			}
		   }
		}
		else if(format[i+1]>='0' && format[i+1]<='9')
		{
			while(format[i+1]>='0' && format[i+1]<='9')
			{
				number = (float(format[i+1])-48)+number*10;
				i++;
			}
		}
		NumStack.push(number);
	}
	else //否则提示非法字符
	{
		cout<<"输入非法字符"<<endl;
		return 0;
	}
  }	
	while(!CharStack.empty()){  //进行栈内计算，直到运算符栈为空
		Calculate();
	}
	return 1;
}


void menu(){   //提示输入表达式菜单
  cout<<"请输入表达式:"<<endl;
}

void cmdMenu(){   //提示输入命令菜单
  cout<<"A:存储 C:清空 F:退出"<<endl;
}

void Start(){  //初始化字符串，并调用表达式转换函数。得到计算结果
	char* format = new char[100];
        cin>>format;
	while(ChangeFormat(format) == 0)
	{
		menu();
		cin>>format;
	}
	cout<<"计算结果为:"<<NumStack.top()<<endl;
}
void Store() //存储功能
{
	cout<<"存储成功,你上次计算的结果为:"<<NumStack.top()<<endl;
	cout<<"继续上次计算，请输入表达式"<<endl;
	Start();
}

void Clean(){  //清空功能
      NumStack.pop();
      cout<<"清空成功"<<endl;
      menu();
      Start();
}
int main(){  //主函数
  menu();
  Start();
  char cmd;
  cmdMenu();
  while(cin>>cmd && cmd!='F' && cmd!= 'f'){  //输入命令 当命令不为'F'时执行下面操作，为'F'则退出程序
	switch(cmd){
	 	case 'A':
		case 'a':
			Store();
			break;
		case 'C':
		case 'c':
			Clean();
			break;
		default:
			cout<<"错误命令!请重新输入"<<endl;
			break;
	}
  	cmdMenu();
  }
  cout<<"退出中,谢谢使用"<<endl;
  return 0;
}
