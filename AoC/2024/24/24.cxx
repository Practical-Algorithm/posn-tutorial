#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: Advent of Code 2024 Day 24
 * Resource: https://adventofcode.com/2024/day/24
 * Topic: Graph, DAG
 */

enum Operation
{
  AND,
  OR,
  XOR
};

map<string, int> mappingNameToId;
int availableId = 0;

struct Node
{
  bool value;
  bool calculated;

  int id;
  int indegree;
  Operation op;
  vector<int> inDependents;
  vector<int> outDependents;

  Node(int id, bool value) : id(id), value(value), calculated(true)
  {
    indegree = 0;
  }
  Node(int id) : id(id), calculated(false)
  {
    indegree = 0;
  }

  void setOperation(Operation op)
  {
    this->op = op;
  }
};
Node *nodes[512];

int addId(string name)
{
  if (mappingNameToId.find(name) != mappingNameToId.end())
    return mappingNameToId[name];
  return mappingNameToId[name] = availableId++;
}

Node *getNode(int id)
{
  if (nodes[id] == NULL)
    return nodes[id] = new Node(id);
  return nodes[id];
}

int main()
{
  char name[8];
  int n = 45;
  for (int i = 0; i < 2 * n; i++)
  {
    int value;
    scanf("%s %d", name, &value);
    int id = addId(name);

    nodes[id] = new Node(id, value);
  }

  // fjm XOR gqp -> z14
  int query = 222;
  char a[8], op[8], b[8], c[8], d[8];
  vector<pair<string, int>> Z;
  for (int i = 0; i < query; i++)
  {
    scanf("%s %s %s %s %s", a, op, b, c, d);

    int idA = addId(a);
    int idC = addId(c);
    int idD = addId(d);

    if (d[0] == 'z')
    {
      Z.emplace_back(d, idD);
    }
    Operation operation;
    if (op[0] == 'A')
      operation = AND;
    else if (op[0] == 'O')
      operation = OR;
    else
      operation = XOR;

    Node *nodeA = getNode(idA);
    Node *nodeC = getNode(idC);
    Node *nodeD = getNode(idD);

    nodeD->indegree += 2;
    nodeD->inDependents.push_back(idA);
    nodeD->inDependents.push_back(idC);
    nodeD->setOperation(operation);

    nodeA->outDependents.push_back(idD);
    nodeC->outDependents.push_back(idD);
  }

  queue<int> q;
  for (int i = 0; i < 2 * n; i++)
  {
    if (nodes[i] != NULL && nodes[i]->indegree == 0 && nodes[i]->calculated)
      q.push(i);
  }

  while (!q.empty())
  {
    int id = q.front();
    q.pop();

    Node *node = nodes[id];

    printf("Found node %d\n", id);

    if (!node->calculated)
    {
      Node *nodeA = nodes[node->inDependents[0]];
      Node *nodeB = nodes[node->inDependents[1]];

      if (node->op == AND)
        node->value = nodeA->value && nodeB->value;
      else if (node->op == OR)
        node->value = nodeA->value || nodeB->value;
      else
        node->value = nodeA->value ^ nodeB->value;

      printf("Calculated node %d\n", id);
      printf("Operation: %d\n", node->op);
      printf("Value: %d\n", node->value);

      node->calculated = true;
    }

    for (int i = 0; i < node->outDependents.size(); i++)
    {
      int outId = node->outDependents[i];
      Node *outNode = nodes[outId];
      outNode->indegree--;

      printf("Decrease indegree of %d to %d\n", outId, outNode->indegree);

      if (outNode->indegree == 0)
        q.push(outId);
    }
  }

  for (int i = 0; i < Z.size(); i++)
  {
    printf("%s %d\n", Z[i].first.c_str(), nodes[Z[i].second]->value);
  }
}