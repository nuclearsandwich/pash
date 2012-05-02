require_relative "quick_fi"
require "minitest/autorun"

PathLookup = QuickFI.c_library "path_lookup" do |c| # load shared object (external library) path_lookup as compiled by makefile to .so
  c.resolve_data [:string], :string # [:pamarter], :return_type
  c.resolve_path [:string], :string
  c.searchVariable [:string, :string] :string
  c.searchPath [:string, :string] :string
end

# char* resolve_data(char* inputFileName);
# char* resolve_path(char* inputFileName);
# char* searchVariable(char* inputVariable, char* inputExecutableName);
# char* searchPath(char* inputPath, char* inputExecutableName);

class TestPathLookup < MiniTest::Unit::TestCase
  def setup
    @inputPath = "/home/user/sean/code"
  end

  def test_string_length_returns_string_length
    assert_equal(@a_string.length, PathLookup.string_length(@a_string))
  end
end