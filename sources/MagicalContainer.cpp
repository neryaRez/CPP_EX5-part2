#include "MagicalContainer.hpp"

using namespace std;

namespace ariel{

    MagicalContainer::MagicalContainer(){}
    MagicalContainer::~MagicalContainer(){}

    void MagicalContainer::addElement(int element) {

        auto it = lower_bound(data.begin(), data.end(), element);
        if (it != data.end() && *it == element) return; // If element already exists in the vector, no need to insert.  
        data.insert(it, element);  // Insert at the position determined by lower_bound.
        update_primes();
    
    }

    void MagicalContainer::update_primes(){

        primes.clear();
        for (size_t i = 0; i < data.size(); i++){
            if(is_prime(data[i])) primes.push_back(&data[i]);
        }
    }

    void MagicalContainer::removeElement(int element){

        auto it = lower_bound(data.begin(), data.end(), element);
        if(it == data.end() || *it != element) throw runtime_error("Element not found. can not be removed\n");
        
        data.erase(it);
        update_primes();
        
    }

    int MagicalContainer::size(){
        return this->data.size();
    }

    bool MagicalContainer::is_prime(int element){

        if(element < 2) return false;
        int sqr = sqrt(element);

        for (int i = 2; i <= sqr; i++){
            if (element%i == 0) return false;    
        }

        return true;   
    }

        // Iterator

    MagicalContainer::Iterator::Iterator( MagicalContainer& container) : my_container(&container) {
        this->index_order =0;
        this->position =0;
    }

    MagicalContainer::Iterator::Iterator(const Iterator& other): my_container(other.my_container) {
        this->index_order = other.index_order;
        this->position = other.position;
        this->type = other.type;
    }

    MagicalContainer::Iterator::Iterator(): my_container(nullptr){}

    MagicalContainer::Iterator::~Iterator() {}

    MagicalContainer::Iterator& MagicalContainer::Iterator::operator=(const Iterator& other) {
        this->index_order = other.index_order;
        this->my_container = other.my_container;
        this->position = other.position;
        this->type = other.type;
        return *this;
    }

    bool MagicalContainer::Iterator::operator==(const Iterator& other) const {

        if(other.type != this->type || other.my_container != this->my_container) 
            throw runtime_error("There is no comparing between iterators of different types, or containers\n");

        return this->index_order == other.index_order;
    }

    bool MagicalContainer::Iterator::operator!=(const Iterator& other) const {

        if(other.type != this->type || other.my_container != this->my_container) 
            throw runtime_error("There is no comparing between iterators of different types, or containers\n");

        return this->index_order != other.index_order;
    }

    bool MagicalContainer::Iterator::operator<(const Iterator& other) const {

        if(other.type != this->type || other.my_container != this->my_container) 
            throw runtime_error("There is no comparing between iterators of different types, or containers\n");

        return this->index_order < other.index_order;
    }

    bool MagicalContainer::Iterator::operator>(const Iterator& other) const {

        if(other.type != this->type || other.my_container != this->my_container) 
            throw runtime_error("There is no comparing between iterators of different types, or containers\n");

        return this->index_order > other.index_order;
    }

    int MagicalContainer::Iterator::operator*() const {

        return this->my_container->data[static_cast<size_t> (position)];
    }

    int MagicalContainer::Iterator::get_position() {
        return position;
    }

    int MagicalContainer::Iterator::get_index_order() {
        return this->index_order;
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

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {

        if( *this == this->end()) throw runtime_error("End should not be incremented\n");
        this->index_order++;
        this->position++;
        return *this;
    }
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin(){

        AscendingIterator beg;
        beg.my_container = this->my_container;
        beg.index_order = 0;
        beg.position = 0;
        return beg;
        
    }
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end(){
       
        AscendingIterator en;
        en.my_container = this->my_container;
        en.index_order = this->my_container->data.size();
        en.position = this->my_container->data.size();
        return en;

    }

    // SideCrossIterator

    MagicalContainer::SideCrossIterator::SideCrossIterator(): Iterator(){
        this->type = 's';
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) : Iterator(container) {
        this->type = 's';
        this->start_index = 1;
        this->end_index = this->my_container->size()-1;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other):Iterator(other) {
        this->start_index = other.start_index;
        this->end_index = other.end_index;
    }

    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {

        if( *this == this->end()) throw runtime_error("End should not be incremented\n");
    
        if(index_order%2 ==0)
        {
                this->position = end_index;
                end_index --;
        }
        else
        {
            this->position = start_index;
            start_index++;
        }
        this->index_order++;
        return *this;
    }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin(){

        SideCrossIterator beg;
        beg.my_container = this->my_container;
        beg.index_order = 0;
        beg.position = 0;
        beg.start_index = 1;
        beg.end_index = this->my_container->size()-1;

        return beg;
    }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end(){

        SideCrossIterator en;
        en.my_container = this->my_container;
        en.index_order = this->my_container->size();
        en.position = (my_container->size() / 2) + 1;
        en.start_index = en.position-1;
        en.end_index = en.position-1;

        return en;
    }

    // PrimeIterator

    MagicalContainer::PrimeIterator::PrimeIterator():Iterator() {
        this->type = 'p';
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) : Iterator(container) {
        this->type = 'p';
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other): Iterator(other) {}

    MagicalContainer::PrimeIterator::~PrimeIterator() {}

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {

        if( *this == this->end()) throw runtime_error("End should not be incremented\n");

        this->index_order++;
        this->position++;
        return *this;

    }
    int MagicalContainer::PrimeIterator::operator*() const{

        return *(this->my_container->primes[static_cast<size_t> (position)]);
    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin(){

        PrimeIterator beg;
        beg.my_container = this->my_container;
        beg.index_order = 0;
        beg.position = 0;
        return beg;
    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end(){
        
        PrimeIterator en;
        en.my_container = this->my_container;
        en.index_order = my_container->primes.size();
        en.position = my_container->primes.size();

        return en;
    }














}