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
//Main heart of the code "Evaluating the Prefix expression" and returns the result
double evaluatePrefix(char* prefixExpression,struct stack* s){
    int i=0;
    while(prefixExpression[i]!='\0'){
        i++;
    }
    i--;
    while(i>=0){
        //This part is for skipping the spaces
        if(prefixExpression[i]==' '){
            i--;
            continue;
        }
        //If the number isn't a single digit then this code helps us in getting the full number,as our code reads our postfix expression one digit at a time
        if(prefixExpression[i]>='0'&& prefixExpression[i]<='9'){
            double num=0;
            int place=1;
            while(prefixExpression[i]>='0'&& prefixExpression[i]<='9'){
                num=num+(prefixExpression[i]-'0')*place;
                place*=10;
                i--;
            }
            push(s,num);
            continue;
        }

        //Pops two operands, b is the top one(second operand) and a is below b(first operand)
        double a= pop(s);
        double b= pop(s);
        switch (prefixExpression[i]){
        case '+':
            push(s,a+b);
            break;
        case '-':
            push(s,a-b);
            break;
        case '*':
            push(s,a*b);
            break;
        case '/':
            if(b==0){
                printf("Error!(Division cant be done by zero)");
                exit(1);
            }
            else{
                push(s,a/b);
                break;
            }
        case '^':{
            double result = 1;
            for(int j = 0;j< (int)b; j++){
                result *= a;
            }
            push(s,result);
            break;
        }
        }
        i--;
    }
    //returns the final value since only one value is left over in the stack
    return pop(s);
}



int main(){
    char prefix_expression[100];
    printf("Enter the prefix expression: ");
    /*
    scanf("%[^\n], postsix_expression");
    we could also use this instead of using fgets and then using strcspn
    */
    fgets(prefix_expression,sizeof(prefix_expression),stdin);
    /*
    fgets also scans the last pressed button i.e "enter button", so we have '\n' in our postfixExpression
    so we use strcspn for replacing that with '/0' which represents the end of a string
    */
    prefix_expression[strcspn(prefix_expression,"\n")]='\0';

    struct stack s;
    initStack(&s);

    printf("The result of the prefix expression: %0.3f",evaluatePrefix(prefix_expression,&s));
    return 0;
}
