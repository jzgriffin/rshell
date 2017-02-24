mkdir test_is_file_dir
touch test_is_file_file
test -f test_is_file_dir && echo a
test -f test_is_file_file && echo b
test -f test_not_is_file_dir && echo c
test -f test_not_is_file_file && echo d
rm -rf test_is_file_dir test_is_file_file
