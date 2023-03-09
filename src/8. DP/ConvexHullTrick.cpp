#include "../Header.cpp"

struct Line {
    ll m, c, id;
    ll calc(ll x) {
	
        return m * x + c;
    }
};
bool obsolete(Line a, Line b, Line c){
    return (c.c - a.c) * (a.m - b.m) < (a.m - c.m) * (b.c - a.c); 
}

vector<Line>lines;
void insert(Line l) {
    while(lines.size() > 1) {
        ll sz = lines.size();
        if(obsolete(lines[sz-2], lines[sz-1], l)){
            lines.pop_back();
        } else break;
    }
    lines.push_back(l);
}