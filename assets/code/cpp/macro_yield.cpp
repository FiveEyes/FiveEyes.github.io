// Title       : Implementation of Coroutine in Cpp
// Author      : hanzh.xu@gmail.com
// Date        : 11-21-2020
// License     : MIT License

/*
Implementation of Coroutine in Cpp

Compiler:
// clang version 3.8.1-24+rpi1 (tags/RELEASE_381/final)
// Target: armv6--linux-gnueabihf
// Thread model: posix
// clang -std=c++0x -lstdc++

Usage:
// class MyGen        : public Gen<Output type of the generator>
class OneMoreHanoiGen : public Gen<string> {
public:
    // Local variables of the generator.
    int n;
    string a, b, c;
    shared_ptr<Gen<string> > iter;
    
    // Constructor of the generator.
    OneMoreHanoiGen(int _n, string _a, string _b, string _c):
        n(_n), a(_a), b(_b), c(_c) {}
    
    // Write your code in the step method.
    // It is very straight forward. 
    // You just need to replace all control statements with the MACRO in your generator.
    // bool step(string& output);
    // Args: 
    //   output: the output of your generator, set the output before doing yield.
    // Return:
    //    The return value is used by the framework.
    //    DO NOT return true or false by yourself, let the MACRO takes care of it.
    bool step(string& output) {
        // Declare all the control statements at first.
        // IMPORTANT: You can NOT use a control MACRO without declaring its name.
        // DEC_BEG : begin the declaration.
        // DEF_IF(if_name) : declare a if statement named if_name.
        // DEF_LOOP(loop_name) : declare a loop statement named loop_name.
        // DEC_YIELD(yield_name) : declare a loop statement named yield_name.
        // DEC_END : end the declaration.
        DEC_BEG
            DEC_IF(if1), DEC_LOOP(loop1), DEC_LOOP(loop2), DEC_LOOP(loop3), 
            DEC_YIELD(y1), DEC_YIELD(y2), DEC_YIELD(y3), DEC_YIELD(y4)
        DEC_END
        
        // Using the control MACRO to write the code.
        // PRG_BEG                                       -> Begin the program.
        //   IF(name, condition, true_block, false_block); -> A if statment with name.
        //   WHILE(name, condition loop_block);            -> A while loop with name.
        //   BREAK(loop_name);                             -> Jump to the end of the loop named loop_name
        //   CONTINUE(loop_name);                          -> Jump to the begin of the loop named loop_name
        //   YIELD(name);                                  -> A yield statement with name.
        //   RETURN();                                     -> Finish the generator.
        // PRG_END                                       -> End the program.
        PRG_BEG
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
        PRG_END
    }
};

int main() {
    string output;
    
    // Build a HanoiGen with Args (3, "A", "B", "C").
    OneMoreHanoiGen hanoiGen(3, "A", "B", "C");
    
    // Get the next output, until the generator returns false. 
    // bool isAlive = hanoiGen(output);
    // if(isAlive) cout << output << endl;
    while(hanoiGen(output)) cout << output << endl;
    
    return 0;
}

// You also can create a coroutine having full functionality, if you want to do some interactive operations with the coroutine.
// The only difference is that the step method has an extra argument input now.
// The input argument represents the input variable that you pass into the Coroutine.
// See the example class GuessNumber to know how to use it.
template<typename S, typename T>
class Coroutine : public std::enable_shared_from_this<Coroutine<S,T>> {
public:
    virtual bool step(S& input, T& output) = 0;
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <typeinfo>
#include <utility>
#include <vector>

using namespace std;

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

template<typename S, typename T>
class Coroutine : public std::enable_shared_from_this<Coroutine<S,T>> {
public:
    int state;
    bool isAlive;
    Coroutine() : state(0), isAlive(true) {}

    virtual ~Coroutine() {}
    virtual bool step(S& input, T& output) = 0;

    bool next(S& input, T& output) {
        while(!step(input, output));
        return isAlive;
    }
    bool operator()(S& input, T& output) {
        return next(input, output);
    }
    shared_ptr<Coroutine<S,T>> getPtr() { return this->shared_from_this(); }
};


#define PRG_BEG \
switch(state) { \
case PBEG: {}

#define PRG_END \
case PEND: {} \
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

#define RETURN() { state = PEND; return false; }

#define DEC_BEG enum { PBEG = 0, PEND, 
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
        PRG_BEG
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
        PRG_END
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
        PRG_BEG
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
        PRG_END
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
        PRG_BEG
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
        PRG_END
    }
};

class GuessNumber : public Coroutine<int, int> {
public:
    int t, num;
    GuessNumber() {}
    bool step(int& input, int& output) {
        DEC_BEG
            DEC_IF(if1), DEC_IF(if2), 
            DEC_LOOP(loop1), DEC_LOOP(loop2), 
            DEC_YIELD(y1), DEC_YIELD(y2)
        DEC_END
        PRG_BEG
        t = 0;
        srand(time(0));
        cout << "Guess a number between 0 and 100!" << endl;
        WHILE(loop1, true, {
            cout << "Match " << t << endl;
            num = rand() % 100;
            cout << "input a number:";
            YIELD(y1);
            WHILE(loop2, input != num, {
                IF(if2, input == -1, BREAK(loop1), {});
                IF(if1, input < num, {
                    cout << "Too small!" << endl;
                    output = -1;
                }, {
                    cout << "Too large!" << endl;
                    output = 1;
                });
                cout << "input a number agian:";
                YIELD(y2);
            });
            cout << "Bingo! It's " << num << "!" << endl;
            cout << "Let's play it again!" << endl;
            t++;
            output = 0;
        });
        cout << "ByeBye!" << endl;
        PRG_END
    }
};

template<typename T>
void print(vector<T>& vec) {
    for(int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

void testGuessNumber() {
    GuessNumber guess;
    int num, output;
    guess(num, output);
    do {
        cin >> num;
    } while(guess(num, output));
}

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
    
    testGuessNumber();
    return 0;
}
