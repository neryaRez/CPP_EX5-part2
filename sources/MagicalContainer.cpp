#include "MagicalContainer.hpp"

using namespace std;

namespace ariel{

    MagicalContainer::MagicalContainer(){}
    MagicalContainer::~MagicalContainer(){}


    void MagicalContainer::addElement(int element) {

        auto it = lower_bound(data.begin(), data.end(), element); //Uses binary search to find the proper place to insert. 
        if (it != data.end() && *it == element) return; // If element already exists in the vector, no need to insert.  
        data.insert(it, element);  // Insert at the position determined by lower_bound.
        update_primes(); // updating the addresses list of the prime numbers.
    }

    void MagicalContainer::update_primes(){

        primes.clear();
        for (size_t i = 0; i < data.size(); i++)
        {
            if(is_prime(data[i])) primes.push_back(&data[i]);
        }
    }

    void MagicalContainer::removeElement(int element){

        auto it = lower_bound(data.begin(), data.end(), element); // Uses binary search to find the element.
        if(it == data.end() || *it != element) throw runtime_error("Element not found. can not be removed\n");  
        data.erase(it);
        update_primes();  //delete and update the pointers list
    }

    int MagicalContainer::size(){
        return this->data.size(); // returns the size of the general data structure to all of the elements.
    }

    bool MagicalContainer::is_prime(int element){ //checks if number is prime

        if(element < 2) return false;
        int sqr = sqrt(element);
        for (int i = 2; i <= sqr; i++){
            if (element%i == 0) return false;    
        }
        return true;   
    }

        // Iterator

    MagicalContainer::Iterator::Iterator( MagicalContainer& _container) : container(&_container) {
        this->index_order =0;
    }

    MagicalContainer::Iterator::Iterator(const Iterator& other): container(other.container) {
        this->index_order = other.index_order;
        this->type = other.type;
    }

    MagicalContainer::Iterator::Iterator(): container(nullptr){}

    MagicalContainer::Iterator::~Iterator() {}

    bool MagicalContainer::Iterator::operator==(const Iterator& other) const {

        if(other.type != this->type || other.container != this->container) 
            throw runtime_error("There is no comparing between iterators of different types, or containers\n");

        return this->index_order == other.index_order;
    }

    bool MagicalContainer::Iterator::operator!=(const Iterator& other) const {

        if(other.type != this->type || other.container != this->container) 
            throw runtime_error("There is no comparing between iterators of different types, or containers\n");

        return this->index_order != other.index_order;
    }

    bool MagicalContainer::Iterator::operator<(const Iterator& other) const {

        if(other.type != this->type || other.container != this->container) 
            throw runtime_error("There is no comparing between iterators of different types, or containers\n");

        return this->index_order < other.index_order;
    }

    bool MagicalContainer::Iterator::operator>(const Iterator& other) const {

        if(other.type != this->type || other.container != this->container) 
            throw runtime_error("There is no comparing between iterators of different types, or containers\n");

        return this->index_order > other.index_order;
    }

    // AscendingIterator

    MagicalContainer::AscendingIterator::AscendingIterator() :Iterator(){
        this->type = 'a';
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) : Iterator(container) {
        this->type = 'a';
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) : Iterator(other) {}

    MagicalContainer::AscendingIterator::~AscendingIterator(){}

    //assignment operator
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other){
        
        if (this->container != other.container ) 
        throw runtime_error("Iterator can not be initialized to operator of different container\n"); 
        this->index_order = other.index_order;
        return *this;
    }
    //dereference operator 
    int MagicalContainer::AscendingIterator::operator*() const {

        if(index_order == container->size())
            throw runtime_error("End should not be dereferenced\n");

        return container->data[static_cast<size_t> (index_order)];

    }
    //incerases the iterator by its logical order.
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {

        if( *this == this->end()) throw runtime_error("End should not be incremented\n");
        this->index_order++;
        return *this;
    }
    // returns the start_point of the iterator
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin(){

        AscendingIterator beg;
        beg.container = this->container;
        beg.index_order = 0;
        return beg;
    }
    // returns the end_point of the iterator
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end(){
       
        AscendingIterator en;
        en.container = this->container;
        en.index_order = this->container->data.size();
        return en;

    }

    //SideCrossIterator

    MagicalContainer::SideCrossIterator::SideCrossIterator(): Iterator(){
        this->type = 's';
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) : Iterator(container) {
        this->type = 's';
        this->start_index = 0;
        this->end_index = this->container->size()-1;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other):Iterator(other) {
        this->start_index = other.start_index;
        this->end_index = other.end_index;
    }

    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other){
        if (this->container != other.container ) 
        throw runtime_error("Iterator can not be initialized to operator of different container\n"); 
        
        this->index_order = other.index_order;
        this->end_index = other.end_index;
        this->start_index = other.start_index;

        return *this;
    }

    int MagicalContainer::SideCrossIterator::operator*() const{

        if(index_order == container->size())
            throw runtime_error("End should not be dereferenced\n");

        if(index_order%2 ==0) return container->data[static_cast<size_t> (start_index)];

        else return container->data[static_cast<size_t> (end_index)];

    }
    

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {

        if( *this == this->end()) throw runtime_error("End should not be incremented\n");
    
        if(index_order%2 ==0) start_index++;
       
        else end_index--;
       
        this->index_order++;
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin(){

        SideCrossIterator beg;
        beg.container = this->container;
        beg.index_order = 0;
        beg.start_index = 0;
        beg.end_index = this->container->size()-1;

        return beg;
    }
    
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end(){

        SideCrossIterator en;
        en.container = this->container;
        en.index_order = this->container->size();
        en.start_index = (container->size() / 2);
        en.end_index = (container->size() / 2);

        return en;
    }

    //PrimeIterator

    MagicalContainer::PrimeIterator::PrimeIterator():Iterator() {
        this->type = 'p';
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) : Iterator(container) {
        this->type = 'p';
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other): Iterator(other) {}

    MagicalContainer::PrimeIterator::~PrimeIterator() {}

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other){

        if (this->container != other.container ) 
        throw runtime_error("Iterator can not be initialized to operator of different container\n"); 
        this->index_order = other.index_order;
        return *this;
        
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {

        if( *this == this->end()) throw runtime_error("End should not be incremented\n");
        this->index_order++;
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*() const{

        if(index_order == container->primes.size())
            throw runtime_error("End should not be dereferenced\n");

        return *(container->primes[static_cast<size_t> (index_order)]);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin(){

        PrimeIterator beg;
        beg.container = this->container;
        beg.index_order = 0;
        return beg;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end(){
        
        PrimeIterator en;
        en.container = this->container;
        en.index_order = container->primes.size();
        return en;
    }
}