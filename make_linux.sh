mkdir linux_64
gcc src/bs_codec.c -shared -o linux_64/bs_codec.so
gcc src/oki_codec.c -shared -o linux_64/oki_codec.so
gcc src/yma_codec.c -shared -o linux_64/yma_codec.so
gcc src/ymb_codec.c -shared -o linux_64/ymb_codec.so
gcc src/ymz_codec.c -shared -o linux_64/ymz_codec.so
g++ src/brr_codec.cpp -shared -o linux_64/brr_codec.so -static
