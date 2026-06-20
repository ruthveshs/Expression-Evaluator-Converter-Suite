#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Node structure for linked list used in stack
struct node{
    double data;
    struct node * next;
};
//stack structure
struct stack{
    struct node* top;
};
//Initializing the stack's top to NULL
void initStack(struct stack *s){
    s->top=NULL;
}
//Checks if the stack is empty or not if empty it returns 1 else 0
int isEmpty(struct stack *s){
    return s->top==NULL;
}
//Pushing an element into a stack
void push(struct stack* s,double val){
    struct node * newNode =(struct node*)malloc(sizeof(struct node));
    newNode->data=val;
    newNode->next=s->top;
    s->top=newNode;
}
//Pop a value from the stack, exits when the stack is empty
double pop(struct stack *s){
    if(s->top==NULL){
        printf("Stack is empty, underflow");
        exit(1);
    }
    struct node *temp=s->top;
    s->top=temp->next;
    double val=temp->data;
    free(temp);
    return val;
}
/*
This checks the presedence of the operator
like +,- has least precedence so 1 and ^ has the highest precedence so 3
*/
int precedence(char c){
    if(c=='+'|| c=='-')
        return 1;
    if(c=='*'|| c=='/')
        return 2;
    if(c=='^')
        return 3;
    return 0;
}
//Checks if the charecter is an operator, returns 1 if it is an operator else 0
int isOperator(char c){
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='^';
}
/*
This is the main code that connects everything and gives us an "POSTFIX" code
    *if the charecter is:
        -number:prints it directly into output
        -'(':push onto stack
        -')':pop and print until '(' is found
        -operator:pop higher/equal precedence operators first, then push
                  Exception: '^' is right-associative, so only pop strictly higher 
        -end of input:pop and print all remaining operators from stack      
*/
void infixPostfix(char* infix_expression,struct stack* s){
    int i=0;
    while(infix_expression[i]!='\0'){
        if(infix_expression[i]==' '){
            i++;
            continue;
        }
        //If the number isn't a single digit then this code helps us in getting the full number,as our code reads our postfix expression one digit at a time
        if(infix_expression[i]>='0'&& infix_expression[i]<='9'){
            double num=0;
            while(infix_expression[i]>='0'&& infix_expression[i]<='9'){
                num=num*10+(infix_expression[i]-'0');
                i++;
            }
            //%g is used for dropping all the trailing zeros
            printf("%g ",num);
            continue;
        }
        if (infix_expression[i]=='('){
            push(s,'(');
            i++;
            continue;
        }
        if(infix_expression[i]==')'){
            while(!isEmpty(s)&&(char)s->top->data!='('){
                printf("%c ",(char)pop(s));
            }
            if(!isEmpty(s)){
                pop(s);
            }
            i++;
            continue;
        }
        
        if(isOperator(infix_expression[i])){
            while(!isEmpty(s)){
                char top=(char)s->top->data;
                if(infix_expression[i]=='^'){
                    if(precedence(top)>precedence(infix_expression[i])){
                        printf("%c ",(char)pop(s));
                    }
                    else break;
                }
                else{
                    if(precedence(top)>=precedence(infix_expression[i])){
                        printf("%c ",(char)pop(s));
                    }
                    else
                        break;
                }
            }
            push(s, infix_expression[i]);
            i++;
            continue;
        }
        i++;
    }
    while(!isEmpty(s)){
        printf("%c ",(char)pop(s));
    }
    printf("\n");
}

int main(){
    char infix_expression[100];
    printf("Enter the infix expression: ");
    /*
    scanf("%[^\n], postsix_expression");
    we could also use this instead of using fgets and then using strcspn
    */
    fgets(infix_expression,sizeof(infix_expression),stdin);
    /*
    fgets also scans the last pressed button i.e "enter button", so we have '\n' in our postfixExpression
    so we use strcspn for replacing that with '/0' which represents the end of a string
    */
    infix_expression[strcspn(infix_expression,"\n")]='\0';

    struct stack s;
    initStack(&s);

    printf("The postfix expression: ");
    infixPostfix(infix_expression,&s);
    return 0;
}