mkdir test_is_file_dir
touch test_is_file_file
[ -f test_is_file_dir ] && echo a
[ -f test_is_file_file ] && echo b
[ -f test_not_is_file_dir ] && echo c
[ -f test_not_is_file_file ] && echo d
rm -rf test_is_file_dir test_is_file_file
