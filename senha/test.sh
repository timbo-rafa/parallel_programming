FILE=senha
mkdir -p out
for file in in/*.in ; do \
  filename=${file##*/} ; \
  filenamenoext=${filename%%.*} ; \
  ./$FILE < $file > out/${filenamenoext}.out ; \
done
