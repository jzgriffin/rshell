mkdir test_exists_dir
touch test_exists_file
test -e test_exists_dir && echo a
test -e test_exists_file && echo b
test -e test_not_exists_dir && echo c
test -e test_not_exists_file && echo d
rm -rf test_exists_dir test_exists_file
