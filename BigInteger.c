#include "BigInteger.h"
#include <stdio.h>
#include <stdlib.h>

struct BigInteger initializeList()
{
    struct BigInteger list;
    list.head = NULL;
    return list;
}

void insertDigit(struct BigInteger list, int digit)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = digit;
    newNode->next = list.head;
    list.head = newNode;
}

// Function to compare two big integers represented as linked lists
int compareLists(struct BigInteger num1, struct BigInteger num2)
{
    struct Node* current1 = num1.head;
    struct Node* current2 = num2.head;

    while (current1 != NULL && current2 != NULL)
    {
        if (current1->data > current2->data)
        {
            return 1;
        }

        else if (current1->data < current2->data)
        {
            return -1;
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    if (current1 != NULL)
    {
        return 1;
    }

    else if (current2 != NULL)
    {
        return -1;
    }

    return 0;
}

void printList(struct BigInteger list)
{
    struct Node* current = list.head;
    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

struct BigInteger add(struct BigInteger num1, struct BigInteger num2)
{
    struct BigInteger result = initializeList();
    struct Node* current1 = num1.head;
    struct Node* current2 = num2.head;
    int carry = 0;

    while (current1 != NULL || current2 != NULL || carry != 0)
    {
        int sum = carry;

        if (current1 != NULL)
        {
            sum += current1->data;
            current1 = current1->next;
        }

        if (current2 != NULL)
        {
            sum += current2->data;
            current2 = current2->next;
        }

        carry = sum / 10;
        sum = sum % 10;

        insertDigit(result, sum);
    }

    // If there's a carry after the loop, add it as a new digit
    if (carry > 0)
    {
        insertDigit(result, carry);
    }

    return result;
}



// Function to subtract two big integers represented as linked lists
struct BigInteger sub(struct BigInteger num1, struct BigInteger num2)
{
    struct BigInteger result = initializeList();
    struct Node* current1 = num1.head;
    struct Node* current2 = num2.head;
    int borrow = 0;

    while (current1 != NULL || current2 != NULL)
    {
        int diff = borrow;

        if (current1 != NULL)
        {
            diff += current1->data;
            current1 = current1->next;
        }

        if (current2 != NULL)
        {
            diff -= current2->data;
            current2 = current2->next;
        }

        if (diff < 0)
        {
            diff += 10;
            borrow = -1;
        }

        else
        {
            borrow = 0;
        }

        insertDigit(result, diff);
    }

    while (result.head != NULL && result.head->data == 0)
    {
        struct Node* temp = result.head;
        result.head = result.head->next;
        free(temp);
    }

    return result;
}

struct BigInteger mul(struct BigInteger num1, struct BigInteger num2)
{
    struct BigInteger result = initializeList();
    struct Node* current1 = num1.head;

    while (current1 != NULL)
    {
        int carry = 0;
        struct BigInteger tempResult = initializeList();
        struct Node* current2 = num2.head;

        while (current2 != NULL || carry != 0)
        {
            int product = carry;

            if (current2 != NULL)
            {
                product += current1->data * current2->data;
                current2 = current2->next;
            }

            carry = product / 10;
            product = product % 10;

            insertDigit(tempResult, product);
        }

        result = add(result, tempResult);
        freeList(tempResult);

        current1 = current1->next;
    }

    return reverse(result);
}
// Function to reverse a linked list
struct BigInteger reverse(struct BigInteger list)
{
    struct Node* prev = NULL;
    struct Node* current = list.head;
    struct Node* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list.head = prev;

    return list;
}


// Function to divide two big integers represented as linked lists
struct BigInteger div1(struct BigInteger num1, struct BigInteger num2)
{
    struct BigInteger result = initializeList();
    struct BigInteger remainder = initializeList();
    struct Node* current = num1.head;

    while (current != NULL)
    {
        insertDigit(remainder, current->data);

        while (compareLists(remainder, num2) >= 0)
        {
            struct BigInteger temp = sub(remainder, num2);

            // Increment the last digit of the quotient
            struct Node* lastDigit = result.head;
            struct Node* prev = NULL;
            while (lastDigit != NULL)
            {
                lastDigit->data++;
                prev = lastDigit;
                lastDigit = lastDigit->next;
            }

            // Check for carry
            if (prev != NULL && prev->data > 9)
            {
                prev->data %= 10;
                insertDigit(result, 1);
            }

            freeList(remainder);
            remainder = temp;
        }

        current = current->next;
    }

    // If the result is empty, insert a zero
    if (result.head == NULL)
    {
        insertDigit(result, 0);
    }

    freeList(remainder);

    return result;
}



struct BigInteger mod(struct BigInteger num1, struct BigInteger num2)
{
    struct BigInteger remainder = initializeList();
    struct Node* current = num1.head;

    while (current != NULL)
    {
        insertDigit(remainder, current->data);

        while (compareLists(remainder, num2) >= 0)
        {
            struct BigInteger temp = sub(remainder, num2);
            freeList(remainder);
            remainder = temp;
        }

        current = current->next;
    }

    return remainder;
}

void freeList(struct BigInteger list)
{
    struct Node* current = list.head;
    while (current != NULL)
    {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

}
