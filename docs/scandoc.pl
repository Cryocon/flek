#!/usr/bin/perl

require "ctime.pl";
require "getopts.pl";

# Get the current date
$date = &ctime(time);

# Set the default tab size and output file name
$tabSize = 4;
$destpath = "";

# Set up default templates
&Getopts( 'i:d:p:t:' );

if ($#ARGV < 0) {
    die "Usage: -i <doc-template> -p <output-path> -t<tabsize> -d<sym>=<value> [ <input-files> ... ]\n";
}

&readtemplate( $opt_i || "template.html" );

$destpath = $opt_p;
$tabSize = $opt_t if ($opt_t);

# Handle defines
if ($opt_d)
{
    foreach $def (split( /,/, $opt_d )) {
	if ($def =~ /\s*(\w*)\=(.*)/) {
	    $${1} = $2;
	}
	else {
	    $${1} = 1;
	}
    }
}

# For each input filename, parse it
while ($srcfile = shift(@ARGV)) {

    open( FILE, $srcfile ) || die "Can't open file $srcfile\n";
    print STDERR "Reading \"$srcfile\"\n";

    $docTag = 'description';
    $docEmpty = 1;
    $packageName = '.general';
    $author = '';
    $version = '';
    $class = 0;
    $_ = '';

    while (&parse_declaration( '' )) {}
}

# Collate subclasses and associate with class record.
foreach $className (keys %subclasses) {
    my $class = &class_record( $className );
    
    if ($class) {
      my @subs = ();
      # print STDERR "$className ", join( ',', @{$subclasses{ $className }} ), "\n";
      foreach $subName ($subclasses{ $className }) {
	if (&class_record( $subName )) {
	  push @subs, $subName;
	}
	$class->{ 'subs' } = @subs;
      }
    }
}

# Turn packages into objects. Special case for "default" package.
foreach $pkg (keys %packages)
{
#    print STDERR $pkg, "\n";
    bless $packages{ $pkg }, PackageRecord;
    if ($pkg eq '.general') {
	$packages{ $pkg }{ 'name' } = "General";
    }
    else {
	$packages{ $pkg }{ 'name' } = $pkg;
    }
#    print STDERR $packages{ $pkg }->Classes(), "\n";
}

# Execute template file
   # print STDERR $docTemplate; # For debugging
eval $docTemplate;
print STDERR $@;

exit;

# ======================= Subroutines ================================

# Read a line of input, and remove blank lines and preprocessor directives.
sub rdln {
    while (/^(\s*|#.*)$/ && ($_ = <FILE>)) {}
}

# Remove comments from current line
sub removeComment	{
    s|//.*||;
}

# parsing functions
sub matchKW		{ &rdln; s/^\s*(@_[0])// && $1; }
sub matchStruct		{ &rdln; s/^\s*(struct|class)// && $1; }
sub matchPermission	{ &rdln; s/^\s*(public|private|protected)// && $1; }
sub matchID		{ &rdln; s/^\s*([A-Za-z_]\w*)//	&& $1; }
sub matchColon		{ &rdln; s/^\s*\://; }
sub matchComma		{ &rdln; s/^\s*\,//; }
sub matchSemi		{ &rdln; s/^\s*\;//; }
sub matchRBracket	{ &rdln; s/^\s*\{//; }
sub matchLBracket	{ &rdln; s/^\s*\}//; }
sub matchRParen		{ &rdln; s/^\s*\(//; }
sub matchLParen		{ &rdln; s/^\s*\)//; }
sub matchRAngle		{ &rdln; s/^\s*\<//; }
sub matchLAngle		{ &rdln; s/^\s*\>//; }
sub matchDecl		{ &rdln; s/^(\s*[\s\w\*\[\]\~\&\n]+)// && $1; }
sub matchOper		{ &rdln; s/^\s*([\~\&\^\>\<\=\!\%\*\+\-\/\|\w]*)// && $1; }
sub matchFuncOper	{ &rdln; s/^\s*(\(\))// && $1; }
sub matchAny		{ &rdln; s/^\s*(\S+)// && $1; }
sub matchChar		{ &rdln; s/^(.)// && $1; }
sub matchString 	{ &rdln; s/^\"(([^\\\"]|(\\.)))*\"// && $1; }

# Skip to next semicolon
sub skipToSemi {

    while (!&matchSemi) {

	&rdln;
	s|//.*||;			# Eat comments
	if (&matchLBracket) {
	    &skipBody;
	    next;
	}
	last if !s/^\s*([^\s\{\;]+)//;
#	print STDERR "$1 ";
    };
}

# Skip function body
sub skipBody {
    local( $nest );
	
    $nest = 1;
	
    for (;;)
    {
	if (&matchRBracket) { $nest++; }
	elsif (&matchLBracket)
	{
	    $nest--;
	    last if !$nest;
	}
	else { last if &matchKW( "[^\{\}]" ) eq ""; }
    }
}

# Parse (*name) syntax
sub parse_paren_pointer {
    if (s/^(\s*\(\s*\*)//) {
	$decl .= $1;
	$nest = 1;

	for (;;)
	{
	    # Preserve spaces, eliminate in-line comments
	    &removeComment;
	    while (s/^(\s+)//) { $decl .= $1; &rdln; }

	    if (&matchRParen) { $nest++; $decl .= "("; }
	    elsif (&matchLParen)
	    {
		$decl .= ")";
		$nest--;
		last if !$nest;
	    }
	    elsif ($d = &matchKW( "[^\(\)]*" )) { $decl .= $d; }
	    else { last; }
	}

	# Just in case there are array braces afterwards.
	while ($d = &matchDecl) { $decl .= $d; }
    }
}

# Parse template arguments
sub matchAngleArgs {

    if (&matchRAngle) {
	local ($args, $nest);

	$args = "&lt;";
	$nest = 1;

	for (;;)
	{
	    if (&matchRAngle) { $nest++; $args .= "&lt;"; }
	    elsif (&matchLAngle)
	    {
		$nest--;
		$args .= "&gt;";
		last if !$nest;
	    }
	    elsif ($d = &matchChar) { $args .= $d; }
	    else { last; }
	}
	return $args;
    }
    else { return ''; }
}

# convert tabs to spaces
sub expand_tabs {
    local	($text) = @_;
    local 	($n);

    while (($n = index($text,"\t")) >= 0) {
	substr($text, $n, 1) = " " x ($tabSize-($n % $tabSize));
    }
	
    return $text;
}

# Process a line of text from a "special" comment
sub handleCommentLine {
    local ($_) = @_;

    if ($docEmpty)
    {
	# Eliminate blank lines at the head of the doc.
	return if (/^\s*$/);
    }

    # First, expand tabs.
    $_ = &expand_tabs( $_ );
    
    # Remove gratuitous \s*\s
    s/\s*\*\s//g;

    #print $_;
    #print "\n\n";

    # If it's one of the standard tags
    if (s/^\s*\@(see|package|version|author|param|return|result|exception|keywords|deffunc|defvar|heading|todo)\s*//)
    {
	my $tag = $1;
	$tag = 'return' if ($tag eq 'result');

	# for param and exception, split the param name and the text
	# seperate them with tabs.
	if ($tag eq "param" || $tag eq "exception") {
	    s/^\s*(\w+)\s*(.*)/\t$1\t$2/;
	}
	elsif ($tag eq "heading") {
	    # 'heading' is processed by the template, if at all.
	    $_ = "\@heading\t$_";
	    $tag = "description";
	}
	elsif ($tag eq 'todo') {
	    if ($todolist{ $srcfile } ne '') {
		$todolist{ $srcfile } .= "\n";
	    }
	}

	# If it's @deffunc or @defvar
	if ($tag =~ /def(.*)/) {

	    $type = $1;
	    
	    # @deffunc and @defvar force a comment to be written out as if there was a
	    # declaration.
	    # Designed for use with macros and other constructs I can't parse.

	    if (/(\S+)\s+(.*)$/)
	    {
		$name = $1;
		$decl = $2;
		$dbname = &uniqueName( "$baseScope$name" );

		my $entry = { 'type'    => $type,
			      'name'    => $name,
			      'longname'=> $name,
			      'fullname'=> "$name",
			      'scopename'=>"$baseScope$name",
			      'uname'   => $dbname,
			      'decl'    => $decl,
			      'package' => $packageName };

		if ($class) {
		    $entry->{ 'class' } = "$context";
		    $class->{ 'members' }{ $dbname } = $entry;
		}
		else {
		    $packages{ $packageName }{ 'globals' }{ $dbname } = $entry;
		}
		$docTag = 'description';
		&dumpComments( $entry );
		return;
	    }
	}
	elsif ($tag eq 'package') {
	    s/^\s*//;
	    s/\s*$//;
	    $packageName = $_;
	    $docTag = 'description';
	    return;
	}
	elsif ($tag eq 'author') {
	    $author = $_;
	    $docTag = 'description';
	    return;
	}
	elsif ($tag eq 'version')
	{
	    $version = $_;
	    $docTag = 'description';
	    return;
	}

	$docTag = $tag;
    }
    elsif (/^\s*@\w+/)
    {
	# any other line that begins with an @ should be inserted into the main
	# description for later expansion.
	$docTag = 'description';
    }

    # "To-do" lists are handled specially, and not associated with a class.
    if ($docTag eq 'todo') {
	$todolist{ $srcfile } .= $_;
	return;
    }
   
    # Append to current doc tag, regardless of whether it's a new line
    # or a continuation. Also mark this doc as non-empty.
    $docTags{ $docTag } .= $_;
    $docEmpty = 0;
    
    # @see doesn't persist.
    if ($docTag eq 'see') { $docTag = 'description'; }

#    print STDERR ":$_";
}

# Clear doc tag information at end of class or file
sub clearComments {

    $docTag = 'description';
    $docEmpty = 1;
    %docTags = ();
}

# Add doc tag information to current documented item
sub dumpComments {
    local ($hashref) = @_;

    if ($docEmpty == 0) {

	if ($author ne  '') { $hashref->{ 'author'  } = $author;  }
	if ($version ne '') { $hashref->{ 'version' } = $version; }
	$hashref->{ 'sourcefile' } = $srcfile;

	# Store the tags for this documentation into the global doc symbol table
	foreach $key (keys %docTags) {
	    my $data = $docTags{ $key };

	    $data =~ s/\s*$//;

	    $hashref->{ $key } = $data;
	}
    }

    &clearComments();
}

# Generate a unique name from the given name.
sub uniqueName {
    local ($name) = @_;
	
    # Duplicate doc entries need to be distinguished, so give them a different label.
    while ($docs{ $name }) {
	if ($name =~ /-(\d+)$/) {
	    $name = $` . "-" . ($1 + 1);
	}
	else { $name .= "-2"; }
    }

    $docs{ $name } = 1;
    return $name;
}

# Get the current class record.
sub class_record {
    local ($className) = @_;
    local ($pkg) = $classToPackage{ $className };

    if ($pkg)
    {
	return $packages{ $pkg }{ 'classes' }{ $className };
    }
    0;
}

# Parse a declaration in the file
sub parse_declaration {

    local ($context) = @_;
    local ($baseScope) = '';
    local ($decl);
	
    if ($context) { $baseScope = $context . "::"; }

    &rdln;

    if (s|^\s*//\*\s+||) {
	# Special C++ comment
	&handleCommentLine( $' );
	$_ = ''; &rdln;
    }	
    elsif (s|^\s*//||) { 
	# Ordinary C++ comment
	$_ = '';
	&rdln;
    }
    elsif (s|^\s*\/\*\*\s+||) {
	# Special C comments

	s/\={3,}|\-{3,}|\*{3,}//;			# Eliminate banner strips
	$text = '';
	$docTag = 'description';

	# Special comment
	while (!/\*\//) { &handleCommentLine( $_ ); $text .= $_; $_ = <FILE>; }
	s/\={3,}|\-{3,}|\*{3,}//;			# Eliminate banner strips
	/\*\//;
	&handleCommentLine( $` );
	$text.= $`; $_ = $';
    }
    elsif (s|^\s*\/\*||) {
	# Ordinary C comment
	$text = "";

	while (!/\*\//) { $text .= $_; $_ = <FILE>; }
	/\*\//;
	$text.= $`; $_ = $';
    }
    elsif ($tag = &matchKW( "template" )) {
	# Template definition
	$args = &matchAngleArgs;
	&rdln;
		
	$tmplParams = $args;
	$result = &parse_declaration( $context );
	$tmplParams = '';
	return $result;
    }
    elsif ($tag = &matchKW( "class|struct" )) {
	# Class or structure definition
	local ($className,$class);

	if ($className = &matchID) {
			
	    return 1 if (&matchSemi);		# Only a struct tag

	    # A class instance
	    if ($varname = &matchID) {
		&matchSemi;
		return 1;
	    }
 
	    my $fullName = "$baseScope$className$tmplParams";
	    # print STDERR "CLASS $fullName\n";
			
	    my @bases = ();

	    if (&matchColon) {
		
		for (;;) {
		    my $p;
		    &matchKW( "virtual" );
		    $perm = "private";
		    if ($p = &matchKW( "public|private|protected" )) { $perm = $p; }
		    &matchKW( "virtual" );
				
		    last if !($base = &matchID);
					
		    push @bases, $base;
		    push @{ $subclasses{ $base } }, $fullName;
		    # print STDERR " : $perm $base\n";
		    last if !&matchComma;
		}
	    }

#	    print STDERR "\n";
#	    print STDERR "parsing class $fullName\n";

	    if ($docEmpty == 0)
	    {
		$class = { 'type'    => $tag,
			   'name'    => $fullName,
			   'longname'=> "$tag $className",
			   'fullname'=> "$tag $className$tmplParams",
			   'scopename'=> "$tag $fullName",
			   'uname'   => $fullName,
			   'bases'   => \@bases,
			   'package' => $packageName,
			   'members' => {} };

#		print STDERR "$className: @bases\n";

		bless $class, ClassRecord;

		print STDERR "   parsing class $fullName\n";
#		$classToPackage{ $className } = $packageName;
		$classToPackage{ $fullName } = $packageName;
#		$classList{ $className } = $class;
		$classList{ $fullName } = $class;
		$packages{ $packageName }{ 'classes' }{ $fullName } = $class;
		&dumpComments( $class );
	    }

	    if (&matchRBracket) {
		local ($perm) = ("private");

		while (!&matchLBracket)
		{
		    my $p;
		    if ($p = &matchKW( "public\:|private\:|protected\:" ))
		    {
			$perm = $p;
		    }
		    else
		    {
			&parse_declaration( $fullName )
			    || die "Unmatched brace!\n";
		    }
		}
				
		&matchSemi;
	    }
			
	    &clearComments;
	}
    }
    elsif (&matchKW( "enum" ) || &matchKW( "typedef" ))
    {
	&skipToSemi;
    }
    elsif (&matchKW( "friend\s*class" ))
    {
	&skipToSemi;
    }
#	elsif ($kw = &matchID)
#	{
#		$type = "$kw ";
#
#		if ($kw =~/virtual|static|const|volatile/) {
#			$type .= &typ;
#		}
#	}
    elsif ($decl = &matchDecl)
    {
	return 1 if ($decl =~ /^\s*$/);

	# Eliminate in-line comments
	&removeComment;

	# Check for multi-line declaration
	while ($d = &matchDecl) { $decl .= $d; }
		
	# Handle template args, but don't let operator overloading confuse us!
	$tempArgs = '';
	if (!($decl =~ /\boperator\b/) && ($tempArgs = &matchAngleArgs))
	{
	    $tempArgs = $decl . $tempArgs;
	    $decl = '';
	    while ($d = &matchDecl) { $decl .= $d; }
	}

	# Look for (*name) syntax
	&parse_paren_pointer;

	# Special handling for operator... syntax
	$oper = "";
	if ($decl =~ s/\boperator\b(.*)/operator/) {
	    $oper = $1;
	    $oper .= &matchOper;
	    # If, after all that there's no opers, then try a () operator
	    if (!($oper =~ /\S/)) { $oper .= &matchFuncOper; }
	}

	($type,$mod,$decl) = $decl =~ /([\s\w]*)([\s\*\&]+\s?)(\~?\w+(\[.*\])*)/;
	$type = $tempArgs . $type;
	$decl .= $oper;

	if ($mod =~ /\s/) { $type .= $mod; $mod = ""; }

	for (;;) {

#print STDERR "Looping: $type/$mod/$decl\n";
		
	    if (&matchRParen)
	    {
		$nest = 1;
		$args = "";
			
		for (;;)
		{
#print STDERR "Argloop $_\n";

		    # Process argument lists.

		    # Preserve spaces, eliminate in-line comments
		    # REM: Change this to save inline comments and automatically
		    # generate @param clauses
		    s|//.*||;
		    while (s/^(\s+)//) { $args .= " "; &rdln; }
					
		    if (&matchRParen) { $nest++; $args .= "("; }
		    elsif (&matchLParen)
		    {
			$nest--;
			last if !$nest;
			$args .= ")";
		    }
		    elsif ($d = &matchKW( "[\,\=\.\:\-]" )) { $args .= $d; }
		    elsif ($d = &matchDecl) { $args .= $d; }
		    elsif ($d = &matchAngleArgs) { $args .= $d; }
		    elsif ($d = &matchString) { $args .= "\"$d\""; }
		    else { last; }
		}
				
#print STDERR "$type$mod$baseScope$decl($args);\n";
	
		&matchKW( "const" );
				
		# Search for any text within the name field
#		if ($docTag && $decl =~ /\W*(~?\w*).*/)
		if ($docEmpty == 0)
		{
		    $type =~ s/^\s+//;
		    $mod  =~ s/\&/\&amp;/g;
		    $args =~ s/\&/\&amp;/g;
		    $args =~ s/\s+/ /g;
		    $dbname = &uniqueName( "$baseScope$decl" );

		    my $entry = { 'type'    => 'func',
				  'name'    => $decl,
				  'longname'=> "$decl()",
				  'fullname'=> "$type$mod$decl($args)",
				  'scopename'=>"$type$mod$baseScope$decl($args)",
				  'uname'   => $dbname,
				  'decl'    => "$type$mod$decl($args)",
				  'package' => $packageName };

		    bless $entry, MemberRecord;

		    if ($class)
		    {
			$entry->{ 'class' } = "$context";
			$class->{ 'members' }{ $dbname } = $entry;
		    }
		    else {
			$packages{ $packageName }{ 'globals' }{ $dbname } = $entry;
		    }
		    &dumpComments( $entry );
		}
		else { &clearComments; }

		s|//.*||;

		# Constructor super-call syntax
		if (&matchColon) {
		    
		    #	Skip over it.
		    for (;;) {
			&rdln;
			last if /^\s*(\{|\;)/;
			last if !&matchAny;
		    }
		}
	
		last if &matchSemi;
		if (&matchRBracket) { &skipBody; last; }
		last if !&matchComma;
		last if !($decl = &matchDecl);
		
		# Look for (*name) syntax
		&parse_paren_pointer;

		$decl =~ s/^\s*//;
		$oper = "";
		if ($decl =~ /\boperator\b/) {
		    $decl =~ s/\boperator\b(.*)/operator/;
		    $oper = $1 . &matchOper;
		}
		($mod,$d) = $decl =~ /^\s*([\*\&]*)\s*(\~?\w+(\[.*\])*)/;
		$decl .= $oper;
		$decl = $d if $d ne "";
	    }
	    else
	    {
		s|//.*||;

		$final = 0;

		if (&matchKW( "\=" ))
		{
		    for (;;) {
			
			if (&matchRBracket) {
			    &skipBody;
			    $final = 1;
			    last;
			}

			if (&matchSemi) {
			    $final = 1;
			    last;
			}
			last if /^\s*,/;
			last if !&matchAny;
		    }
		}
		
		s|//.*||;

		#	void ~*&foo[];
		#	void foo[];
		#	void far*foo[];

#print STDERR "Decl: $type$mod$baseScope$decl;\n";

		#	Search for any text within the name field
		if ($docEmpty == 0 && ($decl =~ /\W*(~?\w*).*/))
		{
		    $mod  =~ s/\&/\&amp;/g;
		    $dbname = &uniqueName( "$baseScope$1" );

		    my $entry = { 'type'     => 'var',
				  'name'     => $1,
				  'longname' => "$name",
				  'fullname' => "$type$mod$decl",
				  'scopename'=> "$baseScope$type$mod$decl",
				  'uname'    => $dbname,
				  'decl'     => "$type$mod$decl",
				  'package'  => $packageName };

		    bless $entry, MemberRecord;

		    if ($class)
		    {
			$entry->{ 'class' } = "$context";
			$class->{ 'members' }{ $dbname } = $entry;
		    }
		    else {
			$packages{ $packageName }{ 'globals' }{ $dbname } = $entry;
		    }
		    &dumpComments( $entry );
		}
		else { &clearComments; }
		
		last if $final;
		last if &matchSemi;
		last if !&matchComma;
		last if !($decl = &matchDecl);
		
		#	Look for (*name) syntax
		&parse_paren_pointer;

		$decl =~ s/^\s*//;
		($mod,$d) = $decl =~ /^\s*([\*\&]*)(\~?\w+(\[.*\])*)/;
		$decl = $d if $d ne "";
	    }
	}
    }
    elsif ($context ne "" && /^\s*\}/)
    {
#print STDERR "Popping!\n";
	return 1;
    }
    elsif (&matchRBracket)
    {
	&skipBody;
    }
    elsif ($token = &matchAny)
    {
	# Comment in for debugging
#print STDERR "$token ";
    }
    else { return 0; }

    return 1;
}

# read a file into a string ( filename, default-value )
sub readfile {
    local ( $filename, $result ) = @_;

    if ($filename && open( FILE, $filename )) {
	$result = "";
	while (<FILE>) { $result .= $_; }
	close( FILE );
    }
    $result;
}

# Read the entire document template and translate into PERL code.
sub readtemplate {
    local ( $filename ) = @_;
    $docTemplate = '';
    $indent = '';
    $literal = 1;  # We're in literal mode.

    open( FILE, $filename ) || die "Error opening '$filename'.\n";
    while (<FILE>) {
	last if (/END/);

	# if we found a code entry.
	for (;;) {
	    &expand_tabs( $_ );
	    if ($literal)
	    {
		# Check for beginning of code block.
		if (s/^(.*)\<\<//) {
		    $line = $1; 
		    if (substr( $line, 0, length( $indent ) ) eq $indent) {
			substr( $line, 0, length( $indent ) ) = '';
		    }

		    if ($line ne '') {
			$line =~ s/\"/\\\"/g;
			$line =~ s/\$\((\w+)\.(\w+)\)/\" \. \$$1->$2() \. \"/g;
			$docTemplate .= "${indent}print\"$line\";";
		    }
#		    else { $docTemplate .= "\n"; }
		    $literal = 0;
		}
		else
		{
		    if (substr( $_, 0, length( $indent ) ) eq $indent) {
			substr( $_, 0, length( $indent ) ) = "";
		    }
		    chop;
		    s/\"/\\\"/g;
		    s/\$\((\w+)\.(\w+)\)/\" \. \$$1->$2() \. \"/g;
		    $_ = $indent . "print \"" . $_ . "\\n\";\n";
		    last;
		}
	    }
	    else
	    {
		# Check for beginning of literal block.
		if (s/^(\s*)\>\>//) {
		    $indent = $1;
		    $literal = 1;
		}
		elsif (s/^(\s*)(.*)\>\>//) {
		    $docTemplate .= "$indent$2";
		    $literal = 1;
		}
		else {
		    last;
		}
	    }
	}

	$docTemplate .= $_;
    }
    close( FILE );
#    print $docTemplate;
}

# Functions intended to be called from doc template file.

# Open a new output file
sub file {
    my $mfile = $_[ 0 ];

    open( STDOUT, ">$destpath$mfile" ) || die "Error writing to '$mfile'\n";
}

# return list of package objects
sub packages {
    my $p, @r = ();
    foreach $p (sort keys %packages) {
	push @r, $packages{ $p };
    }
    @r;
}

# return list of source files which have to-do lists
sub todolist_files {
    my $p, @r = ();
    foreach $p (sort keys %todolist) {
	push @r, $p;
    }
    @r;
}

# return list of tab-delimited to-do-list texts.
sub todolist_entries
{
    local $_ = $todolist{ $_[0] };
    s/^\s+//;				# Remove whitespace from beginning
    s/\s+$/\n/;				# Remove whitespace from end
    return split( /\n/, $_ );
}

# Convert package name to URL.
sub package_url {
    my $p = $_[0];

    if ($p eq 'General') { $p = '.general'; }
    if ($p eq '') { $p = '.general'; }

    if (ref $packages{ $p })
    {
	return $packages{ $p }->url();
    }
    0;
}

# Get the see-also list for an object
sub get_seealso_list {
    my $self = shift;
    my $see, $name, $url, $p, @r = (), $_;

    foreach $_ (split(/\n/,$self->{ 'see' })) {
       
	if (/^\<a\s+href/)			# if already an HREF.
	{
	    $name = $_;
	    $url = 0;
	}
	elsif (/([^\#]*)\#(.*)/)		# If a package name is present
	{
	    $url = &package_url( $1 ) . '#' . $2;
	    $name = $2;
	}
	else
	{
	    $name = $_;
	    $url = "#$_";

	    # Look up the package in the index and use it to construct the html filename.
	    if (/^([^\:]*)\:\:(.*)/)
	    {
		$className = ($1 eq '') ? '' : $classToPackage{ $1 };
		$p = $packageToFile{ $className };
		if ($p ne '' && $p ne $package) {
		    $url = &package_url( $1 ) . '#' . $_;
		}
	    }
	}
	    
	$url =~ s/^\:*//;		# Remove leading colons from name
	$url =~ s/::/-/g;		# Replace :: with dash
	    
	my $entry = { 'name' => $name,
		      'url'  => $url };

	bless $entry, DocReference;

	push @r, $entry;
    }
    @r;
}

# Class for parsed package
package PackageRecord;

sub classes {
    my $self = shift;
    my $classes = $self->{ 'classes' };
    return map $classes->{ $_ }, (sort keys %$classes);
}

sub globals {
    my $self = shift;
    my $globals = $self->{ '.globals' };
    return map $globals->{ $_ }, (sort keys %$globals);
}

sub globalvars {
    my $self = shift;
    my $globals = $self->{ '.globals' };
    my $p, @r;

    foreach $p (sort keys %$globals) {
	my $m = $globals->{ $p };
	if ($m->{ 'type' } != 'func') { push @r, $m; }
    }
    @r;
}

sub globalfuncs {
    my $self = shift;
    my $globals = $self->{ '.globals' };
    my $p, @r;

    foreach $p (sort keys %$globals) {
	my $m = $globals->{ $p };
	if ($m->{ 'type' } == 'func') { push @r, $m; }
    }
    @r;
}

sub name {
    my $self = shift;
    return $self->{ 'name' };
}

sub url {
    my $self = shift;
    return "default-pkg.html" if ($self->{ 'name' } eq '.general');
    return $self->{ 'name' } . '.html';
}

sub anchor {
    my $self = shift;
    my $url = $self->{ 'name' };
    $url;
}

# Class for parsed class
package ClassRecord;

sub keywords    { return ${$_[0]}{ 'keywords' }; }
sub author      { return ${$_[0]}{ 'author' }; }
sub version     { return ${$_[0]}{ 'version' }; }
sub name        { return ${$_[0]}{ 'name' }; }
sub longname    { return ${$_[0]}{ 'longname' }; }
sub fullname    { return ${$_[0]}{ 'fullname' }; }
sub scopename   { return ${$_[0]}{ 'scopename' }; }
sub sourcefile  { return ${$_[0]}{ 'sourcefile' }; }
#sub description { return &::processDescription( ${$_[0]}{ 'description' } ); }
sub description { return ${$_[0]}{ 'description' }; }
sub seealso     { &::get_seealso_list( $_[0] ); }

sub url {
    my $self = shift;
    return 0 unless $self->{ 'package' };
    my $pname = ::package_url( $self->{ 'package' } );
    my $url = $self->{ 'uname' };
    $url =~ s/::/-/g;
    "$pname#$url";
}

sub anchor {
    my $self = shift;
    my $url = $self->{ 'uname' };
    $url =~ s/::/-/g;
    $url;
}

sub members {
    my $p, @r = ();
    my $self = shift;
    my $members = $self->{ 'members' };

    foreach $p (sort keys %$members) {
	push @r, $members->{ $p };
    }
    @r;
}

sub membervars {
    my $p, @r = ();
    my $self = shift;
    my $members = $self->{ 'members' };

    foreach $p (sort keys %$members) {
	my $m = $members->{ $p };
	if ($m->{ 'type' } != 'func') { push @r, $m; }
    }
    @r;
}

sub memberfuncs {
    my $p, @r = ();
    my $self = shift;
    my $members = $self->{ 'members' };

    foreach $p (sort keys %$members) {
	my $m = $members->{ $p };
	if ($m->{ 'type' } == 'func') { push @r, $m; }
    }
    @r;
}

sub baseclasses {
    my $self = shift;
    my $bases = $self->{ 'bases' };
    my $p, $class, @r = ();

    foreach $p (@$bases) {

	unless ($class = $classList{ $p })
	{
	    # It's one we don't know about, so just make something up
	    $class = { 'name'    => $p,
		       'longname'=> "class $p",
		       'fullname'=> "class $p",
		       'scopename'=>"class $p",
		       'uname'   => $p,
		       'members' => {} };

	    if ($::classToPackage{ $p }) {
		$class->{ 'package' } = $::classToPackage{ $p };
	    }

	    bless $class, ClassRecord;
	}
	push @r, $class;
    }
    @r;
}

sub subclasses {
    my $self = shift;
    my $subs = $self->{ 'subs' };
    my $p, $class, @r = ();

    foreach $p (sort @$subs) {
	$class = $::classList{ $p };
	push @r, $class;
    }
    @r;
}

# Class for parsed class member or global
package MemberRecord;

sub type        { return ${$_[0]}{ 'type' }; }
sub keywords    { return ${$_[0]}{ 'keywords' }; }
sub author      { return ${$_[0]}{ 'author' }; }
sub version     { return ${$_[0]}{ 'version' }; }
sub name        { return ${$_[0]}{ 'name' }; }
sub longname    { return ${$_[0]}{ 'longname' }; }
sub fullname    { return ${$_[0]}{ 'fullname' }; }
sub scopename   { return ${$_[0]}{ 'scopename' }; }
sub returnval   { return ${$_[0]}{ 'returnval' }; }
sub sourcefile  { return ${$_[0]}{ 'sourcefile' }; }
sub description { return ${$_[0]}{ 'description' }; }
sub seealso     { &::get_seealso_list( $_[0] ); }

sub url {
    my $self = shift;
    return 0 unless $self->{ 'package' };
    my $pname = ::package_url( $self->{ 'package' } );
    my $url = $self->{ 'uname' };
    $url =~ s/::/-/g;
    "$pname#$url";
}

sub anchor {
    my $self = shift;
    my $url = $self->{ 'uname' };
    $url =~ s/::/-/g;
    $url;
}

sub params {
    my $self = shift;
    my $params = $self->{ 'param' };
    my @r = ();

    return 0 unless ($params);

    my @paramList = split( /\t/, $params );
    
    for ($i = 1; $i < $#paramList; $i += 2)
    {
	my $entry = { 'name'        => $paramList[ $i ],
		      'description' => $paramList[ $i + 1 ] };

	bless $entry, ArgRecord;

	push @r, $entry;
    }
    @r;
}

sub exceptions {
    my $self = shift;
    my $params = $self->{ 'exception' };
    my @r = ();

    return 0 unless ($params);

    my @paramList = split( /\t/, $params );
    
    for ($i = 1; $i < $#paramList; $i += 2)
    {
	my $entry = { 'name'        => $paramList[ $i ],
		      'description' => $paramList[ $i + 1 ] };

	bless $entry, ArgRecord;

	push @r, $entry;
    }
    @r;
}

package ArgRecord;
sub name        { return ${$_[0]}{ 'name' }; }
sub description { return ${$_[0]}{ 'description' }; }

package DocReference;
sub name        { return ${$_[0]}{ 'name' }; }
sub url         { return ${$_[0]}{ 'url' }; }
