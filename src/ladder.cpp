#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error with word: " << word1 << " & " << word2 << "\n";
    cout << "Error: " << msg << endl;
}
 
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int size1 = str1.size();
    int size2 = str2.size();
    int size_diff = abs(size1 - size2);
    int diff = 0;

    if(size_diff == 0) {
        for(int i = 0; i < size1; ++i) {
            if(str1[i] != str2[i]) {
                ++diff;
                // if(diff > 1) return false;
            }
        }
    }
    else if(size_diff == 1) {
        int i = 0, j = 0;
        while (i < size1 && j < size2) {
            if (str1[i] != str2[j]) {
                if (size1 > size2) ++i;
                else ++j;
                ++diff;
                // if (diff > 1) return false;
            } 
            else {
                i++;
                j++;
            }
        }
    } 
    else if (size_diff > d) return false;
    
    return diff <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Entered the same word, no ladder");
        return {};
    }
    // bool in = false;
    // for(string word: word_list){
    //     if(end_word == word) {
    //         bool in = true;
    //         break;
    //     }
    // }
    // if(!in) return {};

    queue<vector<string>> ladder_queue;
    vector<string> sub_ladder;
    sub_ladder.push_back(begin_word);
    ladder_queue.push(sub_ladder);

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> sub_ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = sub_ladder.back();
        for (string word: word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder(sub_ladder);
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
     if (!file.is_open()) {
        cout << "Couldn't open file" << endl;        
        return;
    }

    string word;

    while(getline(file, word)) 
        word_list.insert(word);

    file.close();

}

void print_word_ladder(const vector<string>& ladder) {
    if(ladder.empty()) 
        cout << "No word ladder found." << endl;
    else {
        cout << "Word ladder found: ";
        for(string word: ladder)
            cout << word << " ";
        cout << endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}



// COPY PASTE DUMP
// VertexList bfs(const Graph& graph, Vertex startVertex) {
//     VertexList res;
//     vector<bool> visted(graph.size(), false);
//     queue<Vertex> que;
//     visted[startVertex] = true;
//     que.push(startVertex);
    
//     while(!que.empty()) {
//         Vertex cur = que.front();
//         que.pop();
//         res.push_back(cur);

//         for(Vertex v: graph.edges_from(cur)) {
//             if(!visted[v]) {
//                 visted[v] = true;
//                 que.push(v);
//             }
//         }
//     }

//     return res;
// }