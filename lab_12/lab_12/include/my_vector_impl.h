template<class T>
void my_vector<T>::swap(my_vector<T>& other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(array_, other.array_);
}

static std::size_t min_power_2(std::size_t n){
    if (n<=1){
        return (std::size_t)1;
    }
    n--;
    size_t cnt = 0;
    while(n != 0){
        cnt++;
        n>>=1;
    }
    return (size_t)(1<<cnt);
}

template<typename T>
my_vector<T>::my_vector() : my_vector<T>::my_vector((std::size_t)0) {
}

template<typename T>
my_vector<T>::my_vector(std::size_t n) {
    capacity_ = min_power_2(n);
    size_ = n;
    std::uint8_t* buf = new std::uint8_t [sizeof(T)*capacity_];
    array_ = (T*) buf;
    if (std::is_default_constructible<T>::value){
        for(size_t i=0; i<capacity_; i++){
		new (&(array_[i])) T();
        }
    }
}
            

template<typename T>
my_vector<T>::my_vector(const my_vector<T>& other) : my_vector<T>::my_vector(other.capacity()) {
    static_assert(std::is_copy_constructible<T>::value, "It is not CopyConstructible type!");
    size_ = other.size();
    for(size_t i=0; i<size_; i++){
        array_[i] = other[i];
    }
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T>& other){
    static_assert(std::is_copy_constructible<T>::value, "It is not CopyConstructible type!");
    my_vector<T> tmp(other);
    my_vector<T>::swap(tmp);
    return *this;
}

template<typename T>
my_vector<T>::~my_vector(){
    static_assert(std::is_destructible<T>::value, "It is not Destructible type!");
    for(size_t i=0; i<size_; i++){
        array_[i].~T();
    }
    if (std::is_default_constructible<T>::value){
        for(size_t i=size_; i<capacity_; i++){
            array_[i].~T();
        }
    }
    std::uint8_t* buf = (std::uint8_t*)array_;
    if (array_ != NULL){
        delete [] buf;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const my_vector<T>& v){
    out << "my vector: ";
    for(size_t i=0; i<v.size(); i++){
        out << v[i] << " ";
    }
    return out;
}

template<typename T>
std::size_t my_vector<T>::size() const {
    return size_;
}

template<typename T>
std::size_t my_vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool my_vector<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
void my_vector<T>::resize(std::size_t n){
    if (n > capacity_){
        my_vector<T>::reserve(n);
    }
    size_ = n;
}

template<typename T>
void my_vector<T>::reserve(std::size_t n){
    if (capacity_ < n){
        my_vector<T> tmp(n);
        T* tmp_array = array_;
        my_vector<T>::swap(tmp);
        size_ = tmp.size();
        std::copy(tmp_array, tmp_array+tmp.size(), array_);
    }
}

template<typename T>
T& my_vector<T>::operator[](std::size_t index) const {
    if (index >= size_){
        exit(-1);
    }
    return array_[index];
}

template<typename T>
void my_vector<T>::push_back(const T& t){
    static_assert(std::is_copy_constructible<T>::value, "It is not CopyConstructible type!");
    if(size_ == capacity_){
        my_vector<T>::reserve(capacity_*2);
    }
    array_[size_] = t;
    size_++;
}

template<typename T>
void my_vector<T>::pop_back(){
    if(size_ != 0){
        size_--;
    }
}

template<typename T>
void my_vector<T>::clear(){
    my_vector<T> tmp;
    my_vector<T>::swap(tmp);
}
