#include <iostream>
#include <string>
#include <stack>
using namespace std;

// �������Ľڵ�ṹ
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// �������������ڹ���������
TreeNode* buildTree(string& expression) {
    stack<TreeNode*> nodeStack;
    TreeNode* root = nullptr;
    TreeNode* current = nullptr;
    int value = 0;
    bool isParsingValue = false;

    for (char currentChar : expression) {
        if (isdigit(currentChar)) {
            value = value * 10 + (currentChar - '0');
            isParsingValue = true;
        } else if (currentChar == '(') {
            if (isParsingValue) {
                TreeNode* newNode = new TreeNode(value);
                if (!root) {
                    root = newNode;
                } else {
                        current->left = newNode;
                    // if (current->left == nullptr) {
                    //     current->left = newNode;
                    // } else {
                    //     current->right = newNode;
                    // }
                }
                nodeStack.push(newNode);
                current = newNode;
                value = 0;
                isParsingValue = false;
            }
        } else if (currentChar == ',') {
            if (isParsingValue) {
                TreeNode* newNode = new TreeNode(value);
                current->left = newNode;
                value = 0;
                isParsingValue = false;
            }
        } else if (currentChar == ')') {
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                if(isParsingValue)
                {
                    cout<<current->value<<endl;
                    TreeNode* newNode=new TreeNode(value);
                    current->right = newNode;
                    value = 0;
                    isParsingValue = false;
                }                
                nodeStack.pop();
                if (!nodeStack.empty()) {
                    current = nodeStack.top();
                }
            }
        }
    }

    return root;
}

// ���������ӡ������
void printTree(TreeNode* root) {
    if (root) {
        printTree(root->left);
        cout << root->value << " ";
        printTree(root->right);
    }
}

int main() {
    string expression = "1(2,3(4,5(6,7)))";
    TreeNode* root = buildTree(expression);

    cout << "������������";
    printTree(root);
    
    // �ͷ��ڴ�
    delete root;

    return 0;
}
