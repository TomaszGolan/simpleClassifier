set terminal pngcairo size 1280, 960

set xlabel 'Samples size'
set ylabel 'Number of neighbours'

set pm3d map
set cbrange [0:1]

unset key

files = system ('ls *.dat | rev | cut -c 5- | rev')

do for [file in files] {

    set output sprintf('%s.png', file)
    set title file
    data = sprintf("%s.dat", file)

    splot data
}
