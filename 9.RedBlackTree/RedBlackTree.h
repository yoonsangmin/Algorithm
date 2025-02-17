#pragma once

#include <iostream>
#include <string>
#include "Node.h"

// 레드 블랙 트리 클래스.
class RedBlackTree
{
public:
    RedBlackTree();
    ~RedBlackTree();

    // 노드 검색 함수.
    bool Find(int data, Node** outNode);

    // 노드 추가 함수.
    bool Insert(int data);

private:
    // 노드 생성 함수.
    Node* CreateNode(int data, Color color);

    // 노드 검색 재귀 함수.
    bool FindRecursive(Node* node, Node** outNode, int data);

    // 노드 추가 함수 (새 노드 전달).
    void Insert(Node* newNode);

    // 트리에 노드를 추가하는 재귀 함수.
    void InsertRecursive(Node* node, Node* newNode);

    // 노드 삽입 후 재정렬을 처리하는 함수.
    void RestructureAfterInsert(Node* newNode);

    // 좌회전 함수.
    // node: 회전의 기준점(pivot).
    void RotateToLeft(Node* node);

    // 우회전 함수.
    // node: 회전의 기준점(pivot).
    void RotateToRight(Node* node);

private:
    // 루트 노드.
    Node* root = nullptr;

    // Nil 노드.
    static Node* nil;
};