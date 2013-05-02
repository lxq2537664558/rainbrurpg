
=begin
    Handle a single source file line

    $1 the type of source (m/doxy/path/file/)
    $2 the source location
=cut
sub handle_source
{
    my ($type, $path) = @_;
    print "$type => $path\n";
    
}

1;
