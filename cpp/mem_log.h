/*
A class for logging memory usage statistics.

*/

#include <stdint.h>

#ifndef MEM_LOG_H_
#define MEM_LOG_H_

class MemLog
{
public:
  MemLog();
  void incr_size(int delta_size);
  void incr_ptr_ops_ref(int delta_ops); // All pointer operations
  void incr_ptr_ops_asn(int delta_ops); // Only _moving_ a pointer
  void update_greatest_depth(uint32_t dep);
  uint32_t greatest_size();
  uint32_t greatest_depth();
  uint32_t size_bytes();
  uint32_t ptr_ops_ref(); // Get number of pointer dereferences
  uint32_t ptr_ops_asn(); // Only operations that _move_ a pointer.
private:
  uint32_t size_;
  uint32_t greatest_size_;
  uint32_t greatest_depth_;
  uint32_t ptr_ops_ref_; // Number of pointer dereferences
  uint32_t ptr_ops_asn_; // Number of pointer assignments
  void set_greatest_depth(uint32_t dep);
};

#endif // MEM_LOG_H_
