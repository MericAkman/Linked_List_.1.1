#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct listNode{
    int val;
    struct listNode* next;
};

struct listNode* Constructor(int val){
    struct listNode* node=(struct listNode*)malloc(sizeof(struct listNode));
    node->val=val;
    node->next=NULL;
    return node;
};

struct listNode* head=NULL;
struct listNode* tail=NULL;

void addNode(int value){
    struct listNode* node = Constructor(value);
    if(head==NULL){
            head=node; tail=node;
    } else{
        tail->next=node; tail=node;
    }
}


//-----------------------------


struct listNode* deleteDublicates(struct listNode* head){
    if(head==NULL) return NULL;

    struct listNode* curr = head;

    while(curr && curr->next){
        struct listNode* temp = curr;
        while(temp->next){
            if(curr->val == temp->next->val){
                struct listNode* deletedNode = temp->next;
                temp->next = deletedNode->next;
                free(deletedNode);
            }
            else{
                temp=temp->next;
            }
        }
        curr = curr->next;
    }
    return head;
};


//-----------------------------


struct listNode* findMiddle(struct listNode* head){
    struct listNode* slow = head;
    struct listNode* fast = head;

    while(fast){
        fast=fast->next->next;
        slow=slow->next;
    }

    return slow;
};


//-----------------------------


struct listNode* merge(struct listNode* list1, struct listNode* list2){
    if(!list1) return list2;
    if(!list2) return list1;

    if (list1->val < list2->val) {
        list1->next = merge(list1->next, list2);
        return list1;
    }

    else {
        list2->next = merge(list1, list2->next);
        return list2;
    }
};


//-----------------------------


struct listNode* mergeSort(struct listNode* head) {
    if (!head || !head->next) return head;

    struct listNode* middle = findMiddle(head);
    struct listNode* nextHalf = middle->next;
    middle->next = NULL;

    struct listNode* left = mergeSort(head);
    struct listNode* right = mergeSort(nextHalf);

    return merge(left, right);
}


//-----------------------------


struct listNode* sortList(struct listNode* head){
    if(!head || !head->next) return head;

    int swapped;
    struct listNode* curr;
    struct listNode* listed = NULL;

    do {
        swapped = 0;
        struct listNode* prev = NULL;
        curr = head;

        while(curr->next != listed){

            if(curr->val > curr->next->val){

                struct listNode* nextNode = curr->next;

                curr->next = nextNode->next;
                nextNode->next = curr;

                if(prev == NULL){
                    head = nextNode;
                } else {
                    prev->next = nextNode;
                }

                prev = nextNode;
                swapped = 1;
            }

            else {
                prev = curr;
                curr = curr->next;
            }
        }
        listed = curr;
    } while(swapped);

    return head;
}


//-----------------------------


struct listNode* insertionSortList(struct listNode* head) {
    if(head==NULL || head->next==NULL)return head;

    struct listNode* curr = head;
    struct listNode* sorted = NULL;

    while(curr){
        struct listNode* nextNode = curr->next;

        if(!sorted || curr->val <= sorted->val){
            curr->next = sorted;
            sorted = curr;
        }
        else{
            struct listNode* prev = sorted;
            while(prev->next && prev->next->val < curr->val){
                prev = prev->next;
            }
            curr->next=prev->next;
            prev->next=curr;
        }
        curr=nextNode;
    }
    return sorted;
}


//-----------------------------


struct listNode* reorderList(struct listNode* head){
    if(head==NULL || head->next==NULL) return head;

    struct listNode* slow = head;
    struct listNode* fast = slow;

    while(fast!=NULL && fast->next!=NULL){
        fast=fast->next->next;
        slow=slow->next;
    }

    struct listNode* prev = NULL;
    struct listNode* curr = slow->next;
    slow->next=NULL;

    while(curr){
        struct listNode* nextNode = curr->next;
        curr->next=prev;
        prev = curr;
        curr = nextNode;
    }

    struct listNode* first = head;
    struct listNode* second = prev;

    struct listNode* nextNodeforFirst;
    struct listNode* nextNodeforSecond;

    while(second){
        nextNodeforFirst = first->next;
        nextNodeforSecond = second->next;

        first->next = second;
        second->next = nextNodeforFirst;

        first = nextNodeforFirst;
        second = nextNodeforSecond;
    }
    return head;
};


//-----------------------------


struct listNode* ReverseList(struct listNode* head){
    struct listNode* prev = NULL;
    struct listNode* curr = head;
    struct listNode* next = NULL;

    while(curr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;

};


//-----------------------------


bool PalindromCheck(struct listNode* head){
    if(head==NULL || head->next==NULL) return true;

        struct listNode* fast=head;
        struct listNode* slow=head;

    while(fast!=NULL && fast->next!=NULL){
        fast=fast->next->next;
        slow=slow->next;
    }

        struct listNode* secondHalf;

    if(fast==NULL){
        secondHalf = ReverseList(slow);
    }

    else{
        secondHalf = ReverseList(slow->next);
    }

        struct listNode* firstHalf = head;
        bool palindrome = true;

    while (secondHalf != NULL) {
        if (firstHalf->val != secondHalf->val) {
            palindrome = false;
            break;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    return palindrome;
};


//-----------------------------


 struct listNode* findFromValue(int value){
    if(head == NULL) return head;

    struct listNode* temp = head;
    while(temp){
        if(temp->val == value) break;
        else{
            temp=temp->next;
        }
    }
    return temp;
};


void reverseBetween(int left, int right) {
    if (left > right) {
        printf("Invalid input: left > right\n");
        return;
    }

    struct listNode* leftNode = findFromValue(left);
    struct listNode* rightNode = findFromValue(right);
    struct listNode* afterRifgtNode = rightNode->next;

    if (leftNode == NULL || rightNode == NULL) {
        printf("Error: one or both values not found.\n");
        return;
    }

    struct listNode* firstHalf = NULL;
    if (head != leftNode) {
        struct listNode* temp = head;
        while (temp && temp->next != leftNode){
            temp = temp->next;
        }
        firstHalf = temp;
    }

    struct listNode* prev = rightNode->next;
    struct listNode* curr = leftNode;
    struct listNode* next = NULL;


    while (curr != afterRifgtNode) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    if (firstHalf)
        firstHalf->next = prev;
    else
        head = prev;
};


//-----------------------------


void oddEvenLinkedList(){
    if(head==NULL) return;

    struct listNode* oddNodes=NULL;
    struct listNode* evenNodes=NULL;
    struct listNode* temp = head;
    struct listNode* firstOddNode = NULL;
    struct listNode* firstEvenNode = NULL;


    while(temp){
        if(temp->val %2 ==0){
            if(firstEvenNode == NULL){
                firstEvenNode = temp;
                evenNodes =  temp;
            }
            else{
                evenNodes->next = temp;
                evenNodes = temp;
            }
        }

        else{
            if(firstOddNode == NULL){
                firstOddNode = temp;
                oddNodes = temp;
            }
            else{
                oddNodes->next = temp;
                oddNodes = temp;
            }
        }
        temp = temp->next;
    }

    if(head->val %2 == 0){
        evenNodes->next=firstOddNode;
        if(oddNodes) oddNodes->next = NULL;
    }
    else{
        oddNodes->next=firstEvenNode;
        if(evenNodes) evenNodes->next = NULL;
    }
};


//-----------------------------


struct listNode* getTail(){
    struct listNode* temp = head;

    while(temp->next){
        temp=temp->next;
    }
    return temp;
}


void rotateRight(int k){
    if(head==NULL) return;

    struct listNode* tail = NULL;

    for(int i=0;i<k;i++){
        struct listNode* beforeTail = head;
        tail = getTail();

        while(beforeTail->next != tail){
            beforeTail=beforeTail->next;
        }
        tail->next = head;
        head = tail;
        beforeTail->next = NULL;
    }
}


//-----------------------------


int getLength(struct listNode* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}


void helper(struct listNode* head, int* arr, int* result, int* index) {
    if (head == NULL) return;

    helper(head->next, arr, result, index);


    (*index)--;


    for (int j = *index + 1; arr[j] != -1; j++) {
        if (arr[j] > head->val) {
            result[*index] = arr[j];
            return;
        }
    }
    result[*index] = 0;
}


int* nextLargerNodes(struct listNode* head, int* returnSize) {
    if (head == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int len = getLength(head);
    *returnSize = len;

    int* result = (int*)calloc(len, sizeof(int));
    int* arr = (int*)malloc((len + 1) * sizeof(int));


    struct listNode* temp = head;
    for (int i = 0; i < len; i++) {
        arr[i] = temp->val;
        temp = temp->next;
    }
    arr[len] = -1;

    int index = len;
    helper(head, arr, result, &index);

    free(arr);
    return result;
}


//-----------------------------


int** split(struct listNode* head, int* length, int* k) {
    struct listNode* temp = head;

    int base_size = *length / *k;
    int remainder = *length % *k;

    int** result = (int**)malloc(sizeof(int*) * (*k));
    if (!result) return NULL;

    for (int i = 0; i < *k; i++) {
        int part_size = base_size + (i < remainder ? 1 : 0);
        result[i] = (int*)calloc(part_size, sizeof(int));

        for (int j = 0; j < part_size; j++) {
            if (temp) {
                result[i][j] = temp->val;
                temp = temp->next;
            }
            else {
                result[i][j] = 0;
            }
        }
    }
    return result;
}

//-----------------------------


struct ListNode** splitListToParts(struct ListNode* head, int k, int* returnSize) {
    *returnSize = k;

    struct ListNode** parts = malloc(sizeof(struct ListNode*) * k);
    if (!parts) return NULL;

    int length = 0;
    struct ListNode* temp = head;
    while (temp) {
        length++;
        temp = temp->next;
    }

    int base_size = length / k;
    int remainder = length % k;

    temp = head;
    for (int i = 0; i < k; i++) {
        struct ListNode* part_head = temp;
        struct ListNode* prev = NULL;

        int part_len = base_size + (i < remainder ? 1 : 0);

        for (int j = 0; j < part_len; j++) {
            prev = temp;
            if (temp) temp = temp->next;
        }

        if (prev) prev->next = NULL;

        parts[i] = part_head;
    }

    return parts;
}


//-----------------------------


void printList(){
    struct listNode* temp = head;
    while(temp){
        printf("%d ",temp->val);
        temp=temp->next;
    }
    printf("\n");
}

//-----------------------------

int main(){
    addNode(1);
    addNode(2);
    addNode(3);
    addNode(4);
    addNode(5);
    printList();

    /*head = deleteDublicates(head);
    printList();

    head = insertionSortList(head);
    printList();

    head = reorderList(head);
    printList();

    head = sortList(head);
    printList();

    bool check = PalindromCheck(head);
    if(check){
        printf("\nIt is a polindrom list\n");
    }
    else{
        printf("\nIt is not a polindrom list\n");
    }

    reverseBetween(2,4);
    printList();


    oddEvenLinkedList();
    printList();
    */

    /*
    rotateRight(3);
    printList();
    */

    head = nextLargerNodes(head,0);



}


