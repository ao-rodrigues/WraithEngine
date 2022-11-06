//
// StackLinkedList.h
// WraithEngine
//
// Created by Andre Rodrigues on 06/11/2022.
//

#pragma once

namespace Wraith {
    template <typename T>
    class StackLinkedList {
    public:
        union Node {
            T data;
            Node* next;
        };

        StackLinkedList() = default;

        void Push(Node* newNode) {
            newNode->next = head;
            head = newNode;
        }

        Node* Pop() {
            Node* top = head;
            head = head->next;
            return top;
        }

        Node* head;
    };
}
