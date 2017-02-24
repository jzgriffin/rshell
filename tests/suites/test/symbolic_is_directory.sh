mkdir test_is_directory_dir
touch test_is_directory_directory
[ -d test_is_directory_dir ] && echo a
[ -d test_is_directory_directory ] && echo b
[ -d test_not_is_directory_dir ] && echo c
[ -d test_not_is_directory_directory ] && echo d
rm -rf test_is_directory_dir test_is_directory_directory
