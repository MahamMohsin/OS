read -p "Enter sentence: " sen
echo $sen

vowel=0
#extracting vowels 
for ((i=0; i<${#sen}; i++)) ;do
	extract="${sen:i:1}"
if [[ "$extract" == "a" || "$extract" == "e" || "$extract" == "i" || "$extract" == "o" || "$extract" == "u" ]];then
	((vowel++))
fi
done

echo "vowel count: " $vowel
