require "aruba/cucumber"

bin_dir = File.expand_path File.dirname(__FILE__) + "/../.."
test_tools_bin_dir = File.expand_path bin_dir + "/../test_tools/bin"
puts bin_dir, test_tools_bin_dir
ENV["PATH"] = "#{bin_dir}#{File::PATH_SEPARATOR}#{test_tools_bin_dir}"

puts ENV["PATH"]
