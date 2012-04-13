require "ffi"

module QuickFI
  def self.c_library dylib
    path_to_dylib = "#{File.expand_path "../../dylibs", __FILE__}/#{dylib}.so"
    m = Module.new do
      extend FFI::Library

      def self.load_dylib dylib
        ffi_lib dylib
      end

      def self.method_missing function, *args
        super unless args.length == 2 and args.first.kind_of? Array
        attach_function function, args.first, args.last
      end
    end

    m.load_dylib path_to_dylib
    yield m

    m
  end
end

