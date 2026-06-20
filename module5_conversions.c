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

//String stack node, holds full sub-expressions like "(A+B)"
struct stringNode{
    char data[100];
    struct stringNode* next;
};
struct stringStack{
    struct stringNode* top;
};

//Initializing the stack's top to NULL
void initStack(struct stack *s){
    s->top=NULL;
}
int isEmpty(struct stack *s){
    return s->top==NULL;
}
int isEmptyStr(struct stringStack *s){
    return s->top==NULL;
}

//Pushing an element into a stack
void push(struct stack* s,double val){
    struct node * newNode =(struct node*)malloc(sizeof(struct node));
    newNode->data=val;
    newNode->next=s->top;
    s->top=newNode;
}
//Pushing a string onto the string stack
void pushStr(struct stringStack* s,char* val){
    struct stringNode * newNode =(struct stringNode*)malloc(sizeof(struct stringNode));
    strcpy(newNode->data,val);
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
//Pop a string from the string stack into the caller's buffer
void popStr(struct stringStack* s,char* val){
    if(s->top==NULL){
        printf("Stack is empty, underflow");
        exit(1);
    }
    struct stringNode *temp=s->top;
    s->top=temp->next;
    strcpy(val,temp->data);
    free(temp);
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

//1. Infix -> Postfix (Shunting-yard), writes result into 'result' buffer
void infixPostfix(char* infix_expression, struct stack* s, char* result){
    int i=0;
    int rk=0;
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
            rk+=sprintf(result+rk,"%g ",num);
            continue;
        }
        //Single letter variable operand
        if(infix_expression[i]>='A'&& infix_expression[i]<='Z'){
            rk+=sprintf(result+rk,"%c ",infix_expression[i]);
            i++;
            continue;
        }
        if (infix_expression[i]=='('){
            push(s,'(');
            i++;
            continue;
        }
        if(infix_expression[i]==')'){
            while(!isEmpty(s)&&(char)s->top->data!='('){
                rk+=sprintf(result+rk,"%c ",(char)pop(s));
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
                        rk+=sprintf(result+rk,"%c ",(char)pop(s));
                    }
                    else break;
                }
                else{
                    if(precedence(top)>=precedence(infix_expression[i])){
                        rk+=sprintf(result+rk,"%c ",(char)pop(s));
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
        rk+=sprintf(result+rk,"%c ",(char)pop(s));
    }
    result[rk]='\0';
}

//2. Infix -> Prefix using the reverse trick:
//reverse input, swap parens, run shunting-yard, then reverse output token by token
void infixPrefix(char* infix_expression,struct stack* s, char* result){
    int i=0,infix_expression_length=0;
    while(infix_expression[i]!='\0'){
        infix_expression_length++;
        i++;
    }
    int j=infix_expression_length-1;
    i=0;
    char rev_infix_expression[infix_expression_length+1];
    while(j>=0){
        rev_infix_expression[i]=infix_expression[j];
        j--;
        i++;
    }
    rev_infix_expression[i]='\0';
    infix_expression=rev_infix_expression;
    i=0;

    //swap parentheses since we reversed the string
    while(infix_expression[i]!='\0'){
        if(infix_expression[i]=='('){
            infix_expression[i]=')';
        }
        else if(infix_expression[i]==')'){
            infix_expression[i]='(';
        }
        i++;
    }
    i=0;

    char output[100];
    int k=0;

    while(infix_expression[i]!='\0'){
        if(infix_expression[i]==' '){
            i++;
            continue;
        }
        if(infix_expression[i]>='0'&& infix_expression[i]<='9'){
            double num=0;
            while(infix_expression[i]>='0'&& infix_expression[i]<='9'){
                num=num*10+(infix_expression[i]-'0');
                i++;
            }
            k+=sprintf(output+k,"%g ",num);
            continue;
        }
        if(infix_expression[i]>='A'&& infix_expression[i]<='Z'){
            k+=sprintf(output+k,"%c ",infix_expression[i]);
            i++;
            continue;
        }
        if (infix_expression[i]=='('){
            push(s,'(');
            i++;
            continue;
        }
        if(infix_expression[i]==')'){
            while(!isEmpty(s)&&(char)s->top->data!='('){
                output[k++]=(char)pop(s);
                output[k++]=' ';
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
                        output[k++]=(char)pop(s);
                        output[k++]=' ';
                    }
                    else break;
                }
                else{
                    if(precedence(top)>=precedence(infix_expression[i])){
                        output[k++]=(char)pop(s);
                        output[k++]=' ';
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
        output[k++]=(char)pop(s);
        output[k++]=' ';
    }
    output[k]='\0';

    //reverse token by token (not character by character) so multi-digit
    //numbers like "20" don't get scrambled into "02"
    char* tokens[100];
    int token_count=0;
    char* token=strtok(output," ");
    while(token!=NULL){
        tokens[token_count++]=token;
        token=strtok(NULL," ");
    }
    int rk=0;
    for(int t=token_count-1;t>=0;t--){
        rk+=sprintf(result+rk,"%s ",tokens[t]);
    }
    result[rk]='\0';
}

//3. Postfix -> Infix using the string stack
//operand -> push, operator -> pop b then a, build "(a op b)"
void postfixInfix(char* postfix_expression,struct stringStack*s,char* result){
    int i=0;
    while(postfix_expression[i] != '\0'){
        if(postfix_expression[i] == ' '){
            i++;
            continue;
        }
        if(postfix_expression[i] >= '0' && postfix_expression[i] <= '9'){
            char num[20];
            int k = 0;
            while(postfix_expression[i] >= '0' && postfix_expression[i] <= '9'){
                num[k++] = postfix_expression[i];
                i++;
            }
            num[k] = '\0';
            pushStr(s, num);
            continue;
        }
        if(postfix_expression[i] >= 'A' && postfix_expression[i] <= 'Z'){
            char operand[2];
            operand[0] = postfix_expression[i];
            operand[1] = '\0';
            pushStr(s, operand);
            i++;
            continue;
        }
        if(isOperator(postfix_expression[i])){
            char b[100], a[100];
            popStr(s, b);
            popStr(s, a);

            char combined[210];
            sprintf(combined, "(%s%c%s)", a, postfix_expression[i], b);

            pushStr(s, combined);
            i++;
            continue;
        }
        i++;
    }
    popStr(s,result);
}

//4. Prefix -> Infix using the string stack, scanning right to left
//operator -> pop a then b (opposite order from postfix), build "(a op b)"
void prefixInfix(char* prefix_expression, struct stringStack* s,char* result){
    int len = strlen(prefix_expression);
    int i = len - 1;   // start from the END

    while(i >= 0){
        if(prefix_expression[i] == ' '){
            i--;
            continue;
        }
        //multi-digit numbers need to be walked back to their start,
        //then read forward, so the digits don't come out reversed
        if(prefix_expression[i] >= '0' && prefix_expression[i] <= '9'){
            int end = i;
            while(i >= 0 && prefix_expression[i] >= '0' && prefix_expression[i] <= '9'){
                i--;
            }
            int start = i + 1;

            char num[20];
            int k = 0;
            for(int j = start; j <= end; j++){
                num[k++] = prefix_expression[j];
            }
            num[k] = '\0';

            pushStr(s, num);
            continue;
        }
        if(prefix_expression[i] >= 'A' && prefix_expression[i] <= 'Z'){
            char operand[2];
            operand[0] = prefix_expression[i];
            operand[1] = '\0';
            pushStr(s, operand);
            i--;
            continue;
        }
        if(isOperator(prefix_expression[i])){
            char a[100], b[100];
            popStr(s, a);
            popStr(s, b);

            char combined[210];
            sprintf(combined, "(%s%c%s)", a, prefix_expression[i], b);

            pushStr(s, combined);
            i--;
            continue;
        }
        i--;
    }
    popStr(s, result);
}

//5. Postfix -> Prefix, chained: Postfix -> Infix -> Prefix
void postfixPrefix(char* postfix_expression, struct stringStack* ss, struct stack* s){
    char infix_result[110];
    postfixInfix(postfix_expression, ss, infix_result);

    char prefix_result[110];
    infixPrefix(infix_result, s, prefix_result);

    printf("%s\n", prefix_result);
}

//6. Prefix -> Postfix, chained: Prefix -> Infix -> Postfix
void prefixPostfix(char* prefix_expression, struct stringStack* ss, struct stack* s){
    char infix_result[110];
    prefixInfix(prefix_expression, ss, infix_result);

    char postfix_result[110];
    infixPostfix(infix_result, s, postfix_result);

    printf("%s\n", postfix_result);
}

int main(){
    int choice;
    char expression[100];
    char result[110];

    printf("1. Infix to Postfix\n");
    printf("2. Infix to Prefix\n");
    printf("3. Postfix to Infix\n");
    printf("4. Prefix to Infix\n");
    printf("5. Postfix to Prefix\n");
    printf("6. Prefix to Postfix\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  // consume leftover newline from scanf

    printf("Enter the expression: ");
    fgets(expression, sizeof(expression), stdin);
    /*
    fgets also scans the last pressed button i.e "enter button", so we have '\n' in our expression
    so we use strcspn for replacing that with '\0' which represents the end of a string
    */
    expression[strcspn(expression, "\n")] = '\0';

    struct stack s;
    struct stringStack ss;
    initStack(&s);
    ss.top = NULL;

    switch(choice){
        case 1:
            infixPostfix(expression, &s, result);
            printf("%s\n", result);
            break;
        case 2:
            infixPrefix(expression, &s, result);
            printf("%s\n", result);
            break;
        case 3:
            postfixInfix(expression, &ss, result);
            printf("%s\n", result);
            break;
        case 4:
            prefixInfix(expression, &ss, result);
            printf("%s\n", result);
            break;
        case 5:
            postfixPrefix(expression, &ss, &s);
            break;
        case 6:
            prefixPostfix(expression, &ss, &s);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
