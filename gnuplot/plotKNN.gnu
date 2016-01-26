#set terminal pngcairo size 1280, 960
set terminal postscript eps enhanced color 'ArialBold' 18

set xlabel 'The size of each training set'
set ylabel 'Number of neighbours (k)'

set pm3d map
#set cbrange [0:1]

unset key

files = system ('ls *.dat | rev | cut -c 5- | rev')

do for [file in files] {

    set output sprintf('%s.eps', file)
    # set title file
    data = sprintf("%s.dat", file)

    splot data
}
