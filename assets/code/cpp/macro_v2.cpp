// Title       : Implementation of Coroutine in Cpp, Version 2
// Author      : hanzh.xu@gmail.com
// Date        : 11-22-2020
// License     : MIT License

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

template<typename T>
class Gen : public std::enable_shared_from_this<Gen<T>> {
public:
    int state;
    Gen() : state(0) {}
    virtual bool next(T& output) = 0;
    bool operator()(T& output) {
        return next(output);
    }
};

template<typename S, typename T>
class Coroutine : public std::enable_shared_from_this<Coroutine<S,T>> {
public:
    int state;
    Coroutine() : state(0) {}
    virtual ~Coroutine() {}
    virtual bool next(S& input, T &output) = 0;
    bool operator()(S& input, T &output) {
        return next(input, output);
    }
    shared_ptr<Coroutine<S,T>> getPtr() { return this->shared_from_this(); }
};


#define PRG_BEG \
switch(state) { \
case 0:;

#define PRG_END \
case -1:; \
default: { return false; } }

#define YIELD(name) \
do { state=__LINE__; return true; case __LINE__:; } while (0)

#define RETURN() { state = -1; return false; }

/* Examples */

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
class BetterProdGen : public Gen<vector<int>> {
public:
    vector<unsigned int> s;
    int x;
    shared_ptr<BetterProdGen> iter;
    vector<int> xs;
    BetterProdGen(const vector<unsigned int>& _s) : s(_s) {}
    bool next(vector<int>& output) {
        PRG_BEG
        if(s.size()==0) { 
            output.clear();
            YIELD();
            RETURN();
        }
        for(x = 0; x < s[0]; ++x) {
            iter = make_shared<BetterProdGen>(
            vector<unsigned int>(s.begin() + 1, s.end()));
            while(iter->next(xs)) {
                output.clear();
                output.push_back(x);
                output.insert(output.end(), xs.begin(), xs.end());
                YIELD();
            }
        }
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
class BetterHanoiGen : public Gen<string> {
public:
    int n;
    string a, b, c;
    shared_ptr<Gen<string> > iter;
    BetterHanoiGen(int _n, string _a, string _b, string _c):
        n(_n), a(_a), b(_b), c(_c) {}
    bool next(string& output) {
        PRG_BEG
        if(n == 1) {
            output = a + " --> " + c;
            YIELD();
            RETURN();
        }
        iter = make_shared<BetterHanoiGen>(n - 1, a, c, b);
        while(iter->next(output)) YIELD();
        iter = make_shared<BetterHanoiGen>(1, a, b, c);
        while(iter->next(output)) YIELD();
        iter = make_shared<BetterHanoiGen>(n - 1, b, a, c);
        while(iter->next(output)) YIELD();
        PRG_END
    }
};


class PrimeGen : public Gen<int> {
public:
    vector<int> primes;
    int i, j;
    PrimeGen() {}
    bool next(int& output) {
        PRG_BEG
        for(i = 2; true; ++i) {
            j = 0;
            for(j = 0; j < primes.size(); ++j) {
                if(i % primes[j] == 0) {
                    goto loop1_end;
                }
            }
            primes.push_back(i); 
            output = i; 
            YIELD();
            loop1_end:;
        }
        PRG_END
    }
};


class SubsetGen: public Gen<vector<int> > {
public:
    int n, i, j;
    SubsetGen(int _n) : n(_n) {}
    bool next(vector<int>& output) {
        PRG_BEG
        for(i = 0; i < (1 << n); ++i) {
            output.clear();
            for(int j = 0; j < n; ++j) {
                if((i >> j) & 1) {
                    output.push_back(j);
                }
            }             
            YIELD();
        }
        PRG_END
    }
};

class PermutationGen: public Gen<vector<int> > {
public:
    int beg, n, i;
    vector<int>& arr;
    shared_ptr<PermutationGen> iter;
    PermutationGen(int _beg, vector<int>& _arr) : beg(_beg), n(_arr.size()), arr(_arr) {}
    bool next(vector<int>& output) {
        PRG_BEG
        if(beg >= n - 1) {
            for(i = 0; i < n; ++i) {
                output[i] = arr[i];
            }
            YIELD();
            RETURN();
        }
        for(i = beg; i < n; ++i) {
            swap(arr[beg], arr[i]);
            iter = make_shared<PermutationGen>(beg + 1, arr);
            while((*iter)(output)) YIELD();
            swap(arr[beg], arr[i]);
        }
        PRG_END
    }
    void swap(int& a, int &b) {
        int c = a;
        a = b;
        b = c;
    }
};


class GuessNumber : public Coroutine<int, int> {
public:
    int t, num;
    GuessNumber() {}
    bool next(int& input, int& output) {
        PRG_BEG
        t = 0;
        srand(time(0));
        cout << "Guess a number between 0 and 100!" << endl;
        while(true) {
            cout << "Match " << t << endl;
            num = rand() % 100;
            cout << "input a number:";
            YIELD();
            while(input != num) {
                if(input == -1) RETURN();
                if(input < num) {
                    cout << "Too low!" << endl;
                    output = -1;
                } else {
                    cout << "Too high!" << endl;
                    output = 1;
                }
                cout << "input a number agian:";
                YIELD();
            }
            cout << "Bingo! It's " << num << "!" << endl;
            cout << "Let's play it again!" << endl;
            t++;
            output = 0;
        }
        cout << "ByeBye!" << endl;
        PRG_END
    }
};

class GuessYourNumber : public Coroutine<string, int> {
public:
    int beg, end, mid;
    GuessYourNumber() {}
    bool next(string& input, int& output) {
        PRG_BEG
        cout << "Keep a number between 0 and 100 in your mind!" << endl;
        cout << "Are you ready?(y/n)" << endl;
        YIELD();
        if(input[0] != 'y') {
            goto bye;
        }
        beg = 0, end = 101;
        while(beg < end) {
            mid = (beg + end) / 2;
            cout << "Is it " << mid << "?" << endl;
            cout << "Input 's' if it is smaller than your number." << endl;
            cout << "Input 'b' if it is bigger than your number." << endl;
            cout << "Input 'y' if it is your number!" << endl;
            YIELD();
            if(input[0] == 's') {
                beg = mid+1;
            } else if(input[0] == 'b') {
                end = mid;
            } else {
                cout << "YES! It's " << mid << "!" << endl;
                RETURN();
            }
        }
        cout << "No possible! The number must be " << mid << "!" << endl;
        bye:;
        cout << "ByeBye!" << endl;
        PRG_END
    }
};

template<typename T>
void print(vector<T>& vec) {
    cout << "{ ";
    for(int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ", ";
    }
    cout << "}" << endl;
}

void testBetterHanoiGen() {
    cout << "testBetterHanoiGen" << endl;
    string s;
    BetterHanoiGen gen(3, "A", "B", "C");
    int k = 0;
    while(gen(s)) {
        cout << s << endl;
        k++;
    }
    cout << "HanoiGen is solved in " << k << " steps." << endl;
}

void testPrimeGen() {
    cout << "Prime numbers" << endl;
    PrimeGen primeGen;
    int p;
    for(int i = 0; i < 30; ++i) {
        primeGen(p);
        cout << p << " ";
    }
    cout << endl;
}

void testSubsetGen() {
    cout << "testSubsetGen" << endl;
    int n = 5;
    vector<int> output(n);
    SubsetGen gen(n);
    int k = 0;
    while(gen(output)) {
        print(output);
        k++;
    }
    cout << "Generated " << k << " Subsets." << endl;
}

void testPermutationGen() {
    cout << "testPermutationGen" << endl;
    vector<int> arr({1,2,3,4});
    PermutationGen gen(0, arr);
    vector<int> output(arr.size());
    int k = 0;
    while(gen(output)) {
        print(output);
        k++;
    }
    cout << "Generated " << k << " Permutations." << endl;
}


void testBetterProdGen() {
    cout << "testBetterProdGen" << endl;
    vector<unsigned int> dimSize({3,2,4});
    vector<int> output(dimSize.size());
    BetterProdGen gen(dimSize);
    int k = 0;
    while(gen(output)) {
        print(output);
        k++;
    }
    cout << "Generated " << k << " rows." << endl;
}

void testGuessNumber() {
    GuessNumber guess;
    int num, output;
    guess(num, output);
    do {
        cin >> num;
    } while(guess(num, output));
}

void testGuessYourNumber() {
    cout << "testGuessYourNumber" << endl;
    GuessYourNumber guess;
    string input;
    int output;
    guess(input, output);
    do {
        cin >> input;
    } while(guess(input, output));
}

int main() {

    testBetterHanoiGen();
        
    testPrimeGen();
    
    testSubsetGen();
    
    testPermutationGen();
    
    testBetterProdGen();
    
    // testGuessNumber();
    
    // testGuessYourNumber();
    
    return 0;
}
