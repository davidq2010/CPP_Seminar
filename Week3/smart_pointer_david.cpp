// Smart Pointers
//
// In Java, we don't have control over Garbage Collection. Also, only memory is
// counted as a resource in Java; have to call open and close. C++ it's handled
// by constructor and destructor.
//
// Resource Acquisition is Initialization: the concept of allocating resources
// in constructor and deleting them in destructor.
//
void parse_some_data(const string& _file) {
  ofstream ofs(_file);

  if (ofs) {
    // Complex logic of parsing file
    // Many places this can go wrong.
    // In Java, we'd have to call ofs.close() before exiting (via a throw,
    // return, etc.). Except not really, b/c of you can try with resources in
    // Java. But in C++, we don't have to worry about this b/c destructor will
    // return resources when we exit.
  }
  else { // File not existing
    throw std::exception;
  }
}
