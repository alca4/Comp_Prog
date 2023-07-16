g++ generator.cpp -std=c++20 -o generator
g++ correct.cpp -std=c++20 -o correct
g++ incorrect.cpp -std=c++20 -o incorrect

for i in `seq 1 100`
do
    echo "test $i"
    ./generator > tc.in
    echo "test generated"
    time ./correct
    echo "correct solution run"
    time ./incorrect
    echo "incorrect solution run"
    diff tc.out tc2.out > feedback.txt
    if [ $? -gt 0 ]
    then
        echo "wrong answer on test $i"
        break
    fi
done