grep -i foo redirect_input.out > redirect_output_1.tmp; cat redirect_output_1.tmp
echo hello world >redirect_output_2.tmp; cat redirect_output_2.tmp
rm redirect_output_1.tmp redirect_output_2.tmp
