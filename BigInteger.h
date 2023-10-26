
#ifndef BigInteger_h
#define BigInteger_h

struct Node
{
    int data;
    struct Node* next;
};

struct BigInteger
{
    struct Node* head;
};

struct BigInteger initializeList();
void insertDigit(struct BigInteger list, int digit);
void printList(struct BigInteger list);
struct BigInteger add(struct BigInteger num1, struct BigInteger num2);
struct BigInteger sub(struct BigInteger num1, struct BigInteger num2);
struct BigInteger mul(struct BigInteger num1, struct BigInteger num2);
struct BigInteger div1(struct BigInteger num1, struct BigInteger num2);
struct BigInteger mod(struct BigInteger num1, struct BigInteger num2);
struct BigInteger reverse(struct BigInteger list);
void freeList(struct BigInteger list);

#endif
