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
int isEmpty(struct stack *s){
    return s->top==NULL;
}
int isOperator(char c){
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='^';
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

double evaluate(struct stack* operands,struct stack* operators){
    double b=pop(operands);
    double a=pop(operands);
    char operator=pop(operators);
    switch (operator)
    {
    case '+':
        return a+b;
    case '-':
        return a-b;
    case '*':
        return a*b;
    case '/':
        if(b==0){
            printf("Error!, Division can't be done by 0");
            exit(1);
        }
        else
            return a/b; 
    case '^':{
        double result = 1;
        for(int i = 0; i < (int)b; i++){
            result *= a;
        }
        return result;
    }
    }
    return 0;
}

double evaluateInfix(char* infixExpression,struct stack* operands,struct stack* operators){
     int i=0;
    while(infixExpression[i]!='\0'){
        //This part is for skipping the spaces
        if(infixExpression[i]==' '){
            i++;
            continue;
        }
        //If the number isn't a single digit then this code helps us in getting the full number,as our code reads our postfix expression one digit at a time
        if(infixExpression[i]>='0'&& infixExpression[i]<='9'){
            double num=0;
            while(infixExpression[i]>='0'&& infixExpression[i]<='9'){
                num=num*10+(infixExpression[i]-'0');
                i++;
            }
            push(operands,num);
            continue;
        }

        if(infixExpression[i]=='('){
            push(operators,'(');
            i++;
            continue;
        }

        if(infixExpression[i]==')'){
            while(!isEmpty(operators)&&(char)operators->top->data!='('){
                push(operands,evaluate(operands,operators));
            }
            if(!isEmpty(operators)){
                pop(operators);
            }
            i++;
            continue;
        }

        if(isOperator(infixExpression[i])){
            while(!isEmpty(operators)){
                char top=(char)operators->top->data;
                if(top=='('){
                    break;
                }
                if(infixExpression[i]=='^'){
                    if(precedence(top)>precedence(infixExpression[i])){
                        push(operands,evaluate(operands,operators));
                    }
                    else{
                        break;
                    }
                }
                else{
                    if(precedence(top)>=precedence(infixExpression[i])){
                        push(operands,evaluate(operands,operators));
                    }
                    else
                        break;
                }
            }
            push(operators,infixExpression[i]);
            i++;
            continue;
        }
        i++;
    }
    while(!isEmpty(operators)){
        push(operands,evaluate(operands,operators));
    }
    //returns the final value since only one value is left over in the stack
    return pop(operands);
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

    struct stack operands;
    struct stack operators;
    initStack(&operands);
    initStack(&operators);

    printf("The result of the infix expression: %0.3f",evaluateInfix(infix_expression,&operands,&operators));
    
    return 0;
}