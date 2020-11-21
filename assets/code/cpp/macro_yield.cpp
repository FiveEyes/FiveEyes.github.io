// clang -std=c++17 -lstdc++ prod.cpp -o prod && ./prod

#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <typeinfo>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
void print(vector<T>& vec) {
    for(int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

template<typename S>
class Source : public std::enable_shared_from_this<Source<S>> {
public:
	virtual ~Source() {}
    virtual bool operator()(S& output) = 0;
    bool next(S& output) {
        return (*this)(output);
    }
    shared_ptr<Source<S>> getPtr() { return this->shared_from_this(); }
};

template<typename S>
class Gen : public Source<S> {
public:
    int state;
    bool isAlive;
    Gen() : state(0), isAlive(true) {}
    virtual bool step(S& output) = 0;
    bool operator()(S& output) {
        while(!step(output));
        return isAlive;
    }
};

#define GEN_BEG \
switch(state) { \
case BEG: {}

#define GEN_END \
default: { isAlive = false; return true; } }

#define BEG(name) BEG_##name
#define ELSE(name) ELSE_##name
#define END(name) END_##name


#define IF(name,c,a,b) \
case BEG(name): { if(c) { {a;} state = END(name); return false; } else { state = ELSE(name); } } \
case ELSE(name): { b; } \
case END(name): {}

#define LOOP(name,s) \
case BEG(name): { {s;} state = BEG(name); return false; } \
case END(name): {}

#define WHILE(name,c,s) \
case BEG(name): { if(!(c)) { state = END(name); return false; } {s;} state = BEG(name); return false; } \
case END(name): {}

#define YIELD(name) \
case BEG(name): { state = END(name); isAlive = true; return true; } \
case END(name): {}

#define CONTINUE(loop) { state = BEG(loop); return false; }
#define BREAK(loop) { state = END(loop); return false; }

#define GOTO(label) { state = label; return false; }

#define DEC_BEG enum { BEG = 0,
#define DEC_IF(name) BEG(name), ELSE(name), END(name)
#define DEC_LOOP(name) BEG(name), END(name)
#define DEC_YIELD(name) BEG(name), END(name)
#define DEC_END };

/*
L: def prod_iter(s):
0:   if len(s) == 0:
1:     yield []
2:   else:
3:     x = 0
4:     while true:
5:       xs = []
6:       iter = generator.create(prod_iter(s[1:]))
7:       while true:
8:         xs, isAlive = iter.resume()
9:         if !isAlive:
10           break
11         yield [x] + xs
12       x += 1
13       if x >= s[0]:
14         break
-1   return
*/
class OneMoreProdGen : public Gen<vector<int> > {
public:
    vector<unsigned int> s;
    int x;
    shared_ptr<Source<vector<int> > > iter;
    vector<int> xs;
    OneMoreProdGen(const vector<unsigned int>& _s) : s(_s) {}
    bool step(vector<int>& output) {
        DEC_BEG
            DEC_IF(if1), DEC_IF(if2), DEC_IF(if3),
            DEC_LOOP(loop1), DEC_LOOP(loop2),
            DEC_YIELD(y1), DEC_YIELD(y2)
        DEC_END
        GEN_BEG
        IF(if1, s.size()==0, { 
            output.clear();
            YIELD(y1); 
        }, {
            x = 0;
            WHILE(loop1, true, {
                IF(if3, x >= s[0], BREAK(loop1), {});
                {
                vector<unsigned int> ss(s.begin() + 1, s.end());
                iter = make_shared<OneMoreProdGen>(ss);
                }
                WHILE(loop2, iter->next(xs), {
                    output.clear();
                    output.push_back(x);
                    output.insert(output.end(), xs.begin(), xs.end());
                    YIELD(y2);
                });
                x += 1;
            })
        });
        GEN_END
    }
};


/*
def hanoi(n, a, b, c):
    if n == 1:
        s = str(a) +  ' --> ' + str(c)
        yield s
    else:
        for s in hanoi(n - 1, a, c, b):
            yield s
        for s in hanoi(1    , a, b, c):
            yield s
        for s in hanoi(n - 1, b, a, c):
            yield s
*/
class OneMoreHanoiGen : public Gen<string> {
public:
    int n;
    string a, b, c;
    shared_ptr<Gen<string> > iter;
    OneMoreHanoiGen(int _n, string _a, string _b, string _c):
        n(_n), a(_a), b(_b), c(_c) {}
    bool step(string& output) {
        DEC_BEG
            DEC_IF(if1), DEC_LOOP(loop1), DEC_LOOP(loop2), DEC_LOOP(loop3), 
            DEC_YIELD(y1), DEC_YIELD(y2), DEC_YIELD(y3), DEC_YIELD(y4)
        DEC_END
        GEN_BEG
        IF(if1, n == 1, {
            output = a + " --> " + c;
            YIELD(y1);
        }, {
            iter = make_shared<OneMoreHanoiGen>(n - 1, a, c, b);
            WHILE(loop1, iter->next(output), YIELD(y2));
            iter = make_shared<OneMoreHanoiGen>(1, a, b, c);
            WHILE(loop2, iter->next(output), YIELD(y3));
            iter = make_shared<OneMoreHanoiGen>(n - 1, b, a, c);
            WHILE(loop3, iter->next(output), YIELD(y4));
        });
        GEN_END
    }
};

class PrimeGen : public Gen<int> {
public:
    vector<int> primes;
    int i, j;
    PrimeGen() {}
    bool step(int& output) {
        DEC_BEG
            DEC_IF(if1), DEC_IF(if2),
            DEC_LOOP(loop1), DEC_LOOP(loop2),
            DEC_YIELD(y1)
        DEC_END
        GEN_BEG
        i = 2;
        WHILE(loop1, true, {
            j = 0;
            WHILE(loop2, j < primes.size(), {
               IF(if1, i % primes[j] == 0, {i++; CONTINUE(loop1);}, j++); 
            });
            primes.push_back(i); 
            output = i; 
            YIELD(y1);
        });
        GEN_END
    }
};

int main() {
    cout << "HanoiGen" << endl;
    string s;
    OneMoreHanoiGen hanoiGen(3, "A", "B", "C");
    while(hanoiGen(s)) cout << s << endl;
    
    cout << "CartesianProduct" << endl;
    vector<unsigned int> dimSize({2,3,4});
    vector<int> output(dimSize.size());
    OneMoreProdGen prodGen(dimSize);
    while(prodGen(output)) print(output);
    
    cout << "Prime numbers" << endl;
    PrimeGen primeGen;
    int p;
    for(int i = 0; i < 30; ++i) {
        primeGen(p);
        cout << p << " ";
    }
    cout << endl;
    return 0;
}
