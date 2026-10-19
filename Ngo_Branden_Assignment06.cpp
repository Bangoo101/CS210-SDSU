#include <cstdint>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>
using namespace std;

uint64_t demoHash(const string& s) {
    uint64_t h = 1469598103934665603ULL;
    for (unsigned char c : s) {
        h = (h ^ c) * 1099511628211ULL;
    }
    return h;
}

struct UserRecord {
    string username;
    string salt;
    uint64_t passwordHash{};
};

enum class CollisionStrategy {
    Chaining,
    LinearProbing,
    QuadraticProbing,
    DoubleHashing
};
//used ai
string strategyName(CollisionStrategy strategy) {
    switch (strategy) {
        case CollisionStrategy::Chaining: return "separate chaining";
        case CollisionStrategy::LinearProbing: return "linear probing";
        case CollisionStrategy::QuadraticProbing: return "quadratic probing";
        case CollisionStrategy::DoubleHashing: return "double hashing";
    }
    return "unknown";
}

class HashTable {
private:
    struct Entry {
        string key;
        UserRecord value;
    };

    enum class SlotState { Empty, Occupied, Deleted };

    struct Slot {
        SlotState state = SlotState::Empty;
        Entry entry;
    };

    CollisionStrategy strategy_;
    vector<list<Entry>> chains_;
    vector<Slot> slots_;
    size_t size_ = 0;
    size_t deletedSlots_ = 0;
    double maxLoadFactor_ = 0.70;

    bool isChaining() const {
        return strategy_ == CollisionStrategy::Chaining;
    }

    size_t indexFor(const string& key, size_t capacity) const {
        return static_cast<size_t>(demoHash(key) % capacity);
    }

    size_t stepFor(const string& key, size_t capacity) const {
        // Capacity is kept prime, so this step is nonzero and coprime to capacity.
        return 1 + static_cast<size_t>(demoHash(key) % (capacity - 1));
    }
    //looked up
    size_t probeIndex(const string& key, size_t attempt,
                           size_t capacity) const {
        const size_t h1 = indexFor(key, capacity);
        switch (strategy_) {
            case CollisionStrategy::LinearProbing:
                return (h1 + attempt) % capacity;
            case CollisionStrategy::QuadraticProbing:
                return (h1 + attempt * attempt) % capacity;
            case CollisionStrategy::DoubleHashing:
                return (h1 + attempt * stepFor(key, capacity)) % capacity;
            case CollisionStrategy::Chaining:
                return h1;
        }
        return h1;
    }

    static bool isPrime(size_t n) {
        if (n < 2) return false;
        for (size_t divisor = 2; divisor * divisor <= n; ++divisor) {
            if (n % divisor == 0) return false;
        }
        return true;
    }

    static size_t nextPrime(size_t n) {
        while (!isPrime(n)) ++n;
        return n;
    }

    double effectiveLoadFactor() const {
        if (isChaining()) return loadFactor();
        return static_cast<double>(size_ + deletedSlots_) / slots_.size();
    }
    //looked up 
    void rehash(size_t requestedCapacity) {
        const size_t newCapacity = nextPrime(requestedCapacity);
        vector<UserRecord> records;

        if (isChaining()) {
            for (const auto& bucket : chains_) {
                for (const auto& entry : bucket) records.push_back(entry.value);
            }
            chains_.assign(newCapacity, {});
        } else {
            for (const auto& slot : slots_) {
                if (slot.state == SlotState::Occupied) records.push_back(slot.entry.value);
            }
            slots_.assign(newCapacity, {});
            deletedSlots_ = 0;
        }

        size_ = 0;
        for (const auto& record : records) insertWithoutResize(record);
    }
    //looked up
    bool insertWithoutResize(const UserRecord& record) {
        const string& key = record.username;

        if (isChaining()) {
            auto& bucket = chains_[indexFor(key, chains_.size())];
            for (auto& entry : bucket) {
                if (entry.key == key) {
                    entry.value = record;
                    return false;
                }
            }
            bucket.push_back({key, record});
            ++size_;
            return true;
        }
        //used ai
        for (size_t attempt = 0; attempt < slots_.size(); ++attempt) {
            const size_t index = probeIndex(key, attempt, slots_.size());
            Slot& slot = slots_[index];
            if (slot.state == SlotState::Occupied && slot.entry.key == key) {
                slot.entry.value = record;
                return false;
            }
            if (slot.state != SlotState::Occupied) {
                if (slot.state == SlotState::Deleted) --deletedSlots_;
                slot.state = SlotState::Occupied;
                slot.entry = {key, record};
                ++size_;
                return true;
            }
        }
        return false;
    }

public:
    // looked up
    explicit HashTable(CollisionStrategy strategy, size_t initialCapacity = 11): strategy_(strategy) {
        const size_t capacity = nextPrime(initialCapacity);
        if (isChaining()) chains_.assign(capacity, {});
        else slots_.assign(capacity, {});
    }

    bool insert(const string& username, const UserRecord& record) {
        if (username.empty()) return false;

        const bool newKey = find(username) == nullptr;
        if (newKey && effectiveLoadFactor() >= maxLoadFactor_) {
            cout << "  [rehash] " << strategyName(strategy_)
                      << ": " << capacity() << " -> " << nextPrime(capacity() * 2)
                      << " buckets/slots\n";
            rehash(capacity() * 2);
        }
        return insertWithoutResize(record);
    }
    //looked up
    const UserRecord* find(const string& username) const {
        if (isChaining()) {
            const auto& bucket = chains_[indexFor(username, chains_.size())];
            for (const auto& entry : bucket) {
                if (entry.key == username) return &entry.value;
            }
            return nullptr;
        }

        for (size_t attempt = 0; attempt < slots_.size(); ++attempt) {
            const Slot& slot = slots_[probeIndex(username, attempt, slots_.size())];
            if (slot.state == SlotState::Empty) return nullptr;
            if (slot.state == SlotState::Occupied && slot.entry.key == username) {
                return &slot.entry.value;
            }
        }
        return nullptr;
    }

    bool remove(const string& username) {
        if (isChaining()) {
            auto& bucket = chains_[indexFor(username, chains_.size())];
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (it->key == username) {
                    bucket.erase(it);
                    --size_;
                    return true;
                }
            }
            return false;
        }

        for (size_t attempt = 0; attempt < slots_.size(); ++attempt) {
            Slot& slot = slots_[probeIndex(username, attempt, slots_.size())];
            if (slot.state == SlotState::Empty) return false;
            if (slot.state == SlotState::Occupied && slot.entry.key == username) {
                slot.state = SlotState::Deleted;
                --size_;
                ++deletedSlots_;
                return true;
            }
        }
        return false;
    }

    //used ai
    double loadFactor() const {
        const size_t capacityValue = capacity();
        return capacityValue == 0 ? 0.0: static_cast<double>(size_) / capacityValue;
    }

    //looked up online
    size_t capacity() const {
        return isChaining() ? chains_.size() : slots_.size();
    }

    size_t size() const { return size_; }
    CollisionStrategy strategy() const { return strategy_; }
};

//from class
string storedHash(const string& salt, const string& password, const string& pepper) {
    return to_string(demoHash(salt + password + pepper));
}

UserRecord makeUser(const string& username, const string& password, const string& salt, const string& pepper) {
    return {username, salt, demoHash(salt + password + pepper)};
}
//used ai
bool login(const HashTable& users, const  string& username,
           const  string& password, const  string& pepper) {
    const UserRecord* record = users.find(username);
    if (record == nullptr) {
         cout << "login(" << username << "): unknown user\n";
        return false;
    }
    //used ai
    const uint64_t submittedHash = demoHash(record->salt + password + pepper);
    const bool accepted = submittedHash == record->passwordHash;
     cout << "login(" << username << "): "
              << (accepted ? "success" : "failed password") << "\n";
    return accepted;
}
//used ai
void demonstrateAllStrategies() {
     cout << "Collision strategy smoke test\n";
    for (const auto strategy : {CollisionStrategy::Chaining,
                                CollisionStrategy::LinearProbing,
                                CollisionStrategy::QuadraticProbing,
                                CollisionStrategy::DoubleHashing}) {
        HashTable table(strategy, 5);
        table.insert("alice", {"alice", "s1", 1});
        table.insert("bob", {"bob", "s2", 2});
        table.insert("carol", {"carol", "s3", 3});
        const bool found = table.find("bob") != nullptr;
        const bool removed = table.remove("bob");
         cout << "  " << strategyName(strategy)
                  << ": find bob=" <<  boolalpha << found
                  << ", remove bob=" << removed
                  << ", load factor=" <<  fixed <<  setprecision(2)
                  << table.loadFactor() << "\n";
    }
     cout << "\n";
}

int main() {
    demonstrateAllStrategies();

    constexpr const char* PEPPER = "bazinga-sixseven";
    HashTable users(CollisionStrategy::DoubleHashing, 5);
    
    const  vector<UserRecord> sampleUsers = {
        makeUser("alice", "maple", "salt-a", PEPPER),
        makeUser("branden", "binary", "salt-b", PEPPER),
        makeUser("carol", "graphs", "salt-c", PEPPER),
        makeUser("devin", "queues", "salt-d", PEPPER),
        makeUser("erik", "vectors", "salt-e", PEPPER),
        makeUser("frank", "pointers", "salt-f", PEPPER)
    };
    // used ai
    for (const auto& user : sampleUsers) users.insert(user.username, user);

     cout << "Chosen table: " << strategyName(users.strategy())
              << ", users=" << users.size()
              << ", load factor=" <<  fixed <<  setprecision(2)
              << users.loadFactor() << "\n\n";

    login(users, "branden", "binary", PEPPER);     // Successful login.
    login(users, "branden", "wrong", PEPPER);     // Failed password.
    login(users, "nobody", "binary", PEPPER);     // Unknown user.

     cout << "remove(carol): " << boolalpha << users.remove("carol") << "\n";
    cout << "find(carol) after removal: "
              << (users.find("carol") == nullptr ? "not found" : "found") << "\n";

    users.insert("grace", makeUser("grace", "trees", "salt-g", PEPPER));
    cout << "after rehash: capacity=" << users.capacity()
              << ", load factor=" << users.loadFactor() << "\n";
    login(users, "branden", "binary", PEPPER);     // Still works after rehash.

}
