//����ó ���α׷�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_NAME_SIZE 100
#define MAX_NUMBER_SIZE 200

int count = 0;
int* pcount = &count; //��ȭ��ȣ�� ������ ���� ���� ������ ����

//������ ����
typedef struct {
    char name[MAX_NAME_SIZE]; //Ű�ʵ�
    char number[MAX_NUMBER_SIZE];
}element;

//����� ����
typedef struct TreeNode {
    element key;
    struct TreeNode* left, * right;
}TreeNode;

//���� e1 < e2�̸� -1 ��ȯ
//���� e1 == e2�̸� 0 ��ȯ
//���� e1 > e2�̸� 1 ��ȯ

int compare(element e1, element e2) {
    return strcmp(e1.name, e2.name);
}

//���� Ž�� Ʈ�� ��� �Լ�
void display(TreeNode* p) {
    if (p) {
        display(p->left);
        printf("%s:%s\n", p->key.name, p->key.number);
        count++;
        display(p->right);
    }
}

//���� Ž�� Ʈ�� Ž�� �Լ�
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
    //Ž���� �������� ��� NULL��ȯ
}


TreeNode* new_node(element item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

//���� Ž�� Ʈ�� ���� �Լ�
TreeNode* insert_node(TreeNode* node, element key) {
    //Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
    if (node == NULL) return new_node(key);
    //�׷��� ������ ��ȯ������ Ʈ���� ��������.
    if (compare(key, node->key) < 0)
        node->left = insert_node(node->left, key);
    else if (compare(key, node->key) > 0)
        node->right = insert_node(node->right, key);
    else {
        node->key = key; //���� key�� ������ ���� �����.
    }
    //��Ʈ �����͸� ��ȯ�Ѵ�.
    return node;
}
TreeNode* max_value_node(TreeNode* node) {
    TreeNode* current = node;
    //����Ʈ�������� ������ �ܸ� ��带 ã���� ������
    while (current->right != NULL)
        current = current->right;
    return current;
}

//���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ� ���ο� ��Ʈ ��带 ��ȯ�Ѵ�.
TreeNode* delete_node(TreeNode* root, element key) {
    int i = 0;
    if (root == NULL) {
        return root;
    }
    //���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
    if (compare(key, root->key) < 0)
        root->left = delete_node(root->left, key);
    //���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
    if (compare(key, root->key) > 0)
        root->right = delete_node(root->right, key);
    //Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
    if (compare(key,root->key)==0){
        //ù ��°�� �� ��° ���
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
        else { //�� ��°�� ���
            TreeNode* temp = max_value_node(root->left);

            //�߿� ��ȸ�� �İ� ��带 �����Ѵ�.
            root->key = temp->key;
            //���� ��ȸ�� �İ��带 �����Ѵ�.
            root->left = delete_node(root->left, temp->key);
        }
    }
    return root;
}

//���� Ž�� Ʈ���� �翵�ϴ� ���� ���� ���α׷�
int main(void) {
    char c;
    element e;
    TreeNode* root = NULL;
    TreeNode* tmp;

    do {
        printf("����(i), Ž��(s), ���(p), ����(d), ����(q): ");
        c = getchar();
        getchar();  //����Ű ����
        switch (c) {
        case 'i':
            printf("�̸�: ");
            gets_s(e.name, MAX_NAME_SIZE);
            printf("��ȭ��ȣ: ");
            gets_s(e.number, MAX_NUMBER_SIZE);
            root = insert_node(root, e);
            break;
        case 'd':
            printf("�̸�: ");
            gets_s(e.name, MAX_NAME_SIZE);
            root = delete_node(root, e);
            break;
        case 'p':
            count = 0; //�ʱ�ȭ
            display(root);
            printf("��ȭ��ȣ�� ����: %d\n", count);
            printf("\n");
            break;
        case 's':
            printf("�̸�: ");
            gets_s(e.name, MAX_NAME_SIZE);
            tmp = search(root, e);
            if (tmp != NULL)
                printf("\'%s\'�� ��ȭ��ȣ: %s\n", tmp->key.name, tmp->key.number);
            break;
        }
    } while (c != 'q');
    return 0;
}