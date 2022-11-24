mkdir /root/kernelbuild-2
mkdir /root/kernelbuild-3
cp -R /root/kernelbuild-1 /root/kernelbuild-2
cp -R /root/kernelbuild-1 /root/kernelbuild-3
cd /root/kernelbuild-1/linux-5.15.79
make mrproper
cd /root/kernelbuild-2/kernelbuild-1/linux-5.15.79
make mrproper
cd /root/kernelbuild-3/kernelbuild-1/linux-5.15.79
make mrproper
