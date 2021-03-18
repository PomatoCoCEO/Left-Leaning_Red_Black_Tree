start=1000
end=2000000
step=1000
iter=$start
g++ -std=c++17 redBlackTree.cpp -o RBT

if [ -f times.txt ]; then
    rm times.txt;
fi

while [ $iter -le $end ]; do
    ./RBT $iter >> times.txt
    iter=$((iter+step));
done