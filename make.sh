gcc src/bs_codec.c -shared -o libs/bs_codec.dll
gcc src/oki_codec.c -shared -o libs/oki_codec.dll
gcc src/yma_codec.c -shared -o libs/yma_codec.dll
gcc src/ymb_codec.c -shared -o libs/ymb_codec.dll
gcc src/ymz_codec.c -shared -o libs/ymz_codec.dll
g++ src/brr_codec.cpp -shared -o libs/brr_codec.dll -static
gcc src/protools_unxor.c -shared -o libs/protools_unxor.dll