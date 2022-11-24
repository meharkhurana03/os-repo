cd /root/kernelbuild-1/linux-5.15.79
wget -P /root/kernelbuild-1/linux-5.15.79 --no-check-certificate 'https://docs.google.com/uc?export=download&id=1YvJeK9Wfz-1PStKuElGP_0LCEr4zoulU' -O .config
make nconfig
make -j3
