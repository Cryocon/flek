<<
# Scandoc template file.
# This is an example set of templates that is designed to create several different
# kinds of index files. It generates a "master index" which intended for use with
# a frames browser; A "package index" which is the root page of the index, and then
# "package files" containing documentation for all of the classes within a single
# package.
# =========================================
# For quick and superficial customization, simply change these variables
$project_name = 'The Fast Light Environment Kit';
$project_logo = '<img src="flek.gif">';            # change this to an image tag.
$copyright = '&copy 2000 the Flek Development team.';
$image_directory = ""; #"../images/";
#$index_background = $image_directory . "tile.gif";
#$page_background  = $image_directory . "tile.gif";

# =========================================
# Begin generating package index file
file "index.html";
>><html>

<head>
<title>$project_name : Documentation</title>
<BODY BGCOLOR="white">
</head>

<center>
$project_logo
<h4>Documentation for $project_name</h4>
</center>
<hr>
<h2>Documentation</h2>
<ul>
<li><a href="flek-config.htm">Using flek-config</a></li>
<li><a href="fDom.htm">fDom: The Flek Document-Component Model</a></li>
<li><a href="hacking.htm">The Flek Coding Style Guide</a></li>
</ul>
<h2>Class and Function Reference</h2>
<blockquote>
<<
# For each package, generate an index entry.
foreach $p (packages()) {
if ($p->name() ne "General")
{ >><h3>$(p.name)</h3><ul><< }
if ($p->globalfuncs()) 
{
  print "<li><a href=\"" . $p->name . "_globals.html\">Global Functions</a></li>\n";
}
foreach $c ($p->classes()) {
	>><li><a href = "$(c.name).html">$(c.name)</a></li>
	<<
}
>></ul><<
}
>>
</blockquote>
<hr>
<h2>Flvw Documentation</h2> 
<i>(this documentation is not yet included in Flek distribution, but will be soon)</i>
<ol>
<li><A HREF="http://flvw.sourceforge.net/documentation/intro.html">Introduction to FLVW</A></li>
<li><A HREF="http://flvw.sourceforge.net/documentation/basics.html">Basics</A></li>
<li><A HREF="http://flvw.sourceforge.net/documentation/stylebasics.html">Virtual Style Basics</A></li>
<li><A HREF="http://flvw.sourceforge.net/documentation/classref.html">Class reference</A>
<br>
<ul>
<li><a href="http://flvw.sourceforge.net/documentation/flv_style.html">Flv_Style</a></li>
<li><a href="http://flvw.sourceforge.net/documentation/flv_style_list.html">Flv_Style_List</a></li>
<li><a href="http://flvw.sourceforge.net/documentation/flv_list.html">Flv_List</a></li>
<li><a href="http://flvw.sourceforge.net/documentation/flv_table.html">Flv_Table</a></li>
</ul>
</li>
</ul>

<hr>
<h3>Fltk Documentation (Fast Light ToolKit)</h3>
  <ul>
    <li><a href="http://www.fltk.org/doc/toc.html">Documentation</a> 
    (Also available in 
    <a href="http://www.fltk.org/doc/fltk.pdf">PDF</a> and 
      <a href="http://www.fltk.org/doc/fltk.ps">Postscript</a> format)
	</li>
	<li><a href="http://www.fltk.org/faq.html">Frequently Asked Questions</a></li>
      </ul>
      
<p>
<hr>

<font size="-1">$copyright<br>
Generated by <a href="http://www.sylvantech.com/~talin/projects/scandoc/scandoc.html"><b>ScanDoc</b></a><br>
Last Updated: $date<br>
</font>
</body>
</html>

<<
# =========================================
# Generate "To-do list"

file "to-do.html";
>><html>

<head>
<title>$project_name -- To-Do list</title>
<BODY  BGCOLOR="white">
</head>

$project_logo

<h1>To-do list for $project_name</h1>

<<
if (&todolist_files()) {
	>><hr><p>
	<<
	foreach $f (&todolist_files()) {
		my @m = &todolist_entries( $f );
		if ($f =~ /([^\/]+)$/) { $f = $1; }
		>><b>$f:</b><ul>
		<<
		foreach $text (@m) {
			if ($text)
			{
				print "<li>", &processDescription( $text ), "\n";
			}
		}
		>></ul>
		<<
	}
}
>>
<hr>
<font size="-1">
$copyright<br>
Generated by <a href="http://www.sylvantech.com/~talin/projects/scandoc/scandoc.html"><b>ScanDoc</b></a><br>
Last Updated: $date<br>
</font>
</body>
</html>

<<


### Generate detailed class documentation

foreach $p (packages()) {
foreach $c ($p->classes()) {
	file $c->name() . ".html";


>><html>

<head>
<title>$project_name -- $(p.name)</title>
<BODY BGCOLOR="white">
</head>

<center>
$project_logo
<h4>$project_name</h4>
</center>
<hr>
<<

	# Output searchable keyword list
	if ($c->keywords()) {
		print "<!-- ", $c->keywords(), " -->\n";
	}

	>><a name="$(c.anchor)"></a>
	<br><h2>$(c.fullname)</h2>
	<<

	# Output author tag
	if ($c->author()) {
		>><tr><th width=20% align=right>Author:</th><<
		>><td>$(c.author)</td></tr><<
	}

	# Output package version
	if ($c->version()) {
		>><tr><th width=20% align=right>Version:</th><<
		>><td>$(c.version)</td></tr><<
	}

	# Output base class list
	if ($c->baseclasses()) {
		>><h2>Class Hierarchy</h2><blockquote><pre><<
		my @t = ();
		foreach $b ($c->baseclasses()) {
			my $name = $b->name();
			if ($url = $b->name()) {
				push @t, "<a href=\"$url.html\">$name</a>";
			}
			else { push @t, $name; }
		}
		print join( ', ', @t );
		>>
   |
   +----<b>$(c.name)</b>
<<
  if ($c->subclasses()) {
>>           |
           +----<<
    my @t = ();
		foreach $s ($c->subclasses()) {
			my $name = $s->name();
			if ($url = $s->name()) {
				push @t, "<a href=\"$url.html\">$name</a>";
			}
			else { push @t, $name; }
		}
		print join( ', ', @t );
	}
>></pre></blockquote><<
	}	

	# Output Source file
	if ($c->sourcefile()) {
	$jamessrc = $c->sourcefile(); #$(c.sourcefile);
	$jamessrc =~ s/^.*(Flek)/$1/;
	$jamessrc = "<pre>\#include \&lt\;" . $jamessrc . "\&gt\;</pre>";
		>><h3>Include Files</h3><<
		>><blockquote>$jamessrc</blockquote><<
	}

	# Output main class description
	>><h2>Description</h2>
	<blockquote>
	<<
	print &processDescription( $c->description() );
	>></blockquote><<
	# Output "see also" information
	if ($c->seealso()) {
		>><p><dt><b>See Also</b><dd>
		<<
		my @r = ();
		foreach $a ($c->seealso()) {
			my $name = $a->name();
			if ($url = $a->url()) {
				push @r, "<a href=\"$url\">$name</a>";
			}
			else { push @r, $name; }
		}
		print join( ',', @r );
		>><p>
		<<
	}

	# Output class member index
	if ($c->members()) {
		print "<h2>Methods</h2>\n";
		print "<ul>";
		foreach $m ($c->members()) {
			>><li><a href="$(m.url)">$(m.name)</a>
			<<
		}
		>></ul><hr><<
	}
	
	# Output class member variable documentation
	if ($c->membervars()) {
		print "<h3>Variable Descriptions</h3>\n";
		print "\n";
		foreach $m ($c->membervars()) { &variable( $m ); }
	}

	# Output class member function documentation
	if ($c->memberfuncs()) {
		print "<h3>Method Descriptions</h3>\n";
		print "\n";
		foreach $m ($c->memberfuncs()) { &function( $m ); }
	}
>>
<hr>
<font size="-1">$copyright<br>
Generated by <a href="http://www.sylvantech.com/~talin/projects/scandoc/scandoc.html"><b>ScanDoc</b></a><br>
Last Updated: $date<br></font>
</body>
</html>
<<

}

# Output global functions
if ($p->globalfuncs())
  {
    file ($p->name() . "_globals.html");

>><html>

<head>
<title>$project_name -- $(p.name)</title>
<BODY BGCOLOR="white">
</head>

<center>
$project_logo
<h4>$project_name</h4>
</center>
<hr>
<h3><<

print $p->name () . " Global Functions</h3>\n";

    foreach $m ($p->globalfuncs()) 
      {
	&global_function ($m);
      }

>>
<hr>
<font size="-1">$copyright<br>
Generated by <a href="http://www.sylvantech.com/~talin/projects/scandoc/scandoc.html"><b>ScanDoc</b></a><br>
Last Updated: $date<br></font>
</body>
</html>
<<

  }
}


# Subroutine to generate documentation for a member function
sub function {
	local ($f) = @_;

	if ($f->keywords()) {
		>><!-- $(f.keywords) -->
		<<
	}

   $jamesname = $f->fullname();
   if ($jamesname =~ m/operator/)
   {
     $jamesname = $f->fullname();
     $jamestwo = $c->name();
     $jamesname =~ s/operator/$jamestwo\:\:operator/;
   }
   else
   {
     $jamesname = $f->fullname();
     $jamesone = $f->name();
     $jamestwo = $c->name();
     $jamesname =~ s/($jamesone)/$jamestwo\:\:$1/;
   } 

	>>
	<a name="$(f.anchor)"></a>
	<dl>
	<dt>
	<h4>$jamesname;</h4>
	<dd>
	<<print &processDescription( $f->description() );>>
	<p><dl>
	<<
	if ($f->params()) {
		>>
		<dt><b>Parameters</b><dd>
		<table width=85%><tr><td colspan=2><hr></td></tr>
		<<
		foreach $a ($f->params()) {
			>><tr valign=top><th align=right>
			$(a.name)</th><td><<
			print &processDescription( $a->description() );
			>></td></tr>
			<<
		}
		>><tr><td colspan=2><hr></td></tr></table>
		<<
	}
	
	if ($f->returnval()) {
		>><dt><b>Return Value</b>
		<dd><<
		print &processDescription( $f->returnval() );>><p>
		<<
	}
	
	if ($f->exceptions()) {
		>><dt><b>Exceptions</b><dd>
		<table width=85%><tr><td colspan=2><hr></td></tr>
		<<
		foreach $a ($f->exceptions()) {
			>><tr valign=top><th align=right>
			$(a.name)</th><td><<
			print &processDescription( $a->description() );
			>></td></tr>
			<<
		}
		>><tr><td colspan=2><hr></td></tr></table>
		<<
	}
	
	if ($f->seealso()) {
		>><dt><b>See Also</b><dd>
		<<
		my @r = ();
		foreach $a ($f->seealso()) {
			my $name = $a->name();
			if ($url = $a->url()) {
				push @r, "<a href=\"$url\">$name</a>";
			}
			else { push @r, $name; }
		}
		print join( ',', @r );
		>><p>
		<<
	}
	>></dl></dl>
	<<
}

sub global_function {
	local ($f) = @_;

	if ($f->keywords()) {
		>><!-- $(f.keywords) -->
		<<
	}

   $jamesname = $f->fullname();

	>>
	<a name="$(f.anchor)"></a>
	<dl>
	<dt>
	<h4>$jamesname;</h4>
	<dd>
	<<print &processDescription( $f->description() );>>
	<p><dl>
	<<
	if ($f->params()) {
		>>
		<dt><b>Parameters</b><dd>
		<table width=85%><tr><td colspan=2><hr></td></tr>
		<<
		foreach $a ($f->params()) {
			>><tr valign=top><th align=right>
			$(a.name)</th><td><<
			print &processDescription( $a->description() );
			>></td></tr>
			<<
		}
		>><tr><td colspan=2><hr></td></tr></table>
		<<
	}
	
	if ($f->returnval()) {
		>><dt><b>Return Value</b>
		<dd><<
		print &processDescription( $f->returnval() );>><p>
		<<
	}
	
	if ($f->exceptions()) {
		>><dt><b>Exceptions</b><dd>
		<table width=85%><tr><td colspan=2><hr></td></tr>
		<<
		foreach $a ($f->exceptions()) {
			>><tr valign=top><th align=right>
			$(a.name)</th><td><<
			print &processDescription( $a->description() );
			>></td></tr>
			<<
		}
		>><tr><td colspan=2><hr></td></tr></table>
		<<
	}
	
	if ($f->seealso()) {
		>><dt><b>See Also</b><dd>
		<<
		my @r = ();
		foreach $a ($f->seealso()) {
			my $name = $a->name();
			if ($url = $a->url()) {
				push @r, "<a href=\"$url\">$name</a>";
			}
			else { push @r, $name; }
		}
		print join( ',', @r );
		>><p>
		<<
	}
	>></dl></dl>
	<<
}


# Subroutine to generate documentation for a member variable or global variable.
sub variable {
	local ($v) = @_;

	if ($v->keywords()) {
		print "<!-- $(v.keywords) -->";
	}

	>>
	<a name="$(v.name)"></a>
	<dl><dt>
	<h4>$(v.fullname);</h4>
	<dd>
	<<print &processDescription( $v->description() );>>
	<p><dl>
	<<
	if ($v->seealso()) {
		>><dt><b>See Also</b><dd>
		<<
		$comma = 0;
		foreach $a ($v->seealso()) {
			if ($comma) { print ","; }
			$comma = 1;
			>><a href="$(a.url)">$(a.name)</a>
			<<
		}
		>><p>
		<<
	}
	>></dl></dl>
	<<
}

sub processDescription {
    local ($_) = @_;
	
    s/^\s+//;				# Remove whitespace from beginning
    s/\s+$/\n/;				# Remove whitespace from end
    s/\n\n/<p>\n/g;			# Replace multiple CR's with paragraph markers
    s:\@heading(.*)\n:<p><h2>$1</h2>:;	# Handle heading text

    # Handle embedded image tags
    s:\@caution:<p><img src=\"${image_directory}/caution.gif\" align=left>:;
    s:\@warning:<p><img src=\"${image_directory}/warning.gif\" align=left>:;
    s:\@bug:<p><img src=\"${image_directory}/bug.gif\">:;
    s:\@tip:<p><img src=\"${image_directory}/tip.gif\">:;

    return $_;
}
