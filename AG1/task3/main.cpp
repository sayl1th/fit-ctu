#include <iostream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_set>


using namespace std;

struct Node
{
    int v;
    char w;

    Node (int _v, char _w) {  v = _v, w = _w; }
    int getV() { return v; }
    char getW() { return w; }
};


void buildWord(vector<vector<Node> > &words, int x, int y, string word,int &result) {
    
    if (x == y) {

        int tmp = word.size() - 1;

        for (int j = 0; j < (int)word.size()/2 ; j++) {
            if (word[j] != word[tmp])
                return;
            tmp--;
        }  

        result+=1;

    }

    for (int i = 0; i < (int) words[x].size(); i++) 
        buildWord(words, words[x][i].v, y, word+words[x][i].w, result);

}



int main() {

    int n, k;
    int x, y;
    int numOfPos;
    int p; 
    char c;
    string word;
    int result = 0;

    cin >> n; 
    cin >> k;
    cin >> x; 
    cin >> y;
    vector<vector<Node> > words(n);

    for (int i = 0; i < n; i++) {
        cin >> numOfPos;

        for (int j = 0; j < numOfPos; j++) {
            cin >> p;
            cin >> c;
            words[i].push_back(Node(p, c));

        }
    }

    buildWord(words, x, y, word, result);

    cout << result % 1000000007 << endl;
    
}
