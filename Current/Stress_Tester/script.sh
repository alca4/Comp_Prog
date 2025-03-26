g++ -std=c++20 generator.cpp -o generator
g++ -std=c++20 correct.cpp -o correct
g++ -std=c++20 incorrect.cpp -o incorrect

for i in `seq 1 1000`; do
    ./generator

    echo "===== Test Case $i ====="

    ./incorrect
    ./correct

    if diff -q "incorrect.out" "correct.out" > /dev/null; then
        continue
    else
        echo "WA"
        break
    fi

done;