#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <stdbool.h>

typedef enum {
    RUSSIA = 1,
    USA,
    MAURITIUS,
    EGYPT,
    ISRAEL,
    TURKEY,
    UAE
} Country;

typedef struct Node {
    Country data;
    struct Node *left;
    struct Node *right;
} Node;

const char* countryToString(Country c) {
    switch(c) {
        case RUSSIA:   return "Russia";
        case USA:      return "USA";
        case MAURITIUS:return "Mauritius";
        case EGYPT:    return "Egypt";
        case ISRAEL:   return "Israel";
        case TURKEY:   return "Turkey";
        case UAE:      return "UAE";
        default:       return "???";
    }
}

Node* createNode(Country value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* addNode(Node* root, Country value) {
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = addNode(root->left, value);
    else if (value > root->data)
        root->right = addNode(root->right, value);
    else
        printf("Страна уже есть в дереве!\n");
    return root;
}

Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, Country value) {
    if (root == NULL) {
        printf("Страна не найдена!\n");
        return NULL;
    }
    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

bool findValue(Node* root, Country value) {
    if (root == NULL) return false;
    if (root->data == value) return true;
    if (value < root->data)
        return findValue(root->left, value);
    return findValue(root->right, value);
}

void printTree(Node* root, int level) {
    if (root == NULL) return;
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%s\n", countryToString(root->data));
    printTree(root->left, level + 1);
}

bool isBTree(Node* root) {
    if (root == NULL) return true;
    int children = (root->left != NULL) + (root->right != NULL);
    if (children == 1) return false;
    return isBTree(root->left) && isBTree(root->right);
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    Node* root = NULL;
    int choice, val;

    while (1) {
        printf("\nМЕНЮ\n");
        printf("1 - Добавить страну\n");
        printf("2 - Показать дерево\n");
        printf("3 - Удалить страну\n");
        printf("4 - Проверить, B-дерево ли это\n");
        printf("5 - Выход\n");
        printf("Выбор: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("\n1-Russia,2-USA,3-Mauritius,4-Egypt,5-Israel,6-Turkey,7-UAE\n");
                printf("Куда вы хотите отправиться сегодня (номер): ");
                scanf("%d", &val);
                if (val < 1 || val > 7) {
                    printf("Ошибка: номер от 1 до 7\n");
                    break;
                }
                root = addNode(root, (Country)val);
                break;

            case 2:
                if (root == NULL)
                    printf("Дерево пусто!\n");
                else
                    printTree(root, 0);
                break;

            case 3:
                if (root == NULL) {
                    printf("Дерево пусто!\n");
                    break;
                }
                printf("Куда вы хотите отправиться сегодня (номер): ");
                scanf("%d", &val);
                if (val < 1 || val > 7) {
                    printf("Ошибка: номер от 1 до 7\n");
                    break;
                }
                if (!findValue(root, (Country)val))
                    printf("Такой страны нет в дереве!\n");
                else
                    root = deleteNode(root, (Country)val);
                break;

            case 4:
                if (isBTree(root))
                    printf("Да: дерево является B-деревом\n");
                else
                    printf("Нет: дерево не является B-деревом\n");
                break;

            case 5:
                freeTree(root);
                printf("Программа завершена.\n");
                return 0;

            default:
                printf("Неверный выбор! Введите 1-5\n");
        }
    }
    return 0;
}
