#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
struct Node
{
	char* val;
	struct Node* next;
};
struct Node* operand;
struct Node* operator;
struct Node* head;
int map[26];
char* res;
char* expr;
int n=0;
int prec(char a)
{
	if(a=='*'||a=='/')	return 1;
	else return 0;
}
void push(char* v,int x)
{
	// printf("%s\n",v);
	if(x==1)
		head=operand;
	else	
		head=operator;
	struct Node* ptr=(struct Node*)(malloc(sizeof(struct Node)));
	ptr->val=(char*)malloc(sizeof(v));
	strcpy(ptr->val,v);
	ptr->next=head;
	if(x==1)
		operand=ptr;
	else
		{operator=ptr;n++;}
}
void pop(int x)
{
	if(x==1)
		head=operand;
	else
		head=operator;
	free(res);
	res=(char*)malloc(sizeof(head->val));
	strcpy(res,head->val);
	struct Node* old=head;
	head=head->next;
	if(x==1)
		operand=head;
	else
		{operator=head;n--;}

	free(old);
}
int toInt(char* s)
{
	int len=strlen(s);
	int f = 1;
	int i=0;
	if(s[0]=='-')
	{
		f=-1;i=1;
	}
	if(isalpha(s[i]))
	{
		return f*map[s[i]-'a'];
	}
	int sum=0;
	for(;i<len;i++)
	{
		sum=sum*10+(s[i]-'0');
	}
	return sum*f;
}
char* toString(int x)
{
	char* ress=(char*)malloc(sizeof(char)*10);
	int poss=0,flag=0;
	if(x<0)
	{
		flag=1;
		x*=-1;
	}
	do
	{
		int d=x%10;
		ress[poss++]=(char)(d+'0');
		x/=10;

	}while(x>0);
	ress[poss]='\0';
	// printf("%s\n",ress);
	int len=strlen(ress);
	char* ans=(char*) malloc(sizeof(char)*10);
	poss=len-1;
	int i=0;
	if(flag)
	{
		ans[0]='-';
		i++;
	}
	for(;poss>=0;)
	{
		ans[i++]=ress[poss--];
	}
	ans[i]='\0';
	return ans;
}
void compute()
{
	pop(1);
	char* op1=(char*)malloc(sizeof(res));
	strcpy(op1,res);
	pop(1);
	char* op2=(char*)malloc(sizeof(res));
	strcpy(op2,res);
	pop(0);
	int b=toInt(op1);
	int a=toInt(op2);
	// printf("%d %d %s\n",a,b,res);
	int ans;
	if(res[0]=='+')	ans=a+b;
	else if(res[0]=='-')	ans=a-b;
	else if(res[0]=='*')	ans=a*b;
	else	ans=a/b;	
	char* k=toString(ans);
	push(k,1);
}
int eval()
{
	int i;
	// printf("%d",strlen(expr));
	int sz=strlen(expr);
	char* curr=(char*) malloc(sizeof(expr));
	int pos=0;
	int x=0;
	int num=-1;
	for(i=0;i<sz && expr[i];i++)
	{
		// printf("%d\n",i);
		// getchar();
		if(isdigit(expr[i])||isalpha(expr[i]))
		{
			curr[pos++]=expr[i];
			curr[pos]='\0';
			num=0;
		}
		else if(expr[i]=='+'||expr[i]=='-'||expr[i]=='/'||expr[i]=='*')
		{
			if(num==1)
			{
				free(curr);
				curr=(char*)malloc(sizeof(expr));
				pos=0;
				if(expr[i]=='-')
				{
					curr[0]='-';
					pos=1;
				}
			}
			else
			{
				push(curr,1);
				free(curr);
				curr=(char*)malloc(sizeof(expr));
				pos=0;
				num=1;
			
				while(n)
				{
					pop(0);
					push(res,0);
					if(prec(res[0])>=prec(expr[i]))
					{
						compute();
					}
					else break;
				}
				char* op=(char*)malloc(sizeof(char));
				op[0]=expr[i];
				push(op,0);
			}
		}	
	}
	push(curr,1);
	// return;
	while(n)
	{
		compute();
	}
	pop(1);
	int ans=toInt(res);
	// printf("%d\n",ans);
	return ans;
}
int main()
{
	n=0;
	while(1)
	{
		free(expr);
		expr=(char*)malloc(sizeof(char)*1000);
		size_t x=1000;
		getline(&expr,&x,stdin);
		// scanf("%s",expr);
		// printf("%s",expr);
		// printf("%d",strlen(expr));
		if(expr[1]=='=')
		{
			int i=2;
			int pos=0;
			char* str=(char*)malloc(sizeof(expr));
			for(;expr[i];i++)
				str[pos++]=expr[i];
			int idx=expr[0]-'a';
			strcpy(expr,str);
			int ans=eval();
			map[idx]=ans;
			printf("%d\n",ans);
		}
		else
		{
			int ans=eval();
			printf("%d\n",ans);
		}
	}
	/*char* x=(char*) malloc(20);
	x=toString(-1);
	printf("%s\n",x);*/
}