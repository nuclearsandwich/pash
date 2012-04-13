A directory for super neat Unit tests written in Ruby.

In order to write a unit test do the following:

Assume the file you've created is called `my_lib.c` and resides in
`src/my_lib.c` and has the following functions.
    #include <string.h>
    int string_length(char* str) {
      return strlen(str);
    }
    
    int add_five(int n) {
      return n + 5;
    }

* Add dylibs/my_lib.so to the list of dylibs in the `Makefile`
    dylibs: dylibs/some_other_lib.so dylibs/my_lib.so

* Create a Ruby file in the `test` directory (this one) with a name matching the
  library. In this case, `test/my_lib_test.rb`

* Within the file, add the following preamble:
    require_relative "quick_fi" # Load Steven!'s easy C loader
    require "minitest/autorun" # Load the unit testing framework
    
    MyLib = QuickFI.c_library "my_lib" do |c|
      c.string_length [:string], :int
      c.add_five [:int], :int
    end

As you can see, this code has a simple pattern

    CamelCaseCFileName = QuickFI.c_library "your library's name" do |c|
      c.c_function_name [:array_of_c_args], :c_return_type
    end

You can now call any of the functions declared from the Ruby code.
