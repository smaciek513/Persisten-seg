#g++ @opcjeCpp tester.cpp prev.cpp -o mac
#g++ @opcjeCpp tester.cpp prev_syl.cpp -o syl

for((i = 1; ; i++))
do
    ./gen > in.in
    ./mac < in.in > mac.out
    ./syl < in.in > syl.out
    ./brut < in.in > brut.out

    if diff -b brut.out mac.out < /dev/null
    then 
        echo "$i maciej ok"
    else 
        echo "$i fatalnie maciej"
        break
    fi

    if diff -b brut.out syl.out < /dev/null
    then
        echo "$i sylwia ok"
    else 
        echo "$i fatalnie sylwia"
        break
    fi
done