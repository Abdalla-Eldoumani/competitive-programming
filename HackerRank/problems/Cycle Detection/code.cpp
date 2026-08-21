#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class SinglyLinkedListNode {
    public:
        int data;
        SinglyLinkedListNode *next;

        SinglyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
        }
};


int has_cycle(SinglyLinkedListNode* head) {
    if (head == nullptr) {
        return 0;
    }

    SinglyLinkedListNode* slow = head;
    SinglyLinkedListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1;
        }
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    if (!(cin >> tests)) return 0;
    while (tests--) {
        int index;
        cin >> index;

        int n;
        cin >> n;

        SinglyLinkedListNode *head = nullptr, *tail = nullptr;
        vector<SinglyLinkedListNode*> nodes;
        for (int i = 0, val; i < n; ++i) {
            cin >> val;
            auto *p = new SinglyLinkedListNode(val);
            nodes.push_back(p);
            if (!head) head = p;
            else       tail->next = p;
            tail = p;
        }

        if (index >= 0 && index < (int)nodes.size())
            tail->next = nodes[index];

        cout << has_cycle(head) << '\n';
    }
    return 0;
}