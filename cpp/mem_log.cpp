/*
A class for logging memory usage statistics.

*/

#include "mem_log.h"

// Initialize the counters to zero.
MemLog::MemLog() {
  size_ = 0;
  greatest_size_ = 0;
  ptr_ops_all_ = 0;
  ptr_ops_asn_ = 0;
}

// Increment the size field, and track if it changes the greatest size attained.
void MemLog::incr_size(int delta_size) {
  size_ += delta_size;
  if (size_ > greatest_size_)
    greatest_size_ = size_;
}

// Increment the number of pointer operations.
void MemLog::incr_ptr_ops_all(int delta_ops) {
  ptr_ops_all_ += delta_ops;
}

// Increment the number of pointer assignments, which also increments the tally
// of all operations.
void MemLog::incr_ptr_ops_asn(int delta_ops) {
  ptr_ops_asn_ += delta_ops;
  incr_ptr_ops_all(delta_ops);
}

// Retrieve the largest that the object has ever been
uint32_t MemLog::greatest_size() {
  return greatest_size_;
}

// Retrieve the current size of the object in bytes
uint32_t MemLog::size_bytes() {
  return size_;
}

// Retrieve the number of all pointer operations
uint32_t MemLog::ptr_ops_all() {
  return ptr_ops_all_;
}

// Return the number of pointer assignments
uint32_t MemLog::ptr_ops_asn() {
  return ptr_ops_asn_;
}
