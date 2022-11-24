mkdir kernelbuild-1
cd kernelbuild-1/
wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.15.79.tar.xz
unxz linux-5.15.79.tar.xz
tar -xvf linux-5.15.79.tar
chown -R $USER:$USER linux-5.15.79
