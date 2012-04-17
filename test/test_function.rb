require_relative "quick_fi"
require "minitest/autorun"

TestFunction = QuickFI.c_library "test_function" do |c|
  c.string_length [:string], :int
end

class TestTestFunction < MiniTest::Unit::TestCase
  def setup
    @a_string = "Please excuse my dear aunt Sally"
  end

  def test_string_length_returns_string_length
    assert_equal(@a_string.length, TestFunction.string_length(@a_string))
  end
end

