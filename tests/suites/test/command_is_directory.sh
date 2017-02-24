mkdir test_is_directory_dir
touch test_is_directory_directory
test -d test_is_directory_dir && echo a
test -d test_is_directory_directory && echo b
test -d test_not_is_directory_dir && echo c
test -d test_not_is_directory_directory && echo d
rm -rf test_is_directory_dir test_is_directory_directory
