/* Remi Trettin COP4530 Assignment 5 */

// default constructor that inits underlying vector and currentSize
template <typename K, typename V>
HashTable<K, V>::HashTable(std::size_t n) : currentSize{0}, bucketVector(prime_below(n), std::list<std::pair<K, V>>()) {
}

// deletes all contents of the hash table
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
	makeEmpty();
}

// returns true if the key,value pair is found in the hash table
template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V>& kv) const {
	std::size_t i;
	if(contains(kv.first))
		i = myhash(kv.first);
	else
		return false;
	for(auto obj : bucketVector[i]) {
		if(obj.second == kv.second)
			return true;
	}
	return false;
}

// returns true if only the key is found in the hash table
template <typename K, typename V>
bool HashTable<K, V>::contains(const K &x) const {
	std::size_t i = myhash(x);
	if(bucketVector[i].empty())
		return false;
	for(auto obj : bucketVector[i]) {
		if(x == obj.first)
			return true;
	}
	return false;
}

// empties the hash table
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
	if(bucketVector.empty())
		return;

	for(auto itr = bucketVector.begin(); itr != bucketVector.end(); ++itr) {
		(*itr).clear();
	}
	currentSize = 0;
}

// empties the hash table
template <typename K, typename V>
void HashTable<K, V>::clear() {
	makeEmpty();
}

// returns the current size of the hash table
template <typename K, typename V>
std::size_t HashTable<K, V>::size() const {
	return currentSize;
}

// inserts a new item into the hash table
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) {
	std::size_t i = myhash(kv.first);
	if(match(kv))
	 	return false;
	if(contains(kv.first)) {
		for(auto itr = bucketVector[i].begin(); itr != bucketVector[i].end(); ++itr) {
			if(itr->first == kv.first) {
				itr->second = kv.second;
				currentSize++;
				if(currentSize > bucketVector.size()) {
					rehash();
				}
				return true;
			}
		}
	}
	bucketVector[i].push_back(kv);
	currentSize++;
	if(currentSize > bucketVector.size()) {
		rehash();
	}
	return true;
}

// inserts a new item into the hash table for the rehash() function
template <typename K, typename V>
bool HashTable<K, V>::rehashinsert(const std::pair<K, V> & kv) {
	std::size_t i = myhash(kv.first);
	bucketVector[i].push_back(kv);
	currentSize++;
	return true;
}

// move version of insert
template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv) {
	return insert(kv);
}

// removes an item from the hash table
template <typename K, typename V>
bool HashTable<K, V>::remove(const K &x) {
	if(contains(x)) {
		std::size_t i = myhash(x);
		for(auto itr = bucketVector[i].begin(); itr != bucketVector[i].end(); ++itr) {
			if(itr->first == x) {
				bucketVector.at(i).erase(itr);
				currentSize--;
				return true;
			}
		}
	}
	return false;
}

// loads item into the hash table from a file
template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
	std::ifstream inputFile;
	inputFile.open(filename);
	if(inputFile.is_open()) {
		std::string fileline;
		while(std::getline(inputFile, fileline)) {
			std::istringstream iss(fileline);
			std::string key, value;
			iss >> key >> value;
			std::pair<std::string, std::string> p = std::make_pair(key, value);
			this->insert(p);
		}
		inputFile.close();
		return true;
	}else {
		return false;
	}
}

// outputs the contents of the hash table
template <typename K, typename V>
void HashTable<K, V>::dump() const {
	int x = 0;
	for(auto itr = bucketVector.begin(); itr != bucketVector.end(); ++itr) {
		std::cout << "v[" << x << "]: ";
		if(!(*itr).empty()) {
			for(auto obj : *itr) {
				if((*itr).front().first != obj.first) {
					std::cout << ":";
				}
				std::cout << obj.first << " " << obj.second;
			}
		}
		std::cout << std::endl;
		++x;
	}
}

// writes the contents of the hash table to a file
template <typename K, typename V>
bool HashTable<K, V>::write_to_file(char *filename) {
	std::ofstream outputFile;
	outputFile.open(filename);
	for(std::list<std::pair<K, V>> & cellList : bucketVector) {
		for(std::pair<K, V> & x : cellList) {
			outputFile << x.first << " " << x.second << std::endl;
		}
	}
	outputFile.close();
	return true;
}

// rehashes the table if the size limit is reached
template <typename K, typename V>
void HashTable<K, V>::rehash(){
	int newSize = bucketVector.size() * 2;
	std::vector<std::list<std::pair<K, V>>> tempTable = bucketVector;
	bucketVector.resize(prime_below(newSize));
	for(std::list<std::pair<K, V>> & cellList : bucketVector) {
		cellList.clear();
	}
	currentSize = 0;
	for(std::list<std::pair<K, V>> & cellList : tempTable) {
		for(std::pair<K, V> & x : cellList) {
			this->rehashinsert(x);
		}
	}
}

// computes the hash for an input key
template <typename K, typename V>
std::size_t HashTable<K, V>::myhash(const K &k) const {
	std::hash<K> h;
	return h(k) % bucketVector.size();
}

// generates a prime number below n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n) {
	if (n > max_prime) {
		std::cerr << "** input too large for prime_below()\n";
		return 0;
	}
	if (n == max_prime) {
		return max_prime;
	}
	if (n <= 1) {
		std::cerr << "** input too small \n";
		return 0;
	}
	std::vector<unsigned long> v(n+1);
	setPrimes(v);
	while (n > 2) {
		if (v[n] == 1)
			return n;
		--n;
	}
	return 2;
}

template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes) {
	int i = 0;
	int j = 0;
	vprimes[0] = 0;
	vprimes[1] = 0;
	int n = vprimes.capacity();

	for (i = 2; i < n; ++i)
		vprimes[i] = 1;
	for( i = 2; i*i < n; ++i) {
		if (vprimes[i] == 1)
			for(j = i + i ; j < n; j += i)
				vprimes[j] = 0;
	}
}
