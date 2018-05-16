#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct node_t* Node;
struct node_t {
    int n;
    Node next;
};

typedef bool (*boolFunction)(int);

Node listFilter(Node list, boolFunction condition);
bool isEven(int n);
void destroyList(Node list);
Node listCreate(int arr[], int len);
Node coolElements(Node* lists, int len);
bool isDivisableBy3(int n);
bool isDivisableBy2(int n);
bool isDivisableBy1(int n);

int main() {
    int arr[3][6] = {{1,2,3,4,5,6}
                    ,{2,3,4,5,8,7}
                    ,{7,1,2,0,1,6}};
    Node* lists = malloc(sizeof(Node)*3);
    for(int i=0; i<3; i++)
    {
        lists[i] = listCreate(arr[i], 6);
    }

    Node new_list = coolElements(lists, 3);

    Node ptr = new_list;

    while(ptr){
        printf("%d ", ptr->n);
        ptr = ptr->next;
    }

    destroyList(new_list);
    for(int i =0; i<3; i++){
        destroyList(lists[i]);
    }

    return 0;
}

Node listFilter(Node list, boolFunction condition){
    if(!list || !condition) return NULL;
    Node new_list = NULL;
    Node ptr = list;
    Node prev = NULL;
    while(ptr){
        if(condition(ptr->n)){
            Node node = malloc(sizeof(*node));
            if(!node){
                destroyList(new_list);
                return NULL;
            }
            node->n = ptr->n;
            node->next = NULL;
            if(!new_list){
                new_list = node;
                prev = node;
            }
            else{
                prev->next = node;
                prev = node;
            }
        }
        ptr = ptr->next;
    }
    return new_list;
}

bool isEven(int n){
    if(n%2 == 0) return true;
    return false;
}

void destroyList(Node list){
    while(list){
        Node toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

Node listCreate(int* arr, int len){
    Node list = NULL, prev = NULL;
    for(int i=0; i<len; i++){
        Node node = malloc(sizeof(*node));
        node->n = arr[i];
        node->next = NULL;

        if(!list){
            list = node;
            prev = node;
        }
        else{
            prev->next = node;
            prev = node;
        }
    }
    return list;
}

Node coolElements(Node* lists, int len){
    if(!lists) return NULL;
    Node new_list = NULL, ptr = NULL;
    for(int i=0; i<len; i++){
        Node sub_list = NULL;
        if(!lists[i]){
            destroyList(new_list);
            return NULL;
        }
        switch(i%3+1) {
            case 1:
                sub_list = listFilter(lists[i], isDivisableBy1);
                break;
            case 2:
                sub_list = listFilter(lists[i], isDivisableBy2);
                break;
            case 3:
                sub_list = listFilter(lists[i], isDivisableBy3);
                break;
            default:
                sub_list = NULL;
                break;
        }
        if(!sub_list){
            destroyList(sub_list);
            destroyList(new_list);
            return NULL;
        }
        if(!new_list){
            new_list = sub_list;
            ptr = sub_list;
        }
        else{
            ptr->next = sub_list;
        }
        while(ptr->next){
            ptr = ptr->next;
        }
    }
    return new_list;
}
bool isDivisableBy1(int n){
    return n % 1 == 0;
}
bool isDivisableBy2(int n){
    return n % 2 == 0;
}
bool isDivisableBy3(int n){
    return n % 3 == 0;
}