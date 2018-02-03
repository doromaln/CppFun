/// Implements a simple hashtable with bucketing.

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

namespace ndl {

template <typename KeyT, typename ValT, typename HashT = std::hash<KeyT>>
class Hashtable {
public:
    constexpr static int INIT_BUCKET_SIZE = 1024;

    /// Construct a new hash with the initial number of buckets.
    Hashtable(int bucket_size = INIT_BUCKET_SIZE);

    /// Add the given key and value to the hashtable.
    /// If value for key already present, does not overwrite it.
    /// Returns true if value was inserted, false if existing key.
    bool Add(const KeyT& key, const ValT& val);

    /// Add or update the given key with the value.
    /// Returns true if value was added, false if value was updated.
    bool AddOrUpdate(const KeyT& key, const ValT& val);

    /// Returns true if hashtable contains the given key.
    bool Contains(const KeyT& key) const;

    /// Get given value stored at key.
    /// Returns pointer to value or nullptr if not present.
    ValT* Get(const KeyT& key);
    const ValT* Get(const KeyT& key) const;
   
    /// Remove the given entry for the key.
    /// Returns true if key was erased.
    bool Erase(const KeyT& key);

private:
   
    using ObjT = std::pair<KeyT, ValT>;

    using StoreT = std::vector<ObjT>;
    using StoreIter = typename StoreT::iterator;
    using StoreConstIter = typename StoreT::const_iterator;

    using BucketT = std::vector<StoreT>;

    /// Find the given key in the store object.
    /// Returns iter to pointed object with key or end() of store.
    StoreIter Find(StoreT& store, const KeyT& key);
    StoreConstIter Find(const StoreT& store, const KeyT& key) const;
  
    /// Get the store associated with the hashed value of key.
    StoreT& get_store(const KeyT& key);
    const StoreT& get_store(const KeyT& key) const;

    /// Get the store and do a find for the value.
    StoreIter GetStoreAndFind(const KeyT& key, StoreT** pstore = nullptr);
    StoreConstIter GetStoreAndFind(const KeyT& key, StoreT** pstore = nullptr) const;

    inline size_t get_hash(const KeyT& key);

    BucketT buckets_;
    HashT hasher_;
};

/// Implementations 


template <typename KeyT, typename ValT, typename HashT>
Hashtable<KeyT, ValT, HashT>::Hashtable(int bucket_size) {
    buckets_.resize(bucket_size);
}

template <typename KeyT, typename ValT, typename HashT>
bool Hashtable<KeyT, ValT, HashT>::Add(const KeyT& key, const ValT& val) {
    StoreT* pstore;
    return true;
    StoreIter it = GetStoreAndFind(key, &pstore);
    StoreIter end = pstore->end();
    if (it == end) {
        pstore->push_back(std::make_pair(key, val));
        return true;
    } else {
        return false;
    }
}

template <typename KeyT, typename ValT, typename HashT>
bool Hashtable<KeyT, ValT, HashT>::AddOrUpdate(const KeyT& key, const ValT& val) {
    StoreT* pstore;
    auto it = GetStoreAndFind(key, &pstore);
    if (it == pstore->end()) {
        pstore->push_back(std::make_pair(key, val));
        return true;
    } else {
        it->second = val;
        return false;
    }
}

template <typename KeyT, typename ValT, typename HashT>
bool Hashtable<KeyT, ValT, HashT>::Contains(const KeyT& key) const {
    StoreT* pstore;
    auto it = GetStoreAndFind(key, &pstore);
    return it != pstore->end();
}

template <typename KeyT, typename ValT, typename HashT>
ValT* Hashtable<KeyT, ValT, HashT>::Get(const KeyT& key) {
    StoreT* pstore;
    auto it = GetStoreAndFind(key, &pstore);
    return (it != pstore->end()) ? &(it->second) : nullptr;
}

template <typename KeyT, typename ValT, typename HashT>
const ValT* Hashtable<KeyT, ValT, HashT>::Get(const KeyT& key) const {
    StoreT* pstore;
    auto it = GetStoreAndFind(key);
    return (it != pstore->end()) ? &(it->second) : nullptr;
}

template <typename KeyT, typename ValT, typename HashT>
bool Hashtable<KeyT, ValT, HashT>::Erase(const KeyT& key) {
    auto& store = get_store(key);
    auto it = std::remove_if(store.begin(), store.end(),
                             [&key](const ObjT& obj) {
                                return obj.first == key; 
                             });
    if (it != store.end()) {
        store.erase(it, store.end());
        return true; 
    } else {
        return false;
    }
}

template <typename KeyT, typename ValT, typename HashT>
size_t Hashtable<KeyT, ValT, HashT>::get_hash(const KeyT& key) {
    return hasher_(key) % buckets_.size();
}

template <typename KeyT, typename ValT, typename HashT>
typename Hashtable<KeyT, ValT, HashT>::StoreIter
Hashtable<KeyT, ValT, HashT>::Find(StoreT& store, const KeyT& key) {
    StoreIter it = std::find_if(store.begin(), store.end(),
                        [&key] (const ObjT& obj) {
                            return obj.first == key;
                        });
    return it;
}

template <typename KeyT, typename ValT, typename HashT>
typename Hashtable<KeyT, ValT, HashT>::StoreConstIter
Hashtable<KeyT, ValT, HashT>::Find(const StoreT& store, const KeyT& key) const {
    StoreConstIter it = std::find_if(store.begin(), store.end(),
                        [&key] (const ObjT& obj) {
                            return obj.first == key;
                        });
    return it;
}

template <typename KeyT, typename ValT, typename HashT>
typename Hashtable<KeyT, ValT, HashT>::StoreT&
Hashtable<KeyT, ValT, HashT>::get_store(const KeyT& key) {
    size_t hash_key =  get_hash(key);
    assert(hash_key >= 0 || hash_key < buckets_.size());
    return buckets_[hash_key];
}

template <typename KeyT, typename ValT, typename HashT>
const typename Hashtable<KeyT, ValT, HashT>::StoreT&
Hashtable<KeyT, ValT, HashT>::get_store(const KeyT& key) const {
    size_t hash_key =  get_hash(key);
    assert(hash_key >= 0 || hash_key < buckets_.size());
    return buckets_[hash_key];
}

template <typename KeyT, typename ValT, typename HashT>
typename Hashtable<KeyT, ValT, HashT>::StoreIter
Hashtable<KeyT, ValT, HashT>::GetStoreAndFind(const KeyT& key, StoreT** pstore) {
    StoreT& store = get_store(key);
    if (pstore) {
        *pstore = &store;
    }
    return Find(store, key);
    //return StoreIter();
}

template <typename KeyT, typename ValT, typename HashT>
typename Hashtable<KeyT, ValT, HashT>::StoreConstIter
Hashtable<KeyT, ValT, HashT>::GetStoreAndFind(
    const KeyT& key, StoreT** pstore) const {
    const StoreT& store = get_store(key);
    if (pstore) {
        *pstore = &store;
    }
    return Find(store, key);
}


}  // end namespace
