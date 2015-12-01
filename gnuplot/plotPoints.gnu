set terminal pngcairo size 1280, 960

set xlabel 'x'
set ylabel 'y'

set xrange [-1:1]
set yrange [-1:1]

set key horiz outside center top 

files = system ('ls *_A.dat | rev | cut -c 7- | rev')

do for [file in files] {

    setA = sprintf("%s_A.dat", file)
    setB = sprintf("%s_B.dat", file)
    setS = sprintf("%s_S.dat", file)
    setF = sprintf("%s_F.dat", file)

    set title file

    set output sprintf('%s_samples.png', file)
    plot setA lc rgb color1 title 'Learning sample A', setB lc rgb color3 title 'Learning sample A'

    set output sprintf('%s_results.png', file)
    plot setS lc rgb color5 title 'Success', setF lc rgb color4 title 'Failure'
}
