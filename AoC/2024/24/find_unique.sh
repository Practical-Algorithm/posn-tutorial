cat input.txt | grep -e "->" | awk -F' ' '{print $1 "\n"$3"\n"$5}' | sort | uniq 
> unique.txt