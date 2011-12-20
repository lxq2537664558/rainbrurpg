#!/usr/bin/ruby

require 'test/unit'
require 'next_release'

class ParserTest < Test::Unit::TestCase
  def test_parser_changelog?
    assert(Parser.new.changelog? "=== ChangeLog ===")
    assert(Parser.new.changelog? "=== CHANGELOG ===")
  end

  def test_parser_items_by_revsion?
    p = Parser.new
    assert(p.items_by_revision? "(5 items by revisions)")
    assert(p.items_by_revision == 5, 
           "items_by_revision member should be 5 but is #{p.items_by_revision}")

    assert(p.items_by_revision? "(18 items by revisions)")
    assert(p.items_by_revision == 18)

    assert(p.items_by_revision? "   (4 items by revisions)")
    assert(p.items_by_revision == 4)

  end

  def test_parser_version?
    assert(Parser.new.version? "* v0.0.0-5")
    assert(Parser.new.version?("    * vlkjdf") == nil)
  end

  def test_parser_item?
    assert(Parser.new.item? "- azeaze")
    assert(Parser.new.item?("  lkj - azeaze") == nil)
  end

  def test_parser_states_initialization
    p = Parser.new
    assert(p.found_changelog == false)
    assert(p.found_items_by_revision == false)
    assert(p.found_version == false)
    assert(p.must_exit == false)
  end

  def test_parser_state_changelog
    p = Parser.new
    p.changelog? "=== ChangeLog ==="
    assert(p.found_changelog)
    
  end

  def test_parser_states
    p = Parser.new

    # Before we found ChangeLog items and version should be stated
    p.items_by_revision? "(5 items by revisions)"
    assert(p.found_items_by_revision == false)

    p.version? "* v0.0.0-5"
    assert(p.found_version == false)

    # We should find them in this order
    p.changelog? "=== ChangeLog ==="
    assert(p.found_changelog)
    
    p.items_by_revision? "(5 items by revisions)"
    assert(p.found_items_by_revision)

    p.version? "* v0.0.0-5"
    assert(p.found_version)
  end

  def test_increment_item
    p = Parser.new
    
    # We can't increment item since Changelog and Item_by_revision not found
    p.item? "- azeaze"
    assert(p.items == 0)
    p.items_by_revision? "(5 items by revisions)"
    p.item? "- azeaze"
    assert(p.items == 0)

    # But we must increment if all found
    p = Parser.new
    p.parse_line "=== ChangeLog ==="
    p.parse_line "(5 items by revisions)"
    p.parse_line "* v0.0.0-5"
    p.parse_line "- azeaze"
    assert(p.items == 1)
    p.parse_line "- azeaze"
    p.parse_line "- azeaze"
    assert(p.items == 3)

    # A second version item must exit
    assert(p.parse_line("* v0.0.0-4") == true)
    assert(p.must_exit == true)

    # And we can't count items anymore
    p.parse_line "- azeaze"
    assert(p.items == 3)
  end
end
