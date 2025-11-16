#include <cstdio>
#include <vector>
#include <algorithm>

int main(){

    std::vector<int> arr;
    std::vector<int> sorted_arr;
    std::vector<int> ans;

    int x;

    while (scanf("%d", &x) == 1){
        arr.push_back(x);
        sorted_arr.push_back(x);
    }

    int n = arr.size();
    std::sort(sorted_arr.begin(), sorted_arr.end());

    for (int i = n - 1; i >= 0; --i){

        int cursored_elem = sorted_arr[i];

        //o(n)
        auto it = std::find(arr.begin(), arr.end(), cursored_elem);
        int pos = it - arr.begin();


        //if the cursored elem is at the correct pos
        if (pos == i) continue;

        //put the cursored elem to the end
        if (pos != 0){
            ans.push_back(pos + 1);
            int L = 0, R = pos;
            //flip
            while (L < R){
                int tmp = arr[L]; 
                arr[L] = arr[R]; 
                arr[R] = tmp;
                L++; R--;
            }
        }
        //put the cursored elem to the next front
        ans.push_back(i + 1);
        int L = 0, R = i;
        //flip
        while (L < R){
            int tmp = arr[L]; 
            arr[L] = arr[R];
            arr[R] = tmp;
            L++; R--;
        }
    }

    //5 -> 1
    //4 -> 2
    //3 -> 3.
    for (int i = 0; i < (int)ans.size(); i++){
        int inverse = ans[i];
        inverse = n - inverse + 1;
        printf("%d ", inverse);
    }

    printf("0\n");
    return 0;
}