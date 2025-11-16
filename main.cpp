#include <cstdio>

#define INF 1000000000

int main(){
    int M, N; 
    scanf("%d %d", &M, &N);

    int coins[101];
    for (int i = 0; i < N; i++) scanf("%d", &coins[i]);

    int MAX = 20000;

    static int dp[20001];
    for (int i = 0; i <= MAX; i++) dp[i] = INF;
    dp[0] = 0;

    for (int i = 0; i < N; i++) {
        int v = coins[i];
        for (int s = MAX; s >= v; s--) {
            if (dp[s - v] + 1 < dp[s]) dp[s] = dp[s - v] + 1;
        }
    }

    int bestSum = -1;
    int bestCoins = INF;

    for (int s = M; s <= MAX; s++) {
        if (dp[s] < INF) {
            bestSum = s;
            bestCoins = dp[s];
            break;
        }
    }

    printf("%d %d\n", bestSum, bestCoins);
    return 0;
}