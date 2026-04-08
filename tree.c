#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <stdbool.h>

// Перечисление стран (1-7)
typedef enum {
    RUSSIA = 1,
    USA,
    CHINA,
    GERMANY,
    FRANCE,
    JAPAN,
    UK
} Country;

// Структура узла
typedef struct Node {
    Country data;
    struct Node *left;
    struct Node *right;
} Node;

// Преобразование enum в строку
const char* countryToString(Country c) {
    switch(c) {
        case RUSSIA: return "Russia";
        case USA:    return "USA";
        case CHINA:  return "China";
        case GERMANY:return "Germany";
        case FRANCE: return "France";
        case JAPAN:  return "Japan";
        case UK:     return "UK";
        default:     return "???";
    }
}

// Создание нового узла
Node* createNode(Country value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Добавление узла
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

// Поиск минимального узла
Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Удаление узла с сохранением порядка
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
        // Узел найден
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
        // Два потомка
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Поиск значения в дереве
bool findValue(Node* root, Country value) {
    if (root == NULL) return false;
    if (root->data == value) return true;
    if (value < root->data)
        return findValue(root->left, value);
    return findValue(root->right, value);
}

// Визуализация дерева
void printTree(Node* root, int level) {
    if (root == NULL) return;
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%s\n", countryToString(root->data));
    printTree(root->left, level + 1);
}

// Проверка B-дерева
bool isBTree(Node* root) {
    if (root == NULL) return true;
    int children = (root->left != NULL) + (root->right != NULL);
    if (children == 1) return false;  // узел с одним потомком
    return isBTree(root->left) && isBTree(root->right);
}

// Освобождение памяти
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
            case 1:  // Добавление
                printf("\n1-Russia,2-USA,3-China,4-Germany,5-France,6-Japan,7-UK\n");
                printf("Введите номер страны: ");
                scanf("%d", &val);
                if (val < 1 || val > 7) {
                    printf("Ошибка: номер от 1 до 7\n");
                    break;
                }
                root = addNode(root, (Country)val);
                break;

            case 2:  // Визуализация
                if (root == NULL)
                    printf("Дерево пусто!\n");
                else
                    printTree(root, 0);
                break;

            case 3:  // Удаление
                if (root == NULL) {
                    printf("Дерево пусто!\n");
                    break;
                }
                printf("Введите номер страны для удаления: ");
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

            case 4:  // Проверка на B-дерево
                if (isBTree(root))
                    printf("Да: дерево является B-деревом\n");
                else
                    printf("Нет: дерево не является B-деревом\n");
                break;

            case 5:  // Выход
                freeTree(root);
                printf("Программа завершена.\n");
                return 0;

            default:
                printf("Неверный выбор! Введите 1-6\n");
        }
    }
    return 0;
}
