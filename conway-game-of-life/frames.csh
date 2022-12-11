#!/bin/csh -f

set indir = "testInputs"
set outdir = "studentOutputs"
set life = "./gameOfLife"

if ($#argv != 3) then
    echo "Usage: $0 <rootname> <rule> <frames>"
    echo "Example: frames.csh glider 0x1808 10"
    echo "         This will run Conway's Game of Life simulation $life"
    echo "         with rule 0x1808 on the file $indir/glider.ppm"
    echo "         and write into $outdir/glider/ the files"
    echo "         glider_0x1808_10000.ppm through glider_0x1808_10010.ppm"
    exit 0
endif

if (! -e $indir) then
    echo "$indir input directory doesn't exist, exiting..."
    exit -1
endif

if (! -e $indir/$1.ppm) then
    echo "$indir/$1.ppm initial PPM file doesn't exist, exiting..."
    exit -1
endif

if (! -e $outdir) then
    echo "$outdir output directory doesn't exist, creating..."
    mkdir $outdir
endif

if (! -e $outdir/$1) then
    echo "$1 directory doesn't exist, creating..."
    mkdir $outdir/$1
else
    echo "$1 directory already exists; existing files will not be recomputed"
endif

cp $indir/$1.ppm $outdir/$1/$1_$2_10000.ppm
@ n = 10000
@ max = 10000 + $3
while ($n < $max)
    @ np = $n + 1
    @ report = $np - 10000
    if (-e $outdir/$1/$1_$2_$np.ppm) then    
		echo -n "[$report] "
	else
		echo -n "$report "
	    $life $outdir/$1/$1_$2_$n.ppm $2 >! $outdir/$1/$1_$2_$np.ppm
	endif
    @ n = $n + 1
end
echo "Making gif in $1.gif"
convert -delay 20 -loop 0 -scale 400% $outdir/$1/*.ppm $outdir/$1/$1.gif
echo ""
