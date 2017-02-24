mkdir test_exists_dir
touch test_exists_file
[ -e test_exists_dir ] && echo a
[ -e test_exists_file ] && echo b
[ -e test_not_exists_dir ] && echo c
[ -e test_not_exists_file ] && echo d
rm -rf test_exists_dir test_exists_file
