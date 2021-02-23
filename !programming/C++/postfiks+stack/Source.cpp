#include <iostream>
#include <string>
using namespace std;
struct node
{
	int info;
	node* next;
	node() { info = 0; next = NULL; };
	node(int a) { info = a; next = NULL; };
	node(int a, node * p) { info = a; next = p; };
};

struct myStack
{
	node* top;
	myStack() { top = 0; };
	virtual ~myStack() { Erase();};
	void push(int x)
	{
		node *a = new node(x, top);
		top = a;
	}
	int ftop() 
	{
		return top->info;
	}
	char fpop() {
		node *p = top;
		char c = p->info;
		top = top->next;
		delete p;
		return c;
	}
	bool is_empty() { if (top == nullptr) return true; else return false; }
private:
	void Erase()
	{
		node *a = top;
		node *b;
		while (a != nullptr)
		{
			b = a;
			a = a->next;
			delete b;
		}
	}
};
struct myStackInt {
	node *top;
	myStackInt() { top = 0; }
	virtual ~myStackInt() { Erase(); }
	void push(int x) 
	{ 
		node *a = new node(x, top); 
	    top = a; 
	}
	int ftop() { return top->info; }
	int fpop() {
		node *p = top;
		int c = p->info;
		top = top->next;
		delete p;
		return c;
	}
	bool is_empty() 
	{ 
		if (top == nullptr) 
			return true; 
	    else 
			return false;
	}
private:
	void Erase() {
		node *a = top, *b;
		while (a != nullptr) {
			b = a;
			a = a->next;
			delete b;
		}
	}
};
struct postfix {
public:
	postfix() { postf = ""; }
	postfix(string *a) 
	{ 
		st = *a; 
		postf = ""; 
	}
	string* transform() {
		for (int i = 0; i < st.length(); i++) {
			switch (st[i])
			{
			case ('*'):
				
				while(!(stack.is_empty()) && (stack.ftop() == '*' || stack.ftop() == '/'))
					postf += stack.fpop();
				stack.push(st[i]);
				break;
			case ('/'):
				while (!(stack.is_empty()) && (stack.ftop() == '*' || stack.ftop() == '/'))
					postf += stack.fpop();
				stack.push(st[i]);
				break;

			case ('+'):
				while (!(stack.is_empty()) && stack.ftop() != '(' ) postf += stack.fpop();
				stack.push(st[i]);
				break;

			case ('-'):
				while (!(stack.is_empty()) && stack.ftop() != '(') postf += stack.fpop();
				stack.push(st[i]);
				break;
			case ('('):
				stack.push(st[i]);
				break;

			case (')'):
				while (stack.ftop() != '(')
					postf += stack.fpop();
				stack.fpop();
				break;

			default:
				postf += st[i];
				break;
			}
		}
		while (!stack.is_empty()) postf += stack.fpop();
		return &postf;
	}
private:
	string st;
	string postf;
	myStack stack;
};
struct stanswer
{
	stanswer() { postf = ""; }
	stanswer(string *a) { postf = *a; }
	string* transform2() 
	{
		int a, b;
		for (int i = 0; i < postf.length(); ++i)
		{
			switch (postf[i])
			{
			case('+'):
			{
				a = stack.fpop() - 48;
				b = stack.fpop() - 48;
				stack.push(a + b + 48);
				break;
			}
			case('-'):
			{
				a = stack.fpop() - 48;
				b = stack.fpop() - 48;
				stack.push(-a + b + 48);
				break;
			}
			case('*'):
			{
				a = stack.fpop() - 48;
				b = stack.fpop() - 48;
				stack.push(a * b + 48);
				break;
			}
			case('/'):
			{
				a = stack.fpop() - 48;
				b = stack.fpop() - 48;
				stack.push(a / b + 48);
				break;
			}
			default:
				stack.push(postf[i]);
				break;
			}
		}
		answer = to_string(stack.fpop() - 48);
		return &answer;
	}
private:
	string postf;
	string answer;
	myStackInt stack;
};
int main()
{
	string st;
	getline(cin, st);
	postfix a(&st);
	st = *a.transform();
	cout <<st << endl;
	stanswer b(&st);
	st = *b.transform2();
	cout << st << endl;

	system("pause");
	return 0;
}
