if [ -z "$1" ]
then
    echo "Day number needed as argument"
    exit -1
fi

set -xe

dir=$(printf %02d $1)
src="./$dir/main.cpp"
out="./$dir/out"

g++ -std=c++17 -Wall -Wextra $src -o $out
$out
rm $out