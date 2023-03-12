// ID:83677624
// =========================================================================================
// Hash table is implemented via template class hash_table<Key, T, Hash, KeyEqual>.
// * Key - type for keys
// * T - type for values
// * Hash - type of object with () operator, which takes `Key` type as input and gives
// value of hash function as output.
// * KeyEqual - type of object with () operator, which takes two `Key` objects as parameters
// and gives `true` if they are equal.
// -----------------------------------------------------------------------------------------
// * Number of bucket is chosen by division by `table_size`.
// * Table deals with collisions using sequences method(is based on `vector<forward_list>`).
// * `get` and `delete_key` methods return `pair<T,bool>`, in which the second element is 
// `true` if the element is found, and `true` if not.
// -----------------------------------------------------------------------------------------
// Time complexity: 
// * Put: O(1)
// * Get: O(1)
// * Delete: O(1)
// -----------------------------------------------------------------------------------------
// Memory complexity:
// At every moment hash table stores O(n), where n - number of buckets.
// * Put: O(1) additional memory
// * Get: O(1) additional memory
// * Delete: O(1) additional memory
// =========================================================================================

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <forward_list>

std::ifstream in;
std::ofstream out;

namespace HASH_TABLE {

#define N_BUCKETS 100003

template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>
> class hash_table {
    std::size_t table_size;
    std::vector<std::forward_list<std::pair<const Key, T>>> table;
    Hash hasher;
    KeyEqual equal;
public:
    hash_table( std::size_t table_size = N_BUCKETS, 
                const Hash& hasher = Hash(), 
                const KeyEqual& equal = KeyEqual() ) : 
                table_size(table_size), table(table_size), hasher(hasher), equal(equal) {};
    
    void put(const Key& key, const T& value);
    std::pair<T, bool> get(const Key& key) const;
    std::pair<T, bool> delete_key(const Key& key);
};

template<class Key, 
         class T, 
         class Hash, 
         class KeyEqual
> void hash_table<Key, T, Hash, KeyEqual>::put(const Key& key, const T& value) {
    std::size_t bucket_number = hasher(key) % table_size;
    bool found = false;
    for (auto& pair : table[bucket_number]) {
        if (equal(key, pair.first)) {
            found = true;
            pair.second = value;
            break;
        }
    }
    if (!found) {
        table[bucket_number].push_front(std::make_pair(key, value));
    }
}

template<class Key, 
         class T, 
         class Hash, 
         class KeyEqual
> std::pair<T, bool> hash_table<Key, T, Hash, KeyEqual>::get(const Key& key) const {
    std::size_t bucket_number = hasher(key) % table_size;
    bool found = false;
    T value_found;
    for (const auto& pair : table[bucket_number]) {
        if (equal(key, pair.first)) {
            found = true;
            value_found = pair.second;
            break;
        }
    }
    
    return std::make_pair(value_found, found);
}

template<class Key, 
         class T, 
         class Hash, 
         class KeyEqual
> std::pair<T, bool> hash_table<Key, T, Hash, KeyEqual>::delete_key(const Key& key) {
    std::size_t bucket_number = hasher(key) % table_size;
    bool found = false;
    T value_found;
    auto prev = table[bucket_number].before_begin();
    for (auto& pair : table[bucket_number]) {
        if (equal(key, pair.first)) {
            found = true;
            value_found = pair.second;
            table[bucket_number].erase_after(prev);
            break;
        }
        prev++;
    }
    
    return std::make_pair(value_found, found);
}

}

enum commands {PUT, GET, DELETE};
std::unordered_map<std::string, commands> str_to_commands {
    {"put", PUT},
    {"get", GET}, 
    {"delete", DELETE}, 
};

void process_instructions(int number_of_instructions, HASH_TABLE::hash_table<int, int>& my_hash){
    std::string instruction;
    int key, value;
    std::pair<int, bool> pair;
    for (int i = 0; i < number_of_instructions; ++i){
        in >> instruction;
        switch (str_to_commands[instruction])
        {
        case PUT:
            in >> key >>  value;
            my_hash.put(key, value);
            break;
        case GET:
            in >> key;
            pair = my_hash.get(key);
            if (pair.second) {
                out << pair.first << std::endl;
            } else {
                out << "None" << std::endl;
            }
            break;
        case DELETE:
            in >> key;
            pair = my_hash.delete_key(key);
            if (pair.second) {
                out << pair.first << std::endl;
            } else {
                out << "None" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    HASH_TABLE::hash_table<int, int> my_hash;
    int number_of_instructions;
    in >> number_of_instructions;

    process_instructions(number_of_instructions, my_hash);

    in.close();
    out.close();
}