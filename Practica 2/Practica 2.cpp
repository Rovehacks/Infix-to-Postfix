#include <iostream>
using namespace std;

template <typename  T>

struct Stack
{
    int top;
    T *data;
    Stack(int length)
    {
        data = new T[length];
    }
};

bool isEmpty(Stack<char>* s)
{
    if (s->top == -1)
        return true;
    else
        return false;
}

void init(Stack<char> *s)
{
    s->top = -1;
}

void push(Stack<char> *s, char p)
{
    s->top++;
    s->data[s->top] = p;
}

char pop(Stack<char>*s)
{
    s->top--;
    return s->data[s->top+1];
}

char top(Stack<char> *s)
{
    return s->data[s->top];
}

int checkHierarchy(char o1, char o2)
{
    switch (o1)
    {
    case '+':
    case '-':
    {
        if (o2 == '+' || o2 == '-')
            return 0;
        else
            return 1;
    }break;
    case '*':
    case '/':
    {
        if (o2 == '+' || o2 == '-')
            return -1;
        else if (o2 == '*' || o2 == '/')
            return 0;
        else
            return 1;
    }break;
    case '^':
    {
        if (o2 == '^')
            return 0;
        else
            return -1;
    }break;
    }
}

string postfix(string chain, Stack<char>* s)
{
    string res = "";
    for (int i = 0; i < chain.length(); i++)
    {
        switch (chain[i])
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        {
                while (!isEmpty(s) && top(s) != '(' && checkHierarchy(top(s), chain[i]) != 1)
                    res += pop(s);
                push(s, chain[i]);
        }break;
        case '(':
        {
            push(s, chain[i]);
        }break;
        case ')':
        {
            while (!isEmpty(s) && top(s) != '(')
                res += pop(s);
            if (!isEmpty(s))
                pop(s);
        }break;
        default:
        {
            res += chain[i];
        }break;
        }
    }
    while(!isEmpty(s))
        res += pop(s);
    return res;
}

int main()
{
    string chain;
    cout << "Ingresa la cadena correcta" << endl;
    cin >> chain;
    Stack<char>* s = new Stack<char>(chain.length());
    init(s);
    cout << postfix(chain, s);
}