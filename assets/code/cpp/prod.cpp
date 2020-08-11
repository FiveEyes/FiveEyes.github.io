#include <iostream>
#include <vector>
#include <functional>
#include <tuple>
#include <utility>

using namespace std;

template<typename T>
void printVec(vector<T>& vec, string s = "") {
    cout << s;
    for(auto v : vec) {
        cout << v << " ";
    }
    cout << endl;
}

template<unsigned int I, typename... Ts>
void printTupleIndex(const tuple<Ts...>& t) {
    cout << get<I>(t) << " ";
}

template<unsigned int N, typename... Ts>
struct printTupleHelper;

template<typename... Ts>
struct printTupleHelper<0, Ts...> {
    static void apply(const tuple<Ts...>& t) {
        printTupleIndex<0, Ts...>(t);
    }
};

template<unsigned int N, typename... Ts>
struct printTupleHelper {
    static void apply(const tuple<Ts...>& t) {
        printTupleHelper<N-1, Ts...>::apply(t);
        printTupleIndex<N, Ts...>(t);
    }
};

template<typename... Ts>
void printTuple(const tuple<Ts...>& t) {
    printTupleHelper<tuple_size<tuple<Ts...>>::value-1, Ts...>::apply(t);
    cout << endl;
}

template<typename... Ts>
void test_vec_size(vector<Ts>... vs) {
    vector<int> size;
    (size.push_back(vs.size()),...);
    cout << "size: ";
    for(auto i : size) cout << i << " ";
    cout << endl;
}

template<unsigned int i, typename... Ts>
void update(tuple<vector<Ts>...>& input, tuple<Ts...>& output, unsigned int k) {
    get<i>(output) = get<i>(input)[k];
}

template<unsigned int K, typename... Ts>
struct UpdateBefore;

template<typename... Ts>
struct UpdateBefore<0, Ts...> {
    static void apply(tuple<vector<Ts>...>& input, tuple<Ts...>& output, vector<int> cur, int i) {
        update<0, Ts...>(input, output, cur[0]);
    }
};

template<unsigned int K, typename... Ts>
struct UpdateBefore {
    static void apply(tuple<vector<Ts>...>& input, tuple<Ts...>& output, vector<int> cur, int i) {
        if(K <= i) update<K>(input, output, cur[K]);
        UpdateBefore<K-1,Ts...>::apply(input, output, cur, i);
    }
};

template<typename... Ts>
struct ProdIter {
    using InputT = tuple<vector<Ts>...>;
    using OutputT = tuple<Ts...>;
    static constexpr auto N = sizeof...(Ts);
    InputT input;
    OutputT output;
    vector<int> cur;
    vector<unsigned int> sz;
    ProdIter(vector<Ts>... vs) {
        input = InputT(vs...);
        (sz.push_back(vs.size()),...);
        (cur.push_back(vs.size()-1),...);
        cur[N-1] = -1;
    }
    const OutputT* next() {
        int i = 0;
        while(i < N && sz[i] <= cur[i] + 1) cur[i++] = 0;
        if(i >= N) {
            return NULL;
        }
        cur[i]++;
        UpdateBefore<N-1,Ts...>::apply(input, output, cur, i);
        return &output;
    }
    void reset() {
        for(int i = 0; i < N; ++i) cur[i] = sz[i] - 1;
        cur[N-1] = -1;
    }
};

template<typename... Ts>
struct ProdCollection {
    using InputT = tuple<vector<Ts>...>;
    using OutputT = tuple<Ts...>;
    static constexpr auto N = sizeof...(Ts);
    InputT input;
    OutputT output;
    vector<int> cur;
    vector<unsigned int> sz;
    vector<unsigned int> len;
    ProdCollection(vector<Ts>... vs) {
        input = InputT(vs...);
        vector<int>(N, 0).swap(cur);
        (sz.push_back(vs.size()),...);
        vector<unsigned int>(N+1, 1).swap(len);
        for(int i = 0; i < N; ++i) {
            len[i+1] = len[i] * sz[i];
        }
    }
    unsigned int size() {
        return len[N];
    }

    const OutputT* get(unsigned int k) {
        if(k >= size()) return NULL;
        for(int i = N - 1; i >= 0; --i) {
            cur[i] = k / len[i];
            k %= len[i];
        }
        UpdateBefore<N-1,Ts...>::apply(input, output, cur, N-1);
        return &output;
    }
};

int main() {
    vector<int> ints = {1,2,3};
    vector<string> strs = {"hello", "world"};
    vector<double> doubles = {4.4, 5.5};

    ProdCollection<int,double,string> collection(ints, doubles, strs);
    for(int i = 0; i < collection.size(); ++i) {
        cout << i << ": ";
        printTuple(*(collection.get(i)));
    }

    ProdCollection collection1(strs, strs);
    for(int i = 0; i < collection1.size(); ++i) {
        cout << i << ": ";
        printTuple(*(collection1.get(i)));
    }

    ProdIter iter(ints, doubles, strs);
    while(auto v = iter.next()) {
        printTuple(*v);
    }
    iter.reset();
    while(auto v = iter.next()) {
        printTuple(*v);
    }

    return 0;
}
