#! /usr/bin/perl

if (@ARGV < 4) {
  print<<HEAD

  This code converts a DataCard to a python fragment for DataCardFileWriter.

  Syntax:

  ConvertDataCardToPython {inputfile} {outputfile} {fragmentname} {datacardname} 

    inputfile    - The name of the input file to be converted to a python fragment for DataCardFileWriter
    outputfile   - The name of the output file  that is to contain DataCardFileWriter python fragment
    fragmentname - The name of the python fragment
    datacardname - The name of the datacard to be written out by DataCardFileWriter

HEAD
;
}
else {
    $inputfile=$ARGV[0];
    $outputfile=$ARGV[1];
    $fragmentname=$ARGV[2];
    $datacardname=$ARGV[3];

    if(-e $outputfile){
	printf("Output File already exists: $outputfile \nRemove it and try again...");
	exit();
    }

    @DataSets;
    open(InDAT, $inputfile) || die("Could not open file $inputfile!\n");
    while ($item = <InDAT>) {
	chomp($item);
	push(@DataSets,$item);
    }
    close(InDAT);
    
    open(OutDAT, '>>', $outputfile) || die("Could not open file $inputfile!");
    print {OutDAT} "import FWCore.ParameterSet.Config as cms\n";
    print {OutDAT} "import os\n";
    print {OutDAT} "from subprocess import call\n";
    print {OutDAT} "theFileName=\"$datacardname\"\n";
    print {OutDAT} "$fragmentname = cms.EDAnalyzer(\"DataCardFileWriter\",\n";
    print {OutDAT} "\tFileName = cms.string(theFileName),\n";
    print {OutDAT} "\tFileContent = cms.vstring()\n";
    print {OutDAT} "\t)\n";
    print {OutDAT} "file = os.path.relpath(os.environ.get('CMSSW_BASE'))+'/src/'+theFileName\n";
    print {OutDAT} "call([\"touch\", file])\n";
    $i=0;
    $j=0;
    $nlines = @DataSets;

    foreach $DS (@DataSets){
	if($i==255){
	    $i=0;
	    print {OutDAT} "\t])\n";
	}
	if($i==0){
	    print {OutDAT} "$fragmentname.FileContent.extend([\n";
	}
        $i++;
	$j++;
        $comma=",";
        if($i==255 || $j==$nlines){ $comma="";}
        $DS =~ s/\\/\\\\\\\\/g;
	$DS =~ s/\"/\\"/g;
	print {OutDAT} "\t\"$DS\"$comma\n";
    }
    print {OutDAT} "\t])\n";
    close(OutDAT);
}
