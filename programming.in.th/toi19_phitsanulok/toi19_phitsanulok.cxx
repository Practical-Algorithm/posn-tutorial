#include <bits/stdc++.h>
using namespace std;
/**
 * Problem: toi19_phitsanulok
 * Resource: https://programming.in.th/tasks/toi19_phitsanulok
 * Topic: Graph, Bitmask
 */

// Maximum number of poison states b/c there's 19 poisons
const int maximumPoisonState = 1 << 19;

struct Apple
{
  int weight;
  int poisonMask;
  int antidoteMask;

  Apple(int weight, int poisonMask, int antidoteMask) : weight(weight), poisonMask(poisonMask), antidoteMask(antidoteMask) {}
};

struct PoisonState
{
  int poisonMask;
  int weight;

  PoisonState(int weight, int poisonMask) : poisonMask(poisonMask), weight(weight) {}
  bool operator<(const PoisonState &other) const
  {
    return weight > other.weight;
  }
};

int main()
{
  int n, s;
  scanf("%d %d", &n, &s);

  // Array for storing the poison state of each apple
  vector<Apple *> apples(n);

  // Graph for storing the weight and antidote of each apple
  vector<vector<Apple *>> g(maximumPoisonState);
  for (int i = 0; i < n; i++)
  {
    int weight, poison = 0, antidote = 0;
    scanf("%d", &weight);
    for (int j = 0; j < s; j++)
    {
      int x;
      scanf("%d", &x);
      if (x == -1)
        poison |= 1 << j;
      else if (x == 1)
        antidote |= 1 << j;
    }

    // printf("Poison: %d, Antidote: %d\n", poison, antidote);

    apples[i] = new Apple(weight, poison, antidote);
    g[poison].push_back(apples[i]);
  }

  // Array for storing the optimal weight for each poison state
  int optimalWeight[maximumPoisonState];
  // Initialize to not visit any state
  for (int i = 0; i < maximumPoisonState; i++)
    optimalWeight[i] = INT_MAX;

  // Set the "No poison" state to 0
  optimalWeight[0] = 0;

  // Priority queue for searching the reachable state from the "no poison" state
  priority_queue<PoisonState> stateSpaceSearch;
  stateSpaceSearch.push(PoisonState(0, 0));
  while (!stateSpaceSearch.empty())
  {
    PoisonState currentState = stateSpaceSearch.top();
    stateSpaceSearch.pop();

    if (optimalWeight[currentState.poisonMask] < currentState.weight)
      continue;
    // printf("Current Poison State: %d, Weight: %d\n",
    //        currentState.poisonMask, currentState.weight);

    // Find possible apple that can be eaten to get this state
    for (auto &apple : g[currentState.poisonMask])
    {
      // printf("Found apple with weight: %d, poison: %d, antidote: %d\n",
      //        apple->weight, apple->poisonMask, apple->antidoteMask);

      int nextPoisonState = apple->antidoteMask;
      int nextWeight = currentState.weight + apple->weight;

      // printf("Next Poison State: %d, Next Weight: %d\n",
      //        nextPoisonState, nextWeight);
      // printf("Optimal Weight: %d\n", optimalWeight[nextPoisonState]);
      if (nextWeight < optimalWeight[nextPoisonState])
      {
        optimalWeight[nextPoisonState] = nextWeight;
        stateSpaceSearch.push(PoisonState(nextWeight, nextPoisonState));
      }
    }

    // Checking the other possible poison state that can be cured
    for (int i = 0; i < s; i++)
    {
      // Have poison "i"
      if ((currentState.poisonMask & (1 << i)))
      {
        // Remove poison "i" -> Eating the same apple will yield the same result
        int possiblePoisonState = currentState.poisonMask ^ (1 << i);
        int nextWeight = currentState.weight;
        if (nextWeight < optimalWeight[possiblePoisonState])
        {
          optimalWeight[possiblePoisonState] = nextWeight;
          stateSpaceSearch.push(PoisonState(nextWeight, possiblePoisonState));
        }
      }
    }
  }

  // Find the maximum weight that can be obtained
  int answer = 0;
  for (int i = 0; i < n; i++)
  {
    if (optimalWeight[apples[i]->poisonMask] != INT_MAX)
      answer = max(answer, optimalWeight[apples[i]->poisonMask]);

    // Free Apples memory
    delete apples[i];
  }
  printf("%d\n", answer);
}

/**
Random Test Case:
4 3
1 1 1 1
4 -1 0 -1
2 1 0 1
3 1 0 -1
 */