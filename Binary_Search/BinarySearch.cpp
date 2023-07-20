//연락처 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_NAME_SIZE 100
#define MAX_NUMBER_SIZE 200

int count = 0;
int* pcount = &count; //전화번호부 개수를 세기 위한 포인터 변수

//데이터 형식
typedef struct {
    char name[MAX_NAME_SIZE]; //키필드
    char number[MAX_NUMBER_SIZE];
}element;

//노드의 구조
typedef struct TreeNode {
    element key;
    struct TreeNode* left, * right;
}TreeNode;

//만약 e1 < e2이면 -1 반환
//만약 e1 == e2이면 0 반환
//만약 e1 > e2이면 1 반환

int compare(element e1, element e2) {
    return strcmp(e1.name, e2.name);
}

//이진 탐색 트리 출력 함수
void display(TreeNode* p) {
    if (p) {
        display(p->left);
        printf("%s:%s\n", p->key.name, p->key.number);
        count++;
        display(p->right);
    }
}

//이진 탐색 트리 탐색 함수
TreeNode* search(TreeNode* root, element key) {
    TreeNode* p = root;
    while (p != NULL) {
        if (compare(key, p->key) == 0)
            return p;
        else if (compare(key, p->key) < 0)
            p = p->left;
        else if (compare(key, p->key) > 0)
            p = p->right;
    }
    return p;
    //탐색에 실패했을 경우 NULL반환
}


TreeNode* new_node(element item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

//이진 탐색 트리 삽입 함수
TreeNode* insert_node(TreeNode* node, element key) {
    //트리가 공백이면 새로운 노드를 반환한다.
    if (node == NULL) return new_node(key);
    //그렇지 않으면 순환적으로 트리를 내려간다.
    if (compare(key, node->key) < 0)
        node->left = insert_node(node->left, key);
    else if (compare(key, node->key) > 0)
        node->right = insert_node(node->right, key);
    else {
        node->key = key; //같은 key가 있으면 덮어 씌운다.
    }
    //루트 포인터를 반환한다.
    return node;
}
TreeNode* max_value_node(TreeNode* node) {
    TreeNode* current = node;
    //왼쪽트리에서의 오른쪽 단말 노드를 찾으러 내려감
    while (current->right != NULL)
        current = current->right;
    return current;
}

//이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 새로운 루트 노드를 반환한다.
TreeNode* delete_node(TreeNode* root, element key) {
    int i = 0;
    if (root == NULL) {
        return root;
    }
    //만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
    if (compare(key, root->key) < 0)
        root->left = delete_node(root->left, key);
    //만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
    if (compare(key, root->key) > 0)
        root->right = delete_node(root->right, key);
    //키가 루트와 같으면 이 노드를 삭제하면 됨
    if (compare(key,root->key)==0){
        //첫 번째나 두 번째 경우
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        else { //세 번째의 경우
            TreeNode* temp = max_value_node(root->left);

            //중외 순회시 후계 노드를 복사한다.
            root->key = temp->key;
            //중위 순회시 후계노드를 삭제한다.
            root->left = delete_node(root->left, temp->key);
        }
    }
    return root;
}

//이진 탐색 트리를 사영하는 영어 사전 프로그램
int main(void) {
    char c;
    element e;
    TreeNode* root = NULL;
    TreeNode* tmp;

    do {
        printf("삽입(i), 탐색(s), 출력(p), 삭제(d), 종료(q): ");
        c = getchar();
        getchar();  //엔터키 제거
        switch (c) {
        case 'i':
            printf("이름: ");
            gets_s(e.name, MAX_NAME_SIZE);
            printf("전화번호: ");
            gets_s(e.number, MAX_NUMBER_SIZE);
            root = insert_node(root, e);
            break;
        case 'd':
            printf("이름: ");
            gets_s(e.name, MAX_NAME_SIZE);
            root = delete_node(root, e);
            break;
        case 'p':
            count = 0; //초기화
            display(root);
            printf("전화번호부 개수: %d\n", count);
            printf("\n");
            break;
        case 's':
            printf("이름: ");
            gets_s(e.name, MAX_NAME_SIZE);
            tmp = search(root, e);
            if (tmp != NULL)
                printf("\'%s\'의 전화번호: %s\n", tmp->key.name, tmp->key.number);
            break;
        }
    } while (c != 'q');
    return 0;
}