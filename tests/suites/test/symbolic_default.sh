mkdir test_default_dir
touch test_default_file
[ test_default_dir ] && echo a
[ test_default_file ] && echo b
[ test_not_default_dir ] && echo c
[ test_not_default_file ] && echo d
rm -rf test_default_dir test_default_file
