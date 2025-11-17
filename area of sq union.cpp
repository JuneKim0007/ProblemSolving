#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
using namespace std;


struct Interval{
    double yB, yT;
    int id;
};

struct Cmp{
    bool operator()(const Interval* a, const Interval* b) const{
        if(a->yB != b->yB) return a->yB < b->yB;
        return a->id < b->id;
    }
};

double computeY(const multiset<Interval*, Cmp> &active){
    if(active.empty()) return 0.0;

    double tot = 0.0;
    double curL = -1, curR = -1;

    for(auto p : active){
        if(p->yB > curR){
            if(curR > curL) tot += curR - curL;
            curL = p->yB;
            curR = p->yT;
        }
        else{
            if(p->yT > curR) curR = p->yT;
        }
    }

    if(curR > curL) tot += curR - curL;
    return tot;
}

int main(){
    int N;
    scanf("%d", &N);

    vector<Interval> intervals(N);
    unordered_map<double, vector<Interval*>> pushmap;
    unordered_map<double, vector<Interval*>> popmap;
    vector<double> x_vals;

    for(int i=0;i<N;i++){
        double Xu, Yu, Ru;
        scanf("%lf %lf %lf", &Xu, &Yu, &Ru);

        double xL = Xu - Ru;
        double xR = Xu + Ru;
        double yB = Yu - Ru;
        double yT = Yu + Ru;

        intervals[i] = {yB, yT, i};

        pushmap[xL].push_back(&intervals[i]);
        popmap[xR].push_back(&intervals[i]);

        x_vals.push_back(xL);
        x_vals.push_back(xR);
    }

    sort(x_vals.begin(), x_vals.end());
    x_vals.erase(unique(x_vals.begin(), x_vals.end()), x_vals.end());

    multiset<Interval*, Cmp> active;
    double area = 0;

    for(int i=0;i+1<(int)x_vals.size();i++){
        double x = x_vals[i];

        if(pushmap.count(x))
            for(auto p : pushmap[x]) active.insert(p);

        if(popmap.count(x))
            for(auto p : popmap[x]){
                auto it = active.find(p);
                if(it != active.end()) active.erase(it);
            }

        double width = x_vals[i+1] - x;
        if(width <= 0) continue;

        double height = computeY(active);
        area += height * width;
    }

    printf("%.2f", area);
    return 0;
}
