#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node_t* Node;
struct node_t {
    int n;
    Node next;
};

typedef bool (*BoolFunction)(int);

void DestroyList(Node list);
Node CopyList(Node list);

Node ListFilter(Node list, BoolFunction Condition);

Node CoolElements(Node* lists, int len);
bool IsDivisableBy3(int n);
bool IsDivisableBy2(int n);
bool IsDivisableBy1(int n);


bool isEven(int n);

Node listCreate(const int* arr, int len);


int main() {
    int arr[3][6] = {{1,2,3,4,5,6}
                    ,{2,3,4,5,8,7}
                    ,{7,1,2,0,1,6}};
    Node* lists = malloc(sizeof(Node)*3);
    for(int i=0; i<3; i++)
    {
        lists[i] = listCreate(arr[i], 6);
    }

    Node list1 = ListFilter(NULL, isEven);
    list1 = ListFilter(lists[0], NULL);

    list1 = CoolElements(NULL, 1);
    list1 = CoolElements(lists, 0);
    list1 = CoolElements(lists, -1);
    DestroyList(NULL);


    Node new_list = CoolElements(lists, 3);
    Node ptr = new_list;
    while(ptr){
        printf("%d ", ptr->n);
        ptr = ptr->next;
    }

    for(int i = 0; i<3; i++) {
        DestroyList(lists[i]);
    }

    printf("\nafter:\n");
    ptr = new_list;
    while(ptr){
        printf("%d ", ptr->n);
        ptr = ptr->next;
    }

    DestroyList(new_list);

    return 0;
}
/*
Node listCreate(const int* arr, int len){
    if(!arr || len <=0) return NULL;
    Node list = NULL, last_node = NULL;
    for(int i=0; i<len; i++){
        Node node = malloc(sizeof(*node));
        node->n = arr[i];
        node->next = NULL;

        if(!list){
            list = node;
            last_node = node;
        }
        else{
            last_node->next = node;
            last_node = node;
        }
    }
    return list;
}
*/

Node ListFilter(Node list, BoolFunction Condition){
    // Check input
    if(!list || !Condition) return NULL;

    // Define pointers to list
    Node new_list = NULL, ptr = list, last_node = NULL;

    // Go thorough each node in list
    while(ptr){

        // Check condition
        if(Condition(ptr->n)){

            // Make a new node
            Node node = malloc(sizeof(*node));
            if(!node){
                DestroyList(new_list);
                return NULL;
            }
            node->n = ptr->n;
            node->next = NULL;

            // Add node to list
            if(!new_list){
                new_list = node;
                last_node = node;
            } else{
                last_node->next = node;
                last_node = node;
            }
        }

        ptr = ptr->next;
    }

    return new_list;
}


Node CoolElements(Node* lists, int len){
    // Check input
    if(!lists || len <= 0) return NULL;

    // Define pointers
    Node new_list = NULL, ptr = NULL;

    // Check each list in array
    for(int i = 0; i < len; i++){
        if(!lists[i]){
            DestroyList(new_list);
            return NULL;
        }

        // Filter current list in array
        Node sub_list = NULL;
        switch(i % 3 + 1) {
            case 1:
                sub_list = ListFilter(lists[i], IsDivisableBy1);
                break;
            case 2:
                sub_list = ListFilter(lists[i], IsDivisableBy2);
                break;
            case 3:
                sub_list = ListFilter(lists[i], IsDivisableBy3);
                break;
            default:
                sub_list = NULL;
                DestroyList(new_list);
                break;
        }
        if(!sub_list){
            DestroyList(new_list);
            return NULL;
        }

        // Add the filtered list to the new list
        if(!new_list){
            new_list = CopyList(sub_list);
            ptr = new_list;
        } else{
            ptr->next = CopyList(sub_list);
        }
        DestroyList(sub_list);

        // Adjust pointer to the last node of the new list
        while(ptr->next){
            ptr = ptr->next;
        }
    }

    return new_list;
}

bool IsDivisableBy1(int n){
    return n % 1 == 0;
}
bool IsDivisableBy2(int n){
    return n % 2 == 0;
}
bool IsDivisableBy3(int n){
    return n % 3 == 0;
}

Node CopyList(Node list){

    if(!list) return NULL;
    Node new_list = NULL;
    Node ptr = list, last_node = new_list;
    while(ptr){
        Node node = malloc(sizeof(*node));
        node->n = ptr->n;
        node->next = NULL;
        if(!new_list){
            new_list = node;
            last_node = node;
        }
        else{
            last_node->next = node;
            last_node = last_node->next;
        }
        ptr = ptr->next;
    }

    return new_list;
}
void DestroyList(Node list){
    while(list){
        Node to_delete = list;
        list = list->next;
        free(to_delete);
    }
}

/*
bool isEven(int n){
    if(n%2 == 0) return true;
    return false;
}
 */