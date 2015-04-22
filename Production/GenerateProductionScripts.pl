#! /usr/bin/perl
use Cwd;
use POSIX;
use POSIX qw(strftime);


#############################################
$numArgs = $#ARGV +1;
$ARGV[$argnum];

$OutputDir="LHEProduction";
$listofLHEFiles="lhe5591.txt";
$crabTemplate="crabConfig_MC_GenSim_Prodwithsanc1000x1000_template.py";
$genfragTemplate="DYtoTauTautomuhad_cfi_GEN_SIM_VALIDATION_TEMPLATE.py";

if($ARGV[0] eq "--help" || $ARGV[0] eq ""){
    printf("\nThis code requires one input option. The systax is:./todo_Grid.pl [OPTION]");
    printf("\nPlease choose from the following options:\n");
    printf("\n./GenerateProductionScripts.pl --help                                   Prints this message\n");
    printf("\n./GenerateProductionScripts --LHE <listofLHEFiles>                      Setups up TauNtuple and gives instructions for submission");
    printf("\n                                                                        --OutputDir <OutputDir> Default value: $OutputDir");
    printf("\n                                                                        --crabTemplate    <crabTemplate>    Default value: $crabTemplate");
    printf("\n                                                                        --genfragTemplate <genfragTemplate> Default value: $genfragTemplate");
    printf("\n");
    exit(0);  
} 

######################################

for($l=10;$l<$numArgs; $l++){
    if($ARGV[$l] eq "--OutputDir"){
	$l++;
	$OutputDir=$ARGV[$l];
    }
    if($ARGV[$l] eq "--LHE"){
	$l++;
	$listofLHEFiles=$ARGV[$l];
    }
    if($ARGV[$l] eq "--crabTemplate"){
	$l++;
	$crabTemplate=$ARGV[$l];
    }
    if($ARGV[$l] eq "--genfragTemplate"){
        $l++;
        $genfragTemplate=$ARGV[$l];
    }
}

my $dir = getcwd;

$time= strftime("%h_%d_%Y",localtime);
$temp= $set . $time;
$set=$temp;

if( $ARGV[0] eq "--LHE"){
    $currentdir=getcwd;

    # Print out input parameters
    printf("Output directory will be:         $OutputDir \n");
    printf("List of LHE files:                $listofLHEFiles \n");
    printf("Template file for crab:           $crabTemplate \n");
    printf("Template file for gen-Fragment:   $genfragTemplate \n");

    system(sprintf("mkdir ../$OutputDir"));

    # Open ListofFile.txt
    @LHEFiles;
    open(DAT, $listofLHEFiles) || die("Could not open file $TempDataSetFile!");
    while ($item = <DAT>) {
	chomp($item);
	#print("File: $item \n");
	push(@LHEFiles,$item);
    }
    close(DAT);

    $OutFile=0;
    $NLHEFiles=0;
    $filelist="";
    $idx=0;
    $arrSize = @LHEFiles;
    $OutputDir =~ s{\/}{\\\/}g;
    foreach $lhe (@LHEFiles){
	$tmpstring = $filelist; 
	if($NLHEFiles==0){
	    $filelist = $tmpstring . "\"" . $lhe . "\"";
	}
	else{
	    $filelist = $tmpstring . ",\"" . $lhe . "\"";
	}
	$NLHEFiles++;
	$idx++;
	if($NLHEFiles>=10 || $idx==$arrSize ){
	    $OutFile++;
	    $NLHEFiles=0;
	    system(sprintf("sed 's/GENFRAGMENT/%s\\\/GenFagment_GENSIM_Production%d.py/'  $crabTemplate > ../$OutputDir/crab_GENSIM_Production$OutFile.py ",$OutputDir,$OutFile));
	    system(sprintf("sed -i.bak s/NUMBER/$OutFile/g ../$OutputDir/crab_GENSIM_Production$OutFile.py"));
	    $filelist =~ s{\/}{\\\/}g;
	    system(sprintf("sed 's/LISTOFFILES/$filelist/'  $genfragTemplate > ../$OutputDir/GenFagment_GENSIM_Production$OutFile.py "));
	    $filelist="";
	    if($OutFile==10){ 
		exit(0);
	    }
	}
    }
}
