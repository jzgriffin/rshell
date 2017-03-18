echo Foo > mixed_1.tmp
cat < mixed_1.tmp | tr A-Z a-z | tee mixed_2.tmp | tr a-z A-Z > mixed_3.tmp
cat mixed_1.tmp
cat mixed_2.tmp
cat mixed_3.tmp
