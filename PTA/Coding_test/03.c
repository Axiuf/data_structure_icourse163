// 02-线性结构2 一元多项式的乘法与加法运算 (20分)

#include <stdio.h>
#include <stdlib.h>


// 定义单链节点
typedef struct PolyNode *PtrToNode;
struct PolyNode
{
    int coef;
    int expon;
    PtrToNode link;
};
typedef PtrToNode Polynomial;


// 初始化一个单节点
Polynomial NewNode()
{
    Polynomial Node;
    Node = (Polynomial) malloc(sizeof(struct PolyNode));
    Node->coef = 0;
    Node->expon = 0;
    Node->link = NULL;

    return Node;
}


// 在指定的尾部添加节点
Polynomial Attach(int c, int e, Polynomial rear)
{
    if (c)
    {
        Polynomial Node = NewNode();
        Node->coef = c;
        Node->expon = e;
        
        rear->link = Node;
        rear = Node;
    } 

    return rear;
}


// 读入多项式
Polynomial ReadPoly()
{
    int N;
    scanf("%d", &N);

    Polynomial front = NewNode(), rear, temp;
    rear = front;
    int c, e;

    while (N > 0)
    {
        scanf("%d %d", &c, &e);
        rear = Attach(c, e, rear);
        N--;
    } 
    
    if (front->link != NULL)
    {
        temp = front;
        front = front->link;
        free(temp);
    }

    return front;
}


// 输出多项式
void PrintPoly(Polynomial P)
{
    printf("%d %d", P->coef, P->expon);
    P = P->link;
    while (P)
    {
        printf(" %d %d", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}


// 比较两个数的大小
int Compare(int a, int b)
{
    int result;
    if (a > b)
    {
        result = 1;
    }
    else if (a < b)
    {
        result = -1;
    }
    else if (a == b)
    {
        result = 0;
    }

    return result;
}


// 多项式加法
Polynomial AddPoly(Polynomial P1, Polynomial P2)
{
    Polynomial front = NewNode(), rear, temp;
    rear = front;

    while (P1 && P2)
    {
        switch (Compare(P1->expon, P2->expon))
        {
        case 1:
            rear = Attach(P1->coef, P1->expon, rear);
            P1 = P1->link;
            break;
        
        case -1:
            rear = Attach(P2->coef, P2->expon, rear);
            P2 = P2->link;
            break;

        case 0:
            rear = Attach(P1->coef + P2->coef, P1->expon, rear);
            P1 = P1->link;
            P2 = P2->link;
        }
    }

    while (P1) 
    {
        rear = Attach(P1->coef, P1->expon, rear);
        P1 = P1->link;
    }
    while (P2)
    {
        rear = Attach(P2->coef, P2->expon, rear);
        P2 = P2->link;
    }

    if (front->link != NULL)
    {
        temp = front;
        front = front->link;
        free(temp);
    }

    return front;
}


// 释放中间产物多项式
void FreePoly(Polynomial P)
{
    Polynomial temp;
    while (P)
    {
        temp = P;
        P = P->link;
        free(temp);
    }
}


// 多项式乘法
Polynomial MultiPoly(Polynomial P1, Polynomial P2)
{
    Polynomial front = NewNode(), cutpoint, temp;
    cutpoint = front;
    Polynomial rP2;
    rP2 = P2;
    int c, e;

    if (P1->coef == 0 || P2->coef == 0)
    {
        return front;
    }

    while (P1)
    {
        while(rP2)
        {
            c = P1->coef * rP2->coef;
            e = P1->expon + rP2->expon;
            while (cutpoint->link && cutpoint->link->expon > e)
            {
                cutpoint = cutpoint->link;
            }
            temp = cutpoint->link;

            if (temp && temp->expon < e)
            {
                cutpoint = Attach(c, e, cutpoint);
                cutpoint->link = temp;
                cutpoint = front;
            }
            else if (temp && temp->expon == e)
            {
                temp->coef = temp->coef + c;
                if (temp->coef == 0)
                {
                    cutpoint->link = temp->link;
                }
                cutpoint = front;
            }
            else if (temp == NULL)
            {
                cutpoint = Attach(c, e, cutpoint);
                cutpoint = front;
            }
            rP2 = rP2->link;
        }

        P1 = P1->link;
        rP2 = P2;
    }
    
    if (front->link != NULL)
    {
        temp = front;
        front = front->link;
        free(temp);
    }

    return front;
}


int main()
{
    Polynomial P1, P2, MP, AP;
    P1 = ReadPoly();
    P2 = ReadPoly();
    MP = MultiPoly(P1, P2);
    AP = AddPoly(P1, P2);
    PrintPoly(MP);
    PrintPoly(AP);

    return 0;
}