#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

template <typename T>
concept is_container = requires(T a) {
  a.begin();
  a.end();
};

template <is_container T>
requires(!std::same_as<T, std::string>) std::ostream &
operator<<(std::ostream &os, const T &cont) {
  os << '{';
  for (const auto &x : cont) {
    os << x;
    os << ' ';
  }
  os << '}';
  return os;
}

void printMatrix(const is_container auto &cont) {
  for (const auto &x : cont) {
    cout << x;
    cout << '\n';
  }
}

template <typename T, std::size_t... Is>
constexpr std::array<T, sizeof...(Is)>
create_array(T value, std::index_sequence<Is...>) {
  return {{(static_cast<void>(Is), value)...}};
}

template <std::size_t N, typename T>
constexpr std::array<T, N> create_array(const T &value) {
  return create_array(value, std::make_index_sequence<N>());
}
template <typename T> constexpr auto accessor(T &t) {
  return [&](int i) -> typename T::reference { return t.at(i); };
}

template <typename T> constexpr auto accessor(const T &t) {
  return [&](int i) { return t.at(i); };
}

template <typename T> constexpr auto const_accessor(T &t) {
  return [&](int i) { return t.at(i); };
}

template <typename T> constexpr auto matrix_accessor(T &t) {
  return [&](int i, int j) ->
         typename T::value_type::reference { return t.at(i).at(j); };
}

template <typename T> constexpr auto matrix_accessor(const T &t) {
  return [&](int i, int j) { return t.at(i).at(j); };
}

template <typename T> constexpr auto const_matrix_accessor(T &t) {
  return [&](int i, int j) { return t.at(i).at(j); };
}

template <typename T> using lmt = std::numeric_limits<T>;

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept {
  return N;
}

struct TrieNode {
  TrieNode *children[26];
  bool isLeaf;
};

bool contains(TrieNode *root, char c) {
  return root->children[c - 'a'] != nullptr;
}

TrieNode *&get_node(TrieNode *root, char c) { return root->children[c - 'a']; }

void init(TrieNode *root) {
  for (int i = 0; i < 26; i++) {
    root->children[i] = nullptr;
  }
  root->isLeaf = false;
}

void insert(struct TrieNode *root, string key) {
  const auto size = key.size();
  auto cur_node = root;
  for (const char cur_char : key) {
    if (not contains(cur_node, cur_char)) {
      auto &new_trie_node = get_node(cur_node, cur_char);
      new_trie_node = new TrieNode{};
      init(new_trie_node);
    }
    cur_node = get_node(cur_node, cur_char);
  }
  cur_node->isLeaf = true;
}

void recurse_trie(TrieNode *root, string &cur_string,
                  vector<string> &resultant_vector) {
  if(root->isLeaf) resultant_vector.push_back(cur_string);
  for (size_t i = 0; i < 26u; i++) {
    if (root->children[i] == nullptr) {
      continue;
    }
    cur_string += i + 'a';
    recurse_trie(root->children[i], cur_string, resultant_vector);
    cur_string.pop_back();
  }
}

vector<string> all_string(TrieNode *root) {
  vector<string> resultant_vector;
  string cur_string;
  recurse_trie(root, cur_string, resultant_vector);
  return resultant_vector;
}

vector<string> operator+(string &&prefix, vector<string> &&post_strings) {
  for (auto &str : post_strings) {
    str = prefix + str;
  }
  return post_strings;
}

vector<vector<string>> display_contacts(int n, string contact[], string s) {
  TrieNode *root = new TrieNode{};
  init(root);
  for (int i = 0; i < n; i++) {
    insert(root, contact[i]);
  }
  const int size = s.size();
  auto cur_node = root;
  vector<vector<string>> ret_vector;
  bool not_found = false;
  for (int i = 0; i < size; i++) {
    if (not_found) {
      ret_vector.push_back({"0"});
    } else {
      const auto cur_char = s[i];
      if (contains(cur_node, cur_char)) {
        cur_node = get_node(cur_node, cur_char);
        ret_vector.push_back(s.substr(0, i + 1) + all_string(cur_node));
      } else {
        ret_vector.push_back({"0"});
        not_found = true;
      }
    }
  }
  return ret_vector;
}

int main() {
  string contact[]{"saneadeb",      "sanadcbabdcb",   "sanbcaccd",
                   "sanbded",       "sanccdcdbd",     "sancdcbeceaa",
                   "sanadcadeee",   "saneabddabcdea", "sanbaeecdecab",
                   "sanbbeeaaa",    "saneab",         "sanaccccbcbedce",
                   "sanbabdbaecba", "sancaa"};
  vector<vector<string>> result{
      {"sanaccccbcbedce", "sanadcadeee", "sanadcbabdcb", "sanbabdbaecba",
       "sanbaeecdecab", "sanbbeeaaa", "sanbcaccd", "sanbded", "sancaa",
       "sanccdcdbd", "sancdcbeceaa", "saneab", "saneabddabcdea", "saneadeb"},
      {"sanaccccbcbedce", "sanadcadeee", "sanadcbabdcb", "sanbabdbaecba",
       "sanbaeecdecab", "sanbbeeaaa", "sanbcaccd", "sanbded", "sancaa",
       "sanccdcdbd", "sancdcbeceaa", "saneab", "saneabddabcdea", "saneadeb"},
      {"sanaccccbcbedce", "sanadcadeee", "sanadcbabdcb", "sanbabdbaecba",
       "sanbaeecdecab", "sanbbeeaaa", "sanbcaccd", "sanbded", "sancaa",
       "sanccdcdbd", "sancdcbeceaa", "saneab", "saneabddabcdea", "saneadeb"},
      {"0"},
      {"0"},
      {"0"}};
  printMatrix(result);
  cout << endl;
  auto answer = display_contacts(size(contact), contact, "sandde");
  printMatrix(answer);
  for(int i = 0; i < result.size(); i++){
    for(int j = 0; j < result[i].size(); j++){
      cout << (answer[i][j] == result[i][j]) << " ";
    }
    cout << endl;
  }
  return 0;
}
